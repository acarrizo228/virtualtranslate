{		case 983:
		{
		    if(!response)
				return callcmd::filling(playerid);
				
			new
			    fillingid = GetPVarInt(playerid,"fillingid"),
				price = strval(inputtext);

			if(!strlen(inputtext) || !isNumeric(inputtext) || price < 5 || price > 100)
			{
				SendClientMessage(playerid, COLOR_GREY, !"Цена не может быть ниже 5 и выше 100");

				new
				    frmt_filling_price[83];

				format(frmt_filling_price, sizeof frmt_filling_price, "{FFFFFF}Установите новую цену для топлива (от 5$ до 100$)\nТекущая цена: ({33AA33}%d{FFFFFF})", gFillings[fillingid][fillingFuelPrice]);

				ShowPlayerDialogEx(playerid, 983, DIALOG_STYLE_LIST, !"Управление АЗС", frmt_filling_price, !"Изменить", !"Назад");

				return 1;
			}
			
			gFillings[fillingid][fillingFuelPrice] = price;

			new
				query_filling[80 + 6];

			format(query_filling, sizeof query_filling, "UPDATE `fillings` SET `FuelPrice` = '%d' WHERE `ID` = '%d'", gFillings[fillingid][fillingFuelPrice], gFillings[fillingid][fillingID]);
			mysql_tquery(mysql, query_filling);
			
			SendClientMessage(playerid, COLOR_GREEN, !"Цена на топливо изменена");
			UpdateFillingText(fillingid);
			SaveFilling(fillingid);

		}
		case 984:
		{
		    if(!response)
				return callcmd::filling(playerid);
			
			new fillingid = GetPVarInt(playerid,"fillingid");


			switch(listitem)
			{
				case 0:
				{
					if(gFillings[fillingid][fillingTanks] == 10000)
						return SendClientMessage(playerid, COLOR_GREY, !"Вы уже приобрели данное улучшение");

					if(PI[playerid][pMoney] < 125000)
						return SendClientMessage(playerid, COLOR_GREY, !"У вас не хватает денег для покупки данного улучшения.");
						
					new
					    query_improve[80];
					    
					format(query_improve, sizeof query_improve, "UPDATE `fillings` SET `Tanks` = '10000' WHERE ID = '%d'", fillingid+1);
					mysql_tquery(mysql, query_improve);

					if(mysql_errno())
						return SendClientMessage(playerid, COLOR_RED, !"Произошла ошибка MySQL (покупка улучшения для АЗС)");

					gFillings[fillingid][fillingTanks] = 10000;
					GiveMoney(playerid, -125000, "покупка улучшения для АЗС");
					
					SendClientMessage(playerid, COLOR_WHITE, !"Вы успешно приобрели увеличили объем цистерны до 10000 литров.");
                    SaveFilling(fillingid);
				}
			}
		}
		case 972:
		{
		    if(!response)
				return callcmd::filling(playerid);

			new fillingid = GetPVarInt(playerid,"fillingid");

			new
				amount = strval(inputtext);

			if(gFillings[fillingid][fillingTanks] == 10000)
			{
				if(amount < 1 || amount > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное количество топлива");

				if(amount + gFillings[fillingid][fillingFuel] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 топлива");

				if(amount + gFillings[fillingid][fillingFuelOrder] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 топлива");

			}
			else if(gFillings[fillingid][fillingTanks] == 5000)
			{
				if(amount < 1 || amount > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное количество топлива");

				if(amount + gFillings[fillingid][fillingFuel] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 топлива. Купите улучшение чтобы хранить больше.");

				if(amount + gFillings[fillingid][fillingFuelOrder] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 топлива. Купите улучшение чтобы хранить больше.");

			}

			new
				 price = amount*4;

			if(PI[playerid][pMoney] < price)
			{
			    new frmt_buy_products[51 + 9];
				format(frmt_buy_products, sizeof frmt_buy_products, "Вам нужно $%d для того чтобы заказать %d топлива", price, amount);
				SendClientMessage(playerid, COLOR_GREY, frmt_buy_products);
				return 1;
			}

			gFillings[fillingid][fillingFuel] += amount;

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Топливо доставлено");

			GiveMoney(playerid, -price, "заказ топлива");
			SaveFilling(fillingid);
		}
		case 985:
		{
		    if(!response)
				return callcmd::filling(playerid);

			new fillingid = GetPVarInt(playerid,"fillingid");

			new
				amount = strval(inputtext);
			
			if(gFillings[fillingid][fillingTanks] == 10000)
			{
				if(amount < 1 || amount > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное количество топлива");

				if(amount + gFillings[fillingid][fillingFuel] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 топлива");

				if(amount + gFillings[fillingid][fillingFuelOrder] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 топлива");

			}
			else if(gFillings[fillingid][fillingTanks] == 5000)
			{
				if(amount < 1 || amount > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное количество топлива");

				if(amount + gFillings[fillingid][fillingFuel] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 топлива. Купите улучшение чтобы хранить больше.");

				if(amount + gFillings[fillingid][fillingFuelOrder] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 топлива. Купите улучшение чтобы хранить больше.");

			}

			new
				 price = amount*2;

			if(PI[playerid][pMoney] < price)
			{
			    new frmt_buy_products[51 + 9];
				format(frmt_buy_products, sizeof frmt_buy_products, "Вам нужно $%d для того чтобы заказать %d топлива", price, amount);
				SendClientMessage(playerid, COLOR_GREY, frmt_buy_products);
				return 1;
			}
			if(gFillings[fillingid][fillingFuelOrder])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть активный заказ");

			gFillings[fillingid][fillingFuelOrder] += amount;

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Топливо заказано, ожидайте доставки в течении двух часов");

			gFillings[fillingid][fillingOrderTimer] = SetTimerEx("@__FillingOrder",6500000, false, "ii", fillingid, gFillings[fillingid][fillingFuelOrder]);
			GiveMoney(playerid, -price, "заказ топлива");
			SaveFilling(fillingid);
		}
		case 986:
		{
		    if(!response)
				return callcmd::filling(playerid);

			if(!PI[playerid][pBizKey])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет бизнеса");

			new
				fillingid = GetPVarInt(playerid,"fillingid");

			SetString(gFillings[fillingid][fillingOwner], "The State");
			gFillings[fillingid][fillingWorking] = false;

			UpdateFillingText(fillingid);
			SaveFilling(fillingid);

            new frmt_transfer_log[60];
            format(frmt_transfer_log, sizeof frmt_transfer_log, "продажа АЗС (№%d)", fillingid);
			GiveMoney(playerid, gFillings[fillingid][fillingPrice], frmt_transfer_log);

			SendClientMessage(playerid, COLOR_GREEN, !"АЗС продано государству");
			PI[playerid][pBizKey] = 0;
			UpdatePlayerData(playerid, "BizKey", PI[playerid][pBizKey]);
		}
		case 782:
		{
		    if(!response) return 1;
		    if(PI[playerid][pMoney] < 500) return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно денег!");
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили канистру на {FFC800}15 литров. {ffffff}Чтобы заправить ТС подойдите и напишите {FFC800}/fillcar");
			
			new fillingid = GetPVarInt(playerid,"FillID");
   			gFillings[fillingid][fillingFuel] -= 15;
			GiveFillingMoney(fillingid, 500);
			GiveMoney(playerid, -500, "покупка канистры");
			
			DeletePVar(playerid,"FillID");
			SetPlayerAttachedObject(playerid, 6, 1650, 6, 0.131999, 0.014000, 0.037000, 0.000000, -97.900032, -1.000005, 0.979999, 1.000000, 1.000000, 0, 0);

		    temp_canister[playerid] = true;
		    return 1;
		}
		case 751:
		{
		    if(!response)
				return 1;
				
			if(!PI[playerid][pBizKey])
			    return 1;
			    
		    new
				id = PI[playerid][pBizKey] - 1;
				
   			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Бизнес", !"{FFFFFF}Для управления кассой воспользуйтесь {527DFF}банком{FFFFFF} или {527DFF}банкоматом", !"Закрыть", !"");
			    case 1: ShowPlayerDialogEx(playerid, 752, DIALOG_STYLE_INPUT, !"Бизнес", !"{FFFFFF}Введите к-во товара, которое хотите купить:\n{AFAFAF}(1ед. = {FF0000}$2{AFAFAF})", !"Заказать", !"Отмена");
				case 2: ShowPlayerDialogEx(playerid, 744, DIALOG_STYLE_INPUT, !"Бизнес", !"{FFFFFF}Введите к-во товара, которое хотите купить:\n{AFAFAF}(1ед. = {FF0000}$4 (ЭКСПРЕСС){AFAFAF})", !"Заказать", !"Отмена");
				case 3:
       			{
				   	new
					   	business_info[390 + 52 + MAX_PLAYER_NAME + 4 + 11 + 11 + 5 + 5 + 5 + 6 + 20 + 80],
		        		dayprice;
		        		
			       	dayprice = BizInfo[id][bCost]/800;
			        //else dayprice = gBusiness[id][businessSellPrice]/400;

			        format(business_info, sizeof business_info,
					"{4682B4}Название:\t{FFFFFF}%s\n\
					{4682B4}Владелец:\t{FFFFFF}%s\n\
					{4682B4}Кол-во дней:\t{FFFFFF}%d\n\
					{4682B4}Гос. цена\t{FFFFFF}$%d\n\
					{4682B4}Касса:\t\t{FFFFFF}$%d\n\
					{4682B4}Цена товара:\t{FFFFFF}$%d\n", BizInfo[id][bName], BizInfo[id][bOwner], BizInfo[id][bDays], BizInfo[id][bCost], BizInfo[id][bMoney], BizInfo[id][bProdPrice]);
					
					format(business_info, sizeof business_info,
					"%s{4682B4}К-во товара:\t{FFFFFF}%d ед\n\
					{4682B4}Заказано:\t{FFFFFF}%d ед\n\
					{4682B4}Оплата:\t{FFFFFF}$%d/день\n\
					{4682B4}Состояние:\t{FFFFFF}%s\n\n\
					{4682B4}Посетителей за последние 24 часа: {FFFFFF}%d чел", business_info, BizInfo[id][bProducts], BizInfo[id][bProductsOrder], dayprice, (BizInfo[id][bLock]) ? ("{33AA33}Открыт") : ("{FF0000}Закрыт"), BizInfo[id][bVisit]);
			        ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Бизнес", business_info, !"OK", !"");
			    }
				case 4:
				{
					new
						frmt_improve[329];
						
					for(new i; i < 3; i++)
					{
						if(!i)
							format(frmt_improve, sizeof frmt_improve, "{FF7319}%d. {FFFFFF}%s\t{33AA33}%d$", i+1, BusinessImproveName[i], BusinessImprovePrice[i]);

						else
							format(frmt_improve, sizeof frmt_improve, "%s\n{FF7319}%d. {FFFFFF}%s\t{33AA33}%d$", frmt_improve, i+1, BusinessImproveName[i], BusinessImprovePrice[i]);
					}
					
					ShowPlayerDialogEx(playerid, 753, DIALOG_STYLE_LIST, !"Бизнес (Улучшения)", frmt_improve, !"Выбор", !"Отмена");
				}
				case 5:
				{
				    if(BizInfo[id][bState] == 15 || BizInfo[id][bState] == 14 || BizInfo[id][bState] >= 8 && BizInfo[id][bState] <= 11)
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция недоступна в Вашем бизнесе");
				        
					if(BizInfo[id][bLock])
					{
						BizInfo[id][bLock] = 0;
						SendClientMessage(playerid, 0x269BD8FF, !"Бизнес закрыт");
					}
					else
					{
						BizInfo[id][bLock] = 1;
						SendClientMessage(playerid, 0x269BD8FF, !"Бизнес открыт");
					}
					UpdateBiz(id,1);
				}
				case 6:
				{
				    new
				        frmt_sell_business[180 + 9];

					format(frmt_sell_business, sizeof frmt_sell_business, "{FFFFFF}Вы действительно хотите продать свой бизнес государству за {33AA33}$%d\n{AFAFAF}(Если вы хотите продать бизнес другому игроку используйте /sellbusiness [ID игрока] [Сумма])", BizInfo[id][bCost]);
					ShowPlayerDialogEx(playerid, 754, DIALOG_STYLE_MSGBOX, !"Бизнес", frmt_sell_business, !"Да", !"Нет");
				}
				case 7:
				{
				    if(BizInfo[id][bState] == 15 || BizInfo[id][bState] >= 8 && BizInfo[id][bState] <= 11)
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция недоступна в Вашем бизнесе");
				        
					ShowPlayerDialogEx(playerid, 755, DIALOG_STYLE_INPUT, !"Бизнес", !"{FFFFFF}Введите цену за вход, которую хотите установить: (от 0 до 3000)", !"Принять", !"Отмена");
				}
				case 8: ShowPlayerDialogEx(playerid, 756, DIALOG_STYLE_INPUT, !"Бизнес", !"{FFFFFF}Введите цену за 1 ед. товара (от 1 до 500)", !"ОК", !"Отмена");
				case 9: ShowFinancStatDialog(playerid, id+1);
				//case 9: ShowPlayerDialogEx(playerid, 502, 2, !"Бизнес (Работники)", !"Работники бизнеса:\n{3366FF}1. {FFFFFF} Нажмите чтобы назначить\n{3366FF}2. {FFFFFF} Нажмите чтобы назначить\n{3366FF}3. {FFFFFF} Нажмите чтобы назначить", "Выбор", "Отмена");

			}

		}
		case 744:
		{
			if(!response)
				return callcmd::business(playerid,"");

			new
				id = PI[playerid][pBizKey] - 1,
				prod = strval(inputtext);

			if(BizInfo[id][bImprove][1])
			{
				if(prod < 1 || prod > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное к-во товара");

				if(prod + BizInfo[id][bProducts] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 ед. товара");

				if(prod + BizInfo[id][bProductsOrder] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 ед. товара");

			}
			else
			{
				if(prod < 1 || prod > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное к-во товара");

				if(prod + BizInfo[id][bProducts] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 ед. товара. Купите улучшение чтобы хранить больше.");

				if(prod + BizInfo[id][bProductsOrder] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 ед. товара. Купите улучшение чтобы хранить больше.");

			}

			new
				 price = prod*4;

			if(PI[playerid][pMoney] < price)
			{
			    new frmt_buy_products[51 + 9];
				format(frmt_buy_products, sizeof frmt_buy_products, "Вам нужно $%d для того чтобы заказать %d ед. товара", price, prod);
				SendClientMessage(playerid, COLOR_GREY, frmt_buy_products);
				return 1;
			}

			BizInfo[id][bProducts] += prod;

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Товар доставлен в Ваш бизнес");

			GiveMoney(playerid, -price, "заказ товара");

			UpdateBiz(id,1);
		}
		case 752:
		{
   			if(!response) return true;
	        new idx = PI[playerid][pBizKey];
   			new count;
			for(new i = 1; i <= TOTALPRODUCT; i++)
			{
				if(ProductInfo[i][pBizid] == idx) count++;
			}
			if(count) return SCM(playerid, COLOR_GREY, "Извините, заказ для этого бизнеса уже есть в базе данных!");
			new amount,prod = strval(inputtext);
			new lstring[128];
			if(sscanf(inputtext, "d", amount)) return callcmd::business(playerid,"");
			if(BizInfo[idx][bImprove][1])
			{
				if(prod < 1 || prod > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное к-во товара");

				if(prod + BizInfo[idx][bProducts] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 ед. товара");

				if(prod + BizInfo[idx][bProductsOrder] > 10000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 10000 ед. товара");

			}
			else
			{
				if(prod < 1 || prod > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Неверное к-во товара");

				if(prod + BizInfo[idx][bProducts] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 ед. товара. Купите улучшение чтобы хранить больше.");

				if(prod + BizInfo[idx][bProductsOrder] > 5000)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 5000 ед. товара. Купите улучшение чтобы хранить больше.");

			}

			new
				 price = prod*2;

			if(PI[playerid][pMoney] < price)
			{
			    new frmt_buy_products[51 + 9];
				format(frmt_buy_products, sizeof frmt_buy_products, "Вам нужно $%d для того чтобы заказать %d ед. товара", price, prod);
				SendClientMessage(playerid, COLOR_GREY, frmt_buy_products);
				return 1;
			}
			TOTALPRODUCT++;
			strmid(ProductInfo[TOTALPRODUCT][pName], PN(playerid), 0, strlen(PN(playerid)), MAX_PLAYER_NAME);
			ProductInfo[TOTALPRODUCT][pPrice] = price;
			ProductInfo[TOTALPRODUCT][pTill] = prod;
			ProductInfo[TOTALPRODUCT][pBizid] = idx;
			ProductInfo[TOTALPRODUCT][pStatus] = 0;
			GiveMoney(playerid,-price);
			format(lstring, sizeof(lstring), "{7AC71F}[Успешно] {ffffff}Вы заказали {FFC800}%d товара. {ffffff}С вас списано {FFC800}$%d.", prod, ProductInfo[TOTALPRODUCT][pPrice]);
			SCM(playerid, COLOR_WHITE, lstring);
			foreach(new p:Player)
			{
				if(!IsPlayerConnected(p) || IsPlayerLogged[p] == false || PI[p][pJob] != JOB_PRODUCT) continue;
				format(lstring, sizeof(lstring), "{FFC800}[Диспетчер] {ffffff}Поступил новый заказ: {FFC800}%d товара{ffffff} от {FFC800}%s.", prod, PN(playerid));
				SCM(p, COLOR_WHITE, lstring);
				SCM(p, 0x269BD8FF, "Чтобы принять заказ нажмите {33AA33}'Y' {269BD8}на складе продуктов.");
			}
			ProductInfo[TOTALPRODUCT][idxx] = TOTALPRODUCT;
			new request[513];
			format(request, 512, "INSERT INTO `product` (`id`, `name`, `price`, `till`, `biz`, `status`) VALUES ('%i', '%s', '%i', '%i', '%i', '%i')",
			TOTALPRODUCT, ProductInfo[TOTALPRODUCT][pName], ProductInfo[TOTALPRODUCT][pPrice], ProductInfo[TOTALPRODUCT][pTill], ProductInfo[TOTALPRODUCT][pBizid],
			ProductInfo[TOTALPRODUCT][pStatus]);
			mysql_query(mysql, request);
		}
		case 753:
		{
			if(!response)
				return callcmd::business(playerid,"");

			new
				id = PI[playerid][pBizKey] - 1;
				
			if(BizInfo[id][bImprove][listitem])
			{
				new
					frmt_improve[329];

				for(new i; i < 3; i++)
				{
					if(!i)
						format(frmt_improve, sizeof frmt_improve, "{FF7319}%d. {FFFFFF}%s\t{33AA33}%d$", i+1, BusinessImproveName[i], BusinessImprovePrice[i]);

					else
						format(frmt_improve, sizeof frmt_improve, "%s\n{FF7319}%d. {FFFFFF}%s\t{33AA33}%d$", frmt_improve, i+1, BusinessImproveName[i], BusinessImprovePrice[i]);
				}

				ShowPlayerDialogEx(playerid, 753, DIALOG_STYLE_LIST, !"Бизнес (Улучшения)", frmt_improve, !"Выбор", !"Отмена");
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже приобрели данное улучшение");
			}
			
			new
				price = BusinessImprovePrice[listitem];
				
			if(PI[playerid][pMoney] < price)
				return SendClientMessage(playerid, COLOR_GREY, !"У вас не хватает денег для покупки данного улучшения.");

			BizInfo[id][bImprove][listitem] = 1;
			GiveMoney(playerid, -price, "покупка улучшения для бизнеса");


			new
				data[32],
				query[128];
				
			for(new i; i < 3; i++)
			{
				if(!i) format(data, sizeof data, "%d", BizInfo[id][bImprove][i]);
				else format(data, sizeof data, "%s|%d", data, BizInfo[id][bImprove][i]);
			}
			
			format(query, sizeof query,"UPDATE `business` SET `Improve` = '%s' WHERE ID = '%d'", data, id+1);
			print(query);
			mysql_tquery(mysql, query);
			
			SaveBiz(id);
			
			if(mysql_errno())
				return SendClientMessage(playerid, COLOR_RED, !"Произошла ошибка MySQL (покупка улучшения для бизнеса)");

			new format_business_improve[59 + 64];
			format(format_business_improve, sizeof format_business_improve, "{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели данное улучшение {9ACD32}(%s){FFFFFF}.", BusinessImproveName[listitem]);
			SendClientMessage(playerid,COLOR_WHITE,format_business_improve);
			
			switch(listitem)
			{
				case 0: SendClientMessage(playerid,COLOR_WHITE,"Теперь вы можете восстановить свое здоровье, находясь внутри бизнеса {33AAFF}(/healup) {FFFFFF}- {00CC00}$150{FFFFFF}.");
				case 1: SendClientMessage(playerid,COLOR_WHITE,"Теперь количество продуктов вашего бизнеса может быть в 2 раза больше.");
				case 2: SendClientMessage(playerid,COLOR_WHITE,"Теперь ваш бизнес будет отображаться в GPS (Пункт \"Бизнесы\").");
			}
			new
				frmt_improve[329];

			for(new i; i < 3; i++)
			{
				if(!i)
					format(frmt_improve, sizeof frmt_improve, "{FF7319}%d. {FFFFFF}%s\t{33AA33}%d$", i+1, BusinessImproveName[i], BusinessImprovePrice[i]);

				else
					format(frmt_improve, sizeof frmt_improve, "%s\n{FF7319}%d. {FFFFFF}%s\t{33AA33}%d$", frmt_improve, i+1, BusinessImproveName[i], BusinessImprovePrice[i]);
			}

			ShowPlayerDialogEx(playerid, 753, DIALOG_STYLE_LIST, !"Бизнес (Улучшения)", frmt_improve, !"Выбор", !"Отмена");
		}
		case 754:
		{
			if(!response)
				return callcmd::business(playerid,"");

			if(!PI[playerid][pBizKey])
			    return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет бизнеса");
			    
			new
				id = PI[playerid][pBizKey] - 1,
				query_sell_business[100 + 6];

			SetString(BizInfo[id][bOwner], "The State");
			BizInfo[id][bLock] = 1;

			format(query_sell_business,sizeof query_sell_business,"UPDATE `business` SET `Owner` = 'The State', `Lock` = '1' WHERE `ID` = '%d'", id+1);
			mysql_tquery(mysql, query_sell_business);
			
			UpdateBiz(id,1);
			
            new frmt_transfer_log[60];
            format(frmt_transfer_log, sizeof frmt_transfer_log, "продажа бизнеса (№%d)", id);
			GiveMoney(playerid, BizInfo[id][bCost], frmt_transfer_log);
	
			SendClientMessage(playerid, COLOR_GREEN, !"Бизнес продан государству");
			PI[playerid][pBizKey] = 0;
			UpdatePlayerData(playerid, "BizKey", PI[playerid][pBizKey]);
		}
		case 755:
		{
			if(!response)
				return callcmd::business(playerid,"");

			new
				id = PI[playerid][pBizKey] - 1;
				
			if(strval(inputtext) < 0 || strval(inputtext) > 3000)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Неверная сумма (от 0$ до 3000$)");
				
			BizInfo[id][bEnterPrice] = strval(inputtext);
			
			SendClientMessage(playerid, COLOR_GREEN, !"Цена за вход успешно установлена.");
 			UpdateBiz(id,1);
		}
		case 756:
		{
			if(!response)
				return callcmd::business(playerid,"");

			new
				id = PI[playerid][pBizKey] - 1;
				
			if(strval(inputtext) < 1 || strval(inputtext) > 500)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Неверная цена (1-500)");
				
			BizInfo[id][bProdPrice] = strval(inputtext);
			
			SendClientMessage(playerid, COLOR_GREEN, !"Новая цена товара установлена");
 			UpdateBiz(id,1);
		}
		case 760:
		{
  	        if(!response)
			  	return 1;

			new
				businessid = InfoBiz[playerid];
			
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, BizInfo[businessid][bEnter_X], BizInfo[businessid][bEnter_Y], BizInfo[businessid][bEnter_Z]))
				return 1;

		    new
				price = BizInfo[businessid][bEnterPrice];
			
			if(PI[playerid][pMoney] < price)
				return SendClientMessage(playerid,COLOR_GREY,"Недостаточно денег");

			new bint = BizInfo[businessid][bBint]-1;
			
			if(bint < 0 || bint >= MAX_BINTS)
				return SendClientMessage(playerid,COLOR_GREY,"Ошибка (#99)");

            justtp_exit[playerid] = true;

  			SetPlayerPos(playerid, BizInts[bint][bintX], BizInts[bint][bintY], BizInts[bint][bintZ]);

			SetPlayerInterior(playerid, BizInts[bint][bintInterior]);
			SetPlayerVirtualWorld(playerid, businessid+1);
			SetPlayerFacingAngle(playerid, BizInts[bint][bintR]);
			BizEntered[playerid] = BizInfo[businessid][bID];
			BizInfo[businessid][bVisit] ++;
			if(BizInfo[businessid][bImprove][0])
				SendClientMessage(playerid,COLOR_GREY,"В этом бизнесе имеется аптечка. Чтобы восстановить здоровье используйте {FFFFFF}/healup ({00CC00}$150{FFFFFF})");

			GiveMoney(playerid, -BizInfo[businessid][bEnterPrice], "вход в бизнес");
			
			if(BizInfo[businessid][bState] == 1)
			    GiveBusinessMoney(businessid, price/100*15);
			
			else if(BizInfo[businessid][bState] == 2 || BizInfo[businessid][bState] == 3 || BizInfo[businessid][bState] == 4 || BizInfo[businessid][bState] == 5 || BizInfo[businessid][bState] == 6)
			    GiveBusinessMoney(businessid, price/100*45);

			else if(BizInfo[businessid][bState] == 7)
				GiveBusinessMoney(businessid, price/100*35);
				
			else if(BizInfo[businessid][bState] == 12)
				GiveBusinessMoney(businessid, price/100*25);
				
			else
			    GiveBusinessMoney(businessid, price/100*45);

            if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],price/100*10);
			UpdateBiz(businessid,1);

		}
		case 961:
		{
  	        if(!response)
			  	return 1;

			if(PI[playerid][pFraction] != 7)
				return 1;

			if(PI[playerid][pSubfraction] != 1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в Армии Las Venturas");

			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем т/с");

			new
			    carid = GetPlayerVehicleID(playerid);

			if(VehicleInfo[carid][vTeam] != 7 || VehicleInfo[carid][vSubTeam] != 1 || GetVehicleModel(carid) != 433)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем машины для перевозки оружия");

			if(VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");


			VehicleLoad[carid][vlID] = carid;
			VehicleLoad[carid][vlLoading] = true;
			VehicleLoad[carid][vlUnloading] = false;

		    RemovePlayerFromVehicle(playerid);

			new
				Float:x,
				Float:y,
				Float:z,
				Float:a;

			GetVehiclePos(carid, x, y, z);
			GetVehicleZAngle(carid, a);
			x = x - (-6.0*floatsin(a, degrees));
			y = y -6.0*floatcos(a, degrees);
			VehicleLoad[carid][vlPickup] = CreateDynamicPickup(2061, 1, x, y, z-0.5);
			VehicleLoad[carid][vlArea] = CreateDynamicSphere(x, y, z-0.5, 1.0);
			
			new
				mes[128];

			format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[carid][vlLimit]);
			VehicleLoad[carid][vlText] = CreateDynamic3DTextLabel(mes, COLOR_WHITE, x, y, z+0.5, 10.0);

		    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали загрузку боеприпасов. Загрузите их и отправляйтесь на отмеченное место");

		    switch(listitem)
		    {
		        case 0: SetPlayerCheckpointExx(playerid, 1524.4845, -1677.8949, 6.2188, 4.0), VehicleLoad[carid][vlLoadFr] = 8, VehicleLoad[carid][vlLoadSf] = 1;
		        case 1: SetPlayerCheckpointExx(playerid, -1606.3378, 672.0713, -4.9063, 4.0), VehicleLoad[carid][vlLoadFr] = 8, VehicleLoad[carid][vlLoadSf] = 2;
		        case 2: SetPlayerCheckpointExx(playerid, 2297.1123, 2468.7571, 10.8203, 4.0), VehicleLoad[carid][vlLoadFr] = 8, VehicleLoad[carid][vlLoadSf] = 3;
                case 3: SetPlayerCheckpointExx(playerid, -2514.5027,-679.0071,139.3203, 4.0), VehicleLoad[carid][vlLoadFr] = 11, VehicleLoad[carid][vlLoadSf] = 0;
		        case 4: SetPlayerCheckpointExx(playerid, 1132.2310,-2036.9891,69.0078, 4.0), VehicleLoad[carid][vlLoadFr] = 10, VehicleLoad[carid][vlLoadSf] = 0;
		        case 5: SetPlayerCheckpointExx(playerid, 1481.2008,-1765.9036,18.7958, 4.0), VehicleLoad[carid][vlLoadFr] = 10, VehicleLoad[carid][vlLoadSf] = 1;
		        case 6: SetPlayerCheckpointExx(playerid, -2756.8206,375.7390,4.3343, 4.0), VehicleLoad[carid][vlLoadFr]= 10, VehicleLoad[carid][vlLoadSf] = 2;
		        case 7: SetPlayerCheckpointExx(playerid, 2385.2861,2465.8862,10.8203, 4.0), VehicleLoad[carid][vlLoadFr] = 10, VehicleLoad[carid][vlLoadSf] = 3;
		    }
		    

       		foreach(new i : Player)
		    {
		        if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
		            continue;

				if(PI[i][pFraction] != 7)
				    continue;

				temp_army_loadfr[i] = 7;
			}
		}
		case 488:
		{
		    if(!response)
		        return SelectTextDraw(playerid, 0xFFFFFFFF);
		        
			if(temp_table[playerid] == -1)
			    return 1;
			    

                
			new
				tableid = temp_table[playerid];
				
            if(!IsPlayerInDynamicArea(playerid, gCasinoTableCrupie[tableid]))
                return 1;
                
            for(new i; i < 4; i++)
            {
                if(gTable[tableid][tPlayers][i] == playerid && gTable[tableid][tStatus] != true)
                {
                    new frmt_transfer_log[60];
                    format(frmt_transfer_log, sizeof frmt_transfer_log, "вернул деньги (стол: %d)", tableid);
					GiveMoney(playerid, gTable[tableid][tBet], frmt_transfer_log);

                    gTable[tableid][tPlayers][i] = INVALID_PLAYER_ID;
                    
 				    /*for(new pl = 0, j = GetPlayerPoolSize(); pl <= j; i++)
				    {
					    if(temp_table[pl] == tableid && Casino_GetPlayerID(tableid, pl) != -1)
                    		gTable[tableid][tPlayers][Casino_GetSlot(tableid)] = pl;
                    }*/

					
				}
				else if(gTable[tableid][tPlayers][i] == playerid && gTable[tableid][tStatus] == true)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игра уже началась");

			}
            for(new td = 0; td < 22; td++)
				PlayerTextDrawHide(playerid, casino_table[tableid][td]);

            CancelSelectTextDraw(playerid);


            new frmt_player_bet[20 + MAX_PLAYER_NAME];

		    new
		        check[4];

			for(new t; t < 4; t++)
				check[t] = INVALID_PLAYER_ID;

       		foreach(new i : Player)
		    {
		        if(temp_table[i] == tableid)
		        {
					for(new t; t < 4; t++)
					{
                        if(gTable[tableid][tPlayers][t] != INVALID_PLAYER_ID)
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~1. ~w~%s", PN(gTable[tableid][tPlayers][t]));
							PlayerTextDrawSetString(i, casino_table[tableid][8], frmt_player_bet);
							check[0] = gTable[tableid][tPlayers][t];
							break;
						}
					}
					for(new t; t < 4; t++)
					{
                        if(gTable[tableid][tPlayers][t] != INVALID_PLAYER_ID && check[0] != gTable[tableid][tPlayers][t])
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~2. ~w~%s", PN(gTable[tableid][tPlayers][t]));
							PlayerTextDrawSetString(i, casino_table[tableid][9], frmt_player_bet);
							check[1] = gTable[tableid][tPlayers][t];
							break;
						}
					}
					for(new t; t < 4; t++)
					{
                        if(gTable[tableid][tPlayers][t] != INVALID_PLAYER_ID && check[0] != gTable[tableid][tPlayers][t] && check[1] != gTable[tableid][tPlayers][t])
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~3. ~w~%s", PN(gTable[tableid][tPlayers][t]));
							PlayerTextDrawSetString(i, casino_table[tableid][10], frmt_player_bet);
							check[2] = gTable[tableid][tPlayers][t];
							break;
						}
					}
					for(new t; t < 4; t++)
					{
                        if(gTable[tableid][tPlayers][t] != INVALID_PLAYER_ID && check[0] != gTable[tableid][tPlayers][t] && check[1] != gTable[tableid][tPlayers][t] && check[2] != gTable[tableid][tPlayers][t])
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~4. ~w~%s", PN(gTable[tableid][tPlayers][t]));
							PlayerTextDrawSetString(i, casino_table[tableid][11], frmt_player_bet);
							check[3] = gTable[tableid][tPlayers][t];
							break;
						}
					}


					if(check[0] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(i, casino_table[tableid][8], "-");

					if(check[1] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(i, casino_table[tableid][9], "-");

					if(check[2] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(i, casino_table[tableid][10], "-");

					if(check[3] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(i, casino_table[tableid][11], "-");

					format(frmt_player_bet, sizeof frmt_player_bet, "%d$", gTable[tableid][tBet]);
					PlayerTextDrawSetString(i, casino_table[tableid][16], frmt_player_bet);

					format(frmt_player_bet, sizeof frmt_player_bet, "%d$", gTable[tableid][tBet]*Casino_TotalPlayer(tableid));
					PlayerTextDrawSetString(i, casino_table[tableid][17], frmt_player_bet);
				}
			}
		    format(frmt_player_bet, sizeof frmt_player_bet, "%d/4", Casino_TotalPlayer(tableid));
		    TextDrawSetString(crupie_table[tableid][6], frmt_player_bet);

			temp_table[playerid] = -1;
		}
		case 489:
		{
		    if(!response)
		        return 1;
		        
			new
				tableid = temp_table[playerid];
				
            if(!IsPlayerInDynamicArea(playerid, gCasinoTableCrupie[tableid]))
                return 1;
                
			if(InJob[playerid] != 8)
			    return 1;

			if(Casino_TotalPlayer(tableid) > 0)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже идет активная игра");

			if(!strlen(inputtext) || !isNumeric(inputtext))
			    return ShowPlayerDialogEx(playerid, 489, DIALOG_STYLE_INPUT, !"Ставка", !"{FFFFFF}Введите сумму ставки для стола\n\nМинимальная ставка: {FF0000}1000${FFFFFF}\nМаксимальная ставка: {FF0000}10000000$", !"Изменить", !"Отмена");
			    
            if(strval(inputtext) < 1000 || strval(inputtext) > 10000000)
   			    return ShowPlayerDialogEx(playerid, 489, DIALOG_STYLE_INPUT, !"Ставка", !"{FFFFFF}Введите сумму ставки для стола\n\nМинимальная ставка: {FF0000}1000${FFFFFF}\nМаксимальная ставка: {FF0000}10000000$", !"Изменить", !"Отмена");

			gTable[tableid][tBet] = strval(inputtext);
			
		    new
				frmt_bet[26];

		    format(frmt_bet, sizeof frmt_bet, "%d$", gTable[tableid][tBet]);
		    TextDrawSetString(crupie_table[tableid][5], frmt_bet);

			for(new pi = 0, j = GetPlayerPoolSize(); pi <= j; pi++)
			{
				if(temp_table[pi] == tableid)
		        {
				    format(frmt_bet, sizeof frmt_bet, "%d$", gTable[tableid][tBet]);
				    PlayerTextDrawSetString(pi, casino_table[tableid][16], frmt_bet);
				}
			}

		}


		case 133:
		{
		    if(!response) return 1;
		    
			if(temp_table[playerid] != -1)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете использовать анимации во время игры в казино");

			if(temp_hold_sender[playerid] != INVALID_PLAYER_ID)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете использовать анимации в данный момент");

			if(temp_cuffer_sender[playerid] != INVALID_PLAYER_ID)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете использовать анимации в наручниках");

		    if(GetPVarInt(playerid,"narko") > gettime())
				return 1;

		    if(GetPVarInt(playerid,"healme") > gettime())
				return 1;

		    if(GetPVarInt(playerid,"mask") > gettime())
				return 1;


			if(temp_tie_sender[playerid] != INVALID_PLAYER_ID)
			    return 1;

		    switch(listitem)
		    {
		        case 0: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE1);
		        case 1: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE2);
		        case 2: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE3);
		        case 3: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE4);
		        case 4: GoAnim(playerid,"DEALER","Dealer_idle",4.1,1,0,0,0,0,0);
		        case 5: ApplyAnimation(playerid,"DEALER","Dealer_Deal",4.1,0,0,0,0,0,1);
		        case 6: ApplyAnimation(playerid,"FOOD","Eat_Burger",4.1,0,0,0,0,0,1);
				case 7: ApplyAnimation(playerid,"PAULNMAC","Piss_in",4.1,0,0,0,0,0,1);
				case 8: GoAnim(playerid,"PARK","Tai_Chi_Loop",4.1,1,0,0,0,0,0);
				case 9: GoAnim(playerid,"CRACK","Crckidle1",4.1,1,0,0,0,0,0);
				case 10: GoAnim(playerid,"CRACK","Crckidle2",4.1,1,0,0,0,0,0);
				case 11: GoAnim(playerid,"CRACK","Crckidle4",4.1,1,0,0,0,0,0);
				case 12: ApplyAnimation(playerid,"SWEET","sweet_ass_slap",4.1,0,0,0,0,0,1);
				case 13: GoAnim(playerid,"SPRAYCAN","spraycan_full",4.1,1,0,0,0,0,0);
				case 14: GoAnim(playerid,"GRAFFITI","spraycan_fire",4.1,1,0,0,0,0,0);
				case 15: GoAnim(playerid,"SMOKING","M_smkstnd_loop",4.1,1,0,0,0,0,0);
				case 16: GoAnim(playerid,"SHOP","ROB_Loop_Threat",4.1,1,0,0,0,0,0);
				case 17: ApplyAnimation(playerid,"SHOP","ROB_shifty",4.1,0,0,0,0,0,1);
				case 18: GoAnim(playerid,"SHOP","SHP_Rob_HandsUP",4.1,1,0,0,0,0,0);
				case 19: GoAnim(playerid,"RYDER","Ryd_Beckon_02",4.1,1,0,0,0,0,0);
				case 20: ApplyAnimation(playerid,"RIOT","Riot_Angry",4.1,0,0,0,0,0,0);
				case 21: GoAnim(playerid,"RIOT","Riot_Angry_B",4.1,1,0,0,0,0,0);
				case 22: GoAnim(playerid,"RIOT","Riot_Chant",4.1,1,1,0,0,0,0);
				case 23: GoAnim(playerid,"RIOT","Riot_Punches",4.1,1,0,0,0,0,0);
				case 24: ApplyAnimation(playerid,"PED","fucku",4.1,0,0,0,0,0,1);
		        case 25: ApplyAnimation(playerid,"BAR","dnK_StndM_loop",4.1,0,0,0,0,0,1);
		        case 26: GoAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,1,0,0,0,0,0);
		        case 27: GoAnim(playerid,"BD_FIRE","M_smklean_loop",4.1,1,0,0,0,0,0);
				case 28: GoAnim(playerid,"BEACH","bather",4.1,1,0,0,0,0,0);
				case 29: GoAnim(playerid,"BEACH","Lay_Bac_loop",4.1,1,0,0,0,0,0);
				case 30: GoAnim(playerid,"BEACH","Parksit_w_loop",4.1,1,0,0,0,0,0);
				case 31: GoAnim(playerid,"BEACH","Sitnwait_Loop_W",4.1,1,0,0,0,0,0);
				case 32: GoAnim(playerid,"BEACH","Parksit_M_loop",4.1,1,0,0,0,0,0);
				case 33: GoAnim(playerid,"benchpress","gym_bp_celebrate",4.1,1,0,0,0,0,0);
				case 34: GoAnim(playerid,"LOWRIDER","Rap_C_loop",4.1,1,0,0,0,0,0);
				case 35: GoAnim(playerid,"LOWRIDER","Rap_B_loop",4.1,1,0,0,0,0,0);
				case 36: GoAnim(playerid,"LOWRIDER","Rap_A_loop",4.1,1,0,0,0,0,0);
				case 37: GoAnim(playerid,"BSKTBALL","BBALL_idleloop",4.1,1,0,0,0,0,0);
				case 38: ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.1,0,0,0,0,0,1);
				case 39: ApplyAnimation(playerid,"BSKTBALL","BBALL_pickup",4.1,0,0,0,0,0,1);
				case 40: ApplyAnimation(playerid,"CAMERA","camstnd_cmon",4.1,0,0,0,0,0,1);
				case 41: GoAnim(playerid,"CAR","fixn_car_loop",4.1,1,0,0,0,0,0);
				case 42: GoAnim(playerid,"CAR_CHAT","car_talkm_loop",4.1,1,0,0,0,0,0);
				case 43: GoAnim(playerid,"COP_AMBIENT","coplook_loop",4.1,1,0,0,0,0,0);
				case 44: GoAnim(playerid,"CRACK","Bbalbat_Idle_01",4.1,1,0,0,0,0,0);
		        case 45: GoAnim(playerid,"CRACK","Bbalbat_Idle_02",4.1,1,0,0,0,0,0);
		        case 46: ApplyAnimation(playerid,"GHANDS","gsign1",4.1,0,0,0,0,0,1);
		        case 47: ApplyAnimation(playerid,"GHANDS","gsign2",4.1,0,0,0,0,0,1);
		        case 48: ApplyAnimation(playerid,"GHANDS","gsign3",4.1,0,0,0,0,0,1);
				case 49: ApplyAnimation(playerid,"GHANDS","gsign4",4.1,0,0,0,0,0,1);
				case 50: ApplyAnimation(playerid,"GHANDS","gsign5",4.1,0,0,0,0,0,1);
				case 51: ApplyAnimation(playerid,"GHANDS","gsign1LH",4.1,0,0,0,0,0,1);
				case 52: ApplyAnimation(playerid,"GHANDS","gsign2LH",4.1,0,0,0,0,0,1);
				case 53: ApplyAnimation(playerid,"GHANDS","gsign4LH",4.1,0,0,0,0,0,1);
				case 54: GoAnim(playerid,"GRAVEYARD","mrnF_loop",4.1,1,0,0,0,0,0);
				case 55: GoAnim(playerid,"MISC","seat_LR",4.1,1,0,0,0,0,0);
				case 56: GoAnim(playerid,"INT_HOUSE","Lou_in",4.1,0,1,1,1,1,0);
				case 57: GoAnim(playerid,"INT_OFFICE","OFF_sit_Bored_loop",4.1,1,0,0,0,0,0);
				case 58: GoAnim(playerid,"LOWRIDER","F_smklean_loop",4.1,1,0,0,0,0,0);
				case 59: ApplyAnimation(playerid,"MEDIC","CPR",4.1,0,0,0,0,0,1);
				case 60: GoAnim(playerid,"GANGS","LeanIn",4.1,0,1,1,1,1,0);
				case 61: GoAnim(playerid,"MISC","plyrlean_loop",4.1,1,0,0,0,0,0);
				case 62: ApplyAnimation(playerid,"MISC","plyr_shkhead",4.1,0,0,0,0,0,1);
				case 63: GoAnim(playerid,"MISC","scratchballs_01",4.1,1,0,0,0,0,0);
				case 64: GoAnim(playerid,"BOMBER","BOM_Plant",4.1,1,0,0,0,0,0);
				case 65: GoAnim(playerid,"CRACK","crckdeth2",4.1,1,0,0,0,0,0);
				case 66: GoAnim(playerid,"CRACK","crckdeth3",4.1,1,0,0,0,0,0);
				case 67: GoAnim(playerid,"CRACK","crckdeth1",4.1,1,0,0,0,0,0);
				case 68: GoAnim(playerid,"DANCING","dance_loop",4.1,1,0,0,0,0,0);
				case 69: GoAnim(playerid,"DANCING","DAN_Left_A",4.1,1,0,0,0,0,0);
				case 70: GoAnim(playerid,"DANCING","dnce_M_a",4.1,1,0,0,0,0,0);
				case 71: GoAnim(playerid,"DANCING","dnce_M_b",4.1,1,0,0,0,0,0);
				case 72: GoAnim(playerid,"DANCING","dnce_M_d",4.1,1,0,0,0,0,0);
				case 73: GoAnim(playerid,"GANGS","prtial_gngtlkD",4.1,1,0,0,0,0,0);
				case 74: GoAnim(playerid,"GANGS","smkcig_prtl",4.1,1,0,0,0,0,0);
				case 75: GoAnim(playerid,"DANCING","Dan_Down_a",4.1,1,0,0,0,0,0);
				case 76: GoAnim(playerid,"DANCING","Dan_Left_A",4.1,1,0,0,0,0,0);
				case 77: GoAnim(playerid,"DANCING","Dan_Loop_A",4.1,1,0,0,0,0,0);
				case 78: GoAnim(playerid,"DANCING","Dan_Right_A",4.1,1,0,0,0,0,0);
				case 79: GoAnim(playerid,"DANCING","Dan_up_a",4.1,1,0,0,0,0,0);
				case 80: GoAnim(playerid,"DANCING", "Dnce_M_a",4.1,1,0,0,0,0,0);
				case 81: GoAnim(playerid,"DANCING", "Dnce_M_b",4.1,1,0,0,0,0,0);
				case 82: GoAnim(playerid,"DANCING", "Dnce_M_с",4.1,1,0,0,0,0,0);
				case 83: GoAnim(playerid,"DANCING", "Dnce_M_d",4.1,1,0,0,0,0,0);
		    }
		    TextDrawShowForPlayer(playerid, AnimDraw);
		    SetPVarInt(playerid,"Animation", 1);
		    return 1;
		}
		case 66:
		{
			if(!response)
			    return 1;
			    
			switch(listitem)
			{
		    	case 0:
		    	{
	   				new str[1550];
					strcat(str, "{FFFF00}/inv{FFFFFF} - Открыть инвентарь\n");
					strcat(str, "{FFFF00}/pass (id){FFFFFF} - Показать паспорт\n");
					strcat(str, "{FFFF00}/namestore (id){FFFFFF} - Просмотреть историю ников\n");
					strcat(str, "{FFFF00}/anim{FFFFFF} - Список анимаций\n");
					strcat(str, "{FFFF00}/pay{FFFFFF} - Передать деньги\n");
					strcat(str, "{FFFF00}/gps{FFFFFF} - Включить навигатор\n");
					strcat(str, "{FFFF00}/healme{FFFFFF} - Использовать аптечку\n");
					strcat(str, "{FFFF00}/repair{FFFFFF} - Использовать рем. комплект\n");
					strcat(str, "{FFFF00}/lic{FFFFFF} - Показать лицензии\n");
					strcat(str, "{FFFF00}/time{FFFFFF} - Посмотреть текущее время\n");
					strcat(str, "{FFFF00}/c (/call){FFFFFF} - Позвонить\n");
					strcat(str, "{FFFF00}/sms{FFFFFF} - Написать SMS\n");
					strcat(str, "{FFFF00}/togphone{FFFFFF} - Выключить телефон\n");
					strcat(str, "{FFFF00}/play{FFFFFF} - Слушать онлайн-радио\n");
					strcat(str, "{FFFF00}/stop{FFFFFF} - Выключить онлайн-радио\n");
					strcat(str, "{FFFF00}/radio{FFFFFF} - Включить радио в чате\n");
					strcat(str, "{FFFF00}/ad{FFFFFF} - Подать обьявление\n");
					strcat(str, "{FFFF00}/id{FFFFFF} - Узнать id игрока по нику\n");
					strcat(str, "{FFFF00}/skill (id){FFFFFF} - Показать навыки владения оружием\n");
					strcat(str, "{FFFF00}/warntime{FFFFFF} - Узнать оставшееся время варна\n");
					strcat(str, "{FFFF00}/ptime{FFFFFF} - Узнать оставшееся время заключения\n");
					strcat(str, "{FFFF00}/wedding{FFFFFF} - Жениться\n");
					strcat(str, "{FFFF00}/divorce{FFFFFF} - Развестись\n");
					strcat(str, "{FFFF00}/leaders{FFFFFF} - Список лидеров\n");
					strcat(str, "{FFFF00}/med{FFFFFF} - Показать мед. карту\n");
					strcat(str, "{FFFF00}/flower (id){FFFFFF} - Подарить цветы\n");
					strcat(str, "{FFFF00}/pb (/phonebook){FFFFFF} - Открыть телефонную книгу\n");
					strcat(str, "{FFFF00}/sellsim{FFFFFF} - Продать SIM-карту\n");
					strcat(str, "{FFFF00}/pts (id){FFFFFF} - Показать ПТС\n");
					strcat(str, "{FFFF00}/leave{FFFFFF} - Уволиться из организации");
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				case 1:
				{
	   				new str[290];
					strcat(str, "{FFFF00}/n{FFFFFF} - ООС чат\n");
					strcat(str, "{FFFF00}/me{FFFFFF} - Чат для действия\n");
					strcat(str, "{FFFF00}/do{FFFFFF} - Чат от третьего лица\n");
					strcat(str, "{FFFF00}/todo{FFFFFF} - Обычный чат с действием\n");
					strcat(str, "{FFFF00}/try{FFFFFF} - Попытка действия (удачно/неудачно)\n");
					strcat(str, "{FFFF00}/s{FFFFFF} - Кричать\n");
					strcat(str, "{FFFF00}/w{FFFFFF} - Шепот");
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				case 2:
				{
					new str[500];
					
					if(PI[playerid][pJob] == 1)
					    strcat(str, "{FFFF00}/end{FFFFFF} - Завершить рабочий день");
					    
					else if(PI[playerid][pJob] == 2)
					{
					    strcat(str, "{FFFF00}/taxi{FFFFFF} - Запросить место назначения\n");
					    strcat(str, "{FFFF00}/untaxi{FFFFFF} - Снять метку назначения\n");
					    strcat(str, "{FFFF00}/fare{FFFFFF} - Установить цену за километр\n");
					    strcat(str, "{FFFF00}/end{FFFFFF} - Завершить рабочий день");
					}
					else if(PI[playerid][pJob] == 4)
					{
					    strcat(str, "{FFFF00}/repair{FFFFFF} - Починить машину\n");
					    strcat(str, "{FFFF00}/refill{FFFFFF} - Заправить машину\n");
					    strcat(str, "{FFFF00}/end{FFFFFF} - Завершить работу\n");
					    strcat(str, "{FFFF00}/rc{FFFFFF} - RP чат для механиков\n");
					    strcat(str, "{FFFF00}/rcn{FFFFFF} - нонРП чат для механиков\n");
					    strcat(str, "{FFFF00}/lock 2{FFFFFF} - Открыть/закрыть авто\n");
					}
					else if(PI[playerid][pJob] == 11)
					{
					    strcat(str, "{FFFF00}/truck{FFFFFF} - GPS для дальнобойщиков\n");
					    strcat(str, "{FFFF00}/d{FFFFFF} - RP чат для дальнобойщиков\n");
					    strcat(str, "{FFFF00}/dn{FFFFFF} - RP чат для дальнобойщиков\n");
					    strcat(str, "{FFFF00}/end{FFFFFF} - Завершить работу\n");
					    strcat(str, "{FFFF00}/lock 2{FFFFFF} - Открыть/закрыть грузовик\n");
					}
					
					else
						strcat(str, "Нет доступных команд");

					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				
				case 3:
				{
	   				new str[260];
					strcat(str, "{FFFF00}/home{FFFFFF} - Управление домом\n");
					strcat(str, "{FFFF00}/exit{FFFFFF} - Выйти из дома\n");
					strcat(str, "{FFFF00}/sellhouse (id){FFFFFF} - Продать дом\n");
					strcat(str, "{FFFF00}/safe{FFFFFF} - Управление сейфом\n");
					strcat(str, "{FFFF00}/store{FFFFFF} - Управление шкафом");
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				case 4:
				{
	   				new str[250];
					strcat(str, "{FFFF00}/business{FFFFFF} - Управление бизнесом\n");
					strcat(str, "{FFFF00}/sellbusiness{FFFFFF} - Продажа бизнеса\n");
					strcat(str, "{FFFF00}/filling{FFFFFF} - Управление АЗС\n");
					strcat(str, "{FFFF00}/buyfilling{FFFFFF} - Купить АЗС\n");
					strcat(str, "{FFFF00}/sellfilling{FFFFFF} - Продать АЗС");
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				case 5:
				{
	   				new str[590];
					strcat(str, "{FFFF00}/lock{FFFFFF} - Открыть/Закрыть домашнее авто\n");
					strcat(str, "{FFFF00}/lock 2{FFFFFF} - Открыть/Закрыть рабочее авто\n");
					strcat(str, "{FFFF00}/lock 3{FFFFFF} - Открыть/Закрыть арендованное авто\n");
					strcat(str, "{FFFF00}/fill{FFFFFF} - Заправить авто на АЗС\n");
					strcat(str, "{FFFF00}/fillcar{FFFFFF} - Заправить авто из канистры\n");
					strcat(str, "{FFFF00}/limit{FFFFFF} - Установить лимит скорости\n");
					strcat(str, "{FFFF00}/givevkey{FFFFFF} - Дать ключи от авто\n");
					strcat(str, "{FFFF00}/takevkey{FFFFFF} - Забрать ключи от авто\n");
					strcat(str, "{FFFF00}/dropvkey{FFFFFF} - Выкинуть ключи от авто\n");
					strcat(str, "{FFFF00}/eject{FFFFFF} - Выкинуть из авто\n");
					strcat(str, "{FFFF00}/sellcar{FFFFFF} - Продать авто");
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				case 6:
				{
	   				new str[1230];
					strcat(str, "{FFFF00}/lmenu{FFFFFF} - Меню лидера\n");
					strcat(str, "{FFFF00}/l{FFFFFF} - Рация лидеров\n");
					strcat(str, "{FFFF00}/gnews{FFFFFF} - Гос. Новости\n");
					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять во фракцию\n");
					strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из фракции\n");
					strcat(str, "{FFFF00}/uninviteoff{FFFFFF} - Уволить игрока оффлайн\n");
					strcat(str, "{FFFF00}/rang{FFFFFF} - Повысить/Понизить в должности\n");
					strcat(str, "{FFFF00}/newleader{FFFFFF} - Назначить лидера подфракции\n");
					strcat(str, "{FFFF00}/vacation{FFFFFF} - Выдать отпуск\n");
					strcat(str, "{FFFF00}/unvacation{FFFFFF} - Снять отпуск\n");
					strcat(str, "{FFFF00}/offvacation{FFFFFF} - Выдать отпуск оффлайн\n");
					strcat(str, "{FFFF00}/fwarn{FFFFFF} - Выдать выговор\n");
					strcat(str, "{FFFF00}/fwarnoff{FFFFFF} - Выдать выговор оффлайн\n");
					strcat(str, "{FFFF00}/unfwarn{FFFFFF} - Снять выговор\n");
					strcat(str, "{FFFF00}/unfwarnoff{FFFFFF} - Снять выговор оффлайн");
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				case 7:
				{
					new str[1350];
				    if(PI[playerid][pFraction] == 1)
				    {
				        strcat(str, "{FFFF00}/r{FFFFFF} - Рация подразделения\n");
						strcat(str, "{FFFF00}/f{FFFFFF} - Рация организации\n");
				        strcat(str, "{FFFF00}/rn{FFFFFF} - OOC рация подразделения\n");
						strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация организации\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять во фракцию\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из фракции\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн организации\n");
						strcat(str, "{FFFF00}/heal{FFFFFF} - Вылечить игрока\n");
						strcat(str, "{FFFF00}/vac{FFFFFF} - Провести вакцинацию\n");
						strcat(str, "{FFFF00}/inject{FFFFFF} - Сделать укол\n");
						strcat(str, "{FFFF00}/medcard{FFFFFF} - Выдать медицинскую карту\n");
						strcat(str, "{FFFF00}/setsex{FFFFFF} - Сменить пол\n");
						strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявление");
				    }
					else if(IsAGang(playerid))
					{
				        strcat(str, "{FFFF00}/f{FFFFFF} - Рация\n");
				        strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять в банду\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из банды\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн банды\n");
						strcat(str, "{FFFF00}/makegun{FFFFFF} - Сделать оружие\n");
						strcat(str, "{FFFF00}/givegun{FFFFFF} - Передать оружие\n");
						strcat(str, "{FFFF00}/sellgun{FFFFFF} - Продать оружие\n");
						strcat(str, "{FFFF00}/givekey{FFFFFF} - Передать ключи от дома банды\n");
						strcat(str, "{FFFF00}/selldrugs{FFFFFF} - Продать наркотики\n");
						strcat(str, "{FFFF00}/capture{FFFFFF} - Захватить территорию\n");
						strcat(str, "{FFFF00}/klist{FFFFFF} - Включить отображение убийств на захвате\n");
						strcat(str, "{FFFF00}/steal{FFFFFF} - Ограбить полицейскую машину\n");
						strcat(str, "{FFFF00}/grespawn{FFFFFF} - Респавн авто\n");
						strcat(str, "{FFFF00}/warehouse{FFFFFF} - Открыть/Закрыть общак\n");
						strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявлени\n");
      					strcat(str, "{FFFF00}/giveguns{FFFFFF} - Передать ед. оружия\n");
                        strcat(str, "{FFFF00}/givepatr{FFFFFF} - Передать патроны");

					}
					else if(PI[playerid][pFraction] == 7)
					{
				        strcat(str, "{FFFF00}/r{FFFFFF} - Рация подразделения\n");
						strcat(str, "{FFFF00}/f{FFFFFF} - Рация организации\n");
				        strcat(str, "{FFFF00}/rn{FFFFFF} - OOC рация подразделения\n");
						strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация организации\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять во фракцию\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из фракции\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн организации\n");
						strcat(str, "{FFFF00}/ud{FFFFFF} - Показать удостоверение\n");
                        strcat(str, "{FFFF00}/sload{FFFFFF} - Начать загрузку боеприпасов в вертолет\n");
                        strcat(str, "{FFFF00}/sunload{FFFFFF} - Начать разгрузку боеприпасов с вертолета\n");
                        strcat(str, "{FFFF00}/load{FFFFFF} - Начать загрузку боеприпасов в машину\n");
                        strcat(str, "{FFFF00}/unload{FFFFFF} - Начать разгрузку боеприпасов с машины\n");
                        strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявление");
					}
					else if(PI[playerid][pFraction] == 8)
					{
				        strcat(str, "{FFFF00}/r{FFFFFF} - Рация подразделения\n");
						strcat(str, "{FFFF00}/f{FFFFFF} - Рация организации\n");
				        strcat(str, "{FFFF00}/rn{FFFFFF} - OOC рация подразделения\n");
						strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация организации\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять во фракцию\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из фракции\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн организации\n");
						strcat(str, "{FFFF00}/ud{FFFFFF} - Показать удостоверение\n");
						strcat(str, "{FFFF00}/su{FFFFFF} - Объявить в розыск\n");
						strcat(str, "{FFFF00}/cuff{FFFFFF} - Надеть наручники\n");
						strcat(str, "{FFFF00}/uncuff{FFFFFF} - Снять наручники\n");
						strcat(str, "{FFFF00}/arrest{FFFFFF} - Посадить в тюрьму\n");
						strcat(str, "{FFFF00}/push{FFFFFF} - Затолкать в авто\n");
						strcat(str, "{FFFF00}/m{FFFFFF} - Мегафон\n");
						strcat(str, "{FFFF00}/takelic{FFFFFF} - Забрать лицензию на авто\n");
						//strcat(str, "{FFFF00}/skip{FFFFFF} - Выдать пропуск\n");
						strcat(str, "{FFFF00}/frisk{FFFFFF} - Обыскать игрока\n");
						strcat(str, "{FFFF00}/take{FFFFFF} - Изьять вещи игрока\n");
						strcat(str, "{FFFF00}/untie{FFFFFF} - Развязать игрока\n");
						strcat(str, "{FFFF00}/ticket{FFFFFF} - Выписать игроку штраф\n");
						strcat(str, "{FFFF00}/pt{FFFFFF} - Погоня за преступником\n");
						strcat(str, "{FFFF00}/unpt{FFFFFF} - Отменить погоню\n");
						strcat(str, "{FFFF00}/unmask{FFFFFF} - Снять маску с игрока\n");
						strcat(str, "{FFFF00}/hold{FFFFFF} - Вести преступника за собой\n");
						strcat(str, "{FFFF00}/division{FFFFFF} - Установить сотруднику подразделение\n");
						strcat(str, "{FFFF00}/setmark{FFFFFF} - Поиск преступников на карте\n");
						strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявление\n");
						strcat(str, "{FFFF00}/break{FFFFFF} - Управление объектами");

					}
					else if(PI[playerid][pFraction] == 9)
					{
				        strcat(str, "{FFFF00}/r{FFFFFF} - Рация подразделения\n");
						strcat(str, "{FFFF00}/f{FFFFFF} - Рация организации\n");
				        strcat(str, "{FFFF00}/rn{FFFFFF} - OOC рация подразделения\n");
						strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация организации\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять во фракцию\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из фракции\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн организации\n");
						strcat(str, "{FFFF00}/edit{FFFFFF} - Редактировать объявления\n");
						strcat(str, "{FFFF00}/ether{FFFFFF} - Начать/Завершить эфир\n");
						strcat(str, "{FFFF00}/et{FFFFFF} - Написать в эфир\n");
						strcat(str, "{FFFF00}/dial{FFFFFF} - Начать принимать звонки\n");
						strcat(str, "{FFFF00}/takecall{FFFFFF} - Список звонков\n");
						strcat(str, "{FFFF00}/takeoff{FFFFFF} - Завершить звонок\n");
						strcat(str, "{FFFF00}/stopdial{FFFFFF} - Завершить прием звонков\n");
						strcat(str, "{FFFF00}/makeflyer{FFFFFF} - Сделать рекламный флаер\n");
						strcat(str, "{FFFF00}/flyerinfo{FFFFFF} - Список листовок на одобрении\n");
						strcat(str, "{FFFF00}/giveflyer{FFFFFF} - Выдать листовку\n");
						strcat(str, "{FFFF00}/dropflyers{FFFFFF} - Выбросить листовки\n");
						strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявление");
					}
					else if(PI[playerid][pFraction] == 10)
					{
				        strcat(str, "{FFFF00}/r{FFFFFF} - Рация подразделения\n");
						strcat(str, "{FFFF00}/f{FFFFFF} - Рация организации\n");
				        strcat(str, "{FFFF00}/rn{FFFFFF} - OOC рация подразделения\n");
						strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация организации\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять во фракцию\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из фракции\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн организации\n");
						strcat(str, "{FFFF00}/out{FFFFFF} - Вести нарушителя за собой\n");
                        strcat(str, "{FFFF00}/unout{FFFFFF} - Перестать вести нарушителя\n");
                        strcat(str, "{FFFF00}/selllic{FFFFFF} - Продать лицензию на оружие\n");
                        strcat(str, "{FFFF00}/free{FFFFFF} - Освободить заключенного\n");
                        strcat(str, "{FFFF00}/sellcard{FFFFFF} - Продать билет рекордсмена\n");
                        strcat(str, "{FFFF00}/charity{FFFFFF} - Получить пожертвование от игрока\n");
                        strcat(str, "{FFFF00}/reply{FFFFFF} - Ответить на вопрос\n");
                        strcat(str, "{FFFF00}/rfo{FFFFFF} - Включить/Отключить подслушку рации подфракции\n");
                        strcat(str, "{FFFF00}/rf{FFFFFF} - Рация прослушиваемой подфракции\n");
                        strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявление");
					}
					else if(PI[playerid][pFraction] == 11)
					{
						strcat(str, "{FFFF00}/f{FFFFFF} - Рация организации\n");
						strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация организации\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять во фракцию\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из фракции\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн организации\n");
						strcat(str, "{FFFF00}/ud{FFFFFF} - Показать удостоверение\n");
						strcat(str, "{FFFF00}/su{FFFFFF} - Объявить в розыск\n");
						strcat(str, "{FFFF00}/cuff{FFFFFF} - Надеть наручники\n");
						strcat(str, "{FFFF00}/uncuff{FFFFFF} - Снять наручники\n");
						strcat(str, "{FFFF00}/arrest{FFFFFF} - Посадить в тюрьму\n");
						strcat(str, "{FFFF00}/push{FFFFFF} - Затолкать в авто\n");
						strcat(str, "{FFFF00}/m{FFFFFF} - Мегафон\n");
						strcat(str, "{FFFF00}/frisk{FFFFFF} - Обыскать игрока\n");
						strcat(str, "{FFFF00}/take{FFFFFF} - Изьять вещи игрока\n");
						strcat(str, "{FFFF00}/untie{FFFFFF} - Развязать игрока\n");
						strcat(str, "{FFFF00}/ticket{FFFFFF} - Выписать игроку штраф\n");
						strcat(str, "{FFFF00}/pt{FFFFFF} - Погоня за преступником\n");
						strcat(str, "{FFFF00}/unpt{FFFFFF} - Отменить погоню\n");
						strcat(str, "{FFFF00}/unmask{FFFFFF} - Снять маску с игрока\n");
						strcat(str, "{FFFF00}/hold{FFFFFF} - Вести преступника за собой\n");
						strcat(str, "{FFFF00}/settag{FFFFFF} - Установить сотруднику подразделение\n");
						strcat(str, "{FFFF00}/setmark{FFFFFF} - Поиск преступников на карте\n");
                        strcat(str, "{FFFF00}/disguse{FFFFFF} - Маскировка\n");
                        strcat(str, "{FFFF00}/ff{FFFFFF} - Подслушка рации\n");
						strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявление");
					}
					else if(IsAMafia(playerid))
					{
				        strcat(str, "{FFFF00}/f{FFFFFF} - Рация организации\n");
				        strcat(str, "{FFFF00}/fn{FFFFFF} - OOC рация организации\n");
	 					strcat(str, "{FFFF00}/invite{FFFFFF} - Принять в организацию\n");
						strcat(str, "{FFFF00}/uninvite{FFFFFF} - Уволить из организации\n");
						strcat(str, "{FFFF00}/find{FFFFFF} - Посмотреть онлайн организации\n");
                        strcat(str, "{FFFF00}/bizlist{FFFFFF} - Список подконтрольных бизнесов\n");
                        strcat(str, "{FFFF00}/rob{FFFFFF} - Ограбить военную фуру\n");
                        strcat(str, "{FFFF00}/mload{FFFFFF} - Начать загрузку боеприпасов\n");
                        strcat(str, "{FFFF00}/munload{FFFFFF} - Начать разгрузку боеприпасов\n");
                        strcat(str, "{FFFF00}/tie{FFFFFF} - Связать заложника\n");
                        strcat(str, "{FFFF00}/untie{FFFFFF} - Развязать заложника\n");
                        strcat(str, "{FFFF00}/hold{FFFFFF} - Вести заложника за собой\n");
                        strcat(str, "{FFFF00}/unhold{FFFFFF} - Отпустить заложника\n");
                        strcat(str, "{FFFF00}/push{FFFFFF} - Затолкнуть заложника в т/с\n");
                        strcat(str, "{FFFF00}/bizwar{FFFFFF} - Начать войну за бизнес\n");
                        strcat(str, "{FFFF00}/sellmbiz{FFFFFF} - Продать контроль над бизнесом\n");
                        strcat(str, "{FFFF00}/warehouse{FFFFFF} - Открыть/Закрыть общак\n");
                        strcat(str, "{FFFF00}/advert{FFFFFF} - Посмотреть объявление\n");
                        strcat(str, "{FFFF00}/selldrugs{FFFFFF} - Продать наркотики\n");
                        strcat(str, "{FFFF00}/usedrugs{FFFFFF} - Использовать наркотики\n");
                        strcat(str, "{FFFF00}/mrespawn{FFFFFF} - Заспавнить транспорт мафии\n");
                        strcat(str, "{FFFF00}/giveguns{FFFFFF} - Передать ед. оружия\n");
                        strcat(str, "{FFFF00}/givepatr{FFFFFF} - Передать патроны\n");
                        strcat(str, "{FFFF00}/object{FFFFFF} - Управление объектами");
					}

					else
					    strcat(str, "Нет доступных команд");
					    
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
				case 8:
				{
	   				new str[380];
					strcat(str, "{FFFF00}/family{FFFFFF} - Меню семьи\n");
					strcat(str, "{FFFF00}/k{FFFFFF} - Рация семьи\n");
					strcat(str, "{FFFF00}/finvite{FFFFFF} - Принять в семью\n");
					strcat(str, "{FFFF00}/funinvite (Ник){FFFFFF} - Исключить из семьи\n");
					strcat(str, "{FFFF00}/selectzam{FFFFFF} - Назначить заместителя\n");
					strcat(str, "{FFFF00}/delzam{FFFFFF} - Убрать заместителя\n");
					strcat(str, "{FFFF00}/givefamily{FFFFFF} - Передать права основателя заместителю\n");
					strcat(str, "{FFFF00}/fobject{FFFFFF} - Управление объектами");
					ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, !"Команды", str, !"ОК", !"");
				}
			}
		    
		}
		case 67:
		{
            ShowHelpDialog(playerid);
		}
		case 65:
		{
		    if(response && IsPlayerLogged[playerid]) ShowUpdateSettings(playerid);
			return true;
		}
		case 111:
		{
			if(response)
			{
				if(pTemp[playerid][SPECTPLAYER]==true) TogglePlayerSpectating(playerid,false);
			}
		}


	case 738:
	{
	    if(!response)
			return 1;
			
		if(!ChangingSkin[playerid])
		    return 1;

		new
			houseid = PI[playerid][pHouseKey]-1;

		if(!PI[playerid][pHouseKey])
			ShowPlayerDialogEx(playerid, 739, DIALOG_STYLE_MSGBOX, !"Покупка одежды", !"{FF0000}Внимание! {FFFFFF}У Вас нет шкафа для одежды.\nЕсли Вы купите эту одежду, то она заменит вашу текущую\nВы все равно хотите купить Выбранную одежду?", !"Да", !"Нет");

		if(!HouseInfo[houseid][hImprove][2])
			ShowPlayerDialogEx(playerid, 739, DIALOG_STYLE_MSGBOX, !"Покупка одежды", !"{FF0000}Внимание! {FFFFFF}У Вас нет шкафа для одежды.\nЕсли Вы купите эту одежду, то она заменит вашу текущую\nВы все равно хотите купить Выбранную одежду?", !"Да", !"Нет");

		else if(PI[playerid][pHouseKey] && HouseInfo[houseid][hImprove][2]){
			new
				skinid = GetPVarInt(playerid,"clothes_select"),
				skin = Skins[skinid][skinID],
				price = GetSkinPrice(skinid),
				id = BizEntered[playerid]-1,
				slot = -1;

			for(new i;i<4;i++)
			{
				if(skin == HouseInfo[houseid][hSkin][i])
					return SendClientMessage(playerid, COLOR_GREY, !"У Вас уже есть эта одежда в шкафу");

				if(!HouseInfo[houseid][hSkin][i])
				{
					slot = i;
					break;
				}
			}
			if(slot == -1)
				return ShowPlayerDialogEx(playerid, 739, DIALOG_STYLE_MSGBOX, !"Покупка одежды", "{FF0000}Внимание! {FFFFFF}У Вас недостаточно места в шкафу.\nЕсли Вы купите эту одежду, то она заменит вашу текущую\nВы все равно хотите купить Выбранную одежду?", !"Да", !"Нет");

			if(PI[playerid][pMoney] < price)
				return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно денег");

			if(BizInfo[id][bProducts] - floatround((price / 150) * 5) / 10 > 0)
			{
				BizInfo[id][bProducts] -= floatround((price / 150) * 5) / 10;
				GiveBusinessMoney(id, (price / 150) * 12);
				if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
			}

			UpdateBiz(id,1);
			HouseInfo[houseid][hSkin][slot] = skin;
			UpdateHouseDress(houseid);


			GiveMoney(playerid, -price, "покупка скина");

			SendClientMessage(playerid, COLOR_GREEN, !"Одежда была доставлена в ваш шкаф");
			ChangingSkin[playerid] = false;
			if(PI[playerid][pQuest] == 6 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Саймону");
			}
			
			if(GetPVarInt(playerid, "curskin") == PI[playerid][pFractionSkin] && PI[playerid][pFraction])
			{
			    if(PI[playerid][pSex] == 1)
					SetPlayerSkinEx(playerid, OrgInfo[PI[playerid][pFraction]-1][oMSkins][PI[playerid][pRank]-1]);
			    else if(PI[playerid][pSex] == 2)
					SetPlayerSkinEx(playerid, OrgInfo[PI[playerid][pFraction]-1][oWSkins][PI[playerid][pRank]-1]);
					
                PI[playerid][pSkin] = skin, UpdatePlayerData(playerid, "Skin", PI[playerid][pSkin]);
			}
			else
				PI[playerid][pSkin] = skin, UpdatePlayerData(playerid, "Skin", PI[playerid][pSkin]), SetPlayerSkinEx(playerid,skin);

			HidePlayerClothesTD(playerid);
			justtp_exit[playerid] = true;
			SetPlayerPos(playerid, GetPVarFloat(playerid, "posx"), GetPVarFloat(playerid, "posy"), GetPVarFloat(playerid, "posz"));
			SetPlayerInterior(playerid, GetPVarInt(playerid, "interior"));
			SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "vw"));
			SetPlayerFacingAngle(playerid, GetPVarInt(playerid, "posa"));
			f_TogglePlayerControllable(playerid, true);
			SetCameraBehindPlayer(playerid);
			DeletePVar(playerid, "posx");
			DeletePVar(playerid, "posy");
			DeletePVar(playerid, "posz");
			DeletePVar(playerid, "posa");
			DeletePVar(playerid, "interior");
			DeletePVar(playerid, "vw");
			DeletePVar(playerid, "clothes_sel");
			DeletePVar(playerid, "clothes_class");
			ChangingSkin[playerid] = false;
		}
	}
	case 739:
	{
		if(!response)
			return 1;
			
		if(!ChangingSkin[playerid])
		    return 1;
			
		new
			skin,
			skinid = GetPVarInt(playerid,"clothes_select"),
			houseid = PI[playerid][pHouseKey]-1,
			price = GetSkinPrice(skinid),
			id = BizEntered[playerid]-1;
			
        skin = Skins[skinid][skinID];
		if(PI[playerid][pMoney] < price)
			return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно денег");

		if(BizInfo[id][bProducts] - floatround((price / 150) * 5) / 10 > 0)
		{
			BizInfo[id][bProducts] -= floatround((price / 150) * 5) / 10;
			GiveBusinessMoney(id, (price / 150) * 12);
			if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
		}

		UpdateBiz(id,1);

		if((houseid+1))
		{
			new slot=-1, cnt;
			for(new i;i<4;i++)
			{
				if(HouseInfo[houseid][hSkin][i]) cnt++;
				if(HouseInfo[houseid][hSkin][i] == PI[playerid][pSkin]) slot = i;
			}
			if(cnt >= 4)
			{
				if(slot == -1) return SendClientMessage(playerid,COLOR_RED,"Ошибка при нахождении заменямого скина в шкафу");
				HouseInfo[houseid][hSkin][slot] = skin;
				UpdateHouseDress(houseid);
			}
		}
		
		GiveMoney(playerid, -price, "покупка скина");
		PI[playerid][pSkin] = skin;
		if(PI[playerid][pQuest] == 6 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
		{
	        PI[playerid][pQuestProcess] = 1;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        PI[playerid][pQuestStatus] = 0;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Саймону");
		}
			
		if(GetPVarInt(playerid, "curskin") == PI[playerid][pFractionSkin] && PI[playerid][pFraction])
		{
		    if(PI[playerid][pSex] == 1)
				SetPlayerSkinEx(playerid, OrgInfo[PI[playerid][pFraction]-1][oMSkins][PI[playerid][pRank]-1]);
		    else if(PI[playerid][pSex] == 2)
				SetPlayerSkinEx(playerid, OrgInfo[PI[playerid][pFraction]-1][oWSkins][PI[playerid][pRank]-1]);
				
            PI[playerid][pSkin] = skin, UpdatePlayerData(playerid, "Skin", PI[playerid][pSkin]);
		}
		else
			PI[playerid][pSkin] = skin, UpdatePlayerData(playerid, "Skin", PI[playerid][pSkin]), SetPlayerSkinEx(playerid,skin);
			
		HidePlayerClothesTD(playerid);
		justtp_exit[playerid] = true;
		SetPlayerPos(playerid, GetPVarFloat(playerid, "posx"), GetPVarFloat(playerid, "posy"), GetPVarFloat(playerid, "posz"));
		SetPlayerInterior(playerid, GetPVarInt(playerid, "interior"));
		SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "vw"));
		SetPlayerFacingAngle(playerid, GetPVarInt(playerid, "posa"));
		f_TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
		DeletePVar(playerid, "posx");
		DeletePVar(playerid, "posy");
		DeletePVar(playerid, "posz");
		DeletePVar(playerid, "posa");
		DeletePVar(playerid, "interior");
		DeletePVar(playerid, "vw");
		DeletePVar(playerid, "clothes_sel");
		DeletePVar(playerid, "clothes_class");
		ChangingSkin[playerid] = false;
	}
	case 740:
	{
	    if(!response)
	        return 1;
	        
	    BuyCar_Class[playerid] = 0;
		StartChosingVehicle(playerid);
	}
	case 741:
	{
	    if(!response)
	        return 1;

	    BuyCar_Class[playerid] = 1;
		StartChosingVehicle(playerid);
	}
	case 742:
	{
	    if(!response)
	        return 1;

	    BuyCar_Class[playerid] = 2;
		StartChosingVehicle(playerid);
	}
	case 743:
	{
	    if(!response)
	        return 1;

	    BuyCar_Class[playerid] = 3;
		StartChosingVehicle(playerid);
	}
	case 622:
	{
	    if(!response)
	        return 1;

		if(!accs_change[playerid])
		    return 1;
		    
	    new
	        b_type;

	    switch(accs_class[playerid])
	    {
	        case 0:
	            b_type = 0;
	            
  			case 1:
			    b_type = 4;
			    
			case 2..3:
			    b_type = 0;

			case 4:
			    b_type = 1;

			case 5:
			    b_type = 3;
			    
			case 6:
				b_type = 0;
				
			case 7:
			    b_type = 2;

	    }

	    new
	        b_item = acc_select[playerid],
			b_price = gAccessories[b_item][1],
			id = BizEntered[playerid]-1;
	   		

        if(PI[playerid][pMoney] < b_price)
			return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточно денег на покупку этого аксессуара!");


		if(b_type == 0)
		{
		    new
		        total;
		        
	    	for(new i; i < 5; i++)
				if(inventory_head[playerid][i] != 0)
    				total++;

			if(total == 5)
			    return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно места в инвентаре");
			    
	    	for(new i; i < 5; i++)
	    	{

				if(inventory_head[playerid][i] != 0)
    				continue;
					
        		inventory_head[playerid][i] = gAccessories[b_item][0];

				break;
			}

		}

		else if(b_type == 1)
		{
		    new
		        total;

	    	for(new i; i < 5; i++)
				if(inventory_glass[playerid][i] != 0)
    				total++;

			if(total == 5)
			    return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно места в инвентаре");

		
	    	for(new i; i < 5; i++)
	    	{
				if(inventory_glass[playerid][i] != 0)
					continue;
					
        		inventory_glass[playerid][i] = gAccessories[b_item][0];

        		break;
			}
		}
		else if(b_type == 2)
		{
		    new
		        total;

	    	for(new i; i < 5; i++)
				if(inventory_watch[playerid][i] != 0)
    				total++;

			if(total == 5)
			    return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно места в инвентаре");
		
	    	for(new i; i < 5; i++)
	    	{
				if(inventory_watch[playerid][i] != 0)
	                continue;
	                
        		inventory_watch[playerid][i] = gAccessories[b_item][0];

        		break;
			}

		}
		else if(b_type == 3)
		{
		    new
		        total;

	    	for(new i; i < 5; i++)
				if(inventory_mask[playerid][i] != 0)
    				total++;

			if(total == 5)
			    return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно места в инвентаре");
			    
	    	for(new i; i < 5; i++)
			{
				if(inventory_mask[playerid][i] != 0)
					continue;
				
        		inventory_mask[playerid][i] = gAccessories[b_item][0];

        		break;
			}

		}
		else if(b_type == 4)
		{
		    new
		        total;

	    	for(new i; i < 5; i++)
				if(inventory_hp[playerid][i] != 0)
    				total++;

			if(total == 5)
			    return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно места в инвентаре");
			    
	    	for(new i; i < 5; i++)
	    	{
    			if(inventory_hp[playerid][i] != 0)
					continue;

        		inventory_hp[playerid][i] = gAccessories[b_item][0];

        		break;
			}

		}
		else if(b_type == 5)
		{
		    new
		        total;

	    	for(new i; i < 5; i++)
				if(inventory_bag[playerid][i] != 0)
    				total++;

			if(total == 5)
			    return SendClientMessage(playerid, COLOR_GREY, !"Недостаточно места в инвентаре");
			    
	    	for(new i; i < 5; i++)
	    	{
				if(inventory_bag[playerid][i] != 0)
					continue;

        		inventory_bag[playerid][i] = gAccessories[b_item][0];

        		break;
			}

		}
	    GiveItem(playerid, gAccessories[b_item][0]);

		GiveMoney(playerid, -b_price, "покупка акса");

		if(BizInfo[id][bProducts] - floatround((b_price / 150) * 3) > 0)
		{
			BizInfo[id][bProducts] -= floatround((b_price / 150) * 3);
            GiveBusinessMoney(id, b_price);
            if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],b_price);
		}
		PI[playerid][pSlotItem][b_type] = gAccessories[b_item][0];

		SaveAccessories(playerid);

		HidePlayerAccessoriesTD(playerid);

		SetPlayerPos(playerid, GetPVarFloat(playerid, "pos_x"), GetPVarFloat(playerid, "pos_y"), GetPVarFloat(playerid, "pos_z"));
		SetPlayerInterior(playerid, GetPVarInt(playerid, "interior"));
		SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "vw"));
		SetPlayerFacingAngle(playerid, GetPVarInt(playerid, "pos_a"));
		f_TogglePlayerControllable(playerid, true);

	    if(IsValidPlayerObject(playerid, acc_object[playerid]))
			DestroyPlayerObject(playerid, acc_object[playerid]);

		SetCameraBehindPlayer(playerid);
		DeletePVar(playerid, "pos_x");
		DeletePVar(playerid, "pos_y");
		DeletePVar(playerid, "pos_z");
		DeletePVar(playerid, "pos_a");
		DeletePVar(playerid, "interior");
		DeletePVar(playerid, "vw");
		accs_sel[playerid] = 0;
		accs_class[playerid] = 0;
		accs_change[playerid] = false;
		accs_last[playerid] = 0;
		ShowPlayerDialogEx(playerid, 293, DIALOG_STYLE_LIST, !"Магазин аксессуаров", !"1. Шапки\n2. Наушники\n3. Панамы\n4. Кепки\n5. Очки\n6. Банданы\n7. Шляпы\n8. Часы", !"Выбрать", !"Отмена");


		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {ffffff}Поздравляем с покупкой нового аксессуара. Чтобы одеть аксессуар - {FFC800}/inv");
		if(PI[playerid][pQuest] == 7 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
		{
	        PI[playerid][pQuestProcess] = 1;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        PI[playerid][pQuestStatus] = 0;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Саймону");
		}
	}
	case 893:
	{
		if(!response)
			return 1;
			
		switch(listitem)
		{
			case 0:
			{
			    new
			        frmt_atm_balance[30 + 9];

				format(frmt_atm_balance, sizeof frmt_atm_balance, "{FFFFFF}На счету: {4682B4}%d$", PI[playerid][pBank]);
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Информация о счёте", frmt_atm_balance, !"OK", !"");
			}
			
			case 1:
			    ShowPlayerDialogEx(playerid, 894, DIALOG_STYLE_INPUT, !"Снять деньги", !"{FFFFFF}Укажите сумму, которую хотите снять", !"Снять", !"Выход");

			case 2:
			    ShowPlayerDialogEx(playerid, 895, DIALOG_STYLE_INPUT, !"Положить деньги", !"{FFFFFF}Укажите сумму, которую хотите положить на счет", !"Положить", !"Выход");

			case 3:
			{
				if(!PI[playerid][pPhone])
					return SendClientMessage(playerid, COLOR_GREY, !"У Вас нет телефона. Вы можете купить его в 24/7");
					
			    ShowPlayerDialogEx(playerid, 896, DIALOG_STYLE_INPUT, !"Баланс мобильного", !"{FFFFFF}Укажите сумму, которую хотите положить на счет мобильного", !"Положить", !"Выход");
			}
			case 4:
			{
			    if(!PI[playerid][pBizKey])
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет бизнеса");

				new
				    frmt_business_money[140];
					    
				if(PI[playerid][pBizKey] < 1000)
				{
					new
						bid = PI[playerid][pBizKey]-1;

					format(frmt_business_money, sizeof frmt_business_money, "{FFFFFF}Укажите сумму, которую хотите снять\nВ кассе бизнеса: {4682B4}%d$", BizInfo[bid][bMoney]);
				}
				else
				{
					new
						fillingid = PI[playerid][pBizKey]-1001;

                    format(frmt_business_money, sizeof frmt_business_money, "{FFFFFF}Укажите сумму, которую хотите снять\nВ кассе бизнеса: {4682B4}%d$", gFillings[fillingid][fillingBank]);
				}
                ShowPlayerDialogEx(playerid, 899, DIALOG_STYLE_INPUT, !"Снять деньги с кассы бизнеса", frmt_business_money, !"Снять", !"Выход");
			}
		}
	}
	case 899:
	{
		if(!response)
			return 1;

	    if(!PI[playerid][pBizKey])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет бизнеса");


		if(PI[playerid][pBizKey] < 1000)
		{
			new
				bid = PI[playerid][pBizKey]-1,
				amount = strval(inputtext);
				
			if(!isNumeric(inputtext) || !strlen(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверную сумму");

			if(amount < 1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверную сумму");

			if(BizInfo[bid][bMoney] < amount)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Недостаточно денег в кассе бизнеса");

			BizInfo[bid][bMoney] -= amount;
			UpdateBiz(bid,1);
			GiveMoney(playerid, amount, "касса бизнес");
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сняли деньги с кассы бизнеса");
		}
		else
		{
			new
				fillingid = PI[playerid][pBizKey]-1001,
				amount = strval(inputtext);
				
			if(!isNumeric(inputtext) || !strlen(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверную сумму");

			if(amount < 1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверную сумму");

			if(gFillings[fillingid][fillingBank] < amount)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Недостаточно денег в кассе бизнеса");

            gFillings[fillingid][fillingBank] -= amount;
            SaveFilling(fillingid);
            GiveMoney(playerid, amount, "касса АЗС");
            SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сняли деньги с кассы бизнеса");
		}
	}
	case 894:
	{
		if(!response)
			return 1;
			
		new
			amount = strval(inputtext);
			
		if(amount < 1 || amount > 100000)
			return SendClientMessage(playerid, COLOR_GREY, !"Можно снимать от $1 до $100000");
			
		if(PI[playerid][pBank] < amount)
			return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточно денег на счету");
			
		PI[playerid][pBank] -= amount;
		UpdatePlayerData(playerid, "Bank", PI[playerid][pBank]);
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы сняли деньги со счета");
		GiveMoney(playerid, amount, "снял деньги со счета");
	}
	case 895:
	{
		if(!response)
			return 1;
			
		new
			amount = strval(inputtext);
		
		if(amount < 1 || amount > 100000)
			return SendClientMessage(playerid, COLOR_GREY, !"Можно класть от $1 до $100000");
			
		if(PI[playerid][pMoney] < amount)
			return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточено денег на руках");

		PI[playerid][pBank] += amount;
        UpdatePlayerData(playerid, "Bank", PI[playerid][pBank]);
        
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы положили деньги на счет в банке");
		GiveMoney(playerid, -amount, "положил деньги на счет в банке");
	}
	case 896:
	{
		if(!response)
			return 1;
			
		new
			amount = strval(inputtext);
			
		if(amount < 5 || amount > 10000)
			return SendClientMessage(playerid, COLOR_GREY, !"Можно класть от $5 до $10000");
			
		if(PI[playerid][pMoney] < amount)
			return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточено денег на руках");
			
		PI[playerid][pIn_Skill] += amount;
		UpdatePlayerData(playerid, "In_Skill", amount);

	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы успешно пополнили баланс мобильного телефона");
	    GiveMoney(playerid, -amount, "пополнил баланс телефона");
	}
    case 722:
    {
		if(!response)
			return 1;

		switch(listitem)
		{
			case 0: ShowStats(playerid,playerid);
			case 1: ShowUpdateSettings(playerid);
			case 2: ShowSafety(playerid);
			case 3:
			{
				if(!response) return 1;
   				new status[50], count[40], target;
				if(PI[playerid][pTruckSkill] >= TRUCK_LEVEL_3) { status = "{FF9900}Опытный работник"; target = 0; }
				if(PI[playerid][pTruckSkill] >= TRUCK_LEVEL_2) { status = "{FFFF00}Стабильный работник"; target = TRUCK_LEVEL_3; }
				else { status = "{63BD4E}Начинающий работник"; target = TRUCK_LEVEL_2; }
				if(!target) format(count, sizeof(count), "%d", PI[playerid][pTruckSkill]);
				else format(count, sizeof(count), "%d/%d", PI[playerid][pTruckSkill], target);
				
				totalstring[0] = 0;
				format(totalstring,90,"{FFFFFF}Дальнобойщик:\n{FFFFFF}%s поездок | %s",count, status);
				ShowPlayerDialogEx(playerid, 0000, DIALOG_STYLE_MSGBOX, !"Навыки персонажа", totalstring, !"ОК", !"Отмена");
				totalstring[0] = 0;
				return 1;
			}
			case 4: ShowHelpDialog(playerid);
			case 5: callcmd::report(playerid,"");
			case 6: ShowPlayerDialogEx(playerid, 313, DIALOG_STYLE_INPUT, !"Смена ника", !"\n\n\n{FFFFFF}Если у Вас нонРП ник и вы решили его изменить, подайте заявку для смены ника.\nВведите желаемый ник в окошко:\n\n\n", !"ОК", !"Отмена");
			case 7: ShowDonate(playerid);
			case 8: ShowPlayerDialogEx(playerid, 872, DIALOG_STYLE_LIST, !"Улучшения", !"{FF7319}1.{FFFFFF} Решительность\n{FF7319}2.{FFFFFF} Рюкзак", !"Выбор", !"Назад");
			case 9:
			{
				if(PI[playerid][pQuest] == 1 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 20)
				{
				    new
						frmt_quest_info[170];

					format(frmt_quest_info, sizeof frmt_quest_info, "{FFFFFF}Задача: Перенести 20 тележек со щебнем\nНаграда: 3750$ и 1 ехр\nВыполнено: %d/20", PI[playerid][pQuestProcess]);
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", frmt_quest_info, !"Закрыть", !"");
				}
				
				else if(PI[playerid][pQuest] == 2 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Получить водительское удостоверение\nНаграда: 3500$", !"Закрыть", !"");
					
				else if(PI[playerid][pQuest] == 3 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 20)
				{
				    new
						frmt_quest_info[170];

					format(frmt_quest_info, sizeof frmt_quest_info, "{FFFFFF}Задача: Перенести 20 ящиков груза\nНаграда: 4200$ и 1 ехр\nВыполнено: %d/20", PI[playerid][pQuestProcess]);
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", frmt_quest_info, !"Закрыть", !"");
				}
				
				else if(PI[playerid][pQuest] == 4 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				    ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Купить телефон в 24/7\nНаграда: 3500$", !"Закрыть", !"");

				else if(PI[playerid][pQuest] == 5 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 20)
				{
				    new
						frmt_quest_info[170];

					format(frmt_quest_info, sizeof frmt_quest_info, "{FFFFFF}Задача: Собрать 20 автозапчастей\nНаграда: 5200$ и 1 ехр\nВыполнено: %d/20", PI[playerid][pQuestProcess]);
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", frmt_quest_info, !"Закрыть", !"");
				}

				else if(PI[playerid][pQuest] == 6 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				    ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Купить новый скин в магазине одежды\nНаграда: 5000$", !"Закрыть", !"");

				else if(PI[playerid][pQuest] == 7 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				    ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Приобрести аксессуар в магазине аксессуаров\nНаграда: 4700$", !"Закрыть", !"");

		    	else if(PI[playerid][pQuest] == 8 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] == 0)
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Поговорить с Линкольном\nНаграда: 8000$ и 2 ехр", !"Закрыть", !"");

		    	else if(PI[playerid][pQuest] == 9 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 250)
				{
				    new
						frmt_quest_info[170];

					format(frmt_quest_info, sizeof frmt_quest_info, "{FFFFFF}Задача: Проехать 250 чекпоинтов\nНаграда: 7800$ и 2 ехр\nВыполнено: %d/250", PI[playerid][pQuestProcess]);
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", frmt_quest_info, !"Закрыть", !"");
				}
				
		    	else if(PI[playerid][pQuest] == 10 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Получить мед. карту в больнице\nНаграда: 6200$", !"Закрыть", !"");

				else if(PI[playerid][pQuest] == 11 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Получить лицензию на оружие в мэрии\nНаграда: 6600$", !"Закрыть", !"");

				else if(PI[playerid][pQuest] == 12 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 200)
				{
				    new
						frmt_quest_info[170];

					format(frmt_quest_info, sizeof frmt_quest_info, "{FFFFFF}Задача: Выстрелить 200 патрон из \"Пустынного орла\" на территории тира\nНаграда: 7000$ и 15 патронов \"Пустынного орла\"\nВыполнено: %d/200", PI[playerid][pQuestProcess]);
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", frmt_quest_info, !"Закрыть", !"");
				}

				else if(PI[playerid][pQuest] == 13 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Поучаствовать в турнире по пейнтболу\nНаграда: 7500$", !"Закрыть", !"");

				else if(PI[playerid][pQuest] == 14 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 15)
				{
				    new
						frmt_quest_info[170];

					format(frmt_quest_info, sizeof frmt_quest_info, "{FFFFFF}Задача: Перевезти 15 грузов\nНаграда: 10000$ и 2 exp\nВыполнено: %d/15", PI[playerid][pQuestProcess]);
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", frmt_quest_info, !"Закрыть", !"");
				}

				else if(PI[playerid][pQuest] == 15 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Приобрести любое блюдо в любой закусочной\nНаграда: 7000$", !"Закрыть", !"");

				else if(PI[playerid][pQuest] == 16 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
					ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Задание", !"{FFFFFF}Задача: Устроиться в организацию\nНаграда: 25000$", !"Закрыть", !"");

				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет активных заданий");
			}
			case 10:
			{
			    if(PI[playerid][pPromo])
			    {
					new
					    frmt_promo_info[290];
					    
					format(frmt_promo_info, sizeof frmt_promo_info, "{FFFFFF}\n\nПромокод: %s\n\nУдвоенный опыт: %d/3 дней\nУдвоенная зарплата: %d/3 дней\nУровень для получения бонуса: %d\nСумма бонуса: %d$", gPromo[PI[playerid][pPromo]-1][pcName], PI[playerid][pDaysExp], PI[playerid][pDaysSalary], PI[playerid][pPromoLvl], PI[playerid][pPromoBonus]);
					
                    ShowPlayerDialogEx(playerid, 310, DIALOG_STYLE_MSGBOX, !"Промокод", frmt_promo_info, !"Закрыть", !"");
				}
				
				else
					ShowPlayerDialogEx(playerid, 311, DIALOG_STYLE_INPUT, !"Промокод", !"{FFFFFF}Введите имеющийся у Вас промокод:\n\n{AFAFAF}С его помощью Вы можете получить определенные преимущества", !"Готово", !"Отмена");
			}
		}
    }
	    
	    case 872:
	    {
			if(!response)
				return callcmd::menu(playerid, "");
	    
	        if(listitem == 0)
				ShowPlayerDialogEx(playerid, 873, DIALOG_STYLE_MSGBOX, !"Решительность", !"{FFFFFF}Улучшение {AFAFAF}Решительность{FFFFFF}\n\nСтоимость: {33AA00}30000${FFFFFF}\nДоступно с 5 уровня\n\nВозможность уволиться из организации", !"Далее", !"Отмена");

			else if(listitem == 1)
				ShowPlayerDialogEx(playerid, 874, DIALOG_STYLE_MSGBOX, !"Рюкзак", !"{FFFFFF}Улучшение {AFAFAF}Рюкзак{FFFFFF}\n\nСтоимость: {33AA00}100000${FFFFFF}\nДоступно с 10 уровня\n\nВозможность переносить в два раза больше патронов, единиц оружия и наркотиков", !"Далее", !"Отмена");

		}
		case 873:
		{
			if(!response)
				return 1;

			if(PI[playerid][pDash])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже установлено выбранное улучшение");
			    
		    if(PI[playerid][pLevel] < 5)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Для покупки выбранного улучшения требуется 5 уровень");
		        
			if(PI[playerid][pMoney] < 30000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
			    
			GiveMoney(playerid, -30000, "покупка ул. решит");
			    
			PI[playerid][pDash] = 1;
			UpdatePlayerData(playerid, "Dash", PI[playerid][pDash]);
			
  			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы приобрели улучшение {FF9900}\"Решительность\"");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Теперь Вы можете покидать организацию по собственному желанию {FFFF00}(/leave)");
		}
		case 874:
		{
			if(!response)
				return 1;
				
			if(PI[playerid][pBag])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже установлено выбранное улучшение");

		    if(PI[playerid][pLevel] < 10)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Для покупки выбранного улучшения требуется 10 уровень");

			if(PI[playerid][pMoney] < 100000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			GiveMoney(playerid, -100000, "покупка ул. рюкзак");

			PI[playerid][pBag] = 1;
			UpdatePlayerData(playerid, "Bag", PI[playerid][pBag]);

  			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы приобрели улучшение {FF9900}\"Рюкзак\"");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Теперь Вы можете переносить в два раза больше патронов, единиц оружия и наркотиков");
		}
	    case 310:
		{
			callcmd::menu(playerid, "");
		}

		case 311:
		{
			if(!response)
				return 1;
				
		    if(PI[playerid][pPromo])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже активировали чей-то промокод");


  		   	new
	 			temp[48];

   			mysql_escape_string(inputtext, temp);

			new
				query_check_promo[49 + 40];

			mysql_format(mysql, query_check_promo, sizeof query_check_promo, "SELECT * FROM `promoyt` WHERE `pcName` = '%e'", temp);
			mysql_function_query(mysql, query_check_promo, true, "CheckPromo", "ds", playerid, temp);
		}
	    case 313:
	    {
			if(!response)
				return 1;
				
			if(GetPVarInt(playerid,"player_name_change"))
				return SendClientMessage(playerid, COLOR_GREY, !"Вы уже подавали заявку на смену ника");
				
   			if(strlen(inputtext) < 3 || strlen(inputtext) > 20)
			   	return SendClientMessage(playerid, COLOR_GREY, !"Длина ника не может быть меньше трех и больше 20 символов");
			   	
			if(strfind(inputtext,"|") != -1)
		 		return SendClientMessage(playerid, COLOR_GREY, !"В нике не может содержаться символ \"|\"");

			new regex:r = regex_new("^[a-zA-Z_]+$");
			
			if(!regex_check(inputtext, r))
                return SendClientMessage(playerid, COLOR_GREY, !"В никнейме найдены запрещенные символы!");

            regex_delete(r);
            

			new nickname[MAX_PLAYER_NAME],
				query_change_name[60 + MAX_PLAYER_NAME];

			mysql_escape_string(inputtext, nickname);
		    format(query_change_name, sizeof query_change_name, "SELECT `ID` FROM `accounts` WHERE `NickName` = '%s'", nickname);
		    mysql_function_query(mysql, query_change_name, true, "CheckChangeName", "ds", playerid, nickname);
	    }
	    case 270:
	    {
	        if(!response)
	            return 1;
	            
			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 271, DIALOG_STYLE_INPUT, !"Игровая валюта", !"{FFFFFF}Введите сумму, которую вы хотите получить (в игровых долларах)\nТекущий курс: {86B9FF}1 рубль - 1200$", !"Далее", !"Отмена");
			    case 1:
				{
					if(PI[playerid][pVirMoney] < 20)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 20 рублей на донат счете, чтобы поменять ник");
					}
					ShowPlayerDialogEx(playerid, 273, DIALOG_STYLE_INPUT, !"Смена ника", !"{FFFFFF}Введите игровой ник, на который вы хотите поменять свой:", !"Далее", !"Отмена");
				}
				case 2:
				{
					if(PI[playerid][pVirMoney] < 60)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 60 рублей на донат счете, чтобы сменить национальность и цвет кожи");
					}
					ShowPlayerDialogEx(playerid, 275, DIALOG_STYLE_MSGBOX, !"Смена цвета кожи", !"{FFFFFF}Выберите цвет кожи:", !"Светлый", !"Тёмный");
				}
				case 3:
				{
					if(PI[playerid][pVirMoney] < 50)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 50 рублей на донат счете, чтобы поменять возраст");
					}
					ShowPlayerDialogEx(playerid, 278, DIALOG_STYLE_INPUT, !"Смена игрового возраста", !"{FFFFFF}Введите желаемый возраст:\n{AFAFAF}Значение должно быть от 16 до 80 лет", !"Далее", !"Отмена");
				}
				case 4:
				{
					if(PI[playerid][pVirMoney] < 15)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 15 рублей на донат счете, чтобы поменять пол");
					}
                    ShowPlayerDialogEx(playerid, 280, DIALOG_STYLE_LIST, !"Смена пола", !"Мужской\nЖенский", !"Далее", !"Отмена");
				}
				case 5:
				{
					if(PI[playerid][pVirMoney] < 75)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 75 рублей на донат счете, чтобы снять варн");
					}
                    ShowPlayerDialogEx(playerid, 281, DIALOG_STYLE_MSGBOX, !"Снятие варна", !"{FFFFFF}Вы действительно хотите снять одно предупреждение за 75 рублей?", !"Да", !"Отмена");
				}
				case 6:
				{
					if(PI[playerid][pVirMoney] < 10)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 10 рублей на донат счете, чтобы повысить свою законопослушность");
					}
				    ShowPlayerDialogEx(playerid, 282, DIALOG_STYLE_MSGBOX, !"Законопослушность", !"{FFFFFF}Вы действительно хотите получить 10 единиц законопослушности за 10 рублей?", !"Да", !"Отмена");
				}
				case 7:
				{
					if(PI[playerid][pVirMoney] < 70)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 70 рублей на донат счете, чтобы приобрести пакет лицензий");
					}
                    ShowPlayerDialogEx(playerid, 283, DIALOG_STYLE_MSGBOX, !"Пакет лицензий", !"{FFFFFF}Вы действительно хотите приобрести пакет всех лицензий за 70 рублей?", !"Да", !"Отмена");
				}
				case 8:
				{
   					if(PI[playerid][pVirMoney] < 100)
					{
						ShowDonate(playerid);
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 100 рублей на донат счете, чтобы приобрести навык");
					}
                    return ShowPlayerDialogEx(playerid, 5561, DIALOG_STYLE_MSGBOX, !"Макс. навык дальнобойщика", !"{FFFFFF}Вы действительно хотите приобрести макс. навык дальнобойщика за 100 рублей?", !"Да", !"Отмена");
				}
				case 9:
				{
				    return SendClientMessage(playerid,-1,"Для регистрации семьи отправляйтесь в ближайшую мерию");
				}
				case 10:
				{
				    UpdateDonate(playerid);
				    
				    new
				        frmt_donate_info[120];
				        
					format(frmt_donate_info, sizeof frmt_donate_info, "{FFC800}[ДОНАТ] {FFFFFF}У вас на донат счете {86B9FF}%d{FFFFFF} %s", PI[playerid][pVirMoney], Declension_GetMoney(PI[playerid][pVirMoney]));
					SendClientMessage(playerid, COLOR_WHITE, frmt_donate_info);
					
				    ShowDonate(playerid);
				}
			}
	    }
	    case 271:
	    {
	        if(!response)
	            return ShowDonate(playerid);
	            
            if(!isNumeric(inputtext) || !strlen(inputtext))
				return ShowPlayerDialogEx(playerid, 271, DIALOG_STYLE_INPUT, !"Игровая валюта", !"{FFFFFF}Введите сумму, которую вы хотите получить (в игровых долларах)\nТекущий курс: {86B9FF}1 рубль - 1200$", !"Далее", !"Отмена");
	    
	        new amount = strval(inputtext);
	        
	        if(amount < 1200)
	        {
	            ShowPlayerDialogEx(playerid, 271, DIALOG_STYLE_INPUT, !"Игровая валюта", !"{FFFFFF}Введите сумму, которую вы хотите получить (в игровых долларах)\nТекущий курс: {86B9FF}1 рубль - 1200$", !"Далее", !"Отмена");
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Минимальная сумма: 1200$");
	        }
	        
			new
				money = floatround(amount / 1200.0, floatround_floor) * 1,
				tr_money = money * 1200;
				
			if(money < 1)
				return 1;
				
			if(PI[playerid][pVirMoney] < money)
			{
	            ShowPlayerDialogEx(playerid, 271, DIALOG_STYLE_INPUT, !"Игровая валюта", !"{FFFFFF}Введите сумму, которую вы хотите получить (в игровых долларах)\nТекущий курс: {86B9FF}1 рубль - 1200$", !"Далее", !"Отмена");
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег на донат счете");
			}
			
			pTemp[playerid][pDonateMoney] = money;
			pTemp[playerid][pDonateAmount] = tr_money;
			
			new
				frmt_donate_money[280];

			format(frmt_donate_money, sizeof frmt_donate_money, "{FFFFFF}Будет снято: %d %s\nБудет зачислено: %d$\nОстанется на донат счете: %d %s\n\nВы действительно хотите конвертировать?", money, Declension_GetMoney(money), tr_money, PI[playerid][pVirMoney] - money, Declension_GetMoney(PI[playerid][pVirMoney] - money));
			ShowPlayerDialogEx(playerid, 272, DIALOG_STYLE_MSGBOX, !"Игровая валюта", frmt_donate_money, !"Да", !"Отмена");
	    }
	    case 272:
	    {
	        if(!response)
	            return ShowDonate(playerid);
	            
			new
			    money = pTemp[playerid][pDonateMoney],
			    amount = pTemp[playerid][pDonateAmount];

	        if(money < 1 || amount < 1200)
	        {
	            ShowPlayerDialogEx(playerid, 271, DIALOG_STYLE_INPUT, !"Игровая валюта", !"{FFFFFF}Введите сумму, которую вы хотите получить (в игровых долларах)\nТекущий курс: {86B9FF}1 рубль - 1200$", !"Далее", !"Отмена");
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Минимальная сумма к оплате: 1 рубль");
	        }

			//UpdateDonate(playerid);
			
			if(PI[playerid][pVirMoney] < money)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег на донат счете");
				
			PI[playerid][pVirMoney] -= money;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);
			GiveMoney(playerid, amount, "перевод в рубли");

			new
			    frmt_message_transfer[100];
			    
			format(frmt_message_transfer, sizeof frmt_message_transfer, "{7AC71F}[Успешно] {FFFFFF}%d %s переведено в %d$", money, Declension_GetMoney(money), amount);
			SendClientMessage(playerid, COLOR_WHITE, frmt_message_transfer);
			
			if(PI[playerid][pPromo])
			{
			    new
			        promoid = PI[playerid][pPromo]-1;
			        
				GivePromoMoney(playerid, promoid, amount/100*10);
			}
			    
            ShowDonate(playerid);
            
			pTemp[playerid][pDonateMoney] = 0;
			pTemp[playerid][pDonateAmount] = 0;
	    }
	    case 273:
	    {
			if(!response)
				return ShowDonate(playerid);

   			if(strlen(inputtext) < 3 || strlen(inputtext) > 20)
   			{
   			    ShowPlayerDialogEx(playerid, 273, DIALOG_STYLE_INPUT, !"Смена ника", !"{FFFFFF}Введите игровой ник, на который вы хотите поменять свой:", !"Далее", !"Отмена");
			   	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Длина ника не может быть меньше трех и больше 20 символов");
			}
			
			if(strfind(inputtext,"|") != -1)
			{
			    ShowPlayerDialogEx(playerid, 273, DIALOG_STYLE_INPUT, !"Смена ника", !"{FFFFFF}Введите игровой ник, на который вы хотите поменять свой:", !"Далее", !"Отмена");
		 		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В нике не может содержаться символ \"|\"");
			}
			
			new regex:r = regex_new("^[a-zA-Z_]+$");

			if(!regex_check(inputtext, r))
			{
			    ShowPlayerDialogEx(playerid, 273, DIALOG_STYLE_INPUT, !"Смена ника", !"{FFFFFF}Введите игровой ник, на который вы хотите поменять свой:", !"Далее", !"Отмена");
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В никнейме найдены запрещенные символы!");
			}
			
            regex_delete(r);


			new nickname[MAX_PLAYER_NAME],
				query_change_name[60 + MAX_PLAYER_NAME];

			mysql_escape_string(inputtext, nickname);
		    format(query_change_name, sizeof query_change_name, "SELECT `ID` FROM `accounts` WHERE `NickName` = '%s'", nickname);
		    mysql_function_query(mysql, query_change_name, true, "CheckChangeNameDonate", "ds", playerid, nickname);
	    }
		case 274:
		{
			if(!response)
				return ShowDonate(playerid);
				
			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 20)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 20 рублей на донат счете, чтобы поменять ник");
			}
			
			new
			    nickname[MAX_PLAYER_NAME];
			    
			SetString(nickname, pTemp[playerid][pNewNick]);
			strdel(pTemp[playerid][pNewNick], 0, MAX_PLAYER_NAME);

   			if(strlen(nickname) < 3 || strlen(nickname) > 20)
   			{
   			    ShowPlayerDialogEx(playerid, 273, DIALOG_STYLE_INPUT, !"Смена ника", !"{FFFFFF}Введите игровой ник, на который вы хотите поменять свой:", !"Далее", !"Отмена");
			   	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Длина ника не может быть меньше трех и больше 20 символов");
			}
			if(strfind(nickname,"|") != -1)
			{
			    ShowPlayerDialogEx(playerid, 273, DIALOG_STYLE_INPUT, !"Смена ника", !"{FFFFFF}Введите игровой ник, на который вы хотите поменять свой:", !"Далее", !"Отмена");
		 		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В нике не может содержаться символ \"|\"");
			}

			new regex:r = regex_new("^[a-zA-Z_]+$");

			if(!regex_check(nickname, r))
			{
			    ShowPlayerDialogEx(playerid, 273, DIALOG_STYLE_INPUT, !"Смена ника", !"{FFFFFF}Введите игровой ник, на который вы хотите поменять свой:", !"Далее", !"Отмена");
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В никнейме найдены запрещенные символы!");
			}

			if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка при смене ника");
			}

			regex_delete(r);
            
            mysql_escape_string(nickname, nickname);



			new
			    oldname[MAX_PLAYER_NAME];
			    
			GetPlayerName(playerid, oldname, MAX_PLAYER_NAME);
			
			if(SetPlayerName(playerid, nickname) == -1)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас присутствуют запрещенные символы в никнейме");
			}

			
			new
			    query_namestore_new[140],
			    query_change_nick[130],
				query_updhouse_owner[130],
				query_business_owner[130],
				frmt_nick_message[220];

			
			
			PI[playerid][pVirMoney] -= 20;
	
			format(query_change_nick, sizeof query_change_nick, "UPDATE `accounts` SET `NickName` = '%s', `VirMoney` = '%d' WHERE `ID` = '%d'", nickname, PI[playerid][pVirMoney], PI[playerid][pID]);
			mysql_tquery(mysql, query_change_nick);
			
			new
				date[12],
				d,
				m,
				y;

			getdate(y, m, d);
			format(date, sizeof date, "%d-%d-%d", d, m, y);

			format(query_namestore_new, sizeof query_namestore_new, "INSERT INTO `namestore` (`account_id`, `newname`, `data`) VALUES ('%d', '%s', '%s')", PI[playerid][pID], PN(playerid), date);
			mysql_tquery(mysql, query_namestore_new);

			SetString(PlayerName[playerid], nickname);
			
			

			if(PI[playerid][pHouseKey] != 0)
			{
				if(GetString(HouseInfo[PI[playerid][pHouseKey]-1][hOwner], oldname))
				{
					new houseid = PI[playerid][pHouseKey] - 1;
					SetString(HouseInfo[houseid][hOwner], nickname);
					format(query_updhouse_owner,sizeof query_updhouse_owner,"UPDATE `houses` SET `Owner` = '%s' WHERE `ID` = '%d'",nickname,houseid+1);
					mysql_tquery(mysql, query_updhouse_owner);
				}

				format(string, sizeof(string), "UPDATE `houses` SET `Room_Owner_0` = '%s' WHERE `Room_Owner_0` = '%s'", nickname, oldname);
				mysql_tquery(mysql, string);
				format(string, sizeof(string), "UPDATE `houses` SET `Room_Owner_1` = '%s' WHERE `Room_Owner_1` = '%s'", nickname, oldname);
				mysql_tquery(mysql, string);
				format(string, sizeof(string), "UPDATE `houses` SET `Room_Owner_2` = '%s' WHERE `Room_Owner_2` = '%s'", nickname, oldname);
				mysql_tquery(mysql, string);
			}

			if(PI[playerid][pFamily] != 0)
			{
				new
				    famid = PI[playerid][pFamily]-1,
					frmt_update_family[120];

				if(GetString(gFamily[famid][fOwner], oldname))
				{
				    SetString(gFamily[famid][fOwner], nickname);
					format(frmt_update_family, sizeof frmt_update_family, "UPDATE `family` SET `Owner` = '%s' WHERE `ID` = '%d'", nickname, famid+1);
					mysql_tquery(mysql, frmt_update_family);
				}

				if(GetString(gFamily[famid][fSubOwner], oldname))
				{
				    SetString(gFamily[famid][fSubOwner], nickname);
					format(frmt_update_family, sizeof frmt_update_family, "UPDATE `family` SET `SubOwner` = '%s' WHERE `ID` = '%d'", nickname, famid+1);
					mysql_tquery(mysql, frmt_update_family);
				}

			}
			if(PI[playerid][pBizKey] < 1000 && PI[playerid][pBizKey] != 0)
			{
				if(GetString(BizInfo[PI[playerid][pBizKey]-1][bOwner], oldname))
				{
					new bizid = PI[playerid][pBizKey] - 1;
					SetString(BizInfo[bizid][bOwner], nickname);
					format(query_business_owner, sizeof query_business_owner, "UPDATE `business` SET `Owner` = '%s' WHERE `ID` = '%d'", nickname, bizid+1);
					mysql_tquery(mysql, query_business_owner);
					UpdateBiz(bizid,1);
				}
			}
			if(PI[playerid][pBizKey] > 1000 && PI[playerid][pBizKey] != 0)
			{
				if(GetString(gFillings[PI[playerid][pBizKey]-1000][fillingOwner], oldname))
				{
					new fillingid = PI[playerid][pBizKey] - 1000;
					SetString(gFillings[fillingid][fillingOwner], nickname);
					format(query_business_owner, sizeof query_business_owner, "UPDATE `fillings` SET `Owner` = '%s' WHERE `ID` = '%d'", nickname, fillingid+1);
					mysql_tquery(mysql, query_business_owner);
					UpdateFillingText(fillingid);
				}
			}

			for(new i; i < 15; i++)
			{
				for(new b; b < 10; b++)
				{
					if(GetString(gNickNomination[i][b], oldname))
					{
					    SetString(gNickNomination[i][b], nickname);
					    if(b == 0) SetDynamicObjectMaterialText(gNomination[i], 0, nickname, 130, "Ariel", 27, 1, 0xFFFFFF00, 0x00000000, 1);
					}
				}
			}
			
			
			format(frmt_nick_message, sizeof frmt_nick_message, "{7AC71F}[Успешно] {FFFFFF}Ваш никнейм был изменен на %s", nickname);
			SendClientMessage(playerid, COLOR_WHITE, frmt_nick_message);

			format(frmt_nick_message, sizeof frmt_nick_message, "%s изменил имя на %s", oldname, nickname);
			SendClientMessageToAll(COLOR_YELLOW, frmt_nick_message);

			format(frmt_nick_message, sizeof frmt_nick_message, "Ваш ник изменен на %s. Не забудьте указать новый ник в SA-MP клиенте.", nickname);
			SendClientMessage(playerid, 0xFF7640FF, frmt_nick_message);
		}
		case 275:
		{
			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 60)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 60 рублей на донат счете, чтобы сменить национальность и цвет кожи");
			}
			
			if(!response)
			{
				pTemp[playerid][pDonateColor] = 0;
			    ShowPlayerDialogEx(playerid, 276, DIALOG_STYLE_LIST, !"Смена национальности", !"Американец\nРусский\nФранцуз\nМексиканец\nЛатиноамериканц\nИспанец\nПортугалец\nЯпонец\nИтальянец\nАнгличанин", !"Выбор", !"Отмена");
			}
			else
			{
				pTemp[playerid][pDonateColor] = 1;
			    ShowPlayerDialogEx(playerid, 276, DIALOG_STYLE_LIST, !"Смена национальности", !"Американец\nРусский\nФранцуз\nМексиканец\nЛатиноамериканц\nИспанец\nПортугалец\nЯпонец\nИтальянец\nАнгличанин", !"Выбор", !"Отмена");
			}
		
		}
		case 276:
		{
	        if(!response)
	            return ShowDonate(playerid);

			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 60)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 60 рублей на донат счете, чтобы сменить национальность и цвет кожи");
			}
			
			pTemp[playerid][pDonateNation] = listitem+1;
			
			new
			    nation[32];

		    switch(pTemp[playerid][pDonateNation])
			{
				case 1: strcat(nation,"Американец");
				case 2: strcat(nation,"Русский");
				case 3: strcat(nation,"Француз");
				case 4: strcat(nation,"Мексиканец");
				case 5: strcat(nation,"Латиноамериканец");
				case 6: strcat(nation,"Испанец");
				case 7: strcat(nation,"Португалец");
				case 8: strcat(nation,"Японец");
				case 9: strcat(nation,"Итальянец");
				case 10: strcat(nation,"Англичанин");
			}

			new
				race = pTemp[playerid][pDonateColor],
				frmt_change_color[200];
				
			format(frmt_change_color, sizeof frmt_change_color, "{FFFFFF}Смена национальности\n\nЦвет кожи: %s\nНациональность: %s\nБудет снято: 60 рублей\nОстанется на донат счете: %d %s\n\nПродолжить?", race ? ("Светлый") : ("Тёмный"), nation, PI[playerid][pVirMoney] - 60, Declension_GetMoney(PI[playerid][pVirMoney] - 60));
			ShowPlayerDialogEx(playerid, 277, DIALOG_STYLE_MSGBOX, !"Смена национальности", frmt_change_color, !"Да", !"Отмена");
		}
		case 277:
		{
	        if(!response)
	            return ShowDonate(playerid);
		
			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 60)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 30 рублей на донат счете, чтобы сменить национальность и цвет кожи");
			}
			
			new
				race = pTemp[playerid][pDonateColor],
				nation = pTemp[playerid][pDonateNation];
				
			PI[playerid][pRace] = race;
			UpdatePlayerData(playerid, "Race", PI[playerid][pRace]);
			PI[playerid][pNation] = nation;
			UpdatePlayerData(playerid, "Nation", PI[playerid][pNation]);
			
			PI[playerid][pVirMoney] -= 60;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);
			
			ShowDonate(playerid);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно сменили национальность и цвет кожи");
		}
		case 278:
		{
	        if(!response)
	            return ShowDonate(playerid);

			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 50)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 50 рублей на донат счете, чтобы поменять возраст");
			}
		
			if(!strlen(inputtext))
			    return ShowPlayerDialogEx(playerid, 278, DIALOG_STYLE_INPUT, !"Смена игрового возраста", !"{FFFFFF}Введите желаемый возраст:\n{AFAFAF}Значение должно быть от 16 до 80 лет", !"Далее", !"Отмена");
			    
			if(!isNumeric(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Возраст персонажа должен содержать только цифры. Например: 17"), ShowPlayerDialogEx(playerid, 278, DIALOG_STYLE_INPUT, !"Смена игрового возраста", !"{FFFFFF}Введите желаемый возраст:\n{AFAFAF}Значение должно быть от 16 до 80 лет", !"Далее", !"Отмена");

			if(strval(inputtext) < 16 || strval(inputtext) > 80)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Возраст персонажа не может быть меньше 16 и больше 80"), ShowPlayerDialogEx(playerid, 278, DIALOG_STYLE_INPUT, !"Смена игрового возраста", !"{FFFFFF}Введите желаемый возраст:\n{AFAFAF}Значение должно быть от 16 до 80 лет", !"Далее", !"Отмена");

			pTemp[playerid][pDonateAge] = strval(inputtext);

			new
				frmt_change_age[180];
				
			format(frmt_change_age, sizeof frmt_change_age, "{FFFFFF}Смена возраста\n\nНовый игровой возраст: %d\nБудет снято: 25 рублей\nОстанется на донат счете: %d %s\nПродолжить?", strval(inputtext), PI[playerid][pVirMoney] - 50, Declension_GetMoney(PI[playerid][pVirMoney] - 50));
			ShowPlayerDialogEx(playerid, 279, DIALOG_STYLE_MSGBOX, !"Смена возраста", frmt_change_age, !"Да", !"Нет");
		}
		case 279:
		{
	        if(!response)
	            return ShowDonate(playerid);

			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 50)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 25 рублей на донат счете, чтобы поменять возраст");
			}
			
			new
			    age = pTemp[playerid][pDonateAge];

			if(age < 16 || age > 80)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Возраст персонажа не может быть меньше 16 и больше 80"), ShowDonate(playerid);

			PI[playerid][pAge] = age;
			UpdatePlayerData(playerid, "Age", PI[playerid][pAge]);
			PI[playerid][pVirMoney] -= 50;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);

			ShowDonate(playerid);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили свой игровой возраст");

		}
		case 280:
		{
	        if(!response)
	            return ShowDonate(playerid);

			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 15)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 15 рублей на донат счете, чтобы поменять пол");
			}
			if(PI[playerid][pSex] == listitem+1)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете изменить свой пол на текущий");
			}
		
		    PI[playerid][pSex] = listitem+1;
		    UpdatePlayerData(playerid, "Sex", PI[playerid][pSex]);
			PI[playerid][pVirMoney] -= 15;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);
			
			ShowDonate(playerid);
			
			if(listitem == 0)
				SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили свой игровой пол на Мужской");

			else if(listitem == 1)
				SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили свой игровой пол на Женский");
				
				
			if(PI[playerid][pFraction])
			{
			    new
			        fractionid = PI[playerid][pFraction]-1,
					rank = PI[playerid][pRank],
					skinid;

				if(PI[playerid][pSex] == 1)
				    skinid = OrgInfo[fractionid][oMSkins][rank-1];

				else if(PI[playerid][pSex] == 2)
				    skinid = OrgInfo[fractionid][oWSkins][rank-1];

				SetPlayerSkinEx(playerid, skinid);
				PI[playerid][pFractionSkin] = skinid;
				UpdatePlayerData(playerid, "FractionSkin", skinid);
			}
		}
		case 281:
		{
	        if(!response)
	            return ShowDonate(playerid);

			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 75)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 75 рублей на донат счете, чтобы снять варн");
			}
			
			if(!PI[playerid][pWarns])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет варнов"), ShowDonate(playerid);
			    
			PI[playerid][pWarns]--;
			UpdatePlayerData(playerid, "Warns", PI[playerid][pWarns]);
			
			if(PI[playerid][pWarnTime] > 7)
			{
			    PI[playerid][pWarnTime] = 7;
			    UpdatePlayerData(playerid, "WarnTime", PI[playerid][pWarnTime]);
			}
			else if(PI[playerid][pWarnTime] < 7)
			{
			    PI[playerid][pWarnTime] = 0;
			    UpdatePlayerData(playerid, "WarnTime", PI[playerid][pWarnTime]);
			}
			    
			PI[playerid][pVirMoney] -= 75;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);

			ShowDonate(playerid);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно сняли одно игровое предупреждение");
		}
		case 282:
		{
	        if(!response)
	            return ShowDonate(playerid);

			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 10)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 10 рублей на донат счете, чтобы повысить свою законопослушность");
			}

		    if(PI[playerid][pZKP] + 10 >= 100)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже максимальное значение законопослушности"), ShowDonate(playerid);
		        
			PI[playerid][pZKP] += 10;
			UpdatePlayerData(playerid, "ZKP", PI[playerid][pZKP]);

			PI[playerid][pVirMoney] -= 10;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);

			ShowDonate(playerid);
		    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно повысили свою законопослушность на 10 единиц");
		}
		case 283:
		{
	        if(!response)
	            return ShowDonate(playerid);

			//UpdateDonate(playerid);

			if(PI[playerid][pVirMoney] < 70)
			{
				ShowDonate(playerid);
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно иметь 70 рублей на донат счете, чтобы приобрести пакет лицензий");
			}
			if(PI[playerid][pCarLic] == YES_LICENSE && PI[playerid][pFlyLic] == YES_LICENSE && PI[playerid][pBoatLic] == YES_LICENSE && PI[playerid][pGunLic] == YES_LICENSE)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже имеются все лицензии"), ShowDonate(playerid);

			PI[playerid][pCarLic] = YES_LICENSE;
			UpdatePlayerData(playerid, "CarLic", PI[playerid][pCarLic]);

			PI[playerid][pFlyLic] = YES_LICENSE;
			UpdatePlayerData(playerid, "FlyLic", PI[playerid][pFlyLic]);

			PI[playerid][pBoatLic] = YES_LICENSE;
			UpdatePlayerData(playerid, "BoatLic", PI[playerid][pBoatLic]);

			PI[playerid][pGunLic] = YES_LICENSE;
			UpdatePlayerData(playerid, "GunLic", PI[playerid][pGunLic]);
	
			PI[playerid][pVirMoney] -= 35;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);

			if(PI[playerid][pQuest] == 11 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
			}
			
			ShowDonate(playerid);
		    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели пакет лицензий");

		}
	    case 817:
	    {
	        if(!response)
	            return 1;

			if(listitem == 0)
			    ShowPlayerDialogEx(playerid, 818, DIALOG_STYLE_INPUT, !"Телефонная книга", !"{FFFFFF}Введите номер, который хотите добавить", !"Далее", !"Отмена");
			    
			else
			    temp_pb_sel[playerid] = listitem, ShowPlayerDialogEx(playerid, 820, DIALOG_STYLE_LIST, !"Телефонная книга", !"1. Позвонить\n2. Написать СМС\n3. Удалить", !"Выбор", !"Закрыть");
	    }
	    case 818:
	    {
	        if(!response)
	            return 1;

			if(temp_pb_total[playerid] > 20)
			    return SendClientMessage(playerid, COLOR_GREY, !"Телефонная книга заполнена");
			    
			if(!strlen(inputtext))
			    return ShowPlayerDialogEx(playerid, 818, DIALOG_STYLE_INPUT, !"Телефонная книга", !"{FFFFFF}Введите номер, который хотите добавить:", !"Далее", !"Отмена");
			    
			if(!isNumeric(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 6)
			    return ShowPlayerDialogEx(playerid, 818, DIALOG_STYLE_INPUT, !"Телефонная книга", !"{FFFF00}Неверный номер\n\n{FFFFFF}Введите номер, который хотите добавить:", !"Далее", !"Отмена");

			temp_addnum_number[playerid] = strval(inputtext);
			ShowPlayerDialogEx(playerid, 819, DIALOG_STYLE_INPUT, !"Телефонная книга", !"{FFFFFF}Введите имя для сохранения номера:", !"Далее", !"Отмена");
		}
		case 819:
	    {
	        if(!response)
	            return 1;

			if(!strlen(inputtext))
			    return ShowPlayerDialogEx(playerid, 819, DIALOG_STYLE_INPUT, !"Телефонная книга", !"{FFFFFF}Введите имя для сохранения номера:", !"Далее", !"Отмена");
			    
			if(strlen(inputtext) < 3 || strlen(inputtext) > 24)
			    return ShowPlayerDialogEx(playerid, 819, DIALOG_STYLE_INPUT, !"Телефонная книга", !"{FFFF00}Неверное имя\n\n{FFFFFF}Введите имя для сохранения номера:", !"Далее", !"Отмена");

			new
				query_upt_num[80 + 31 + 11 + 10];
			    
			format(query_upt_num, sizeof query_upt_num, "UPDATE `phonebook` SET `Number%d` = '%d', `Name%d` = '%s' WHERE `OwnerID` = '%d'", temp_pb_total[playerid]+1, temp_addnum_number[playerid], temp_pb_total[playerid]+1, inputtext, PI[playerid][pID]);
			mysql_tquery(mysql, query_upt_num);
			
			SendClientMessage(playerid, COLOR_GREEN, !"Вы добавили номер в телефонную книгу");
		}
		case 820:
		{
	        if(!response)
	            return 1;

			new
			    query_checknum[120],
				name[32];
			    
			format(query_checknum, sizeof query_checknum, "SELECT `Number%d`, `Name%d` FROM `phonebook` WHERE `OwnerID` = '%d'", temp_pb_sel[playerid], temp_pb_sel[playerid], PI[playerid][pID]);
			
			new Cache:result = mysql_query(mysql, query_checknum);
		    if(cache_get_row_count(mysql))
		    {
				new number = cache_get_row_int(0, 0);
				cache_get_row(0, 1, name, mysql);
				
				new
				    number_new[12];
				    
				format(number_new, 12, "%d", number);
				
				if(listitem == 0)
				    callcmd::call(playerid, number_new);
				    
				else if(listitem == 1)
				    callcmd::sms(playerid, number_new);
				    
				else if(listitem == 2)
				{
					new
						query_upt_num[80 + 31 + 11 + 10];

					format(query_upt_num, sizeof query_upt_num, "UPDATE `phonebook` SET `Number%d` = '0', `Name%d` = '' WHERE `OwnerID` = '%d'", temp_pb_sel[playerid], temp_pb_sel[playerid], PI[playerid][pID]);
					mysql_tquery(mysql, query_upt_num);
				}
			}
			cache_delete(result, mysql);
		}
		case 828:
		{
			if(!temp_sim_timer[playerid])
			    return 1;

			if(temp_sim_seller[playerid] == INVALID_PLAYER_ID)
			    return 1;
			
			new
				sellerid = temp_sim_seller[playerid]-1;
					
		    if(!response)
			{
				SendClientMessage(playerid, COLOR_GREY, !"Вы отказались от покупки SIM-карты");
				SendClientMessage(sellerid, COLOR_GREY, !"Покупатель отказался покупать SIM-карту");
				temp_sim_seller[playerid] = INVALID_PLAYER_ID;
				temp_sim_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_sim_num[playerid] = 0;
				temp_sim_price[playerid] = 0;
				temp_sim_timer[playerid] = 0;
				return 1;
		    }
		    
			if(PI[sellerid][pTelNum] != temp_sim_num[playerid])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}SIM-карта была продана");
				temp_sim_seller[playerid] = INVALID_PLAYER_ID;
				temp_sim_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_sim_num[playerid] = 0;
				temp_sim_price[playerid] = 0;
				temp_sim_timer[playerid] = 0;
				return 1;
			}
			if(sellerid == INVALID_PLAYER_ID || !IsPlayerConnected(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Продавец вышел из игры, либо продал SIM-карту другому игроку");
				temp_sim_seller[playerid] = INVALID_PLAYER_ID;
				temp_sim_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_sim_num[playerid] = 0;
				temp_sim_price[playerid] = 0;
				temp_sim_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < temp_sim_price[playerid])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_sim_seller[playerid] = INVALID_PLAYER_ID;
				temp_sim_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_sim_num[playerid] = 0;
				temp_sim_price[playerid] = 0;
				temp_sim_timer[playerid] = 0;
				return 1;
			}

            PI[playerid][pTelNum] = temp_sim_num[playerid];
            PI[sellerid][pTelNum] = 0;
			
			new
			    frmt_buysim[70];
			    
			format(frmt_buysim, sizeof frmt_buysim, "Поздравляем с покупкой номера %d", temp_sim_num[playerid]);
			
			SendClientMessage(playerid, COLOR_GREEN, frmt_buysim);
			
            SendClientMessage(sellerid, COLOR_GREEN, !"Номер телефона продан!");
            PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
            
            UpdatePlayerData(playerid, "TelNum", PI[playerid][pTelNum]);
            UpdatePlayerData(sellerid, "TelNum", PI[sellerid][pTelNum]);
            //SaveAccount(playerid);

 			GiveMoney(playerid, -temp_sim_price[playerid], "покупка SIM у игрока");
 			GiveMoney(sellerid, temp_sim_price[playerid], "продажа SIM игроку");

			temp_sim_seller[playerid] = INVALID_PLAYER_ID;
			temp_sim_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_sim_num[playerid] = 0;
			temp_sim_price[playerid] = 0;
			temp_sim_timer[playerid] = 0;
		}
	    case 654:
	    {
	        if(!response)
	            return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			switch(listitem)
			{
				case 0: ShowPlayerDialogEx(playerid, 655, DIALOG_STYLE_LIST, !"Общак", !"Положить ед. оружия\nВзять ед. оружия", !"Далее", !"Назад");
				case 1: ShowPlayerDialogEx(playerid, 658, DIALOG_STYLE_LIST, !"Общак", !"Положить патроны\nВзять патроны", !"Далее", !"Назад");
				case 2: ShowPlayerDialogEx(playerid, 661, DIALOG_STYLE_LIST, !"Общак", !"Положить деньги\nВзять деньги", !"Далее", !"Назад");
				case 3: ShowPlayerDialogEx(playerid, 664, DIALOG_STYLE_LIST, !"Общак", !"Положить наркотики\nВзять наркотики", !"Далее", !"Назад");
			}
	    }
	    case 655:
	    {
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 654, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 656, DIALOG_STYLE_INPUT, !"Положить ед.оружия", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] < gMafiaStorageRank[mafiaid])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

					ShowPlayerDialogEx(playerid, 657, DIALOG_STYLE_INPUT, !"Взять ед.оружия", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}
			}
	    }
	    case 656:
	    {
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;
				
            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 500)");

			if(PI[playerid][pPackets] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно ед. оружия");

			PI[playerid][pPackets] -= strval(inputtext);
			UpdatePlayerData(playerid, "Packets", PI[playerid][pPackets]);

			gMafiaStorage[mafiaid][0] += strval(inputtext);
			UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `gun` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][0], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} ед. оружия", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил ед. оружия в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
	    }
		case 657:
		{
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			if(!gMafiaStorageStatus[mafiaid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

		    if(PI[playerid][pRank] < gMafiaStorageRank[mafiaid])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 500)");

			if(!PI[playerid][pBag])
			{
				if(PI[playerid][pPackets]+strval(inputtext) > 500)
			    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас максимальное количество ед. оружия");
			}
			else
			{
				if(PI[playerid][pPackets]+strval(inputtext) > 1000)
			    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас максимальное количество ед. оружия");
			}
			
			if(gMafiaStorage[mafiaid][0] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно ед. оружия");

			PI[playerid][pPackets] += strval(inputtext);
			UpdatePlayerData(playerid, "Packets", PI[playerid][pPackets]);

            gMafiaStorage[mafiaid][0] -= strval(inputtext);
            UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `gun` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][0], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} ед. оружия", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял ед. оружия из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

		}
		case 658:
		{
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 654, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 659, DIALOG_STYLE_INPUT, !"Положить патроны", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] < gMafiaStorageRank[mafiaid])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

					ShowPlayerDialogEx(playerid, 660, DIALOG_STYLE_INPUT, !"Взять патроны", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}
			}
		}
		case 659:
		{
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 500)");

			if(PI[playerid][pMats] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно патронов");

			PI[playerid][pMats] -= strval(inputtext);
			UpdatePlayerData(playerid, "Mats", PI[playerid][pMats]);

            gMafiaStorage[mafiaid][1] += strval(inputtext);
            UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `ammo` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][1], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} патронов", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил патроны в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 660:
		{
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			if(!gMafiaStorageStatus[mafiaid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

		    if(PI[playerid][pRank] < gMafiaStorageRank[mafiaid])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 500)");
		        
			if(!PI[playerid][pBag])
			{
				if(PI[playerid][pMats]+strval(inputtext) > 500)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас максимальное количество патронов");
			}
			else
			{
				if(PI[playerid][pMats]+strval(inputtext) > 1000)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас максимальное количество патронов");

			}
			
			if(gMafiaStorage[mafiaid][1] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно патронов");

			PI[playerid][pMats] += strval(inputtext);
			UpdatePlayerData(playerid, "Mats", PI[playerid][pMats]);

            gMafiaStorage[mafiaid][1] -= strval(inputtext);
            UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `ammo` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][1], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} патронов", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял патроны из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

		}
		case 661:
		{
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 654, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;


			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 662, DIALOG_STYLE_INPUT, !"Положить деньги", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] != 10)
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только лидеру");

					ShowPlayerDialogEx(playerid, 663, DIALOG_STYLE_INPUT, !"Взять деньги", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}
			}

		}

		case 662:
		{
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;
				
            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 500 || strval(inputtext) > 100000)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 500 до 100000)");

			if(PI[playerid][pMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			GiveMoney(playerid, -strval(inputtext), "склад");

            gMafiaStorage[mafiaid][3] += strval(inputtext);
            UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `money` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][3], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} $", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил деньги в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 663:
		{
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			if(!gMafiaStorageStatus[mafiaid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

		    if(PI[playerid][pRank] != 10)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только лидеру");

			if(strval(inputtext) < 1 || strval(inputtext) > 100000)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 100000)");

			if(gMafiaStorage[mafiaid][3] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно денег");

			GiveMoney(playerid, strval(inputtext), "склад");

            gMafiaStorage[mafiaid][3] -= strval(inputtext);
            UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `money` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][3], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} $", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял деньги из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 664:
		{
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 654, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 665, DIALOG_STYLE_INPUT, !"Положить наркотики", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] < gMafiaStorageRank[mafiaid])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

					ShowPlayerDialogEx(playerid, 666, DIALOG_STYLE_INPUT, !"Взять наркотики", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}
			}

		}
		case 665:
		{
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;
				
            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 100000)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 100000)");

			if(PI[playerid][pDrugs] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно наркотиков");

			PI[playerid][pDrugs] -= strval(inputtext);
			UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);

            gMafiaStorage[mafiaid][2] += strval(inputtext);
            UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `drugs` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][2], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} грамм наркотиков", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил наркотики в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 666:
		{
		    if(!response)
		        return 1;

			if(!IsAMafia(playerid))
				return 1;

			new
			    mafiaid = PI[playerid][pFraction] - 12;

			if(!IsPlayerInDynamicArea(playerid, gMafiaStockArea) && GetPlayerVirtualWorld(playerid) != mafiaid+1)
				return 1;

			if(!gMafiaStorageStatus[mafiaid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

		    if(PI[playerid][pRank] < gMafiaStorageRank[mafiaid])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

			if(strval(inputtext) < 1 || strval(inputtext) > 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 500)");

			if(!PI[playerid][pBag])
			{
				if(PI[playerid][pDrugs]+strval(inputtext) > 500)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас максимальное количество наркотиков");
			}
			else
			{
				if(PI[playerid][pDrugs]+strval(inputtext) > 1000)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас максимальное количество наркотиков");
			}
			
			if(gMafiaStorage[mafiaid][2] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно наркотиков");

			PI[playerid][pDrugs] += strval(inputtext);
			UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);

            gMafiaStorage[mafiaid][2] -= strval(inputtext);
            UpdateTextMafia();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `drugs` = '%d' WHERE `id` = %d", gMafiaStorage[mafiaid][2], mafiaid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} грамм наркотиков", PN(playerid), strval(inputtext));
			FractionChat(mafiaid+12, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял наркотики из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}

	    case 669:
		{
	        new
				vehid = pTemp[playerid][pTuningID],
				component = pTemp[playerid][pTuningComponent];
				
			if(!response)
				return RemoveVehicleComponent(vehid, component);

            if(!PI[playerid][pCars])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с"), RemoveVehicleComponent(vehid, component);

			if(PI[playerid][pMoney] < 10000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег"), RemoveVehicleComponent(vehid, component);
			    
		    for(new i; i < sizeof CarInfo; i++)
			{
				if(CarInfo[i][cVehID] != vehid)
					continue;
					
				for(new tn; tn < 14; tn++)
				{
				    if(GetVehicleComponentType(component) == tn)
						CarInfo[i][cTuning][tn] = component;
				}
				break;
			}
			SaveOwnableCar(playerid, vehid);
			GiveMoney(playerid, -10000, "тюнинг");
			
			new
			    frmt_tun_message[86];
			    
			format(frmt_tun_message, sizeof frmt_tun_message, "{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели постоянный элемент тюнинга [№%d]", component);
            SendClientMessage(playerid, COLOR_WHITE, frmt_tun_message);
		}
		case 670:
		{
            if(!response)
				return 1;

            if(!PI[playerid][pCars])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с");
				
			if(PI[playerid][pMoney] < 15000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			new slot = GetCarSlot(PI[playerid][pCars]),
	        	Float:x, Float:y, Float:z, Float:a,
				carid = CarInfo[slot][cVehID];

			if(CarInfo[slot][cVehID] == INVALID_VEHICLE_ID)
				return 1;
				
			GetVehiclePos(carid, x, y, z);
			GetVehicleZAngle(carid, a);

            new
				query_delete_tuning[128];

			format(query_delete_tuning, sizeof query_delete_tuning, "UPDATE `cars` SET `cPaintJob` = '5', `cTuning` = '0|0|0|0|0|0|0|0|0|0|0|0|0|0' WHERE `cOwnerID` = '%d'", PI[playerid][pID]);
			mysql_tquery(mysql, query_delete_tuning);

			CarInfo[slot][cPaintJob] = 5;
			
			SetVehicleToRespawn(carid);
			CarInfo[slot][cVehID] = carid;
			 
	  		SetVehicleNumberPlate(carid, CarInfo[slot][cNumber]);

			for(new tn; tn < 14; tn++)
				if(CarInfo[slot][cTuning][tn] != 0) RemoveVehicleComponent(CarInfo[slot][cVehID], CarInfo[slot][cTuning][tn]), CarInfo[slot][cTuning][tn] = 0;

			ChangeVehiclePaintjob(CarInfo[slot][cVehID], 5);

			
			VehicleInfo[carid][vFuel] = CarInfo[slot][cFuel];
			VehicleInfo[carid][vLock] = 1;
			SetVehiclePos(carid, x, y, z);
			SetVehicleZAngle(carid, a);
			SaveOwnableCar(playerid, carid);
			
			GiveMoney(playerid, -15000, "удаление тюнинг");
   			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Все элементы тюнинга удалены");
		}
		case 671:
		{
	        new
				vehid = pTemp[playerid][pTuningID],
				paintjob = pTemp[playerid][pTuningPaintjob]-1;

			new slot = GetCarSlot(PI[playerid][pCars]),
				carid = CarInfo[slot][cVehID];
				
			if(!response)
				return ChangeVehiclePaintjob(vehid, CarInfo[carid][cPaintJob]);

            if(!PI[playerid][pCars])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с"), ChangeVehiclePaintjob(vehid, CarInfo[carid][cPaintJob]);

			if(PI[playerid][pMoney] < 15000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег"), ChangeVehiclePaintjob(vehid, CarInfo[carid][cPaintJob]);

			for(new i; i < sizeof CarInfo; i++)
			{
				if(CarInfo[i][cVehID] != vehid)
					continue;

				CarInfo[i][cPaintJob] = paintjob;
			}
			SaveOwnableCar(playerid, vehid);
			GiveMoney(playerid, -15000, "тюнинг");

            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы успешно приобрели постоянную покраску авто");
		}
	    case 694:
		{
  			if(!response)
  				return 1;
  				
			if(!PI[playerid][pCars])
			    return 1;
  				
			if(!PI[playerid][pPTS] && temp_car_num_get[playerid])
			{
				PI[playerid][pPTS] = 1;
				UpdatePlayerData(playerid, "PTS", PI[playerid][pPTS]);
				temp_car_num_get[playerid] = 0;
				SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы получили ПТС. Используйте /pts, для его просмотра");
			}
		}
		case 695:
		{
  			if(!response)
  				return 1;

			if(!PI[playerid][pFine])
			    return 1;

			GiveMoney(playerid, -PI[playerid][pFine], "оплата штрафа");
			
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы оплатили штраф. Больше не нарушайте правила");
			PI[playerid][pFine] = 0;
			UpdatePlayerData(playerid, "Fine", PI[playerid][pFine]);
		}
		case 696:
		{
  			if(!response)
  				return 1;
  				
	 	    if(!PI[playerid][pWanted])
	        	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет розыска");

			new
	            time;

			if(PI[playerid][pWanted] > 1)
			    time = (PI[playerid][pWanted]-1) * 300;

			else
			    time = PI[playerid][pWanted] * 300;

		    if(temp_cuffer_sender[playerid] != INVALID_PLAYER_ID)
		    {
		        new
					cufferid = temp_cuffer_sender[playerid]-1;

		        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		        RemovePlayerAttachedObject(playerid, 0);
		        temp_cuffer_sender[playerid] = INVALID_PLAYER_ID;
		        temp_cuffer_receiver[cufferid] = INVALID_PLAYER_ID;
		    }
			if(GotoInfo[playerid][gtGoID] != INVALID_PLAYER_ID)
			{
			    CheckPlayerGoCuff(GotoInfo[playerid][gtGoID]);
				CheckPlayerGoCuff(playerid);
			}
		    PI[playerid][pJailTime] = time;
		    UpdatePlayerData(playerid, "JailTime", PI[playerid][pJailTime]);
		    PI[playerid][pWanted] = 0;
		    UpdatePlayerData(playerid, "Wanted", PI[playerid][pWanted]);
			PI[playerid][pJailAdmin] = 0;
			UpdatePlayerData(playerid, "JailAdmin", PI[playerid][pJailAdmin]);
		    SetPlayerWantedLevel(playerid, 0);
		    ResetPlayerWeapons(playerid);
		    SetPlayerSkinEx(playerid, 42);
		    PlayerPlaySound(playerid, 17004, 0.0, 0.0, 0.0);

		    switch(GetPlayerVirtualWorld(playerid))
		    {
				case 2:
				{
			        new JailedLS = random(4)+1;
				    switch(JailedLS)
				    {
				        case 1: SetPlayerPos(playerid, 226.9169,109.1662,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 2: SetPlayerPos(playerid, 222.7322,108.9943,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 3: SetPlayerPos(playerid, 218.7821,109.3731,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 4: SetPlayerPos(playerid, 214.7852,108.9267,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
					}
					SetPlayerVirtualWorld(playerid, 2);
		            SetPlayerInterior(playerid, 10);
		            PI[playerid][pPrison] = 1;
				}
		        case 0:
				{
			        new JailedSF = random(4)+1;
				    switch(JailedSF)
				    {
				        case 1: SetPlayerPos(playerid, 226.9169,109.1662,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 2: SetPlayerPos(playerid, 222.7322,108.9943,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 3: SetPlayerPos(playerid, 218.7821,109.3731,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 4: SetPlayerPos(playerid, 214.7852,108.9267,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
					}
					SetPlayerVirtualWorld(playerid, 0);
		            SetPlayerInterior(playerid, 10);
		            PI[playerid][pPrison] = 2;
				}
		        case 12:
				{
			        new JailedLV = random(4)+1;
				    switch(JailedLV)
				    {
				        case 1: SetPlayerPos(playerid, 226.9169,109.1662,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 2: SetPlayerPos(playerid, 222.7322,108.9943,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 3: SetPlayerPos(playerid, 218.7821,109.3731,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
				        case 4: SetPlayerPos(playerid, 214.7852,108.9267,999.0156), J_SetPlayerFacingAngle(playerid, 181.7349);
					}
					SetPlayerVirtualWorld(playerid, 12);
		            SetPlayerInterior(playerid, 10);
		            PI[playerid][pPrison] = 3;
				}
		    }
		    UpdatePlayerData(playerid, "Prison", PI[playerid][pPrison]);
		    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы посмотреть сколько Вам осталось сидеть в тюрьме, введите команду {FFFF00}/ptime");
		    ResetPlayerWeapons(playerid);
			if(PI[playerid][pJailKey])
			{
				PI[playerid][pJailTime] = 0;
				UpdatePlayerData(playerid, "JailTime", PI[playerid][pJailTime]);
				PI[playerid][pJailAdmin] = 0;
				UpdatePlayerData(playerid, "JailAdmin", PI[playerid][pJailAdmin]);

				SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У вас были ключи от камеры. Вы были освобождены");

				new
					prison = PI[playerid][pPrison]-1;

				SetPlayerSkinEx(playerid, GetSkinOfPlayer(playerid));
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, gJailExit[prison][0], gJailExit[prison][1], gJailExit[prison][2]);
				J_SetPlayerFacingAngle(playerid, gJailExit[prison][3]);
				PI[playerid][pPrison] = 0;
				UpdatePlayerData(playerid, "Prison", PI[playerid][pPrison]);
				PI[playerid][pJailKey] = 0;
				UpdatePlayerData(playerid, "JailKey", PI[playerid][pJailKey]);
			}
		}
	    case 780:
	    {
  			if(!response)
  				return 1;

			switch(listitem)
			{
			    case 0:
			    {
			        if(!PI[playerid][pReturnHouse])
			            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Компенсация за дом не найдена");
			            
					GiveMoney(playerid, PI[playerid][pReturnHouse], "возврат средств за дом");
					
					new
					    frmt_info[100];
					    
					format(frmt_info, sizeof frmt_info, "{7AC71F}[Успешно] {FFFFFF}Вы вернули {3B844D}$%d{FFFFFF} за неуплаченное имущество", PI[playerid][pReturnHouse]);
					SendClientMessage(playerid, COLOR_WHITE, frmt_info);
					
					PI[playerid][pReturnHouse] = 0;
					UpdatePlayerData(playerid, "ReturnHouse", PI[playerid][pReturnHouse]);
				}
			    case 1:
			    {
			        if(!PI[playerid][pReturnBusiness])
			            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Компенсация за бизнес не найдена");

					GiveMoney(playerid, PI[playerid][pReturnBusiness], "возврат средств за бизнес");

					new
					    frmt_info[100];

					format(frmt_info, sizeof frmt_info, "{7AC71F}[Успешно] {FFFFFF}Вы вернули {3B844D}$%d{FFFFFF} за неуплаченное имущество", PI[playerid][pReturnBusiness]);
					SendClientMessage(playerid, COLOR_WHITE, frmt_info);

					PI[playerid][pReturnBusiness] = 0;
					UpdatePlayerData(playerid, "ReturnBusiness", PI[playerid][pReturnBusiness]);
				}
			    case 2:
			    {
			        if(!PI[playerid][pReturnFilling])
			            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Компенсация за АЗС не найдена");

					GiveMoney(playerid, PI[playerid][pReturnFilling], "возврат средств за АЗС");

					new
					    frmt_info[100];

					format(frmt_info, sizeof frmt_info, "{7AC71F}[Успешно] {FFFFFF}Вы вернули {3B844D}$%d{FFFFFF} за неуплаченное имущество", PI[playerid][pReturnFilling]);
					SendClientMessage(playerid, COLOR_WHITE, frmt_info);

					PI[playerid][pReturnFilling] = 0;
					UpdatePlayerData(playerid, "ReturnFilling", PI[playerid][pReturnFilling]);
				}
			}
	    }
		case 787:
		{
  			if(!response)
  				return 1;
  				
			new house = PI[playerid][pHouseKey]-1;
  				
	        if(!PI[playerid][pHouseKey])
	            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет дома");

            if(!strlen(inputtext))
            {
				new frmt_days_h[120];
               	format(frmt_days_h, sizeof frmt_days_h, "{FFFFFF}Введите количество дней, на которые хотите оплатить дом\n\n{AFAFAF}От 1 до 30 дней\nОплачено: %d %s", HouseInfo[PI[playerid][pHouseKey]-1][hDays], Declension_GetDays(HouseInfo[PI[playerid][pHouseKey]-1][hDays]));
                ShowPlayerDialogEx(playerid, 787, DIALOG_STYLE_INPUT, !"Оплата дома", frmt_days_h, !"Оплатить", !"Отмена");
				return 1;
			}
			
			if(strval(inputtext) < 1 || strval(inputtext) > 30)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Неверное кол-во дней (от 1 до 30)");

			new rent = floatround(HouseInfo[house][hCost] * 0.005);
			if(HouseInfo[house][hImprove][3]) rent = rent / 2;
			
			new total = rent * strval(inputtext);
			
			if(HouseInfo[house][hDays] + strval(inputtext) > 30)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Максимальное количество оплаченных дней: 30");
				
			if(PI[playerid][pMoney] < total)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				
			new query[50 + 9];
			
			format(query, sizeof query, "UPDATE `houses` SET `Days` = '%d' WHERE ID = '%d'", HouseInfo[house][hDays]+strval(inputtext) , house+1);
			mysql_tquery(mysql, query);
			HouseInfo[house][hDays] += strval(inputtext);
			
			GiveMoney(playerid, -total, "оплата дома");
			
			SendClientMessage(playerid, COLOR_GREEN, "Вы успешно продлили аренду недвижимости.");


		}
		case 784:
		{
  			if(!response)
  				return 1;


	        if(PI[playerid][pBizKey] > 1000 || !PI[playerid][pBizKey])
	            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет бизнеса");


			new
				bizid = PI[playerid][pBizKey]-1;
			
            if(!strlen(inputtext))
            {
				new frmt_days_b[120];
               	format(frmt_days_b, sizeof frmt_days_b, "{FFFFFF}Введите количество дней, на которые хотите оплатить бизнес\n\n{AFAFAF}От 1 до 30 дней\nОплачено: %d %s", BizInfo[PI[playerid][pBizKey]-1][bDays], Declension_GetDays(BizInfo[PI[playerid][pBizKey]-1][bDays]));
				ShowPlayerDialogEx(playerid, 784, DIALOG_STYLE_INPUT, !"Оплата бизнеса", frmt_days_b, !"Оплатить", !"Отмена");
				return 1;
			}
			
			if(strval(inputtext) < 1 || strval(inputtext) > 30)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Неверное кол-во дней (от 1 до 30)");

			new rent = BizInfo[bizid][bCost]/800;

			new total = rent * strval(inputtext);

			if(BizInfo[bizid][bDays] + strval(inputtext) > 30)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Максимальное количество оплаченных дней: 30");

			if(PI[playerid][pMoney] < total)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			new query[80 + 9];

			format(query, sizeof query, "UPDATE `business` SET `Days` = '%d' WHERE ID = '%d'", BizInfo[bizid][bDays]+strval(inputtext) , bizid+1);
			mysql_tquery(mysql, query);
			BizInfo[bizid][bDays] += strval(inputtext);

			GiveMoney(playerid, -total, "оплата бизнеса");

			SendClientMessage(playerid, COLOR_GREEN, "Вы успешно продлили аренду недвижимости.");

		}
		case 785:
		{
  			if(!response)
  				return 1;


	        if(PI[playerid][pBizKey] < 1000 || !PI[playerid][pBizKey])
	            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет заправки");


			new fillingid = PI[playerid][pBizKey]-1001;

            if(!strlen(inputtext))
            {
				new frmt_days_a[120];
               	format(frmt_days_a, sizeof frmt_days_a, "{FFFFFF}Введите количество дней, на которые хотите оплатить АЗС\n\n{AFAFAF}От 1 до 30 дней\nОплачено: %d %s", gFillings[fillingid][fillingDay], Declension_GetDays(gFillings[fillingid][fillingDay]));
				ShowPlayerDialogEx(playerid, 785, DIALOG_STYLE_INPUT, !"Оплата заправки", frmt_days_a, !"Оплатить", !"Отмена");
				return 1;
			}
			
			if(strval(inputtext) < 1 || strval(inputtext) > 30)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Неверное кол-во дней (от 1 до 30)");

			new rent = gFillings[fillingid][fillingPrice]/200;

			new total = rent * strval(inputtext);

			if(gFillings[fillingid][fillingDay] + strval(inputtext) > 30)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Максимальное количество оплаченных дней: 30");

			if(PI[playerid][pMoney] < total)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			new query[80 + 9];

			format(query, sizeof query, "UPDATE `fillings` SET `Day` = '%d' WHERE ID = '%d'", gFillings[fillingid][fillingDay]+strval(inputtext) , fillingid+1);
			mysql_tquery(mysql, query);
			gFillings[fillingid][fillingDay] += strval(inputtext);

			GiveMoney(playerid, -total, "оплата азс");

			SendClientMessage(playerid, COLOR_GREEN, "Вы успешно продлили аренду недвижимости.");

		}
	    case 790:
	    {
  			if(!response)
  				return 1;
  				
			switch(listitem)
			{
			    case 0:
			    {
			        if(!PI[playerid][pHouseKey])
			            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет дома");

					new frmt_days_h[120];
	               	format(frmt_days_h, sizeof frmt_days_h, "{FFFFFF}Введите количество дней, на которые хотите оплатить дом\n\n{AFAFAF}От 1 до 30 дней\nОплачено: %d %s", HouseInfo[PI[playerid][pHouseKey]-1][hDays], Declension_GetDays(HouseInfo[PI[playerid][pHouseKey]-1][hDays]));
	                ShowPlayerDialogEx(playerid, 787, DIALOG_STYLE_INPUT, !"Оплата дома", frmt_days_h, !"Оплатить", !"Отмена");
				}
			    case 1:
			    {
			        if(PI[playerid][pBizKey] > 1000 || PI[playerid][pBizKey] == 0)
			            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет бизнеса");

					new frmt_days_b[120];
	               	format(frmt_days_b, sizeof frmt_days_b, "{FFFFFF}Введите количество дней, на которые хотите оплатить бизнес\n\n{AFAFAF}От 1 до 30 дней\nОплачено: %d %s", BizInfo[PI[playerid][pBizKey]-1][bDays], Declension_GetDays(BizInfo[PI[playerid][pBizKey]-1][bDays]));
					ShowPlayerDialogEx(playerid, 784, DIALOG_STYLE_INPUT, !"Оплата бизнеса", frmt_days_b, !"Оплатить", !"Отмена");
				}
			    case 2:
			    {
			        if(PI[playerid][pBizKey] < 1000 || PI[playerid][pBizKey] == 0)
			            return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет заправки");

					new frmt_days_a[120];
	               	format(frmt_days_a, sizeof frmt_days_a, "{FFFFFF}Введите количество дней, на которые хотите оплатить АЗС\n\n{AFAFAF}От 1 до 30 дней\nОплачено: %d %s", gFillings[PI[playerid][pBizKey]-1001][fillingDay], Declension_GetDays(gFillings[PI[playerid][pBizKey]-1001][fillingDay]));
					ShowPlayerDialogEx(playerid, 785, DIALOG_STYLE_INPUT, !"Оплата заправки", frmt_days_a, !"Оплатить", !"Отмена");
				}
			}
	    }
	    case 710:
		{
  			if(!response)
  				return 1;

			if(listitem == 0)
				ShowPlayerDialogEx(playerid, 710, DIALOG_STYLE_LIST, !"Экзамен", !"Выберите вид транспорта, на который хотите получить лицензию:\n{FF7319}1.{FFFFFF} Наземный транспорт\t{42B02C}500$\n{FF7319}2.{FFFFFF} Воздушный транспорт\t{42B02C}10000$\n{FF7319}3.{FFFFFF} Водный транспорт\t\t{42B02C}3000$", !"OK", !"Отмена");
				
			else if(listitem == 1)
			{
			    if(PI[playerid][pCarLic] == YES_LICENSE)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть водительские права");
					
				if(PI[playerid][pMoney] < 500)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");
					
				ShowPlayerDialogEx(playerid, 711, DIALOG_STYLE_MSGBOX, !"Автошкола", !"{FF9900}\t\t\t\t\t\tШкола вождения\n\n{FFFFFF}Добро пожаловать в автошколу. Чтобы сдать на права Вам нужно выполнить следующие действия\n{FF7319}1.{FFFFFF} Прочитайте и запомните ПДД\n{FF7319}2.{FFFFFF} Сдайте тест на знание ПДД\n{FF7319}3.{FFFFFF} Оплатите сдачу на права", !"Далее", !"Выход");

			}
			else if(listitem == 2)
			{
			    if(PI[playerid][pFlyLic] == YES_LICENSE)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть лицензия на полеты");

				if(PI[playerid][pMoney] < 10000)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

				if(PI[playerid][pLevel] < 3)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Лицензию можно получить с 3 уровня");

				ShowPlayerDialogEx(playerid, 709, DIALOG_STYLE_MSGBOX, !"Покупка лицензии", !"{FFFFFF}Вы действительно хотите приобрести лицензию на полеты за 10000$?", !"Да", !"Отмена");

			}
			else if(listitem == 3)
			{
			    if(PI[playerid][pBoatLic] == YES_LICENSE)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть лицензия на водный транспорт");

				if(PI[playerid][pMoney] < 3000)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

				if(PI[playerid][pLevel] < 3)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Лицензию можно получить с 3 уровня");

				ShowPlayerDialogEx(playerid, 708, DIALOG_STYLE_MSGBOX, !"Покупка лицензии", !"{FFFFFF}Вы действительно хотите приобрести лицензию на водный транспорт за 3000$?", !"Да", !"Отмена");

			}
		}
		case 709:
		{
  			if(!response)
  				return 1;
  				
		    if(PI[playerid][pFlyLic] == YES_LICENSE)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть лицензия на полеты");

			if(PI[playerid][pMoney] < 10000)
            	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

			if(PI[playerid][pLevel] < 3)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Лицензию можно получить с 3 уровня");

            PI[playerid][pFlyLic] = YES_LICENSE;
            UpdatePlayerData(playerid, "FlyLic", PI[playerid][pFlyLic]);
			GiveMoney(playerid, -10000, "покупка лиц полеты");

			SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем, Вы приобрели лицензию на полеты. Теперь Вы можете управлять воздушным транспортом");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFCC00}/lic [ID игрока]{FFFFFF}, для показа лицензий другому игроку");
		}
		case 708:
		{
  			if(!response)
  				return 1;

		    if(PI[playerid][pBoatLic] == YES_LICENSE)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть лицензия на водный транспорт");

			if(PI[playerid][pMoney] < 3000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

			if(PI[playerid][pLevel] < 3)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Лицензию можно получить с 3 уровня");

            PI[playerid][pBoatLic] = YES_LICENSE;
            UpdatePlayerData(playerid, "BoatLic", PI[playerid][pBoatLic]);
			GiveMoney(playerid, -3000, "покупка лиц водный");

			SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем, Вы приобрели лицензию на водный транспорт");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFCC00}/lic [ID игрока]{FFFFFF}, для показа лицензий другому игроку");

		}
		case 711:
		{
  			if(!response)
  				return 1;
  				
		    new
				frmt_info[2300];
				
			strcat(frmt_info,"Общие положения:\n");
			strcat(frmt_info,"1. Разрешенная скорость передвижения для т/с, по городу - 60 км/ч, за городом - 110 км/ч, на автомагистралях - 150 км/ч.\n");
			strcat(frmt_info,"2. При необходимости, водитель обязан пропустить т/с со спец.сигналом (Полиция,Служба спасения,Скорая помощь) , а именно: постепенно снижая скорость, прижаться к обочине.\n");
			strcat(frmt_info,"3. Перекрестки в штате являются нерегулируемыми. Разрешается проезд на запрещающие сигналы светофора.\n");
			strcat(frmt_info,"4. По требованию работника правоoхранительных органов, водитель обязан остановиться и выполнить все перечисленные требования сотрудника правоохранительных органов.\n");
			strcat(frmt_info,"5. В случае возникновения ДТП(Дорожно-транспортного происшествия) водитель обязан: \n");
			strcat(frmt_info,"  а) оставаться на месте ДТП;\n");
			strcat(frmt_info,"  б) Вызвать сотрудников правоохоранительных органов;\n");
			strcat(frmt_info,"  в) Вызвать сотрудников скорой помощи, если того требует ситуация.\n");
			strcat(frmt_info,"6. Водитель обязан пропускать пешеходов, в специальных местах для перехода (перекрестки, специальная разметка).\n");
			strcat(frmt_info,"7. Водитель обязан осуществлять парковку транспортного средства только на стоянках, либо на обочине, заезжая при этом только 2-мя колесами.\n");
			strcat(frmt_info,"Запрещается:\n");
			strcat(frmt_info,"1.  Выезд на полосу встречного движения при очевидной угрозе лобового столкновения.\n");
			strcat(frmt_info,"2.  Экстренное торможение без везкой причины, в случае возникновения поломки т/с, по мере возможности Вам следует:\n");
			strcat(frmt_info," а) прижаться к обочине;\n");
			strcat(frmt_info," б) включить сигнал, оповещающий об аварийной ситуации.\n");
			strcat(frmt_info,"3. Обгон впереди движущегося т/с с правой стороны,обгон разрешен лишь в случае поворота впереди движущегося т/с.\n");
			strcat(frmt_info,"4. Нарушение установленного скоростного лимита.\n");
			strcat(frmt_info,"5. Управление транспортным средством в нетрезвом виде.\n");
			strcat(frmt_info,"6. Разворот в туннелях строго запрещен.\n");
			strcat(frmt_info,"7. Движение транспортного средства задним ходом разрешается при условии, что этот маневр будет безопасен и не создаст помех другим участникам движения.\n");
			strcat(frmt_info,"При необходимости водитель должен прибегнуть к помощи других лиц.\n");
			strcat(frmt_info,"8. На автомагистралях запрещается: движение задним ходом и учебная езда.");
	        ShowPlayerDialogEx(playerid, 712, DIALOG_STYLE_MSGBOX, !"Автошкола", frmt_info, !"Далее", !"Отмена");

		}
		case 712:
		{
			if(!response)
				return 1;
				
			ShowPlayerDialogEx(playerid, 713, DIALOG_STYLE_MSGBOX, !"Автошкола", !"{FFFFFF}Сейчас Вам будет предложено пройти тест.\nЧтобы получить права, Вам нужно правильно ответить на все 5 вопросов", !"Далее", !"Отмена");
		}
		case 713:
		{
			if(!response)
				return 1;
				
            ShowTestQuestion(playerid, 0, 5, 764);
		}
		case 764:
		{
			if(!response)
				return 1;
				
			new
				q = temp_question_number[playerid];
				
			if(!listitem)
			    return ShowTestQuestion(playerid, 0, 2, 764, q);

			if(listitem != gExamTrueAnswer[q])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К сожалению Вы ответили неверно. Тест провален");

            ShowTestQuestion(playerid, 5, 10, 765);
		}
		case 765:
		{
			if(!response)
				return 1;

			new
				q = temp_question_number[playerid];

			if(!listitem)
			    return ShowTestQuestion(playerid, 2, 4, 765, q);

			if(listitem != gExamTrueAnswer[q])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К сожалению Вы ответили неверно. Тест провален");

            ShowTestQuestion(playerid, 10, 15, 766);
		}
		case 766:
		{
			if(!response)
				return 1;

			new
				q = temp_question_number[playerid];

			if(!listitem)
			    return ShowTestQuestion(playerid, 4, 6, 766, q);

			if(listitem != gExamTrueAnswer[q])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К сожалению Вы ответили неверно. Тест провален");

            ShowTestQuestion(playerid, 15, 20, 767);
		}
		case 767:
		{
			if(!response)
				return 1;

			new
				q = temp_question_number[playerid];

			if(!listitem)
			    return ShowTestQuestion(playerid, 6, 8, 767, q);

			if(listitem != gExamTrueAnswer[q])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К сожалению Вы ответили неверно. Тест провален");

            ShowTestQuestion(playerid, 20, 25, 768);
		}
		case 768:
		{
			if(!response)
				return 1;

			new
				q = temp_question_number[playerid];

			if(!listitem)
			    return ShowTestQuestion(playerid, 8, 12, 768, q);

			if(listitem != gExamTrueAnswer[q])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К сожалению Вы ответили неверно. Тест провален");
				
		    if(PI[playerid][pCarLic] == YES_LICENSE)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть водительские права");

			if(PI[playerid][pMoney] < 500)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");
				
            PI[playerid][pCarLic] = YES_LICENSE;
            UpdatePlayerData(playerid, "CarLic", PI[playerid][pCarLic]);
			GiveMoney(playerid, -500, "сдача на права");
			
			SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем, Вы получили водительские права");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFCC00}/lic [ID игрока]{FFFFFF}, для показа лицензий другому игроку");

			if(PI[playerid][pQuest] == 2 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Саймону");
			}
		}
	    case 791:
		{
            if(!response) return 1;

            if(listitem == 0)
            {
                new
                    query_templist[62],
                    id;

                format(query_templist, sizeof query_templist, "SELECT `id` FROM `bank` WHERE `ownerid` = '%d' LIMIT 3", PI[playerid][pID]);

                new Cache:tlist = mysql_query(mysql, query_templist), rows, fields;

                cache_get_data(rows,fields);

                if(cache_get_row_count(mysql))
                {
                    PI[playerid][pBankCount] = 0;
                    for(new i = 0; i < rows; i++)
                    {
                        id = cache_get_row_int(i, 0);
                        PI[playerid][pBankID][i] = id;

                        new query_save_bank[110];
                        format(query_save_bank, sizeof query_save_bank, "UPDATE `accounts` SET `BankID` = '%d|%d|%d' WHERE `ID` = '%d'", PI[playerid][pBankID][0], PI[playerid][pBankID][1], PI[playerid][pBankID][2], PI[playerid][pID]);
                        mysql_tquery(mysql, query_save_bank);


                        PI[playerid][pBankCount]++;
                        UpdatePlayerData(playerid, "BankCount", PI[playerid][pBankCount]);
                    }
                }
                cache_delete(tlist, mysql);

                new
                    query_get_banklist[60 + 9],
                    name[50],
                    frmt_bank_list[40 + 770];

                format(query_get_banklist, sizeof query_get_banklist, "SELECT `id`, `name` FROM `bank` WHERE `ownerid` = '%d' LIMIT 3", PI[playerid][pID]);

                new
                    Cache:result = mysql_query(mysql, query_get_banklist);

                cache_get_data(rows,fields);

                if(cache_get_row_count(mysql))
                {
                    format(frmt_bank_list, sizeof frmt_bank_list, "{9EE2FF}Основной счёт{FFFFFF}\n");
                    for(new i = 0; i < rows; i++)
                    {
                        id = cache_get_row_int(i, 0);
                        cache_get_row(i, 1, name, mysql, sizeof name);
                        format(frmt_bank_list, sizeof frmt_bank_list, "%s%d. %s (№%d)\n", frmt_bank_list, i+1, name, id);
                    }
                }
                else
                    format(frmt_bank_list, sizeof frmt_bank_list, "{9EE2FF}Основной счёт{FFFFFF}");

                ShowPlayerDialogEx(playerid, 792, DIALOG_STYLE_LIST, !"Список счетов", frmt_bank_list, !"Выбор", !"Назад");
                cache_delete(result, mysql);
            }
			else if (listitem == 1)
			{
			    if(PI[playerid][pBankCount] >= 3)
			        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Превышен лимит банковских счетов");
			        
				ShowPlayerDialogEx(playerid, 793, DIALOG_STYLE_INPUT, !"Создание банковского счета", !"\n\n{FFFFFF}Введите название будущего банковского счета.\nОно не должно превышать 15 символов\n\n", !"Создать", !"Назад");
			}
			else if(listitem == 2)
			{
			    if(!PI[playerid][pBizKey])
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет бизнеса");

				new
				    frmt_business_money[140];

				if(PI[playerid][pBizKey] < 1000)
				{
					new
						bid = PI[playerid][pBizKey]-1;

					format(frmt_business_money, sizeof frmt_business_money, "{FFFFFF}Укажите сумму, которую хотите снять\nВ кассе бизнеса: {4682B4}%d$", BizInfo[bid][bMoney]);
				}
				else
				{
					new
						fillingid = PI[playerid][pBizKey]-1001;

                    format(frmt_business_money, sizeof frmt_business_money, "{FFFFFF}Укажите сумму, которую хотите снять\nВ кассе бизнеса: {4682B4}%d$", gFillings[fillingid][fillingBank]);
				}
                ShowPlayerDialogEx(playerid, 899, DIALOG_STYLE_INPUT, !"Снять деньги с кассы бизнеса", frmt_business_money, !"Снять", !"Выход");
			}
		}
		case 792:
		{
  			if(!response)
  			{
			 	if(PI[playerid][pBizKey])
				 	ShowPlayerDialogEx(playerid, 791, DIALOG_STYLE_LIST, !"Услуги банка", !"Мои счета\nОткрыть новый счёт\nСнять деньги с кассы бизнеса", !"Принять", !"Отмена");

			 	else
			 		ShowPlayerDialogEx(playerid, 791, DIALOG_STYLE_LIST, !"Услуги банка", !"Мои счета\nОткрыть новый счёт", !"Принять", !"Отмена");
			 		
  				return 1;
			}
			
			if(listitem == 0)
            	ShowPlayerDialogEx(playerid, 893, DIALOG_STYLE_LIST, !"Банк", !"{FF7319}1.{FFFFFF} Узнать баланс счета\n{FF7319}2.{FFFFFF} Снять деньги\n{FF7319}3.{FFFFFF} Положить деньги\n{FF7319}4.{FFFFFF} Пополнить баланс телефона", !"Принять", !"Отмена");

			else if(listitem >= 1)
				bank_tec[playerid] = listitem-1, ShowPlayerDialogEx(playerid, 794, DIALOG_STYLE_INPUT, !"Доступ к счету", !"\n\n{FFFFFF}Чтобы войти в меню управления, введите защитный код:\n\n", !"Вход", !"Выход");

		}
		case 793:
        {
            if(!response)
            {
                if(PI[playerid][pBizKey])
                    ShowPlayerDialogEx(playerid, 791, DIALOG_STYLE_LIST, !"Услуги банка", !"Мои счета\nОткрыть новый счёт\nСнять деньги с кассы бизнеса", !"Принять", !"Отмена");

                else
                    ShowPlayerDialogEx(playerid, 791, DIALOG_STYLE_LIST, !"Услуги банка", !"Мои счета\nОткрыть новый счёт", !"Принять", !"Отмена");

                return 1;
            }

            if(PI[playerid][pLevel] < 3)
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Создание банковского счета доступно с 3 уровня!");

            if(strfind(inputtext,"|") != -1 || strfind(inputtext,"}") != -1 || strfind(inputtext,"{") != -1 || strfind(inputtext,"&") != -1 || strfind(inputtext,"#") != -1 || strfind(inputtext,"@") != -1)
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В название счета присутствуют запрещеные символы");

            if(strlen(inputtext) < 3 || strlen(inputtext) > 15)
                return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Название счета должно быть от 3 до 15 символов");

            new
                query[78],
                str[250],
                frmt_bank_name[83];

            format(query, sizeof query, "INSERT INTO `bank` VALUES ('', '%s', '9999', '0', '%d')", inputtext, PI[playerid][pID]);
            new Cache:result = mysql_query(mysql, query);

            new id = cache_insert_id(mysql);

            PI[playerid][pBankID][PI[playerid][pBankCount]] = id;
            new query_save_bank[110];
            format(query_save_bank, sizeof query_save_bank, "UPDATE `accounts` SET `BankID` = '%d|%d|%d' WHERE `ID` = '%d'", PI[playerid][pBankID][0], PI[playerid][pBankID][1], PI[playerid][pBankID][2], PI[playerid][pID]);
            mysql_tquery(mysql, query_save_bank);

            PI[playerid][pBankCount]++;
            UpdatePlayerData(playerid, "BankCount", PI[playerid][pBankCount]);
            bank_tec[playerid] = PI[playerid][pBankCount]-1;

            SendClientMessage(playerid, COLOR_YELLOW, "Вы успешно открыли новый счет в банке.");
            format(str,sizeof(str),"- Номер вашего счёта: %d. Название счета: %s. ПИН-код: 9999", id,inputtext);
            SendClientMessage(playerid, COLOR_YELLOW, str);
            SendClientMessage(playerid, COLOR_RED, "Не забудьте запомнить пин-код. При его утере Вы не сможете получить доступ к счету");

            format(frmt_bank_name, sizeof frmt_bank_name, "Счет №%d [%s]", id, inputtext);
            ShowPlayerDialogEx(playerid, 795, DIALOG_STYLE_LIST, frmt_bank_name, "{9EE2FF}Текущий баланс счета: 0{FFFFFF}\n1. Снять деньги со счета\n2. Положить деньги на счет\n3. Перевести на другой счет\n4. Сменить защитный код\n5. Переименовать счет", !"Выбор", !"Назад");
            cache_delete(result, mysql);
        }
		case 794:
		{
  			if(!response)
  				return bank_tec[playerid] = 0;
  			
			new query_get_code[117];
			
			format(query_get_code, sizeof query_get_code, "SELECT `code`, `name`, `money`, `id` FROM `bank` WHERE `ownerid` = '%d' AND `id` = '%d'", PI[playerid][pID], PI[playerid][pBankID][bank_tec[playerid]]);
			print(query_get_code);
			
			new
				Cache:result = mysql_query(mysql, query_get_code),
				code,
				name[50],
				money,
				id,
				frmt_bank_oper[290],
				frmt_bank_name[83];
				
			if(cache_get_row_count(mysql))
			{
				code = cache_get_row_int(0, 0);
				cache_get_row(0, 1, name, mysql, sizeof name);
				money = cache_get_row_int(0, 2);
				id = cache_get_row_int(0, 3);
				 
				if(strval(inputtext) != code)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Код введен неверно!");
					
  				format(frmt_bank_oper, sizeof frmt_bank_oper, "{9EE2FF}Текущий баланс счета: %d{FFFFFF}\n1. Снять деньги со счета\n2. Положить деньги на счет\n3. Перевести на другой счет\n4. Сменить защитный код\n5. Переименовать счет", money);
				format(frmt_bank_name, sizeof frmt_bank_name, "Счет №%d [%s]", id, name);
				ShowPlayerDialogEx(playerid, 795, DIALOG_STYLE_LIST, frmt_bank_name, frmt_bank_oper, !"Выбор", !"Назад");
			}
			
			else
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка при загрузке банковских счетов. Сообщите об этом на форуме.");
			    
			cache_delete(result, mysql);

		}
		case 795:
		{
  			if(!response)
  				return bank_tec[playerid] = 0;

			switch(listitem)
			{
				case 0:
				{
					new query_get_code[117];

					format(query_get_code, sizeof query_get_code, "SELECT `name`, `money`, `id` FROM `bank` WHERE `ownerid` = '%d' AND `id` = '%d'", PI[playerid][pID], PI[playerid][pBankID][bank_tec[playerid]]);

					new
						Cache:result = mysql_query(mysql, query_get_code),
						name[50],
						money,
						id,
						frmt_bank_oper[290],
						frmt_bank_name[83];

					if(cache_get_row_count(mysql))
					{
						cache_get_row(0, 0, name, mysql, sizeof name);
						money = cache_get_row_int(0, 1);
						id = cache_get_row_int(0, 2);
						
		  				format(frmt_bank_oper, sizeof frmt_bank_oper, "{9EE2FF}Текущий баланс счета: %d{FFFFFF}\n1. Снять деньги со счета\n2. Положить деньги на счет\n3. Перевести на другой счет\n4. Сменить защитный код\n5. Переименовать счет", money);
						format(frmt_bank_name, sizeof frmt_bank_name, "Счет №%d [%s]", id, name);
						ShowPlayerDialogEx(playerid, 795, DIALOG_STYLE_LIST, frmt_bank_name, frmt_bank_oper, !"Выбор", !"Назад");
					}

					else
					    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка при загрузке банковских счетов. Сообщите об этом на форуме.");

					cache_delete(result, mysql);
				}
				
		    	case 1:
					ShowPlayerDialogEx(playerid, 796, DIALOG_STYLE_INPUT, !"Вывод средств", !"{FFFFFF}Введите сумму, которую Вы хотите {FF0000}снять{FFFFFF} с банковского счета:", !"Ок", !"Выход");

				case 2:
					ShowPlayerDialogEx(playerid, 797, DIALOG_STYLE_INPUT, !"Пополнить счет", !"{FFFFFF}Введите сумму, которую Вы хотите {FF0000}положить{FFFFFF} на Ваш банковский счет:\n\n{AFAFAF}Значение от 1$ до 5000000$", !"Ок", !"Выход");

				case 3:
				    ShowPlayerDialogEx(playerid, 798, DIALOG_STYLE_INPUT, !"Перевод средств", !"{FFFFFF}Введите номер счета, на который Вы хотите {FF0000}перевести{FFFFFF} деньги:", !"Ок", !"Выход");

				case 4:
				    ShowPlayerDialogEx(playerid, 799, DIALOG_STYLE_INPUT, !"Смена кода", !"{FFFFFF}Введите новый защитный код\n\n{AFAFAF}Код может состоять только из цифр и не может начинаться с 0\nТребуется как минимум 4 цифры, максимальная длина кода 8 цифр", !"Ок", !"Выход");

   				case 5:
				    ShowPlayerDialogEx(playerid, 802, DIALOG_STYLE_INPUT, !"Переименовать счет", !"{FFFFFF}Введите новое{FFFFFF} название счета\n\nОно не дожно превышать 15 символов", !"Ок", !"Выход");

			}
		}
		case 796:
		{
  			if(!response)
  				return 1;
  				
			if(!strval(inputtext) || !isNumeric(inputtext))
				return ShowPlayerDialogEx(playerid, 796, DIALOG_STYLE_INPUT, !"Вывод средств", !"{FFFFFF}Введите сумму, которую Вы хотите {FF0000}снять{FFFFFF} с банковского счета:", !"Ок", !"Выход");

			if(strval(inputtext) < 1 || strval(inputtext) > 1000000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сумма от 1$ до 1000000$"), ShowPlayerDialogEx(playerid, 796, DIALOG_STYLE_INPUT, !"Вывод средств", !"{FFFFFF}Введите сумму, которую Вы хотите {FF0000}снять{FFFFFF} с банковского счета:", !"Ок", !"Выход");
				
			new query_get_money[100];

			format(query_get_money, sizeof query_get_money, "SELECT `money` FROM `bank` WHERE `ownerid` = '%d' AND `id` = '%d'", PI[playerid][pID], PI[playerid][pBankID][bank_tec[playerid]]);

			new
				Cache:result = mysql_query(mysql, query_get_money),
				query_money[120],
				money;
				
			if(cache_get_row_count(mysql))
			{
				money = cache_get_row_int(0, 0);
				if(strval(inputtext) > money)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На Вашем счету недостаточно средств");
					
				format(query_money, sizeof query_money, "UPDATE `bank` SET `money` = `money`-%d WHERE `ownerid` = '%d' AND `id` = '%d'", strval(inputtext), PI[playerid][pID], PI[playerid][pBankID][bank_tec[playerid]]);
				mysql_tquery(mysql, query_money);
				
				GiveMoney(playerid, strval(inputtext), "снятие средств с банк с");
				SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сняли деньги с банковского счета");
			}
			
			cache_delete(result, mysql);
			
		}
		case 797:
		{
  			if(!response)
  				return 1;

			if(!strval(inputtext) || !isNumeric(inputtext))
				return ShowPlayerDialogEx(playerid, 797, DIALOG_STYLE_INPUT, !"Пополнить счет", !"{FFFFFF}Введите сумму, которую Вы хотите {FF0000}положить{FFFFFF} на Ваш банковский счет:\n\n{AFAFAF}Значение от 1$ до 5000000$", !"Ок", !"Выход");

			if(strval(inputtext) < 1 || strval(inputtext) > 5000000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сумма от 1$ до 5000000$"), ShowPlayerDialogEx(playerid, 797, DIALOG_STYLE_INPUT, !"Пополнить счет", !"{FFFFFF}Введите сумму, которую Вы хотите {FF0000}положить{FFFFFF} на Ваш банковский счет:\n\n{AFAFAF}Значение от 1$ до 5000000$", !"Ок", !"Выход");

			new
				query_money[120];

			if(PI[playerid][pMoney] < strval(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			format(query_money, sizeof query_money, "UPDATE `bank` SET `money` = `money`+%d WHERE `ownerid` = '%d' AND `id` = '%d'", strval(inputtext), PI[playerid][pID], PI[playerid][pBankID][bank_tec[playerid]]);
			mysql_tquery(mysql, query_money);

			GiveMoney(playerid, -strval(inputtext), "пополнение средств в банк с");
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы положили деньги на банковский счет");

		}
		case 798:
		{
  			if(!response)
  				return 1;
  				
			if(!strval(inputtext) || !isNumeric(inputtext))
				return ShowPlayerDialogEx(playerid, 798, DIALOG_STYLE_INPUT, !"Перевод средств", !"{FFFFFF}Введите номер счета, на который Вы хотите {FF0000}перевести{FFFFFF} деньги:", !"Ок", !"Выход");

			if(strval(inputtext) < 1 || strval(inputtext) > 1000000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сумма от 1$ до 1000000$"), ShowPlayerDialogEx(playerid, 798, DIALOG_STYLE_INPUT, !"Перевод средств", !"{FFFFFF}Введите номер счета, на который Вы хотите {FF0000}перевести{FFFFFF} деньги:", !"Ок", !"Выход");

			if(strval(inputtext) >= PI[playerid][pBankID][0] && strval(inputtext) <= PI[playerid][pBankID][2])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нельзя перевести на свой счет!"), ShowPlayerDialogEx(playerid, 798, DIALOG_STYLE_INPUT, !"Перевод средств", !"{FFFFFF}Введите номер счета, на который Вы хотите {FF0000}перевести{FFFFFF} деньги:", !"Ок", !"Выход");


			new query_check_bank[65];

			format(query_check_bank, sizeof query_check_bank, "SELECT `name` FROM `bank` WHERE `id` = '%d'", strval(inputtext));

			new
				Cache:result = mysql_query(mysql, query_check_bank),
				name[50],
				frmt_check[200];

			if(cache_get_row_count(mysql))
			{
				cache_get_row(0, 0, name, mysql, sizeof name);
				temp_send_money[playerid] = strval(inputtext);
				format(frmt_check, sizeof frmt_check, "{FFFFFF}Номер счета: %d\nНазвание счета: %s\n\nПроверьте правильность данных, если они верны, то введите сумму необходимую для перевода:", temp_send_money[playerid], name);
				ShowPlayerDialogEx(playerid, 801, DIALOG_STYLE_INPUT, !"Перевод средств", frmt_check, !"Перевод", !"Отмена");
			}
			
			else
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Введенный банковский счет не существует");
			    
            cache_delete(result, mysql);
		}
		case 799:
		{
  			if(!response)
  				return 1;
  				
			if(!strval(inputtext) || !isNumeric(inputtext))
				return ShowPlayerDialogEx(playerid, 799, DIALOG_STYLE_INPUT, !"Смена кода", !"{FFFFFF}Введите новый защитный код\n\n{AFAFAF}Код может состоять только из цифр и не может начинаться с 0\nТребуется как минимум 4 цифры, максимальная длина кода 8 цифр", !"Ок", !"Выход");

			if(strlen(inputtext) < 4 || strlen(inputtext) > 8 || inputtext[0] == '0')
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Код должен быть от 4 символов до 8 и не может начинаться с нуля!"), ShowPlayerDialogEx(playerid, 799, DIALOG_STYLE_INPUT, !"Смена кода", !"{FFFFFF}Введите новый защитный код\n\n{AFAFAF}Код может состоять только из цифр и не может начинаться с 0\nТребуется как минимум 4 цифры, максимальная длина кода 8 цифр", !"Ок", !"Выход");

			new query_change_code[100];
			format(query_change_code, sizeof query_change_code, "UPDATE `bank` SET `code` = '%d' WHERE `id` = '%d'", strval(inputtext), PI[playerid][pBankID][bank_tec[playerid]]);
			mysql_tquery(mysql, query_change_code);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сменили защитный код, не забудьте записать его!");
		}
		case 802:
		{
			if(!strlen(inputtext))
				return ShowPlayerDialogEx(playerid, 800, DIALOG_STYLE_INPUT, !"Переименовать счет", !"{FFFFFF}Введите новое{FFFFFF} название счета\n\nОно не дожно превышать 15 символов", !"Ок", !"Выход");

			if(strlen(inputtext) < 1 || strlen(inputtext) > 15)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Название счета должно быть от 1 до 15 символов");
				
			if(strfind(inputtext,"|") != -1 || strfind(inputtext,"}") != -1 || strfind(inputtext,"{") != -1 || strfind(inputtext,"&") != -1 || strfind(inputtext,"#") != -1 || strfind(inputtext,"@") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В название счета присутствуют запрещеные символы");

			new
				query_rename[80],
				frmt_rename[90];
				
			format(query_rename, sizeof query_rename, "UPDATE `bank` SET `name` = \"%s\" WHERE `id` = %d", inputtext, PI[playerid][pBankID][bank_tec[playerid]]);
			mysql_tquery(mysql, query_rename);
			
			format(frmt_rename, sizeof frmt_rename, "{7AC71F}[Успешно] {FFFFFF}Вы сменили название счета №%d на %s", PI[playerid][pBankID][bank_tec[playerid]], inputtext);
			SendClientMessage(playerid, COLOR_WHITE, frmt_rename);
		}
		case 801:
		{
  			if(!response)
  				return 1;

			if(!strval(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма"), ShowPlayerDialogEx(playerid, 798, DIALOG_STYLE_INPUT, !"Перевод средств", !"{FFFFFF}Введите номер счета, на который Вы хотите {FF0000}перевести{FFFFFF} деньги:", !"Ок", !"Выход");

			if(strval(inputtext) < 1 || strval(inputtext) > 1000000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сумма от 1$ до 1000000$"), ShowPlayerDialogEx(playerid, 798, DIALOG_STYLE_INPUT, !"Перевод средств", !"{FFFFFF}Введите номер счета, на который Вы хотите {FF0000}перевести{FFFFFF} деньги:", !"Ок", !"Выход");

			new
				query_get_money[100],
				query_get_owner[60],
				ownerid;
				
			format(query_get_owner, sizeof query_get_owner, "SELECT `ownerid` FROM `bank` WHERE `id` = '%d'", temp_send_money[playerid]);
			new Cache:get_owner = mysql_query(mysql, query_get_owner);
			if(cache_get_row_count(mysql))
			{
			    ownerid = cache_get_row_int(0, 0);

			    if(ownerid == PI[playerid][pID])
			        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете перевести деньги на свой банковский счет"), cache_delete(get_owner, mysql);

			}
			else
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный счет"), cache_delete(get_owner, mysql);
			
			cache_delete(get_owner, mysql);
			
			format(query_get_money, sizeof query_get_money, "SELECT `money` FROM `bank` WHERE `ownerid` = '%d' AND `id` = '%d'", PI[playerid][pID], PI[playerid][pBankID][bank_tec[playerid]]);

			new
				Cache:send_bank = mysql_query(mysql, query_get_money),
				query[140],
				money;


			if(cache_get_row_count(mysql))
			{
			    money = cache_get_row_int(0, 0);
			    
				if(money < strval(inputtext))
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На Вашем счету недостаточно средств"), cache_delete(send_bank, mysql);


				format(query, sizeof query, "UPDATE `bank` SET `money` = `money`-%d WHERE `ownerid` = '%d' AND `id` = '%d'", strval(inputtext), PI[playerid][pID], PI[playerid][pBankID][bank_tec[playerid]]);
				mysql_tquery(mysql, query);
				format(query, sizeof query, "UPDATE `bank` SET `money` = `money`+%d WHERE `id` = '%d'", strval(inputtext), temp_send_money[playerid]);
				mysql_tquery(mysql, query);
				
				SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы перевели деньги на другой банковский счет");
				
			}
            cache_delete(send_bank, mysql);
            
            
			new query_check_owner[80];

			format(query_check_owner, sizeof query_check_owner, "SELECT `ownerid` FROM `bank` WHERE `id` = '%d'", temp_send_money[playerid]);

			new
				Cache:check_bank = mysql_query(mysql, query_check_owner),
				nickname[50],
				frmt_send[100];

			if(cache_get_row_count(mysql))
			{
				ownerid = cache_get_row_int(0, 0);
                GetPlayerNameByID(ownerid, nickname);
                
				new target = GetNameID(nickname);
				if(target != INVALID_PLAYER_ID && IsPlayerLogged[target])
				{
				    format(frmt_send, sizeof frmt_send, "{FFFF66}[BANK] {FFFFFF}На ваш банковский счет поступил перевод в размере $%d", strval(inputtext));
				    SendClientMessage(target, COLOR_WHITE, frmt_send);
				}
                
			}

			cache_delete(check_bank, mysql);
		}
		case 774:
		{
  			if(!response) return 1;
  				
			new businessid = BizEntered[playerid]-1;
			if(businessid < 0) return 1;
			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pPhone])
						return SendClientMessage(playerid,COLOR_WHITE,"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть телефон");
						
					new price = ShopPrice[0];
					
					if(PI[playerid][pMoney] < price)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					new number,
						count,
     					Cache:result;
					do
					{
						count++;
						if(count >= 20) return SendClientMessage(playerid,COLOR_WHITE,"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка, попробуйте еще раз");
						number = RandomEx(100000,999999);
						new format_buy_number[128];
						format(format_buy_number,sizeof(format_buy_number),"SELECT `ID` FROM `accounts` WHERE `TelNum` = '%d'",number);
						result = mysql_query(mysql, format_buy_number);
					}
					while(cache_get_row_count(mysql) > 0);
					
					cache_delete(result, mysql);
					
					PI[playerid][pPhone] = 1;
					UpdatePlayerData(playerid, "Phone", PI[playerid][pPhone]);
					PI[playerid][pTelNum] = number;
					UpdatePlayerData(playerid, "TelNum", PI[playerid][pTelNum]);
					
					if(BizInfo[businessid][bProducts] - ShopProduct[0] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[0];
						GiveBusinessMoney(businessid, ShopPrice[0]);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[0]/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -ShopPrice[0], "покупка телефона");

					new format_buy_number_text[128];
					format(format_buy_number_text, sizeof format_buy_number_text, "{7AC71F}[Успешно] {FFFFFF}Вы купили телефон. Ваш номер: {00BFFF}%d",number);
					SendClientMessage(playerid, COLOR_WHITE, format_buy_number_text);
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы позвонить, используйте команду {FFD700}/call{FFFFFF}, чтобы отправить SMS, используйте команду {FFD700}/sms");

					if(PI[playerid][pQuest] == 4 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
					{
				        PI[playerid][pQuestProcess] = 1;
				        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
				        PI[playerid][pQuestStatus] = 0;
				        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
				        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Саймону");
					}
				    new
						format_shop_buy[480];

					for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;
				}
				case 1:
				{
					if(PI[playerid][pMoney] < ShopPrice[1])
						return SendClientMessage(playerid,COLOR_WHITE,"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(!PI[playerid][pPhone])
						return SendClientMessage(playerid,COLOR_WHITE,"{FF2222}[Ошибка] {FFFFFF}У Вас нет телефона");
						
					ShowPlayerDialogEx(playerid, 75, DIALOG_STYLE_INPUT, !"Смена номера SIM-карты", !"\n{ffffff}Введите новый шестизначный номер телефона:\n", !"Купить", !"Отмена");
					return 1;

				}
				case 2:
				{
					if(PI[playerid][pKit] > 1)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже имеется максимальное количество аптечек");
						
					if(PI[playerid][pMoney] < ShopPrice[2])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
						

					if(BizInfo[businessid][bProducts] - ShopProduct[2] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[2];
						GiveBusinessMoney(businessid, ShopPrice[2]);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[2]/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -ShopPrice[2], "покупка аптечки");
					PI[playerid][pKit] += 1;
					UpdatePlayerData(playerid, "Kit", PI[playerid][pKit]);
					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили аптечку. Чтобы вылечиться введите команду {FFD700}/healme");

					new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;
				}
				case 3:
				{
				    if(PI[playerid][pWatch])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть часы");
						
				    if(PI[playerid][pMoney] < ShopPrice[3])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
						
					if(BizInfo[businessid][bProducts] - ShopProduct[3] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[3];
                        GiveBusinessMoney(businessid, ShopPrice[3]);
                        if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[3]/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -ShopPrice[3], "покупка часов");
					PI[playerid][pWatch] = 1;
                    UpdatePlayerData(playerid, "Watch", PI[playerid][pWatch]);
                    
				    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили часы. Чтобы посмотреть время введите команду {FFD700}/time");
					new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;
				}
				case 4:
				{
				    if(PI[playerid][pMoney] < ShopPrice[4])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
 					new weapon,ammo;
					GetPlayerWeaponData(playerid, GetWeaponSlot(14), weapon, ammo);
					if(ammo == 1 && weapon == 14) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть цветы!");
					if(BizInfo[businessid][bProducts] - ShopProduct[4] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[4];
						GiveBusinessMoney(businessid, ShopPrice[4]);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[4]/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -ShopPrice[4], "покупка цветов");
					
     				_GiveGun(playerid, 14, 1);
					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили букет цветов. Чтобы подарить цветы введите команду {FFD700}/flower");
					
					new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;
				}
				case 5:
				{
    				if(PI[playerid][pMoney] < ShopPrice[5])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					new weapon,ammo;
					GetPlayerWeaponData(playerid, GetWeaponSlot(46), weapon, ammo);
					if(ammo == 1 && weapon == 46) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть парашют!");
					if(BizInfo[businessid][bProducts] - ShopProduct[5] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[5];
                        GiveBusinessMoney(businessid, ShopPrice[5]);
                        if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[5]/100*10);
					}
					UpdateBiz(businessid,1);
   					
					GiveMoney(playerid, -ShopPrice[5], "покупка парашюта");
					
					_GiveGun(playerid, 46, 1);
					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили {FFD700}Парашют");
					
					new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;
				}
				case 6:
				{
    				if(PI[playerid][pMoney] < ShopPrice[6])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
						
				    if(PI[playerid][pMask])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть маска");
						
					if(BizInfo[businessid][bProducts] - ShopProduct[6] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[6];
						GiveBusinessMoney(businessid, ShopPrice[6]);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[6]/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -ShopPrice[6], "покупка маски");
					
					PI[playerid][pMask] = 1;
					UpdatePlayerData(playerid, "Mask", PI[playerid][pMask]);
					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили маску. Чтобы её использовать введите команду {FFD700}/mask");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы снять маску введите команду {FFD700}/maskoff");
					new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;

				}
				case 7:
				{
    				if(PI[playerid][pMoney] < ShopPrice[7])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					new weapon,ammo;
					GetPlayerWeaponData(playerid, GetWeaponSlot(43), weapon, ammo);
					if(ammo > 100 && weapon == 43) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть фотоаппарат!");
					if(BizInfo[businessid][bProducts] - ShopProduct[7] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[7];
                        GiveBusinessMoney(businessid, ShopPrice[7]);
                        if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[7]/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -ShopPrice[7], "покупка фотоаппарата");
					_GiveGun(playerid, 43, 50);
					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили {FFD700}Фотоаппарат");
					
					new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;

				}
				case 8:
				{
    				if(PI[playerid][pMoney] < ShopPrice[8])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
						
				    if(PI[playerid][pPhoneBook])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть телефонная книга");
						
					if(BizInfo[businessid][bProducts] - ShopProduct[8] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[8];
                        GiveBusinessMoney(businessid, ShopPrice[8]);
                        if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[8]/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -ShopPrice[8], "покупка телефонной книги");
					PI[playerid][pPhoneBook] = 1;
					UpdatePlayerData(playerid, "PhoneBook", PI[playerid][pPhoneBook]);
					
					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили телефонную книгу. Чтобы её использовать введите команду {FFD700}/phonebook");

					new
					    query_buy_pb[300];
					    
					format(query_buy_pb, sizeof query_buy_pb, "INSERT INTO `phonebook` VALUES \
					('', '%d', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '')", PI[playerid][pID]);
					
					mysql_tquery(mysql, query_buy_pb);
					
					new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;
				}
				case 9:
				{
    				if(PI[playerid][pMoney] < ShopPrice[9])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					if(PI[playerid][pTalkie] == 1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть рация");
					if(BizInfo[businessid][bProducts] - ShopProduct[9] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[9];
						GiveBusinessMoney(businessid, ShopPrice[9]);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[9]/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -ShopPrice[9], "покупка рации");

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили рацию. Использовать {FFD700}(/k или /d)");

					PI[playerid][pTalkie] = 1;
                    UpdatePlayerData(playerid, "Talkie", PI[playerid][pTalkie]);
					
					new format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;

				}
				case 10:
				{
    				if(PI[playerid][pMoney] < ShopPrice[10])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					if(PI[playerid][pRope] == 1)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть веревка");

					if(BizInfo[businessid][bProducts] - ShopProduct[10] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[10];
                        GiveBusinessMoney(businessid, ShopPrice[10]);
                        if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[10]/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -ShopPrice[10], "покупка веревки");

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили веревку");

					PI[playerid][pRope] = 1;
                    UpdatePlayerData(playerid, "Rope", PI[playerid][pRope]);
                    
					new format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;

				}
				case 11:
				{
    				if(PI[playerid][pMoney] < ShopPrice[11])
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(PI[playerid][pClip] > 0)
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть скрепки");
					    
					if(BizInfo[businessid][bProducts] - ShopProduct[11] > 0)
					{
						BizInfo[businessid][bProducts] -= ShopProduct[11];
                        GiveBusinessMoney(businessid, ShopPrice[11]);
                        if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[11]/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -ShopPrice[11], "покупка скрепки");

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы купили пачку скрепок. Чтобы ими воспользоваться, используйте {FFD700}/breakcar");

					PI[playerid][pClip] = 2;
                    UpdatePlayerData(playerid, "Clip", PI[playerid][pClip]);
				
					new format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
					return 1;
				}
			}
		}
		case 75:
		{
  			if(!response)
			  	return 1;

			new
				businessid = BizEntered[playerid]-1;

			if(businessid < 0)
				return 1;

			if(!PI[playerid][pPhone])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет телефона");
						
			if(!isNumeric(inputtext) || strlen(inputtext) != 6 || inputtext[0] == '0' || inputtext[0] == '+' || inputtext[0] == '-')
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Номер должен состоять из {FFD700}6 цифр{FFFFFF}. Первая цифра не должна быть {FFD700}нулём");
				ShowPlayerDialogEx(playerid, 75, DIALOG_STYLE_INPUT, !"Смена номера SIM-карты", !"{ffffff}Введите новый шестизначный номер телефона", !"Купить", !"Отмена");
				return 1;
			}
			
			new format_phone_acc[50 + 12];
			format(format_phone_acc,sizeof(format_phone_acc),"SELECT `ID` FROM `accounts` WHERE `TelNum` = '%s'",inputtext);

			new Cache:result = mysql_query(mysql, format_phone_acc);
			
			if(cache_get_row_count(mysql))
			{
		 		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Такой номер уже используется");
		 		ShowPlayerDialogEx(playerid, 75, DIALOG_STYLE_INPUT, !"Смена номера SIM-карты", !"{ffffff}Введите новый шестизначный номер телефона", !"Купить", !"Отмена");
		 		return cache_delete(result, mysql);
			}
			
			cache_delete(result, mysql);

			PI[playerid][pTelNum] = strval(inputtext);
			UpdatePlayerData(playerid, "TelNum", PI[playerid][pTelNum]);
			
			new mysql_phone_acc[60];
			format(mysql_phone_acc, sizeof mysql_phone_acc, "UPDATE `accounts` SET `TelNum` = '%s' WHERE `ID` = %d", inputtext, PI[playerid][pID]);
			mysql_tquery(mysql, mysql_phone_acc);

			new frmt_new_phonenumber[65 + 7];
			format(frmt_new_phonenumber, sizeof frmt_new_phonenumber, "{7AC71F}[Успешно] {FFFFFF}Ваш новый номер телефона: {00FF00}%d", PI[playerid][pTelNum]);
			SendClientMessage(playerid, COLOR_WHITE, frmt_new_phonenumber);
			
			
			if(BizInfo[businessid][bProducts] - ShopProduct[1] > 0)
			{
				BizInfo[businessid][bProducts] -= ShopProduct[1];
                GiveBusinessMoney(businessid, ShopPrice[1]);
                if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],ShopPrice[1]/100*10);
			}
			UpdateBiz(businessid,1);
					
			GiveMoney(playerid, -ShopPrice[1], "покупка сим-карты");
		}
		
		case 716:
		{
  			if(!response)
  				return 1;

			new
				id = BizEntered[playerid]-1;

			if(id < 0)
				return 1;
			
			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pMoney] < 215)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");
						
					if(BizInfo[id][bProducts] < 80)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В баре недостаточно продуктов");
						
					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) пиво", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 80;
					GiveBusinessMoney(id, 215);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],21);
					GiveMoney(playerid, -215, "покупка пива");
					SetPlayerSpecialAction(playerid, 22);
					UpdateBiz(id,1);
				}
				case 1:
				{
					if(PI[playerid][pMoney] < 330)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 120)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В баре недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) вино", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 120;
                    GiveBusinessMoney(id, 330);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],33);
					GiveMoney(playerid, -330, "покупка вино");
					SetPlayerSpecialAction(playerid, 20);
					UpdateBiz(id,1);
				}
				case 2:
				{
					if(PI[playerid][pMoney] < 335)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 124)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В баре недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) шампанское", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 124;
					GiveBusinessMoney(id, 335);
					
					GiveMoney(playerid, -335, "покупка шампанского");
					SetPlayerSpecialAction(playerid, 20);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],33);
					UpdateBiz(id,1);
				}
				case 3:
				{
					if(PI[playerid][pMoney] < 290)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 95)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В баре недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) виски", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 95;
                    GiveBusinessMoney(id, 290);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],29);
					GiveMoney(playerid, -290, "покупка виски");
					SetPlayerSpecialAction(playerid, 20);
					UpdateBiz(id,1);
				}
				case 4:
				{
					if(PI[playerid][pMoney] < 490)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 150)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В баре недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) шаверму", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 150;
                    GiveBusinessMoney(id, 490);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],49);
					GiveMoney(playerid, -490, "покупка шавермы");
					SetPlayerAttachedObject(playerid,0,2769,6,0.095999,0.073999,0.049000,-156.000030,-81.899986,12.599999,1.000000,1.000000,1.000000);
					ApplyAnimation(playerid,"FOOD","EAT_Burger", 2.0,0,0,0,0,5000,1);
					SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,0);

					UpdateBiz(id,1);
				}
			}
		}
		case 717:
		{
  			if(!response)
  				return 1;

			new
				id = BizEntered[playerid]-1;

			if(id < 0)
				return 1;

			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pMoney] < 580)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 190)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В ресторане недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) запеченного лосося", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 190;
                    GiveBusinessMoney(id, 580);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],58);
					GiveMoney(playerid, -580, "покупка запеченного лосося");
					SetPlayerAttachedObject(playerid,0,2355,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					ApplyAnimation(playerid,"FOOD","EAT_Burger", 2.0,0,0,0,0,5000,1);
					SetTimerEx("RemovePlayerAttachedObjectDelay",3000,false,"ii",playerid,0);
					UpdateBiz(id,1);
				}
				case 1:
				{
					if(PI[playerid][pMoney] < 650)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 220)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В ресторане недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) стейк средний прожарки", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 220;
                    GiveBusinessMoney(id, 650);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],65);
					GiveMoney(playerid, -650, "покупка стейка средней прожарки");
					SetPlayerAttachedObject(playerid,0,2354,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					ApplyAnimation(playerid,"FOOD","EAT_Burger", 2.0,0,0,0,0,5000,1);
					SetTimerEx("RemovePlayerAttachedObjectDelay",3000,false,"ii",playerid,0);
					UpdateBiz(id,1);
				}
				case 2:
				{
					if(PI[playerid][pMoney] < 540)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 170)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В ресторане недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) салат с судаком", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);
					
					BizInfo[id][bProducts] -= 170;
                    GiveBusinessMoney(id, 540);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],54);
					GiveMoney(playerid, -540, "покупка салата с судаком");
					SetPlayerAttachedObject(playerid,0,2353,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					ApplyAnimation(playerid,"FOOD","EAT_Burger", 2.0,0,0,0,0,5000,1);
					SetTimerEx("RemovePlayerAttachedObjectDelay",3000,false,"ii",playerid,0);
					UpdateBiz(id,1);
				}
				case 3:
				{
					if(PI[playerid][pMoney] < 330)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 80)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В ресторане недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) вино", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 80;
                    GiveBusinessMoney(id, 330);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],33);
					GiveMoney(playerid, -330, "покупка вина");
					SetPlayerSpecialAction(playerid, 20);
					UpdateBiz(id,1);
				}
				case 4:
				{
					if(PI[playerid][pMoney] < 335)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 85)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В ресторане недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) малиновый чизкейк", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 85;
					GiveBusinessMoney(id, 335);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],33);
					GiveMoney(playerid, -335, "покупка малинового чизкейка");
					SetPlayerAttachedObject(playerid,0,2213,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					ApplyAnimation(playerid,"FOOD","EAT_Burger", 2.0,0,0,0,0,5000,1);
					SetTimerEx("RemovePlayerAttachedObjectDelay",3000,false,"ii",playerid,0);
					UpdateBiz(id,1);
				}
			}
		}
		case 718:
		{
  			if(!response)
  				return 1;

			new
				id = BizEntered[playerid]-1;

			if(id < 0)
				return 1;

			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pMoney] < 380)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 120)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) бургер с курицей", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 120;
                    GiveBusinessMoney(id, 380);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],38);
					GiveMoney(playerid, -380, "покупка бургер с курицей");
					temp_eat[playerid] = 1;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 1:
				{
					if(PI[playerid][pMoney] < 410)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 140)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) бургер с говядиной", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 140;
                    GiveBusinessMoney(id, 410);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],41);
					GiveMoney(playerid, -410, "покупка бургер с говядиной");
					temp_eat[playerid] = 2;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 2:
				{
					if(PI[playerid][pMoney] < 425)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 145)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) чизбургер", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 145;
                    GiveBusinessMoney(id, 425);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],42);
					GiveMoney(playerid, -425, "покупка чизбургер");
					temp_eat[playerid] = 3;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 3:
				{
					if(PI[playerid][pMoney] < 110)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 50)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");
						
					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) картошку фри", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 50;
					GiveBusinessMoney(id, 110);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],11);
					GiveMoney(playerid, -110, "покупка картошки фри");
					temp_eat[playerid] = 4;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 4:
				{
					if(PI[playerid][pMoney] < 230)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 90)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) газированный напиток", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 90;
					GiveBusinessMoney(id, 230);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],23);
					GiveMoney(playerid, -230, "покупка газированный напиток");
					temp_eat[playerid] = 5;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
			}
			if(PI[playerid][pQuest] == 15 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
			}
		}
		case 719:
		{
  			if(!response)
  				return 1;

			new
				id = BizEntered[playerid]-1;

			if(id < 0)
				return 1;

			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pMoney] < 356)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 120)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) пиццу Маргариту", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 120;
                    GiveBusinessMoney(id, 356);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],35);
					GiveMoney(playerid, -356, "покупка Пицца Маргарита");
					temp_eat[playerid] = 6;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 1:
				{
					if(PI[playerid][pMoney] < 390)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 130)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) пиццу 4 сыра", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);
					
					BizInfo[id][bProducts] -= 130;
                    GiveBusinessMoney(id, 390);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],39);
					GiveMoney(playerid, -390, "покупка Пицца 4 сыра");
					temp_eat[playerid] = 7;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 2:
				{
					if(PI[playerid][pMoney] < 335)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 105)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) кальцоне с ветчиной", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 105;
                    GiveBusinessMoney(id, 335);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],33);
					GiveMoney(playerid, -335, "покупка кальцоне с ветчиной");
					temp_eat[playerid] = 8;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 3:
				{
					if(PI[playerid][pMoney] < 230)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 90)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) газированный напиток", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);
					
					BizInfo[id][bProducts] -= 90;
					GiveBusinessMoney(id, 230);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],23);
					GiveMoney(playerid, -230, "покупка газированный напиток");
					temp_eat[playerid] = 9;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {CD32CD}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {CD32CD}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
			}
			if(PI[playerid][pQuest] == 15 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
			}
		}
		case 720:
		{
  			if(!response)
  				return 1;

			new
				id = BizEntered[playerid]-1;

			if(id < 0)
				return 1;

			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pMoney] < 380)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 140)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) бургер с курицей", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 140;
                    GiveBusinessMoney(id, 380);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],38);
					temp_eat[playerid] = 10;
					GiveMoney(playerid, -380, "покупка Бургер с курицей");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {CD32CD}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {CD32CD}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 1:
				{
					if(PI[playerid][pMoney] < 325)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 110)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) куриные крылышки", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 110;
                    GiveBusinessMoney(id, 325);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],32);
					temp_eat[playerid] = 11;
					GiveMoney(playerid, -325, "покупка куриные крылышки");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {CD32CD}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {CD32CD}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 2:
				{
					if(PI[playerid][pMoney] < 295)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 90)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) хотдог с куриной сосиской", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 90;
                    GiveBusinessMoney(id, 295);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],29);
					temp_eat[playerid] = 12;
					GiveMoney(playerid, -295, "покупка Хотдог с куриной сосиской");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {CD32CD}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {CD32CD}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 3:
				{
					if(PI[playerid][pMoney] < 270)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 85)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) пирожок с яблоком", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 85;
                    GiveBusinessMoney(id, 270);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],27);
					temp_eat[playerid] = 13;
					GiveMoney(playerid, -270, "покупка пирожок с яблоком");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {CD32CD}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {CD32CD}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
				case 4:
				{
					if(PI[playerid][pMoney] < 220)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

					if(BizInfo[id][bProducts] < 60)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В закусочной недостаточно продуктов");

					new frmt_me[MAX_PLAYER_NAME + 60];
					format(frmt_me, sizeof frmt_me, "%s купил(-а) чай", PN(playerid));
					ProxDetector(25, playerid, frmt_me, COLOR_ME);

					BizInfo[id][bProducts] -= 60;
                    GiveBusinessMoney(id, 220);
                    if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],22);
					temp_eat[playerid] = 14;
					GiveMoney(playerid, -220, "покупка чай");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {CD32CD}/eat{FFFFFF}, чтобы употребить купленное");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {CD32CD}/put");
					SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
					UpdateBiz(id,1);
				}
			}
			if(PI[playerid][pQuest] == 15 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
			}
		}
		case 293:
		{
  			if(!response)
  				return 1;
  				
			if(!accs_change[playerid])
			{
				accs_change[playerid] = true;

				new
					Float:X, Float:Y, Float:Z, Float:R;

				GetPlayerPos(playerid, X, Y, Z);

				GetPlayerFacingAngle(playerid, R);
				SetPVarFloat(playerid, "pos_x", X);
				SetPVarFloat(playerid, "pos_y", Y);
				SetPVarFloat(playerid, "pos_z", Z);
				SetPVarFloat(playerid, "pos_a", R);

				SetPVarInt(playerid, "interior", GetPlayerInterior(playerid));
				SetPVarInt(playerid, "vw", GetPlayerVirtualWorld(playerid));
				f_TogglePlayerControllable(playerid, false);
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, playerid + 1);
				SetPlayerCameraPos(playerid, 204.210372, -43.788745, 1002.280212);
				SetPlayerCameraLookAt(playerid, 204.091766, -38.912220, 1001.182312);

                accs_sel[playerid] = 0;
                accs_class[playerid] = listitem;
				ShowPlayerAccessoriesTD(playerid);
			}
		}
		case 464:
		{
  			if(!response)
  				return 1;

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, 822.1745, 1.8692, 1004.1797))
				return 1;
				
			switch(listitem)
			{
			    case 0:
			    {
			        if(PI[playerid][pLevel] < 4)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игра доступна с четвертого уровня");
			            
				    if(0 == gPaintBall[pbStatus])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент нет активной игры");

					if(gPaintBall[pbStatus] != 1)
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игра уже началась");

					if(pTemp[playerid][pRegPaint])
					   return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже зарегистрировались в игре. Ожидайте начала");

					ShowPlayerDialogEx(playerid, 465, DIALOG_STYLE_MSGBOX, !"PaintBall", !"{FFFFFF}Стоимость аренды снаряжения: {33AA33}3000${FFFFFF}\n\nВы действительно хотите зарегистрироваться?", !"Да", !"Нет");
			    }
			}
		}
		case 465:
		{
  			if(!response)
  				return 1;

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, 822.1745, 1.8692, 1004.1797))
				return 1;
				
		    if(0 == gPaintBall[pbStatus])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент нет активной игры");

			if(gPaintBall[pbStatus] != 1)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игра уже началась");
				
			if(gPaintBall[pbPlayers] >= 30)
			   return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Все места заняты");

			if(pTemp[playerid][pRegPaint])
			   return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже зарегистрировались в игре. Ожидайте начала");

			if(PI[playerid][pMoney] < 3000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
			    
	        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы зарегистрировались в PaintBall. Ожидайте начала");
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Не покидайте помещение, иначе Вы будете исключены!");
            gPaintBall[pbPlayers]++;
			pTemp[playerid][pRegPaint] = true;
			GiveMoney(playerid, -3000, "пеинт");
			
		    if(BizInfo[67][bProducts] - 15 > 0)
		    {
			    BizInfo[67][bProducts] -= 15;
				GiveBusinessMoney(67, 700);
				if(BizInfo[67][bKrasher]) GiveFracBank(BizInfo[67][bKrasher],700/100*10);
			}
		}
		case 377:
		{
  			if(!response)
  				return 1;
				
			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;
				
			switch(listitem)
			{
				case 0: ShowPlayerDialogEx(playerid, 377, DIALOG_STYLE_LIST, !"Агентство недвижимости", !"Выберите тип недвижимости:\n{FF7319}1.{FFFFFF} Дома\n{FF7319}2.{FFFFFF} Бизнесы\n{FF7319}3.{FFFFFF} АЗС", !"Выбор", !"Выход");
				case 1:
				{
				    new
				        frmt_houses_list[700],
						classname[25],
						house_count;
				        
					for(new i; i < OWNABLEHOUSES; i++)
					{
					    if(!GetString(HouseInfo[i][hOwner], "The State"))
							continue;

                        house_count++;
						pTemp[playerid][pEstateHouseLast] = i+1;

						if(house_count > 20)
						{
                        	format(frmt_houses_list, sizeof frmt_houses_list, "%s{ED6160}Далее >>", frmt_houses_list);
						    break;
						}

				    	switch(HouseInfo[i][hLevel])
						{
							case 0: SetString(classname, "Дом эконом класса");
							case 1: SetString(classname, "Дом среднего класса");
							case 2: SetString(classname, "Дом элитного класса");
							case 3: SetString(classname, "Особняк");
							default: SetString(classname, "Неизвестно");
						}

				    	format(frmt_houses_list, sizeof frmt_houses_list, "%s%s [№%d]\n", frmt_houses_list, classname, i+1);
					}
				    if(house_count)
				        ShowPlayerDialogEx(playerid, 378, DIALOG_STYLE_LIST, !"Выберите дом:", frmt_houses_list, !"Выбор", !"Назад");
				    
				    else
				        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных домов");
				}
				case 2:
				{
				    new
				        frmt_business_list[700],
						biz_count;

					for(new i; i < OWNABLEBIZES; i++)
					{
					    if(!GetString(BizInfo[i][bOwner], "The State"))
							continue;

                        biz_count++;
						pTemp[playerid][pEstateBizLast] = i+1;

						if(biz_count > 20)
						{
                        	format(frmt_business_list, sizeof frmt_business_list, "%s{ED6160}Далее >>", frmt_business_list);
						    break;
						}

				    	format(frmt_business_list, sizeof frmt_business_list, "%s%s [№%d]\n", frmt_business_list, BizInfo[i][bName], i+1);
					}
				    if(biz_count)
				        ShowPlayerDialogEx(playerid, 381, DIALOG_STYLE_LIST, !"Выберите бизнес:", frmt_business_list, !"Выбор", !"Назад");

				    else
				        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных бизнесов");
				}
				case 3:
				{
				    new
				        frmt_filling_list[700],
						filling_count;

					for(new i; i < MAX_FILLING; i++)
					{
					    if(!GetString(gFillings[i][fillingOwner], "The State"))
							continue;

                        filling_count++;
						pTemp[playerid][pEstateFillLast] = i+1;

						if(filling_count > 20)
						{
                        	format(frmt_filling_list, sizeof frmt_filling_list, "%s{ED6160}Далее >>", frmt_filling_list);
						    break;
						}

				    	format(frmt_filling_list, sizeof frmt_filling_list, "%sАЗС [№%d]\n", frmt_filling_list, i+1);
					}
				    if(filling_count)
				        ShowPlayerDialogEx(playerid, 384, DIALOG_STYLE_LIST, !"Выберите АЗС:", frmt_filling_list, !"Выбор", !"Назад");

				    else
				        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных АЗС");
				}
			}
			return 1;
		}
		case 378:
		{
  			if(!response) return ShowPlayerDialogEx(playerid, 377, DIALOG_STYLE_LIST, !"Агентство недвижимости", !"Выберите тип недвижимости:\n{FF7319}1.{FFFFFF} Дома\n{FF7319}2.{FFFFFF} Бизнесы\n{FF7319}3.{FFFFFF} АЗС", !"Выбор", !"Выход");

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;
				
			switch(listitem)
			{
				case 0..19:
				{
				    pTemp[playerid][pEstateHouseLast] = 0;
				    
					new
						idh = strval(inputtext[strfind(inputtext, "№")]),
						classname[25],
						frmt_info_sel[30];
						
					pTemp[playerid][pEstateHouseInfo] = idh;
						
			    	switch(HouseInfo[idh-1][hLevel])
					{
						case 0: SetString(classname, "Дом эконом класса");
						case 1: SetString(classname, "Дом среднего класса");
						case 2: SetString(classname, "Дом элитного класса");
						case 3: SetString(classname, "Особняк");
						default: SetString(classname, "Неизвестно");
					}
						
					format(frmt_info_sel, sizeof frmt_info_sel, "%s [№%d]", classname, idh);
					ShowPlayerDialogEx(playerid, 379, DIALOG_STYLE_MSGBOX, frmt_info_sel, !"{FFFFFF}Просмотр информации о выбранном доме стоит {33AA33}30${FFFFFF}.\n\nПродолжить?", !"Да", !"Нет");
				}
				case 20:
				{
				    new
				        frmt_houses_list[700],
						classname[25],
						house_count,
						lasth = pTemp[playerid][pEstateHouseLast]-1;

					for(new i = lasth; i < OWNABLEHOUSES; i++)
					{
					    if(!GetString(HouseInfo[i][hOwner], "The State"))
							continue;

                        house_count++;
						pTemp[playerid][pEstateHouseLast] = i+1;

						if(house_count > 20)
						{
                        	format(frmt_houses_list, sizeof frmt_houses_list, "%s{ED6160}Далее >>", frmt_houses_list);
						    break;
						}

				    	switch(HouseInfo[i][hLevel])
						{
							case 0: SetString(classname, "Дом эконом класса");
							case 1: SetString(classname, "Дом среднего класса");
							case 2: SetString(classname, "Дом элитного класса");
							case 3: SetString(classname, "Особняк");
							default: SetString(classname, "Неизвестно");
						}

				    	format(frmt_houses_list, sizeof frmt_houses_list, "%s%s [№%d]\n", frmt_houses_list, classname, i+1);
					}
				    if(house_count)
				        ShowPlayerDialogEx(playerid, 378, DIALOG_STYLE_LIST, !"Выберите дом:", frmt_houses_list, !"Выбор", !"Назад");

				    else
				        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных домов");
				}
			}
			return 1;
		}
		case 379:
		{
  			if(!response)
  			{
			    new
			        frmt_houses_list[700],
					classname[25],
					house_count;

				for(new i; i < OWNABLEHOUSES; i++)
				{
				    if(!GetString(HouseInfo[i][hOwner], "The State"))
						continue;

                    house_count++;
					pTemp[playerid][pEstateHouseLast] = i+1;

					if(house_count > 20)
					{
                    	format(frmt_houses_list, sizeof frmt_houses_list, "%s{ED6160}Далее >>", frmt_houses_list);
					    break;
					}

			    	switch(HouseInfo[i][hLevel])
					{
						case 0: SetString(classname, "Дом эконом класса");
						case 1: SetString(classname, "Дом среднего класса");
						case 2: SetString(classname, "Дом элитного класса");
						case 3: SetString(classname, "Особняк");
						default: SetString(classname, "Неизвестно");
					}

			    	format(frmt_houses_list, sizeof frmt_houses_list, "%s%s [№%d]\n", frmt_houses_list, classname, i+1);
				}
			    if(house_count) ShowPlayerDialogEx(playerid, 378, DIALOG_STYLE_LIST, !"Выберите дом:", frmt_houses_list, !"Выбор", !"Назад");
			    else SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных домов");
				return 1;
  			}
  			
			if(!IsPlayerInRangeOfPoint(playerid, 50.0, -2170.0134, 640.4874, 1052.3817)) return 1;

			new id = BizEntered[playerid]-1, hid = pTemp[playerid][pEstateHouseInfo];

			if(id < 0) return 1;
		    if(!GetString(HouseInfo[hid-1][hOwner], "The State")) return 1;
		    if(PI[playerid][pMoney] < 30) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			GiveBusinessMoney(id, 30);
			if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],3);
			GiveMoney(playerid, -30, "инф. о доме");

		    new
				frmt_house_info[240],
				classname[20],
    			rent = floatround(HouseInfo[hid-1][hCost] * 0.005);

			switch(HouseInfo[hid-1][hLevel])
			{
				case 0: SetString(classname, "Эконом");
				case 1: SetString(classname, "Cредний");
				case 2: SetString(classname, "Элитный");
				case 3: SetString(classname, "Особняк");
				default: SetString(classname, "Неизвестно");
			}

		    format(frmt_house_info, sizeof frmt_house_info, "{FFFFFF}Номер: %d\n{FFFFFF}Класс: %s\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию дома\n{ED6160} > Отметить дом на GPS", hid, classname, HouseInfo[hid-1][hCost], rent);
		    ShowPlayerDialogEx(playerid, 380, DIALOG_STYLE_LIST, !"Информация о доме", frmt_house_info, !"Выбор", !"Назад");
		    return 1;
		}
		case 380:
		{
  			if(!response)
  			{
			    new
			        frmt_houses_list[700],
					classname[25],
					house_count;

				for(new i; i < OWNABLEHOUSES; i++)
				{
				    if(!GetString(HouseInfo[i][hOwner], "The State"))
						continue;

                    house_count++;
					pTemp[playerid][pEstateHouseLast] = i+1;

					if(house_count > 20)
					{
                    	format(frmt_houses_list, sizeof frmt_houses_list, "%s{ED6160}Далее >>", frmt_houses_list);
					    break;
					}

			    	switch(HouseInfo[i][hLevel])
					{
						case 0: SetString(classname, "Дом эконом класса");
						case 1: SetString(classname, "Дом среднего класса");
						case 2: SetString(classname, "Дом элитного класса");
						case 3: SetString(classname, "Особняк");
						default: SetString(classname, "Неизвестно");
					}

			    	format(frmt_houses_list, sizeof frmt_houses_list, "%s%s [№%d]\n", frmt_houses_list, classname, i+1);
				}
			    if(house_count)
			        ShowPlayerDialogEx(playerid, 378, DIALOG_STYLE_LIST, !"Выберите дом:", frmt_houses_list, !"Выбор", !"Назад");

			    else
			        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных домов");

				return 1;
  			}

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;

			new
                hid = pTemp[playerid][pEstateHouseInfo];
                
		    if(!GetString(HouseInfo[hid-1][hOwner], "The State"))
				return 1;
						
			switch(listitem)
			{
				case 0..3:
				{
				    new
						frmt_house_info[240],
						classname[20],
		    			rent = floatround(HouseInfo[hid-1][hCost] * 0.005);

					switch(HouseInfo[hid-1][hLevel])
					{
						case 0: SetString(classname, "Эконом");
						case 1: SetString(classname, "Cредний");
						case 2: SetString(classname, "Элитный");
						case 3: SetString(classname, "Особняк");
						default: SetString(classname, "Неизвестно");
					}

				    format(frmt_house_info, sizeof frmt_house_info, "{FFFFFF}Номер: %d\n{FFFFFF}Класс: %s\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию дома\n{ED6160} > Отметить дом на GPS", hid, classname, HouseInfo[hid-1][hCost], rent);
				    ShowPlayerDialogEx(playerid, 380, DIALOG_STYLE_LIST, !"Информация о доме", frmt_house_info, !"Выбор", !"Назад");
				}
				case 4:
				{
                    new
						Float:x, Float:y, Float:z;
						
				    GetPlayerPos(playerid, x, y, z);
				    if(GetPlayerInterior(playerid) == 0) SetPVarInt(playerid,"housephoto_int", 0);
				    else SetPVarInt(playerid,"housephoto_int", GetPlayerInterior(playerid));
					if(GetPlayerVirtualWorld(playerid) == 0) SetPVarInt(playerid,"housephoto_world", 0);//-14, +26, +30
					else SetPVarInt(playerid,"housephoto_world", GetPlayerVirtualWorld(playerid));

					SetPlayerVirtualWorld(playerid, hid);
					SetPlayerInterior(playerid, 0);
					f_TogglePlayerControllable(playerid, true);
					SetPlayerPos(playerid, HouseInfo[hid-1][hEnter_X], HouseInfo[hid-1][hEnter_Y], HouseInfo[hid-1][hEnter_Z]-20);
                    f_TogglePlayerControllable(playerid, false);
				    SetPlayerCameraPos(playerid, HouseInfo[hid-1][hEnter_X] + (-15.0 * floatsin(HouseInfo[hid-1][hEnter_R], degrees)), HouseInfo[hid-1][hEnter_Y] + (35.0 * floatcos(HouseInfo[hid-1][hEnter_R], degrees)), HouseInfo[hid-1][hEnter_Z]+70);
					SetPlayerCameraLookAt(playerid, HouseInfo[hid-1][hEnter_X], HouseInfo[hid-1][hEnter_Y], HouseInfo[hid-1][hEnter_Z]+2);

					for(new i = 0; i < 10; i++)
						SendClientMessage(playerid, COLOR_WHITE, !" ");
						
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Для выхода из режима просмотра нажмите ПРОБЕЛ (или быстрый бег)");
					SetPVarInt(playerid, "watch_house", 1);
				}
				case 5:
				{
                    SetPlayerCheckpointExx(playerid, HouseInfo[hid-1][hEnter_X], HouseInfo[hid-1][hEnter_Y], HouseInfo[hid-1][hEnter_Z], 3.0);
					SendClientMessage(playerid, 0xAA3333FF, !"Выбранный дом отмечен на карте");
				}
			}
			return 1;
		}
		case 381:
		{
  			if(!response) return ShowPlayerDialogEx(playerid, 377, DIALOG_STYLE_LIST, !"Агентство недвижимости", !"Выберите тип недвижимости:\n{FF7319}1.{FFFFFF} Дома\n{FF7319}2.{FFFFFF} Бизнесы\n{FF7319}3.{FFFFFF} АЗС", !"Выбор", !"Выход");

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;

			switch(listitem)
			{
				case 0..19:
				{
				    pTemp[playerid][pEstateBizLast] = 0;

					new
						idb = strval(inputtext[strfind(inputtext, "№")]),
						frmt_info_sel[30];

					pTemp[playerid][pEstateBizInfo] = idb;
					
					format(frmt_info_sel, sizeof frmt_info_sel, "%s [№%d]", BizInfo[idb-1][bName], idb);
					ShowPlayerDialogEx(playerid, 382, DIALOG_STYLE_MSGBOX, frmt_info_sel, !"{FFFFFF}Просмотр информации о выбранном бизнесе стоит {33AA33}30${FFFFFF}.\n\nПродолжить?", !"Да", !"Нет");
				}
				case 20:
				{
				    new
				        frmt_business_list[700],
						biz_count,
						lastb = pTemp[playerid][pEstateBizLast]-1;

					for(new i = lastb; i < OWNABLEBIZES; i++)
					{
					    if(!GetString(BizInfo[i][bOwner], "The State"))
							continue;

                        biz_count++;
						pTemp[playerid][pEstateBizLast] = i+1;

						if(biz_count > 20)
						{
                        	format(frmt_business_list, sizeof frmt_business_list, "%s{ED6160}Далее >>", frmt_business_list);
						    break;
						}

				    	format(frmt_business_list, sizeof frmt_business_list, "%s%s [№%d]\n", frmt_business_list, BizInfo[i][bName], i+1);
					}
				    if(biz_count)
				        ShowPlayerDialogEx(playerid, 381, DIALOG_STYLE_LIST, !"Выберите бизнес:", frmt_business_list, !"Выбор", !"Назад");

				    else
				        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных бизнесов");
				}
			}
			return 1;
		}
		case 382:
		{
  			if(!response)
  			{
  			    pTemp[playerid][pEstateBizLast] = 0;
			    new
			        frmt_business_list[700],
					biz_count;

				for(new i; i < OWNABLEBIZES; i++)
				{
				    if(!GetString(BizInfo[i][bOwner], "The State"))
						continue;

                    biz_count++;
					pTemp[playerid][pEstateBizLast] = i+1;

					if(biz_count > 20)
					{
                    	format(frmt_business_list, sizeof frmt_business_list, "%s{ED6160}Далее >>", frmt_business_list);
					    break;
					}

			    	format(frmt_business_list, sizeof frmt_business_list, "%s%s [№%d]\n", frmt_business_list, BizInfo[i][bName], i+1);
				}
			    if(biz_count)
			        ShowPlayerDialogEx(playerid, 381, DIALOG_STYLE_LIST, !"Выберите бизнес:", frmt_business_list, !"Выбор", !"Назад");

			    else
			        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных бизнесов");
			        
  			    return 1;
  			}

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;
				
			new
				id = BizEntered[playerid]-1,
				bid = pTemp[playerid][pEstateBizInfo];

			if(id < 0)
				return 1;

		    if(!GetString(BizInfo[bid-1][bOwner], "The State"))
				return 1;

		    if(PI[playerid][pMoney] < 30)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			GiveBusinessMoney(id, 30);
			if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],3);
			GiveMoney(playerid, -30, "инф. о биз");

		    new
				frmt_biz_info[240],
    			rent = floatround(BizInfo[bid-1][bCost] / 800);

		    format(frmt_biz_info, sizeof frmt_biz_info, "{FFFFFF}Номер: %d\n{FFFFFF}Название: %s\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию бизнеса\n{ED6160} > Отметить бизнес на GPS", bid, BizInfo[bid-1][bName], BizInfo[bid-1][bCost], rent);
		    return ShowPlayerDialogEx(playerid, 383, DIALOG_STYLE_LIST, !"Информация о бизнесе", frmt_biz_info, !"Выбор", !"Назад");
		}
		case 383:
		{
  			if(!response)
  			{
  			    pTemp[playerid][pEstateBizLast] = 0;
			    new
			        frmt_business_list[700],
					biz_count;

				for(new i; i < OWNABLEBIZES; i++)
				{
				    if(!GetString(BizInfo[i][bOwner], "The State"))
						continue;

                    biz_count++;
					pTemp[playerid][pEstateBizLast] = i+1;

					if(biz_count > 20)
					{
                    	format(frmt_business_list, sizeof frmt_business_list, "%s{ED6160}Далее >>", frmt_business_list);
					    break;
					}

			    	format(frmt_business_list, sizeof frmt_business_list, "%s%s [№%d]\n", frmt_business_list, BizInfo[i][bName], i+1);
				}
			    if(biz_count)
			        ShowPlayerDialogEx(playerid, 381, DIALOG_STYLE_LIST, !"Выберите бизнес:", frmt_business_list, !"Выбор", !"Назад");

			    else
			        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных бизнесов");

  			    return 1;
			}
			
			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;

			new
				bid = pTemp[playerid][pEstateBizInfo];
				
		    if(!GetString(BizInfo[bid-1][bOwner], "The State"))
				return 1;
				
			switch(listitem)
			{
				case 0..3:
				{
				    new
						frmt_biz_info[240],
		    			rent = floatround(BizInfo[bid-1][bCost] / 800);

				    format(frmt_biz_info, sizeof frmt_biz_info, "{FFFFFF}Номер: %d\n{FFFFFF}Название: %s\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию бизнеса\n{ED6160} > Отметить бизнес на GPS", bid, BizInfo[bid-1][bName], BizInfo[bid-1][bCost], rent);
				    ShowPlayerDialogEx(playerid, 383, DIALOG_STYLE_LIST, !"Информация о бизнесе", frmt_biz_info, !"Выбор", !"Назад");
				}
				case 4:
				{
                    new
						Float:x, Float:y, Float:z;
						
				    GetPlayerPos(playerid, x, y, z);
				    if(GetPlayerInterior(playerid) == 0) SetPVarInt(playerid,"businessphoto_int", 0);
				    else SetPVarInt(playerid,"businessphoto_int", GetPlayerInterior(playerid));
					if(GetPlayerVirtualWorld(playerid) == 0) SetPVarInt(playerid,"businessphoto_world", 0);//-14, +26, +30
					else SetPVarInt(playerid,"businessphoto_world", GetPlayerVirtualWorld(playerid));

					SetPlayerVirtualWorld(playerid, bid);
					SetPlayerInterior(playerid, 0);
					f_TogglePlayerControllable(playerid, true);
					SetPlayerPos(playerid, BizInfo[bid-1][bEnter_X], BizInfo[bid-1][bEnter_Y], BizInfo[bid-1][bEnter_Z]-20);
                    f_TogglePlayerControllable(playerid, false);
				    SetPlayerCameraPos(playerid, BizInfo[bid-1][bEnter_X] + (-15.0 * floatsin(BizInfo[bid-1][bEnter_R], degrees)), BizInfo[bid-1][bEnter_Y] + (35.0 * floatcos(BizInfo[bid-1][bEnter_R], degrees)), BizInfo[bid-1][bEnter_Z]+50);
					SetPlayerCameraLookAt(playerid, BizInfo[bid-1][bEnter_X], BizInfo[bid-1][bEnter_Y], BizInfo[bid-1][bEnter_Z]);

					for(new i = 0; i < 10; i++)
						SendClientMessage(playerid, COLOR_WHITE, !" ");
						
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Для выхода из режима просмотра нажмите ПРОБЕЛ (или быстрый бег)");
					SetPVarInt(playerid, "watch_business", 1);
				}
				case 5:
				{
                    SetPlayerCheckpointExx(playerid, BizInfo[bid-1][bEnter_X], BizInfo[bid-1][bEnter_Y], BizInfo[bid-1][bEnter_Z], 3.0);
					SendClientMessage(playerid, 0xAA3333FF, !"Выбранный бизнес отмечен на карте");
				}
			}
			return 1;
		}
		case 384:
		{
  			if(!response) return ShowPlayerDialogEx(playerid, 377, DIALOG_STYLE_LIST, !"Агентство недвижимости", !"Выберите тип недвижимости:\n{FF7319}1.{FFFFFF} Дома\n{FF7319}2.{FFFFFF} Бизнесы\n{FF7319}3.{FFFFFF} АЗС", !"Выбор", !"Выход");

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;

			switch(listitem)
			{
				case 0..19:
				{
				    pTemp[playerid][pEstateFillLast] = 0;

					new
						idf = strval(inputtext[strfind(inputtext, "№")]),
						frmt_info_sel[30];

					pTemp[playerid][pEstateFillInfo] = idf;

					format(frmt_info_sel, sizeof frmt_info_sel, "АЗС [№%d]", idf);
					ShowPlayerDialogEx(playerid, 385, DIALOG_STYLE_MSGBOX, frmt_info_sel, !"{FFFFFF}Просмотр информации о выбранной АЗС стоит {33AA33}30${FFFFFF}.\n\nПродолжить?", !"Да", !"Нет");
				}
				case 20:
				{
				    new
				        frmt_filling_list[700],
						filling_count,
						lastf = pTemp[playerid][pEstateFillLast]-1;

					for(new i = lastf; i < MAX_FILLING; i++)
					{
					    if(!GetString(gFillings[i][fillingOwner], "The State"))
							continue;

                        filling_count++;
						pTemp[playerid][pEstateFillLast] = i+1;

						if(filling_count > 20)
						{
                        	format(frmt_filling_list, sizeof frmt_filling_list, "%s{ED6160}Далее >>", frmt_filling_list);
						    break;
						}

				    	format(frmt_filling_list, sizeof frmt_filling_list, "%sАЗС [№%d]\n", frmt_filling_list, i+1);
					}
				    if(filling_count)
				        ShowPlayerDialogEx(playerid, 384, DIALOG_STYLE_LIST, !"Выберите АЗС:", frmt_filling_list, !"Выбор", !"Назад");

				    else
				        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных АЗС");
				}
			}
		}
		case 385:
		{
  			if(!response)
  			{
  			    pTemp[playerid][pEstateFillLast] = 0;
  			    
			    new
			        frmt_filling_list[700],
					filling_count;

				for(new i; i < MAX_FILLING; i++)
				{
				    if(!GetString(gFillings[i][fillingOwner], "The State"))
						continue;

                    filling_count++;
					pTemp[playerid][pEstateFillLast] = i+1;

					if(filling_count > 20)
					{
                    	format(frmt_filling_list, sizeof frmt_filling_list, "%s{ED6160}Далее >>", frmt_filling_list);
					    break;
					}

			    	format(frmt_filling_list, sizeof frmt_filling_list, "%sАЗС [№%d]\n", frmt_filling_list, i+1);
				}
			    if(filling_count)
			        ShowPlayerDialogEx(playerid, 384, DIALOG_STYLE_LIST, !"Выберите АЗС:", frmt_filling_list, !"Выбор", !"Назад");

			    else
			        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных АЗС");
  			
  			    return 1;
  			}
  			
			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;
				
			new
				id = BizEntered[playerid]-1,
				fid = pTemp[playerid][pEstateFillInfo];

			if(id < 0)
				return 1;

		    if(!GetString(gFillings[fid-1][fillingOwner], "The State"))
				return 1;

		    if(PI[playerid][pMoney] < 30)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			GiveBusinessMoney(id, 30);
			if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],3);
			GiveMoney(playerid, -30, "информация о азс");

		    new
				frmt_fill_info[240],
    			rent = floatround(gFillings[fid-1][fillingPrice]/200);

		    format(frmt_fill_info, sizeof frmt_fill_info, "{FFFFFF}Номер: %d\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию АЗС\n{ED6160} > Отметить АЗС на GPS", fid, gFillings[fid-1][fillingPrice], rent);
		    ShowPlayerDialogEx(playerid, 386, DIALOG_STYLE_LIST, !"Информация о АЗС", frmt_fill_info, !"Выбор", !"Назад");
		}
		case 386:
		{
  			if(!response)
  			{
  			    pTemp[playerid][pEstateFillLast] = 0;

			    new
			        frmt_filling_list[700],
					filling_count;

				for(new i; i < MAX_FILLING; i++)
				{
				    if(!GetString(gFillings[i][fillingOwner], "The State"))
						continue;

                    filling_count++;
					pTemp[playerid][pEstateFillLast] = i+1;

					if(filling_count > 20)
					{
                    	format(frmt_filling_list, sizeof frmt_filling_list, "%s{ED6160}Далее >>", frmt_filling_list);
					    break;
					}

			    	format(frmt_filling_list, sizeof frmt_filling_list, "%sАЗС [№%d]\n", frmt_filling_list, i+1);
				}
			    if(filling_count)
			        ShowPlayerDialogEx(playerid, 384, DIALOG_STYLE_LIST, !"Выберите АЗС:", frmt_filling_list, !"Выбор", !"Назад");

			    else
			        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных АЗС");

  			    return 1;
  			}

			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -2170.0134, 640.4874, 1052.3817))
				return 1;
				
			new
				fid = pTemp[playerid][pEstateFillInfo];

		    if(!GetString(gFillings[fid-1][fillingOwner], "The State"))
				return 1;
				
			switch(listitem)
			{
				case 0..2:
				{
				    new
						frmt_fill_info[240],
		    			rent = floatround(gFillings[fid-1][fillingPrice]/200);

				    format(frmt_fill_info, sizeof frmt_fill_info, "{FFFFFF}Номер: %d\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию АЗС\n{ED6160} > Отметить АЗС на GPS", fid, gFillings[fid-1][fillingPrice], rent);
				    ShowPlayerDialogEx(playerid, 386, DIALOG_STYLE_LIST, !"Информация о АЗС", frmt_fill_info, !"Выбор", !"Назад");
				}
				case 3:
				{
                    new
						Float:x, Float:y, Float:z;

				    GetPlayerPos(playerid, x, y, z);
				    if(GetPlayerInterior(playerid) == 0) SetPVarInt(playerid,"fillingphoto_int", 0);
				    else SetPVarInt(playerid,"fillingphoto_int", GetPlayerInterior(playerid));
					if(GetPlayerVirtualWorld(playerid) == 0) SetPVarInt(playerid,"fillingphoto_world", 0);//-14, +26, +30
					else SetPVarInt(playerid,"fillingphoto_world", GetPlayerVirtualWorld(playerid));

					SetPlayerVirtualWorld(playerid, fid);
					SetPlayerInterior(playerid, 0);
					f_TogglePlayerControllable(playerid, true);
					SetPlayerPos(playerid, gFillingBuy[fid-1][0], gFillingBuy[fid-1][1], gFillingBuy[fid-1][2]-30);
                    f_TogglePlayerControllable(playerid, false);
				    SetPlayerCameraPos(playerid, gFillingBuy[fid-1][0] + 15.0, gFillingBuy[fid-1][1] + 35.0, gFillingBuy[fid-1][2]+50);
					SetPlayerCameraLookAt(playerid, gFillingBuy[fid-1][0], gFillingBuy[fid-1][1], gFillingBuy[fid-1][2]);

					for(new i = 0; i < 10; i++)
						SendClientMessage(playerid, COLOR_WHITE, !" ");

					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Для выхода из режима просмотра нажмите ПРОБЕЛ (или быстрый бег)");
					SetPVarInt(playerid, "watch_filling", 1);
				}
				case 4:
				{
                    SetPlayerCheckpointExx(playerid, gFillingBuy[fid-1][0], gFillingBuy[fid-1][1], gFillingBuy[fid-1][2], 3.0);
					SendClientMessage(playerid, 0xAA3333FF, !"Выбранная АЗС отмечен на карте");
				}
			}
		
		}
		case 721:
		{
  			if(!response)
  				return 1;

			new
				id = BizEntered[playerid]-1;

			if(id < 0)
				return 1;

			if(PI[playerid][pGunLic] != YES_LICENSE)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет лицензии на оружие");
		        
			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pMoney] < 50)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[id][bProducts] < 15)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");
					
					BizInfo[id][bProducts] -= 15;
					GiveBusinessMoney(id, 50);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],5);

					SendClientMessage(playerid, COLOR_WHITE, "{7AC71F}[Успешно] {FFFFFF}Вы купили {FFD700}Кастет");
					_GiveGun(playerid, 1, 1);
					UpdateBiz(id,1);
					ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				}
				case 1:
				{
					if(PI[playerid][pMoney] < 100)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[id][bProducts] < 25)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");

					BizInfo[id][bProducts] -= 25;
					GiveBusinessMoney(id, 100);
					if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],10);
					GiveMoney(playerid, -100, "покупка бейсбольной биты");
					SendClientMessage(playerid, COLOR_WHITE, "{7AC71F}[Успешно] {FFFFFF}Вы купили {FFD700}Бейсбольную биту");
					_GiveGun(playerid, 5, 1);
					UpdateBiz(id,1);
					ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				}
				case 2: ShowPlayerDialogEx(playerid, 728, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Дробовика\nЦена одного патрона - {33AA00}70$", !"Купить", !"Назад");
				case 3: ShowPlayerDialogEx(playerid, 723, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Desert Eagle\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
				case 4: ShowPlayerDialogEx(playerid, 724, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Полуавтомата MP5\nЦена одного патрона - {33AA00}30$", !"Купить", !"Назад");
				case 5: ShowPlayerDialogEx(playerid, 725, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Автомата AK47\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
				case 6: ShowPlayerDialogEx(playerid, 726, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Винтовки\nЦена одного патрона - {33AA00}70$", !"Купить", !"Назад");
				case 7: ShowPlayerDialogEx(playerid, 727, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Автомата M4\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
			}
		}
		case 728:
		{
		    if(response)
		    {
				new
					id = BizEntered[playerid]-1;
				
				if(!strlen(inputtext))
					return ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");

				new
					ammo = strval(inputtext),
					price = strval(inputtext) * 70;
					
				if(ammo < 1 || ammo > 100)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Укажите значение патронов от 1 до 100");
                    ShowPlayerDialogEx(playerid, 728, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Дробовика\nЦена одного патрона - {33AA00}70$", !"Купить", !"Назад");
					return 1;
				}
				if(PI[playerid][pMoney] < price)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					ShowPlayerDialogEx(playerid, 728, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Дробовика\nЦена одного патрона - {33AA00}70$", !"Купить", !"Назад");
					return 1;
				}
				if(BizInfo[id][bProducts] < 50)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");


				BizInfo[id][bProducts] -= 50;
				GiveBusinessMoney(id, price);

                if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
				new frmt_ammob[144];
				format(frmt_ammob, sizeof(frmt_ammob), "{7AC71F}[Успешно] {FFFFFF}Вы купили дробовик с {FFD700}%d{FFFFFF} патронами за {33AA00}%d$", ammo, price);
				SendClientMessage(playerid, COLOR_WHITE, frmt_ammob);



                UpdateBiz(id,1);
				GiveMoney(playerid, -price, "покупка дробивика");
				_GiveGun(playerid, 25, ammo);
				ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
		    }
		    else
		    {
		        ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
			}
		}
		case 723:
		{
		    if(response)
		    {
				new
					id = BizEntered[playerid]-1;

				if(!strlen(inputtext))
					return ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");

				new
					ammo = strval(inputtext),
					price = strval(inputtext) * 60;

				if(ammo < 1 || ammo > 100)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Укажите значение патронов от 1 до 100");
                    ShowPlayerDialogEx(playerid, 723, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Desert Eagle\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
					return 1;
				}
				if(PI[playerid][pMoney] < price)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					ShowPlayerDialogEx(playerid, 723, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Desert Eagle\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
					return 1;
				}
				if(BizInfo[id][bProducts] < 50)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");

				BizInfo[id][bProducts] -= 50;
                GiveBusinessMoney(id, price);
                if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
				new frmt_ammob[144];
				format(frmt_ammob, sizeof(frmt_ammob), "{7AC71F}[Успешно] {FFFFFF}Вы купили Desert Eagle с {FFD700}%d{FFFFFF} патронами за {33AA00}%d$", ammo, price);
				SendClientMessage(playerid, COLOR_WHITE, frmt_ammob);
                
                UpdateBiz(id,1);
				GiveMoney(playerid, -price, "покупка Desert Eagle");
				_GiveGun(playerid, 24, ammo);
				ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
		    }
		    else
		    {
		        ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
			}
		}
		case 724:
		{
		    if(response)
		    {
				new
					id = BizEntered[playerid]-1;

				if(!strlen(inputtext))
					return ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");

				new
					ammo = strval(inputtext),
					price = strval(inputtext) * 30;

				if(ammo < 1 || ammo > 200)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Укажите значение патронов от 1 до 200");
                    ShowPlayerDialogEx(playerid, 724, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Полуавтомата MP5\nЦена одного патрона - {33AA00}30$", !"Купить", !"Назад");
					return 1;
				}
				if(PI[playerid][pMoney] < price)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					ShowPlayerDialogEx(playerid, 724, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Полуавтомата MP5\nЦена одного патрона - {33AA00}30$", !"Купить", !"Назад");
					return 1;
				}
				if(BizInfo[id][bProducts] < 50)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");

				BizInfo[id][bProducts] -= 50;
                GiveBusinessMoney(id, price);
				if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
				new frmt_ammob[144];
				format(frmt_ammob, sizeof(frmt_ammob), "{7AC71F}[Успешно] {FFFFFF}Вы купили полуавтомат МР5 с {FFD700}%d{FFFFFF} патронами за {33AA00}%d$", ammo, price);
				SendClientMessage(playerid, COLOR_WHITE, frmt_ammob);
				
                UpdateBiz(id,1);
				GiveMoney(playerid, -price, "покупка полуавтомата МР5");
				_GiveGun(playerid, 29, ammo);
				ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
		    }
		    else
		    {
		        ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
			}
		}
		case 725:
		{
		    if(response)
		    {
				new
					id = BizEntered[playerid]-1;

				if(!strlen(inputtext))
					return ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");

				new
					ammo = strval(inputtext),
					price = strval(inputtext) * 60;

				if(ammo < 1 || ammo > 100)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Укажите значение патронов от 1 до 100");
                    ShowPlayerDialogEx(playerid, 725, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Автомата AK47\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
					return 1;
				}
				if(PI[playerid][pMoney] < price)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					ShowPlayerDialogEx(playerid, 725, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Автомата AK47\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
					return 1;
				}
				if(BizInfo[id][bProducts] < 50)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");

				BizInfo[id][bProducts] -= 50;
                GiveBusinessMoney(id, price);
                if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
				new frmt_ammob[144];
				format(frmt_ammob, sizeof(frmt_ammob), "{7AC71F}[Успешно] {FFFFFF}Вы купили автомат АК47 с {FFD700}%d{FFFFFF} патронами за {33AA00}%d$", ammo, price);
				SendClientMessage(playerid, COLOR_WHITE, frmt_ammob);

                
                UpdateBiz(id,1);
				GiveMoney(playerid, -price, "покупка автомата АК47");
				_GiveGun(playerid, 30, ammo);
				ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
		    }
		    else
		    {
		        ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
			}
		}
		case 726:
		{
		    if(response)
		    {
				new
					id = BizEntered[playerid]-1;

				if(!strlen(inputtext))
					return ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");

				new
					ammo = strval(inputtext),
					price = strval(inputtext) * 70;

				if(ammo < 1 || ammo > 100)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Укажите значение патронов от 1 до 100");
                    ShowPlayerDialogEx(playerid, 726, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Винтовки\nЦена одного патрона - {33AA00}70$", !"Купить", !"Назад");
					return 1;
				}
				if(PI[playerid][pMoney] < price)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					ShowPlayerDialogEx(playerid, 726, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Винтовки\nЦена одного патрона - {33AA00}70$", !"Купить", !"Назад");
					return 1;
				}
				if(BizInfo[id][bProducts] < 50)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");

				BizInfo[id][bProducts] -= 50;
                GiveBusinessMoney(id, price);
				if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
				new frmt_ammob[144];
				format(frmt_ammob, sizeof(frmt_ammob), "{7AC71F}[Успешно] {FFFFFF}Вы купили винтовку с {FFD700}%d{FFFFFF} патронами за {33AA00}%d$", ammo, price);
				SendClientMessage(playerid, COLOR_WHITE, frmt_ammob);
                
                UpdateBiz(id,1);
				GiveMoney(playerid, -price, "покупка винтовки");
				_GiveGun(playerid, 33, ammo);
				ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
		    }
		    else
		    {
		        ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
			}
		}
		case 727:
		{
		    if(response)
		    {
				new
					id = BizEntered[playerid]-1;

				if(!strlen(inputtext))
					return ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");

				new
					ammo = strval(inputtext),
					price = strval(inputtext) * 60;

				if(ammo < 1 || ammo > 100)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Укажите значение патронов от 1 до 100");
                    ShowPlayerDialogEx(playerid, 727, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Автомата M4\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
					return 1;
				}
				if(PI[playerid][pMoney] < price)
				{
				    SendClientMessage(playerid, COLOR_WHITE, "У Вас недостаточно денег");
					ShowPlayerDialogEx(playerid, 727, DIALOG_STYLE_INPUT, !"Покупка оружия", !"{FFFFFF}Укажите число патронов для Автомата M4\nЦена одного патрона - {33AA00}60$", !"Купить", !"Назад");
					return 1;
				}
				if(BizInfo[id][bProducts] < 50)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В аммунации недостаточно товара");

				BizInfo[id][bProducts] -= 50;
					
                GiveBusinessMoney(id, price);
                if(BizInfo[id][bKrasher]) GiveFracBank(BizInfo[id][bKrasher],price/100*10);
				new frmt_ammob[144];
				format(frmt_ammob, sizeof(frmt_ammob), "{7AC71F}[Успешно] {FFFFFF}Вы купили автомат M4 с {FFD700}%d{FFFFFF} патронами за {33AA00}%d$", ammo, price);
				SendClientMessage(playerid, COLOR_WHITE, frmt_ammob);
                
                UpdateBiz(id,1);
				GiveMoney(playerid, -price, "покупка M4");
				_GiveGun(playerid, 31, ammo);
				ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
		    }
		    else
		    {
		        ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				return 1;
			}
		}

	    case 789:
	    {
	        if(!response)
	            return callcmd::menu(playerid, "");
	            
            switch(listitem)
			{
                case 0:
	        	{
     				if(!strlen(PI[playerid][pCode]))
		 				ShowPlayerDialogEx(playerid, 770, DIALOG_STYLE_LIST, !"Код безопасности", !"{FF7319}1.{FFFFFF} Установить код безопасности\n{FF7319}2.{FFFFFF} Удалить код безопасности", !"Выбрать", !"Назад");

					else
		 				ShowPlayerDialogEx(playerid, 770, DIALOG_STYLE_LIST, !"Код безопасности", !"{FF7319}1.{FFFFFF} Изменить код безопасности\n{FF7319}2.{FFFFFF} Удалить код безопасности", !"Выбрать", !"Назад");

 				}
				case 1:
				    ShowPlayerDialogEx(playerid, 788, DIALOG_STYLE_PASSWORD, !"Смена пароля", !"{FFFFFF}Введите текущий пароль", !"Далее", !"Отмена");
				    
				case 2:
				{

				    
				    new
						query_check_google[80],
						googleauth[18];
						
					format(query_check_google, sizeof query_check_google, "SELECT `GoogleAuth` FROM `accounts` WHERE `ID` = '%d'", PI[playerid][pID]);
					new Cache:result = mysql_query(mysql, query_check_google);

					if(cache_get_row_count(mysql))
					{
						cache_get_row(0, 0, googleauth, mysql);
						
						if(strlen(googleauth) && !PI[playerid][pGoogleAuthStatus])
						{
							SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы активировали защиту Google Authenticatior");
							SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Никогда никому не сообщайте одноразовый пароль из приложения");
							SetString(PI[playerid][pGoogleAuth], googleauth);
					        PI[playerid][pGoogleAuthStatus] = 1;
							UpdatePlayerData(playerid, "GoogleAuthStatus", PI[playerid][pGoogleAuthStatus]);
						}
					    else if(strlen(googleauth) && PI[playerid][pGoogleAuthStatus])
					        ShowPlayerDialogEx(playerid, 749, DIALOG_STYLE_INPUT, !"Отключение защиты", !"Google Authenticatior\n{FFFFFF}Введите одноразовый пароль из приложения Google Authenticatior для отключения защиты:", !"Отключить", !"Отмена");
				    
						else
					    	SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала настройте защиту в личном кабинете");
				    }
					else
					    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");
					    
					cache_delete(result, mysql);
				}
				case 3:
				{
				    new
						query_check_google[80],
						googleauth[18];

					format(query_check_google, sizeof query_check_google, "SELECT `GoogleAuth` FROM `accounts` WHERE `ID` = '%d'", PI[playerid][pID]);
					new Cache:result = mysql_query(mysql, query_check_google);
					

					if(cache_get_row_count(mysql))
					{
						cache_get_row(0, 0, googleauth, mysql);

				    	if(strlen(googleauth) && PI[playerid][pGoogleAuthStatus])
					    {
							if(0 == PI[playerid][pGoogleAuthCheck])
							{
						        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы активировали запрос кода Google Authenticatior при каждом входе");
						        PI[playerid][pGoogleAuthCheck] = 1;
								UpdatePlayerData(playerid, "GoogleAuthCheck", PI[playerid][pGoogleAuthCheck]);
							}
							else
							{
						        ShowPlayerDialogEx(playerid, 750, DIALOG_STYLE_INPUT, !"Отключение запроса кода", !"Google Authenticatior\n{FFFFFF}Введите одноразовый пароль из приложения Google Authenticatior для отключения защиты:", !"Отключить", !"Отмена");
						        return 1;
							}
					    }
						else
					    	SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала активируйте защиту Google Authenticatior");
					}
                    cache_delete(result, mysql);
				}
			}
	    }
	    case 749:
	    {
		    if(!response)
				return 1;
				
			if(!strlen(inputtext) || !isNumeric(inputtext) || strlen(inputtext) != 6)
			{
				ShowPlayerDialogEx(playerid, 749, DIALOG_STYLE_INPUT, !"Отключение защиты", !"Google Authenticatior\n{FFFFFF}Введите одноразовый пароль из приложения Google Authenticatior для отключения защиты:", !"Отключить", !"Отмена");
				return 1;
	        }
	        if(PI[playerid][pGoogleAuth] == '\0')
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

			if(!PI[playerid][pGoogleAuthStatus])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка");
				
	        new
				getcode = GoogleAuthenticatorCode(PI[playerid][pGoogleAuth], gettime());
				
			if(strval(inputtext) != getcode)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверный одноразовый пароль из приложения Google Authenticatior");
			    J_Kick(playerid);
			    return 1;
			}
	        PI[playerid][pGoogleAuthStatus] = 0;
			UpdatePlayerData(playerid, "GoogleAuthStatus", PI[playerid][pGoogleAuthStatus]);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы отключили защиту Google Authenticator");
	    }
	    case 750:
	    {
		    if(!response)
				return 1;

			if(!strlen(inputtext) || !isNumeric(inputtext) || strlen(inputtext) != 6)
			{
		        ShowPlayerDialogEx(playerid, 750, DIALOG_STYLE_INPUT, !"Отключение запроса кода", !"Google Authenticatior\n{FFFFFF}Введите одноразовый пароль из приложения Google Authenticatior для отключения защиты:", !"Отключить", !"Отмена");
		        return 1;
	        }
	        if(PI[playerid][pGoogleAuth] == '\0')
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

			if(!PI[playerid][pGoogleAuthStatus] || !PI[playerid][pGoogleAuthCheck])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка");

	        new
				getcode = GoogleAuthenticatorCode(PI[playerid][pGoogleAuth], gettime());

			if(strval(inputtext) != getcode)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверный одноразовый пароль из приложения Google Authenticatior");
			    J_Kick(playerid);
			    return 1;
			}
	        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы отключили запрос кода Google Authenticatior при каждом входе");
	        PI[playerid][pGoogleAuthCheck] = 0;
			UpdatePlayerData(playerid, "GoogleAuthCheck", PI[playerid][pGoogleAuthCheck]);
		}
		case 770:
		{
		    if(!response)
				return 1;
		
		    if(listitem == 0)
			{
			    if(!strlen(PI[playerid][pCode]))
		        	ShowPlayerDialogEx(playerid, 771, DIALOG_STYLE_INPUT, !"Код безопасности", !"{FFFFFF}Введите новый код безопасности", !"Далее", !"Отмена");

				else
				    ShowPlayerDialogEx(playerid, 769, DIALOG_STYLE_INPUT, !"Код безопасности", !"{FFFFFF}Введите текущий код безопасности", !"Далее", !"Отмена");
			}
			else if(listitem == 1)
			{
			    if(!strlen(PI[playerid][pCode]))
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Для начала установите код безопасности");
					
				new
				    query_delete_code[65];

				format(query_delete_code, sizeof query_delete_code, "UPDATE `accounts` SET `Code` = '' WHERE `ID` = '%d'", PI[playerid][pID]);
				mysql_tquery(mysql, query_delete_code);
				
				strdel(PI[playerid][pCode], 0, 25);
				SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы удалили текущий код безопасности");

			}
		}
		case 769:
		{
		    if(!response)
				return 1;

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

		    if(!strlen(PI[playerid][pCode]))
				return 1;

			if(strlen(inputtext) < 4 || strlen(inputtext) > 22)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Длина кода безопасности должна быть от 4 до 22 символов");

			if(!CheckPassword(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			if(!strcmp(inputtext, PI[playerid][pCode], false) && strlen(inputtext))
			{
				new
				    query_delete_code[65];

				format(query_delete_code, sizeof query_delete_code, "UPDATE `accounts` SET `Code` = '' WHERE `ID` = '%d'", PI[playerid][pID]);
				mysql_tquery(mysql, query_delete_code);

				strdel(PI[playerid][pCode], 0, 25);
				ShowPlayerDialogEx(playerid, 771, DIALOG_STYLE_INPUT, !"Код безопасности", !"{FFFFFF}Введите новый код безопасности", !"Далее", !"Отмена");
			}
			else
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный код безопасности");
		}
		case 771:
		{
		    if(!response)
				return 1;
		
			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

		    if(strlen(PI[playerid][pCode]))
				return 1;

			if(strlen(inputtext) < 4 || strlen(inputtext) > 22)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Длина кода безопасности должна быть от 4 до 22 символов");

			if(!CheckPassword(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            SetString(pTemp[playerid][pChangeCode], inputtext);
            ShowPlayerDialogEx(playerid, 772, DIALOG_STYLE_INPUT, !"Код безопасности", !"{FFFFFF}Повторите новый код безопасности", !"Далее", !"Отмена");
		}
		case 772:
		{
		    if(!response)
				return 1;

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

		    if(strlen(PI[playerid][pCode]))
				return 1;

			if(strlen(inputtext) < 4 || strlen(inputtext) > 22)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Длина кода безопасности должна быть от 4 до 22 символов");

			if(!CheckPassword(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			new
			    oldcode[25],
				code[25];
			    
			SetString(oldcode, pTemp[playerid][pChangeCode]);
			
			mysql_escape_string(inputtext, code);
			if(!strcmp(inputtext, oldcode, false) && strlen(inputtext))
			{
				new
				    query_delete_code[110];

				format(query_delete_code, sizeof query_delete_code, "UPDATE `accounts` SET `Code` = '%s' WHERE `ID` = '%d'", code, PI[playerid][pID]);
				mysql_tquery(mysql, query_delete_code);
				
				SetString(PI[playerid][pCode], code);
				SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы установили код безопасности. Обязательно запишите и запомните его");
			}
			else
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Введенные Вами коды не совпадают");
		}
	    case 788:
		{
		    if(!response)
				return 1;
				
  			if(!strcmp(inputtext, PI[playerid][pPassword], false) && strlen(inputtext))
			  	ShowPlayerDialogEx(playerid, 786, DIALOG_STYLE_PASSWORD, !"Смена пароля", !"{FFFFFF}Введите ваш новый пароль", !"Далее", !"Отмена");

			else
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Пароль введен неверно");

		}
		case 786:
		{
			if(!response)
				return 1;
				
			if(!CheckPassword(inputtext))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
				return ShowPlayerDialogEx(playerid, 786, DIALOG_STYLE_PASSWORD, !"Смена пароля", !"{FFFFFF}Введите ваш новый пароль", !"Далее", !"Отмена");
			}
				
			if(strlen(inputtext) < 6 || strlen(inputtext) > 22)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Длина пароля должна быть от 6-и до 22-х символов");
				return ShowPlayerDialogEx(playerid, 786, DIALOG_STYLE_PASSWORD, !"Смена пароля", !"{FFFFFF}Введите ваш новый пароль", !"Далее", !"Отмена");
			}

			SetString(pTemp[playerid][pChangePassword], inputtext);
			ShowPlayerDialogEx(playerid, 387, DIALOG_STYLE_PASSWORD, !"Смена пароля", !"{FFFFFF}Повторите ваш пароль:", !"Далее", !"Отмена");

		}
		case 387:
		{
			if(!response)
				return 1;

			new
			    oldpass[25],
				pass[25];
			    
			SetString(oldpass, pTemp[playerid][pChangePassword]);

            mysql_escape_string(inputtext, pass);
			if(!strcmp(inputtext, oldpass, false) && strlen(inputtext))
			{
				new
					query_password_change[54 + 25 + 9];
					
				format(query_password_change, sizeof query_password_change, "UPDATE `accounts` SET `Password` = '%s' WHERE `ID` = '%d'", pass, PI[playerid][pID]);
    			mysql_tquery(mysql, query_password_change);
				SetString(PI[playerid][pPassword], pass);
				SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Пароль изменен. Пожалуйста запишите его.");
			}
			else
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Введенные Вами пароли не совпадают");

		}
		case 878:
		{
			if(!response)
				return 1;

		    new
				query_get_name[80],
				name[MAX_PLAYER_NAME],
				query_delete[75],
				frmt_delete_message[90],
				family,
				promo;

			format(query_get_name, sizeof query_get_name, "SELECT `NickName`, `Family`, `Promo` FROM `accounts` WHERE `ID` = '%d'", pTemp[playerid][pDelName]);
			new Cache:result = mysql_query(mysql, query_get_name);

			if(cache_get_row_count(mysql))
			{
			    cache_get_row(0, 0, name, mysql, MAX_PLAYER_NAME);
				family = cache_get_row_int(0, 1);
				promo = cache_get_row_int(0, 2);
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный никнейм");
				return cache_delete(result, mysql);
			}
			cache_delete(result, mysql);


      		if(GetPlayerID(name) != INVALID_PLAYER_ID)
            {
                SendClientMessage(GetPlayerID(name), COLOR_RED,"Ваш аккаунт был удалён за нарушение правил сервера");
                Kick(GetPlayerID(name));
            }
		    for(new bid; bid < MAX_BIZ; bid++)
		    {
	            if(GetString(BizInfo[bid][bOwner], name))
	            {
					SetString(BizInfo[bid][bOwner], "The State");
					BizInfo[bid][bLock] = 1;
					
					new
      					query_sell_business[80];
      					
					format(query_sell_business,sizeof query_sell_business,"UPDATE `business` SET `Owner` = 'The State', `Lock` = '1' WHERE `ID` = '%d'", bid+1);
					mysql_tquery(mysql, query_sell_business);
					UpdateBiz(bid,1);
	            }
			}
		    for(new fid; fid < MAX_FILLING; fid++)
		    {
	            if(GetString(gFillings[fid][fillingOwner], name))
	            {
					SetString(gFillings[fid][fillingOwner], "The State");
					gFillings[fid][fillingWorking] = false;

					UpdateFillingText(fid);
					SaveFilling(fid);
	            }
			}
		    for(new hid; hid < OWNABLEHOUSES; hid++)
		    {
	            if(GetString(HouseInfo[hid][hOwner], name))
	            {
					new
						query_house[136 + 5];

					format(query_house, sizeof query_house, "UPDATE `houses` SET `Owner` = 'The State', `Days` = '0', `Improve` = '0|0|0|0' WHERE `ID` = '%d'", HouseInfo[hid][hID]);
					mysql_tquery(mysql, query_house);

					if(IsValidDynamic3DTextLabel(HintStoreText[hid]))
					    DestroyDynamic3DTextLabel(HintStoreText[hid]);

					if(IsValidDynamic3DTextLabel(HintSafeText[hid]))
					    DestroyDynamic3DTextLabel(HintSafeText[hid]);

					if(IsValidDynamicObject(HintStoreObject[hid]))
					    DestroyDynamicObject(HintStoreObject[hid]);

					if(IsValidDynamicObject(HintSafeObject[hid]))
					    DestroyDynamicObject(HintSafeObject[hid]);

					SetString(HouseInfo[hid][hOwner], "The State");


		     		HouseInfo[hid][hSafeCode] = 0;
		     		HouseInfo[hid][hSkin][1] = 0;
		     		HouseInfo[hid][hSkin][2] = 0;
		     		HouseInfo[hid][hSkin][3] = 0;
		     		HouseInfo[hid][hSkin][0] = 0;
		     		HouseInfo[hid][hMoney] = 0;

		     		UpdateHouseDress(hid);
		     		UpdateHouseGun(hid);

		     		for(new i;i<8;i++)
		     		{
		     		    HouseInfo[hid][hGun][i] = 0;
						DestroyDynamicObject(HouseGunObject[hid][i]);
						HouseGunObject[hid][i] = 0;
					}

				    if(IsValidDynamicObject(HintDressObject[hid][0]))
				    	DestroyDynamicObject(HintDressObject[hid][0]);
				    if(IsValidDynamicObject(HintDressObject[hid][1]))
				    	DestroyDynamicObject(HintDressObject[hid][1]);
				    if(IsValidDynamicObject(HintDressObject[hid][2]))
				    	DestroyDynamicObject(HintDressObject[hid][2]);

					for(new i; i < 4; i++)
					{
					    if(HouseInfo[hid][hImprove][i])
							HouseInfo[hid][hImprove][i] = 0;
					}

					UpdateHouse(hid);
				}
			}
			new
				query_family_save[170];

			if(promo)
			{
			    gPromo[promo-1][pcUsed]--;
				format(query_family_save, sizeof query_family_save, "UPDATE `promo` SET `pcUsed` = `pcUsed`-1 WHERE `ID` = '%d'", promo);
	            mysql_tquery(mysql, query_family_save);
			}
			if(family)
			{
			    gFamily[family-1][fMembers]--;
				format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `Members` = `Members`-1 WHERE `ID` = '%d'", family);
	            mysql_tquery(mysql, query_family_save);
			}
			for(new famid; famid < family_count; famid++)
			{
	            if(GetString(gFamily[famid][fOwner], name))
	            {
					SetString(gFamily[famid][fOwner], "The State");
					format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `Owner` = 'The State' WHERE `ID` = '%d'", famid+1);
		            mysql_tquery(mysql, query_family_save);
			    }
	            if(GetString(gFamily[famid][fSubOwner], name))
	            {
					SetString(gFamily[famid][fSubOwner], "The State");
					format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `SubOwner` = 'The State' WHERE `ID` = '%d'", famid+1);
		            mysql_tquery(mysql, query_family_save);
			    }
			}
            format(query_delete, sizeof query_delete, "DELETE FROM `accounts` WHERE `NickName` = '%s'", name);
            mysql_tquery(mysql, query_delete);

            format(frmt_delete_message, sizeof frmt_delete_message, "Администратор %s удалил аккаунт %s", PN(playerid), name);
            SendAdminsMessage(0xFB4D00FF, frmt_delete_message);
            
		}
	 	case 154:
	 	{
	 	    if(response)
	 	    {
	 	        switch(listitem)
				{
					case 0:
				    {
				        if(PI[playerid][pShowName] == 0)
				        {
							PI[playerid][pShowName] = 1;
						 	foreach(new i : Player) ShowPlayerNameTagForPlayer(playerid, i, PI[playerid][pShowName]);
				        }
				        else if(PI[playerid][pShowName] == 1)
				        {
                            PI[playerid][pShowName] = 0;
						 	foreach(new i : Player) ShowPlayerNameTagForPlayer(playerid, i, PI[playerid][pShowName]);
				        }
				        ShowUpdateSettings(playerid);
				    }
					case 1:
					{
					    if(PI[playerid][pShowCase]>0) PI[playerid][pShowCase]=0;
					    else
					    {
					        PI[playerid][pShowCase]=1;
					        if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) RemovePlayerAttachedObject(playerid,9);

					    }
					    ShowUpdateSettings(playerid);
					}
				}
	 	    }
	 	}

		case 171:
		{
		    if(response)
		    {


		    }
		}

		case 172:
		{
		    if(response)
		    {
		    }
		}

		case 882:
		{
		    if(!response)
				return 1;
				
			if(!IsACop(playerid))
				return 1;

			if(PI[playerid][pRank] < 3)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			if(listitem == 40)
			{
				new
				    fmrt_wanted_list[1900],
				    color[10],
				    new_page,
					number_wanted,
					total;

				strcat(fmrt_wanted_list, "{FFFFFF}№. Никнейм игрока\t{FFFFFF}Уровень розыска\n");

			 	for(new i = pTemp[playerid][pLastWanted], j = GetPlayerPoolSize(); i <= j; i++)
				{
					if(!PI[i][pID] || !PI[i][pWanted])
						continue;
						
				    if(number_wanted > 39 && total > 40)
					{
					    pTemp[playerid][pLastWanted] = i;
					    new_page = true;
						format(fmrt_wanted_list, sizeof fmrt_wanted_list, "%s{FFFFFF}Следующая страница", fmrt_wanted_list);
					    break;
					}

					if(PI[i][pWanted] > 6)
					    strcat(color, "{FF0000}");

					format(fmrt_wanted_list, sizeof fmrt_wanted_list, "%s{FFFFFF}%d. %s\t%s%d\n", fmrt_wanted_list, temp_wanted_count[playerid]+1, PN(i), color, PI[i][pWanted]);

					temp_wanted_count[playerid]++;
					number_wanted++;
				}
				if(number_wanted == 0)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Преступников не найдено");

				if(new_page)
					ShowPlayerDialogEx(playerid, 882, DIALOG_STYLE_TABLIST_HEADERS, !"Список преступников", fmrt_wanted_list, !"Далее", !"Закрыть");

				else
					ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Список преступников", fmrt_wanted_list, !"Закрыть", !"");

			}
		}
		case 949:
		{
		    if(!response)
				return 1;

			if(!IsACop(playerid))
				return 1;

			if(PI[playerid][pRank] < 4)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
			    
			if(temp_take_receiver[playerid] == INVALID_PLAYER_ID)
				return 1;
				
			new
			    target = temp_take_receiver[playerid]-1,
				frmt_take_message[135];
			    
			if(listitem == 0)
			{
				if(PI[target][pDrugs] < 0)
			    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет наркотиков");

				format(frmt_take_message, sizeof frmt_take_message, "%s %s конфисковал у Вас наркотики", gFractionRankName[PI[playerid][pFraction]-1][PI[playerid][pRank]-1], PN(playerid));
				SendClientMessage(target, 0xFF5030AA, frmt_take_message);

				format(frmt_take_message, sizeof frmt_take_message, "Вы конфисковали наркотики у {FFFFFF}%s", PN(target));
				SendClientMessage(playerid, 0x269BD8FF, frmt_take_message);
				
                PI[target][pDrugs] = 0;
                UpdatePlayerData(target, "Drugs", PI[target][pDrugs]);
                
	       		new
				   	frmt_action[120];

				format(frmt_action, sizeof frmt_action, "%s конфисковал(а) наркотики у %s", PN(playerid), PN(target));
				ProxDetector(25, playerid, frmt_action, COLOR_ME);
			}
			else if(listitem == 1)
			{
				if(PI[target][pPackets] < 0)
			    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет ед. оружия");
			    	
				format(frmt_take_message, sizeof frmt_take_message, "%s %s конфисковал у Вас ед. оружия", gFractionRankName[PI[playerid][pFraction]-1][PI[playerid][pRank]-1], PN(playerid));
				SendClientMessage(target, 0xFF5030AA, frmt_take_message);

				format(frmt_take_message, sizeof frmt_take_message, "Вы конфисковали ед. оружия у {FFFFFF}%s", PN(target));
				SendClientMessage(playerid, 0x269BD8FF, frmt_take_message);

                PI[target][pPackets] = 0;
                UpdatePlayerData(target, "Packets", PI[target][pPackets]);

	       		new
				   	frmt_action[120];

				format(frmt_action, sizeof frmt_action, "%s конфисковал(а) ед. оружия у %s", PN(playerid), PN(target));
				ProxDetector(25, playerid, frmt_action, COLOR_ME);
			}
			else if(listitem == 2)
			{
				if(PI[target][pMats] < 0)
			    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет патронов");

				format(frmt_take_message, sizeof frmt_take_message, "%s %s конфисковал у Вас патроны", gFractionRankName[PI[playerid][pFraction]-1][PI[playerid][pRank]-1], PN(playerid));
				SendClientMessage(target, 0xFF5030AA, frmt_take_message);

				format(frmt_take_message, sizeof frmt_take_message, "Вы конфисковали патроны у {FFFFFF}%s", PN(target));
				SendClientMessage(playerid, 0x269BD8FF, frmt_take_message);

                PI[target][pMats] = 0;
                UpdatePlayerData(target, "Mats", PI[target][pMats]);

	       		new
				   	frmt_action[120];

				format(frmt_action, sizeof frmt_action, "%s конфисковал(а) патроны у %s", PN(playerid), PN(target));
				ProxDetector(25, playerid, frmt_action, COLOR_ME);

			}
		}
  		case 950:
  		{
  			if(!response)
				return 1;

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 5)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			if(!strlen(inputtext) || strlen(inputtext) < 4 || strlen(inputtext) > 20)
				return ShowPlayerDialogEx(playerid, 950, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите название листовки:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			SetString(pTemp[playerid][pFlyerName], inputtext);
            pTemp[playerid][pFlyerCount] = 0;
            strdel(pTemp[playerid][pFlyerText], 0, 128);
            
            new
				flyer_count[50],
				flyer_text[128];

			if(!strlen(pTemp[playerid][pFlyerText]))
			    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");
			    
            if(!pTemp[playerid][pFlyerCount])
                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");

            //SetString(pTemp[playerid][pFlyerText], "-");

			new
			    frmt_flyer_list[200];

			format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);
			ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");
		}
		case 951:
		{
		    if(!response)
		    {
				strdel(pTemp[playerid][pFlyerName], 0, 24);
				strdel(pTemp[playerid][pFlyerText], 0, 128);
				pTemp[playerid][pFlyerCount] = 0;
				return 1;
			}
			
			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 5)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 952, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите название листовки:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");
			    case 1: ShowPlayerDialogEx(playerid, 953, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите текст:\n\n{AFAFAF}Он должен быть от 10-и до 120-и символов", !"Далее", !"Отмена");
			    case 2: ShowPlayerDialogEx(playerid, 954, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите количество листовок:\n\n{AFAFAF}Одна листовка - 7$ с бюджета организации", !"Далее", !"Отмена");
				case 3:
				{
				    new
				        frmt_flyer_text[310];
				        
					format(frmt_flyer_text, sizeof frmt_flyer_text, "{FFFFFF}Название: {4EAAFF}%s\n\n{FFFFFF}Текст: {4EAAFF}%s", pTemp[playerid][pFlyerName], pTemp[playerid][pFlyerText]);
				    ShowPlayerDialogEx(playerid, 955, DIALOG_STYLE_MSGBOX, !"Предпросмотр", frmt_flyer_text, !"ОК", !"");
				}
				case 4:
				{
				    new
				        frmt_flyer_create[130];
				        
					format(frmt_flyer_create, sizeof frmt_flyer_create, "{FFC800}[Подсказка] {FFFFFF}Вы отправили листовку {4EAAFF}\"%s\"{FFFFFF} на проверку", pTemp[playerid][pFlyerName]);
				    SendClientMessage(playerid, COLOR_WHITE, frmt_flyer_create);
				    
				    new
				        frmt_query_flyer[320];
				        
					format(frmt_query_flyer, sizeof frmt_query_flyer, "INSERT INTO `flyers` VALUES ('', '%s', '%s', '%d', '%d', '0', '%d')", pTemp[playerid][pFlyerName], pTemp[playerid][pFlyerText], PI[playerid][pID], pTemp[playerid][pFlyerCount], PI[playerid][pSubfraction]);
					mysql_tquery(mysql, frmt_query_flyer);
					
					strdel(pTemp[playerid][pFlyerName], 0, 24);
					strdel(pTemp[playerid][pFlyerText], 0, 128);
					pTemp[playerid][pFlyerCount] = 0;
				}
			}
		}
  		case 952:
  		{
		    if(!response)
		    {
	 			new
				    flyer_text[128],
					flyer_count[50];

				if(strlen(pTemp[playerid][pFlyerText]) > 12)
				{
					strmid(flyer_text, pTemp[playerid][pFlyerText], 0, 12, 128);
					format(flyer_text, sizeof flyer_text, "%s...", flyer_text);
				}
				else if(!strlen(pTemp[playerid][pFlyerText]))
				    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");

				else if(strlen(pTemp[playerid][pFlyerText]) < 12)
				    SetString(flyer_text, pTemp[playerid][pFlyerText]);

	            if(!pTemp[playerid][pFlyerCount])
	                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");
	                
				else
				    format(flyer_count, sizeof flyer_count, "%d", pTemp[playerid][pFlyerCount]);

				new
				    frmt_flyer_list[250];

				if(strlen(pTemp[playerid][pFlyerText]) && pTemp[playerid][pFlyerCount] && strlen(pTemp[playerid][pFlyerName]))
					format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр\n{FF7319}5.{FFFFFF} Создать", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

				else
					format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

				ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");
				return 1;
			}

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 5)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			if(!strlen(inputtext) || strlen(inputtext) < 4 || strlen(inputtext) > 20)
				return ShowPlayerDialogEx(playerid, 950, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите название листовки:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			SetString(pTemp[playerid][pFlyerName], inputtext);
			
			new
			    flyer_text[128],
				flyer_count[50];
			    
			if(strlen(pTemp[playerid][pFlyerText]) > 12)
			{
				strmid(flyer_text, pTemp[playerid][pFlyerText], 0, 12, 128);
				format(flyer_text, sizeof flyer_text, "%s...", flyer_text);
			}
			else if(!strlen(pTemp[playerid][pFlyerText]))
			    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");
			    
			else if(strlen(pTemp[playerid][pFlyerText]) < 12)
			    SetString(flyer_text, pTemp[playerid][pFlyerText]);

            if(!pTemp[playerid][pFlyerCount])
                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");

			else
			    format(flyer_count, sizeof flyer_count, "%d", pTemp[playerid][pFlyerCount]);
			    
			new
			    frmt_flyer_list[250];

			if(strlen(pTemp[playerid][pFlyerText]) && pTemp[playerid][pFlyerCount] && strlen(pTemp[playerid][pFlyerName]))
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр\n{FF7319}5.{FFFFFF} Создать", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			else
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");
		}
		case 953:
		{
		    if(!response)
		    {
	 			new
				    flyer_text[128],
					flyer_count[50];

				if(strlen(pTemp[playerid][pFlyerText]) > 12)
				{
					strmid(flyer_text, pTemp[playerid][pFlyerText], 0, 12, 128);
					format(flyer_text, sizeof flyer_text, "%s...", flyer_text);
				}
				else if(!strlen(pTemp[playerid][pFlyerText]))
				    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");

				else if(strlen(pTemp[playerid][pFlyerText]) < 12)
				    SetString(flyer_text, pTemp[playerid][pFlyerText]);

	            if(!pTemp[playerid][pFlyerCount])
	                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");

				else
				    format(flyer_count, sizeof flyer_count, "%d", pTemp[playerid][pFlyerCount]);

				new
				    frmt_flyer_list[250];

				if(strlen(pTemp[playerid][pFlyerText]) && pTemp[playerid][pFlyerCount] && strlen(pTemp[playerid][pFlyerName]))
					format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр\n{FF7319}5.{FFFFFF} Создать", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

				else
					format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

				ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");
				return 1;
			}

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 5)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
			    
			if(!strlen(inputtext) || strlen(inputtext) < 10 || strlen(inputtext) > 120)
				return ShowPlayerDialogEx(playerid, 953, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите текст:\n\n{AFAFAF}Он должен быть от 10-и до 120-и символов", !"Далее", !"Отмена");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			SetString(pTemp[playerid][pFlyerText], inputtext);

			new
			    flyer_text[128],
				flyer_count[50];

			if(strlen(pTemp[playerid][pFlyerText]) > 12)
			{
				strmid(flyer_text, pTemp[playerid][pFlyerText], 0, 12, 128);
				format(flyer_text, sizeof flyer_text, "%s...", flyer_text);
			}
			else if(!strlen(pTemp[playerid][pFlyerText]))
			    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");

			else if(strlen(pTemp[playerid][pFlyerText]) < 12)
			    SetString(flyer_text, pTemp[playerid][pFlyerText]);

            if(!pTemp[playerid][pFlyerCount])
                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");

			else
			    format(flyer_count, sizeof flyer_count, "%d", pTemp[playerid][pFlyerCount]);

			new
			    frmt_flyer_list[250];

			if(strlen(pTemp[playerid][pFlyerText]) && pTemp[playerid][pFlyerCount] && strlen(pTemp[playerid][pFlyerName]))
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр\n{FF7319}5.{FFFFFF} Создать", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			else
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");
			
		}
		case 954:
		{
		    if(!response)
		    {
	 			new
				    flyer_text[128],
					flyer_count[50];

				if(strlen(pTemp[playerid][pFlyerText]) > 12)
				{
					strmid(flyer_text, pTemp[playerid][pFlyerText], 0, 12, 128);
					format(flyer_text, sizeof flyer_text, "%s...", flyer_text);
				}
				else if(!strlen(pTemp[playerid][pFlyerText]))
				    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");

				else if(strlen(pTemp[playerid][pFlyerText]) < 12)
				    SetString(flyer_text, pTemp[playerid][pFlyerText]);

	            if(!pTemp[playerid][pFlyerCount])
	                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");

				else
				    format(flyer_count, sizeof flyer_count, "%d", pTemp[playerid][pFlyerCount]);

				new
				    frmt_flyer_list[250];

				if(strlen(pTemp[playerid][pFlyerText]) && pTemp[playerid][pFlyerCount] && strlen(pTemp[playerid][pFlyerName]))
					format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр\n{FF7319}5.{FFFFFF} Создать", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

				else
					format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

				ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");
				return 1;
			}

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 5)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
			    
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 100)
				return ShowPlayerDialogEx(playerid, 954, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите количество листовок:\n\n{AFAFAF}Одна листовка - 7$ с бюджета организации", !"Далее", !"Отмена");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
				
			if(OrgInfo[8][oMoney] < strval(inputtext)*7)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете организации недостаточно средств на создание такой суммы листовок");

            pTemp[playerid][pFlyerCount] = strval(inputtext);
            
 			new
			    flyer_text[128],
				flyer_count[50];

			if(strlen(pTemp[playerid][pFlyerText]) > 12)
			{
				strmid(flyer_text, pTemp[playerid][pFlyerText], 0, 12, 128);
				format(flyer_text, sizeof flyer_text, "%s...", flyer_text);
			}
			else if(!strlen(pTemp[playerid][pFlyerText]))
			    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");

			else if(strlen(pTemp[playerid][pFlyerText]) < 12)
			    SetString(flyer_text, pTemp[playerid][pFlyerText]);

            if(!pTemp[playerid][pFlyerCount])
                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");

			else
			    format(flyer_count, sizeof flyer_count, "%d", pTemp[playerid][pFlyerCount]);

			new
			    frmt_flyer_list[250];

			if(strlen(pTemp[playerid][pFlyerText]) && pTemp[playerid][pFlyerCount] && strlen(pTemp[playerid][pFlyerName]))
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр\n{FF7319}5.{FFFFFF} Создать", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			else
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");

		}
		case 955:
		{
			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 5)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

 			new
			    flyer_text[128],
				flyer_count[50];

			if(strlen(pTemp[playerid][pFlyerText]) > 12)
			{
				strmid(flyer_text, pTemp[playerid][pFlyerText], 0, 12, 128);
				format(flyer_text, sizeof flyer_text, "%s...", flyer_text);
			}
			else if(!strlen(pTemp[playerid][pFlyerText]))
			    format(flyer_text, sizeof flyer_text, "{FF0000}-{FFFFFF}");

			else if(strlen(pTemp[playerid][pFlyerText]) < 12)
			    SetString(flyer_text, pTemp[playerid][pFlyerText]);

            if(!pTemp[playerid][pFlyerCount])
                format(flyer_count, sizeof flyer_count, "{FF0000}-{FFFFFF}");

			else
			    format(flyer_count, sizeof flyer_count, "%d", pTemp[playerid][pFlyerCount]);
			    
			new
			    frmt_flyer_list[250];

			if(strlen(pTemp[playerid][pFlyerText]) && pTemp[playerid][pFlyerCount] && strlen(pTemp[playerid][pFlyerName]))
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр\n{FF7319}5.{FFFFFF} Создать", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			else
				format(frmt_flyer_list, sizeof frmt_flyer_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Количество [%s]\n{FF7319}4.{FFFFFF} Предпросмотр", pTemp[playerid][pFlyerName], flyer_text, flyer_count);

			ShowPlayerDialogEx(playerid, 951, DIALOG_STYLE_LIST, !"Создание листовки", frmt_flyer_list, !"Далее", !"Отмена");
		}
		case 960:
		{
		    if(!response)
		    	return 1;
		    	
			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 8)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			if(listitem != 40)
			{
			    new
					id;

			    id = strval(inputtext[strfind(inputtext, "№")]);
			    
				new
					query_flyer_info[350],
					frmt_flyer_info[400],
					name[24],
					text[128],
					sender,
					nickname[MAX_PLAYER_NAME];

				format(query_flyer_info, sizeof query_flyer_info, "SELECT `name`, `text`, `sender` FROM `flyers` WHERE `checked` = 0 AND `subfraction` = %d AND `id` = %d", PI[playerid][pSubfraction], id);
				new Cache:result = mysql_query(mysql, query_flyer_info);
				new flyers = cache_get_row_count(mysql);

				if(flyers == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных листовок для проверки");
				  	
                cache_get_row(0, 0, name, mysql);
				cache_get_row(0, 1, text, mysql);
				sender = cache_get_row_int(0, 2, mysql);
				GetPlayerNameByID(sender, nickname);
				
				format(frmt_flyer_info, sizeof frmt_flyer_info, "{FFFFFF}Название: {4EAAFF}%s\n\n{FFFFFF}Текст: {4EAAFF}%s\n\n\n{FFFFFF}Отправитель: {FFF748}%s", name, text, nickname);
				ShowPlayerDialogEx(playerid, 963, DIALOG_STYLE_MSGBOX, !"Проверка листовки", frmt_flyer_info, !"Далее", !"");
				cache_delete(result, mysql);
				
				pTemp[playerid][pFlyerID] = id;
			}
			else if(listitem == 40)
			{
				new
				    frmt_flyers_list[2900],
					query_get_list[350],
					name[24],
					id,
					flyers_count;

				format(query_get_list, sizeof query_get_list, "SELECT `id`, `name`, `sender` FROM `flyers` WHERE `checked` = 0 AND `subfraction` = %d LIMIT %d, 41", PI[playerid][pSubfraction]+1, pTemp[playerid][pFlyersList]);
				new Cache:result = mysql_query(mysql, query_get_list);
				new flyers = cache_get_row_count(mysql);

				if(flyers == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных листовок для проверки");

				for(new i; i < flyers; i ++)
				{
				    if(flyers_count > 39 && flyers > 40)
					{
						format(frmt_flyers_list, sizeof frmt_flyers_list, "%s{FFFFFF}Следующая страница", frmt_flyers_list);
					    break;
					}

			        id = cache_get_row_int(i, 0, mysql);
					cache_get_row(i, 1, name, mysql);

					format(frmt_flyers_list, sizeof frmt_flyers_list, "%s%d. %s [№%d]\n", frmt_flyers_list, i+1, name, id);

					pTemp[playerid][pFlyersList]++;
			        flyers_count++;
				}
				ShowPlayerDialogEx(playerid, 960, DIALOG_STYLE_LIST, !"Проверка листовок", frmt_flyers_list, !"Далее", !"Назад");
				cache_delete(result, mysql);
			}
		}
		case 963:
		{
		    if(!response)
		    	return 1;

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 8)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			new
				query_flyer_info[200],
				name[24];

			format(query_flyer_info, sizeof query_flyer_info, "SELECT `name` FROM `flyers` WHERE `checked` = 0 AND `subfraction` = %d AND `id` = %d", PI[playerid][pSubfraction], pTemp[playerid][pFlyerID]);
			new Cache:result = mysql_query(mysql, query_flyer_info);
			new flyer = cache_get_row_count(mysql);

			if(flyer == 0)
			  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Листовка больше недоступна");
			  	
			cache_get_row(0, 0, name, mysql);
			
			
			ShowPlayerDialogEx(playerid, 962, DIALOG_STYLE_LIST, name, !"{FF7319}1.{FFFFFF} Одобрить\n{FF7319}2.{FFFFFF} Отклонить", !"Далее", !"Отмена");
			cache_delete(result, mysql);
		}
		case 962:
		{
		    if(!response)
		    	return 1;

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 8)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			new
				query_flyer_info[200],
				frmt_flyer_message[120],
				query_flyer_upt[120],
				name[24];

			format(query_flyer_info, sizeof query_flyer_info, "SELECT `name` FROM `flyers` WHERE `checked` = 0 AND `subfraction` = %d AND `id` = %d", PI[playerid][pSubfraction], pTemp[playerid][pFlyerID]);
			new Cache:result = mysql_query(mysql, query_flyer_info);
			new flyer = cache_get_row_count(mysql);

			if(flyer == 0)
			  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Листовка больше недоступна");

            cache_get_row(0, 0, name, mysql);
            
            switch(listitem)
            {
                case 0:
                {
					format(frmt_flyer_message, sizeof frmt_flyer_message, "[R] %s одобрил(а) листовку \"%s\"", PN(playerid), name);
      				foreach(new i : Player)
					{
						if(IsPlayerConnected(i) && PI[i][pFraction] == PI[playerid][pFraction] &&
						PI[i][pSubfraction] == PI[playerid][pSubfraction]) SendClientMessage(i, 0x4682B4AA, frmt_flyer_message);
					}
					format(query_flyer_upt, sizeof query_flyer_upt, "UPDATE `flyers` SET `checked` = '1' WHERE `id` = %d", pTemp[playerid][pFlyerID]);
					mysql_tquery(mysql, query_flyer_upt);
				}
                case 1:
                {
					format(frmt_flyer_message, sizeof frmt_flyer_message, "[R] %s отклонил(а) листовку \"%s\"", PN(playerid), name);
      				foreach(new i : Player)
					{
						if(IsPlayerConnected(i) && PI[i][pFraction] == PI[playerid][pFraction] &&
						PI[i][pSubfraction] == PI[playerid][pSubfraction]) SendClientMessage(i, 0x4682B4AA, frmt_flyer_message);
					}
					format(query_flyer_upt, sizeof query_flyer_upt, "DELETE FROM `flyers` WHERE `id` = %d", pTemp[playerid][pFlyerID]);
					mysql_tquery(mysql, query_flyer_upt);
				}
			}
			cache_delete(result, mysql);
		}
		case 965:
		{
		    if(!response)
		    	return 1;

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(listitem != 40)
			{
			    new
					id;

			    id = strval(inputtext[strfind(inputtext, "№")]);

				if(PI[playerid][pFlyers])
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть листовки");
				    
				new
					query_flyer_info[350],
					frmt_flyer_info[400],
					name[24],
					text[128],
					count;

				format(query_flyer_info, sizeof query_flyer_info, "SELECT `name`, `text`, `count` FROM `flyers` WHERE `checked` = 1 AND `subfraction` = %d AND `id` = %d  AND `count` > 0", PI[playerid][pSubfraction], id);
				new Cache:result = mysql_query(mysql, query_flyer_info);
				new flyers = cache_get_row_count(mysql);

				if(flyers == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных листовок");

                cache_get_row(0, 0, name, mysql);
				cache_get_row(0, 1, text, mysql);
                count = cache_get_row_int(0, 2, mysql);

				format(frmt_flyer_info, sizeof frmt_flyer_info, "{FFFFFF}Название: {4EAAFF}%s\n\n{FFFFFF}Текст: {4EAAFF}%s\n\n{FFFFFF}Введите количество которое хотите взять:\n\n{AFAFAF}Доступно: %d штук", name, text, count);
				ShowPlayerDialogEx(playerid, 966, DIALOG_STYLE_INPUT, !"Взятие листовок", frmt_flyer_info, !"Далее", !"Отмена");
				cache_delete(result, mysql);

				pTemp[playerid][pFlyerID] = id;
			}
			else if(listitem == 40)
			{
				new
				    frmt_flyers_list[2900],
					query_get_list[350],
					name[24],
					id,
					flyers_count;

				format(query_get_list, sizeof query_get_list, "SELECT `id`, `name`, `sender` FROM `flyers` WHERE `checked` = 1 AND `subfraction` = %d AND `count` > 0 LIMIT %d, 41", PI[playerid][pSubfraction]+1, pTemp[playerid][pFlyersList]);
				new Cache:result = mysql_query(mysql, query_get_list);
				new flyers = cache_get_row_count(mysql);

				if(flyers == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных листовок");

				for(new i; i < flyers; i ++)
				{
				    if(flyers_count > 39 && flyers > 40)
					{
						format(frmt_flyers_list, sizeof frmt_flyers_list, "%s{FFFFFF}Следующая страница", frmt_flyers_list);
					    break;
					}

			        id = cache_get_row_int(i, 0, mysql);
					cache_get_row(i, 1, name, mysql);

					format(frmt_flyers_list, sizeof frmt_flyers_list, "%s%d. %s [№%d]\n", frmt_flyers_list, i+1, name, id);

					pTemp[playerid][pFlyersList]++;
			        flyers_count++;
				}
				ShowPlayerDialogEx(playerid, 965, DIALOG_STYLE_LIST, !"Список листовок", frmt_flyers_list, !"Далее", !"Назад");
				cache_delete(result, mysql);
			}
		}
		case 966:
		{
		    if(!response)
		    	return 1;

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

		    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 1733.2097, 182.4489, 1125.9989))
			    return 1;


			new
			    id = pTemp[playerid][pFlyerID];
			    
			if(PI[playerid][pFlyers])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть листовки");
				    
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 10)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");
			
			
			new
				query_flyer_info[350],
				frmt_flyer_info[230],
				query_flyer_upt[230],
				name[24],
				count;

			format(query_flyer_info, sizeof query_flyer_info, "SELECT `name`, `count` FROM `flyers` WHERE `checked` = 1 AND `subfraction` = %d AND `id` = %d  AND `count` > 0", PI[playerid][pSubfraction], id);
			new Cache:result = mysql_query(mysql, query_flyer_info);
			new flyers = cache_get_row_count(mysql);

			if(flyers == 0)
			  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных листовок");

            cache_get_row(0, 0, name, mysql);
            count = cache_get_row_int(0, 1, mysql);
            
			if(count < strval(inputtext))
			  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе нет столько листовок");

			format(frmt_flyer_info, sizeof frmt_flyer_info, "{7AC71F}[Успешно] {FFFFFF}Вы взяли %d листовок под названием \"%s\"", strval(inputtext), name);
			SendClientMessage(playerid, COLOR_WHITE, frmt_flyer_info);
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FF0000}/giveflyer [ID]{FFFFFF} для передачи листовки");
			
			PI[playerid][pFlyers] = id;
			UpdatePlayerData(playerid, "Flyers", PI[playerid][pFlyers]);
			PI[playerid][pFlyersCount] = strval(inputtext);
			UpdatePlayerData(playerid, "FlyersCount", PI[playerid][pFlyersCount]);
			
			format(query_flyer_upt, sizeof query_flyer_upt, "UPDATE `flyers` SET `count` = `count`-%d WHERE `id` = %d", strval(inputtext), id);
			mysql_tquery(mysql, query_flyer_upt);
			
			pTemp[playerid][pFlyerID] = 0;
			
			cache_delete(result, mysql);
			
			
		}
		case 195:
		{
		    if(0 == response)
				return 1;
				
		    if(0 == PI[playerid][pHouseKey])
				return 1;
				
	        new
				house = PI[playerid][pHouseKey]-1;
				
	        if(!GetString(HouseInfo[house][hOwner], PN(playerid)))
				return 1;
				
            if(GetString(HRoomOwner[house][listitem], "The State"))
				return callcmd::home(playerid, "");
				
		    new
				target = GetNameID(HRoomOwner[house][listitem]),
				frmt_evicting_message[120],
				query_evicting[110];
				
		    if(target != INVALID_PLAYER_ID && IsPlayerConnected(target) && IsPlayerLogged[target])
		    {
		        PI[target][pHouseKey] = 0;
		        UpdatePlayerData(target, "HouseKey", PI[target][pHouseKey]);
				PI[target][pSpawn] = 0;
				UpdatePlayerData(target, "Spawn", 0);
		        format(frmt_evicting_message, sizeof frmt_evicting_message, "%s выселил Вас из дома", PN(playerid));
		        SendClientMessage(target, 0xFF5030AA, frmt_evicting_message);
		    }
		    else
		    {
		        format(query_evicting, sizeof query_evicting, "UPDATE `accounts` SET `HouseKey` = '0', `Spawn` = '0' WHERE `NickName` = '%s'", HRoomOwner[house][listitem]);
		        mysql_tquery(mysql, query_evicting);
		    }
		    format(frmt_evicting_message, sizeof frmt_evicting_message, "{7AC71F}[Успешно] {FFFFFF}Вы выселили игрока {FF0000}%s{FFFFFF} из своего дома", HRoomOwner[house][listitem]);
			SendClientMessage(playerid, COLOR_WHITE, frmt_evicting_message);
		    SetString(HRoomOwner[house][listitem], "The State");
			SaveHouse(house);
		}
		case 196:
		{
		    if(!response)
				return pTemp[playerid][pRentOffer] = INVALID_PLAYER_ID;
				
		    new
				target = pTemp[playerid][pRentOffer];
				
		    if(target == INVALID_PLAYER_ID || !IsPlayerConnected(target) || !IsPlayerLogged[target])
				return pTemp[playerid][pRentOffer] = INVALID_PLAYER_ID, SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Предложение больше неактивно");

			if(!PI[target][pHouseKey])
				return pTemp[playerid][pRentOffer] = INVALID_PLAYER_ID, SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Предложение больше неактивно");

			new
				house = PI[target][pHouseKey]-1,
				frmt_offer_list[180];
				
			if(house+1 == 0)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неизвестный номер дома");
				
		    if(!GetString(HouseInfo[house][hOwner], PN(target)))
				return pTemp[playerid][pRentOffer] = INVALID_PLAYER_ID, SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Предложение больше неактивно");

			for(new i; i < GetHouseClass(house); i++)
				format(frmt_offer_list, sizeof frmt_offer_list, "%s{FF7319}%d.{FFFFFF} Комната №%d\n", frmt_offer_list, i+1, i+1);
				
    		ShowPlayerDialogEx(playerid, 197, DIALOG_STYLE_LIST, !"Выберите комнату", frmt_offer_list, !"Занять", !"Назад");
		}
		case 197:
		{
		    if(!response)
				return pTemp[playerid][pRentOffer] = INVALID_PLAYER_ID;
				
		    new
				target = pTemp[playerid][pRentOffer];

		    if(target == INVALID_PLAYER_ID || !IsPlayerConnected(target) || !IsPlayerLogged[target])
				return pTemp[playerid][pRentOffer], SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Предложение больше неактивно");

			if(!PI[target][pHouseKey])
				return pTemp[playerid][pRentOffer], SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Предложение больше неактивно");

		    if(!GetString(HouseInfo[PI[target][pHouseKey]-1][hOwner], PN(target)))
				return pTemp[playerid][pRentOffer], SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Предложение больше неактивно");

			new
				house = PI[target][pHouseKey]-1,
				frmt_offer_list[180],
				frmt_accept_message[125];
				
	    	if(GetString(HRoomOwner[house][listitem], "The State"))
	    	{
	    	    SetString(HRoomOwner[house][listitem], PN(playerid));

	    	    format(frmt_accept_message, sizeof frmt_accept_message, "{7AC71F}[Успешно] {FFFFFF}Вы арендовали комнату в доме игрока %s", PN(target));
	    	    SendClientMessage(playerid, COLOR_WHITE, frmt_accept_message);

	    	    format(frmt_accept_message, sizeof frmt_accept_message, "{7AC71F}[Успешно] {FFFFFF}%s принял предложение пожить у Вас в доме", PN(playerid));
	    	    SendClientMessage(target, COLOR_WHITE, frmt_accept_message);

				PI[playerid][pHouseKey] = HouseInfo[house][hID];
				UpdatePlayerData(playerid, "HouseKey", PI[playerid][pHouseKey]);
				
				pTemp[playerid][pRentOffer] = INVALID_PLAYER_ID;

				PI[playerid][pSpawn] = 2;
				UpdatePlayerData(playerid, "Spawn", 2);

				SaveHouse(house);
	    	}
	    	else
	    	{
				for(new i; i < GetHouseClass(house); i++)
					format(frmt_offer_list, sizeof frmt_offer_list, "%s{FF7319}%d.{FFFFFF} Комната №%d\n", frmt_offer_list, i+1, i+1);

	    		ShowPlayerDialogEx(playerid, 197, DIALOG_STYLE_LIST, !"Выберите комнату", frmt_offer_list, !"Занять", !"Назад");
	    	}
		}
		case 198:
		{
		    if(!response)
			    return 1;

			if(!strlen(inputtext) || !isNumeric(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");
			    
		    new
				target = strval(inputtext);
				
			if(!IsPlayerConnected(target) || playerid == target)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

			if(GetPlayerDistanceToPlayer(playerid, target) > 5.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				
		 	if(PI[target][pHouseKey] != 0)
			 	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок уже живет в доме");
			 	
		 	//if(PI[id][pFrom] != -1) return SCM(playerid,COLOR_RED,"[Ошибка] {FFFFFF}Вы не можете подселить этого игрока к вам в дом, так как он проживает в отеле!");

			new
				house = PI[playerid][pHouseKey]-1,
				frmt_rent_message[85];
			
		    for(new i; i < GetHouseClass(house); i++)
			{
				if(GetString(HRoomOwner[house][i], "The State"))
				{
					format(frmt_rent_message, sizeof frmt_rent_message, "%s предлагает Вам арендовать комнату в его доме", PN(playerid));
					ShowPlayerDialogEx(target, 196, DIALOG_STYLE_MSGBOX, !"Аренда", frmt_rent_message, !"Принять", !"Отмена");

					format(frmt_rent_message, sizeof frmt_rent_message, "Вы предложили {FFFFFF}%s{269BD8} арендовать комнату в Вашем доме", PN(target));
					SendClientMessage(playerid, 0x269BD8FF, frmt_rent_message);
	
					pTemp[target][pRentOffer] = playerid;
					return true;
				}
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Все комнаты Вашего дома заняты");
			}
			
		}

		case 174:
		{
		    if(response)
		    {
		        new house = PI[playerid][pHouseKey]-1;
		        if(PI[playerid][pHouseKey] != 0)
				{
					switch(listitem)
					{
					    case 0:
					    {
							if(HouseInfo[house][hLock])
							{
								HouseInfo[house][hLock] = 0;
								GameTextForPlayer(playerid,"~g~opened",2000,3);
								UpdateHouse(house);
								SaveHouse(house);
							}
							else
							{
						       	HouseInfo[house][hLock] = 1;
						       	
						       	GameTextForPlayer(playerid,"~r~closed",2000,3);
						       	UpdateHouse(house);
						       	SaveHouse(house);
							}
						}
						case 1: //Статистика
						{
							new classname[20];
							switch(HouseInfo[house][hLevel])
							{
								case 0:classname = "Эконом";
								case 1:classname = "Cредний";
								case 2:classname = "Элитный";
								case 3:classname = "Особняк";
								default: classname = "Неизвестно";
							}
							new mes[256];

							new carname[24];
							if(!PI[playerid][pCars]) strcat(carname,"Нет");
							else
							{
								for(new i;i<MAX_VEHICLES;i++)
								{
									if(CarInfo[i][cOwnerID] == PI[playerid][pID])
									{
										strcat(carname, Transport[CarInfo[i][cModelID]][trName]);
										break;
									}
								}
							}
							new rent = floatround(HouseInfo[house][hCost] * 0.005);
							if(HouseInfo[house][hImprove][3]) rent = rent / 2;
							

							new status[24];
							if(HouseInfo[house][hLock]) strcat(status,"{FF0000}Закрыт");
							else strcat(status,"{33AA33}Открыт");
							
							new improve[65];
							if(HouseInfo[house][hImprove][0]) strcat(improve," -Автом. двери\n");
							if(HouseInfo[house][hImprove][1]) strcat(improve," -Сейф\n");
							if(HouseInfo[house][hImprove][2]) strcat(improve," -Шкаф\n");
							if(HouseInfo[house][hImprove][3]) strcat(improve," -Субсидии");
							
							if(!HouseInfo[house][hImprove][0] && !HouseInfo[house][hImprove][1] && !HouseInfo[house][hImprove][2] && !HouseInfo[house][hImprove][3])
								format(mes,sizeof(mes),"{FFFFFF}House ID: %d\nКласс: %s\nДомашний транспорт: %s\nКвартплата: %d\nКол-во оплаченных дней: %d\nСостояние: %s\n{FFFFFF}Гос. цена: %d", house+1, classname, carname, rent, HouseInfo[house][hDays], status, HouseInfo[house][hCost]);

							else
								format(mes,sizeof(mes),"{FFFFFF}House ID: %d\nКласс: %s\nДомашний транспорт: %s\nКвартплата: %d\nКол-во оплаченных дней: %d\nСостояние: %s\n{FFFFFF}Гос. цена: %d\nУлучшения:\n%s", house+1, classname, carname, rent, HouseInfo[house][hDays], status, HouseInfo[house][hCost], improve);

							ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Управление домом", mes, !"OK", !"");
						}
						case 2:
						{
							new mes[289];
							for(new i;i<4;i++)
							{
								new c[7];
								if(HouseInfo[house][hImprove][i]) c = "33AA33";
								else if(!i || HouseInfo[house][hImprove][i-1]) c = "FFFFFF";
								else c = "AFAFAF";
								if(!i) format(mes,sizeof(mes),"{%s}%d. %s",c, i+1, HouseImproveName[i]);
								else format(mes,sizeof(mes),"%s\n{%s}%d. %s",mes, c, i+1, HouseImproveName[i]);
							}
		    			    ShowPlayerDialogEx(playerid, 176, DIALOG_STYLE_LIST, !"Улучшения", mes, !"Купить", !"Отмена");
						}
						case 3:
						{
     						if(!GetString(HouseInfo[house][hOwner], PN(playerid)))
	                        	return SendClientMessage(playerid, COLOR_GREY, !"Данная функция доступна только владельцу дома");
	                        	
						    callcmd::sellcar(playerid, "");
						}
						case 4:
						{
     						if(!GetString(HouseInfo[house][hOwner], PN(playerid)))
	                        	return SendClientMessage(playerid, COLOR_GREY, !"Данная функция доступна только владельцу дома");

						    if(!PI[playerid][pCars])
								return SendClientMessage(playerid, COLOR_GREY, !"У Вас нет личного т/c");
								
							if(PI[playerid][pMoney] < 1000)
								return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточно денег");
								
							new slot = GetCarSlot(PI[playerid][pCars]),
					    		query_save_house[381],
							 	modelid = CarInfo[slot][cModelID];

							format(query_save_house, sizeof query_save_house, "UPDATE `cars` SET `cFuel` = '%.2f', `cMilage` = '%.2f' WHERE `cOwnerID` = '%d'", CarInfo[slot][cFuel], CarInfo[slot][cMilage], PI[playerid][pID]);
							mysql_tquery(mysql, query_save_house);

					    	new carID = PI[playerid][pCars];
					    	DestroyVehicle(CarInfo[GetCarSlot(carID)][cVehID]);
					    	
							new vehicleid = CreateVehicle(Transport[modelid][trModel], HouseInfo[house][hPark_X], HouseInfo[house][hPark_Y], HouseInfo[house][hPark_Z], HouseInfo[house][hPark_R], CarInfo[slot][cColor_1], CarInfo[slot][cColor_2], -1);
							CarInfo[slot][cVehID] = vehicleid;

							if(CarInfo[slot][cHealth] < 300.0)
								CarInfo[slot][cHealth] = 1000.0;

							J_SetVehicleHealth(vehicleid, CarInfo[slot][cHealth]);
							ToggleLock(vehicleid);
							VehicleInfo[vehicleid][vFuel] = CarInfo[slot][cFuel];
							VehicleInfo[vehicleid][vMillage] = CarInfo[slot][cMilage];
							VehicleInfo[vehicleid][vHealth] = CarInfo[slot][cHealth];
							VehicleInfo[vehicleid][vOwnerid] = CarInfo[slot][cOwnerID];
							SetVehicleNumberPlate(vehicleid, CarInfo[slot][cNumber]);
							SetDoorsStatus(vehicleid, 1);
							
							for(new tn; tn < 14; tn++)
								if(CarInfo[slot][cTuning][tn] != 0) AddVehicleComponent(vehicleid, CarInfo[slot][cTuning][tn]);

							ChangeVehiclePaintjob(vehicleid, CarInfo[slot][cPaintJob]);

							foreach(new i : Player) if(IsPlayerConnected(i) && IsVehicleStreamedIn(vehicleid,i)) SetVehicleParamsForPlayer(vehicleid,i,0,1);
							VehicleInfo[vehicleid][vLock] = 1;
			                SetDoorsStatus(vehicleid, 1);
		                
							GiveMoney(playerid, -1000, "респавн авто");
							SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Транспорт доставлен к дому");
						}
						case 5:
						{
     						if(!GetString(HouseInfo[house][hOwner] , PN(playerid)))
	                        	return SendClientMessage(playerid, COLOR_GREY, !"Данная функция доступна только владельцу дома");

							if(!PI[playerid][pCars])
								return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с");
								
							new carid = GetCarSlot(PI[playerid][pCars]);
							
							if(carid == -1)
								return SendClientMessage(playerid, COLOR_GREY, !"Ошибка #115");
								
							new vid = CarInfo[carid][cVehID];
							
							if(vid == INVALID_VEHICLE_ID)
								return SendClientMessage(playerid, COLOR_GREY, !"Ошибка #116");
								
                            GetVehiclePos(vid, VehicleInfo[vid][vX], VehicleInfo[vid][vY], VehicleInfo[vid][vZ]);
							SetPlayerCheckpointExx(playerid, VehicleInfo[vid][vX], VehicleInfo[vid][vY], VehicleInfo[vid][vZ], 5.0);
						}
						case 6:
						{
     						if(!GetString(HouseInfo[house][hOwner], PN(playerid)))
	                        	return SendClientMessage(playerid, COLOR_GREY, !"Данная функция доступна только владельцу дома");

							callcmd::sellhouse(playerid, "");
						}
						case 7:
						{
     						if(!GetString(HouseInfo[house][hOwner], PN(playerid)))
	                        	return SendClientMessage(playerid, COLOR_GREY, !"Данная функция доступна только владельцу дома");

		                    if(!PI[playerid][pCars])
								return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с");
								
		                    if(PI[playerid][pMoney] < 15000)
								return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточно денег");
								
		                    ShowPlayerDialogEx(playerid, 670, DIALOG_STYLE_MSGBOX, !"Удаление тюнинга", !"\n\n\n{FFFFFF}Вы действительно хотите удалить все компоненты\nтюнинга с Вашего транспорта?\n\n\n", !"Да", !"Отмена");

						}
						case 8:
						{
     						if(GetString(HouseInfo[house][hOwner], PN(playerid)))
	                        	ShowPlayerDialogEx(playerid, 198, DIALOG_STYLE_INPUT, !"Аренда", !"{FFFFFF}Введите ID игрока, которого хотите подселить к себе в дом:", !"Далее", !"Отмена");

							else
							{
		     					for(new i; i < GetHouseClass(house); i++)
								{
									if(GetString(HRoomOwner[house][i], PN(playerid)))
									{
									    SetString(HRoomOwner[house][i], "The State");
			        					SaveHouse(house);
									    PI[playerid][pHouseKey] = 0;
									    UpdatePlayerData(playerid, "HouseKey", PI[playerid][pHouseKey]);
										PI[playerid][pSpawn] = 0;
										UpdatePlayerData(playerid, "Spawn",0);
								        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выселились из дома");
								       	return true;
									}
								}
								PI[playerid][pHouseKey] = 0;
								UpdatePlayerData(playerid, "HouseKey", PI[playerid][pHouseKey]);
								PI[playerid][pSpawn] = 0;
								UpdatePlayerData(playerid, "Spawn",0);
								SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выселились из дома");
							}

						}
						case 9:
						{
     						if(!GetString(HouseInfo[house][hOwner], PN(playerid)))
	                        	return SendClientMessage(playerid, COLOR_GREY, !"Данная функция доступна только владельцу дома");
	                        	
		    			    new
								status[60],
								frmt_room_list[155];
								
		    			    for(new i; i < GetHouseClass(house); i++)
		    			    {
		    			        if(GetString(HRoomOwner[house][i], "The State"))
									SetString(status, "-");
									
		    			        else
		    			            SetString(status, HRoomOwner[house][i]);
									
 			        			format(frmt_room_list, sizeof frmt_room_list , "%s{FF7319}%d.{FFFFFF} %s\n", frmt_room_list, i+1, status);
		    			    }
		    			    if(strlen(frmt_room_list) > 0)
								ShowPlayerDialogEx(playerid, 195, DIALOG_STYLE_LIST, !"Список жильцов", frmt_room_list, !"Выселить", !"Назад");
								
		    			    else
								SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашем доме нет жильцов");
								
						}
					}
				}
			}
		}

		case 176:
		{
			if(!response) return callcmd::home(playerid, "");
			new houseid = PI[playerid][pHouseKey] - 1;
			if(HouseInfo[houseid][hImprove][listitem])
			{
				SendClientMessage(playerid, COLOR_GREEN, !"У Вас уже установлено это улучшение");
				new mes[289];
				for(new i;i<4;i++)
				{
					new c[7];
					if(HouseInfo[houseid][hImprove][i]) c = "33AA33";
					else if(!i || HouseInfo[houseid][hImprove][i-1]) c = "FFFFFF";
					else c = "AFAFAF";
					if(!i) format(mes,sizeof(mes),"{%s}%d. %s",c, i+1, HouseImproveName[i]);
					else format(mes,sizeof(mes),"%s\n{%s}%d. %s",mes, c, i+1, HouseImproveName[i]);
				}
			    ShowPlayerDialogEx(playerid, 176, DIALOG_STYLE_LIST, !"Улучшения", mes, !"Купить", !"Отмена");

			}
			else if((!listitem && !HouseInfo[houseid][hImprove][listitem]) || (HouseInfo[houseid][hImprove][listitem-1] && !HouseInfo[houseid][hImprove][listitem]))
			{
				new mes[92 + 46 + 6];
				format(mes, sizeof(mes),"{FFFFFF}Вы хотите купить улучшение: {269BD8}\"%s\"?\n{FFFFFF}Оно обойдется Вам в {FF0000}$%d", HouseImproveName[listitem], HouseImprovePrice[listitem]);
				ShowPlayerDialogEx(playerid, 491, DIALOG_STYLE_MSGBOX, !"Покупка улучшения", mes, !"Купить", !"Отмена");
				SetPVarInt(playerid, "improveid", listitem);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, !"Это улучшение еще не доступно Вам");
				new mes[289];
				for(new i;i<4;i++)
				{
					new c[7];
					if(HouseInfo[houseid][hImprove][i]) c = "33AA33";
					else if(!i || HouseInfo[houseid][hImprove][i-1]) c = "FFFFFF";
					else c = "AFAFAF";
					if(!i) format(mes,sizeof(mes),"{%s}%d. %s",c, i+1, HouseImproveName[i]);
					else format(mes,sizeof(mes),"%s\n{%s}%d. %s",mes, c, i+1, HouseImproveName[i]);
				}
			    ShowPlayerDialogEx(playerid, 176, DIALOG_STYLE_LIST, !"Улучшения", mes, !"Купить", !"Отмена");

			}
		}
		case 491:
		{
			new improveid = GetPVarInt(playerid,"improveid");
			DeletePVar(playerid,"improveid");
			if(!response) return callcmd::home(playerid, "");
			new price = HouseImprovePrice[improveid];
			if(PI[playerid][pMoney] < price)
			{
				callcmd::home(playerid, "");
				return SendClientMessage(playerid, COLOR_GREY, "У Вас недостаточно денег");
			}
			new houseid = PI[playerid][pHouseKey] - 1;
			HouseInfo[houseid][hImprove][improveid] = 1;
			new hintid = HouseInfo[houseid][hNumInt]-1;

			
			switch(improveid)
			{
				case 1:
				{
					HintSafeObject[houseid] = CreateDynamicObject(2332, HintSafe[hintid][0], HintSafe[hintid][1], HintSafe[hintid][2], HintSafe[hintid][3], HintSafe[hintid][4], HintSafe[hintid][5], 51+houseid), HintSafeText[hintid] = CreateDynamic3DTextLabel("Сейф\n\n{FFFFFF}Введите /safe для взаимодействия", 0x1E90FFFF, HintSafe[hintid][0],HintSafe[hintid][1],HintSafe[hintid][2], 5.0, .worldid = 51+houseid);
					HintSafeText[houseid] = CreateDynamic3DTextLabel("Сейф\n\n{FFFFFF}Введите /safe для взаимодействия", 0x1E90FFFF, HintSafe[hintid][0], HintSafe[hintid][1], HintSafe[hintid][2], 5.0, .worldid = 51+houseid);

				//case 2: CreateDynamicObject(2141, HintFreez[hintid][0], HintFreez[hintid][1], HintFreez[hintid][2], HintFreez[hintid][3], HintFreez[hintid][4], HintFreez[hintid][5], 51+houseid);
				}
				case 2:
				{
					HintStoreObject[houseid] = CreateDynamicObject(2708, HintStore[hintid][0], HintStore[hintid][1], HintStore[hintid][2], HintStore[hintid][3], HintStore[hintid][4], HintStore[hintid][5], 51+houseid);
					HintStoreText[houseid] = CreateDynamic3DTextLabel("Шкаф\n\n{FFFFFF}Введите /store для взаимодействия", 0x1E90FFFF, HintStore[hintid][0], HintStore[hintid][1]+0.7, HintStore[hintid][2]+1.0, 5.0, .worldid = 51+houseid);
					HouseInfo[houseid][hSkin][0] = PI[playerid][pSkin];
					//if(pInfo[playerid][pFraction]) gHouses[houseid][houseSkin][3] = pInfo[playerid][pFractionSkin];
					UpdateHouseDress(houseid);
					//if(mysql_errno()) return SendClientMessage(playerid,COLOR_RED,"Ошибка Mysql (сохранение одежды в шкафу)");
				}
			}

			new data[32],query[128];
			for(new i;i<4;i++)
			{
				if(!i) format(data,sizeof(data),"%d",HouseInfo[houseid][hImprove][i]);
				else format(data,sizeof(data),"%s|%d",data,HouseInfo[houseid][hImprove][i]);
			}
			format(query,sizeof(query),"UPDATE `houses` SET `Improve` = '%s' WHERE ID = '%d'", data, houseid+1);
			mysql_tquery(mysql, query);
			SaveHouse(houseid);
			
			if(mysql_errno())
				return SendClientMessage(playerid,COLOR_RED,"Произошла ошибка MySQL (покупка улучшения для дома)");
			
			GiveMoney(playerid, -HouseImprovePrice[improveid], "покупка улучшения для дома");
			
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Поздравляем, Вы купили улучшение для дома.");
			
			if(improveid == 1) SendClientMessage(playerid,0x3399FFFF,"Код сейфа по умолчанию: \"{AFAFAF}0000{269BD8}\"");
			
			new mes[289];
			for(new i;i<4;i++)
			{
				new c[7];
				if(HouseInfo[houseid][hImprove][i]) c = "33AA33";
				else if(!i || HouseInfo[houseid][hImprove][i-1]) c = "FFFFFF";
				else c = "AFAFAF";
				if(!i) format(mes,sizeof(mes),"{%s}%d. %s",c, i+1, HouseImproveName[i]);
				else format(mes,sizeof(mes),"%s\n{%s}%d. %s",mes, c, i+1, HouseImproveName[i]);
			}
		    ShowPlayerDialogEx(playerid, 176, DIALOG_STYLE_LIST, !"Улучшения", mes, !"Купить", !"Отмена");
		}

		case 207:
		{
		    if(response) StopAudioStreamForPlayer(playerid);
		    //callcmd::phone(playerid, "");
		}
		case 211:
		{
		    if(response)
		    {
		        if(!strlen(inputtextsave))
					return ShowPlayerDialogEx(playerid, 211, 1, !"{74FFA0}Авторизация", !"{FFFFFF}Введите админ-пароль:", !"ОК", !"Отмена");
					
		        if(!GetString(ADMPASSWORD,inputtextsave))
		        {
		            J_Kick(playerid);
		            return 1;
		        }
		        
		       	switch(PI[playerid][pAdmin])
		        {
					case 1..5: SCM(playerid, COLOR_YELLOW, !"Вы вошли как Администратор");
					case 6: SCM(playerid, COLOR_YELLOW, !"Вы вошли как Главный Администратор");
        			case 7: SCM(playerid, COLOR_YELLOW, !"Вы вошли как Разработчик проекта");
		        }

				new
					city[102],
					country[201],
					regcity[102],
					regcountry[201],
					frmt_alogin_info[160];
					
				GetIPCountry(PlayerIp[playerid], country, sizeof(country));
				GetIPCity(PlayerIp[playerid], city, sizeof(city));
				
				GetIPCountry(PlayerRegIP[playerid], regcountry, sizeof(regcountry));
				GetIPCity(PlayerRegIP[playerid], regcity, sizeof(regcity));

				
			    format(frmt_alogin_info, sizeof frmt_alogin_info, "[A] %s авторизовался [RegIP: %s] [IP: %s] ...", PN(playerid), PlayerRegIP[playerid], PlayerIp[playerid]);
			    
				if(PI[playerid][pAdmin] < 6)
					SendAdminsMessage(0xC3EF15FF, frmt_alogin_info, 1);
					
                frmt_alogin_info[0] = EOS;
			    
				format(frmt_alogin_info, sizeof frmt_alogin_info, "... [%s %s] [%s %s]", country, city, regcountry, regcity);
				
				if(PI[playerid][pAdmin] < 6)
					SendAdminsMessage(0xC3EF15FF, frmt_alogin_info, 1);

					
                if(!Iter_Contains(Connect_Admin, playerid)) Iter_Add(Connect_Admin, playerid);
                
				ADuty[playerid] = 228;
				if(PI[playerid][pFamily]) gFamily[PI[playerid][pFamily]-1][fOnline]++;
		    }
		    else
		    {
		        J_Kick(playerid);
		        return 1;
		    }
		}
		case 213:
		{
		    if(!response)
		    {
		        J_Kick(playerid);
		        return 1;
			}
			
	        if(!strlen(inputtextsave))
				return ShowPlayerDialogEx(playerid, 213, DIALOG_STYLE_INPUT, !"Авторизация", !"{FFFFFF}Введите код, отправленный ботом ВКонтакте", !"ОК", !"Отмена");
				
	        if(temp_tester_code[playerid] != strval(inputtextsave))
	        {
	            J_Kick(playerid);
	            SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверный код!");
	            return 1;
	        }
	        
	        SendClientMessage(playerid, COLOR_YELLOW, !"Вы вошли как тестер проекта");
	        temp_tester_code[playerid] = 0;
			new color;
			
			switch(PI[playerid][pID])
			{
				case 62: color = 0xFFF312FF;
				case 63: color = 0xFF1255FF;
				case 64: color = 0xE3A0FbFF;
				case 65: color = 0xEA9A85FF;
				case 66: color = 0x8F8E6AFF;
				case 67: color = 0xA9A2ADFF;
				case 68: color = 0xD1999FFF;
				case 69: color = 0xEFC8ECFF;
				case 70: color = 0x272222FF;
				case 73: color = 0x3ACD7FFF;
			}
	        PlayerTextDrawColor(playerid, striplogo[playerid], color);

			PlayerTextDrawShow(playerid, striplogo[playerid]);
		}
		case 348:
		{
		    if(!response)
		        return 1;

            if(listitem == 0)
            	ShowPlayerDialogEx(playerid, 349, DIALOG_STYLE_MSGBOX, !"Инструкция", !"{FFFFFF}Горячие клавиши:\n\n{008080}Escape {FFFFFF}- чтобы выйти из редактора,\nили выбора объекта\n{008080}Shift {FFFFFF}- чтобы вращать камеру\nво время редактирования", !"Готово", !"Назад");

            else if(listitem == 1)
            	ShowPlayerDialogEx(playerid, 350, DIALOG_STYLE_INPUT, !"Создание объекта", !"{FFFFFF}Введите ID модели объекта для того чтобы его создать\nОбъект появится перед вами, далее вы будете изменять его\n\nМаксимальный ID объекта - 19469", !"Создать", !"Назад");

			else if(listitem == 2)
			    SelectObject(playerid);

			else if(listitem == 3)
				ShowPlayerDialogEx(playerid, 351, DIALOG_STYLE_MSGBOX, !"Удаление объектов", !"{FFFFFF}Удалить все созданные объекты?", !"Готово", !"Назад");

		}
		case 349:
		{
		    if(!response)
		        return callcmd::lego1(playerid);
		}
		case 350:
		{
		    if(!response)
		        return callcmd::lego1(playerid);

            if(!strval(inputtext))
                return ShowPlayerDialogEx(playerid, 350, DIALOG_STYLE_INPUT, !"Создание объекта", !"{FFFFFF}Введите ID модели объекта для того чтобы его создать\nОбъект появится перед вами, далее вы будете изменять его\n\nМаксимальный ID объекта - 19469", !"Создать", !"Назад");

			new
				Float:X,
				Float:Y,
				Float:Z;
			GetPlayerPos(playerid, X, Y, Z);

			new
				objectid = CreateDynamicObject(strval(inputtext), X+1, Y+1, Z+1, 0.0,0.0,0.0);

			EditDynamicObject(playerid, objectid);
			SetPVarInt(playerid, "DynamicModelID", strval(inputtext));
			CreatedObject[objectid] = true;
			
		}
		case 353:
		{
			new
				objectid = GetPVarInt(playerid, "SelectedObject");

			if(response)
				EditObject(playerid, objectid);

			else
				DestroyObject(objectid) && CancelEdit(playerid);

		}
		case 354:
		{
			new
				objectid = GetPVarInt(playerid, "SelectedDynamicObject");

			if(response)
				EditDynamicObject(playerid, objectid);
				

			else
			{
				DestroyDynamicObject(objectid) && CancelEdit(playerid);
				
				new
					Float:rx,
					Float:ry,
					Float:rz;
					
                GetDynamicObjectRot(objectid, rx, ry, rz);

                
				new File:File_read = fopen("edit.txt", io_read);
				
				new object_list[2480], tempstring[200];
				
				new length = flength(File_read);
				for(new i; i < length; i++)
				{
					fread(File_read, tempstring);
					strcat(object_list, tempstring);
				}

				fclose(File_read);
				
				new File:File = fopen("edit.txt", io_write);
				
				new striRng[2480];
				format(striRng, sizeof(striRng),"%sCreateDynamicObject(%d, %f, %f, %f, %f, %f, %f);\n", object_list, GetPVarInt(playerid, "DynamicModelID"), gLegoObject[objectX], gLegoObject[objectY], gLegoObject[objectZ], rx, ry, rz);

				fwrite(File, striRng);
				fclose(File);
			}
		}
		case 351:
		{
		    if(!response)
		        return callcmd::lego1(playerid);

			for(new i = 0; i < MAX_OBJECTS; i++)
			{
				if(CreatedObject[i] == true)
					DestroyDynamicObject(i);
	  		}

		    SendClientMessage(playerid, COLOR_WHITE, !"Вы удалили созданые объекты");
		}
		case 216:
	    {
			if(response) ShowPlayerDialogEx(playerid,217,2,"Общак","{42B02C}-{FFFFFF} Положить наркотики\n{42B02C}-{FFFFFF} Положить патроны\n{42B02C}-{FFFFFF} Достать наркотики\n{42B02C}-{FFFFFF} Достать патроны\n{42B02C}-{FFFFFF} Положить канистру\n{42B02C}-{FFFFFF} Достать канистру\n{42B02C}-{FFFFFF} Положить наборы для починки\n{42B02C}-{FFFFFF} Достать наборы для починки\n{42B02C}-{FFFFFF} Положить маски\n{42B02C}-{FFFFFF} Достать маски\n \nВзять организационное оружие","Выбор","Назад");
		}
		
		case 189:
		{
		    if(!response) return 1;
			if(!PI[playerid][pDisease]) return 1;
					
			new
			    Float:pos_x,
			    Float:pos_y,
			    Float:pos_z,
				vacid = PI[playerid][pDisease]-1;

			if(PI[playerid][pMoney] < gDiseasePrice[vacid]) return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточно денег");
			GetPlayerPos(playerid, pos_x, pos_y, pos_z);
			
		    temp_disease_text[playerid] = Create3DTextLabel("_", 0xFFFFFFFF, pos_x, pos_y, pos_z+1.3, 10.0, playerid);
            Attach3DTextLabelToPlayer(temp_disease_text[playerid], playerid, 0.0, 0.0, 0.4);
			if(PI[playerid][pDisease] == 1 || PI[playerid][pDisease] == 2)
			{
				Update3DTextLabelText(temp_disease_text[playerid], 0x6699CCFF, "Требуется укол");
				temp_inject_need[playerid] = true;
			}
			
			else if(PI[playerid][pDisease] == 3 || PI[playerid][pDisease] == 4 || PI[playerid][pDisease] == 5 || PI[playerid][pDisease] == 6)
			{
				Update3DTextLabelText(temp_disease_text[playerid], 0x6699CCFF, "Требуется операция");
				temp_operation_need[playerid] = true;
			}
			SendClientMessage(playerid, COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Вы начали лечение, дожидайтесь врача или отправляйтесь в операционную");
			GiveMoney(playerid, -gDiseasePrice[vacid], "лечение болезни");
		}
		case 188:
		{
		    if(!response) return 1;
			new receiver = temp_vac_receiver[playerid]-1;

			if(!IsPlayerConnected(receiver)) return 1;
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver)) return 1;
			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 188, DIALOG_STYLE_LIST, !"Вакцинация", !"Выберите болезнь:\nАнгина\nБронхит\nЯзва желудка\nРевматизм\nАртрит\nАнемия", !"Выбор", !"Отмена");
				case 1..6:
				{
				    if(PI[receiver][pVaccine][listitem-1] > 0)
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже имеется вакцина на выбранную болезнь");

					new
						mes[155];

					format(mes, sizeof mes, "%s предлагает Вам пройти вакцинацию от болезни %s за 1500$", PN(playerid), gDiseaseName[listitem-1]);
					SendClientMessage(receiver, 0x269BD8FF, mes);
					SendClientMessage(receiver, COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");
					
					format(mes, sizeof mes, "Вы предложили %s пройти вакцинацию от болезни за 1500$", PN(receiver), gDiseaseName[listitem-1]);
					SendClientMessage(playerid, 0x269BD8FF, mes);
					
					temp_vac_sender[receiver] = playerid + 1;
					temp_vac_id[receiver] = listitem;
					
				}
			}
		}
		case 190:
		{
		    if(!response) return 1;
			if(GetPlayerID(inputtext) == INVALID_PLAYER_ID) return 1;
			new receiver = GetPlayerID(inputtext);

			if(GetPlayerDistanceToPlayer(playerid, receiver) > 7.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок слишком далеко от вас");
			temp_operation_need[receiver] = false;
			temp_inject_need[receiver] = false;
			
			
			new str[100];
			format(str,sizeof str,"{FFC800}[Подсказка] {FFFFFF}%s начал лечение",PN(playerid));
			SendClientMessage(receiver,COLOR_WHITE,str);
			
			SendClientMessage(playerid,COLOR_WHITE,!"{FFC800}[Подсказка] {FFFFFF}Вы начали проводить лечение");
			J_SetPlayerPos(receiver,698.2794,1515.6704,1310.5159);
			J_SetPlayerFacingAngle(receiver,268.8108);
			TogglePlayerControllable(receiver,false);
			GoAnim(receiver,"CRACK","Crckidle1",4.1,1,0,0,0,10000,0);// для пациента лежит на тележке
			
            ApplyAnimation(playerid, !"CAR_CHAT", !"CAR_Sc4_BL", 4.0, 1, 1, 1, 0, 10000, 1);
            SetTimerEx("@__OperationReady",9000, false, "ii", receiver, playerid);
		}
		case 615:
		{
		    if(!response) return 1;
			if(listitem == 0) ShowPlayerDialogEx(playerid, 503, DIALOG_STYLE_INPUT, !"Полиция", !"\n\nЗдравствуйте, опишите ситуацию:\n\n", !"Далее", !"Отмена");
			else if(listitem == 1) ShowPlayerDialogEx(playerid, 616, DIALOG_STYLE_INPUT, !"Скорая помощь", !"\n\nЗдравствуйте, опишите ситуацию:\n\n", !"Далее", !"Отмена");
			else if(listitem == 2) ShowPlayerDialogEx(playerid, 5566, DIALOG_STYLE_INPUT, !"Механики", !"{FFFFFF}\nОпишите ситуацию:\n", !"Далее", !"Отмена");
			return 1;
		}
		case 616:
		{
		    if(!response)
				return 1;

			if(strlen(inputtext) > 32)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинная причина");

			new Float:x, Float:y, Float:z, pos[5];
			GetPlayerPos(playerid, x, y, z);
			if(x < 0) strcat(pos, "SF");
			else if(y > 100.0) strcat(pos, "LV");
			else strcat(pos, "LS");
    		foreach(new i : Player)
			{
				if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
					continue;
					
				if(PI[i][pFraction] != 1)
					continue;
					
				new mes[128];
				format(mes,sizeof(mes),"[Внимание] %s вызывает скорую помощь (%s). Чтобы принять вызов введите {FFFFFF}/mc",PN(playerid),pos);
				SendClientMessage(i,0x007FFFFF,mes);
				format(mes,sizeof(mes),"[Внимание] Причина вызова: %s",inputtext);
				SendClientMessage(i,0x007FFFFF,mes);

			}
			gEmCall[1] = playerid;
			ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Скорая помощь", !"{FFFFFF}Ваш вызов принят. Ожидайте помощь", !"ОК", !"");
		}
		case 503:
		{
		    if(!response)
				return 1;

			if(strlen(inputtext) > 32)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинная причина");


			new Float:x, Float:y, Float:z, pos[5];
			GetPlayerPos(playerid, x, y, z);
			if(x < 0) strcat(pos, "SF");
			else if(y > 100.0) strcat(pos, "LV");
			else strcat(pos, "LS");
    		foreach(new i : Player)
			{
				if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
					continue;

				if(!IsACop(i))
					continue;
					
				new mes[128];
				format(mes,sizeof(mes),"[Внимание] %s вызывает полицию/фбр (%s). Чтобы принять вызов введите {FFFFFF}/pc",PN(playerid),pos);
				SendClientMessage(i,0x007FFFFF,mes);
				format(mes,sizeof(mes),"[Внимание] Причина вызова: %s",inputtext);
				SendClientMessage(i,0x007FFFFF,mes);

			}
			gEmCall[0] = playerid;
			ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Полиция", !"{FFFFFF}Ваш вызов принят. Ожидайте", !"ОК", !"");
		}
		case 504:
		{
		    if(!response) return 1;
		    
			if(timeforcd[playerid] > gettime()) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы уже вызывали такси, ожидайте!");
			if(strlen(inputtext) > 32) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинная причина");
		
			new
			    frmt_taxi_message[102];
			    
    		foreach(new i : Player)
			{
				if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
					continue;

				if(PI[i][pJob] != 2)
					continue;

				format(frmt_taxi_message, sizeof frmt_taxi_message, "[TAXI] %s вызывает такси. Местоположение: %s", PN(playerid), inputtext);
				SendClientMessage(i, 0xFFA700FF, frmt_taxi_message);
				
			}
			timeforcd[playerid] = gettime() + 60;
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы вызвали такси. Ожидайте");
		}
		case 5568:
		{
		    if(!response) return 1;
		    new fillingid = GetPVarInt(playerid,"FillID");
		    new price = floatround(gFillings[fillingid][fillingFuelPrice] * strval(inputtext));
			if(!isNumeric(inputtext)) return SCM(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Для ввода доступны только цифры ");
		    if(gFillings[fillingid][fillingFuel] < strval(inputtext)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На АЗС нету топлива");
		    if(pTemp[playerid][pMechFuel] + strval(inputtext) > 500 || pTemp[playerid][pMechFuel] + strval(inputtext) < 1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}От 1 до 500 л вмещается в авто!");
		    if(GetMoney(playerid) < price) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас не хватает денег.");
		    
			totalstring[0] = 0;
			format(totalstring, 144,"{7AC71F}[Успешно] {FFFFFF}Вы купили {FFC800}%d литров{ffffff} бензина за %d$",strval(inputtext),price);
			SendClientMessage(playerid, COLOR_WHITE, totalstring);
			totalstring[0] = 0;

			pTemp[playerid][pMechFuel] += strval(inputtext);

			new mes[30];
			format(mes,sizeof mes,"Бензин: %d/500",pTemp[playerid][pMechFuel]);
			UpdateDynamic3DTextLabelText(pTemp[playerid][pMechText],0xFFFFFFFF,mes);

			temp_filling_price[playerid] = price;
			if(!GetString(gFillings[fillingid][fillingOwner], "The State"))
				GiveFillingMoney(fillingid, temp_filling_price[playerid]);

			if(!GetString(gFillings[fillingid][fillingOwner], "The State"))
				gFillings[fillingid][fillingFuel] -= floatround(strval(inputtext));

			SaveFilling(fillingid);
			
			GiveMoney(playerid, -temp_filling_price[playerid], "buy канистр. механик");
			DeletePVar(playerid,"FillID");
		    return 1;
		}
		case 5567:
		{
	        new vehicleid = GetPlayerVehicleID(playerid);
			if(GetMoney(playerid) < 200) return SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно денег");
			if(!response || vehicleid == INVALID_VEHICLE_ID) return RemovePlayerFromVehicle(playerid);
			pTemp[playerid][pMechID] = vehicleid;
			GiveMoney(playerid,-200);
			pTemp[playerid][pMechText] = CreateDynamic3DTextLabel("Бензин: 0/500",0xFFFFFFFF,0.0,0.0,2.0,20.0,INVALID_PLAYER_ID,pTemp[playerid][pMechID]);
			SendClientMessage(playerid,COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Вы арендовали авто. Чтобы загрузить канистры для продажи бензина используйте {FFC800}/buyfuel {ffffff}на заправке");
			SendClientMessage(playerid,COLOR_WHITE,"{FFC800}[Подсказка] {FFFFFF}Используйте {FFC800}/refill {ffffff}чтобы заправить авто, {FFC800}/repair{ffffff} для починки авто");
			return 1;
		}
		case 5566:
		{
			new total = 0;
			if(GetPVarInt(playerid, "CallMech") > gettime()) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Диспетчер]: {ffffff}Извините, но вы уже вызывали механиков. (Доступно раз в минуту)");
			foreach(new i:Player)
			{
				if(IsPlayerLogged[i] == false || i == playerid || GetPlayerState(i) != 2 || GetVehicleModel(GetPlayerVehicleID(i)) != 552) continue;
				if(PI[i][pJob] == JOB_MECHANIC/* && IsPlayerInRangeOfPlayer(500.0, playerid, i)*/) // Вызов механика;
				{
					total++;
					MechCall = playerid;
					new lstring[144];
					format(lstring, sizeof(lstring), "{FFC800}[Диспетчер]: {ffffff}Поступил вызов от {FFC800}%s, {ffffff}в {FFC800}%.1f метрах от вас.", PN(playerid), GetDistanceBetweenPlayers(playerid, i));
					SCM(i, COLOR_WHITE, lstring);
					SCM(i, 0x269BD8FF, "Чтобы принять вызов нажмите {33AA33}'Y'{269BD8}, если вы хотите отказаться нажмите {FF0000}'N'");
					SetPVarInt(i, "NeedMech", 1);
     				SetPVarInt(playerid, "CallMech", gettime() + 30);
				}
			}
			if(total == 0) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Диспетчер]: {ffffff}Извините, но в данный момент нет механиков на дежурстве.");
			SCM(playerid, COLOR_WHITE, !"{7AC71F}[Диспетчер]: {ffffff}Ваш запрос отправлен, ожидайте ответа.");
		}
		case 1691:
		{
		    if(response)
		    {
			 	switch(listitem)
		        {
		            case 0:
		            {
						new frmt_item[200];
				    	for(new i; i < 5; i++)
		                {
							if(inventory_head[playerid][i])
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} %d\n", frmt_item, i+1, inventory_head[playerid][i]);

							else
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} Пустой слот\n", frmt_item, i+1);
						}
                        ShowPlayerDialogEx(playerid, 1692, DIALOG_STYLE_LIST, !"Головные уборы", frmt_item, !"Далее", !"Назад");
		            }
		            case 1:
		            {
		                new frmt_item[200];
				    	for(new i ; i < 5; i++)
		                {
							if(inventory_glass[playerid][i])
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} %d\n", frmt_item, i+1, inventory_glass[playerid][i]);

							else
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} Пустой слот\n", frmt_item, i+1);
						}
                        ShowPlayerDialogEx(playerid, 1693, DIALOG_STYLE_LIST, !"Очки", frmt_item, !"Далее", !"Назад");
					}
		            case 2:
		            {
		                new frmt_item[200];
				    	for(new i ; i < 5; i++)
		                {
							if(inventory_watch[playerid][i])
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} %d\n", frmt_item, i+1, inventory_watch[playerid][i]);

							else
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} Пустой слот\n", frmt_item, i+1);
						}
                        ShowPlayerDialogEx(playerid, 1694, DIALOG_STYLE_LIST, !"Наручные часы", frmt_item, !"Далее", !"Назад");
		            }
		            case 3:
		            {
		                new frmt_item[200];
				    	for(new i ; i < 5; i++)
		                {
							if(inventory_mask[playerid][i])
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} %d\n", frmt_item, i+1, inventory_mask[playerid][i]);

							else
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} Пустой слот\n", frmt_item, i+1);
						}
                        ShowPlayerDialogEx(playerid, 1695, DIALOG_STYLE_LIST, !"Бандана", frmt_item, !"Далее", !"Назад");
		            }
		            case 4:
		            {
		                new frmt_item[200];
				    	for(new i ; i < 5; i++)
		                {
							if(inventory_hp[playerid][i])
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} %d\n", frmt_item, i+1, inventory_hp[playerid][i]);

							else
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} Пустой слот\n", frmt_item, i+1);
						}
                        ShowPlayerDialogEx(playerid, 1696, DIALOG_STYLE_LIST, !"Наушники", frmt_item, !"Далее", !"Назад");
		            }
		            case 5:
		            {
		                new frmt_item[200];
				    	for(new i ; i < 5; i++)
		                {
							if(inventory_bag[playerid][i])
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} %d\n", frmt_item, i+1, inventory_bag[playerid][i]);

							else
								format(frmt_item, sizeof frmt_item, "%s%d.{FFFFFF} Пустой слот\n", frmt_item, i+1);
						}
                        ShowPlayerDialogEx(playerid, 1697, DIALOG_STYLE_LIST, !"Сумки", frmt_item, !"Далее", !"Назад");
					}
			    }
			}
		}
		case 1692:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0..4:
				    {
						if(!inventory_head[playerid][listitem])
						    return Myitems(playerid);
						    
						if(PI[playerid][pSlotItem][0] == inventory_head[playerid][listitem])
							ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Снять\n2. Выбросить", !"Далее", !"Назад");
                        
                        else
                            ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Надеть\n2. Выбросить", !"Далее", !"Назад");
                            
                        temp_sel_accs_id[playerid] = inventory_head[playerid][listitem];
                        temp_sel_accs_slot[playerid] = 1;
                        temp_sel_accs_num[playerid] = listitem+1;
				    }
				}
			}
			else Myitems(playerid);
		}
		case 1693:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0..4:
				    {
						if(!inventory_glass[playerid][listitem])
						    return Myitems(playerid);

						if(PI[playerid][pSlotItem][1] == inventory_glass[playerid][listitem])
							ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Снять\n2. Выбросить", !"Далее", !"Назад");

                        else
                            ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Надеть\n2. Выбросить", !"Далее", !"Назад");

                        temp_sel_accs_id[playerid] = inventory_glass[playerid][listitem];
                        temp_sel_accs_slot[playerid] = 2;
                        temp_sel_accs_num[playerid] = listitem+1;
				    }
				}
			}
			else Myitems(playerid);
		}
		case 1694:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0..4:
				    {
						if(!inventory_watch[playerid][listitem])
						    return Myitems(playerid);
				    
						if(PI[playerid][pSlotItem][2] == inventory_watch[playerid][listitem])
							ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Снять\n2. Выбросить", !"Далее", !"Назад");

                        else
                            ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Надеть\n2. Выбросить", !"Далее", !"Назад");

                        temp_sel_accs_id[playerid] = inventory_watch[playerid][listitem];
                        temp_sel_accs_slot[playerid] = 3;
                        temp_sel_accs_num[playerid] = listitem+1;
				    }
				}
			}
			else Myitems(playerid);
		}
		case 1695:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0..4:
				    {
						if(!inventory_mask[playerid][listitem])
						    return Myitems(playerid);
						    
						if(PI[playerid][pSlotItem][3] == inventory_mask[playerid][listitem])
							ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Снять\n2. Выбросить", !"Далее", !"Назад");

                        else
                            ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Надеть\n2. Выбросить", !"Далее", !"Назад");

                        temp_sel_accs_id[playerid] = inventory_mask[playerid][listitem];
                        temp_sel_accs_slot[playerid] = 4;
                        temp_sel_accs_num[playerid] = listitem+1;
				    }
				}
			}
			else Myitems(playerid);
		}
		case 1696:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0..4:
				    {
						if(!inventory_hp[playerid][listitem])
						    return Myitems(playerid);
						    
						if(PI[playerid][pSlotItem][4] == inventory_hp[playerid][listitem])
							ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Снять\n2. Выбросить", !"Далее", !"Назад");

                        else
                            ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Надеть\n2. Выбросить", !"Далее", !"Назад");

                        temp_sel_accs_id[playerid] = inventory_hp[playerid][listitem];
                        temp_sel_accs_slot[playerid] = 5;
                        temp_sel_accs_num[playerid] = listitem+1;
				    }
				}
			}
			else Myitems(playerid);
		}
		case 1697:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0..4:
				    {
						if(!inventory_bag[playerid][listitem])
						    return Myitems(playerid);
				    
						if(PI[playerid][pSlotItem][5] == inventory_bag[playerid][listitem])
							ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Снять\n2. Выбросить", !"Далее", !"Назад");

                        else
                            ShowPlayerDialogEx(playerid, 1698, DIALOG_STYLE_LIST, !"Взаимодействие с аксессуаром", !"1. Надеть\n2. Выбросить", !"Далее", !"Назад");

                        temp_sel_accs_id[playerid] = inventory_bag[playerid][listitem];
                        temp_sel_accs_slot[playerid] = 6;
                        temp_sel_accs_num[playerid] = listitem+1;
				    }
				}
			}
			else Myitems(playerid);
		}
		case 1698:
		{
		    if(!response)
		        return Myitems(playerid);
		        
			new
			    slot_id = temp_sel_accs_slot[playerid]-1,
				num = temp_sel_accs_num[playerid]-1;
			    
			if(listitem == 0)
			{
			    if(PI[playerid][pSlotItem][slot_id] == temp_sel_accs_id[playerid])
			    {
			        PI[playerid][pSlotItem][slot_id] = 0;

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сняли надетый на Вас аксессуар.");
					callcmd::inv(playerid);
					
					if(IsPlayerAttachedObjectSlotUsed(playerid, slot_id))
						RemovePlayerAttachedObject(playerid, slot_id);

                    temp_sel_accs_slot[playerid] = 0;
                    temp_sel_accs_id[playerid] = 0;
                    temp_sel_accs_num[playerid] = 0;
			    }
			    else if(PI[playerid][pSlotItem][slot_id] != temp_sel_accs_id[playerid])
			    {
			        PI[playerid][pSlotItem][slot_id] = temp_sel_accs_id[playerid];

					if(IsPlayerAttachedObjectSlotUsed(playerid, slot_id))
						RemovePlayerAttachedObject(playerid, slot_id);

					GiveItem(playerid, PI[playerid][pSlotItem][slot_id]);
            		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы надели выбранный аксессуар.");
            		
                    temp_sel_accs_slot[playerid] = 0;
                    temp_sel_accs_id[playerid] = 0;
                    temp_sel_accs_num[playerid] = 0;
			    }
			}
			else if(listitem == 1)
			{
				if(PI[playerid][pSlotItem][slot_id] == temp_sel_accs_id[playerid])
				{
				    PI[playerid][pSlotItem][slot_id] = 0;
				    
					if(IsPlayerAttachedObjectSlotUsed(playerid, slot_id))
						RemovePlayerAttachedObject(playerid, slot_id);
				}
				
			    switch(slot_id)
			    {
			        case 0: inventory_head[playerid][num] = 0;
			        case 1: inventory_glass[playerid][num] = 0;
			        case 2: inventory_watch[playerid][num] = 0;
			        case 3: inventory_mask[playerid][num] = 0;
			        case 4: inventory_hp[playerid][num] = 0;
			        case 5: inventory_bag[playerid][num] = 0;
			        default: return SendClientMessage(playerid, COLOR_RED, !"Ошибка при выбросе аксессуара");
			    }
			    
			    SaveAccessories(playerid);

			    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выбросили выбранный аксессуар.");
			    
                temp_sel_accs_slot[playerid] = 0;
                temp_sel_accs_id[playerid] = 0;
                temp_sel_accs_num[playerid] = 0;
			}
		}
		case 5872:
		{
		    if(response)
		    {
		        switch(listitem)
		        {
		            case 0:
		            {
		                PI[playerid][pRadio] = 1;
		                UpdatePlayerData(playerid, "Radio", PI[playerid][pRadio]);
		                SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы переключились на радиостанцию ЛС");
		            }
		            case 1:
		            {
		                PI[playerid][pRadio] = 2;
		                UpdatePlayerData(playerid, "Radio", PI[playerid][pRadio]);
		                SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы переключились на радиостанцию СФ");
		            }
		            case 2:
		            {
		                PI[playerid][pRadio] = 3;
		                UpdatePlayerData(playerid, "Radio", PI[playerid][pRadio]);
		                SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы переключились на радиостанцию ЛВ");
		            }
		        }
		    }
		}

		case 6971:
		{
		    if(response)
		    {
				switch(listitem)
				{

				}
		    }
		}

		case 94:
		{
		    if(!response)
		        return 1;
		        
		    switch(listitem)
		    {
		        case 0: PlayAudioStreamForPlayer(playerid, "https://zaycevfm.cdnvideo.ru/ZaycevFM_pop_128.mp3");
				case 1: PlayAudioStreamForPlayer(playerid, "http://www.radioroks.com.ua/RadioROKS.m3u");
				case 2: PlayAudioStreamForPlayer(playerid, "http://radiopotok.ru/f/m3u/station_2.m3u");
				case 3: PlayAudioStreamForPlayer(playerid, "http://online.radiorecord.ru:8101/rr_128");
				case 4: PlayAudioStreamForPlayer(playerid, "http://striiming.trio.ee/dfm64.mp3.m3u");
				case 5: PlayAudioStreamForPlayer(playerid, "http://ep256.hostingradio.ru:8052/europaplus256.mp3");
		    }
 			SendClientMessage(playerid, COLOR_GREEN, !"Онлайн радио включено. Для выключения введите /stop");
		}
		case 536:
		{
		    if(!response)
	 			return callcmd::store(playerid);
	 			
			new cnt;
			new houseid = PI[playerid][pHouseKey] - 1;
			for(new i;i<=11;i++)
			{
				new gunid,ammo,storeslot;
				GetPlayerWeaponData(playerid,i,gunid,ammo);
				storeslot = GetStoreGunSlot(gunid);
				if(!gunid || storeslot == -1 || ammo <= 0) continue;
				if(listitem == cnt)
				{
					new cnt2;
					for(new i2;i2<8;i2++) if(HouseInfo[houseid][hGun][i2] && storeslot != i2) cnt2++;
					if(cnt2 >= 3)
					{
						SendClientMessage(playerid, COLOR_GREY, !"Вы не можете хранить больше 3-х видов оружия в шкафу");
						return callcmd::store(playerid);
					}
					if(HouseInfo[houseid][hGun][storeslot] + ammo > 10000) return SendClientMessage(playerid, COLOR_WHITE, !"У Вас в шкафу максимальное к-во патронов данного оружия");
					HouseInfo[houseid][hGun][storeslot] += ammo;
					SaveStoreGun(houseid);
					UpdateHouseGun(houseid);

                    new slot = GetWeaponSlot(gunid);
                    SetPlayerAmmo(playerid, gunid, 0);
                    
					gunmute[playerid] = gettime()+3;

				    WeaponInfo[playerid][gunid] = true;
				    AmmoSlot[playerid][slot] = 0;
				    AmmoInfo[playerid][gunid] = AmmoSlot[playerid][slot];

					PI[playerid][pAmmos][slot] = 0;
					PI[playerid][pGuns][slot] = gunid;
					

					SendClientMessage(playerid, COLOR_GREEN, !"Вы положили оружие в шкаф");
					SetTimerEx("ShowGunList",500, false, "i", playerid);
					break;
				}
				cnt++;
			}
		}
		case 537:
		{
		    if(!response)
	 			return 1;

			new ammo = strval(inputtext);
			new storeslot = PI[playerid][pStoreGun];
			new houseid = PI[playerid][pHouseKey] - 1;
			if(ammo < 1)
			{
				new gunname[32],mes[128];
				GetWeaponName(HintGunID[storeslot],gunname,32);
				format(mes,sizeof(mes),"{FFFFFF}Укажите сколько патронов{33AA33}%s{FFFFFF} Вы хотите взять:");
				ShowPlayerDialogEx(playerid,537,1,"Шкаф",mes,"Взять","Отмена");
				return SendClientMessage(playerid,COLOR_GREEN,"Нельзя брать меньше 1 патрона");
			}
			if(ammo > HouseInfo[houseid][hGun][storeslot])
			{
				new gunname[32],mes[128];
				GetWeaponName(HintGunID[storeslot],gunname,32);
				format(mes,sizeof(mes),"{FFFFFF}Укажите сколько патронов{33AA33}%s{FFFFFF} Вы хотите взять:");
				ShowPlayerDialogEx(playerid,537,1,"Шкаф",mes,"Взять","Отмена");
				return SendClientMessage(playerid,COLOR_GREEN,"Недостаточно патронов в шкафу");
			}
			HouseInfo[houseid][hGun][storeslot] -= ammo;
			SaveStoreGun(houseid);
			UpdateHouseGun(houseid);
			_GiveGun(playerid, GetStoreGunID(storeslot), ammo);
			GameTextForPlayer(playerid," ",100,3);

			new active=-1;
			for(new i;i<8;i++) if(HouseInfo[houseid][hGun][i]) active = i;
			if(active == -1)
			{
				SendClientMessage(playerid,COLOR_GREY,"В шкафу больше нет оружия");
				new Float:x, Float:y, Float:z, Float:x1, Float:y1, Float:z1;
				x = GetPVarFloat(playerid,"oldcx");
				y = GetPVarFloat(playerid,"oldcy");
				z = GetPVarFloat(playerid,"oldcz");
				GetPlayerCameraPos(playerid,x1,y1,z1);
				InterpolateCameraPos(playerid,x1,y1,z1,x,y,z,700,CAMERA_MOVE);
				SetTimerEx("SetCameraBehindPlayerDelay",1000,false,"i",playerid);

				PI[playerid][pSelectStoreGun] = false;
				PI[playerid][pStoreGun] = 0;
				GameTextForPlayer(playerid," ",100,3);
				TogglePlayerControllable(playerid,1);
			}
		}
		case 538:
		{
		    if(!response)
	 			return callcmd::store(playerid);

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintStoreArea[hintid]))
				return 1;

			new houseid = PI[playerid][pHouseKey] - 1,
				id,
				skin;
			

		    SetPlayerColor(playerid,0xffffff11);
			sscanf(inputtext,"{s[100]}i",id);
			skin = HouseInfo[houseid][hSkin][id-1];

			PI[playerid][pSkin] = skin;
			UpdatePlayerData(playerid, "skin", skin);
            UpdateHouseDress(playerid);

			SetPlayerSkinEx(playerid, skin);

			new frmt_clother_store[128],cnt;
			for(new i; i < 4; i++)
			{
				if(HouseInfo[houseid][hSkin][i])
				{
					format(frmt_clother_store, sizeof frmt_clother_store, "%sОдежда %d [ID: %d]\n", frmt_clother_store, i+1, HouseInfo[houseid][hSkin][i]);
				}
				else continue;
				cnt++;
			}
			if(!cnt)
			{
				SendClientMessage(playerid,COLOR_GREY,"Нет одежды в шкафу");
				return callcmd::store(playerid);
			}
			ShowPlayerDialogEx(playerid, 538, DIALOG_STYLE_LIST, !"Шкаф", frmt_clother_store, !"Надеть", !"Отмена");
		}
		case 539:
		{
		    if(!response)
	 			return callcmd::store(playerid);
	 			
			if(!PI[playerid][pHouseKey])
			    return 1;

            new skin_slot;
            
            sscanf(inputtext, "{s[7]}d{s[10]d}", skin_slot);
            
			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintStoreArea[hintid]))
				return 1;

			new houseid = PI[playerid][pHouseKey] - 1;
            
            UpdateHouseDress(houseid);

			new cnt = 0;
			
			for(new l; l < 4 ; l++)
			{
				if(HouseInfo[houseid][hSkin][l])
					cnt++;
			}
			cnt--;
			
			if(cnt < 1)
			{
				if(IsValidDynamicObject(HintDressObject[houseid][0]))
					DestroyDynamicObject(HintDressObject[houseid][0]);
			}
			
			else if(cnt < 2)
			{
				if(IsValidDynamicObject(HintDressObject[houseid][1]))
					DestroyDynamicObject(HintDressObject[houseid][1]);
			}
			
			else if(cnt < 3)
			{
				if(IsValidDynamicObject(HintDressObject[houseid][2]))
					DestroyDynamicObject(HintDressObject[houseid][2]);
			}
			
			HouseInfo[houseid][hSkin][skin_slot-1] = 0 ;
	
		    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выкинули выбранную одежду из шкафа");
		    
		}
		case 540:
		{
			if(!response) return 1;
			
			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintStoreArea[hintid]))
				return 1;

			switch(listitem)
			{
				case 0:
				{
					new houseid = PI[playerid][pHouseKey]-1;

					for( new i ; i < 8 ; i++ )
					{
						if(HouseInfo[houseid][hGun][i])
						{
							new
								Float:x,
								Float:y,
								Float:z,
								Float:x2,
								Float:y2,
								Float:z2;

							GetPlayerCameraPos(playerid,x,y,z);
							SetPVarFloat(playerid,"oldcx",x);
							SetPVarFloat(playerid,"oldcy",y);
							SetPVarFloat(playerid,"oldcz",z);
							GetGunCameraOffset(HintGun[hintid][i][0],HintGun[hintid][i][1],HintStore[hintid][5],x2,y2);
							z2 = HintGun[hintid][i][2] + 0.4;
							InterpolateCameraPos(playerid,x,y,z,x2,y2,z2,1000,CAMERA_MOVE);
							GetPlayerCameraFrontVector(playerid,x2,y2,z2);
							x += x2;
							y += y2;
							z += z2;
							InterpolateCameraLookAt(playerid,x,y,z,HintGun[hintid][i][0],HintGun[hintid][i][1],HintGun[hintid][i][2],1000,CAMERA_MOVE);
							PI[playerid][pSelectStoreGun] = true;
							PI[playerid][pStoreGun] = i;
							PI[playerid][pSelectStoreGun] = false;
							SetTimerEx("@__SelectStoreGun",1000, false, "i", playerid);
							SendClientMessage(playerid,COLOR_WHITE,"Используйте клавиши {33AA33}влево{FFFFFF} и {33AA33}вправо{FFFFFF} для выбора оружия");
							SendClientMessage(playerid,COLOR_WHITE,"Используйте клавишу {33AA33}входа / выхода из транспорта{FFFFFF} для выхода");
							SendClientMessage(playerid,COLOR_WHITE,"Используйте клавишу {33AA33}быстрого бега{FFFFFF} для подтверждения");
							new
								gunname[32],
								mes[48];

							GetWeaponName(GetStoreGunID(i),gunname,32);

							format(mes,48,"~w~%s (~g~%d~w~)",gunname,HouseInfo[houseid][hGun][i]);

							GameTextForPlayer(playerid,mes,100000,3);
							TogglePlayerControllable(playerid,0);
							return 1;
						}
					}
					return SendClientMessage(playerid,COLOR_GREY,"У Вас нет оружия в шкафу");
				}
				case 1:
				{
					ShowGunList(playerid);
				}
				case 2:
				{
					new
						houseid = PI[playerid][pHouseKey]-1,
				 		frmt_clother_store[128],
				 		cnt;

					for(new i; i < 4; i++)
					{
						if(HouseInfo[houseid][hSkin][i])
						{
							format(frmt_clother_store, sizeof frmt_clother_store, "%sОдежда %d [ID: %d]\n", frmt_clother_store, i+1, HouseInfo[houseid][hSkin][i]);
						}
						else continue;
						cnt++;
					}
					if(!cnt)
					{
						SendClientMessage(playerid,COLOR_GREY,"Нет одежды в шкафу");
						return callcmd::store(playerid);
					}
					ShowPlayerDialogEx(playerid, 538, DIALOG_STYLE_LIST, !"Шкаф", frmt_clother_store, !"Надеть", !"Отмена");
				}
				case 3:
				{
				    new
						houseid = PI[playerid][pHouseKey]-1,
			 			frmt_clother_store[128],
			 			cnt;

					for(new i;i<4;i++)
					{
					    if(HouseInfo[houseid][hSkin][i]) format(frmt_clother_store,sizeof frmt_clother_store,"%sОдежда %d [ID: %d]\n",frmt_clother_store,i+1,HouseInfo[houseid][hSkin][i]);
      					else continue;
						cnt++;
					}
					if(!cnt)
					{
						SendClientMessage(playerid,COLOR_GREY,"Нет одежды в шкафу");
						return callcmd::store(playerid);
					}
					ShowPlayerDialogEx(playerid, 539, DIALOG_STYLE_LIST, !"Шкаф",frmt_clother_store, !"Выкинуть", !"Отмена");
				}
			}
		}
		case 541:
		{
			if(!response) return 1;

			if(!PI[playerid][pHouseKey])
			    return 1;
			
			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;
			
			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;
				
			new houseid = PI[playerid][pHouseKey] - 1;
			
			if(!isNumeric(inputtext) || strlen(inputtext) != 4 || strval(inputtext) != HouseInfo[houseid][hSafeCode])
				return SendClientMessage(playerid, COLOR_GREY, !"Код введен неверно");
				
			new format_safe[140 + 6 + 8 + 9];
			format(format_safe,sizeof(format_safe),"{FFFFFF}Наркотики [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Материалы [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Деньги [{33aa33}%d$/1000000${FFFFFF}]", HouseInfo[houseid][hDrugs], HouseInfo[houseid][hMats], HouseInfo[houseid][hMoney]);
			ShowPlayerDialogEx(playerid, 542, DIALOG_STYLE_MSGBOX, !"Сейф", format_safe, !"Далее", !"Отмена");
		}
		case 542:
		{
			if(!response) return 1;
			
			if(!PI[playerid][pHouseKey])
			    return 1;
			    
			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;
				
			ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");
		}
		case 543:
		{
			if(!response)
			{
				new houseid = PI[playerid][pHouseKey] - 1;
				new format_safe[140 + 6 + 8 + 9];
				format(format_safe,sizeof(format_safe),"{FFFFFF}Наркотики [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Материалы [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Деньги [{33aa33}%d$/1000000${FFFFFF}]", HouseInfo[houseid][hDrugs], HouseInfo[houseid][hMats], HouseInfo[houseid][hMoney]);
				ShowPlayerDialogEx(playerid, 542, DIALOG_STYLE_MSGBOX, !"Сейф", format_safe, !"Далее", !"Отмена");

				return 1;
			}
			if(!PI[playerid][pHouseKey])
			    return 1;
			    
			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			switch(listitem)
			{
				case 0:	ShowPlayerDialogEx(playerid,544,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Укажите сумму, которую хотите положить в сейф:","Положить","Отмена");
				case 1: ShowPlayerDialogEx(playerid,545,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Укажите сумму, которую хотите взять из сейфа:","Взять","Отмена");
				case 2: ShowPlayerDialogEx(playerid,546,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Укажите к-во наркотиков, которое Вы хотите положить в сейф","Положить","Отмена");
				case 3: ShowPlayerDialogEx(playerid,547,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Укажите к-во наркотиков, которое Вы взять из сейфа","Взять","Отмена");
				case 4: ShowPlayerDialogEx(playerid,548,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Укажите к-во материалов, которое Вы хотите положить в сейф","Положить","Отмена");
				case 5: ShowPlayerDialogEx(playerid,549,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Укажите к-во материалов, которое Вы взять из сейфа","Взять","Отмена");
				case 6: ShowPlayerDialogEx(playerid,550,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Введите новый код от сейфа в формате \"{FF0000}XXXX{FFFFFF}\"","Изменить","Отмена");
			}
		}
		case 544:
		{
			if(!response) return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			new money = strval(inputtext);
			if(money < 1 || money > 1000000)
			{
				SendClientMessage(playerid,COLOR_GREY,"Неверная сумма");
				return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");
			}
			if(PI[playerid][pMoney] < money)
			{
				SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно денег");
				return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");
			}
			new houseid = PI[playerid][pHouseKey] - 1;
   			if(HouseInfo[houseid][hMoney] + money > 1000000)
			{
				SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно места в сейфе");
				return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");
			}
			HouseInfo[houseid][hMoney] += money;
			new query_safe_money_put[59 + 9 + 4];
			format(query_safe_money_put,sizeof(query_safe_money_put),"UPDATE `houses` SET `Money` = '%d' WHERE ID = '%d'", HouseInfo[houseid][hMoney], houseid+1);
			mysql_tquery(mysql, query_safe_money_put);
			
            GiveMoney(playerid, -money, "положил в сейф");
			ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");

		}
		case 545:
		{
			if(!response) return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;
				
			new money = strval(inputtext);
			if(money < 1 || money > 1000000)
			{
				SendClientMessage(playerid,COLOR_GREY,"Сумма должна быть от 1 до 1000000");
				return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");
			}
			new houseid = PI[playerid][pHouseKey] - 1;
			if(money > HouseInfo[houseid][hMoney])
			{
				SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно денег в сейфе");
				return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");
			}
			HouseInfo[houseid][hMoney] -= money;
			new query_safe_money_get[59 + 9 + 4];
			format(query_safe_money_get,sizeof(query_safe_money_get),"UPDATE `houses` SET `Money` = '%d' WHERE ID = '%d'", HouseInfo[houseid][hMoney],houseid+1);
			mysql_tquery(mysql, query_safe_money_get);
			
            GiveMoney(playerid, money, "взял с сейфа");
			ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");
		}
		case 546:
		{
			if(!response) return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			new drug = strval(inputtext);
			new houseid = PI[playerid][pHouseKey] - 1;
			if(drug < 1 || drug > 2000) return SendClientMessage(playerid,COLOR_GREY,"Вы не можете положить меньше 1 и больше 2000 г. наркотиков в сейф");
			if(PI[playerid][pDrugs] < drug) return SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно наркотиков");
			if(HouseInfo[houseid][hDrugs] + drug > 2000) return SendClientMessage(playerid,COLOR_GREY,"Недостаточно места в сейфе");
			new query_safe_put_drugs[55 + 5 + 4];
			format(query_safe_put_drugs,sizeof(query_safe_put_drugs),"UPDATE `houses` SET `Drugs` = '%d' WHERE ID = '%d'", HouseInfo[houseid][hDrugs]+drug,houseid+1);
			mysql_tquery(mysql, query_safe_put_drugs);
			
			HouseInfo[houseid][hDrugs] += drug;
			PI[playerid][pDrugs] -= drug;
		}
		case 547:
		{
			if(!response) return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			new drug = strval(inputtext);
			new houseid = PI[playerid][pHouseKey] - 1;
			if(!PI[playerid][pBag])
			{
				if(PI[playerid][pDrugs] + drug > 500)
				    return SendClientMessage(playerid,COLOR_GREY,"Вы не можете унести больше 500 г.");
			}
			else
			{
				if(PI[playerid][pDrugs] + drug > 1000)
				    return SendClientMessage(playerid,COLOR_GREY,"Вы не можете унести больше 1000 г.");
			}
			if(drug < 1 || drug > 500) return SendClientMessage(playerid,COLOR_GREY,"Вы не можете взять меньше 1 и больше 500 г. наркотиков из сейфа");
			if(HouseInfo[houseid][hDrugs] < drug) return SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно наркотиков в сейфе");
			new query_safe_get_drugs[55 + 5 + 4];
			format(query_safe_get_drugs,sizeof(query_safe_get_drugs),"UPDATE `houses` SET `Drugs` = '%d' WHERE ID = '%d'", HouseInfo[houseid][hDrugs]-drug,houseid+1);
			mysql_tquery(mysql, query_safe_get_drugs);
			HouseInfo[houseid][hDrugs] -= drug;
			PI[playerid][pDrugs] += drug;
		}
		case 548:
		{
			if(!response) return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			new mats = strval(inputtext);
			new houseid = PI[playerid][pHouseKey] - 1;
			if(mats < 1 || mats > 2000) return SendClientMessage(playerid,COLOR_GREY,"Вы не можете положить меньше 1 и больше 2000 материалов в сейф");
			if(PI[playerid][pMats] < mats) return SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно материалов");
			if(HouseInfo[houseid][hMats] + mats > 2000) return SendClientMessage(playerid,COLOR_GREY,"Недостаточно места в сейфе");
			new query_safe_put_drugs[55 + 5 + 4];
			HouseInfo[houseid][hMats] += mats;
			format(query_safe_put_drugs,sizeof(query_safe_put_drugs),"UPDATE `houses` SET `Mats` = '%d' WHERE ID = '%d'", HouseInfo[houseid][hMats]+mats, houseid+1);
			mysql_tquery(mysql, query_safe_put_drugs);

			PI[playerid][pMats] -= mats;
			
			UpdatePlayerData(playerid,"Mats",PI[playerid][pMats]);
		}
		case 549:
		{
			if(!response) return ShowPlayerDialogEx(playerid, 543, DIALOG_STYLE_LIST, !"Сейф", !"Положить деньги\nВзять деньги\nПоложить наркотики\nВзять наркотики\nПоложить материалы\nВзять материалы\nСменить код", !"ОК", !"Отмена");

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			new mats = strval(inputtext);
			new houseid = PI[playerid][pHouseKey] - 1;

			if(!PI[playerid][pBag])
			{
				if(PI[playerid][pMats] + mats > 500)
				    return SendClientMessage(playerid,COLOR_GREY,"Вы не можете унести больше 500 материалов");
			    
			}
			else
			{
				if(PI[playerid][pMats] + mats > 1000)
				    return SendClientMessage(playerid,COLOR_GREY,"Вы не можете унести больше 1000 материалов");
			
			}

			if(mats < 1 || mats > 500) return SendClientMessage(playerid,COLOR_GREY,"Вы не можете взять меньше 1 и больше 500 материалов из сейфа");
			if(HouseInfo[houseid][hMats] < mats) return SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно материалов в сейфе");
			new query_safe_get_drugs[55 + 5 + 4];
			format(query_safe_get_drugs,sizeof(query_safe_get_drugs),"UPDATE `houses` SET `Mats` = '%d' WHERE ID = '%d'",HouseInfo[houseid][hMats]-mats, houseid+1);
			mysql_tquery(mysql, query_safe_get_drugs);
			HouseInfo[houseid][hMats] -= mats;
			PI[playerid][pMats] += mats;
		}
		case 550:
		{
			if(!response)
			{
				new houseid = PI[playerid][pHouseKey] - 1;
				new format_safe[140 + 6 + 8 + 9];
				format(format_safe,sizeof(format_safe),"{FFFFFF}Наркотики [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Материалы [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Деньги [{33aa33}%d$/1000000${FFFFFF}]", HouseInfo[houseid][hDrugs], HouseInfo[houseid][hMats], HouseInfo[houseid][hMoney]);
				ShowPlayerDialogEx(playerid, 542, DIALOG_STYLE_MSGBOX, !"Сейф", format_safe, !"Далее", !"Отмена");
				return 1;
			}
			if(strlen(inputtext) != 4 || !isNumeric(inputtext))
			{
				SendClientMessage(playerid,COLOR_GREY,"Код должен состоять из 4-х цифр");
				return ShowPlayerDialogEx(playerid,550,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Введите новый код от сейфа в формате \"{FF0000}XXXX{FFFFFF}\"","Изменить","Отмена");
			}

			if(!PI[playerid][pHouseKey])
			    return 1;
			    
			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			new code = strval(inputtext);
			SetPVarInt(playerid,"safecode",code);
			ShowPlayerDialogEx(playerid,551,DIALOG_STYLE_INPUT,"Сейф","{ffffff}Введите новый код еще раз","Изменить","Отмена");
		}
		case 551:
		{
			if(!response)
			{
				new houseid = PI[playerid][pHouseKey] - 1;
				new format_safe[140 + 6 + 8 + 9];
				format(format_safe,sizeof(format_safe),"{FFFFFF}Наркотики [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Материалы [{33aa33}%d/2000{FFFFFF}]\n{FFFFFF}Деньги [{33aa33}%d$/1000000${FFFFFF}]", HouseInfo[houseid][hDrugs], HouseInfo[houseid][hMats], HouseInfo[houseid][hMoney]);
				ShowPlayerDialogEx(playerid, 542, DIALOG_STYLE_MSGBOX, !"Сейф", format_safe, !"Далее", !"Отмена");
				return 1;
			}

			if(!PI[playerid][pHouseKey])
			    return 1;

			new hintid = HouseInfo[PI[playerid][pHouseKey]-1][hNumInt]-1;

			if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
				return 1;

			if(strlen(inputtext) != 4 || !isNumeric(inputtext))
			{
				SendClientMessage(playerid,COLOR_GREY,"Код должен состоять из 4-х цифр");
				return ShowPlayerDialogEx(playerid,550,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Введите новый код от сейфа в формате \"{FF0000}XXXX{FFFFFF}\"","Изменить","Отмена");
			}
			new code = strval(inputtext);
			if(code != GetPVarInt(playerid,"safecode"))
			{
				SendClientMessage(playerid,COLOR_GREY,"Коды не совпадают");
				return ShowPlayerDialogEx(playerid,550,DIALOG_STYLE_INPUT,"Сейф","{FFFFFF}Введите новый код от сейфа в формате \"{FF0000}XXXX{FFFFFF}\"","Изменить","Отмена");
			}
			new houseid = PI[playerid][pHouseKey] - 1;
			HouseInfo[houseid][hSafeCode] = code;
			new query_safe_change_code[59 + 4 + 4],
				frmt_str_new_code[41 + 5];
			format(query_safe_change_code,sizeof(query_safe_change_code),"UPDATE `houses` SET `SafeCode` = '%d' WHERE ID = '%d'",code,houseid+1);
			mysql_tquery(mysql, query_safe_change_code);
			format(frmt_str_new_code,sizeof(frmt_str_new_code),"Ваш новый код сейфа: %s. Не забудьте его!",inputtext);
			SendClientMessage(playerid,COLOR_GREEN,frmt_str_new_code);
		}
		case 473:
		{
		    if(!response)
		        return 1;
		        
			if(gAdvertCount >= MAX_ADVERTS)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К сожалению, очередь на объявления занята, попробуйте позже");
				
			
			if(PI[playerid][pMoney] < gAdvertPrice)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");
				
			gAdvertCount++;
			
			new slot = -1;
			for(new i; i < MAX_ADVERTS; i++)
			{
				if(!gAdvert[i][adBusy])
				{
					slot = i;
					break;
				}
			}
			
			if(slot == -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ошибка (#111)");

			GiveMoney(playerid, -gAdvertPrice, "/ad");

			SetString(gAdvert[slot][adSender], PN(playerid));
			gAdvert[slot][adPhone] = PI[playerid][pTelNum];
			SetString(gAdvert[slot][adText], pTemp[playerid][pAdvertText]);
			gAdvert[slot][adBusy] = true;
			
			PI[playerid][pAdvertTime] = 180;
			//UpdatePlayerData(playerid, "AdvertTime", PI[playerid][pAdvertTime]);
			
			SendClientMessage(playerid, COLOR_GREEN, !"Ваше объявление отправлено на обработку");
			
			new
			    frmt_gametext[35];
			    
			format(frmt_gametext, sizeof frmt_gametext, "~r~-$%d", gAdvertPrice);
			GameTextForPlayer(playerid, frmt_gametext, 1000, 1);
				
				
			new
				frmt_advert_message[140];
				
			format(frmt_advert_message, sizeof frmt_advert_message, "[R] Пришло новое объявление от {FFFFFF}%s[%d]{4682B4} | Редактировать: {FFFFFF}/edit", PN(playerid), playerid);
			FractionChat(9, 0x4682B4AA, frmt_advert_message);
            strdel(pTemp[playerid][pAdvertText], 0, 128);
		}
        case 474:
        {
 		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 9)
			    return 1;
			    
			if(PI[playerid][pRank] < 2)
			    return 1;
			    
			if(!gAdvert[listitem][adBusy] || gAdvert[listitem][adChecked] || gAdvert[listitem][adChecking])
				return ShowAdvertList(playerid);

			pTemp[playerid][pAdvertEdit] = listitem+1;
           	gAdvert[listitem][adChecking] = true;
           	
			new frmt_advert_actions[256];
			format(frmt_advert_actions, sizeof frmt_advert_actions, "%s\n1. Отправить\n2. Редактировать\n3. Удалить и отправить администрации\n4. Удалить", gAdvert[listitem][adText]);
			ShowPlayerDialogEx(playerid, 475, DIALOG_STYLE_LIST, gAdvert[listitem][adSender], frmt_advert_actions, !"ОК", !"Отмена");
        }
		case 475:
		{
		    new
		        id = pTemp[playerid][pAdvertEdit]-1;
		        
 		    if(!response)
			{
			    gAdvert[id][adChecking] = false;
		        return ShowAdvertList(playerid);
			}
			
			if(PI[playerid][pFraction] != 9)
			{
			    gAdvert[id][adChecking] = false;
			    return 1;
			}
			
			if(PI[playerid][pRank] < 2)
			{
			    gAdvert[id][adChecking] = false;
			    return 1;
			}
			
			if(!gAdvert[id][adBusy] || gAdvert[id][adChecked] || !gAdvert[id][adChecking])
			{
                gAdvert[id][adChecking] = false;
				return ShowAdvertList(playerid);
			}
			
			switch(listitem)
			{
			    case 0:
			    {
			        gAdvert[id][adChecking] = false;
					new frmt_advert_actions[256];
					format(frmt_advert_actions, sizeof frmt_advert_actions, "%s\n1. Отправить\n2. Редактировать\n3. Удалить и отправить администрации\n4. Удалить", gAdvert[id][adText]);
					ShowPlayerDialogEx(playerid, 475, DIALOG_STYLE_LIST, gAdvert[id][adSender], frmt_advert_actions, !"ОК", !"Отмена");
			    }
			    case 1:
			    {
					gAdvert[id][adTime] = gAdvertTime;
					gAdvertTime += 30;
					GiveMoney(playerid,50,"оплата за объяву");
					format(gAdvert[id][adChecker], MAX_PLAYER_NAME, "%s", PN(playerid));
					gAdvert[id][adCheckerID] = playerid+1;
					
					new
						fraction_name[30];

					switch(PI[playerid][pSubfraction])
					{
					    case 0: SetString(fraction_name, "Директор Virtual. Media");
					    case 1:
					    {
							if(PI[playerid][pRank] != 10)
								SetString(fraction_name, "Сотрудник радиоцентра ЛС");
								
							else
								SetString(fraction_name, "Главный редактор ЛС");
						}
					    case 2:
					    {
							if(PI[playerid][pRank] != 10)
								SetString(fraction_name, "Сотрудник радиоцентра СФ");

							else
								SetString(fraction_name, "Главный редактор СФ");
						}
					    case 3:
						{
							if(PI[playerid][pRank] != 10)
								SetString(fraction_name, "Сотрудник радиоцентра ЛВ");

							else
								SetString(fraction_name, "Главный редактор ЛВ");
						}
					}

					format(gAdvert[id][adRang], 30, "%s", fraction_name);

					gAdvert[id][adChecking] = false;
					gAdvert[id][adChecked] = true;
					new
						salary = floatround((gAdvertCount / 100) * 17, floatround_ceil),
						fmoney = floatround((gAdvertCount / 100) * 83, floatround_ceil);
						
					GiveMoney(playerid, salary, "/edit");
					OrgInfo[8][oMoney] += fmoney;
					
					ShowAdvertList(playerid);
			    }
			    case 2: ShowPlayerDialogEx(playerid, 476, DIALOG_STYLE_INPUT, gAdvert[id][adSender], gAdvert[id][adText], !"OK", !"Отмена");
			    case 3:
			    {
					new
						frmt_report_ad[160];
						
					format(frmt_report_ad, sizeof frmt_report_ad, "[A] [EDIT] %s хотел отправить: %s (Проверил: %s[%d])", gAdvert[id][adSender],gAdvert[id][adText],gAdvert[id][adChecker], gAdvert[id][adCheckerID]-1);
					SendAdminsMessage(0xFFFF00FF, frmt_report_ad);
					SendClientMessage(playerid, 0xFFFF00FF, frmt_report_ad);
					
					strdel(gAdvert[id][adSender],0,24);
					gAdvert[id][adPhone] = 0;
					strdel(gAdvert[id][adText],0,100);
					strdel(gAdvert[id][adChecker],0,24);
					gAdvert[id][adCheckerID] = 0;
					strdel(gAdvert[id][adRang],0,30);
					gAdvert[id][adBusy] = false;
					gAdvert[id][adChecked] = false;
					gAdvert[id][adChecking] = false;
					gAdvert[id][adTime] = 0;
					
					if(gAdvertCount > 0)
						gAdvertCount--;
						
					ShowAdvertList(playerid);
			    }
				case 4:
				{
				    ShowPlayerDialogEx(playerid, 477, DIALOG_STYLE_INPUT, gAdvert[id][adSender], !"{FFFFFF}Введите причину для удаления объявления:", !"Удалить", !"Отмена");

				}
			}
		}
		case 476:
		{
		    new
		        id = pTemp[playerid][pAdvertEdit]-1;

 		    if(!response)
			{
			    gAdvert[id][adChecking] = false;
		        return ShowAdvertList(playerid);
			}

			if(PI[playerid][pFraction] != 9)
			{
			    gAdvert[id][adChecking] = false;
			    return 1;
			}

			if(PI[playerid][pRank] < 2)
			{
			    gAdvert[id][adChecking] = false;
			    return 1;
			}
			if(!gAdvert[id][adBusy] || gAdvert[id][adChecked] || !gAdvert[id][adChecking])
			{
                gAdvert[id][adChecking] = false;
				return ShowAdvertList(playerid);
			}

			format(gAdvert[id][adText], 100, "%s", inputtext);
			gAdvert[id][adTime] = gAdvertTime;
			gAdvertTime += 30;
			format(gAdvert[id][adChecker], MAX_PLAYER_NAME, "%s", PN(playerid));
            gAdvert[id][adCheckerID] = playerid+1;
            
			new
				fraction_name[30];

			switch(PI[playerid][pSubfraction])
			{
			    case 0: SetString(fraction_name, "Директор Virtual. Media");
			    case 1: SetString(fraction_name, "Сотрудник радиоцентра ЛС");
			    case 2: SetString(fraction_name, "Сотрудник радиоцентра СФ");
			    case 3: SetString(fraction_name, "Сотрудник радиоцентра ЛВ");
			}
			
			format(gAdvert[id][adRang], 30, "%s", fraction_name);
			gAdvert[id][adChecking] = false;
			gAdvert[id][adChecked] = true;
			new
				salary = floatround((gAdvertCount / 100) * 17, floatround_ceil),
				fmoney = floatround((gAdvertCount / 100) * 83, floatround_ceil);

			GiveMoney(playerid, salary, "/edit");
			OrgInfo[8][oMoney] += fmoney;
			
			

   			ShowAdvertList(playerid);
		}
		case 477:
		{
		    new
		        id = pTemp[playerid][pAdvertEdit]-1;

 		    if(!response)
			{
			    gAdvert[id][adChecking] = false;
		        return ShowAdvertList(playerid);
			}

			if(PI[playerid][pFraction] != 9)
			{
			    gAdvert[id][adChecking] = false;
			    return 1;
			}

			if(PI[playerid][pRank] < 2)
			{
			    gAdvert[id][adChecking] = false;
			    return 1;
			}
			if(!gAdvert[id][adBusy] || gAdvert[id][adChecked] || !gAdvert[id][adChecking])
			{
                gAdvert[id][adChecking] = false;
				return ShowAdvertList(playerid);
			}
			if(!strlen(inputtext) || strlen(inputtext) < 2 || strlen(inputtext) > 80)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткий/длинный текст");
			    gAdvert[id][adChecking] = false;
			    return 1;
			}
			if(strfind(inputtext,"|") != -1)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
			    gAdvert[id][adChecking] = false;
			    return 1;
			}

			if(GetPlayerID(gAdvert[id][adSender]) != INVALID_PLAYER_ID)
			{
			    new
			        frmt_cancel_ad[254],
					rank = PI[playerid][pRank]-1,
					fractionid = PI[playerid][pFraction]-1;
					
				format(frmt_cancel_ad, sizeof frmt_cancel_ad, "[AD] %s %s отклонил Ваше объявление. Причина: %s", gFractionRankName[fractionid][rank], PN(playerid), inputtext);
				SendClientMessage(GetPlayerID(gAdvert[id][adSender]), 0xFF0033FF, frmt_cancel_ad);
				format(frmt_cancel_ad, sizeof frmt_cancel_ad, "[AD] %s %s отклонил %s[%d] объявление. Причина: %s", gFractionRankName[fractionid][rank], PN(playerid), gAdvert[id][adSender], GetPlayerID(gAdvert[id][adSender]), inputtext);
				FractionChat(9, 0x4682B4AA, frmt_cancel_ad);
			}
			
			strdel(gAdvert[id][adSender],0,24);
			gAdvert[id][adPhone] = 0;
			strdel(gAdvert[id][adText],0,100);
			strdel(gAdvert[id][adChecker],0,24);
			gAdvert[id][adCheckerID] = 0;
			strdel(gAdvert[id][adRang],0,30);
			gAdvert[id][adBusy] = false;
			gAdvert[id][adChecked] = false;
			gAdvert[id][adChecking] = false;
			gAdvert[id][adTime] = 0;
			if(gAdvertCount > 0)
				gAdvertCount--;

			ShowAdvertList(playerid);
		}
		case 3391:
		{
		    if(!response)
			    return 1;
			    
			ShowStats(playerid,playerid);
		}
		case 824:
		{
		    if(!response)
		        return 1;
		        
			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -1989.8998,1117.9297,54.4688))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от церкви");

			if(!PI[playerid][pMerrit])
				return SendClientMessage(playerid, COLOR_GREY, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в браке");
				
			if(GetPlayerID(PI[playerid][pMerrit]) != INVALID_PLAYER_ID)
			{
			    new target = GetPlayerID(PI[playerid][pMerrit]);
				PI[target][pMerrit] =
                PI[playerid][pMerrit] = 0;
				UpdatePlayerData(playerid, "Merrit", PI[playerid][pMerrit]);
				UpdatePlayerData(target, "Merrit", PI[target][pMerrit]);
				SendClientMessage(playerid, COLOR_GREEN, !"Вы разорвали брак");
				return 1;
			}
			
            mysql_query_string[0] = EOS;
            
			format(mysql_query_string, sizeof mysql_query_string, "UPDATE `accounts` SET `Merrit` = '0' WHERE `ID` = '%d'", PI[playerid][pMerrit]);
			mysql_tquery(mysql, mysql_query_string);
			
			PI[playerid][pMerrit] = 0;
			UpdatePlayerData(playerid, "Merrit", PI[playerid][pMerrit]);
			
			SendClientMessage(playerid, COLOR_GREEN, !"Вы разорвали брак");
		}

	}
	return true;
}