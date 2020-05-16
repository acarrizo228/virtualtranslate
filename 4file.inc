stock GetNameID(const name[])
{
    new ID = INVALID_PLAYER_ID;
	sscanf(name,"u",ID);
	if(IsPlayerConnected(ID)) return ID;
	return INVALID_PLAYER_ID;
}

stock ShowHelpDialog(playerid)
{
	ShowPlayerDialogEx(playerid, 66, DIALOG_STYLE_LIST, !"Команды сервера", "{FF7319}1.{FFFFFF} Общие\n{FF7319}2.{FFFFFF} Чаты\n{FF7319}3.{FFFFFF} Работы\n{FF7319}4.{FFFFFF} Дом\n{FF7319}5.{FFFFFF} Бизнес\n{FF7319}6.{FFFFFF} Авто\n{FF7319}7.{FFFFFF} Лидерам\n{FF7319}8.{FFFFFF} Фракция\n{FF7319}9.{FFFFFF} Семья", !"Выбрать", !"Отмена");
	return true;
}
stock DestroyPlayerTD(playerid, &PlayerText:td)
{
	if(td != PlayerText:-1)
	{
	    PlayerTextDrawDestroy(playerid, td);
	    td = PlayerText:-1;
	}
	return true;
}
stock GetHouseStyle(houseid)
{
	for(new i = 1;i < sizeof(GHSPos);i ++)
	{
	    if(floatcomp(GHSPos[i][0], 0.000000)) continue;
	    if(	floatcomp(HouseInfo[houseid][hExit_X], GHSPos[i][0]) &&
	    	floatcomp(HouseInfo[houseid][hExit_Y], GHSPos[i][1]) &&
	    	floatcomp(HouseInfo[houseid][hExit_Z], GHSPos[i][2])) return i;
	}
	return -1;
}
stock CountWords(text[])
{
	new words;
	for(new i; i < strlen(text); i ++)
	{
	    if(text[i] != ' ' && ( (i-1) < 0 || text[i - 1] == ' ') ) words ++;
	}
	return words;
}
stock GetEndWord(text[], word)
{
	new len = strlen(text);
    for(new i = word; i < len; i ++)
	{
	    if(i == (len-1) ) return i + 1;
	    else if(text[i] == ' ') return i;
	}
	return -1;
}
stock GetWord(text[], word, wordstr[], sizword)
{
	new w;
	for(new i; i < strlen(text); i ++)
	{
	    if(text[i] != ' ' && ( (i-1) < 0 || text[i - 1] == ' ') )
	    {
	        if(w == word)
			{
				strmid(wordstr, text, i, GetEndWord(text, i), sizword);
				return i;
			}
			w ++;
	    }
	}
	return 0;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(_:clickedid == INVALID_TEXT_DRAW)
    {
        if(Clother[playerid] != -1) SelectTextDraw(playerid, -16776961);

		if(GetPVarInt(playerid, "clothes_td")) {
			HidePlayerClothesTD(playerid);
			justtp_exit[playerid] = true;
			SetPlayerPos(playerid, GetPVarFloat(playerid, "posx"), GetPVarFloat(playerid, "posy"), GetPVarFloat(playerid, "posz"));
			SetPlayerInterior(playerid, GetPVarInt(playerid, "interior"));
			SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "vw"));
			SetPlayerFacingAngle(playerid, GetPVarInt(playerid, "posa"));
			f_TogglePlayerControllable(playerid, true);
			
			new
			    skin_fract = GetSkinOfPlayer(playerid);

			SetPlayerSkinEx(playerid, skin_fract);
			
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
		if(GetPVarInt(playerid, "accs_td")) {
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
		}
		
		if(temp_filling_status[playerid]) {
			HideFillingBar(playerid);
            f_TogglePlayerControllable(playerid, true);
			temp_filling_buy_id[playerid] = 0;
			temp_filling_amount[playerid] = 0;
			temp_filling_speed[playerid] = 0;
			temp_filling_going[playerid] = false;
			temp_filling_accel[playerid] = 0;
			temp_filling_status[playerid] = false;
			temp_filling_id[playerid] = 0;
			temp_filling_price[playerid] = 0;
		}
		if(temp_buying_car[playerid]) {
	        if(VehicleToBuy[playerid] != INVALID_VEHICLE_ID) DestroyVehicle(VehicleToBuy[playerid]);
	        VehicleToBuy[playerid] = INVALID_VEHICLE_ID;
	        BuyCar[playerid] = -1;
			f_TogglePlayerControllable(playerid, true);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid,0);
			SetCameraBehindPlayer(playerid);
			CancelSelectTextDraw(playerid);


			for(new t = 0; t < 22; t++)
				PlayerTextDrawHide(playerid, BuyingCar[playerid][t]);

			switch(BuyCar_Class[playerid])
			{
				case 0: SetPlayerPos(playerid,555.1915,-1293.4724,17.2482);
				case 1: SetPlayerPos(playerid,-1958.7511,298.4377,35.4688);
				case 2: SetPlayerPos(playerid,1658.5024,2199.9299,10.8203);
				case 3: SetPlayerPos(playerid,2131.6028,-1149.9248,24.2113);
			}
			justtp_exit[playerid] = true;
	        BuyCar_Class[playerid] = -1;
	        temp_buying_car[playerid] = false;
		}
		if(temp_pts_td[playerid]) {
			CancelSelectTextDraw(playerid);

			for(new t = 0; t < 24; t++)
				PlayerTextDrawHide(playerid, pts_td[t]);
				
            temp_pts_td[playerid] = false;
				
		}
		if(temp_table[playerid] != -1 && InJob[playerid] == 8) {
			new table = temp_table[playerid];
			for(new td = 0; td < 13; td++)
				TextDrawHideForPlayer(playerid, crupie_table[table][td]);

            CancelSelectTextDraw(playerid), temp_table[playerid] = -1;
            gTable[table][tCrup] = INVALID_PLAYER_ID;
		}
		if(temp_table[playerid] != -1) {
			SelectTextDraw(playerid, 0xFFFFFFFF);
		}
        return 1;
    }




	new Float:Health;
	GetPlayerHealth(playerid,Health);

	if(Clother[playerid] != -1)
	{
	    if(_:clickedid == 65535) SelectTextDraw(playerid, 0xFFFFFFAA);
	    else if(clickedid == select_skin[0]) callcmd::back(playerid,"");
	    else if(clickedid == select_skin[1]) callcmd::next(playerid,"");
	    else if(clickedid == select_skin[10]) callcmd::done(playerid,"");
	    return true;
	}
	
	if(clickedid == SkinShopDraw[1]) {
	
	    if(!ChangingSkin[playerid])
	        return 1;
	        
		new
		    b_skins[114][2],
		    b_class = 1,
		    b_sel = GetPVarInt(playerid, "clothes_sel"),
		    b_skin,
		    b_price,
		    b_max = 0,
		    b_str[32]
		;
		for(new x, z; x < sizeof(Skins); x ++) {
			b_skin = GetSkinID(b_class, PI[playerid][pSex], PI[playerid][pRace], x);
			b_price = GetSkinPrice(x);
			if(!b_skin) continue;
			b_skins[z][0] = b_skin;
			b_skins[z][1] = b_price;
			z ++;
		}
		for(new x; x < sizeof(b_skins) - 1; x ++) {
		    if(!b_skins[x + 1][0]) {
				b_max = x;
				break;
			}
		    else continue;
		}
		if(b_sel == b_max) b_sel = 0;
		else b_sel ++;
		SetPlayerSkinEx(playerid, b_skins[b_sel][0]);
		format(b_str, 32, "$%i", b_skins[b_sel][1]);
		PlayerTextDrawSetString(playerid, SkinShopPriceDraw[playerid], b_str);
		SetPVarInt(playerid, "clothes_sel", b_sel);
	}
	else if(clickedid == SkinShopDraw[0]) {

	    if(!ChangingSkin[playerid])
	        return 1;
	        
		new
		    b_skins2[114][2],
		    b_class = 1,
		    b_sel = GetPVarInt(playerid, "clothes_sel"),
		    b_skin,
		    b_price,
		    b_max = 0,
		    b_str[32]
		;
		for(new x, z; x < sizeof(Skins); x ++) {
			b_skin = GetSkinID(b_class, PI[playerid][pSex], PI[playerid][pRace], x);
			b_price = GetSkinPrice(x);
			if(!b_skin) continue;
			b_skins2[z][0] = b_skin;
			b_skins2[z][1] = b_price;
			z ++;
		}
		for(new x; x < sizeof(b_skins2) - 1; x ++) {
		    if(!b_skins2[x + 1][0]) {
				b_max = x;
				break;
			}
		    else continue;
		}
		if(b_sel - 1 < 0) b_sel = b_max;
		else b_sel --;
		SetPlayerSkinEx(playerid, b_skins2[b_sel][0]);
		format(b_str, 32, "$%i", b_skins2[b_sel][1]);
		PlayerTextDrawSetString(playerid, SkinShopPriceDraw[playerid], b_str);
		SetPVarInt(playerid, "clothes_sel", b_sel);
	}
	else if(clickedid == SkinShopDraw[10]) {

	    if(!ChangingSkin[playerid])
	        return 1;
	        
		new
			b_skin = GetPlayerSkin(playerid),
			b_index = -15
		;
		for(new x; x < sizeof(Skins); x ++) {
			if(Skins[x][skinID] != b_skin) continue;
			b_index = x;
			break;
		}
		SetPVarInt(playerid, "clothes_select", b_index);

		new
		    frmt_buy_skin[100];
		    
		format(frmt_buy_skin, sizeof frmt_buy_skin, "{FFFFFF}Вы хотите купить эту одежду за {FF0000}$%i{FFFFFF}?", GetSkinPrice(b_index));
		ShowPlayerDialogEx(playerid, 738, DIALOG_STYLE_MSGBOX, !"Покупка одежды", frmt_buy_skin, !"Да", !"Нет");
	}
	else if(clickedid == accessories_td[1])
	{
		new
		    b_accs[98][2],
		    b_class = accs_class[playerid],
		    b_sel = accs_sel[playerid],
		    b_acc,
		    b_price,
		    b_max = 0,
		    b_str[32];
		    
		for(new x, z; x < sizeof(gAccessories); x ++) {
			b_acc = GetAccessoryID(b_class, x);
			b_price = GetAccessoryPrice(x);
			if(!b_acc) continue;
			b_accs[z][0] = b_acc;
			b_accs[z][1] = b_price;
			z ++;
		}
		for(new x; x < sizeof(b_accs) - 1; x ++) {
		    if(!b_accs[x + 1][0]) {
				b_max = x;
				break;
			}
		    else continue;
		}
		if(b_sel == b_max) b_sel = 0;
		else b_sel ++;
	    
	    if(IsValidPlayerObject(playerid, acc_object[playerid]))
			DestroyPlayerObject(playerid, acc_object[playerid]);
  			
  		acc_object[playerid] = CreatePlayerObject(playerid, b_accs[b_sel][0], 204.168548, -42.472404, 1001.884887, 0.000000, 2.299999, -87.800018);
  		


		format(b_str, 32, "$%i", b_accs[b_sel][1]);
		PlayerTextDrawSetString(playerid, AccsShopPriceDraw[playerid], b_str);

		accs_sel[playerid] = b_sel;
		accs_last[playerid] = b_accs[b_sel][0];
		
	}
	else if(clickedid == accessories_td[0])
	{
		new
		    b_accs2[98][2],
		    b_class = accs_class[playerid],
		    b_sel = accs_sel[playerid],
		    b_acc,
		    b_price,
		    b_max = 0,
		    b_str[32];
		
		for(new x, z; x < sizeof(gAccessories); x ++) {
			b_acc = GetAccessoryID(b_class, x);
			b_price = GetAccessoryPrice(x);
			if(!b_acc) continue;
			b_accs2[z][0] = b_acc;
			b_accs2[z][1] = b_price;
			z ++;
		}
		for(new x; x < sizeof(b_accs2) - 1; x ++) {
		    if(!b_accs2[x + 1][0]) {
				b_max = x;
				break;
			}
		    else continue;
		}
		if(b_sel - 1 < 0) b_sel = b_max;
		else b_sel --;
		
	    if(IsValidPlayerObject(playerid, acc_object[playerid]))
			DestroyPlayerObject(playerid, acc_object[playerid]);

  		acc_object[playerid] = CreatePlayerObject(playerid, b_accs2[b_sel][0], 204.168548, -42.472404, 1001.884887, 0.000000, 2.299999, -87.800018);

		format(b_str, 32, "$%i", b_accs2[b_sel][1]);
		PlayerTextDrawSetString(playerid, AccsShopPriceDraw[playerid], b_str);
		accs_sel[playerid] = b_sel;
		accs_last[playerid] = b_accs2[b_sel][0];
	}
	else if(clickedid == accessories_td[10])
	{
		new
			b_acc = accs_last[playerid],
			b_index = -15;

		for(new x; x < sizeof(gAccessories); x ++) {

			if(gAccessories[x][0] != b_acc) continue;

			b_index = x;
			break;
		}

		acc_select[playerid] = b_index;

		new
		    frmt_acc_skin[100];

		format(frmt_acc_skin, sizeof frmt_acc_skin, "\n\n{FFFFFF}Вы действительно хотите приобрести этот аксессуар за {FF0000}$%i{FFFFFF}?\n\n", GetAccessoryPrice(b_index));
		ShowPlayerDialogEx(playerid, 622, DIALOG_STYLE_MSGBOX, !"Покупка аксессуара", frmt_acc_skin, !"Да", !"Нет");
	}
	if(temp_table[playerid] != -1)
	{
	    new table = temp_table[playerid];
	    

		if(InJob[playerid] != 8)
		    return 1;
		
		if(clickedid == crupie_table[table][9])
		{
			for(new td = 0; td < 13; td++)
				TextDrawHideForPlayer(playerid, crupie_table[table][td]);

            CancelSelectTextDraw(playerid), temp_table[playerid] = -1;
            gTable[table][tCrup] = INVALID_PLAYER_ID;

		}
		else if(clickedid == crupie_table[table][7])
		{
	        if(!IsPlayerInDynamicArea(playerid, gCasinoTableCrupie[table]))
	            return 1;
            
			if(Casino_TotalPlayer(table) > 0)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже идет активная игра");

		    ShowPlayerDialogEx(playerid, 489, DIALOG_STYLE_INPUT, !"Ставка", !"{FFFFFF}Введите сумму ставки для стола\n\nМинимальная ставка: {FF0000}1000${FFFFFF}\nМаксимальная ставка: {FF0000}10000000$", !"Изменить", !"Отмена");
		}
		else if(clickedid == crupie_table[table][8])
		{
	        if(!IsPlayerInDynamicArea(playerid, gCasinoTableCrupie[table]))
	            return 1;
            
			if(!gTable[table][tBet])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Установите ставку");
			    
			if(Casino_TotalPlayer(table) < 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Недостаточно игроков для игры");
			    
			if(gTable[table][tStatus] == true)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Дождитесь пока закончится текущая игра");
			    
            CasinoTimer[table] = SetTimerEx("@__Casino_Start",300, true, "d", table);
            
			new
			    string[6];
			    
       		foreach(new i : Player)
		    {
		        if(temp_table[i] == table)
		        {
		            format(string,sizeof(string),"%d",random(10));
		            GameTextForPlayer(i, string, 250, 6);
					SetTimerEx("@__PlayerPlaySoundOne",100,false,"i",i);
		        }
		    }
			gTable[table][tStatus] = true;
		}

	}
    return false;
}
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{

	if(playertextid == BuyingCar[playerid][16])
	{
        if(VehicleToBuy[playerid] != INVALID_VEHICLE_ID) DestroyVehicle(VehicleToBuy[playerid]);
        VehicleToBuy[playerid] = INVALID_VEHICLE_ID;
        BuyCar[playerid] = -1;
		f_TogglePlayerControllable(playerid, true);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid,0);
		SetCameraBehindPlayer(playerid);
		CancelSelectTextDraw(playerid);
		
		
		for(new t = 0; t < 22; t++)
			PlayerTextDrawHide(playerid, BuyingCar[playerid][t]);
			
		switch(BuyCar_Class[playerid])
		{
			case 0: SetPlayerPos(playerid,555.1915,-1293.4724,17.2482);
			case 1: SetPlayerPos(playerid,-1958.7511,298.4377,35.4688);
			case 2: SetPlayerPos(playerid,1658.5024,2199.9299,10.8203);
			case 3: SetPlayerPos(playerid,2131.6028,-1149.9248,24.2113);
		}
		justtp_exit[playerid] = true;
        BuyCar_Class[playerid] = -1;
        temp_buying_car[playerid] = false;
		return true;
	}
	else if(playertextid == BuyingCar[playerid][2])
	{
		if(BuyCar_Class[playerid] == 0)
		{
			if(BuyCar[playerid] == (sizeof(EkonomVehicles)-1))
				BuyCar[playerid] = -1;
		}
		if(BuyCar_Class[playerid] == 1)
		{
			if(BuyCar[playerid] == (sizeof(MiddleVehicles)-1))
				BuyCar[playerid] = -1;
		}
		if(BuyCar_Class[playerid] == 2)
		{
			if(BuyCar[playerid] == (sizeof(EliteVehicles)-1))
				BuyCar[playerid] = -1;
		}
		if(BuyCar_Class[playerid] == 0)
		{
			if(BuyCar[playerid] == (sizeof(EkonomVehicles)-1))
				BuyCar[playerid] = -1;
		}
		if(BuyCar_Class[playerid] == 1)
		{
			if(BuyCar[playerid] == (sizeof(MiddleVehicles)-1))
				BuyCar[playerid] = -1;
		}
		if(BuyCar_Class[playerid] == 3)
		{
			if(BuyCar[playerid] == (sizeof(MotoVehicles)-1))
				BuyCar[playerid] = -1;
		}
		
		new VehicleIDToShow = GetNextCar(playerid,BuyCar[playerid]+1);
		if(VehicleIDToShow == -1)
		{
			PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
			return true;
		}
		BuyCar[playerid] = BuyCar[playerid] +1;
		

		if(VehicleToBuy[playerid] != INVALID_VEHICLE_ID) DestroyVehicle(VehicleToBuy[playerid]);
		VehicleToBuy[playerid] = J_AddStaticVehicleEx(VehicleIDToShow, 1768.6760, -57.0590, 1002.5030, 65.0000, -1, -1, 1000000);

	    new mes[200], classname[30];
		switch(BuyCar_Class[playerid])
		{
			case 0: strcat(classname,"economy");
			case 1: strcat(classname,"middle");
			case 2: strcat(classname,"premium");
			case 3: strcat(classname,"moto");
		}

		format(mes, sizeof(mes), "%s", VehicleName[VehicleIDToShow-400]);
		PlayerTextDrawSetString(playerid, BuyingCar[playerid][17], mes);
		
		format(mes, sizeof(mes), "%d L", Transport[VehicleIDToShow-400][trTank]);
		PlayerTextDrawSetString(playerid, BuyingCar[playerid][19], mes);
		
		format(mes, sizeof(mes), "~g~$~w~%d", Transport[VehicleIDToShow-400][trPrice]);
		GameTextForPlayer(playerid, mes, 5000, 4);
		
		format(mes, sizeof(mes), "%d L", Transport[VehicleIDToShow-400][trConsumption]);
		PlayerTextDrawSetString(playerid, BuyingCar[playerid][11], mes);
		
		format(mes,sizeof(mes),"%s",classname);
		PlayerTextDrawSetString(playerid,BuyingCar[playerid][18],mes);

		LinkVehicleToInterior(VehicleToBuy[playerid], 18);
		SetVehicleVirtualWorld(VehicleToBuy[playerid], BuyCar_Class[playerid]+playerid);

		SetPlayerPos(playerid, 1751.525024, -62.972301, 1002.498718);
		SetPlayerCameraPos(playerid, 1759.817993, -64.480904, 1003.000000);
		SetPlayerCameraLookAt(playerid, 1768.675903, -57.058701, 1002.502808);
		SetPlayerCameraPos(playerid, 1759.798218, -64.480904, 1003.000000);
		
        J_SetVehicleHealth(VehicleToBuy[playerid],1000);
		return true;
	}
	else if(playertextid == BuyingCar[playerid][7])
	{
		if(BuyCar_Class[playerid] == 0)
		{
			if(BuyCar[playerid] == 0)
				BuyCar[playerid] = sizeof(EkonomVehicles);
		}
		if(BuyCar_Class[playerid] == 1)
		{
			if(BuyCar[playerid] == 0)
				BuyCar[playerid] = sizeof(MiddleVehicles);
		}
		if(BuyCar_Class[playerid] == 2)
		{
			if(BuyCar[playerid] == 0)
				BuyCar[playerid] = sizeof(EliteVehicles);
		}
		if(BuyCar_Class[playerid] == 3)
		{
			if(BuyCar[playerid] == 0)
				BuyCar[playerid] = sizeof(MotoVehicles);
		}

		new VehicleIDToShow = GetBackCar(playerid,BuyCar[playerid]-1);
		if(VehicleIDToShow == -1)
		{
			PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
			return true;
		}
		BuyCar[playerid] = BuyCar[playerid]-1;


		if(VehicleToBuy[playerid] != INVALID_VEHICLE_ID) DestroyVehicle(VehicleToBuy[playerid]);
		VehicleToBuy[playerid] = J_AddStaticVehicleEx(VehicleIDToShow, 1768.6760, -57.0590, 1002.5030, 65.0000, -1, -1, 1000000);

	    new mes[200], classname[30];
		switch(BuyCar_Class[playerid])
		{
			case 0: strcat(classname,"economy");
			case 1: strcat(classname,"middle");
			case 2: strcat(classname,"premium");
			case 3: strcat(classname,"moto");
		}

		format(mes, sizeof(mes), "%s", VehicleName[VehicleIDToShow-400]);
		PlayerTextDrawSetString(playerid, BuyingCar[playerid][17], mes);

		format(mes, sizeof(mes), "%d L", Transport[VehicleIDToShow-400][trTank]);
		PlayerTextDrawSetString(playerid, BuyingCar[playerid][19], mes);

		format(mes, sizeof(mes), "~g~$~w~%d", Transport[VehicleIDToShow-400][trPrice]);
		GameTextForPlayer(playerid, mes, 5000, 4);
		
		format(mes, sizeof(mes), "%d L", Transport[VehicleIDToShow-400][trConsumption]);
		PlayerTextDrawSetString(playerid, BuyingCar[playerid][11], mes);

		format(mes,sizeof(mes),"%s",classname);
		PlayerTextDrawSetString(playerid,BuyingCar[playerid][18],mes);

		SetPlayerVirtualWorld(playerid, BuyCar_Class[playerid]+playerid);
		f_TogglePlayerControllable(playerid, false);
		SetPlayerInterior(playerid, 18);
		f_TogglePlayerControllable(playerid, true);
		LinkVehicleToInterior(VehicleToBuy[playerid], 18);
		SetVehicleVirtualWorld(VehicleToBuy[playerid], BuyCar_Class[playerid]+playerid);

		SetPlayerPos(playerid, 1751.525024, -62.972301, 1002.498718);
		SetPlayerCameraPos(playerid, 1759.817993, -64.480904, 1003.000000);
		SetPlayerCameraLookAt(playerid, 1768.675903, -57.058701, 1002.502808);
		SetPlayerCameraPos(playerid, 1759.798218, -64.480904, 1003.000000);

        J_SetVehicleHealth(VehicleToBuy[playerid],1000);
		return true;
	}
	else if(playertextid == BuyingCar[playerid][15])
	{
		if(PI[playerid][pHouseKey] != 0)
		{
			if(GetString(HouseInfo[PI[playerid][pHouseKey]-1][hOwner],Name(playerid)))
			{
				if(PI[playerid][pCars])
					return SendClientMessage(playerid, COLOR_GREY, !"Вам нужно продать свою машину перед тем как купить новую");

				new carid = VehicleToBuy[playerid];
				new model = GetVehicleModel(carid);
				new modelid = model - 400;

				if(PI[playerid][pMoney] < Transport[modelid][trPrice])
				    return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточно денег для покупки этого т/с");


				ShowPlayerDialogEx(playerid, 359, 2, !"Выберите цвет номер 1", !"1.Белый\n{505050}2.Черный\n{33CCFF}3.Голубой\n{FF0000}4.Красный\n{FFFF00}5.Желтый\n{0066FF}6. Синий\n{AFAFAF}7.Серый\n{E75480}8. Розовый\n{f5f5dc}9.Бежевый\n{ff00ff}10.Пурпурный\n{FFFFFF}Другой...", !"OK", !"Выход");
				return true;
			}
			else
			    return SendClientMessage(playerid, COLOR_GREY, !"Доступно только владельцу дома");
		}
		else
			return SendClientMessage(playerid, COLOR_GREY, !"Купите дом или арендуйте комнату в отеле");


	}
	else if(playertextid == pts_td[5])
	{
		CancelSelectTextDraw(playerid);

		for(new t = 0; t < 24; t++)
			PlayerTextDrawHide(playerid, pts_td[t]);
	}
	if(temp_table[playerid] != -1)
	{
		new tableid = temp_table[playerid];
	 	if(playertextid == casino_table[tableid][19])
		{
            if(!IsPlayerInDynamicArea(playerid, gCasinoTableCrupie[tableid]))
                return 1;
                
	        if(gTable[tableid][tBet] == 0)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Дождитесь пока крупье выберет ставку");

			if(gTable[tableid][tStatus] == true)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Пожалуйста подождите пока закончится текущая игра");

			if(Casino_GetPlayerID(tableid,playerid) != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже сделали ставку");

	        if(Casino_TotalPlayer(tableid) == 4)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Все места уже заняты");

	        if(PI[playerid][pMoney] < gTable[tableid][tBet])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

			if(InJob[playerid] == 8)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете играть");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы сделали ставку, дожидайтесь начала игры. Для того чтобы выйти из игры нажмите {F5B800}EXIT");

	        new
				str_bet[32 + MAX_PLAYER_NAME];

	        format(str_bet, sizeof str_bet, "%s{FFFFFF} сделал ставку", PN(playerid));

			ProxDetector(30.0, playerid, str_bet, 0xF5B800FF);

			SetPlayerChatBubble(playerid, "сделал ставку", 0xF5B800FF, 1.20, 5000);
			PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);

			new
				frmt_transfer_log[60];

			format(frmt_transfer_log, sizeof frmt_transfer_log, "сделал ставку (стол: %d)", tableid);
	        GiveMoney(playerid, -gTable[tableid][tBet], frmt_transfer_log);

			gTable[tableid][tPlayers][Casino_GetSlot(tableid)] = playerid;

			new	frmt_player_bet[20 + MAX_PLAYER_NAME];


			
		    format(frmt_player_bet, sizeof frmt_player_bet, "%d/4", Casino_TotalPlayer(tableid));
		    TextDrawSetString(crupie_table[tableid][6], frmt_player_bet);
		    
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
		}
		else if(playertextid == casino_table[tableid][18])
		{
			
			for(new i; i < 4; i++)
            {
                if(gTable[tableid][tPlayers][i] == playerid && gTable[tableid][tStatus] != true)
					return ShowPlayerDialogEx(playerid, 488, 0, !"Кости", !"{FFFFFF}Вы действительно хотите отказаться от участия и забрать деньги?\nДля подтверждения нажмите '{E0E000}Выйти{FFFFFF}'", !"Выйти", !"Отмена");

				else if(gTable[tableid][tPlayers][i] == playerid && gTable[tableid][tStatus] == true)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игра уже началась");
			}

			for(new td = 0; td < 22; td++)
				PlayerTextDrawHide(playerid, casino_table[tableid][td]);

			CancelSelectTextDraw(playerid);
			temp_table[playerid] = -1;
		}
	}
    return true;
}


stock ProxDetector(Float:radi, playerid, string[], color)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:X, Float:Y, Float:Z;
		GetPlayerPos(playerid, X, Y, Z);
   		foreach(new i: Player)
		{
			if(IsPlayerConnected(i))
			{
				if (IsPlayerInRangeOfPoint(i,radi,X,Y,Z) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) SCM(i, color, string);
			}
		}
	}
	return true;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return true;
}

stock OnPlayerRegister(playerid, password[])
{
	new query[600];
	new info[300];
	new pass[100],
		newstring[24];

	new Year, Month, Day;
	getdate(Year, Month, Day);
	format(newstring, sizeof newstring, "%d-%d-%d", Day, Month, Year);

			
	mysql_escape_string(password, pass, mysql);
	strcat(query,"INSERT INTO `accounts` ");
	strcat(query,"(`NickName`,`Password`,`RegIP`,`DateReg`,`Level`,`Sex`,`Age`,`Race`,`Mail`,`Money`,`Bank`,`HouseKey`,`BizKey`,`Nation`,`HP`) ");
	strcat(query,"VALUE ");
    format(info, sizeof(info), "('%s', '%s', '%s', '%s', '1', '%i', '%i', '%i', '%s', '200', '0', '0', '0', '%i', '100.0')",
	PN(playerid), password, PlayerIP(playerid), newstring, RegSex[playerid], RegAge[playerid], RegRace[playerid], RegEmail[playerid], RegNation[playerid]);
	strcat(query,info);
	mysql_tquery(mysql, query, "OnPlayerRegisterMysql", "d", playerid);
	return 1;
}
forward OnPlayerRegisterMysql(playerid);
public OnPlayerRegisterMysql(playerid)
{
    PI[playerid][pID] = cache_insert_id(mysql);
    PI[playerid][pHealth] = 100;
	aml(-3, playerid, "", PlayerIP(playerid),0);
	OnPlayerLogin(playerid);
    return true;
}
stock RemovePlayerAttachedObjectEx(playerid, index)
{
    return RemovePlayerAttachedObject(playerid, index);
}

stock RemovePlayerFromVehicle_Ex(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
	    pTemp[playerid][pAntiAir] += 2;
		new Float:X,Float:Y,Float:Z,Float:A;
		GetPlayerPos(playerid, X, Y, Z);
		GetVehicleZAngle(GetPlayerVehicleID(playerid), A);
		switch(GetPlayerVehicleSeat(playerid))
		{
		    case 0,2: ShiftCords(1, X, Y, A-90.0, 1.5);
		    case 1,3: ShiftCords(1, X, Y, A+90.0, 1.5);
		}
		SetPlayerPos(playerid, X, Y, Z);
	}
	return true;
}
stock acc_int_strcat(query[], len, name[], number)
{
	new string[100];
    format(string, sizeof(string), "`%s` = '%d',",name, number);
    strcat(query, string, len);
    return true;
}
stock acc_str_strcat(query[], len, name[], str[])
{
	new string[256];
    format(string, sizeof(string), "`%s` = '%s',",name, str);
    strcat(query, string, len);
    return true;
}
stock acc_float_strcat(query[], len, name[], Float:number)
{
	new string[100];
    format(string, sizeof(string), "`%s` = '%f',", name, number);
    strcat(query, string, len);
    return true;
}
stock SaveAccount(playerid)
{
	mysql_query_string[0] = 0;
	
	mysql_format(mysql, mysql_query_string, sizeof mysql_query_string, "UPDATE `accounts` SET \
		`MuteTime` = '%d', `GunLic` = '%d', `BoatLic` = '%d', `FlyLic`= '%d' , `CarLic` = '%d', `Level` = '%d', `Exp` = '%d', `Money` = '%d', `Bank` = '%d', `Fraction` = '%d', `Subfraction` = '%d', `HouseKey` = '%d',\
		`BizKey` = '%d', `TelNum` = '%d', `Mats` = '%d', `Packets` = '%d', `Drugs` = '%d', `Job` = '%d', `SDPistol_Skill` = '%d', `Eagle_Skill` = '%d', `ShotGun_Skill` = '%d',\
		`MP5_Skill` = '%d',`AK47_Skill` = '%d',`M4_Skill` = '%d' WHERE `ID` = '%i'",
		PI[playerid][pMuteTime],PI[playerid][pGunLic],PI[playerid][pBoatLic],PI[playerid][pFlyLic],PI[playerid][pCarLic],PI[playerid][pLevel],
		PI[playerid][pExp],PI[playerid][pMoney],PI[playerid][pBank],PI[playerid][pFraction],PI[playerid][pSubfraction],PI[playerid][pHouseKey],PI[playerid][pBizKey],PI[playerid][pTelNum],PI[playerid][pPackets],
		PI[playerid][pMats],PI[playerid][pDrugs],PI[playerid][pJob],PI[playerid][pSDPistol_Skill], PI[playerid][pEagle_Skill], PI[playerid][pShotGun_Skill],
		PI[playerid][pMP5_Skill], PI[playerid][pAK47_Skill],PI[playerid][pM4_Skill],PI[playerid][pID]);
	mysql_tquery(mysql, mysql_query_string, "", "");
	return true;
}
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(PI[playerid][pAdmin] > 3) SetPVarFloat(playerid,"XMap",fX),SetPVarFloat(playerid,"YMap",fY),SetPVarFloat(playerid,"ZMap",fZ);
	if(pTemp[playerid][pTaxiSelect])
	{
		new
			driverid = pTemp[playerid][pTaxiDriver];
			
		if(driverid == INVALID_PLAYER_ID || pTemp[driverid][pTaxiID] != GetPlayerVehicleID(playerid))
		{
		    pTemp[playerid][pTaxiSelect] = false;
		    pTemp[playerid][pTaxiDriver] = INVALID_PLAYER_ID;
		}

			
		if(GetPlayerState(playerid) != PLAYER_STATE_PASSENGER || GetPlayerVehicleID(playerid) != pTemp[driverid][pTaxiID])
		{
		    pTemp[playerid][pTaxiSelect] = false;
		    pTemp[playerid][pTaxiDriver] = INVALID_PLAYER_ID;
		}
		
		SetPlayerMapIcon(driverid, iconTaxi, fX, fY, 0.0, 0, COLOR_YELLOW, 1);
		
		pTemp[playerid][pTaxiSelect] = false;

		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Данные о месте назначения отправлены таксисту");
		SendClientMessage(driverid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Пассажир установил {FFFF00}метку{FFFFFF} на карте. Чтобы убрать метку используйте /untaxi");
	}
 	if(PI[playerid][pAdmin] > 3)
 	{
  		if(GetPlayerState(playerid) == 2)
  		{
	   		new tmpcar = GetPlayerVehicleID(playerid);
	   		J_SetVehiclePos(tmpcar, fX, fY, fZ+2);
  		}
  		else SetPlayerPos(playerid, fX, fY, fZ+1);
  		SetPlayerVirtualWorld(playerid,0);
  		SetPlayerInterior(playerid,0);
  		SetPVarInt(playerid, "anticheat_tp", gettime()+1);
 	}
	return true;
}
stock FixRusText(text[])
{
	new size = strlen(text);
	for ( new i = 0; i != size; i ++ )
    {
        switch ( text[i] )
        {
            case 'а': text[i] = 'a';
            case 'А': text[i] = 'A';
            case 'б': text[i] = '—';
            case 'Б': text[i] = 'Ђ';
            case 'в': text[i] = 'ў';
            case 'В': text[i] = '‹';
            case 'г': text[i] = '™';
            case 'Г': text[i] = '‚';
            case 'д': text[i] = 'љ';
            case 'Д': text[i] = 'ѓ';
            case 'е': text[i] = 'e';
            case 'Е': text[i] = 'E';
            case 'ё': text[i] = 'e';
            case 'Ё': text[i] = 'E';
            case 'ж': text[i] = '›';
            case 'Ж': text[i] = '„';
            case 'з': text[i] = '?';
            case 'З': text[i] = '?';
            case 'и': text[i] = 'њ';
            case 'И': text[i] = '…';
            case 'й': text[i] = 'ќ';
            case 'Й': text[i] = '†';
            case 'к': text[i] = 'k';
            case 'К': text[i] = 'K';
            case 'л': text[i] = 'ћ';
            case 'Л': text[i] = '‡';
            case 'м': text[i] = 'Ї';
            case 'М': text[i] = 'M';
            case 'н': text[i] = '®';
            case 'Н': text[i] = 'H';
            case 'о': text[i] = 'o';
            case 'О': text[i] = 'O';
            case 'п': text[i] = 'Ј';
            case 'П': text[i] = 'Њ';
            case 'р': text[i] = 'p';
            case 'Р': text[i] = 'P';
            case 'с': text[i] = 'c';
            case 'С': text[i] = 'C';
            case 'т': text[i] = '¦';
            case 'Т': text[i] = 'Џ';
            case 'у': text[i] = 'y';
            case 'У': text[i] = 'Y';
            case 'ф': text[i] = '~';
            case 'Ф': text[i] = 'Ѓ';
            case 'х': text[i] = 'x';
            case 'Х': text[i] = 'X';
            case 'ц': text[i] = '*';
            case 'Ц': text[i] = '‰';
            case 'ч': text[i] = '¤';
            case 'Ч': text[i] = 'Ќ';
            case 'ш': text[i] = 'Ґ';
            case 'Ш': text[i] = 'Ћ';
            case 'щ': text[i] = 'Ў';
            case 'Щ': text[i] = 'Љ';
            case 'ь': text[i] = '©';
            case 'Ь': text[i] = '’';
            case 'ъ': text[i] = '§';
            case 'Ъ': text[i] = 'ђ';
            case 'ы': text[i] = 'Ё';
            case 'Ы': text[i] = '‘';
            case 'э': text[i] = 'Є';
            case 'Э': text[i] = '“';
            case 'ю': text[i] = '«';
            case 'Ю': text[i] = '”';
            case 'я': text[i] = '¬';
            case 'Я': text[i] = '•';
            case '*': text[i] = ']';
        }
    }
}
stock OnPlayerLogin(playerid)
{
    if(IsPlayerLogged[playerid]) return J_Kick(playerid);
   	DestroyActor(aActorJoin[playerid]);

	new
		query_load[65 + MAX_PLAYER_NAME];

 	mysql_format(mysql, query_load, sizeof query_load, "SELECT * FROM `accounts` WHERE `NickName` = '%e' LIMIT 1", PlayerName[playerid]);
	mysql_tquery(mysql, query_load, "OnPlayerLoginMysql", "i", playerid);
    return 1;
}

forward OnPlayerLoginMysql(playerid);
public OnPlayerLoginMysql(playerid)
{
    new string[2100], name[60];//, NewVirMoney, qwetemp[3000];
	
    pTemp[playerid][pDialogPassword] = false;

	PI[playerid][pID] = cache_get_field_content_int(0, "ID");
	cache_get_field_content(0, "NickName", name, mysql, 60);
	cache_get_field_content(0, "Password", PI[playerid][pPassword], mysql, 32);
	cache_get_field_content(0, "Code", PI[playerid][pCode], mysql, 25);
	cache_get_field_content(0, "RegIP", PlayerRegIP[playerid], mysql, 15);
	cache_get_field_content(0, "OldIP", PlayerIp[playerid], mysql, 15);
    cache_get_field_content(0, "DateReg", PI[playerid][pDateReg], mysql, 10);
    cache_get_field_content(0, "LastIP", PI[playerid][pLastIP], mysql, 15);
    cache_get_field_content(0, "LastLogin", PI[playerid][pLastLogin], mysql, 10);
	cache_get_field_content(0, "Mail", PlayerMail[playerid], mysql, 50);
	PI[playerid][pLevel] = cache_get_field_content_int(0, "Level");
	PI[playerid][pExp] = cache_get_field_content_int(0, "Exp");
	PI[playerid][pSex] = cache_get_field_content_int(0, "Sex");
	PI[playerid][pAge] = cache_get_field_content_int(0, "Age");
	PI[playerid][pRace] = cache_get_field_content_int(0, "Race");
	PI[playerid][pAdmin] = cache_get_field_content_int(0, "Admin");
	PI[playerid][pMoney] = cache_get_field_content_int(0, "Money");
	PI[playerid][pBank] = cache_get_field_content_int(0, "Bank");
	PI[playerid][pWanted] = cache_get_field_content_int(0, "Wanted");
	PI[playerid][pFraction] = cache_get_field_content_int(0, "Fraction");
	PI[playerid][pSubfraction] = cache_get_field_content_int(0, "Subfraction");
	PI[playerid][pFractionSkin] = cache_get_field_content_int(0, "FractionSkin");
	PI[playerid][pRank] = cache_get_field_content_int(0, "Rank");
	PI[playerid][pGunLic] = cache_get_field_content_int(0, "GunLic");
	PI[playerid][pBoatLic] = cache_get_field_content_int(0, "BoatLic");
	PI[playerid][pFlyLic] = cache_get_field_content_int(0, "FlyLic");
	PI[playerid][pCarLic] = cache_get_field_content_int(0, "CarLic");
	PI[playerid][pWarns] = cache_get_field_content_int(0, "Warns");
	PI[playerid][pHouseKey] = cache_get_field_content_int(0, "HouseKey");
	PI[playerid][pBizKey] = cache_get_field_content_int(0, "BizKey");
	PI[playerid][pFWarns] = cache_get_field_content_int(0, "FWarns");
	PI[playerid][pSkin] = cache_get_field_content_int(0, "Skin");
	PI[playerid][pTelNum] = cache_get_field_content_int(0, "TelNum");
	PI[playerid][pPhone] = cache_get_field_content_int(0, "Phone");
    PI[playerid][pMats] = cache_get_field_content_int(0, "Mats");
    PI[playerid][pPackets] = cache_get_field_content_int(0, "Packets");
    PI[playerid][pDrugs] = cache_get_field_content_int(0, "Drugs");
    PI[playerid][pJob] = cache_get_field_content_int(0, "Job");
    PI[playerid][pMuteTime] = cache_get_field_content_int(0, "MuteTime");
    PI[playerid][pJailTime] = cache_get_field_content_int(0, "JailTime");
    PI[playerid][pSpawn] = cache_get_field_content_int(0, "Spawn");
    PI[playerid][pMask] = cache_get_field_content_int(0, "Mask");
    PI[playerid][pPhoneBook] = cache_get_field_content_int(0, "PhoneBook");
    PI[playerid][pSDPistol_Skill] = cache_get_field_content_int(0, "SDPistol_Skill");
    PI[playerid][pEagle_Skill] = cache_get_field_content_int(0, "Eagle_Skill");
    PI[playerid][pShotGun_Skill] = cache_get_field_content_int(0, "ShotGun_Skill");
    PI[playerid][pMP5_Skill] = cache_get_field_content_int(0, "MP5_Skill");
    PI[playerid][pAK47_Skill] = cache_get_field_content_int(0, "AK47_Skill");
    PI[playerid][pM4_Skill] = cache_get_field_content_int(0, "M4_Skill");
    PI[playerid][pZKP] = cache_get_field_content_int(0, "ZKP");
    PI[playerid][pHeal] = cache_get_field_content_int(0, "Heal");
    PI[playerid][pCheepses] = cache_get_field_content_int(0, "Cheeps");
    PI[playerid][pRadio] = cache_get_field_content_int(0, "Radio");
    PI[playerid][pVirMoney] = cache_get_field_content_int(0, "VirMoney");
    PI[playerid][pClip] = cache_get_field_content_int(0, "Clip");
    PI[playerid][pIn_Skill] = cache_get_field_content_int(0, "In_Skill");
    cache_get_field_content(0, "Merrit", PI[playerid][pMerrit], mysql, 24);
    PI[playerid][pShowCase] = cache_get_field_content_int(0, "ShowCase");
    PI[playerid][pHealth] = cache_get_field_content_int(0, "HP");
    PI[playerid][pWarnTime] = cache_get_field_content_int(0, "WarnTime");

    new weaponsstr[500];

    cache_get_field_content(0, "Weapons", weaponsstr, mysql);
	
    GetPlayerIp(playerid,PlayerIp[playerid],16);
    new idx;
    _ResetGun(playerid);
	for(new x; x < 13; x ++)
	{
	    PI[playerid][pGuns][x] = strval(strtok(weaponsstr, idx));
	    PI[playerid][pAmmos][x] = strval(strtok(weaponsstr, idx));
	}

	/*new trashstr[140];

	cache_get_field_content(0, "TrashCheck", trashstr, mysql);
	sscanf(trashstr, "p<|>iiiiiiiiiiiiiiiiiiii", 	PI[playerid][pTrashCheck][0], PI[playerid][pTrashCheck][1], PI[playerid][pTrashCheck][2],
													PI[playerid][pTrashCheck][3], PI[playerid][pTrashCheck][4], PI[playerid][pTrashCheck][5],
													PI[playerid][pTrashCheck][6], PI[playerid][pTrashCheck][7], PI[playerid][pTrashCheck][8],
													PI[playerid][pTrashCheck][9], PI[playerid][pTrashCheck][10], PI[playerid][pTrashCheck][11],
													PI[playerid][pTrashCheck][12], PI[playerid][pTrashCheck][13], PI[playerid][pTrashCheck][14],
													PI[playerid][pTrashCheck][15], PI[playerid][pTrashCheck][16], PI[playerid][pTrashCheck][17],
													PI[playerid][pTrashCheck][18], PI[playerid][pTrashCheck][19], PI[playerid][pTrashCheck][20]);

    PI[playerid][pTrashWallet] = cache_get_field_content_int(0, "TrashWallet");
    PI[playerid][pTrashBottle] = cache_get_field_content_int(0, "TrashBottle");
    PI[playerid][pTrashBank] = cache_get_field_content_int(0, "TrashBank");
    PI[playerid][pTrashPaper] = cache_get_field_content_int(0, "TrashPaper");
    PI[playerid][pTrashBung] = cache_get_field_content_int(0, "TrashBung");
    PI[playerid][pTrashPhone] = cache_get_field_content_int(0, "TrashPhone");*/
    PI[playerid][pNation] = cache_get_field_content_int(0, "Nation");
    PI[playerid][pJailKey] = cache_get_field_content_int(0, "JailKey");
    PI[playerid][pCars] = cache_get_field_content_int(0, "Cars");
    PI[playerid][pKit] = cache_get_field_content_int(0, "Kit");
    PI[playerid][pWatch] = cache_get_field_content_int(0, "Watch");
    PI[playerid][pSlotItem][0] = cache_get_field_content_int(0, "pSlotItem0");
    PI[playerid][pSlotItem][1] = cache_get_field_content_int(0, "pSlotItem1");
    PI[playerid][pSlotItem][2] = cache_get_field_content_int(0, "pSlotItem2");
    PI[playerid][pSlotItem][3] = cache_get_field_content_int(0, "pSlotItem3");
    PI[playerid][pSlotItem][4] = cache_get_field_content_int(0, "pSlotItem4");
    PI[playerid][pSlotItem][5] = cache_get_field_content_int(0, "pSlotItem5");

	new
		items_head[70],
		items_glass[70],
		items_watch[70],
		items_mask[70],
		items_hp[70],
		items_bag[70];

	cache_get_field_content(0, "inventory_head", items_head, mysql);
	sscanf(items_head, "p<|>iiiii", inventory_head[playerid][0], inventory_head[playerid][1], inventory_head[playerid][2], inventory_head[playerid][3], inventory_head[playerid][4]);

	cache_get_field_content(0, "inventory_glass", items_glass, mysql);
	sscanf(items_glass, "p<|>iiiii", inventory_glass[playerid][0], inventory_glass[playerid][1], inventory_glass[playerid][2], inventory_glass[playerid][3], inventory_glass[playerid][4]);

	cache_get_field_content(0, "inventory_watch", items_watch, mysql);
	sscanf(items_watch, "p<|>iiiii", inventory_watch[playerid][0], inventory_watch[playerid][1], inventory_watch[playerid][2], inventory_watch[playerid][3], inventory_watch[playerid][4]);

	cache_get_field_content(0, "inventory_mask", items_mask, mysql);
	sscanf(items_mask, "p<|>iiiii", inventory_mask[playerid][0], inventory_mask[playerid][1], inventory_mask[playerid][2], inventory_mask[playerid][3], inventory_mask[playerid][4]);

	cache_get_field_content(0, "inventory_hp", items_hp, mysql);
	sscanf(items_hp, "p<|>iiiii", inventory_hp[playerid][0], inventory_hp[playerid][1], inventory_hp[playerid][2], inventory_hp[playerid][3], inventory_hp[playerid][4]);

	cache_get_field_content(0, "inventory_bag", items_bag, mysql);
	sscanf(items_bag, "p<|>iiiii", inventory_bag[playerid][0], inventory_bag[playerid][1], inventory_bag[playerid][2], inventory_bag[playerid][3], inventory_bag[playerid][4]);

	new banks[60];
	cache_get_field_content(0, "BankID", banks, mysql);
	sscanf(banks, "p<|>iii", PI[playerid][pBankID][0], PI[playerid][pBankID][1], PI[playerid][pBankID][2]);

    PI[playerid][pBankCount] = cache_get_field_content_int(0, "BankCount");
    PI[playerid][pTester] = cache_get_field_content_int(0, "Tester");
    PI[playerid][pVKID] = cache_get_field_content_int(0, "VKID");
    PI[playerid][pReturnHouse] = cache_get_field_content_int(0, "ReturnHouse");
    PI[playerid][pReturnBusiness] = cache_get_field_content_int(0, "ReturnBusiness");
    PI[playerid][pReturnFilling] = cache_get_field_content_int(0, "ReturnFilling");
    PI[playerid][pPlayed] = cache_get_field_content_int(0, "Played");
    PI[playerid][pArmyRank] = cache_get_field_content_int(0, "ArmyRank");
    PI[playerid][pArmyTime] = cache_get_field_content_int(0, "ArmyTime");
    PI[playerid][pPTS] = cache_get_field_content_int(0, "PTS");
    PI[playerid][pMedCard] = cache_get_field_content_int(0, "MedCard");
    PI[playerid][pVehicleKey] = cache_get_field_content_int(0, "VehicleKey");
    PI[playerid][pWedding] = cache_get_field_content_int(0, "Wedding");
    cache_get_field_content(0, "DateInvite", PI[playerid][pDateInvite], mysql, 25);
    cache_get_field_content(0, "LastRank", PI[playerid][pLastRank], mysql, 25);
    PI[playerid][pv_Fraction] = cache_get_field_content_int(0, "v_Fraction");
    PI[playerid][pv_Subfraction] = cache_get_field_content_int(0, "v_Subfraction");
    PI[playerid][pv_Rank] = cache_get_field_content_int(0, "v_Rank");
    PI[playerid][pv_FWarns] = cache_get_field_content_int(0, "v_FWarns");
    PI[playerid][pv_Days] = cache_get_field_content_int(0, "v_Days");
    PI[playerid][pv_Status] = cache_get_field_content_int(0, "v_Status");
    PI[playerid][pv_FractionSkin] = cache_get_field_content_int(0, "v_FractionSkin");
    PI[playerid][pDisease] = cache_get_field_content_int(0, "Disease");
    PI[playerid][pLastEat] = cache_get_field_content_int(0, "LastEat");
    PI[playerid][pMesDisease] = cache_get_field_content_int(0, "MesDisease");
    PI[playerid][pVaccine][0] = cache_get_field_content_int(0, "Vaccine[0]");
    PI[playerid][pVaccine][1] = cache_get_field_content_int(0, "Vaccine[1]");
    PI[playerid][pVaccine][2] = cache_get_field_content_int(0, "Vaccine[2]");
    PI[playerid][pVaccine][3] = cache_get_field_content_int(0, "Vaccine[3]");
    PI[playerid][pVaccine][4] = cache_get_field_content_int(0, "Vaccine[4]");
    PI[playerid][pVaccine][5] = cache_get_field_content_int(0, "Vaccine[5]");
    PI[playerid][pKillList] = cache_get_field_content_int(0, "KillList");
    PI[playerid][pGangKey] = cache_get_field_content_int(0, "GangKey");
    PI[playerid][pSellZones] = cache_get_field_content_int(0, "SellZones");
    PI[playerid][pPrison] = cache_get_field_content_int(0, "Prison");
    PI[playerid][pFine] = cache_get_field_content_int(0, "Fine");
    PI[playerid][pDivision] = cache_get_field_content_int(0, "Division");
    PI[playerid][pSalary] = cache_get_field_content_int(0, "Salary");
    PI[playerid][pAdvertTime] = cache_get_field_content_int(0, "AdvertTime");
    PI[playerid][pFlyers] = cache_get_field_content_int(0, "Flyers");
    PI[playerid][pFlyersCount] = cache_get_field_content_int(0, "FlyersCount");
    PI[playerid][pJailAdmin] = cache_get_field_content_int(0, "JailAdmin");
    PI[playerid][pCard] = cache_get_field_content_int(0, "Card");
    PI[playerid][pBonus] = cache_get_field_content_int(0, "Bonus");
    PI[playerid][pRope] = cache_get_field_content_int(0, "Rope");
    PI[playerid][pTalkie] = cache_get_field_content_int(0, "Talkie");
    PI[playerid][pFamily] = cache_get_field_content_int(0, "Family");
    PI[playerid][pCharity] = cache_get_field_content_int(0, "Charity");
    PI[playerid][pPointsOrg] = cache_get_field_content_int(0, "PointsOrg");
    PI[playerid][pPointsLoader] = cache_get_field_content_int(0, "PointsLoader");
    PI[playerid][pPointsRoad] = cache_get_field_content_int(0, "PointsRoad");
    PI[playerid][pPointsFactory] = cache_get_field_content_int(0, "PointsFactory");
    PI[playerid][pTotalDon] = cache_get_field_content_int(0, "TotalDon");
    PI[playerid][pAlley] = cache_get_field_content_int(0, "Alley");
    PI[playerid][pAlleyDays] = cache_get_field_content_int(0, "AlleyDays");
    PI[playerid][pQuest] = cache_get_field_content_int(0, "Quest");
    PI[playerid][pQuestStatus] = cache_get_field_content_int(0, "QuestStatus");
    PI[playerid][pQuestProcess] = cache_get_field_content_int(0, "QuestProcess");
    PI[playerid][pPromo] = cache_get_field_content_int(0, "Promo");
    PI[playerid][pPromoSalary] = cache_get_field_content_int(0, "PromoSalary");
    PI[playerid][pDaysExp] = cache_get_field_content_int(0, "DaysExp");
    PI[playerid][pDaysSalary] = cache_get_field_content_int(0, "DaysSalary");
    PI[playerid][pCPromo] = cache_get_field_content_int(0, "CPromo");
    PI[playerid][pPromoLvl] = cache_get_field_content_int(0, "PromoLvl");
    PI[playerid][pPromoBonus] = cache_get_field_content_int(0, "PromoBonus");
    cache_get_field_content(0, "GoogleAuth", PI[playerid][pGoogleAuth], mysql, 18);
    PI[playerid][pGoogleAuthCheck] = cache_get_field_content_int(0, "GoogleAuthCheck");
    PI[playerid][pGoogleAuthStatus] = cache_get_field_content_int(0, "GoogleAuthStatus");
    PI[playerid][pBanActivate] = cache_get_field_content_int(0, "BanActivate");
    PI[playerid][pBan] = cache_get_field_content_int(0, "Ban");
    PI[playerid][pWarnMessage] = cache_get_field_content_int(0, "WarnMessage");
    PI[playerid][pAdminTime] = cache_get_field_content_int(0, "AdminTime");
    PI[playerid][pWarnStatus] = cache_get_field_content_int(0, "WarnStatus");
    PI[playerid][pPick] = cache_get_field_content_int(0, "pick");
    cache_get_field_content(0, "WarnNick", PI[playerid][pWarnNick], mysql, 24);
    cache_get_field_content(0, "WarnReason", PI[playerid][pWarnReason], mysql, 40);
    PI[playerid][pDash] = cache_get_field_content_int(0, "Dash");
	PI[playerid][pBag] = cache_get_field_content_int(0, "Bag");
	PI[playerid][pTruckSkill] = cache_get_field_content_int(0, "TruckSkill");
	
    format(string,sizeof(string),"UPDATE `accounts` SET `OldIP` = '%s',`Online_status`='%i' WHERE `ID` = '%i'",PlayerIp[playerid],playerid,PI[playerid][pID]);
    mysql_tquery(mysql, string);

	if(PI[playerid][pBan] && !PI[playerid][pBanActivate])
    {
		new query[79 + 9];
		format(query, sizeof query, "SELECT `admin`, `reason` FROM `ban` WHERE `takeid` = '%d'", PI[playerid][pID]);
		new Cache:result = mysql_query(mysql, query);
		
		if(cache_get_row_count(mysql))
		{
	        new
				frmt_offban_message[145],
	            query_update[110],
				admin,
				nickname[MAX_PLAYER_NAME],
				reason[32];

			admin = cache_get_row_int(0, 0);
			cache_get_row(0, 1, reason, mysql);
			GetPlayerNameByID(admin, nickname);
				
			format(frmt_offban_message, sizeof frmt_offban_message, "Вы получили оффлайн бан на %d дней от администратора %s. Причина: %s", PI[playerid][pBan], nickname, reason);
			SendClientMessage(playerid, COLOR_RED, frmt_offban_message);

	        format(query_update, sizeof query_update, "UPDATE `ban` SET `status` = '1' WHERE `takeid` = '%d'", PI[playerid][pID]);
	        mysql_tquery(mysql, query_update);
	        format(query_update, sizeof query_update, "UPDATE `accounts` SET `BanActivate` = '1' WHERE `ID` = '%d'", PI[playerid][pID]);
	        mysql_tquery(mysql, query_update);
			J_Kick(playerid);
		}
		else
		{
		    new
		        query_update[170];
		        
	        format(query_update, sizeof query_update, "UPDATE `accounts` SET `BanActivate` = '0', `Ban` = '0' WHERE `ID` = '%d'", PI[playerid][pID]);
	        mysql_tquery(mysql, query_update);

		    format(query_update, sizeof query_update, "DELETE FROM `ban` WHERE `takeid` = '%d'", PI[playerid][pID]);
		    mysql_tquery(mysql, query_update);
		}
        cache_delete(result, mysql);
	}
	if(PI[playerid][pWarnStatus])
	{
	    new
	        frmt_offwarn_message[140];
	        
	    PI[playerid][pWarnTime] += PI[playerid][pWarnStatus];
	    PI[playerid][pWarnStatus] = 0;
	    UpdatePlayerData(playerid, "WarnTime", PI[playerid][pWarnTime]);
	    UpdatePlayerData(playerid, "WarnStatus", PI[playerid][pWarnStatus]);

		format(frmt_offwarn_message, sizeof frmt_offwarn_message, "Вы получили оффлайн предупреждение от администратора %s. Причина: %s", PI[playerid][pWarnNick], PI[playerid][pWarnReason]);
		SendClientMessage(playerid, COLOR_RED, frmt_offwarn_message);
	}
 	IsPlayerLogged[playerid] = true;
	//if(!IsARPName(Name(playerid)) && RP_Names) ShowPlayerDialogEx(playerid,RENAME_DIALOG,1,"Введите новый ник","{FFFFFF}Ваш ник не соответствует правилам сервера\nВведите новый ник в окошко и нажмите {9ACD32}Далее.","Далее","");
	SetPlayerScore(playerid,PI[playerid][pLevel]);
	GivePlayerMoney(playerid,PI[playerid][pMoney]);
	J_SetPlayerHealth(playerid,PI[playerid][pHealth]);

	//GetNumberCars(playerid,PI[playerid][pCars]);
	if(Clother[playerid] != 0)
	{
		format(string, sizeof(string), "~w~Welcome ~n~~b~ %s",Name(playerid));
		GameTextForPlayer(playerid, string, 5000, 1);
	}

	if(PI[playerid][pPromo])
    	gPromo[PI[playerid][pPromo]-1][pcOnline]++;

    
	NoEnterPickup[playerid]=6;

	new newstring[24], iplast[24];
	GetPlayerIp(playerid,iplast,16);
	SetString(PI[playerid][pLastIP], iplast);

	new Year, Month, Day;
	getdate(Year, Month, Day);

	new Hour, Mon, Sec;
	gettime(Hour,Mon,Sec);

	format(newstring, sizeof newstring, "%d-%d-%d", Day, Month, Year);
	SetString(PI[playerid][pLastLogin], newstring);
	
	new
	    query_save_last[126];
	    
	format(query_save_last, sizeof query_save_last, "UPDATE `accounts` SET `LastLogin` = '%s', `LastIP` = '%s' WHERE `ID` = '%d'", PI[playerid][pLastLogin], PI[playerid][pLastIP], PI[playerid][pID]);
	mysql_tquery(mysql, query_save_last);
	
	aml(-1, playerid, "", PlayerIp[playerid],playerid);
	
	
 	if(PI[playerid][pReturnHouse] > 0)
	{
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Ваш дом был продан государству за неуплату!");
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Если у Вас был транспорт, он тоже был продан");
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Получить 80 процентов от стоимости списанного имущества вы можете в банке");
	}
 	if(PI[playerid][pReturnBusiness] > 0)
	{
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Ваш бизнес был продан государству за неуплату!");
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Получить 80 процентов от стоимости списанного имущества вы можете в банке");
	}
 	if(PI[playerid][pReturnFilling] > 0)
	{
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Ваша АЗС была продано государству за неуплату!");
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Получить 80 процентов от стоимости списанного имущества вы можете в банке");
	}
 	if(PI[playerid][pv_Status])
	{
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Срок вашего отпуска истек. Теперь вы снова состоите в организации");
	    PI[playerid][pv_Status] = 0;
	    UpdatePlayerData(playerid, "v_Status", PI[playerid][pv_Status]);
	}
	if(PI[playerid][pWarnMessage])
	{
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Срок всех Ваших предупреждений истек");
	    PI[playerid][pWarnMessage] = 0;
	    UpdatePlayerData(playerid, "WarnMessage", PI[playerid][pWarnMessage]);
	}
    if(PI[playerid][pAdmin] && PI[playerid][pFraction])
	{
		SendClientMessage(playerid, COLOR_GREY, !"Вы были автоматически уволены из организации, т.к. вы Администратор");
		PI[playerid][pFraction] = 0;
		UpdatePlayerData(playerid, "Fraction", PI[playerid][pFraction]);
		PI[playerid][pRank] = 0;
		UpdatePlayerData(playerid, "Rank", PI[playerid][pRank]);
		PI[playerid][pFractionSkin] = 0;
		UpdatePlayerData(playerid, "FractionSkin", PI[playerid][pFractionSkin]);
		PI[playerid][pSubfraction] = 0;
		UpdatePlayerData(playerid, "Subfraction", PI[playerid][pSubfraction]);
	}
    if(PI[playerid][pAdmin] >= 1)
	{
		ShowPlayerDialogEx(playerid, 211, 1, !"{74FFA0}Авторизация", !"{FFFFFF}Введите админ-пароль:", !"ОК", !"Отмена");
		for(new i; i < max_cheat_text; i++)
			TextDrawShowForPlayer(playerid, CheatText[0][i]), TextDrawShowForPlayer(playerid, CheatText[1][i]);
	}
	if(PI[playerid][pTester])
	{
		if(!PI[playerid][pVKID])
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К Вашему аккаунту не подключен ВКонтакте!"), J_Kick(playerid);

		temp_tester_code[playerid] = RandomEx(100000,999999);

		new
		    frmt_code[7];

		format(frmt_code, sizeof frmt_code, "%d", temp_tester_code[playerid]);

		SendToVK(frmt_code, PI[playerid][pVKID]);

		ShowPlayerDialogEx(playerid, 213, DIALOG_STYLE_INPUT, !"Авторизация", !"{FFFFFF}Введите код, отправленный ботом ВКонтакте", !"ОК", !"Отмена");
	}
	if(PI[playerid][pDisease])
	{
		new
		    frmt_disease[128];
		    
	    format(frmt_disease, sizeof frmt_disease, "Вы больны болезнью {FF0000}%s{FFFFFF}. Обратитесь в ближайшую больницу для лечения", gDiseaseName[PI[playerid][pDisease]-1]);
	    SendClientMessage(playerid, COLOR_WHITE, frmt_disease);
	    if(PI[playerid][pDisease] == 2 || PI[playerid][pDisease] == 3 || PI[playerid][pDisease] == 6)
	        temp_disease_timer[playerid] = 180;
    }
 	if(PI[playerid][pCars] != 0)//загружаем авто при авторизации
    {
		new carID = PI[playerid][pCars];
		new i = GetCarSlot(carID);
		new modelid = CarInfo[i][cModelID];
		new houseid = PI[playerid][pHouseKey]-1;
		if(PI[playerid][pHouseKey] != 0)
		{
			if(GetString(HouseInfo[houseid][hOwner],Name(playerid)))
			{
				new vehicleid = CreateVehicle(Transport[modelid][trModel], HouseInfo[houseid][hPark_X], HouseInfo[houseid][hPark_Y], HouseInfo[houseid][hPark_Z], HouseInfo[houseid][hPark_R], CarInfo[i][cColor_1], CarInfo[i][cColor_2], -1);
				CarInfo[i][cVehID] = vehicleid;

				if(CarInfo[i][cHealth] < 300.0)
					CarInfo[i][cHealth] = 1000.0;

				SetVehicleHealth(vehicleid, CarInfo[i][cHealth]);
				ToggleLock(vehicleid);
				VehicleInfo[vehicleid][vFuel] = CarInfo[i][cFuel];
				VehicleInfo[vehicleid][vMillage] = CarInfo[i][cMilage];
				VehicleInfo[vehicleid][vHealth] = CarInfo[i][cHealth];
				VehicleInfo[vehicleid][vOwnerid] = CarInfo[i][cOwnerID];
                SetVehicleNumberPlate(vehicleid, CarInfo[i][cNumber]);
                SetDoorsStatus(vehicleid, 1);
                
				for(new tn; tn < 14; tn++)
					if(CarInfo[i][cTuning][tn] != 0) AddVehicleComponent(vehicleid, CarInfo[i][cTuning][tn]);

				ChangeVehiclePaintjob(vehicleid, CarInfo[i][cPaintJob]);

				
			}
		}
	}
	if(IsAGang(playerid) && IsCapture)
	{
		for(new td; td < 8; td++)
			TextDrawShowForPlayer(playerid, tdCapture[td]);
			
        GangZoneFlashForPlayer(playerid, GZMZ[captureID][gID], GetGZColorF(PI[playerid][pFraction]));
	}
	if(IsAMafia(playerid) && IsBizWar == 1)
	{
		GangZoneShowForPlayer(playerid, gMafiaZone, 0xFF0000AA);
		TextDrawShowForPlayer(playerid, BizWarTimer);
	}
	if(IsAMafia(playerid) && IsBizWar == 2)
	{
		for(new td; td < 8; td++)
			TextDrawShowForPlayer(playerid, tdBizWar[td]);
	}
	
	if(PI[playerid][pFraction])
	{
		if(strlen(gNotice[PI[playerid][pFraction]-1][PI[playerid][pSubfraction]][nName]))
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFFF00}/advert{FFFFFF} на базе организации для просмотра объявления");
	}

	if(PI[playerid][pDaysExp] > 0 && PI[playerid][pDaysSalary] > 0)
 		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У Вас активен бонус удвоенного опыта и удвоенной зарплаты на начальных работах");

	else if(PI[playerid][pDaysExp] > 0)
 		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У Вас активен бонус удвоенного опыта");

	else if(PI[playerid][pDaysSalary] > 0)
 		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У Вас активен бонус удвоенной зарплаты на начальных работах");

	TogglePlayerSpectating(playerid, false);
	UpdateDonate(playerid);
	
	//SendClientMessage(playerid, COLOR_WHITE, !"{CA6E7E}[TEST] {FFFFFF}Внимание! Идет окончательное тестирование! Все баги отправлять в BRP Tracker");
	//SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFFF00}/ftest{FFFFFF} для быстрого вступления в организацию");
    if(donate_x2 == 1) SendClientMessage(playerid, 0x33AA33FF, !"Внимание! Сегодня действует скидка на донат услуги!");
	if(exp_x2 == 1) SendClientMessage(playerid, 0x33AA33FF, !"Внимание! Сегодня действует акция удвоенного EXP!");
	
	for(new i; i < 13; i++)
	{
	    if(PI[playerid][pGuns][i] != 0 && PI[playerid][pAmmos][i] != 0)
			_SetGun(playerid, PI[playerid][pGuns][i], PI[playerid][pAmmos][i]);
	}
	return true;
}

stock Float:GetPlayerCheckHealth(playerid)
{
	new Float:Health;
	GetPlayerHealth(playerid, Health);
	return (PI[playerid][pHealth] < Health)?PI[playerid][pHealth]:Health;
}
stock Float:GetPlayerCheckArmour(playerid)
{
	new Float:Armour;
	GetPlayerArmour(playerid, Armour);
	return (PI[playerid][pArmour] < Armour)?PI[playerid][pArmour]:Armour;
}
stock SetWeaponNew(playerid)
{
    ResetPlayerWeapons(playerid);

	return 1;
}

stock SetAdminLevel(playerid,level)
{
    PI[playerid][pAdmin] = level;
	UpdatePlayerData(playerid, "Admin", PI[playerid][pAdmin]);
	return true;
}
stock ReplaceText(text[])
{
	for(new i; i < strlen(text); i ++)
	{
	    if('0' <= text[i] <= '9') text[i] = '*';
	}
	return true;
}

stock GetPlayerID(name[])
{
    new player_name[MAX_PLAYER_NAME];
   	foreach(new i : Player)
    {
		if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
			continue;
			
        GetPlayerName(i, player_name, MAX_PLAYER_NAME);
        
        if(!strcmp(player_name, name))
            return i;
    }
    return INVALID_PLAYER_ID;
}
public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if(!IsPlayerConnected(playerid))
		return 0;
		
	if(!IsPlayerLogged[playerid])
	    return 0;
	    
	if(PI[playerid][pDialog])
	{
 		SendClientMessage(playerid, COLOR_GREY, !"Нельзя использовать команды, пока открыт диалог");
 		return 0;
	}

	if(PI[playerid][pAdmin] > 0 && !ADuty[playerid])
	{
		ShowPlayerDialogEx(playerid, 211, 1, !"{74FFA0}Авторизация", !"{FFFFFF}Введите админ-пароль:", !"ОК", !"Отмена");
		return 0;
	}
	
	return 1;
}
stock ReplaceWord(word[])
{
	for(new i; i < strlen(word); i ++)
	{
	    switch(word[i])
	    {
	        case 'A': word[i] = 'a';
	        case 'B': word[i] = 'b';
	        case 'C': word[i] = 's';
	        case 'D': word[i] = 'd';
	        case 'E': word[i] = 'e';
	        case 'F': word[i] = 'f';
	        case 'G': word[i] = 'g';
	        case 'H': word[i] = 'h';
	        case 'I': word[i] = 'i';
	        case 'J': word[i] = 'j';
	        case 'K': word[i] = 'k';
	        case 'L': word[i] = 'l';
	        case 'M': word[i] = 'm';
	        case 'N': word[i] = 'n';
	        case 'O': word[i] = 'o';
	        case 'P': word[i] = 'p';
	        case 'Q': word[i] = 'q';
	        case 'R': word[i] = 'r';
	        case 'S': word[i] = 's';
	        case 'T': word[i] = 't';
	        case 'U': word[i] = 'u';
	        case 'V': word[i] = 'v';
	        case 'W': word[i] = 'w';
	        case 'X': word[i] = 'x';
	        case 'Y': word[i] = 'y';
	        case 'Z': word[i] = 'z';
	    }
	}
}

stock IsARPName(Name[])
{
	if(strlen(Name)>19) return 0;
	if(!strlen(Name)) return 0;
	if(!strcmp("Developer", Name, false)) return 1;
	new simb_, RP_Name[2][24], num;
	for(new i = 0;i < strlen(Name);i ++)
	{
	    if(Name[i] == '_') {simb_ ++; num=i;}
	}
	if(simb_ != 1) return false;
	strmid(RP_Name[0], Name, 0, num-1);
	strmid(RP_Name[1], Name, num+1, strlen(Name));
	//sscanf(Name,"p<_>s[24]s[24]",RP_Name[0],RP_Name[1]);
	if( !IsAGoodName(RP_Name[0]) || !IsAGoodName(RP_Name[1]) ) return false;
	return true;
}
stock IsAGoodName(Name[])
{
	new NameChars;
	if(strlen(Name) < 2) return false;
	if(Name[0] < 'A' || Name[0] > 'Z') return false;
	for(new i = 1;i < strlen(Name);i ++)
	{
	    if(Name[i] < 'a' || Name[i] > 'z')
		{
		    if(Name[i] >= 'A' && Name[i] <= 'Z') NameChars ++;
		    else return false;
		}
	    if(NameChars > 1) return false;
	}
	return true;
}
stock IsABannedWeapon(gunid)
{
	switch(gunid)
	{
	    case 2,7,9,15,16,18,26,32,35..40,44,45: return true;
	}
	return false;
}
stock IsAFireGun(gunid)
{
	return (gunid >= 22 && gunid <= 38);
}
stock IsACheatState(playerid)
{
    new State = GetPlayerState(playerid);
	return (State != PLAYER_STATE_NONE && State != PLAYER_STATE_SPECTATING && State != PLAYER_STATE_SPAWNED);
}
stock EnableGPSForPlayer(playerid, Float:x, Float:y, Float:z)
{
	gpss[playerid]=1;
	SetPlayerRaceCheckpoint(playerid, 1, Float:x, Float:y, Float:z, Float:x, Float:y, Float:z, 4.0);
	GameTextForPlayer(playerid, "GPS: ON", 0, 1);
	return true;
}
stock CheckPointForPlayer(playerid, Float:x, Float:y, Float:z)
{
	gpss[playerid]=1;
	SetPlayerRaceCheckpoint(playerid, 1, Float:x, Float:y, Float:z, Float:x, Float:y, Float:z, 4.0);
	return true;
}


stock GunName(gunid)
{
	new gunname[34];
	SetString(gunname,WeaponNames[gunid]);
	return gunname;
}
stock SetVehicleSpeed(vehicleid,mph)
{
    new Float:Vx, Float:Vy, Float:Vz ,Float:speeds, Float:multiple;
    GetVehicleVelocity(vehicleid,Vx,Vy,Vz);
    speeds = floatsqroot(Vx*Vx + Vy*Vy + Vz*Vz);
    if(speeds > 0)
    {
        multiple = (mph / (speeds * 120));
        return SetVehicleVelocity(vehicleid, Vx*multiple, Vy*multiple, Vz*multiple);
    }
    return false;
}

stock GetPlayerVehicleSpeedZ(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid)) return true;
    new Float:X, Float:Y, Float:Z;
	GetVehicleVelocity(GetPlayerVehicleID(playerid),X,Y,Z);
	return floatround( floatsqroot( X * X + Y * Y) * 180.0 );
}

stock GetPlayerVehicleSpeed(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid)) return true;
    new Float:X, Float:Y, Float:Z;
	GetVehicleVelocity(GetPlayerVehicleID(playerid),X,Y,Z);
	return floatround( floatsqroot( X * X + Y * Y + Z * Z ) * 180.0 );
}
stock PlayerSpeed(playerid)
{
    new Float:X, Float:Y, Float:Z;
    if(!IsPlayerInAnyVehicle(playerid)) GetPlayerVelocity(playerid,X,Y,Z);
    return floatround( floatsqroot( X * X + Y * Y + Z * Z ) * 170.0 );
}
stock VehicleSpeed(carid)
{
    new Float:X, Float:Y, Float:Z;
	GetVehicleVelocity(carid,X,Y,Z);
    return floatround( floatsqroot( X * X + Y * Y + Z * Z ) * 180.0 );
}


public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
    pTemp[playerid][pCarDmg] += 1;
    
	if(vehicleid >= vBus[0] && vehicleid <= vBus[1])
	{
		if(VehicleInfo[vehicleid][vBusOwner] != INVALID_PLAYER_ID)
			AntiCheatGetVehicleHealth(vehicleid, temp_bus_damage[VehicleInfo[vehicleid][vBusOwner]]);
	}
	return true;
}
stock SetHostName(const name[])
{
	new string[100];
	format(string,sizeof(string),"hostname %s",name);
	return SendRconCommand(string);
}
stock CheckPassengers(vehicleid)
{
	for(new i; i < 10; i ++)
	{
	    if(VehicleSeat[vehicleid][i] != INVALID_PLAYER_ID && !IsPlayerInVehicle(VehicleSeat[vehicleid][i], vehicleid)) VehicleSeat[vehicleid][i] = INVALID_PLAYER_ID;
	}
	return true;
}

stock PayDay()
{
	new string[900];
	SaveInforamtion();
	
	k1 = RandomEx(1,5);
	k2 = RandomEx(1,5);
	k3 = RandomEx(1,5);
	
  	for(new i = 0; i < total_players; i++)
	{
	    if(!IsPlayerConnected(i)) continue;
	    if(IsPlayerLogged[i])
	    {
			if(PI[i][pAdmin])
				UpdatePlayerData(i, "AdminTime", PI[i][pAdminTime]);

   			new temp_pd_message;
   			if(pl_afk_time[i] >= 60)
			{
			 	SendClientMessage(i, COLOR_GREY, !"Вы не получили PayDay, потому что были в АФК");
			 	PI[i][pPlayed] = 0;
	 			continue;
			}
			if(!payday_admin)
			{
		        if(PI[i][pPlayed] < 1200)
				{
				 	SendClientMessage(i, COLOR_GREY, !"Для получения PayDay вы должны отыграть минимум 25 минут.");
				 	PI[i][pPlayed] = 0;
		 			continue;
				}
			}

   			if(PI[i][pDaysExp] > 0 || exp_x2 == 1)
   			    PI[i][pExp] += 2;

   			else
	        	PI[i][pExp]++;


	        new money, salary;
	        SendClientMessage(i, COLOR_WHITE, !"      Банковский чек");
	        SendClientMessage(i, COLOR_WHITE, !"---------------------------------");
	        /*if(GetTeamID(i) > 0)
	        {
	        	money += OrgSalary[GetTeamID(i)][PI[i][pRank]];
	        	format(string,sizeof(string),"     Зарплата: {42B02C}%d$",OrgSalary[GetTeamID(i)][PI[i][pRank]]);
	        	SendClientMessage(i, COLOR_WHITE, string);
	        }*/
	        if(!pTemp[i][pTempLeader])
	        {
		        if(PI[i][pFraction] && PI[i][pCard])
		        {
					PI[i][pPointsOrg] += 2;
		        }
		        if(IsAGang(i))
		        {
					money += gangzone_total[IsAGang(i)]*70;
					format(string, sizeof string, "     Зарплата: {42B02C}%d$", gangzone_total[IsAGang(i)]*70);
					SendClientMessage(i, COLOR_WHITE, string);
		        }
		        else if(IsAMafia(i))
				{
					money += gFractionSalary[PI[i][pFraction]-1][PI[i][pRank]-1];
					format(string, sizeof string, "     Зарплата: {42B02C}%d$", gFractionSalary[PI[i][pFraction]-1][PI[i][pRank]-1]);
					SendClientMessage(i, COLOR_WHITE, string);
				}
				else if(PI[i][pFraction] == 1 || PI[i][pFraction] == 7 || PI[i][pFraction] == 8 || PI[i][pFraction] == 9 || PI[i][pFraction] == 10 || PI[i][pFraction] == 11)
				{
				    if(OrgInfo[PI[i][pFraction]-1][oMoney] > gFractionSalary[PI[i][pFraction]-1][PI[i][pRank]-1])
				    {
				        new
							nalog;

				        if(PI[i][pBonus] > 0)
				            salary += PI[i][pBonus];

						if(gSalaryNalog > 0)
						{
						    nalog = (gFractionSalary[PI[i][pFraction]-1][PI[i][pRank]-1]/100)*gSalaryNalog;
						    salary += gFractionSalary[PI[i][pFraction]-1][PI[i][pRank]-1]-nalog;
						    OrgInfo[9][oMoney] += nalog;
						}

						else
							salary += gFractionSalary[PI[i][pFraction]-1][PI[i][pRank]-1];

			        	format(string, sizeof string, "     Зарплата: {42B02C}%d$", salary);
			        	SendClientMessage(i, COLOR_WHITE, string);
			        	OrgInfo[PI[i][pFraction]-1][oMoney] -= gFractionSalary[PI[i][pFraction]-1][PI[i][pRank]-1];
			        	PI[i][pBonus] = 0;
				    }
				    else
					{
				        money += 500;
			        	SendClientMessage(i, COLOR_WHITE, !"     Зарплата: {42B02C}500$");
				        temp_pd_message = true;
					}
				}
			}
			if(PI[i][pSalary])
			{
				money += PI[i][pSalary];
				format(string, sizeof string, "     Зарплата: {42B02C}%d$", PI[i][pSalary]);
				SendClientMessage(i, COLOR_WHITE, string);
				PI[i][pSalary] = 0;
			}
			if(PI[i][pAdmin])
			{
				new
					money_admin;

				if(PI[i][pAdmin] >= 2)
				    money_admin += 5000+(PI[i][pAdmin]*2000);

				else if(PI[i][pAdmin] == 1)
				    money_admin += 5000;

			    money += money_admin;
	        	format(string,sizeof(string),"     Админ. ЗП: {42B02C}%d$", money_admin);
	        	SendClientMessage(i, COLOR_WHITE, string);
			}

			if(PI[i][pTester])
			{
			    money += 2000;
	        	SendClientMessage(i, COLOR_WHITE, "     Зарплата тестера: {42B02C}2000$");
			}
			if(PI[i][pLevel] >= gPensionAge)
			{
			    money += gPension;
			    OrgInfo[9][oMoney] -= gPension;
	        	format(string,sizeof(string),"     Пенсия: {42B02C}%d$", gPension);
	        	SendClientMessage(i, COLOR_WHITE, string);
			}

	        money += salary;

	        //GiveBankMoney(i, money);
	        PI[i][pBank] += money;
	        format(string,sizeof(string),"     Счёт: {42B02C}%d$\n",PI[i][pBank]);
	        SendClientMessage(i, COLOR_WHITE, string);
	        if(PI[i][pWanted] > 0)
	        {
	            PI[i][pWanted]--;
	            SetPlayerWantedLevel(i, PI[i][pWanted]);
	        }
	        else
			{
			    if(PI[i][pZKP] < 100)
					PI[i][pZKP]++;
			}
			//SaveAccount(i);
	        SCM(i, COLOR_WHITE, !"---------------------------------");
	        format(string, sizeof(string), "~y~PAYDAY");
	        PI[i][pPlayed] = 0;
			GameTextForPlayer(i, string, 3000, 1);

	        CheckNextLevel(i);
	   		if(PI[i][pFraction] == 7)
			{
				if(PI[i][pRank] != PI[i][pArmyRank])
				{
					PI[i][pArmyTime]++;
					if(PI[i][pArmyTime] >= 5)
					{
						PI[i][pArmyTime] = 0;
						PI[i][pArmyRank] = PI[i][pRank];
						SendClientMessage(i, COLOR_GREEN, !"Ваше текущее звание в армии было внесено в воинский учет");
					}
				}
				else PI[i][pArmyTime] = 0;
				UpdatePlayerData(i, "ArmyTime", PI[i][pArmyTime]);
				UpdatePlayerData(i, "ArmyRank", PI[i][pArmyRank]);
			}
			if(PI[i][pMesDisease] && PI[i][pAdmin] == 0)
			{
				switch(random(3))
				{
				    case 2:
					{
						new
						    disease = RandomEx(1, 6),
							frmt_disease[128];

				    	if(PI[i][pVaccine][disease] == 0)
						{
						    PI[i][pDisease] = disease;
						    PI[i][pMesDisease] = 0;
						    format(frmt_disease, sizeof frmt_disease, "Вы заболели болезнью {FF0000}%s", gDiseaseName[disease-1]);
						    SendClientMessage(i, COLOR_WHITE, frmt_disease);
						    SendClientMessage(i, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь в ближайшую больницу для лечения");
						    if(PI[i][pDisease] == 2 || PI[i][pDisease] == 3 || PI[i][pDisease] == 6)
						        temp_disease_timer[i] = 180;
						}
					}

			    }
			}
			if(temp_pd_message)
			    SendClientMessage(i, COLOR_GREY, !"В бюджете организации недостаточно средств для выплаты зарплаты");

			new
				query_save_payday[450];

			format(query_save_payday, sizeof query_save_payday, "UPDATE `accounts` SET `Exp` = '%d', `Level` = '%d', `Age` = '%d', `ZKP` = '%d', `Bonus` = '%d', `Salary` = '%d', `Disease` = '%d', `MesDisease` = '%d', `Wanted` = '%d', `PointsOrg` = '%d', `Bank` = '%d' WHERE `ID` = '%d'",
			PI[i][pExp], PI[i][pLevel], PI[i][pAge], PI[i][pZKP], PI[i][pBonus], PI[i][pSalary], PI[i][pDisease], PI[i][pMesDisease], PI[i][pWanted], PI[i][pPointsOrg], PI[i][pBank], PI[i][pID]);
			mysql_tquery(mysql, query_save_payday, "", "");


	    }
		else SendClientMessage(i, COLOR_GREY, !"Вы не авторизированы для получения зарплаты");
	}

	new
	    frmt_balance[128], query_money_upt[80];

	format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[0][oMoney]);
	UpdateDynamic3DTextLabelText(gFractionMoney[0], 0xFFFFFFFF, frmt_balance);

	format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[6][oMoney]);
	UpdateDynamic3DTextLabelText(gFractionMoney[6], 0xFFFFFFFF, frmt_balance);

	format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[7][oMoney]);
	UpdateDynamic3DTextLabelText(gFractionMoney[7], 0xFFFFFFFF, frmt_balance);

	format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[8][oMoney]);
	UpdateDynamic3DTextLabelText(gFractionMoney[8], 0xFFFFFFFF, frmt_balance);

	format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
	UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);

	format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[10][oMoney]);
	UpdateDynamic3DTextLabelText(gFractionMoney[10], 0xFFFFFFFF, frmt_balance);

	format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 1", OrgInfo[0][oMoney]);
	mysql_tquery(mysql, query_money_upt);

	format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 7", OrgInfo[6][oMoney]);
	mysql_tquery(mysql, query_money_upt);
	format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 8", OrgInfo[7][oMoney]);
	mysql_tquery(mysql, query_money_upt);
	format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 9", OrgInfo[8][oMoney]);
	mysql_tquery(mysql, query_money_upt);
	format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 10", OrgInfo[9][oMoney]);
	mysql_tquery(mysql, query_money_upt);
	format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 11", OrgInfo[10][oMoney]);
	mysql_tquery(mysql, query_money_upt);

	for(new tx; tx < 5; tx++)
	{
		new
			money = gangzone_total[tx]*200;

	    gGangStorage[tx][3] += money;

		format(query_money_upt, sizeof query_money_upt, "UPDATE `gangs` SET `money` = '%d' WHERE `id` = %d", gGangStorage[tx][3], tx+1);
		mysql_tquery(mysql, query_money_upt);
	}
	UpdateTextGang();

	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);
	if(hours == 0)
	{
	    for(new hid; hid < OWNABLEHOUSES; hid++)
		{
		    new str[256];

		    if(GetString(HouseInfo[hid][hOwner],"The State") || HouseInfo[hid][hSeal] == 1)
				continue;

			if(HouseInfo[hid][hDays] > 1)
			    HouseInfo[hid][hDays]--;

	     	else
	     	{
	     		new
				 	ownerid = -1,
			 		rent = -1;

		        foreach(new p: Player)
		        {
		            for(new i;i < 3;i ++)
					{
					    if(GetString(HRoomOwner[hid][i], PN(p)))
						{
						    if(IsPlayerLogged[p] && IsPlayerConnected(p))
							{
								PI[p][pSpawn] = 0;
								UpdatePlayerData(p, "Spawn",0);
		                        PI[p][pHouseKey]=0;
		                        UpdatePlayerData(p, "HouseKey", PI[p][pHouseKey]);
		                        rent = p;
							}
						}

					}
					if(GetString(HouseInfo[hid][hOwner], PN(p)) && HouseInfo[hid][hSeal] == 0 && IsPlayerConnected(p))
					{
					    if(IsPlayerLogged[p] && IsPlayerConnected(p))
						{
						    PI[p][pReturnHouse] += HouseInfo[hid][hCost]/100*80;
						    PI[p][pHouseKey] = 0;
						    UpdatePlayerData(p, "HouseKey", PI[p][pHouseKey]);

							if(PI[p][pCars] != 0)
							{
							    new
							        carid = GetCarSlot(PI[p][pCars]),
									vehicleid = CarInfo[carid][cVehID];

								new
									query_car[256];

								format(query_car, sizeof query_car, "DELETE FROM `cars` WHERE `cID` = '%d'", PI[p][pCars]);

								mysql_tquery(mysql, query_car);

								CarInfo[carid][cID] = 0;

								CarInfo[carid][cColor_1] = 0;
								CarInfo[carid][cColor_2] = 0;
								CarInfo[carid][cOwnerID] = 0;
								strdel(CarInfo[carid][cNumber], 0, 12);
								strdel(CarInfo[carid][cDate], 0, 20);
								CarInfo[carid][cFuel] = 0.0;
								CarInfo[carid][cHealth] = 0.0;
								CarInfo[carid][cMilage] = 0.0;
								CarInfo[carid][cSignal] = 0;
								CarInfo[carid][cPaintJob] = 5;
								CarInfo[carid][cSignal] = 0;

								for(new tn; tn < 14; tn++)
									if(CarInfo[carid][cTuning][tn] != 0) RemoveVehicleComponent(CarInfo[carid][cVehID], CarInfo[carid][cTuning][tn]), CarInfo[carid][cTuning][tn] = 0;

								ChangeVehiclePaintjob(CarInfo[carid][cVehID], 5);


                                VehicleInfo[carid][vLock] = 0;

					            if(CarInfo[carid][cVehID] != INVALID_VEHICLE_ID)
									DestroyVehicle(vehicleid), VehicleInfo[vehicleid][vLock] = 0;

								CarInfo[carid][cVehID] = INVALID_VEHICLE_ID;
					            PI[p][pCars] = 0;
					            UpdatePlayerData(p, "Cars", PI[p][pCars]);
					            PI[p][pPTS] = 0;
					            UpdatePlayerData(p, "PTS", PI[p][pPTS]);
					            temp_car_num_get[p] = 0;

					            PI[p][pReturnHouse] += Transport[CarInfo[carid][cModelID]][trPrice]/100*80;
					            printf("Return online [HID = %d], [carid = %d], car=%d, house=%d, Owner(sys): %s, Owner(get) %s", hid, carid, Transport[CarInfo[carid][cModelID]][trPrice]/100*80, HouseInfo[hid][hCost]/100*80, HouseInfo[hid][hOwner], PN(p));
					            CarInfo[carid][cModelID] = 0;

				            }


							if(IsValidDynamic3DTextLabel(HintStoreText[hid]))
							    DestroyDynamic3DTextLabel(HintStoreText[hid]);

							if(IsValidDynamic3DTextLabel(HintSafeText[hid]))
							    DestroyDynamic3DTextLabel(HintSafeText[hid]);

							if(IsValidDynamicObject(HintStoreObject[hid]))
							    DestroyDynamicObject(HintStoreObject[hid]);

							if(IsValidDynamicObject(HintSafeObject[hid]))
							    DestroyDynamicObject(HintSafeObject[hid]);

				            new
				                improve;

							for(new i; i < 4; i++)
							{
							    if(HouseInfo[hid][hImprove][i])
							    {
									HouseInfo[hid][hImprove][i] = 0;
									improve += HouseImprovePrice[i];
								}
							}

							if(improve)
							    PI[p][pReturnHouse] += improve/100*80;

                            UpdatePlayerData(p, "ReturnHouse", PI[p][pReturnHouse]);
				     		for(new i;i<8;i++)
				     		{
				     		    HouseInfo[hid][hGun][i] = 0;
								DestroyDynamicObject(HouseGunObject[hid][i]);
								HouseGunObject[hid][i] = 0;
							}
					        ownerid = p;
					        SendClientMessage(p, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Ваш дом был продан государству за неуплату!");
					        SendClientMessage(p, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Если у Вас был транспорт, он тоже был продан");
					        SendClientMessage(p, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Получить 80 процентов от стоимости списанного имущества вы можете в банке");
					        HouseInfo[hid][hSeal] = 1;
					        SaveHouse(hid);
					        break;

						}
					}
				}
	            if(rent == -1)
				{
				    for(new i;i < 3;i ++)
					{
					    if(!GetString(HRoomOwner[hid][i],"The State"))
						{
						    format(str, sizeof(str), "UPDATE `accounts` SET `HouseKey` = '0' WHERE `NickName` = '%s'", HRoomOwner[hid][i]);
							mysql_tquery(mysql, str);
						}
					}
				}
	            for(new i;i < 3;i ++)
					SetString(HRoomOwner[hid][i], "The State");

				if(ownerid == -1 && HouseInfo[hid][hSeal] == 0)
				{
					new
					    query_carid[60 + MAX_PLAYER_NAME],
						id = strval(MySQLGetPlayerParam(HouseInfo[hid][hOwner], "ID"));

					format(query_carid, sizeof query_carid, "SELECT * FROM `cars` WHERE `cOwnerID` = '%d' ", id);

					new
						Cache:result = mysql_query(mysql, query_carid),
						carid,
						modelid;

					if(cache_get_row_count(mysql))
					{
					    carid = cache_get_row_int(0, 0);
						modelid = cache_get_row_int(0, 2);
						new refund = Transport[modelid][trPrice]/100*80;


					    format(str, sizeof(str), "UPDATE `accounts` SET `Cars` = '0', `ReturnHouse` = `ReturnHouse`+'%d' WHERE `NickName` = '%s'", refund, HouseInfo[hid][hOwner]);
						mysql_tquery(mysql, str);

						printf("Return offline [HID = %d], [carid = %d], car=%d, house=%d, modelid = %d, Owner(sys): %s", hid, carid, refund, HouseInfo[hid][hCost]/100*80, modelid, HouseInfo[hid][hOwner]);

						new
							query_car[256];

						format(query_car, sizeof query_car, "DELETE FROM `cars` WHERE `cID` = '%d'", carid);

						mysql_tquery(mysql, query_car);
					}

					cache_delete(result, mysql);

					new refund = HouseInfo[hid][hCost]/100*80;

				    format(str, sizeof(str), "UPDATE `accounts` SET `HouseKey` = '0', `Cars` = '0', `ReturnHouse` = `ReturnHouse`+'%d' WHERE `NickName` = '%s'", refund, HouseInfo[hid][hOwner]);
					mysql_tquery(mysql, str);

					printf("Return offline [HID = %d], house=%d, Owner(sys): %s", hid, HouseInfo[hid][hCost]/100*80, HouseInfo[hid][hOwner]);

					if(IsValidDynamic3DTextLabel(HintStoreText[hid]))
					    DestroyDynamic3DTextLabel(HintStoreText[hid]);

					if(IsValidDynamic3DTextLabel(HintSafeText[hid]))
					    DestroyDynamic3DTextLabel(HintSafeText[hid]);

					if(IsValidDynamicObject(HintStoreObject[hid]))
					    DestroyDynamicObject(HintStoreObject[hid]);

					if(IsValidDynamicObject(HintSafeObject[hid]))
					    DestroyDynamicObject(HintSafeObject[hid]);

		            new
		                improve;

					for(new i; i < 4; i++)
					{
					    if(HouseInfo[hid][hImprove][i])
					    {
							HouseInfo[hid][hImprove][i] = 0;
							improve += HouseImprovePrice[i];
						}
					}

					if(improve)
					    PI[hid][pReturnHouse] += improve/100*80;

		     		for(new i;i<8;i++)
		     		{
		     		    HouseInfo[hid][hGun][i] = 0;
						DestroyDynamicObject(HouseGunObject[hid][i]);
						HouseGunObject[hid][i] = 0;
					}

					HouseInfo[hid][hSeal] = 1;
				}

				//SetString(HouseInfo[hid][hOwner],"The State");

			    //UpdateHouse(hid);
	     	}
			SaveHouse(hid);
		}

		for(new bizid; bizid < OWNABLEBIZES; bizid++)
		{
		    if(GetString(BizInfo[bizid][bOwner],"The State") || BizInfo[bizid][bSeal] == 1)
				continue;

	        BizInfo[bizid][bNum]=0;
	        BizInfo[bizid][bVisit]=0;
	        BizInfo[bizid][bWin]=0;

		    if(BizInfo[bizid][bDays] > 1)
		        BizInfo[bizid][bDays]--;

		    else
		    {
		        new
					str[256],
		        	ownerid = -1;

		        for(new p = 0, j = GetPlayerPoolSize(); p <= j; p++)
		        {
					if(GetString(BizInfo[bizid][bOwner], PN(p)) && BizInfo[bizid][bSeal] == 0 && IsPlayerConnected(p))
					{
					    if(IsPlayerLogged[p] && IsPlayerConnected(p))
						{
						    PI[p][pBizKey] = 0;
							UpdatePlayerData(p, "BizKey", PI[p][pBizKey]);
							PI[p][pReturnBusiness] += BizInfo[bizid][bCost]/100*80;
							UpdatePlayerData(p, "ReturnBusiness", PI[p][pReturnBusiness]);
					        ownerid = p;

					        SendClientMessage(p, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Ваш бизнес был продан государству за неуплату!");
					        SendClientMessage(p, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Получить 80 процентов от стоимости списанного имущества вы можете в банке");
					        BizInfo[bizid][bSeal] = 1;
					        printf("[SELLBIZ ONLINE] ID: %d, Owner(system): %s, Owner(get): %s", bizid, BizInfo[bizid][bOwner], PN(p));
					        break;

						}
					}
				}

				if(ownerid == -1 && BizInfo[bizid][bSeal] == 0)
				{
				    format(str, sizeof(str), "UPDATE `accounts` SET `BizKey` = 0, `ReturnBusiness`=`ReturnBusiness`+'%d' WHERE `NickName` = '%s'; ",BizInfo[bizid][bCost]/100*80, BizInfo[bizid][bOwner]);
					mysql_tquery(mysql, str);
					BizInfo[bizid][bSeal] = 1;
					printf("[SELLBIZ OFFLINE] ID: %d, Owner: %s", bizid, BizInfo[bizid][bOwner]);
				}
				//SetString(BizInfo[bizid][bOwner], "The State");

		    }
		    SaveBiz(bizid);
		}
		for(new fid; fid < MAX_FILLING; fid++)
		{
		    if(GetString(gFillings[fid][fillingOwner], "The State") || gFillings[fid][fillingSeal] == 1)
				continue;

		    if(gFillings[fid][fillingDay] > 1)
		        gFillings[fid][fillingDay]--;

		    else
		    {
		        new
					str[256],
		        	ownerid = -1;

		        for(new p = 0, j = GetPlayerPoolSize(); p <= j; p++)
		        {
					if(GetString(gFillings[fid][fillingOwner], PN(p)) && gFillings[fid][fillingSeal] == 0 && IsPlayerConnected(p))
					{
					    if(IsPlayerLogged[p] && IsPlayerConnected(p))
						{
						    PI[p][pBizKey] = 0;
						    UpdatePlayerData(p, "BizKey", PI[p][pBizKey]);
							PI[p][pReturnFilling] += gFillings[fid][fillingPrice]/100*80;
							UpdatePlayerData(p, "ReturnFilling", PI[p][pReturnFilling]);
					        ownerid = p;

					        SendClientMessage(p, COLOR_WHITE, !"{FFFF66}[BANK] {FFFFFF}Ваша АЗС была продано государству за неуплату!");
					        SendClientMessage(p, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Получить 80 процентов от стоимости списанного имущества вы можете в банке");
					        gFillings[fid][fillingSeal] = 1;
					        break;

						}
					}
				}

				if(ownerid == -1 && gFillings[fid][fillingSeal] == 0)
				{
				    format(str, sizeof(str), "UPDATE `accounts` SET `BizKey` = 0, `ReturnFilling`=`ReturnFilling`+'%d' WHERE `NickName` = '%s'; ", gFillings[fid][fillingPrice]/100*80, gFillings[fid][fillingOwner]);
					mysql_tquery(mysql, str);
					gFillings[fid][fillingSeal] = 1;
				}

				//SetString(gFillings[fid][fillingOwner], "The State");

		    }
		    SaveFilling(fid);
		}

        for(new p = 0, j = GetPlayerPoolSize(); p <= j; p++)
        {
		    if(IsPlayerLogged[p] && IsPlayerConnected(p))
			{
				if(PI[p][pLevel] < 3)
				    break;

				if(PI[p][pAdmin])
				    break;

	            if(!PI[p][pDisease] && PI[p][pLastEat] < 4 && !PI[p][pMesDisease] && !PI[p][pMesDisease])
				{
				    PI[p][pLastEat]++;
				    UpdatePlayerData(p, "LastEat", PI[p][pLastEat]);
				    if(!PI[p][pVaccine][0] || !PI[p][pVaccine][1] || !PI[p][pVaccine][2] || !PI[p][pVaccine][3] || !PI[p][pVaccine][4] || !PI[p][pVaccine][5])
				    	SendClientMessage(p, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Совсем скоро вы можете заболеть, не забывайте посещать закусочные, бары или рестораны");
				}
				else if(!PI[p][pDisease] && PI[p][pLastEat] == 4 && !PI[p][pMesDisease])
				{
				    PI[p][pLastEat] = 0;
				    UpdatePlayerData(p, "LastEat", PI[p][pLastEat]);

				    PI[p][pMesDisease] = 1;
				    UpdatePlayerData(p, "MesDisease", PI[p][pMesDisease]);

				    if(!PI[p][pVaccine][0] || !PI[p][pVaccine][1] || !PI[p][pVaccine][2] || !PI[p][pVaccine][3] || !PI[p][pVaccine][4] || !PI[p][pVaccine][5])
				    	SendClientMessage(p, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Совсем скоро вы можете заболеть, не забывайте посещать закусочные, бары или рестораны");

				}
			}
		}
		mysql_tquery(mysql, "UPDATE `accounts` SET `LastEat` = `LastEat`+1 WHERE `Disease` = 0 AND `LastEat` < 4 AND `MesDisease` = 0 AND `Level` > 3");
		mysql_tquery(mysql, "UPDATE `accounts` SET `MesDisease` = 1, `LastEat` = 0 WHERE `Disease` = 0 AND `LastEat` = 4 AND `MesDisease` = 0 AND `Level` > 3");


        for(new p = 0, j = GetPlayerPoolSize(); p <= j; p++)
        {
		    if(!IsPlayerLogged[p] || !IsPlayerConnected(p))
		        continue;

			for(new i; i < 6; i++)
			{
			    if(PI[p][pVaccine][i] > 0)
			    {
			        PI[p][pVaccine][i]--;

					new
					    query_vac[120];

					format(query_vac, sizeof query_vac, "UPDATE `accounts` SET `Vaccine[%d]` = '%d', `VaccineCheck` = '1' WHERE `ID` = '%d'", i, PI[p][pVaccine][i], PI[p][pID]);
					mysql_tquery(mysql, query_vac);
				}
			}

		}

		mysql_tquery(mysql, !"UPDATE `accounts` SET `Vaccine[0]` = `Vaccine[0]`-1 WHERE `Vaccine[0]` > 0 AND `VaccineCheck` = 0");
		mysql_tquery(mysql, !"UPDATE `accounts` SET `Vaccine[1]` = `Vaccine[1]`-1 WHERE `Vaccine[1]` > 0 AND `VaccineCheck` = 0");
		mysql_tquery(mysql, !"UPDATE `accounts` SET `Vaccine[2]` = `Vaccine[2]`-1 WHERE `Vaccine[2]` > 0 AND `VaccineCheck` = 0");
		mysql_tquery(mysql, !"UPDATE `accounts` SET `Vaccine[3]` = `Vaccine[3]`-1 WHERE `Vaccine[3]` > 0 AND `VaccineCheck` = 0");
		mysql_tquery(mysql, !"UPDATE `accounts` SET `Vaccine[4]` = `Vaccine[4]`-1 WHERE `Vaccine[4]` > 0 AND `VaccineCheck` = 0");
		mysql_tquery(mysql, !"UPDATE `accounts` SET `Vaccine[5]` = `Vaccine[5]`-1 WHERE `Vaccine[5]` > 0 AND `VaccineCheck` = 0");
        mysql_tquery(mysql, !"UPDATE `accounts` SET `VaccineCheck` = 0");

	    mysql_tquery(mysql, !"UPDATE `ban` SET `time` = `time`-1 WHERE `time` > 0 && `status` = 1");
    	mysql_tquery(mysql, !"UPDATE `accounts` SET `Ban` = `Ban`-1 WHERE `Ban` > 0 && `BanActivate` = 1");

        for(new p = 0, j = GetPlayerPoolSize(); p <= j; p++)
        {
	    	if(PI[p][pWarns] && PI[p][pWarnTime] >= 0)
			{
	            PI[p][pWarnTime] -= 1;
	            UpdatePlayerData(p, "WarnTime", PI[p][pWarnTime]);

	            if(PI[p][pWarns] == 7)
	            {
	                PI[p][pWarns] = 1;
	                UpdatePlayerData(p, "Warns", PI[p][pWarns]);
	            }
	            else if(PI[p][pWarns] == 0)
	            {
	                PI[p][pWarns] = 0;
	                UpdatePlayerData(p, "Warns", PI[p][pWarns]);
	                SendClientMessage(p, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Срок всех Ваших предупреждений истек");
	            }

	            UpdatePlayerData(p, "WarnCheck", 1);
			}
		}
	    mysql_tquery(mysql, !"UPDATE `accounts` SET `WarnTime` = `WarnTime`-1 WHERE `WarnTime` >= 0 AND `WarnCheck` = 0");
	    mysql_tquery(mysql, !"UPDATE `accounts` SET `Warns` = 1 WHERE `WarnTime` = 7 AND `WarnCheck` = 0");
	    mysql_tquery(mysql, !"UPDATE `accounts` SET `Warns` = 0, `WarnMessage` = 1 WHERE `WarnTime` = 0 AND `WarnCheck` = 0");
	    mysql_tquery(mysql, !"UPDATE `accounts` SET `WarnCheck` = 0");


    	mysql_tquery(mysql, "UPDATE `bizstats` SET `day_1` = `day_2`, `day_2` = `day_3`, `day_3` = `day_4`, `day_4` = `day_5`, `day_5` = `day_6`, `day_6` = `day_7`, `day_7` = `day_8`, `day_8` = `day_9`, `day_9` = `day_10`, `day_10` = 0");
	}
	new year, month, day;
	getdate(year, month, day);
	new week = weekday(day, month, year);
	if(hours == 18 && week == 7)
	{
	    new
	        nickname[MAX_PLAYER_NAME];

	    new Cache:result = mysql_query(mysql, "SELECT `NickName`, `AlleyDays` FROM `accounts` WHERE `Alley` = 1 AND `AlleyDays` > 0 ORDER BY `AlleyDays` DESC LIMIT 3");
	    if(cache_get_row_count(mysql) > 0)
	    {
			for(new i; i < 3; i++)
			{
	   			cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 250000;

				else if(i == 1)
					win = 150000;

				else if(i == 2)
					win = 100000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[90];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за нахождение на Аллее Славы", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
    		}
	    }
	    cache_delete(result, mysql);

		new Cache:rLvl = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `Level` >= 15 AND `Card` = 1 ORDER BY `Level` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Долгожитель", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rLvl, mysql);

		new Cache:rCharity = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `Charity` >= 1 AND `Card` = 1 ORDER BY `Charity` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Благотворитель", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}


		cache_delete(rCharity, mysql);

		new Cache:rBestPD = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` = 8 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший сотрудник", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}


		cache_delete(rBestPD, mysql);

		new Cache:rBestArmy = mysql_query(mysql, "SELECT `NickName`FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` = 7 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший сотрудник", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestArmy, mysql);

		new Cache:rBestMedia = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` = 9 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший сотрудник", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestMedia, mysql);

		new Cache:rBestMafia = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` >= 12 AND `Fraction` <= 14 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший Мафиози", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestMafia, mysql);

		new Cache:rBestLoader = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsLoader` >= 1 AND `Card` = 1 ORDER BY `PointsLoader` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Грузчик", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestLoader, mysql);

		new Cache:rBusiness = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsBusiness` >= 1 AND `Card` = 1 ORDER BY `PointsBusiness` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Бизнесмен", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}
		cache_delete(rBusiness, mysql);

		new Cache:rMoney = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsMoney` >= 1 AND `Card` = 1 ORDER BY `PointsMoney` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Самый Богатый", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rMoney, mysql);


		new Cache:rBestDonate = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `TotalDon` >= 1 AND `Card` = 1 ORDER BY `TotalDon` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Меценат штата", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestDonate, mysql);


		new Cache:rBestMeria = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` = 10 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший сотрудник", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestMeria, mysql);

		new Cache:rBestFBI = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` = 11 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший сотрудник", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestFBI, mysql);

		new Cache:rBestHeal = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` = 1 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший сотрудник", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestHeal, mysql);

		new Cache:rBestGang = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsOrg` >= 1 AND `Card` = 1 AND `Fraction` >= 2 AND `Fraction` <= 6 ORDER BY `PointsOrg` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Лучший Бандит", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

        cache_delete(rBestGang, mysql);

		new Cache:rBestRoad = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsRoad` >= 1 AND `Card` = 1 ORDER BY `PointsRoad` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Строитель дорог", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}

		cache_delete(rBestRoad, mysql);

		new Cache:rBestFactory = mysql_query(mysql, "SELECT `NickName` FROM `accounts` WHERE `PointsFactory` >= 1 AND `Card` = 1 ORDER BY `PointsFactory` DESC LIMIT 3");

		if(cache_get_row_count(mysql) > 0)
		{
			for(new i; i < 3; i++)
			{
				cache_get_row(i, 0, nickname, mysql, 24);

	   			if(GetString(nickname, "NULL"))
	   			    continue;

				new	win;

				if(i == 0)
					win = 150000;

				else if(i == 1)
					win = 100000;

				else if(i == 2)
					win = 50000;

	    		if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
	    		{
	    		    new
	    		        frmt_alley_message[130];

					format(frmt_alley_message, sizeof frmt_alley_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за ТОП 3 в номинации Работник завода", win);
	                SendClientMessage(GetPlayerID(nickname), COLOR_WHITE, frmt_alley_message);
	                GiveMoney(GetPlayerID(nickname), win, "аллея славы");
	    		}
				else
				{
				    new
						query_alley_updt[150];

					format(query_alley_updt, sizeof query_alley_updt, "UPDATE `accounts` SET `Money` = `Money`+%d WHERE `NickName` = '%s'", win, nickname);
				    mysql_tquery(mysql, query_alley_updt);
				}
			}
		}
		cache_delete(rBestFactory, mysql);

	}
    payday_admin = false;
	return true;
}
@__GrandTimer();
@__GrandTimer()
{
    new tickcount1 = GetTickCount();
    new hours, minutes;
    gettime(hours,minutes);

    if(gCurMinutes != minutes)
    {
        gCurMinutes = minutes;
        if(minutes == 0)
        {
            SetWorldTime(hours);
            payday_admin = false;
            PayDay();
            if(0 == gPaintBall[pbStatus] && (hours == 7 || hours == 9 || hours == 11 || hours == 13 || hours == 15 || hours == 17 || hours == 19 || hours == 21 || hours == 23 || hours == 1 || hours == 3))
                SetTimer("@__paintball",15000, 0);


            gHouseFree = 0;
            gHouseSeal = 0;
            gBusinessFree = 0;
            gBusinessSeal = 0;
            gFillingFree = 0;
            gFillingSeal = 0;

            for(new h; h < OWNABLEHOUSES; h++)
                HouseEstate(h);

            for(new b; b < OWNABLEBIZES; b++)
                BusinessEstate(b);

            for(new f; f < MAX_FILLING; f++)
                FillingEstate(f);
        }
        if(hours == 5 && minutes == 0)
        {
            SendClientMessageToAll(COLOR_RED, !"Внимание, через 3 минуты произойдет автоматический рестарт сервера!");
            SaveAccAll();
        }
        if(minutes == 2 && hours == 5)
        {
            SendClientMessageToAll(COLOR_RED, !"Авторестарт сервера... (#8)");
            gServerRestart = true;
            foreach(new i : Player)
                J_Kick(i);
        }
        if(minutes == 3 && hours == 5)
        {
            SendClientMessageToAll(COLOR_RED, !"Авторестарт сервера... (#8)");
            foreach(new i : Player)
            {
                if(IsPlayerConnected(i) && IsPlayerLogged[i])
                {
                    if(PI[i][pWedding])
                        PI[i][pWedding] = 0, UpdatePlayerData(i, "Wedding", PI[i][pWedding]);

                    if(PI[i][pSellZones])
                        PI[i][pSellZones] = 0, UpdatePlayerData(i, "SellZones", PI[i][pSellZones]);

                    J_Kick(i);
                }
            }
            mysql_tquery(mysql, "UPDATE `accounts` SET `Wedding` = '0' WHERE `Wedding` = '1'");
            mysql_tquery(mysql, "UPDATE `accounts` SET `AdminTime` = '0' WHERE `AdminTime` > 0");
            mysql_tquery(mysql, "UPDATE `accounts` SET `SellZones` = '0' WHERE `SellZones` > 0");
            mysql_tquery(mysql, "UPDATE `accounts` SET `PointsOrg` = `PointsOrg`+'5' WHERE `Fraction` > 0 AND `Card` = 1");
            for(new hi; hi < OWNABLEHOUSES; hi++)
            {
                if(HouseInfo[hi][hSellTimer])
                {
                    new
                        query_house[136 + 5];

                    format(query_house, sizeof query_house, "UPDATE `houses` SET `Owner` = 'The State', `Days` = '0', `Improve` = '0|0|0|0' WHERE `ID` = '%d'", HouseInfo[hi][hID]);
                    mysql_tquery(mysql, query_house);

                    format(query_house, sizeof query_house, "UPDATE `accounts` SET `HouseKey` = '0' WHERE `NickName` = '%s'", HouseInfo[hi][hOwner]);
                    mysql_tquery(mysql, query_house);

                    SetString(HouseInfo[hi][hOwner], "The State");

                    for(new i; i < 4; i++) HouseInfo[hi][hImprove][i] = 0;

                    HouseInfo[hi][hSeal] = 0;

                    if(IsValidDynamic3DTextLabel(HintStoreText[hi])) DestroyDynamic3DTextLabel(HintStoreText[hi]);
                    if(IsValidDynamic3DTextLabel(HintSafeText[hi])) DestroyDynamic3DTextLabel(HintSafeText[hi]);
                    if(IsValidDynamicObject(HintStoreObject[hi])) DestroyDynamicObject(HintStoreObject[hi]);
                    if(IsValidDynamicObject(HintSafeObject[hi])) DestroyDynamicObject(HintSafeObject[hi]);
                    SetString(HouseInfo[hi][hOwner], "The State");


                    HouseInfo[hi][hSafeCode] = 0;
                    HouseInfo[hi][hSkin][1] = 0;
                    HouseInfo[hi][hSkin][2] = 0;
                    HouseInfo[hi][hSkin][3] = 0;
                    HouseInfo[hi][hSkin][0] = 0;
                    HouseInfo[hi][hMoney] = 0;

                    for(new i;i<8;i++)
                    {
                        HouseInfo[hi][hGun][i] = 0;
                        DestroyDynamicObject(HouseGunObject[hi][i]);
                        HouseGunObject[hi][i] = 0;
                    }

                    if(IsValidDynamicObject(HintDressObject[hi][0])) DestroyDynamicObject(HintDressObject[hi][0]);
                    if(IsValidDynamicObject(HintDressObject[hi][1])) DestroyDynamicObject(HintDressObject[hi][1]);
                    if(IsValidDynamicObject(HintDressObject[hi][2])) DestroyDynamicObject(HintDressObject[hi][2]);

                    SaveHouse(hi);
                    KillTimer(HouseInfo[hi][hSellTimer]);
                }
            }
            for(new bz; bz < MAX_BIZ; bz++)
            {
                if(BizInfo[bz][bSellTimer])
                {
                    new
                        query_sell_business[130 + 6];

                    format(query_sell_business, sizeof query_sell_business, "UPDATE `accounts` SET `BizKey` = '0' WHERE `NickName` = '%s'", BizInfo[bz][bOwner]);
                    mysql_tquery(mysql, query_sell_business);

                    SetString(BizInfo[bz][bOwner], "The State");
                    BizInfo[bz][bLock] = 1;

                    format(query_sell_business,sizeof query_sell_business,"UPDATE `business` SET `Owner` = 'The State', `Lock` = '1', `Seal` = '0' WHERE `ID` = '%d'", bz+1);
                    mysql_tquery(mysql, query_sell_business);

                    BizInfo[bz][bSeal] = 0;

                    UpdateBiz(bz, 1);
                    KillTimer(BizInfo[bz][bSellTimer]);
                }
            }
            for(new f; f < MAX_FILLING; f++)
            {
                if(gFillings[f][fillingSellTimer])
                {
                    new
                        query_buyfilling[155 + 5 + MAX_PLAYER_NAME + 16];

                    format(query_buyfilling, sizeof query_buyfilling, "UPDATE `fillings` SET `OwnerID` = '0', `Owner` = 'The State', `Working` = '1', `Bank` = '0', `Seal` = '0' WHERE `ID` = '%d'", f+1);
                    mysql_tquery(mysql, query_buyfilling);

                    format(query_buyfilling, sizeof query_buyfilling, "UPDATE `accounts` SET `BizKey` = '0' WHERE `NickName` = '%s'", gFillings[f][fillingOwner]);
                    mysql_tquery(mysql, query_buyfilling);

                    SetString(gFillings[f][fillingOwner], "The State");

                    gFillings[f][fillingOwnerID] = 0;
                    gFillings[f][fillingWorking] = true;
                    gFillings[f][fillingBank] = 0;
                    gFillings[f][fillingDay] = 3;

                    gFillings[f][fillingSeal] = 0;
                    SaveFilling(f);
                    UpdateFillingText(f);


                    KillTimer(gFillings[f][fillingSellTimer]);
                }
            }
            mysql_tquery(mysql, "UPDATE `accounts` SET `v_Days` = `v_Days`-1 WHERE `v_Days` > 0");

            mysql_tquery(mysql, "UPDATE `accounts` SET `DaysExp` = `DaysExp`-1 WHERE `DaysExp` > 0");
            mysql_tquery(mysql, "UPDATE `accounts` SET `DaysSalary` = `DaysSalary`-1 WHERE `DaysSalary` > 0");

            mysql_tquery(mysql, "UPDATE `accounts` SET `Fraction` = `v_Fraction`, `Subfraction` = `v_Subfraction`, `Rank` = `v_Rank`, `FWarns` = `v_FWarns`, `v_Days` = '0', `v_Status` = 1, `FractionSkin` = `v_FractionSkin`, `v_FractionSkin` = 0, `v_Fraction` = 0, `v_Subfraction` = 0, `v_Rank` = 0, `v_FWarns` = 0 WHERE `v_Days` = 0 AND `v_Fraction` > 0 AND `Fraction` = 0 AND `Warns` = 0");
            GameModeExit();
        }
    }
    for(new i2;i2<4;i2++)
    {
        new text[256];
        strcat(text,"{74FFA0}  Очередь на загрузку:{FFFFFF}");
        for(new i;i<10;i++)
        {
            if(gTruckLoadTurn[i2][i] != INVALID_PLAYER_ID && !IsPlayerConnected(gTruckLoadTurn[i2][i]))
                gTruckLoadTurn[i2][i] = INVALID_PLAYER_ID;

            if(i != 9 && gTruckLoadTurn[i2][i] == INVALID_PLAYER_ID && gTruckLoadTurn[i2][i+1] != INVALID_PLAYER_ID)
            {
                gTruckLoadTurn[i2][i] = gTruckLoadTurn[i2][i+1];
                gTruckLoadTurn[i2][i+1] = INVALID_PLAYER_ID;
            }
            if(gTruckLoadTurn[i2][i] != INVALID_PLAYER_ID)
                format(text,sizeof(text),"%s\n%d. %s",text,i+1,PN(gTruckLoadTurn[i2][i]));
            else
                format(text,sizeof(text),"%s\n%d. Свободно",text,i+1);
        }
        UpdateDynamic3DTextLabelText(gTruckLoadTurnText[i2], 0xFFFFFFFF, text);
        if(gTruckLoadTurn[i2][0] != INVALID_PLAYER_ID)
        {
            new playerid = gTruckLoadTurn[i2][0];
            new amount = GetPVarInt(playerid,"truckamount");
            if(IsPlayerConnected(playerid))
            {
                if(pTemp[playerid][pTruckWagonID] != INVALID_VEHICLE_ID)
                {
                    if(amount - pTemp[playerid][pTruckWeight] == 100)
                    {
                        pTemp[playerid][pTruckWeight] += 100;
                        pTemp[playerid][pTruckWagonTime] = 60;
                        SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Ваша фура загружена. У Вас есть 1 минута чтобы прицепить её");
                    }
                    else if(pTemp[playerid][pTruckWeight] < amount)
                    {
                        pTemp[playerid][pTruckWeight] += 100;
                    }
                    else if(pTemp[playerid][pTruckWagonTime] && GetPVarInt(playerid,"waitgruz") == 2)
                        pTemp[playerid][pTruckWagonTime]--;

                    if(pTemp[playerid][pTruckWagonTime] < 1 && GetPVarInt(playerid,"waitgruz") == 2)
                    {
                        if(IsValidDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]))
                        {
                            DestroyDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]);
                            pTemp[playerid][pTruckWagonText] = Text3D:INVALID_3DTEXT_ID;
                        }
                        DestroyVehicle(pTemp[playerid][pTruckWagonID]);
                        pTemp[playerid][pTruckWagonID] = INVALID_VEHICLE_ID;
                        pTemp[playerid][pTruckWeight] = 0;
                        pTemp[playerid][pTruckWagonTime] = 0;
                        gTruckLoadTurn[i2][0] = INVALID_PLAYER_ID;
                        DeletePVar(playerid,"mesto");
                        SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы не успели. Заказ аннулирован");
                    }
                    new level = GetPlayerTruckLevel(playerid);
                    new maxcount = (level == 1) ? (TRUCK_LOAD_1) : (level == 2) ? (TRUCK_LOAD_2) : (TRUCK_LOAD_3);
                    if(pTemp[playerid][pTruckWagonText] != Text3D:INVALID_3DTEXT_ID)
                    {
                        new mes[128];
                        switch(i2)
                        {
                            case 0: format(mes,sizeof(mes),"%s\n{FFCC00}Угля в фуре: {FFFFFF}%d/%d",PN(gTruckLoadTurn[i2][0]),pTemp[playerid][pTruckWeight],maxcount);
                            case 1: format(mes,sizeof(mes),"%s\n{FFCC00}Корма: {FFFFFF}%d/%d",PN(gTruckLoadTurn[i2][0]),pTemp[playerid][pTruckWeight],maxcount);
                            case 3: format(mes,sizeof(mes),"%s\n{FFCC00}Щебня: {FFFFFF}%d/%d",PN(gTruckLoadTurn[i2][0]),pTemp[playerid][pTruckWeight],maxcount);
                        }
                        UpdateDynamic3DTextLabelText(pTemp[playerid][pTruckWagonText],0xFFFFFFFF,mes);
                    }
                }
                else
                {
                    SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Подошла очередь загрузки вашей фуры");
                    SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}После загрузки у Вас будет всего минута, чтобы прицепить её.");
                    SetPVarInt(playerid,"waitgruz",2);
                    pTemp[playerid][pTruckWagonTime] = 60;
                    switch(i2)
                    {
                        case 0: pTemp[playerid][pTruckWagonID] = CreateVehicle(450,2179.5881,-2315.8381,14.1330,44.6791,1,1,-1);
                        case 1: pTemp[playerid][pTruckWagonID] = CreateVehicle(450,-1761.3583,-170.3472,4.1351,266.8418,1,1,-1);
                        case 3: pTemp[playerid][pTruckWagonID] = CreateVehicle(450,2859.8894,933.5375,11.3306,90.6410,1,1,-1);
                    }
                    if(pTemp[playerid][pTruckWagonText] != Text3D:INVALID_3DTEXT_ID)
                    {
                        DestroyDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]);
                        pTemp[playerid][pTruckWagonText] = Text3D:INVALID_3DTEXT_ID;
                    }
                    pTemp[playerid][pTruckWagonText] = CreateDynamic3DTextLabel("_",0xFFFFFFFF,0.0,0.0,2.0,20.0,INVALID_PLAYER_ID,pTemp[playerid][pTruckWagonID]);
                }
                if(!IsPlayerInDynamicArea(playerid,arOneCoal) && !IsPlayerInDynamicArea(playerid,arTwoCoal) && !IsPlayerInDynamicArea(playerid,arThreeCoal) && (gTruckLoadTurn[0][0] == playerid || gTruckLoadTurn[1][0] == playerid || gTruckLoadTurn[3][0] == playerid))
                {
                    new vehicleid = GetPlayerVehicleID(playerid);
                    if(IsTrailerAttachedToVehicle(vehicleid))
                    {
                        new trailerid = GetVehicleTrailer(vehicleid);
                        if(pTemp[playerid][pTruckWagonID] == trailerid)
                        {
                            new loadid = GetPVarInt(playerid,"loadid");
                            pTemp[playerid][pTruckLoadID] = loadid;
                            SetPVarInt(playerid,"truckonroad",1);
                            gTruckLoadTurn[loadid][0] = INVALID_PLAYER_ID;
                            SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Теперь можете ехать к месту разгрузки. Метка отмечена на радаре.");
                            SetPlayerCheckpointEx(playerid, 65.9495,-244.0107,2.1663, 10.0);
                            DeletePVar(playerid,"mesto");
                        }
                        else
                        {
                            SendClientMessage(playerid,COLOR_GREY,"Данную фуру уже арендуют");
                            RemovePlayerFromVehicle(playerid);
                        }
                    }
                }
            }
        }
    }
    if(IsCapture) GzCheck();
    if(IsBizWar) BizWarCheck();

    if(FrakCD > 0 && IsCapture == 0) FrakCD--;
    for(new i; i < MAX_GANGZONE; i++)
    {
        if(GZSafeTime[i] > 0)
        {
            GZSafeTime[i]--;

            TextDrawSetString(tdCapture[2], Convert(GZSafeTime[i]));

            if(GZSafeTime[i] == 60 || GZSafeTime[i] == 600)
            {
                new frmt_end_time[51 + 6];
                format(frmt_end_time, sizeof frmt_end_time, "До окончания захвата территории осталось %d секунд.", GZSafeTime[i]);
                FractionChat(GZMZ[i][gNapad], 0xFF2400FF, frmt_end_time);
                FractionChat(GZMZ[i][gGang], 0xFF2400FF, frmt_end_time);
            }
            if(GZSafeTime[i] == 0 && ZoneOnBattle[i] == 1)
            {
                FractionChat(GZMZ[i][gNapad], 0xFF2400FF, "Захват территории был окончен!");
                FractionChat(GZMZ[i][gGang], 0xFF2400FF, "Захват территории был окончен!");
            }
        }
    }
    if(gBizWarTimer > 0 && IsBizWar == 1)
    {
        gBizWarTimer--;
        TextDrawSetString(BizWarTimer, Convert(gBizWarTimer));
    }
    if(gBizWarTimer == 0 && IsBizWar == 1)
    {
        foreach(new i : Player)
            TextDrawHideForPlayer(i, BizWarTimer);

        FractionChat(gNapadMafia, 0xFF0000FF, "Внимание, стрела началась!");
        FractionChat(gMafiaID, 0xFF0000FF, "Внимание, стрела началась!");

        IsBizWar = 2;
        gBizWarTimer = 300;

        new
            str_mafia1[64],
            str_mafia2[64];

        foreach(new i : Player)
        {
            if(!IsAMafia(i) || pTemp[i][pPaintTeam]) continue;

            for(new td; td < 8; td++)
                TextDrawShowForPlayer(i, tdBizWar[td]);

            format(str_mafia1, sizeof str_mafia1, "%s", GetMafiaNameTD(gNapadMafia));
            TextDrawSetString(tdBizWar[4], str_mafia1);

            format(str_mafia2, sizeof str_mafia2, "%s", GetMafiaNameTD(gMafiaID));
            TextDrawSetString(tdBizWar[6], str_mafia2);

            TextDrawSetString(tdBizWar[5], "0");
            TextDrawSetString(tdBizWar[7], "0");
        }
    }
    else if(IsBizWar == 2 && gBizWarTimer > 0)
    {
        gBizWarTimer--;
        TextDrawSetString(tdBizWar[2], Convert(gBizWarTimer));
    }

    //UpdateTextGang();
    //UpdateTextMafia();

    if(gAdvertTime > 0)
        gAdvertTime--;

    if(gPaintBall[pbTimer] > 0)
        gPaintBall[pbTimer]--;

    for(new i; i < MAX_ADVERTS; i++)
    {
        if(gAdvert[i][adTime])
            gAdvert[i][adTime]--;

        if(gAdvert[i][adChecked] && !gAdvert[i][adTime])
        {
            new
                frmt_advert_message[168];

            format(frmt_advert_message, sizeof frmt_advert_message, "%s Отправитель: %s (тел. %d)", gAdvert[i][adText], gAdvert[i][adSender], gAdvert[i][adPhone]);
            SendClientMessageToAll(0x00FF00FF, frmt_advert_message);
            format(frmt_advert_message, sizeof frmt_advert_message, "  Объявление проверил: %s %s[%d]", gAdvert[i][adRang], gAdvert[i][adChecker], gAdvert[i][adCheckerID]-1);
            SendClientMessageToAll(COLOR_GREEN, frmt_advert_message);
            strdel(gAdvert[i][adSender],0,24);
            gAdvert[i][adPhone] = 0;
            gAdvert[i][adCheckerID] = 0;
            strdel(gAdvert[i][adText],0,100);
            strdel(gAdvert[i][adChecker],0,24);
            gAdvert[i][adBusy] = false;
            gAdvert[i][adChecked] = false;
            gAdvert[i][adChecking] = false;
            gAdvert[i][adTime] = 0;

            if(gAdvertCount > 0)
                gAdvertCount--;
        }
    }
    if(gPaintBall[pbStatus] == 1 && gPaintBall[pbTimer] == 300)
    {
        SendClientMessageToAll(0xED485FFF, !"Уважаемые игроки, через {FFFFFF}5{ED485F} минут пройдет мероприятие {FFFFFF}PaintBall");
        SendClientMessageToAll(0xED485FFF, !"Для участия отправляйтесь в {FFFFFF}Центр развлечений");
        SendClientMessageToAll(0xED485FFF, !"Максимальное число участников: {FFFFFF}30{ED485F} игроков");
    }
    else if(gPaintBall[pbStatus] == 1 && gPaintBall[pbTimer] == 120)
    {
        SendClientMessageToAll(0xED485FFF, !"Уважаемые игроки, через {FFFFFF}2{ED485F} минуты пройдет мероприятие {FFFFFF}PaintBall");
        SendClientMessageToAll(0xED485FFF, !"Для участия отправляйтесь в {FFFFFF}Центр развлечений");
        SendClientMessageToAll(0xED485FFF, !"Максимальное число участников: {FFFFFF}30{ED485F} игроков");
    }
    else if(gPaintBall[pbStatus] == 1 && gPaintBall[pbTimer] == 0)
    {
        if(gPaintBall[pbPlayers] < 2)
        {
            gPaintBall[pbStatus] = 0;
            gPaintBall[pbPlayers] = 0;
            SendClientMessageToAll(0xED485FFF, !"PaintBall прерван из-за недостаточного количества участников!");
        }
        else
        {
            gPaintBall[pbWin] = 0;
            SendClientMessageToAll(0xED485FFF, !"Началась игра в PaintBall!");
            gPaintBall[pbStatus] = 2;
            gPaintBall[pbTimer] = 600;

        }
    }
    else if(gPaintBall[pbStatus] == 2 && gPaintBall[pbTimer] != 0)
    {
        if(gPaintBall[pbRedTeam] == 0)
        {
            SendClientMessageToAll(0xED485FFF, !"Игра в PaintBall завершена! Победила команда синих");
            gPaintBall[pbTimer] = 0;
            gPaintBall[pbStatus] = 0;
            gPaintBall[pbPlayers] = 0;
            gPaintBall[pbWin] = 2;
            gPaintBall[pbBlueTeam] = 0;
            gPaintBall[pbRedTeam] = 0;
        }
        else if(gPaintBall[pbBlueTeam] == 0)
        {
            SendClientMessageToAll(0xED485FFF, !"Игра в PaintBall завершена! Победила команда красных");
            gPaintBall[pbTimer] = 0;
            gPaintBall[pbStatus] = 0;
            gPaintBall[pbPlayers] = 0;
            gPaintBall[pbWin] = 1;
            gPaintBall[pbBlueTeam] = 0;
            gPaintBall[pbRedTeam] = 0;

        }
        TextDrawSetString(tdPaintBall[2], Convert(gPaintBall[pbTimer]));
    }
    else if(gPaintBall[pbStatus] == 2 && gPaintBall[pbTimer] == 0 && (gPaintBall[pbRedTeam] != 0 || gPaintBall[pbBlueTeam] != 0))
    {
        if(gPaintBall[pbRedTeam] > gPaintBall[pbBlueTeam])
        {
            SendClientMessageToAll(0xED485FFF, !"Игра в PaintBall завершена! Победила команда красных");
            print("PaintBall end (3)");
            gPaintBall[pbTimer] = 0;
            gPaintBall[pbStatus] = 0;
            gPaintBall[pbPlayers] = 0;
            gPaintBall[pbWin] = 1;
            gPaintBall[pbBlueTeam] = 0;
            gPaintBall[pbRedTeam] = 0;
        }
        else if(gPaintBall[pbBlueTeam] > gPaintBall[pbRedTeam])
        {
            SendClientMessageToAll(0xED485FFF, !"Игра в PaintBall завершена! Победила команда синих");
            print("PaintBall end (4)");
            gPaintBall[pbTimer] = 0;
            gPaintBall[pbStatus] = 0;
            gPaintBall[pbPlayers] = 0;
            gPaintBall[pbWin] = 2;
            gPaintBall[pbBlueTeam] = 0;
            gPaintBall[pbRedTeam] = 0;
        }
        else if(gPaintBall[pbBlueTeam] == gPaintBall[pbRedTeam])
        {
            SendClientMessageToAll(0xED485FFF, !"Игра в PaintBall завершена ничьей!");
            print("PaintBall end (5)");
            gPaintBall[pbTimer] = 0;
            gPaintBall[pbStatus] = 0;
            gPaintBall[pbPlayers] = 0;
            gPaintBall[pbWin] = 3;
            gPaintBall[pbBlueTeam] = 0;
            gPaintBall[pbRedTeam] = 0;
        }
    }
    new weapons[13][2];

    for(new playerid = 0; playerid < total_players; playerid++)
    //foreach (new playerid : Player)
    {
        if(!IsPlayerNPC(playerid))
        {
            if(IsPlayerConnected(playerid) && IsPlayerLogged[playerid])
            {
            // == Конец paint ==
				if((pTemp[playerid][pPaintTeam] == 1 || pTemp[playerid][pPaintTeam] == 2) && !gPaintBall[pbStatus])
			 	{
			  		if(gPaintBall[pbWin] == pTemp[playerid][pPaintTeam])
			    	{
			     		SetPlayerPos(playerid, 827.5557,7.4137,1004.1870);
			       		SetPlayerFacingAngle(playerid, 271.5084);
			         	SetPlayerInterior(playerid, 3);
			          	SetPlayerVirtualWorld(playerid, 68);
			           	ResetPlayerWeapons(playerid);
			            J_SetPlayerHealth(playerid, 100);
			            BizEntered[playerid] = 68;
			            PI[playerid][pDead] = false;
			            if(PI[playerid][pMaskON])
			            {
			            	if(PI[playerid][pFraction]) SetPlayerColor(playerid, gFractionColor[PI[playerid][pFraction] - 1]);
			             	else SetPlayerColor(playerid, 0xFFFFFF11);

							RemovePlayerAttachedObject(playerid, 8);
			    			PI[playerid][pMaskON] = 0;
			       		}

						SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);

						for(new td; td < 8; td++) TextDrawHideForPlayer(playerid, tdPaintBall[td]);

						pTemp[playerid][pPaintTeam] = 0;
			   			if(gPaintBall[pbBlueTeam] <= 15 && gPaintBall[pbBlueTeam] > 12)
			      		{
			        		SendClientMessage(playerid, COLOR_YELLOW, !"Вы выиграли 1500$");
			          		GiveMoney(playerid, 1500, "выигрыш pb");
			            }
			            else if(gPaintBall[pbBlueTeam] <= 12 && gPaintBall[pbBlueTeam] > 8)
			            {
			            	SendClientMessage(playerid, COLOR_YELLOW, !"Вы выиграли 3000$");
			             	GiveMoney(playerid, 3000, "выигрыш pb");
			            }
			            else if(gPaintBall[pbBlueTeam] <= 8 && gPaintBall[pbBlueTeam] > 3)
			            {
			            	SendClientMessage(playerid, COLOR_YELLOW, !"Вы выиграли 4500$");
			             	GiveMoney(playerid, 4500, "выигрыш pb");
			           	}
			            else if(gPaintBall[pbBlueTeam] <= 3)
			            {
			            	SendClientMessage(playerid, COLOR_YELLOW, !"Вы выиграли 9000$");
			             	GiveMoney(playerid, 9000, "выигрыш pb");
			            }
			            return 1;
					}
			  		else if(gPaintBall[pbWin] == 3)
			    	{
			     		SetPlayerPos(playerid, 827.5557,7.4137,1004.1870);
			       		SetPlayerFacingAngle(playerid, 271.5084);
						SetPlayerInterior(playerid, 3);
						SetPlayerVirtualWorld(playerid, 68);
						ResetPlayerWeapons(playerid);
						J_SetPlayerHealth(playerid, 100);
						BizEntered[playerid] = 68;
						PI[playerid][pDead] = false;

			   			if(PI[playerid][pMaskON])
			      		{
			        		if(PI[playerid][pFraction]) SetPlayerColor(playerid, gFractionColor[PI[playerid][pFraction] - 1]);
			          		else SetPlayerColor(playerid, 0xFFFFFF11);

			            	RemovePlayerAttachedObject(playerid, 8);
			             	PI[playerid][pMaskON] = 0;
						}

						SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);
			   			for(new td; td < 8; td++) TextDrawHideForPlayer(playerid, tdPaintBall[td]);
			      		pTemp[playerid][pPaintTeam] = 0;
			      		return 1;
			        }
				}
				// =========================================================
                if(IsPlayerSpawned[playerid])
                {
                    if(!AntiCheatOFF[playerid][MONEY_HACK])
                    {
                        if(PI[playerid][pMoney] > GetPlayerMoney(playerid)) PI[playerid][pMoney] = GetPlayerMoney(playerid);
                        else if(PI[playerid][pMoney] < GetPlayerMoney(playerid)) SetPlayerMoney(playerid, GetMoney(playerid));
                    }
                    else AntiCheatOFF[playerid][MONEY_HACK] --;
                }
                if(Music == true)
                {
                    if(IsPlayerInRangeOfPoint(playerid, MusicU[4], MusicU[1], MusicU[2], MusicU[3]))
                    {
                        if(!GetPVarInt(playerid,"Music"))
                        {
                            SetPVarInt(playerid,"Music",1);
                            PlayAudioStreamForPlayer(playerid, UMusic, MusicU[1], MusicU[2], MusicU[3], MusicU[4], true);
                            SendClientMessage(playerid,COLOR_WHITE,!"{FFC800}[Подсказка]{ffffff} Вы попали в зону проигрывания музыки {FFC800}(Включите громкость в настройках)");
                         }
                    }
                    else
                    {
                        if(GetPVarInt(playerid,"Music"))
                        {
                            DeletePVar(playerid,"Music");
                            StopAudioStreamForPlayer(playerid);
                            SendClientMessage(playerid,COLOR_WHITE,!"{FFC800}[Подсказка]{ffffff} Вы покинули зону проигрывания музыки");
                        }
                    }
                }

                // Anti-cheat ======================================================
                if(GetPlayerState(playerid) == 2)
                {
                    if(SpeedVehicle(playerid) > MAX_VEHICLE_SPEED && PI[playerid][pAdmin] == 0 && GetVehicleModel(GetPlayerVehicleID(playerid)) != 519 && GetVehicleModel(GetPlayerVehicleID(playerid)) != 520)
                    {
                        timeforcd[playerid]++;
                        if(pTemp[playerid][pCheatTime] > 1) KickEx(playerid, 7);
                        if(timeforcd[playerid] >= 3)
                        {
                            new lstring[144];
                            format(lstring, sizeof lstring, "[AC] » %s[%d] возможно использует SpeedHack.", PN(playerid), playerid);
                            SendAdminsMessage(0xFF00FFFF, lstring);
                            timeforcd[playerid] = 0;
                            pTemp[playerid][pCheatTime] +=16;
                        }
                    }
                }
                // метла
                if(GetPlayerAnimationIndex(playerid) == 1058 && GetPlayerState(playerid) != 9 && !IsPlayerInAnyVehicle(playerid) && GetPlayerSpeed(playerid) > 8) KickEx(playerid, 39);
                //
                new Float:xw, Float:yw, Float:zw;
                GetPlayerVelocity(playerid, xw, yw, zw);
                if(IsPlayerLogged[playerid] == false && (xw > 0 || yw > 0 || zw > 0))
                {
                    KickEx(playerid, 32);
                }
                if(xw > 2.0 || yw > 2.0)
                {
                    timeforcd[playerid]++;
                    if(timeforcd[playerid] >= 3)
                    {
                        timeforcd[playerid] = 0;
                        KickEx(playerid, 33);
                    }
                    new lstring[144];
                    format(lstring, sizeof(lstring), "[AC] » Игрок %s[%d] возможно использует Rvanku.", PN(playerid), playerid);
                    SendAdminsMessage(0xFF00FFFF, lstring);
                }
                // =================================================================
                if(AntiCheatOFF[playerid][VEH_ROOT_HACK] > 0) AntiCheatOFF[playerid][VEH_ROOT_HACK] --;

                if(NoEnterPickup[playerid] > 0)
                {
                    NoEnterPickup[playerid] --;
                    if(NoEnterPickup[playerid]==0)
                    {
                        f_TogglePlayerControllable(playerid,true);
                        ReloadAllAnims(playerid);
                    }
                }
                if(IsPlayerInRangeOfPoint(playerid, 50.0, 693.6690, 1527.1469, 1306.1029) && PI[playerid][pHealth] < 100.0)
                {
                    PI[playerid][pHealTime] ++;

                    if(PI[playerid][pHealTime] >= (8+random(3)))
                    {
                        new newhp = random(2);

                        if(newhp == 0) PI[playerid][pHealth] += 2.0, GameTextForPlayer(playerid, "~b~+2 HP", 400, 1);
                        else PI[playerid][pHealth] += 3.0, GameTextForPlayer(playerid, "~b~+3 HP", 400, 1);


                        J_SetPlayerHealth(playerid, PI[playerid][pHealth]);

                        if(PI[playerid][pHealth] >= 100.0)
                        {
                            PI[playerid][pHeal] = 0;
                            PI[playerid][pCheepses]=0;
                            J_SetPlayerHealth(playerid,100);
                            f_TogglePlayerControllable(playerid,true);
                        }
                        PI[playerid][pHealTime] = 0;
                    }
                }

                if(PI[playerid][pMuteTime] > 0)
                {
                    PI[playerid][pMuteTime]--;
                    //UpdatePlayerData(playerid, "MuteTime", PI[playerid][pMuteTime]);

                    if(!PI[playerid][pMuteTime])
                        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы снова можете использовать чат");
                }
                /*if(minutes == 0)
                {
                    if(PI[playerid][pLevel] <= 3)
                    {
                        for(new t; t < sizeof(TrashCanArea); t++)
                            PI[playerid][pTrashCheck][t] = false;

                        new
                            trashstr[140],
                            query_trash[280];

                        format(trashstr, sizeof trashstr, "%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i",    PI[playerid][pTrashCheck][0], PI[playerid][pTrashCheck][1], PI[playerid][pTrashCheck][2],
                                                                                                                            PI[playerid][pTrashCheck][3], PI[playerid][pTrashCheck][4], PI[playerid][pTrashCheck][5],
                                                                                                                            PI[playerid][pTrashCheck][6], PI[playerid][pTrashCheck][7], PI[playerid][pTrashCheck][8],
                                                                                                                            PI[playerid][pTrashCheck][9], PI[playerid][pTrashCheck][10], PI[playerid][pTrashCheck][11],
                                                                                                                            PI[playerid][pTrashCheck][12], PI[playerid][pTrashCheck][13], PI[playerid][pTrashCheck][14],
                                                                                                                            PI[playerid][pTrashCheck][15], PI[playerid][pTrashCheck][16], PI[playerid][pTrashCheck][17],
                                                                                                                            PI[playerid][pTrashCheck][18], PI[playerid][pTrashCheck][19], PI[playerid][pTrashCheck][20]);

                        format(query_trash, sizeof query_trash, "UPDATE `accounts` SET `TrashCheck` = '%s' WHERE `ID` = '%d'", trashstr, PI[playerid][pID]);
                        mysql_tquery(mysql, query_trash);
                    }
                }*/
                if(pTemp[playerid][pRegPaint] && gPaintBall[pbStatus] == 2)
                {
                    pTemp[playerid][pRegPaint] = false;
                    SetPlayerInterior(playerid, 10);
                    SetPlayerVirtualWorld(playerid, 656);
                    PI[playerid][pOldSkin] = GetPlayerSkin(playerid);
                    J_SetPlayerHealth(playerid, 100);

                    new total = gPaintBall[pbPlayers]/2;

                    if(gPaintBall[pbRedTeam] < total)
                    {
                        pTemp[playerid][pPaintTeam] = 1;
                        SetPlayerSkinEx(playerid, 292);
                        gPaintBall[pbRedTeam]++;
                        SetPlayerPos(playerid, -974.2111, 1069.8064, 1344.9972);
                        SetPlayerFacingAngle(playerid, 92.5217);
                    }
                    else if(gPaintBall[pbRedTeam] >= total)
                    {
                        pTemp[playerid][pPaintTeam] = 2;
                        SetPlayerSkinEx(playerid, 293);
                        gPaintBall[pbBlueTeam]++;
                        SetPlayerPos(playerid, -1132.7964, 1049.8667, 1345.7543);
                        SetPlayerFacingAngle(playerid, 270.9352);
                    }

                    ResetPlayerWeapons(playerid);

                    for(new td; td < 8; td++)
                        TextDrawHideForPlayer(playerid, tdPaintBall[td]);

                    for(new td; td < 8; td++)
                        TextDrawShowForPlayer(playerid, tdPaintBall[td]);

                    TextDrawSetString(tdPaintBall[4], "RED TEAM");
                    TextDrawSetString(tdPaintBall[6], "BLUE TEAM");

                    switch(random(3))
                    {
                        case 0:
                        {
                            _GiveGunEx(playerid, 24, 70);
                            _GiveGunEx(playerid, 29, 100);
                        }
                        case 1:
                        {
                            _GiveGunEx(playerid, 31, 140);
                            _GiveGunEx(playerid, 25, 90);
                        }
                        case 2:
                        {
                            _GiveGunEx(playerid, 23, 80);
                            _GiveGunEx(playerid, 25, 90);
                        }
                    }
                    SetPlayerHealth(playerid, 100);
                    PaintUpdate(pTemp[playerid][pPaintTeam]);
                    if(PI[playerid][pMaskON])
                    {
                        if(PI[playerid][pFraction])
                            SetPlayerColor(playerid, gFractionColor[PI[playerid][pFraction] - 1]);

                        else
                            SetPlayerColor(playerid, 0xFFFFFF11);

                        RemovePlayerAttachedObject(playerid, 8);
                        PI[playerid][pMaskON] = 0;
                    }
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У Вас есть маска. Чтобы её использовать введите команду {FFD700}/mask");

                    if(PI[playerid][pQuest] == 13 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
                    {
                        PI[playerid][pQuestProcess] = 1;
                        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
                        PI[playerid][pQuestStatus] = 0;
                        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
                        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
                    }
                }
                if(pTemp[playerid][pRegPaint] && 0 == gPaintBall[pbStatus])
                {
                    pTemp[playerid][pRegPaint] = false;
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы получили компенсацию {33AA00}3000$");
                    GiveMoney(playerid, 3000, "paint компенсация");
                }
                if(pTemp[playerid][pAntiAir]>0) pTemp[playerid][pAntiAir]--;
                ///////
                if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
                {
                    new cuffed = GotoInfo[playerid][gtID];
                    if(!IsPlayerConnected(cuffed) || !IsPlayerLogged[cuffed])
                    {
                        GotoInfo[playerid][gtID] = INVALID_PLAYER_ID;
                        GotoInfo[playerid][gtTPX] = 0.0;
                        GotoInfo[playerid][gtTPY] = 0.0;
                        GotoInfo[playerid][gtTPZ] = 0.0;
                        GotoInfo[cuffed][gtState] = 0;
                        GotoInfo[cuffed][gtStayed] = 0;
                        GotoInfo[cuffed][gtGoID] = INVALID_PLAYER_ID;
                        GotoInfo[cuffed][gtX] = 0.0;
                        GotoInfo[cuffed][gtY] = 0.0;
                        GotoInfo[cuffed][gtZ] = 0.0;
                    }
                }
                new weap = GetPlayerWeapon(playerid);
                new slot = GetWeaponSlot(weap);
                //if(UsePlayerPedAnims(playerid) && IsPlayerLogged[playerid]) PlayerSpawn(playerid);
                if(GotoInfo[playerid][gtGoID] != INVALID_PLAYER_ID)
                {
                    new goid = GotoInfo[playerid][gtGoID];
                    if(IsPlayerConnected(goid) && IsPlayerLogged[goid])
                    {
                        new Float:xX, Float:xY, Float:xZ,Float:agle;
                        GetPlayerPos(goid, xX, xY, xZ);
                        GetPlayerFacingAngle(playerid, agle);
                        if(!IsPlayerInRangeOfPoint(playerid, 20, xX, xY, xZ))
                        {
                            pTemp[playerid][pAntiAir] += 4;
                            SetPlayerInterior(playerid,GetPlayerInterior(goid));
                            SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(goid));
                            NoEnterPickup[playerid] =2;
                            J_SetPlayerFacingAngle(playerid,agle);
                            SetPlayerPos(playerid, xX,xY,xZ);
                        }
                        if(GetPlayerState(goid)==1)
                        {
                            new ANIMATION;
                            if(GotoInfo[goid][gtTPX] != 0.0 || GotoInfo[goid][gtTPY] != 0.0)
                            {
                                SetPlayerFaceToPoint(playerid, GotoInfo[goid][gtTPX], GotoInfo[goid][gtTPY]);
                                ANIMATION = GoPlayerAnimation(playerid, GotoInfo[goid][gtTPX], GotoInfo[goid][gtTPY], GotoInfo[goid][gtTPZ]);
                            }
                            else
                            {
                                TurnPlayerFaceToPlayer(playerid, goid);
                                ANIMATION = GoPlayerAnimation(playerid, xX, xY, xZ);
                            }
                            if(ANIMATION != 1)
                            {
                                if(IsPlayerInRangeOfPoint(playerid, 0.05, GotoInfo[playerid][gtX], GotoInfo[playerid][gtY], GotoInfo[playerid][gtZ]))
                                {
                                    GotoInfo[playerid][gtStayed] ++;
                                    if(GotoInfo[playerid][gtStayed] >= 10)
                                    {
                                        new Float:xA;
                                        pTemp[playerid][pAntiAir] += 4;
                                        GetPlayerPos(playerid, xX, xY, xZ);
                                        GetPlayerFacingAngle(playerid, xA);
                                        ShiftCords(0, xX, xY, xA, 1.5);
                                        SetPlayerPos(playerid, xX, xY, xZ);
                                        GotoInfo[playerid][gtStayed] = 0;
                                    }
                                }
                                else GotoInfo[playerid][gtStayed] = 0;
                                GetPlayerPos(playerid, GotoInfo[playerid][gtX], GotoInfo[playerid][gtY], GotoInfo[playerid][gtZ]);
                            }
                        }
                    }
                    else
                    {
                        GotoInfo[playerid][gtGoID] = INVALID_PLAYER_ID;
                        GotoInfo[playerid][gtX] = 0.0;
                        GotoInfo[playerid][gtY] = 0.0;
                        GotoInfo[playerid][gtZ] = 0.0;
                    }
                }
                if(IsPlayerInRangeOfPoint(playerid, 2.0, 312.4241, -165.9406, 999.6010))
                {
                    new armyid = GetPlayerVirtualWorld(playerid)-1;
                    if((PI[playerid][pFraction] >= 2 && PI[playerid][pFraction] <= 7) && armyid < 3)
                        StealMats(playerid, armyid);

                }

				new string[120];
                pl_afk_time[playerid]++;
                if(pl_afk_time[playerid] >= 3) format(string, sizeof string, "{FFB300}AFK: {FFFFFF}%s сек", Convert(pl_afk_time[playerid]));
                else if(pl_afk_time[playerid] > 7200) format(string, sizeof string, "{FFB300}AFK: {FFFFFF}более двух часов");
                SetPlayerChatBubble(playerid, string, COLOR_WHITE, 10.0, 1600);


                new newkeys,ud,lr;
                GetPlayerKeys(playerid,newkeys,ud,lr);

                if(PI[playerid][pDisease] == 5 && GetPlayerState(playerid) != PLAYER_STATE_DRIVER && temp_tie_sender[playerid] == INVALID_PLAYER_ID)
                {
                    if(newkeys & KEY_SPRINT)
                    {
                        if(ud != 0 || lr != 0)
                            ClearAnimations(playerid), ApplyAnimation(playerid, "FAT", "IDLE_tired", 3.0, 0, 0, 0, 0, 3000);
                    }
                }

                if(PI[playerid][pDisease] == 6 && GetPlayerState(playerid) != PLAYER_STATE_DRIVER && temp_tie_sender[playerid] == INVALID_PLAYER_ID)
                {
                    if(newkeys & KEY_SPRINT)
                    {
                        if(ud != 0 || lr != 0)
                            ClearAnimations(playerid), ApplyAnimation(playerid, "FAT", "IDLE_tired", 3.0, 0, 0, 0, 0, 3000);
                    }
                }

                if(PI[playerid][pJailTime] && pl_afk_time[playerid] <= 3)
                {
                    PI[playerid][pJailTime]--;
                    UpdatePlayerData(playerid, "JailTime", PI[playerid][pJailTime]);
                    if(PI[playerid][pJailTime] <= 0)
                    {
                        PI[playerid][pJailTime] = 0;
                        UpdatePlayerData(playerid, "JailTime", PI[playerid][pJailTime]);
                        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы были освобождены");

                        if(!PI[playerid][pJailAdmin])
                        {
                            new
                                prison = PI[playerid][pPrison]-1;

                            SetPlayerSkinEx(playerid, GetSkinOfPlayer(playerid));
                            SetPlayerInterior(playerid, 0);
                            SetPlayerVirtualWorld(playerid, 0);
                            SetPlayerPos(playerid, gJailExit[prison][0], gJailExit[prison][1], gJailExit[prison][2]);
                            J_SetPlayerFacingAngle(playerid, gJailExit[prison][3]);
                        }
                        else
                            SpawnPlayer(playerid);

                        PI[playerid][pPrison] = 0;
                        UpdatePlayerData(playerid, "Prison", PI[playerid][pPrison]);
                        PI[playerid][pJailAdmin] = 0;
                        UpdatePlayerData(playerid, "JailAdmin", PI[playerid][pJailAdmin]);

                    }
                }
                if(pTemp[playerid][pFermTime])
                {
                    pTemp[playerid][pFermTime]--;
                    if(pTemp[playerid][pFermTime] <= 0)
                    {
                        if(InJob[playerid] != 9)
                            return 1;

                        SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);

                        InJob[playerid] = 0;
                        pTemp[playerid][pFermTime] = 0;
                        pTemp[playerid][pGrass] = 0;

                        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Время аренды поля истекло");
                    }
                }
                if(PI[playerid][pAdvertTime])
                {
                    PI[playerid][pAdvertTime]--;
                    //UpdatePlayerData(playerid, "AdvertTime", PI[playerid][pAdvertTime]);
                }
                if(temp_tazer_timer[playerid])
                {
                    temp_tazer_timer[playerid]--;

                    if(temp_tazer_timer[playerid] <= 0)
                    {
                        temp_tazer_timer[playerid] = 0;
                        ClearAnim(playerid);
                        f_TogglePlayerControllable(playerid, true);
                    }
                }

                if(temp_notpay[playerid] > 0)
                    temp_notpay[playerid]--;

                if(pTemp[playerid][pCheatWarning] && pTemp[playerid][pCheatTime] < gettime())
                {
                    pTemp[playerid][pCheatWarning] = 0;
                    pTemp[playerid][pCheatTime] = 0;
                }


                if(pTemp[playerid][pGNewsTime])
                {
                    pTemp[playerid][pGNewsTime]--;
                    if(pTemp[playerid][pGNewsTime] == 0) pTemp[playerid][pGNews] = 0;
                }

                if(temp_car_timer[playerid] > 0)
                    temp_car_timer[playerid]--;

                if(temp_house_timer[playerid] > 0)
                    temp_house_timer[playerid]--;

                if(temp_biz_timer[playerid] > 0)
                    temp_biz_timer[playerid]--;

                if(temp_job_time[playerid] > 0)
                    temp_job_time[playerid]--;

                if(temp_porter_time[playerid] > 0)
                    temp_porter_time[playerid]--;

                if(temp_sellmed_timer[playerid] > 0)
                    temp_sellmed_timer[playerid]--;

                if(temp_sim_timer[playerid] > 0)
                    temp_sim_timer[playerid]--;

                if(temp_vacation_timer[playerid] > 0)
                    temp_vacation_timer[playerid]--;

                if(temp_inject_timer[playerid] > 0)
                    temp_inject_timer[playerid]--;

                else if(temp_inject_timer[playerid] == 0 && temp_inject_sender[playerid] != INVALID_PLAYER_ID)
                {
                    if(IsPlayerInRangeOfPoint(playerid, 50.0, 693.6690, 1527.1469, 1306.1029) && !temp_inject_need[playerid])
                    {
                        new
                            Float:pos_x,
                            Float:pos_y,
                            Float:pos_z;

                        temp_disease_text[playerid] = Create3DTextLabel("_", 0xFFFFFFFF, pos_x, pos_y, pos_z+1.3, 10.0, playerid);
                        Attach3DTextLabelToPlayer(temp_disease_text[playerid], playerid, 0.0, 0.0, 0.1);
                        Update3DTextLabelText(temp_disease_text[playerid], 0x6699CCFF, "Требуется укол");
                    }
                    else
                        Delete3DTextLabel(temp_disease_text[playerid]);
                }
                if(temp_disease_timer[playerid] > 0)
                    temp_disease_timer[playerid]--;

                else if(temp_disease_timer[playerid] == 0)
                {
                    if(PI[playerid][pDisease] == 2 && temp_tie_sender[playerid] == INVALID_PLAYER_ID)
                    {
                        if(!IsPlayerInAnyVehicle(playerid))
                        {
                            switch(random(2))
                            {
                                case 0: ApplyAnimation(playerid, "FAT", "IDLE_tired", 3.0, 0, 0, 0, 0, 3000);
                                case 1: ApplyAnimation(playerid, "VENDING", "vend_eat1_P", 4.1, 0, 0, 0, 0, 0);
                            }
                        }

                        temp_disease_timer[playerid] = 180;
                    }
                    else if(PI[playerid][pDisease] == 3 && temp_tie_sender[playerid] == INVALID_PLAYER_ID)
                    {
                        if(!IsPlayerInAnyVehicle(playerid))
                            ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0);

                        temp_disease_timer[playerid] = 180;
                    }
                    else if(PI[playerid][pDisease] == 6)
                    {
                        TextDrawShowForPlayer(playerid, RedScreenBox);
                        ScreenStatus[playerid] = 1;

                        PI[playerid][pHealth] =- 1.0;
                        J_SetPlayerHealth(playerid, PI[playerid][pHealth]);

                        RedScreenTimer[playerid] = SetTimerEx("@__RedScreenAnim",1000, true, "i", playerid);
                        temp_disease_timer[playerid] = 180;
                    }
                }
                for(new i ; i < 6; i++)
                    if(AutoTime[i])
                        AutoTime[i]--;

                if(temp_hold_sender[playerid] != INVALID_PLAYER_ID)
                {
                    new
                        Float:px,
                        Float:py,
                        Float:p_distance,
                        sender = temp_hold_sender[playerid]-1;

                    GetPlayerPos(sender, px, py, p_distance);
                    p_distance = GetDistanceBetweenPlayers(playerid, sender);

                    if(p_distance <= 2.0 && temp_hold_status[playerid] == 1)
                    {
                        ClearAnimations(playerid, 1);
                        f_TogglePlayerControllable(playerid, false);
                        SetPlayerLook(playerid, px, py);
                        temp_hold_status[playerid] = 2;
                    }
                    else if(p_distance > 2.5)
                    {
                        ApplyAnimation(playerid, "ped",
                            (p_distance < 6.0) ? ("WALK_player") : ("run_player"),
                            4.1, 1, 1, 1, 0, 0, 1);
                        SetPlayerLook(playerid, px, py);
                        if(temp_hold_status[playerid] != 2)
                        {
                            f_TogglePlayerControllable(playerid, true);
                            temp_hold_status[playerid] = 2;
                        }
                    }


                }
                if(PI[playerid][pSpectating]) UpdateSpectating(playerid);
                if(pl_afk_time[playerid] < 3) PI[playerid][pPlayed]++;


                new weapon = GetPlayerWeapon(playerid);
                new ammo = GetPlayerAmmo(playerid);

                if(gunmute[playerid]<=gettime())
                {
                    if(weapon>0)
                    {
                        if(weap!=46)
                        {
                            if(WeaponInfo[playerid][weap] == false && weap != 0) ToCheat(1,playerid),SCM(playerid,-1,"[1]");
                            for (new s = 0; s <= 12; s++) GetPlayerWeaponData(playerid, s, weapons[s][0], weapons[s][1]);
                            if(weapons[slot][1] > 0)
                            {
                                if(weapons[slot][1] > AmmoInfo[playerid][weap])  ToCheat(1,playerid),SCM(playerid,-1,"[2]");
                                else if(weapons[slot][1] < AmmoInfo[playerid][weap])
                                {
                                    AmmoInfo[playerid][weap] = weapons[slot][1];
                                    PI[playerid][pAmmos][slot] = weapons[slot][1];
                                }
                                if(AmmoInfo[playerid][weap] <= 0) WeaponInfo[playerid][weap] = false;
                                if(AmmoInfo[playerid][weap] < 0) ToCheat(1,playerid),SCM(playerid,-1,"[3]");
                            }
                        }
                    }
                    if(weapon == 4 || weapon == 37 || weapon == 36 || weapon == 35 || weapon == 39 || weapon == 36 || weapon == 16 || weapon == 18 || weapon == 38 || weapon == 44 || weapon == 45)
                    {
                        _ResetGun(playerid);
                        ToCheat(1,playerid);
                    }
                    if(PI[playerid][pGuns][GetWeaponSlot(weapon)] == weapon )
                    {
                        if(PI[playerid][pAmmos][slot]==GetPlayerAmmo(playerid))
                        {
                            PI[playerid][pLastGun]=weapon;
                            PI[playerid][pLastAmmo]= ammo;
                        }
                    }
                }

                if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
                {
                    new str[110];
                    format(str,sizeof(str),"[AC] Игрок %s кикнут за использование JetPack'a",Name(playerid));
                    SendAdminsMessage(COLOR_LIGHTRED,str,1);
                    CheatMessage(playerid);
                    J_Kick(playerid);
                }
                if(PI[playerid][pMoney] < 0)
                {
                    SetPlayerMoney(playerid, 0);
                    SCM(playerid, COLOR_RED, "Были кикнуты за использование багов");
                    new str[128];
                    format(str,sizeof(str),"< Money [-] > %s[%d] Подозревается в использовании, багов и был кикнут!",Name(playerid),playerid);
                    SendAdminsMessage(COLOR_RED,str,1);
                    J_Kick(playerid);
                }

                new attached_info = IsPlayerAttachedObjectSlotUsed(playerid, 9);
                if(GetPlayerMoney(playerid) >= 1000000 && !IsPlayerInAnyVehicle(playerid) && GetPlayerWeapon(playerid) == 0)
                {
                    if(!attached_info && PI[playerid][pShowCase]==0 && InJob[playerid] != 5 && InJob[playerid] != 6 && InJob[playerid] != 7)
                        SetPlayerAttachedObject(playerid,9,1210,5,0.299999,0.099999,0.000000,0.000000,-83.000000,0.000000,1.000000,1.000000,1.000000);
                }
                else if(attached_info) RemovePlayerAttachedObject(playerid, 9);

                new Float:Health; GetPlayerHealth(playerid, Health);
                if(AntiCheatOFF[playerid][HEALTH_HACK]>0)AntiCheatOFF[playerid][HEALTH_HACK]--;
                if(!AntiCheatOFF[playerid][HEALTH_HACK] && Health > PI[playerid][pHealth]) SetPlayerHealth(playerid, PI[playerid][pHealth]);
                if(!AntiCheatOFF[playerid][HEALTH_HACK] && Health < PI[playerid][pHealth]) PI[playerid][pHealth] = Health;
                new Float:Armour;GetPlayerArmour(playerid, Armour);
                if(AntiCheatOFF[playerid][ARMOUR_HACK]>0)AntiCheatOFF[playerid][ARMOUR_HACK]--;
                if(!AntiCheatOFF[playerid][ARMOUR_HACK] && Armour > PI[playerid][pArmour]) SetArmour(playerid, PI[playerid][pArmour]);
                if(!AntiCheatOFF[playerid][ARMOUR_HACK] && Armour < PI[playerid][pArmour]) PI[playerid][pArmour] = Armour;

            }
            if(!IsPlayerLogged[playerid])
            {
                if(pTemp[playerid][pAuthTimeout] > 0)
                {
                    pTemp[playerid][pAuthTimeout]--;
                    if(pTemp[playerid][pAuthTimeout] == 0)
                     {
                        SendClientMessage(playerid, COLOR_RED, !"Вы были кикнуты за бездействие при авторизации");
                        J_Kick(playerid);
                    }
                }
            }
            if(GetPlayerSurfingVehicleID(playerid) != INVALID_VEHICLE_ID)
            {
                new cid = GetPlayerSurfingVehicleID(playerid);
                new cm = GetVehicleModel(cid);
                switch(cm)
                {
                    case 430,446,452,453,454,472,473,484,493,595:{return 1;} // если это лодка, скидывать ненадо
                    default:{}
                }
                new Float:x, Float:y, Float:z;
                GetPlayerPos(playerid, x,y,z);
                x -= 1.5;
                SetPlayerPos(playerid, x,y,z);
            }
            if(temp_filling_going[playerid])
            {
                new
                    vehicleid = GetPlayerVehicleID(playerid);

                if(vehicleid && temp_filling_amount[playerid] > VehicleInfo[vehicleid][vFuel] + 1.0)
                    VehicleInfo[vehicleid][vFuel] += 1.0;

                else if(vehicleid)
                {
                    VehicleInfo[vehicleid][vFuel] = temp_filling_amount[playerid];
                    f_TogglePlayerControllable(playerid, true);
                    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно]{ffffff} Транспорт заправлен, можете ехать");
                    temp_filling_buy_id[playerid] = 0;
                    temp_filling_amount[playerid] = 0;
                    temp_filling_speed[playerid] = 0;
                    temp_filling_accel[playerid] = 0;
                    temp_filling_going[playerid] = false;
                    temp_filling_status[playerid] = false;
                    temp_filling_id[playerid] = 0;
                    temp_filling_price[playerid] = 0;
                }
            }

        }

    }
    time_grandtimer = GetTickCount() - tickcount1;
    if(time_grandtimer > time_grandtimer_max) time_grandtimer_max = time_grandtimer;
    return true;
}
stock LastSeconds(hour, minute, second, day, month, year)
{
	new hour2,minute2,second2,day2,month2,year2;
	gettime(hour2, minute2, second2), getdate(year2, month2, day2);
    return mktime(hour2, minute2, second2, day2, month2, year2) - mktime(hour,minute,second,day,month,year);
}
stock mktime(hour,minute,second,day,month,year) {
	new timestamp2;
	timestamp2 = second + (minute * 60) + (hour * 3600);
	new days_of_month[12];

	if ( ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0) ) {
			days_of_month = {31,29,31,30,31,30,31,31,30,31,30,31};
		} else {
			days_of_month = {31,28,31,30,31,30,31,31,30,31,30,31};
		}
	new days_this_year = 0;
	days_this_year = day;
	if(month > 1) {
		for(new i=0; i<month-1;i++) {
			days_this_year += days_of_month[i];
		}
	}
	timestamp2 += days_this_year * 86400;

	for(new j=1970;j<year;j++) {
		timestamp2 += 31536000;
		if ( ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0) )  timestamp2 += 86400;
	}

	return timestamp2;
}
stock SetBumSkin(playerid)
{
	SetPlayerSkinEx(playerid, PI[playerid][pSkin]);
	f_TogglePlayerControllable(playerid,true);
	return true;
}
stock CheckCarTime(carid)
{
    CarTime[carid] += 10;
	return true;
}

@__FuelTimer();
@__FuelTimer()
{
    for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if(GetEngineStatus(i) > 0)
		{
			if(VehicleInfo[i][vFuel] >= 1.0) VehicleInfo[i][vFuel] -= 1.0;
			else VehicleInfo[i][vFuel] = 0;
		}
	}
}
@__MinuteTimer();
@__MinuteTimer()
{
	foreach(new i: Player)
	{
		if(PI[i][pAdmin] > 0 && pl_afk_time[i] < 4)
		{
		    PI[i][pAdminTime]++;
		    UpdatePlayerData(i, "AdminTime", PI[i][pAdminTime]);
		}


		if(pTemp[i][pAntiDM])
		{
            pTemp[i][pAntiDM]--;
            if(pTemp[i][pAntiDM] == 0)
                temp_green_zone_warning[i] = 0;

		}
	}
	
	new query_update_online[50];
	format(query_update_online, sizeof query_update_online, "UPDATE `settings` SET `online` = '%d'", Iter_Count(Player));
	mysql_tquery(mysql, query_update_online);
}

stock CheckNextLevel(playerid)
{
	new expamount = ( PI[playerid][pLevel] + 1) * 4, string[144];
	if(PI[playerid][pExp] >= expamount)
	{
		PI[playerid][pLevel] ++;
		PI[playerid][pAge]++;
		PI[playerid][pExp] -= expamount;
		SetPlayerScore(playerid,PI[playerid][pLevel]);
		format(string,sizeof(string),"Поздравляем! Вы достигли %d-го уровня!",PI[playerid][pLevel]);
		SCM(playerid,COLOR_GREEN,string);
		if(PI[playerid][pLevel] == 2)
		{
		    if(PI[playerid][pPromo])
		    {
		        new
		            promoid = PI[playerid][pPromo]-1;
		            
				if(gPromo[promoid][pcSettings][0])
				{
					PI[playerid][pDaysExp] = 3;
					UpdatePlayerData(playerid, "DaysExp", PI[playerid][pDaysExp]);
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У Вас активен бонус удвоенного опыта");
				}

				if(gPromo[promoid][pcSettings][1])
				{
					PI[playerid][pDaysSalary] = 3;
					UpdatePlayerData(playerid, "DaysSalary", PI[playerid][pDaysSalary]);
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У Вас активен бонус удвоенной зарплаты на начальных работах");
				}
			}
		}
		if(PI[playerid][pLevel] == PI[playerid][pPromoLvl])
		{
		    if(PI[playerid][pPromo])
		    {
		        new
		            //promoid = PI[playerid][pPromo]-1,
					frmt_bank_message[110];
		            
				format(frmt_bank_message, sizeof frmt_bank_message, "{FFC800}[Подсказка] {FFFFFF}Вы получили {33AA33}%d${FFFFFF} за использование промокода", PI[playerid][pPromoBonus]);
				SendClientMessage(playerid, COLOR_WHITE, frmt_bank_message);

				GiveMoney(playerid, PI[playerid][pPromoBonus]);

			    PI[playerid][pPromoLvl] = 0;
	            UpdatePlayerData(playerid, "PromoLvl", PI[playerid][pPromoLvl]);
	            PI[playerid][pPromoBonus] = 0;
	            UpdatePlayerData(playerid, "PromoBonus", PI[playerid][pPromoBonus]);
			}
		}
		return true;
	}
	return false;
}

stock PN(playerid, sql = 0) //Player Name
{
	if(sql) mysql_real_escape_string(PlayerName[playerid], PlayerName[playerid]);
	return PlayerName[playerid];
}
stock cPN(playerid)//Chat Player Name
{
	return PlayerName[playerid];
}
weekday(day, month, year)
{
    if (month <= 2)
        month += 12, --year;
    new j = year % 100;
    new e = year / 100;
    return (day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7;
}
stock SendAdminsMessage(color, const string[], level = 1)
{
    foreach(new i : Connect_Admin)
    {
		if(!IsPlayerConnected(i))
			continue;
			
        if(PI[i][pAdmin] >= level && ADuty[i] == 228)
			SendClientMessage(i, color, string);
    }
    return true;
}
stock SendAntiCheatLog(target, code)
{
	new
	    frmt_log_message[65];
	    
	format(frmt_log_message, sizeof frmt_log_message, "Игрок %s был кикнут античитом [№%d]", PN(target), code);
    foreach(new i : Connect_Admin)
    {
		if(!IsPlayerConnected(i))
			continue;

        if(PI[i][pAdmin] >= 1 && ADuty[i] == 228 && pTemp[i][pAntiCheatLogs])
			SendClientMessage(i, 0x8800B8FF, frmt_log_message);
    }
    return true;
}
stock SendTesterMessage(color = -1, const string[] = "")
{
  	foreach(new i : Player)
	{
	    if(i != -1)
	    {
			if(IsPlayerConnected(i))
			{
				if(PI[i][pTester] && temp_tester_code[i] == 0 || PI[i][pAdmin] >= 5 && temp_ears_testchat[i])
		 			SCM(i, color, string);
			}
		}
	}
	return true;
}
stock PlayerIP(playerid)
{
	return PlayerIp[playerid];
}
stock CheckPlayerBanIP(playerid)
{
	new string[100], IP[16];
	GetPlayerIp(playerid, IP, 16);
	format(string,sizeof(string),"SELECT * FROM `BanIP` WHERE `IP` = '%s' LIMIT 1", IP);
	new Cache:result = mysql_query(mysql, string);
	if(cache_get_row_count(mysql) > 0)
	{
	    cache_delete(result, mysql);
	    SCM(playerid, COLOR_LIGHTRED, "Данный IP заблокирован на нашем сервере!");
		J_Kick(playerid);
		return 1;
	}
	cache_delete(result, mysql);
	return false;
}
stock BanPlayer(playerid)
{
	BanName(Name(playerid),"который выдал варн в оффлайне",5,"Заблокирован за получение 3-ех варнов");
	J_Kick(playerid);
	return true;
}
stock IsBannedName(name[])
{
	new string[200];
	format(string, sizeof(string), "SELECT `Name` FROM `bannames` WHERE BINARY `Name` = '%s' LIMIT 1",name);
	new Cache:result = mysql_query(mysql, string);
	new i = cache_get_row_count(mysql);
    cache_delete(result, mysql);
	return i;
}
stock BanName(name[], namez[], days, reason[])
{
    new string[200];
	if(!IsBannedName(name))
	{
	    format(string, sizeof(string), "INSERT INTO `bannames` (`Name`, `BanAdmin`, `BanSeconds`, `BanReason`) VALUE ('%s', '%s', '%d', '%s')",name, namez, gettime()+days*60*60*24, reason);
	    mysql_tquery(mysql, string);
	}
	return true;
}
stock BanIP(IP[])
{
    new string[256];
    //format(string,sizeof(string),"DELETE FROM `BanIP` WHERE `IP` = '%s' LIMIT 1",IP);
    format(string,sizeof(string),"INSERT INTO `BanIP` (`IP`) VALUE ('%s')",IP);
	mysql_tquery(mysql, string);
	return true;
}
stock UnBanIP(IP[])
{
    new string[256];
    format(string,sizeof(string),"DELETE FROM `BanIP` WHERE `IP` = '%s'",IP);
	mysql_tquery(mysql, string);
	return true;
}
stock Convert(number)
{
	new hours = 0, mins = 0, secs = 0, string[30];
	hours = floatround(number / 3600);
	mins = floatround((number / 60) - (hours * 60));
	secs = floatround(number - ((hours * 3600) + (mins * 60)));
	if(hours > 0) format(string, 30, "%d:%02d:%02d", hours, mins, secs);
	else format(string, 30, "%d:%02d", mins, secs);
	return string;
}
stock ConvertMsToTime(ms)
{
    new seconds = ms/1000;
    new string[32];
    format(string, sizeof(string), "%02d:%02d:%02d",
        (seconds%86400)/3600, (seconds%3600)/60, seconds%60);
    return string;
}
stock UnBanName(name[])
{
    new string[256];
	if(IsBannedName(name))
	{
        format(string, sizeof(string), "DELETE FROM `bannames` WHERE BINARY `Name` = '%s'",name);
        mysql_tquery(mysql, string);
	}
	return true;
}
stock CarryAnim(playerid)
{
    ApplyAnimation(playerid, "CARRY", "CRRY_PRTIAL", 4.1, 0, 1, 1, 1, 1, 1);
    return true;
}
stock SuccesAngle(Float:angle, Float:ang1, Float:ang2)
{
	return (ang1 <= angle <= ang2);
}
stock IsAZavodSkin(playerid)
{
	new skin = GetPlayerSkin(playerid);
	return (skin == 259 || skin == 260);
}
stock SendMuteMessage(playerid, ret = 1)
{
	new string[200];
	format(string,sizeof(string),"У Вас бан чата. Оставшееся время заглушки %d %s", PI[playerid][pMuteTime]/60, Declension_GetMinutes(PI[playerid][pMuteTime]/60));
	SCM(playerid,COLOR_GREY,string);
	return ret;
}
stock CancelCuff(playerid)
{
    if(PlayerOfCuff[playerid] != INVALID_PLAYER_ID)
	{
		new targetid = PlayerOfCuff[playerid];
	    PlayerOfCuff[playerid] = INVALID_PLAYER_ID;
	    if(PlayerOfCuff[targetid] == playerid)
		{
	    	TimeOfCuff[targetid] = 0;
	    	PlayerOfCuff[targetid] = INVALID_PLAYER_ID;
		}
		ClearAnims(playerid);
	}
	return true;
}
stock GetJobName(jobid)
{
	new
		jobname[50];
		
	switch(jobid)
	{
	    case 1: strcat(jobname, "Водитель автобуса");
	    case 2: strcat(jobname, "Таксист");
		case 4: strcat(jobname, "Механик");
		case JOB_PRODUCT: strcat(jobname, "Развозчик заказов");
	    case 11: strcat(jobname, "Дальнобойщик");
	    default: strcat(jobname, "Нет");
	}
	return jobname;
}
stock GetKeyName(key)
{
	new Name[6];
	switch(key)
	{
	    case KEY_SPRINT: Name = "Space";
	    case KEY_JUMP: Name = "Shift";
	    case KEY_FIRE: Name = "Ctrl";
	    default: Name = "Alt";
	}
	return Name;
}
stock SetSpawnInfoEx(playerid, skin, Float:x, Float:y, Float:z, Float:a)
{
    pTemp[playerid][pAntiAir] += 6;
	SetPlayerPos(playerid, x, y, z);
	SetPlayerSkinEx(playerid, skin);
	J_SetPlayerFacingAngle(playerid, a);

    return 1;
}

stock ShowStats(playerid,giveplayerid)
{
	if(!IsPlayerConnected(giveplayerid)) return false;
	new stats_string[1200];
	new mes_stats[2300];
	new aSex[8],
		nation[20],
		fraction[32],
		job[70],
		jobs[70],
		houseinfo[45],
		bizinfo[40],
		classname[14],
		married[MAX_PLAYER_NAME],
		year,
		month,
		day,
		hour,
		minute,
		second;
		
	getdate(year, month, day);
	gettime(hour,minute,second);

	aSex = (PI[giveplayerid][pSex] == 1) ? ("Мужской") : ("Женский");

 	if(!strlen(PI[giveplayerid][pMerrit])) format(married,sizeof(married),"Отсутствует");
	else format(married,sizeof(married),"%s", PI[giveplayerid][pMerrit]);

    switch(PI[giveplayerid][pNation])
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

	format(jobs, 32, "%s", GetJobName(PI[giveplayerid][pJob]));
	if(!PI[giveplayerid][pFraction] && !PI[giveplayerid][pv_Fraction]) format(job, 32, "Отсутствует");

 	if(PI[giveplayerid][pFraction])
	{
		new fractionid = PI[giveplayerid][pFraction]-1;
		new rank = PI[giveplayerid][pRank];
		strcat(fraction, gFractionName[fractionid]);
		if(PI[giveplayerid][pSubfraction] > 0)
		{
			new frid = GetSubfractionID(fractionid+1);
			new subid = PI[giveplayerid][pSubfraction]-1;
			strcat(job, gSubfractionName[frid][subid]);
			strcat(job, " / ");
		}
		if(fractionid+1 == 10 && !PI[playerid][pSubfraction] && rank <= 9)
			strcat(job, gPrezRankName[rank-1]);
			
		else strcat(job,gFractionRankName[fractionid][rank-1]);
	}
 	else if(PI[giveplayerid][pv_Fraction])
	{
		new fractionid = PI[giveplayerid][pv_Fraction]-1;
		new rank = PI[giveplayerid][pv_Rank];
		strcat(fraction, gFractionName[fractionid]);
		if(PI[giveplayerid][pv_Subfraction] > 0)
		{
			new frid = GetSubfractionID(fractionid+1);
			new subid = PI[giveplayerid][pv_Subfraction]-1;
			strcat(job, gSubfractionName[frid][subid]);
			strcat(job, " / ");
		}
		if(fractionid+1 == 10 && !PI[playerid][pv_Subfraction] && rank <= 9)
			strcat(job, gPrezRankName[rank-1]);

		else strcat(job,gFractionRankName[fractionid][rank-1]);
	}
	else format(fraction, 32, "Отсутствует");

	if(PI[giveplayerid][pHouseKey] != 0)
	{
		switch(HouseInfo[PI[giveplayerid][pHouseKey]-1][hLevel])
		{
			case 0:classname = "[Эконом]";
			case 1:classname = "[Cредний]";
			case 2:classname = "[Элитный]";
			case 3:classname = "[Особняк]";
			default: classname = "[Неизвестно]";
		}
		format(houseinfo,sizeof(houseinfo), "%d %s", PI[giveplayerid][pHouseKey], classname);
	}
	else format(houseinfo,sizeof(houseinfo), "\tОтсутствует");

	if(PI[giveplayerid][pBizKey] != 0)
	{
	    new
	        bizid = PI[giveplayerid][pBizKey];
	        
		if(bizid > 1000)
		    format(bizinfo, sizeof bizinfo, "АЗС №%d", bizid-1000);
		    
		else
			format(bizinfo, sizeof(bizinfo), "%s (%d)", BizInfo[bizid-1][bName], bizid);
	}
	else
		format(bizinfo, sizeof(bizinfo), "Отсутствует");

	if(PI[giveplayerid][pTester])
	{
	    format(mes_stats,sizeof(mes_stats),"{FFF312}Тестер проекта\n\n");
		strcat(stats_string,mes_stats);
	}
    format(mes_stats,sizeof(mes_stats),"{FFFFFF}Номер аккаунта:\t\t{0099ff}%d\n",PI[giveplayerid][pID]);
	strcat(stats_string,mes_stats);
 	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Имя:\t\t\t\t{0099ff}%s\n", Name(giveplayerid));
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Уровень:\t\t\t{0099ff}%d\n",PI[giveplayerid][pLevel]);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Очки опыта:\t\t\t{0099ff}%d из %d\n",PI[giveplayerid][pExp], (PI[giveplayerid][pLevel]+1)*4);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Предупреждений:\t\t{0099ff}%d\n\n",PI[giveplayerid][pWarns]);
	strcat(stats_string,mes_stats);

	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Номер телефона:\t\t{0099ff}%d\n", PI[giveplayerid][pTelNum]);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}На счету телефона:\t\t{0099ff}%d\n\n", PI[giveplayerid][pIn_Skill]);
	strcat(stats_string,mes_stats);

	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Законопослушность:\t\t{0099ff}%d\n", PI[giveplayerid][pZKP]);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Уровень розыска:\t\t{0099ff}%d\n", PI[giveplayerid][pWanted]);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Наркотиков:\t\t\t{0099ff}%d гр.\n", PI[giveplayerid][pDrugs]);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Патроны:\t\t\t{0099ff}%d\n", PI[giveplayerid][pMats]);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Ед. Оружия:\t\t\t{0099ff}%d\n\n", PI[giveplayerid][pPackets]);
	strcat(stats_string,mes_stats);

	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Пол:\t\t\t\t{0099ff}%s\n", aSex);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Возраст:\t\t\t{0099ff}%d\n", PI[giveplayerid][pAge]);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Муж/Жена:\t\t\t{0099ff}%s\n", married);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Национальность:\t\t{0099ff}%s\n\n", nation);
	strcat(stats_string,mes_stats);

	if(!PI[giveplayerid][pv_Days])
	{
		format(mes_stats,sizeof(mes_stats),"{FFFFFF}Организация:\t\t\t{0099ff}%s\n", fraction);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{FFFFFF}Должность:\t\t\t{0099ff}%s\n", job);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{FFFFFF}Работа: \t\t\t{0099ff}%s\n", jobs);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{FFFFFF}Ранг:\t\t\t\t{0099ff}%d\n", PI[giveplayerid][pRank]);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{FFFFFF}Выговоров:\t\t\t\t{0099ff}%d\n\n", PI[giveplayerid][pFWarns]);
		strcat(stats_string,mes_stats);
	}
	else
	{
		format(mes_stats,sizeof(mes_stats),"{F4CD8A}(В отпуске на %d %s)\n", PI[giveplayerid][pv_Days], Declension_GetDays(PI[giveplayerid][pv_Days]));
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{F4CD8A}Организация:\t\t\t%s\n", fraction);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{F4CD8A}Должность:\t\t%s\n", job);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{FFFFFF}Работа: \t\t\t{0099ff}%s\n", jobs);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{F4CD8A}Ранг:\t\t\t\t%d\n", PI[giveplayerid][pv_Rank]);
		strcat(stats_string,mes_stats);
		format(mes_stats,sizeof(mes_stats),"{F4CD8A}Выговоров:\t\t\t\t%d\n\n", PI[giveplayerid][pv_FWarns]);
		strcat(stats_string,mes_stats);
	}

	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Дом:\t\t\t\t{0099ff}%s\n", houseinfo);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Бизнес:\t\t\t{0099ff}%s\n\n", bizinfo);
	strcat(stats_string,mes_stats);
	//format(mes_stats,sizeof(mes_stats),"{FFFFFF}Отель:\t\t\t\t{0099ff}%s\n\n", hotelinfo);
	//strcat(stats_string,mes_stats);

	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Время:\t\t\t\t{0099ff}%02d:%02d:%02d\n", hour,minute,second);
	strcat(stats_string,mes_stats);
	format(mes_stats,sizeof(mes_stats),"{FFFFFF}Дата:\t\t\t\t{0099ff}%02d.%02d.%02d", day,month,year);
	strcat(stats_string,mes_stats);

	ShowPlayerDialogEx(playerid, 871, DIALOG_STYLE_MSGBOX, "Статистика", stats_string, "Закрыть", "");
	return true;
}

stock ApplyAnimationEx(playerid, animid, Float:fDelta, loop, lockx, locky, freeze, time, forcesync)
{
	new animlib[32], animname[32];
	GetAnimationName(animid, animlib, 32, animname, 32);
	return ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
}



stock GiveBizMoney(bizid,money)
{
	if(BizInfo[bizid][bWin]>4000000) return false;
	BizInfo[bizid][bMoney]+=money;
	BizInfo[bizid][bWin]+=money;
    return true;
}

stock GiveMoney(playerid, money, reason[] = "None")
{
	if(!IsPlayerLogged[playerid])
		return 1;
		
    AntiCheatOFF[playerid][MONEY_HACK] = 10;
    
	static
		query_givemoney[210];
		
	query_givemoney[0] = '\0';
	
	PI[playerid][pMoney] += money;
	SetPlayerMoney(playerid, PI[playerid][pMoney]);

	format(query_givemoney, sizeof query_givemoney, "UPDATE `accounts` SET `Money` = `Money`+'%d' WHERE `ID` = '%d'", money, PI[playerid][pID]);
	mysql_tquery(mysql, query_givemoney, "", "");
	
    static
        query_moneylog[81+10+20+80+20];

    query_moneylog[0] = '\0';

	format(query_moneylog, sizeof query_moneylog, "INSERT INTO `moneylog` VALUES ('', '%d', '%d', NOW(), '%s')", PI[playerid][pID], money, reason);
	mysql_tquery(mysql, query_moneylog, "", "");
	
	return true;
}

stock House_Log(playerid,houseid)
{
	static query[150];
	format(query, sizeof query, "INSERT INTO `house_log` VALUES ('', '%d', '%d', NOW())", PI[playerid][pID], houseid);
	mysql_tquery(mysql, query, "", "");
	return 1;
}
stock GivePromoMoney(playerid, promoid, money)
{
    gPromo[promoid][pcBank] += money;

    new
        query_save_bank[100];

	format(query_save_bank, sizeof query_save_bank, "UPDATE `promoyt` SET `pcBank` = '%d' WHERE `pcID` = %d", gPromo[promoid][pcBank], promoid+1);
	mysql_tquery(mysql, query_save_bank);

	PI[playerid][pPromoSalary] += money;
	UpdatePlayerData(playerid, "PromoSalary", PI[playerid][pPromoSalary]);
}


stock GiveBankMoney(playerid, money)
{
	PI[playerid][pBank] += money;
	return true;
}
forward GetMoney(playerid);
public GetMoney(playerid)
{
	return PI[playerid][pMoney];
}
stock SetString(param_1[], param_2[], size = 300)
{
    return strmid(param_1, param_2, 0, strlen(param_2), size);
}



stock GetRankName(org, rank)
{
	if(rank > 0) return RankName[org][(rank-1)];
	else return RankName[org][0];
}
new Domains[][] =
{
	"Гоменюк","ЛОХ","хуй","гамно","ХУЙ","Сливчик","СЛИВЧИК","Самп","САМП","скачал","СКАЧАЛ","факт","Пиздуйте","ПИЗДУЙТЕ","ГОВНА","говна","я Правда","Я ПРАВДА","я ПРАВДА","АРИЗОНЕ","Аризоне","Пиздорасы","ПИДОРАСЫ","ЕБУ","ебу","ебал","ЕБАЛ",
 	"пизда","виртов","Слив","шалава","месная","уходите","Факты","ФАКТЫ","ФАКТ","Факт","СВИТ","Свит","A","a","B","b","C","c","D","d","E","e","F","f","G","g",
	"H","h","I","i","J","j","K","k","L","l","M","m","N","n","O","o","P","p","Q","q","R","r","S","s","T","t","U","u","V","v","W","w","X","x","Y","y","Z","z","гугл","яндекс","Стейдж","Даймонд","Диамонд","Ухадите","Уходите","сервер","Сервер","стейдж","диамонд","даймонд","Чит","ЧИТ","Мастер","мастер","МАСТЕР","админ","АДМИН","Админ","Лидерк","лидерк","ЛИДЕРК"
};
new Mgs[][] =
{
	"самп","школьник","интернет","дота","samp","gta","вирт","вирты","скайп","skype","админ","банили","Warn","WARN","кикнуло","мут","афк","слили","крашнуло","краш","фрапс","нонРП","забанили","разбан","+С","+C","Клео","клео","лаги","лагает","пинг","фпс","fps","cleo","ban","warn","kick","mute","/","ПАХА","Паха","паха","GVR","gvr","ГВР","гвр","подпищик","подписчик","ПОДПИСЧИК","капт","Капт","форум","пукан","школота","скачал","прокачал",
	"ютуб","вконтакте","youtube","бомбит","читы","собей","sobei","сорь","мамка","ддос","ddos","лидерка","солью","role","Role","play","Play","ролеплей","Админ",",баги","багов","багоюз","краб","мгшник","дмщик","Дмщик","нубло","дотер","салоед","кацап","DM","dm","mg","tk","MG","Mg","CK","ck","Sk","pg","PG","Tk","TK","SK","metagaming","Metagaming","афк","АФК","Афк","afk","AFK"
};
stock IsAMg(text[])
{
	for(new i; i < sizeof(Mgs); i ++)
	{
	    new find = strfind(text, Mgs[i], true);
	    if(find != -1) if(IsASymbol(text, find - 2, find))return true;
	}
	return false;
}

stock IsASymbol(text[], first, end)
{
	if(first < 0) first = 0;
	if(end >= strlen(text)) end = strlen(text) - 1;
	for(new i = first; i <= end; i ++) return true;
	return false;
}

stock IsADomen(text[])
{
	for(new i; i < sizeof(Domains); i ++)
	{
	    new find = strfind(text, Domains[i], true);
	    if(find != -1) if(IsASymbol(text, find - 2, find))return true;
	}
	return false;
}
stock IsAIP(text[])
{
	new numbers;
	for(new i = 0;i < strlen(text); i++) if('0' <= text[i] <= '9') if(!('0' <= text[i+1] <= '9')) numbers ++;
	if(numbers >= 4) return true;
	return false;
}
stock IsVehicleInRangeOfPoint(vehicleid, Float:distance, Float:x, Float:y, Float:z)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetVehiclePos(vehicleid, oldposx, oldposy, oldposz);
	tempposx = (oldposx - x);
	tempposy = (oldposy - y);
	tempposz = (oldposz - z);
	if (((tempposx < distance) && (tempposx > -distance)) && ((tempposy < distance) && (tempposy > -distance)) && ((tempposz < distance) && (tempposz > -distance)))return true;
	return false;
}
stock GetGasStation(playerid)
{
	new gasid = -1;
    if(IsPlayerConnected(playerid))
	{
		for(new i;i < sizeof(FuelInfo);i ++)
		{
		    if(IsPlayerInRangeOfPoint(playerid,20.0,FuelInfo[i][fPos_X],FuelInfo[i][fPos_Y],FuelInfo[i][fPos_Z]))
		    {
		        gasid = i;
		        break;
		    }
		}
	}
	return gasid;
}
stock IsAtGasStation(playerid)
{
    if(IsPlayerConnected(playerid))
	{
	    new bool:Succes = false;
		for(new i;i < sizeof(FuelInfo);i ++)
		{
		    if(IsPlayerInRangeOfPoint(playerid,25.0,FuelInfo[i][fPos_X],FuelInfo[i][fPos_Y],FuelInfo[i][fPos_Z]))
		    {
		        Succes = true;
		        break;
		    }
		}
		return Succes;
	}
	return false;
}
stock IsAtGasStationC(carid)
{
	new bool:Succes = false;
	for(new i;i < sizeof(FuelInfo);i ++)
	{
		if(IsVehicleInRangeOfPoint(carid,10.0,FuelInfo[i][fPos_X],FuelInfo[i][fPos_Y],FuelInfo[i][fPos_Z]))
		{
			Succes = true;
			break;
		}
	}
	return Succes;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if(passenger_seat != 0)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 5.0, new_x, new_y, new_z)) return false;
		else if(!IsPlayerInVehicle(playerid, vehicleid)) return false;
		if(timeforcd[playerid] == 0)
		{
		    if(pTemp[playerid][pCheatTime] > 4) KickEx(playerid, 23);
			new lstring[128];
			format(lstring, sizeof(lstring), "[AC] » Игрок %s[%d] возможно использует CarShot.", PN(playerid), playerid);
			SendAdminsMessage(0xFF00FFFF, lstring);
			pTemp[playerid][pCheatTime]+=4;
		}
		timeforcd[playerid] = 10;
		new Float:shealth, Float:slx, Float:sly, Float:slz;
		AntiCheatGetHealth(playerid, shealth);
		SetPlayerHealth(playerid, shealth-5);
		GetPlayerPos(playerid, slx, sly, slz);
		return SetPlayerPos(playerid, slx, sly, slz+5);
	}
	return 1;
}

public MailResponse(index, response_code, data[])
{
	return true;
}
stock LoadVehicle()
{
    new Cache:result = mysql_query(mysql, "SELECT * FROM `transport`");
	OWNABLEVEHICLE = cache_get_row_count(mysql);
	for(new idx = 0;idx < OWNABLEVEHICLE; idx++)
	{
		Transport[idx][trID] = cache_get_row_int(idx, 0, mysql);
		Transport[idx][trModel] = cache_get_row_int(idx, 1, mysql);
		cache_get_row(idx, 2, Transport[idx][trName], mysql, 35);
		Transport[idx][trPrice] = cache_get_row_int(idx, 3, mysql);
		Transport[idx][trTank] = cache_get_row_int(idx, 4, mysql);
		Transport[idx][trConsumption] = cache_get_row_int(idx, 5, mysql);
		Transport[idx][trClass] = cache_get_row_int(idx, 6, mysql);
		Transport[idx][trFuelable] = cache_get_row_int(idx, 7, mysql);
		Transport[idx][trSellable] = cache_get_row_int(idx, 8, mysql);
	}
	cache_delete(result, mysql);
	return true;
}
stock LoadBiz()
{
    new Cache:result = mysql_query(mysql, "SELECT * FROM `business`");
	OWNABLEBIZES = cache_get_row_count(mysql);
	for(new i; i < OWNABLEBIZES; i++)
	{
		BizInfo[i][bID] = cache_get_row_int(i, 0, mysql);
		BizInfo[i][bState] = cache_get_row_int(i, 1, mysql);
		cache_get_row(i, 2, BizInfo[i][bName], mysql, 64);
	 	cache_get_row(i, 3, BizInfo[i][bOwner], mysql, 24);
		BizInfo[i][bEnter_X] = cache_get_row_float(i, 4, mysql);
		BizInfo[i][bEnter_Y] = cache_get_row_float(i, 5, mysql);
	 	BizInfo[i][bEnter_Z] = cache_get_row_float(i, 6, mysql);
	 	BizInfo[i][bEnter_R] = cache_get_row_float(i, 7, mysql);
	 	BizInfo[i][bCost] = cache_get_row_int(i, 8, mysql);
	 	BizInfo[i][bLock] = cache_get_row_int(i, 9, mysql);
	 	BizInfo[i][bMoney] = cache_get_row_int(i, 10, mysql);
	 	BizInfo[i][bEnterPrice] = cache_get_row_int(i, 11, mysql);
		BizInfo[i][bProducts] = cache_get_row_int(i, 12, mysql);
	 	BizInfo[i][bProdPrice] = cache_get_row_int(i, 13, mysql);
	 	BizInfo[i][bKrasher] = cache_get_row_int(i, 14, mysql);
	 	BizInfo[i][bBint] = cache_get_row_int(i, 15, mysql);
	 	
	 	new
	 	    improve[15];
	 	    
		cache_get_row(i, 16, improve, mysql);
		sscanf(improve, "p<|>iii", BizInfo[i][bImprove][0], BizInfo[i][bImprove][1], BizInfo[i][bImprove][2]);

	 	BizInfo[i][bProductsOrder] = cache_get_row_int(i, 17, mysql);
	 	
	 	BizInfo[i][bDays] = cache_get_row_int(i, 18, mysql);
	 	BizInfo[i][bSeal] = cache_get_row_int(i, 19, mysql);
	 	
		BusinessArea[i] = CreateDynamicSphere(BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z], 2.0, 0, 0, -1);
		CreateDynamicPickup(1318, 1, BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z]);

		BusinessText[i] = CreateDynamic3DTextLabel("_",COLOR_WHITE,BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z]+1.0,20.0);
		
		if(BizInfo[i][bProductsOrder] > 0)
		{
		    BizInfo[i][bProducts] = BizInfo[i][bProducts] + BizInfo[i][bProductsOrder];
		    BizInfo[i][bProductsOrder] = 0;
		}
		
		UpdateBiz(i,1);
		BusinessEstate(i);

		if(BizInfo[i][bSeal])
		{
		    new btime;
			btime = RandomEx(7200000, 79200000);
		    BizInfo[i][bSellTimer] = SetTimerEx("@__BizSell",btime, false, "i", i);
		    printf("[SELLBIZ] ID: %d , TIME: %s, MS %d", i, ConvertMsToTime(btime), btime);
		}
		
		new icon = 0;
		
		switch(BizInfo[i][bState])
		{
			case 1: icon = 56;
			case 2: icon = 48;
			case 3: icon = 50;
			case 4: icon = 10;
			case 5: icon = 29;
			case 6: icon = 14;
			case 7: icon = 45;
			case 12: icon = 6;
			case 13: icon = 23;
			case 15: icon = 53;
			case 16: icon = 21;
		}
		
		if(icon != 0)
			CreateDynamicMapIcon(BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z], icon, 0, -1, -1, -1, 300.0);
	}
	cache_delete(result, mysql);
	return true;
}
stock SaveBiz(bizid)
{


	totalstring[0] = 0;
	format(totalstring, sizeof(totalstring), "UPDATE `business` SET \
	`State` = '%d', `Name` = '%s', `Owner` = '%s', `Enter_X` = '%f', `Enter_Y` = '%f', `Enter_Z` = '%f', `Enter_R` = '%f', \
	`Cost` = '%d', `Lock` = '%d', `Money` = '%d', `EnterPrice` = '%d', `Products` = '%d', \
	`ProdPrice` = '%d', `Krasher`='%d',",
	BizInfo[bizid][bState],
	BizInfo[bizid][bName],
	BizInfo[bizid][bOwner],
 	BizInfo[bizid][bEnter_X],
	BizInfo[bizid][bEnter_Y],
	BizInfo[bizid][bEnter_Z],
	BizInfo[bizid][bEnter_R],
	BizInfo[bizid][bCost],
	BizInfo[bizid][bLock],
	BizInfo[bizid][bMoney],
	BizInfo[bizid][bEnterPrice],
	BizInfo[bizid][bProducts],
	BizInfo[bizid][bProdPrice],
	BizInfo[bizid][bKrasher]);

	new
	    save_improve[60];

	for(new i; i < 3; i++)
	{
		if(!i)
			format(save_improve, sizeof save_improve, "%d", BizInfo[bizid][bImprove][i]);

		else
			format(save_improve, sizeof save_improve, "%s|%d", save_improve, BizInfo[bizid][bImprove][i]);
	}

	format(totalstring, sizeof(totalstring), "%s `Bint` = '%d', `Improve` = '%s', `Order` = '%d', `Days` = '%d', `Seal` = '%d' WHERE `ID` = '%i'",
	totalstring,
	BizInfo[bizid][bBint],
	save_improve,
	BizInfo[bizid][bProductsOrder],
	BizInfo[bizid][bDays],
	BizInfo[bizid][bSeal],
	bizid + 1);
	
	if(strlen(totalstring) >= 1024) printf("При сохранении бизнеса №%i произошла ошибка!", bizid);
	if(!EXITSAVEMODE)mysql_tquery(mysql, totalstring); else mysql_query(mysql, totalstring, false);
	return true;
}
stock SaveBizes()
{
    for (new i;i < OWNABLEBIZES;i ++) SaveBiz(i);
	return true;
}
forward LoadBints();
public LoadBints()
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows)
		return print("Интерьеры не найдены!");

	for(new i; i < MAX_BINTS; i++)
	{
		BizInts[i][bintID] = cache_get_field_content_int(i, "ID");
		BizInts[i][bintInterior] = cache_get_field_content_int(i, "Interior");
		BizInts[i][bintX] = cache_get_field_content_float(i, "X");
		BizInts[i][bintY] = cache_get_field_content_float(i, "Y");
		BizInts[i][bintZ] = cache_get_field_content_float(i, "Z");
		BizInts[i][bintR] = cache_get_field_content_float(i, "R");
		BizInts[i][bintXB] = cache_get_field_content_float(i, "XB");
		BizInts[i][bintYB] = cache_get_field_content_float(i, "YB");
		BizInts[i][bintZB] = cache_get_field_content_float(i, "ZB");
		cache_get_field_content(i, "Name", BizInts[i][bintName], mysql, 32);
		BintExitArea[i] = CreateDynamicSphere(BizInts[i][bintX], BizInts[i][bintY], BizInts[i][bintZ],1.0);
		CreateDynamicPickup(1318, 1, BizInts[i][bintX], BizInts[i][bintY], BizInts[i][bintZ]);
		BintBuyArea[i] = CreateDynamicSphere(BizInts[i][bintXB], BizInts[i][bintYB], BizInts[i][bintZB],1.0);
		if(BizInts[i][bintID] == 12)
		    CreateDynamicPickup(1275, 1, BizInts[i][bintXB], BizInts[i][bintYB], BizInts[i][bintZB]);
		else
			CreateDynamicPickup(1239, 1, BizInts[i][bintXB], BizInts[i][bintYB], BizInts[i][bintZB]);
	}
	return true;
}
forward LoadFamily();
public LoadFamily()
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows)
		return print("Семьи не найдены!");

    family_count = rows;
    
	for(new i; i < rows; i++)
	{
	    gFamily[i][fID] = cache_get_field_content_int(i, "ID");
	    cache_get_field_content(i, "Name", gFamily[i][fName], mysql, 43);
	    cache_get_field_content(i, "Owner", gFamily[i][fOwner], mysql, 24);
	    cache_get_field_content(i, "Date", gFamily[i][fDate], mysql, 16);
	    gFamily[i][fNation] = cache_get_field_content_int(i, "Nation");
	    gFamily[i][fColor] = cache_get_field_content_int(i, "Color");
	    gFamily[i][fMembers] = cache_get_field_content_int(i, "Members");
	    cache_get_field_content(i, "SubOwner", gFamily[i][fSubOwner], mysql, 24);
	    gFamily[i][fPromo] = cache_get_field_content_int(i, "Promo");
	}
	return true;
}
forward LoadPromo();
public LoadPromo()
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows)
		return print("Промокоды не найдены!");


	for(new i; i < rows; i++)
	{
	    gPromo[i][pcID] = cache_get_field_content_int(i, "pcID");
	    cache_get_field_content(i, "pcName", gPromo[i][pcName], mysql, 32);
	    gPromo[i][pcOwnerID] = cache_get_field_content_int(i, "pcOwnerID");
	    gPromo[i][pcUsed] = cache_get_field_content_int(i, "pcUsed");
	    gPromo[i][pcBank] = cache_get_field_content_int(i, "pcBank");

	 	new
	 	    improve[30];

		cache_get_field_content(i, "pcSettings", improve, mysql, 24);
		sscanf(improve, "p<|>iiii", gPromo[i][pcSettings][0], gPromo[i][pcSettings][1], gPromo[i][pcSettings][2], gPromo[i][pcSettings][3]);
		
		gPromo[i][pcFOwnerID] = cache_get_field_content_int(i, "pcFOwnerID");
	}
	return true;
}
forward LoadFilling();
public LoadFilling()
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows)
		return print("Заправки не найдены!");

	for(new i; i < MAX_FILLING; i++)
	{
	    gFillings[i][fillingID] = cache_get_field_content_int(i, "ID");
		gFillings[i][fillingOwnerID] = cache_get_field_content_int(i, "OwnerID");
		cache_get_field_content(i, "Owner", gFillings[i][fillingOwner], mysql, MAX_PLAYER_NAME);
		gFillings[i][fillingPrice] = cache_get_field_content_int(i, "Price");
		gFillings[i][fillingDay] = cache_get_field_content_int(i, "Day");
		gFillings[i][fillingBank] = cache_get_field_content_int(i, "Bank");
		gFillings[i][fillingWorking] = cache_get_field_content_int(i, "Working");
		gFillings[i][fillingFuelPrice] = cache_get_field_content_int(i, "FuelPrice");
		gFillings[i][fillingFuel] = cache_get_field_content_int(i, "Fuel");
		gFillings[i][fillingTanks] = cache_get_field_content_int(i, "Tanks");
		gFillings[i][fillingFuelOrder] = cache_get_field_content_int(i, "FuelOrder");
		gFillings[i][fillingSeal] = cache_get_field_content_int(i, "Seal");

  		for ( new fp; fp < 4; fp++ )
		{
			if(gFuelPumps[i][fp][0] == 0.0) break;
			gFuelPumpObjects[i][fp] = CreateDynamicObject(1676, gFuelPumps[i][fp][0], gFuelPumps[i][fp][1], gFuelPumps[i][fp][2]+1.5, gFuelPumps[i][fp][3], gFuelPumps[i][fp][4], gFuelPumps[i][fp][5]+90.0);
		}
		gFillingText[i] = CreateDynamic3DTextLabel("_", COLOR_WHITE, gFillingBuy[i][0], gFillingBuy[i][1], gFillingBuy[i][2], 20.0);
		CreateDynamicMapIcon(gFillingBuy[i][0], gFillingBuy[i][1], gFillingBuy[i][2], 47, 0, -1, -1, -1, 300.0);
		gFillingBuyArea[i] = CreateDynamicSphere(gFillingBuy[i][0], gFillingBuy[i][1], gFillingBuy[i][2], 3.0);
		
		if(gFillings[i][fillingFuelOrder] > 0)
		{
		    gFillings[i][fillingFuel] = gFillings[i][fillingFuel] + gFillings[i][fillingFuelOrder];
		    gFillings[i][fillingFuelOrder] = 0;
		}

		UpdateFillingText(i);
		FillingEstate(i);

		if(gFillings[i][fillingSeal])
		{
		    new btime;
			btime = RandomEx(7200000, 79200000);
		    gFillings[i][fillingSellTimer] = SetTimerEx("@__FillSell",btime, false, "i", i);
		}
	}
	return printf("Filliang loaded");
}
stock SaveFilling(fillingid)
{
	new string[750];
	format(string, sizeof string, "UPDATE `fillings` SET `OwnerID` = '%d', `Owner` = '%s', `Price` = '%d', `Day` = '%d', `Bank` = '%d', `Working` = '%d', `FuelPrice` = '%d', `Fuel` = '%d', `Tanks` = '%d', `Seal` = '%d' WHERE `ID` = '%i'",
	gFillings[fillingid][fillingOwnerID],
	gFillings[fillingid][fillingOwner],
	gFillings[fillingid][fillingPrice],
	gFillings[fillingid][fillingDay],
	gFillings[fillingid][fillingBank],
	gFillings[fillingid][fillingWorking],
	gFillings[fillingid][fillingFuelPrice],
	gFillings[fillingid][fillingFuel],
	gFillings[fillingid][fillingTanks],
	gFillings[fillingid][fillingSeal],
	fillingid + 1);

	if(strlen(string) >= 750)
		printf("При сохранении заправки №%i произошла ошибка!", fillingid);
		
	if(!EXITSAVEMODE)
		mysql_tquery(mysql, string);
		
	else mysql_query(mysql, string, false);
	return true;
}
stock UpdateFillingText(id)
{
	new text_business[450];

	if(!GetString(gFillings[id][fillingOwner], "The State"))
		format(text_business, sizeof text_business, "{FFFFFF}Автозаправочная станция\n\nНомер АЗС: {1E90FF}%i\n{FFFFFF}Владелец: {1E90FF}%s\n{FFFFFF}Стоимость: {32CD32}%i$\n{FFFFFF}Цена за 1 литр: {32CD32}%i$\n{EDFFCC}Заправиться: {FFFFFF}/fill\n{EDFFCC}Купить канистру: {FFFFFF}/buyfuel", gFillings[id][fillingID], gFillings[id][fillingOwner], gFillings[id][fillingPrice], gFillings[id][fillingFuelPrice]);

	else
     	format(text_business, sizeof text_business, "{FFFFFF}Номер АЗС: {1E90FF}%i\n{FFFFFF}Стоимость: {32CD32}%d$\n{FFFFFF}Цена за 1 литр: {32CD32}%i$\n{EDFFCC}Заправиться: {FFFFFF}/fill\n{EDFFCC}Купить канистру: {FFFFFF}/buyfuel\n\n{FFFFFF}Эта автозаправочная станция продается ({FFEE8F}/buyfilling{FFFFFF})", gFillings[id][fillingID], gFillings[id][fillingPrice], gFillings[id][fillingFuelPrice]);

	UpdateDynamic3DTextLabelText(gFillingText[id], -1, text_business);
	return true;
}
stock LoadOwnableCars()
{
	new Cache:result = mysql_query(mysql, "SELECT * FROM `cars`");
	OWNABLECARS = cache_get_row_count(mysql);
	for(new idx = 0;idx < OWNABLECARS; idx++)
	{
		CarInfo[idx][cID] = cache_get_row_int(idx, 0, mysql);
		CarInfo[idx][cOwnerID] = cache_get_row_int(idx, 1, mysql);
		CarInfo[idx][cModelID] = cache_get_row_int(idx, 2, mysql);
		CarInfo[idx][cColor_1] = cache_get_row_int(idx, 3, mysql);
		CarInfo[idx][cColor_2] = cache_get_row_int(idx, 4, mysql);
		cache_get_row(idx, 5, CarInfo[idx][cNumber], mysql, 12);
		CarInfo[idx][cFuel] = cache_get_row_float(idx, 6, mysql);
		CarInfo[idx][cHealth] = cache_get_row_float(idx, 7, mysql);
		CarInfo[idx][cMilage] = cache_get_row_float(idx, 8, mysql);
		cache_get_row(idx, 9, CarInfo[idx][cDate], mysql, 20);

		new
		    tuning[80];
		    
		cache_get_row(idx, 10, tuning, mysql, 100);
		sscanf(tuning, "p<|>iiiiiiiiiiiiii", CarInfo[idx][cTuning][0], CarInfo[idx][cTuning][1], CarInfo[idx][cTuning][2], CarInfo[idx][cTuning][3], CarInfo[idx][cTuning][4],
											 CarInfo[idx][cTuning][5], CarInfo[idx][cTuning][6], CarInfo[idx][cTuning][7], CarInfo[idx][cTuning][8], CarInfo[idx][cTuning][9],
											 CarInfo[idx][cTuning][10], CarInfo[idx][cTuning][11], CarInfo[idx][cTuning][12], CarInfo[idx][cTuning][13]);

        CarInfo[idx][cPaintJob] = cache_get_row_int(idx, 11, mysql);
        CarInfo[idx][cSignal] = cache_get_row_int(idx, 12, mysql);
	}
	cache_delete(result, mysql);
	return true;
}
stock SaveOwnableCar(playerid, carid)
{
    for(new i; i < sizeof CarInfo; i++)
	{
 		if(CarInfo[i][cVehID] != carid)
		 	continue;
 		
		new
			frmt_save_car[1200],
			tuning[80];

		for(new tn; tn < 14; tn++)
		{
			if(!tn) format(tuning, sizeof tuning, "%d", CarInfo[i][cTuning][tn]);
			else format(tuning, sizeof tuning, "%s|%d", tuning, CarInfo[i][cTuning][tn]);
		}
		
		format(frmt_save_car, sizeof frmt_save_car, "UPDATE `cars` SET `cFuel` = '%.2f', `cMilage` = '%.2f', `cColor_1` = '%d', `cColor_2` = '%d', `cPaintJob` = '%d', `cTuning` = '%s', `cSignal` = '%d' WHERE `cOwnerID` = '%d'", CarInfo[i][cFuel], CarInfo[i][cMilage], CarInfo[i][cColor_1], CarInfo[i][cColor_2], CarInfo[i][cPaintJob], tuning, CarInfo[i][cSignal], PI[playerid][pID]);

		mysql_tquery(mysql, frmt_save_car);
		break;
	}
}



stock SaveOwnableCars()
{
	for (new i = 0;i < OWNABLECARS;i ++) SaveOwnableCar(i);
	return true;
}
//==============================================================================
forward LoadProduct();
public LoadProduct()
{
	new rows, fields;
	cache_get_data(rows, fields);
	
	if(!rows) print("Products in the database is not found!");
	else
	{
		for(new i = 1; i < rows + 1; i++)
		{
	   		ProductInfo[i][idxx] = cache_get_field_content_int(i-1, "id");
		    cache_get_field_content(i-1, "name", ProductInfo[i][pName], mysql, MAX_PLAYER_NAME);
		    ProductInfo[i][pPrice] = cache_get_field_content_int(i-1, "price");
		    ProductInfo[i][pTill] = cache_get_field_content_int(i-1, "till");
		    ProductInfo[i][pBizid] = cache_get_field_content_int(i-1, "biz");
		    ProductInfo[i][pStatus] = cache_get_field_content_int(i-1, "status");
			TOTALPRODUCT++;
		}
	}
	printf("LoadProduct' - All %d load", TOTALPRODUCT);
	return true;
}
//==============================================================================
forward LoadOrgs();
public LoadOrgs()
{
	new rows, fields;
	cache_get_data(rows, fields);

	new
	    skins_man[70], skins_women[70], cars_rank[70];
	
	if(!rows)
		return print("Организации не найдены!");

	for(new i; i < MAX_FRACTIONS; i++)
	{
		OrgInfo[i][oID] = cache_get_field_content_int(i, "id");
		OrgInfo[i][oFraction] = cache_get_field_content_int(i, "fraction");
		cache_get_field_content(i, "skins_men", skins_man, mysql, 43);
		sscanf(skins_man, "p<|>iiiiiiiiiii", OrgInfo[i][oMSkins][0], OrgInfo[i][oMSkins][1], OrgInfo[i][oMSkins][2], OrgInfo[i][oMSkins][3], OrgInfo[i][oMSkins][4], OrgInfo[i][oMSkins][5], OrgInfo[i][oMSkins][6],
										OrgInfo[i][oMSkins][7], OrgInfo[i][oMSkins][8], OrgInfo[i][oMSkins][9], OrgInfo[i][oMSkins][10]);
		
		cache_get_field_content(i, "skins_women", skins_women, mysql, 43);
		sscanf(skins_women, "p<|>iiiiiiiiiii", OrgInfo[i][oWSkins][0], OrgInfo[i][oWSkins][1], OrgInfo[i][oWSkins][2], OrgInfo[i][oWSkins][3], OrgInfo[i][oWSkins][4], OrgInfo[i][oWSkins][5], OrgInfo[i][oWSkins][6],
										OrgInfo[i][oWSkins][7], OrgInfo[i][oWSkins][8], OrgInfo[i][oWSkins][9], OrgInfo[i][oWSkins][10]);

		cache_get_field_content(i, "cars_rank", cars_rank, mysql, 32);
		sscanf(cars_rank, "p<|>iiiiiiiiiii", OrgInfo[i][oCarRanks][0], OrgInfo[i][oCarRanks][1], OrgInfo[i][oCarRanks][2], OrgInfo[i][oCarRanks][3], OrgInfo[i][oCarRanks][4], OrgInfo[i][oCarRanks][5], OrgInfo[i][oCarRanks][6],
										OrgInfo[i][oCarRanks][7], OrgInfo[i][oCarRanks][8], OrgInfo[i][oCarRanks][9], OrgInfo[i][oCarRanks][10]);

		OrgInfo[i][oMoney] = cache_get_field_content_int(i, "money");
		switch(OrgInfo[i][oFraction])
		{
			case 1:
			{
				//============================== Больница ЛС ==============================
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][0], 416, 1097.7522, -1328.8531, 13.3763, 0.0422, 3, 1, 600);
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][0], 416, 1110.8314, -1328.8463, 13.3754, 0.0508, 3, 1, 600);
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][0], 416, 1124.1443, -1328.6089, 13.3309, 0.0200, 3, 1, 600);
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][2], 560, 1136.0798, -1335.8942, 13.3634, 270.5429, 3, 1, 600);
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][1], 426, 1136.4796, -1339.8572, 13.4324, 270.2947, 3, 68, 600);
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][1], 426, 1136.4607, -1343.6299, 13.4721, 269.0707, 3, 16, 600);
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][0], 416, 1177.9944, -1308.5768, 13.9590, 270.2338, 3, 1, 600);
				CreateTeamVehicle(1, 1, OrgInfo[i][oCarRanks][0], 416, 1179.6670, -1338.8828, 13.8822, 269.6495, 3, 1, 600);
				//============================== Больница СФ ==============================
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][1], 426, -2571.9441, 632.6732, 14.1653, 270.5573, 144, 106, 600);
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][1], 426, -2571.9463, 627.4703, 14.1578, 270.6414, 144, 76, 600);
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][2], 560, -2571.9912, 622.3321, 14.1234, 270.1230, 144, 104, 600);
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][0], 416, -2668.4175, 608.0135, 14.5051, 179.4475, 144, 1, 600);
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][0], 416, -2662.4185, 607.9530, 14.5276, 180.0801, 144, 1, 600);
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][0], 416, -2656.4380, 607.9570, 14.5276, 180.0321, 144, 1, 600);
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][0], 416, -2650.3955, 607.9932, 14.5421, 180.3327, 144, 1, 600);
				CreateTeamVehicle(1, 2, OrgInfo[i][oCarRanks][0], 416, -2644.3362, 607.9553, 14.5415, 179.3803, 144, 1, 600);
				//============================== Больница ЛВ ==============================
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][1], 426, 1620.2692, 1850.2413, 10.5468, 180.0795, 7, 1, 600);
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][1], 426, 1616.0072, 1850.2612, 10.5448, 179.9999, 7, 1, 600);
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][2], 560, 1590.5623, 1850.7194, 10.4741, 179.9631, 7, 45, 600);
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][0], 416, 1593.6487, 1840.2648, 10.9343, 359.8997, 7, 1, 600);
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][0], 416, 1597.9453, 1840.3269, 10.8860, 0.0012, 7, 1, 600);
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][0], 416, 1602.1809, 1840.3241, 10.9482, 0.1132, 7, 1, 600);
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][0], 416, 1606.2830, 1840.2627, 10.8843, 0.1659, 7, 1, 600);
				CreateTeamVehicle(1, 3, OrgInfo[i][oCarRanks][0], 416, 1610.6616, 1840.2593, 10.9469, 0.0495, 7, 1, 600);

				new
				    frmt_balance[128];
				    
				format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[i][oMoney]);
				
				gFractionMoney[i] = CreateDynamic3DTextLabel(frmt_balance, 0xFFFFFFFF, 694.6301, 1538.5500, 1309.7780, 3.0);
			}
			case 2: //Ballas
			{
				CreateTeamVehicle(2, 0, OrgInfo[i][oCarRanks][0], 566, 2013.8956, -1141.1002, 24.7316, 270.0000, 22, 22, 600);
				CreateTeamVehicle(2, 0, OrgInfo[i][oCarRanks][1], 492, 2015.6178, -1130.6322, 24.6898, 270.0000, 22, 22, 600);
				CreateTeamVehicle(2, 0, OrgInfo[i][oCarRanks][1], 492, 2007.3373, -1130.5071, 24.9282, 270.0000, 22, 22, 600);
				CreateTeamVehicle(2, 0, OrgInfo[i][oCarRanks][2], 482, 1997.6851, -1140.8280, 25.5273, 90.0000, 22, 22, 600);
				CreateTeamVehicle(2, 0, OrgInfo[i][oCarRanks][2], 482, 1988.2654, -1140.6548, 25.7544, 90.0000, 22, 22, 600);
			}
			case 3: //Grove
			{
				CreateTeamVehicle(3, 0, OrgInfo[i][oCarRanks][0], 482, 2469.9019, -1669.4745, 13.4058, 8.7210, 16, 16, 600);
				CreateTeamVehicle(3, 0, OrgInfo[i][oCarRanks][0], 482, 2471.8049, -1675.8572, 13.3856, 27.1554, 16, 16, 600);
				CreateTeamVehicle(3, 0, OrgInfo[i][oCarRanks][1], 492, 2486.3628, -1682.7386, 12.9908, 90.1258, 16, 16, 600);
				CreateTeamVehicle(3, 0, OrgInfo[i][oCarRanks][1], 492, 2492.9758, -1682.8003, 13.0060, 88.8425, 16, 16, 600);
				CreateTeamVehicle(3, 0, OrgInfo[i][oCarRanks][2], 567, 2504.2959, -1678.8505, 13.1938, 134.1668, 16, 16, 600);
			}
			case 4: //Aztec
			{
				CreateTeamVehicle(4, 0, OrgInfo[i][oCarRanks][0], 536, 2171.9185, -1792.2659, 13.0385, 270.6164, 135, 135, 600);
				CreateTeamVehicle(4, 0, OrgInfo[i][oCarRanks][1], 492, 2165.2080, -1808.0054, 13.0971, 317.5882, 135, 135, 600);
				CreateTeamVehicle(4, 0, OrgInfo[i][oCarRanks][1], 492, 2176.2158, -1808.1150, 13.0963, 314.0852, 135, 135, 600);
				CreateTeamVehicle(4, 0, OrgInfo[i][oCarRanks][2], 482, 2189.1768, -1805.7242, 13.4720, 359.9904, 135, 135, 600);
				CreateTeamVehicle(4, 0, OrgInfo[i][oCarRanks][2], 482, 2189.1077, -1797.5648, 13.4818, 0.2551, 135, 135, 600);
			}
			case 5: //Vagos
			{
				CreateTeamVehicle(5, 0, OrgInfo[i][oCarRanks][0], 492, 2771.9521, -1606.7976, 10.6445, 269.1933, 6, 6, 600);
				CreateTeamVehicle(5, 0, OrgInfo[i][oCarRanks][0], 492, 2771.9080, -1615.1504, 10.6321, 272.2517, 6, 6, 600);
				CreateTeamVehicle(5, 0, OrgInfo[i][oCarRanks][1], 482, 2773.7627, -1625.2306, 10.9750, 268.8236, 6, 6, 600);
				CreateTeamVehicle(5, 0, OrgInfo[i][oCarRanks][1], 482, 2782.0183, -1625.4648, 10.9828, 267.9059, 6, 6, 600);
				CreateTeamVehicle(5, 0, OrgInfo[i][oCarRanks][2], 475, 2795.7888, -1608.8563, 10.6804, 336.4459, 6, 6, 600);
			}
			case 6: //Rifa
			{
				CreateTeamVehicle(6, 0, OrgInfo[i][oCarRanks][0], 492, 2719.1101, -1935.8265, 13.1353, 358.1260, 79, 79, 600);
				CreateTeamVehicle(6, 0, OrgInfo[i][oCarRanks][0], 492, 2718.9614, -1943.9688, 13.1338, 0.7014, 79, 79, 600);
				CreateTeamVehicle(6, 0, OrgInfo[i][oCarRanks][1], 566, 2709.1443, -1927.1758, 13.1462, 90.2566, 79, 79, 600);
				CreateTeamVehicle(6, 0, OrgInfo[i][oCarRanks][2], 482, 2718.7935, -1961.0070, 13.4568, 359.6553, 79, 79, 600);
				CreateTeamVehicle(6, 0, OrgInfo[i][oCarRanks][2], 482, 2731.7725, -1970.0742, 13.6016, 89.8337, 79, 79, 600);
			}
			case 7: //МО
			{
				//============================== Армия ЛВ ==============================
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][6], 487, 285.4738,2053.1509,17.8315,269.3565, 131, 131, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][6], 548, 307.9641,2053.0925,19.4146,178.4868, 131, 131, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][1], 433, 276.8645, 2029.9097, 18.0106, 270.8085, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][1], 433, 276.8519, 2024.1102, 18.0106, 268.8565, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][1], 433, 276.6346, 2017.6772, 18.0106, 270.8864, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][2], 470, 281.0517, 2000.9283, 17.5753, 177.6637, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][2], 470, 272.4702, 2001.1406, 17.5750, 180.7897, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][2], 470, 273.0494, 1978.3339, 17.5924, 359.7139, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][2], 470, 281.4377, 1978.2443, 17.5745, 358.5964, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][1], 433, 277.5246, 1961.7705, 18.0106, 268.5392, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][1], 433, 277.5040, 1955.7722, 18.0106, 270.2763, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][4], 431, 276.8052, 1949.5155, 17.6634, 269.8781, 131, 131, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][3], 500, 220.4208, 1920.8452, 17.6918, 180.4941, 131, 99, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][3], 500, 211.3308, 1920.7800, 17.6880, 181.2172, 131, 41, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][2], 470, 202.4676, 1920.6276, 17.6133, 180.0001, 44, 1, 1800);
				CreateTeamVehicle(7, 1, OrgInfo[i][oCarRanks][2], 470, 193.3046, 1920.6039, 17.6133, 180.0001, 44, 1, 1800);
			    //============================== Армия СФ ==============================
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][1], 433, -1706.5677, 274.2743, 7.5224, 0.9397, 28, 36, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][1], 433, -1700.5396, 274.3418, 7.5454, 1.4115, 72, 120, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][1], 433, -1694.6882, 274.4089, 7.5164, 0.9961, 99, 14, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][2], 470, -1676.7986, 274.1520, 7.1534, 269.3436, 18, 80, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][2], 470, -1676.8109, 268.2158, 7.1533, 270.5988, 47, 63, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][2], 470, -1654.1434, 267.8299, 7.1534, 89.8242, 98, 72, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][2], 470, -1654.2389, 273.8024, 7.1534, 90.3365, 65, 30, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][3], 500, -1654.2666, 279.9423, 7.2646, 91.0932, 131, 115, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][1], 433, -1636.2913, 274.8731, 7.5068, 2.2442, 17, 25, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][1], 433, -1630.7701, 275.0072, 7.5080, 1.8325, 112, 92, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][4], 431, -1625.1145, 274.2399, 7.1875, 0.3264, 131, 131, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][1], 433, -1530.0439, 361.8972, 7.5584, 89.9743, 104, 124, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][1], 433, -1530.0361, 368.6253, 7.5584, 90.3420, 104, 75, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][2], 470, -1528.4674, 375.4440, 7.1212, 90.3601, 65, 97, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][3], 500, -1528.1091, 382.2817, 7.2323, 91.3382, 131, 30, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][5], 487, -1419.9590, 495.5397, 18.3536, 90.2871, 131, 131, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][0], 548, -1305.6827, 501.4357, 19.8343, 45.4095, 44, 1, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][6], 595, -1441.0881, 509.6838, -0.0092, 88.5627, 131, 131, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][6], 595, -1441.6056, 505.3232, -0.1031, 90.5331, 131, 131, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][6], 595, -1446.6094, 497.0845, -0.1014, 90.0970, 131, 131, 1800);
				CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][6], 595, -1446.5038, 493.1247, -0.1567, 84.6986, 131, 131, 1800);
                CreateTeamVehicle(7, 2, OrgInfo[i][oCarRanks][0], 548, -1285.0011, 501.2231, 19.6778, 29.1697, 44, 1, 1800);


				gArmyWarehouseText[0] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 1);
				gArmyWarehouseText[1] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 2);

				new
				    frmt_balance[128];

				format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[i][oMoney]);

				gFractionMoney[i] = CreateDynamic3DTextLabel(frmt_balance, 0xFFFFFFFF, 854.4714, 118.9557, 1067.4170, 3.0);

			}
			case 8: //МВД
			{
			    //============================== LSPD ==============================
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1602.0122, -1696.1982, 5.5660, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1602.0122, -1700.2289, 5.5660, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1602.0122, -1704.1812, 5.5660, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1595.2972, -1710.7172, 5.5660, 0.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1591.5980, -1710.7172, 5.5660, 0.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1587.4695, -1710.7172, 5.5660, 0.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1583.5144, -1710.7172, 5.5660, 0.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1578.5865, -1710.7172, 5.5660, 0.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1574.5146, -1710.7172, 5.5660, 0.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][0], 596, 1570.1744, -1710.7172, 5.5660, 0.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][1], 523, 1546.6101, -1684.3074, 5.5660, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][1], 523, 1546.6101, -1680.1350, 5.5660, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][1], 523, 1546.6101, -1676.2479, 5.5660, 90.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][1], 523, 1546.6101, -1672.0221, 5.5660, 90.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][1], 523, 1546.6101, -1668.1606, 5.5660, 90.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][2], 599, 1538.7885, -1645.0391, 5.5660, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][2], 599, 1534.6599, -1645.0391, 5.5660, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][3], 560, 1602.1898, -1684.0667, 5.5660, 90.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][3], 560, 1602.1327, -1687.8364, 5.5660, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 1, OrgInfo[i][oCarRanks][4], 497, 1552.8477, -1610.5408, 14.0469, 90.0000, 0, 1, 600);
				//============================== SFPD ==============================
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1588.0726, 748.7473, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1584.0134, 748.7473, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1579.9343, 748.7473, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1573.4246, 742.7581, -5.5668, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1573.4246, 738.6208, -5.5668, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1573.4246, 734.5035, -5.5668, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1573.4246, 730.5933, -5.5668, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1573.4246, 726.5404, -5.5668, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1573.4246, 722.5157, -5.5668, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][5], 597, -1573.4246, 718.2444, -5.5668, 90.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][1], 523, -1600.1548, 693.7073, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][1], 523, -1604.1461, 693.7073, -5.5668, 180.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][1], 523, -1608.2200, 693.7073, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][1], 523, -1612.3450, 693.7073, -5.5668, 180.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][1], 523, -1616.6451, 693.7073, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][2], 599, -1639.5457, 686.3613, -5.5668, 270.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][2], 599, -1639.5457, 682.2259, -5.5668, 270.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][3], 560, -1596.3109, 749.5499, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][3], 560, -1600.4016, 749.5499, -5.5668, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 2, OrgInfo[i][oCarRanks][4], 497, -1679.8936, 705.5067, 30.7259, 47.0480, 0, 1, 600);
			    //============================== LVPD ==============================
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2282.3589, 2444.0313, 10.5063, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2277.7795, 2444.0313, 10.5063, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2273.4641, 2444.0313, 10.5063, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2269.0137, 2444.0313, 10.5063, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2260.4082, 2444.0313, 10.5063, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2256.0767, 2444.0313, 10.5063, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2251.9094, 2444.0313, 10.5063, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2251.7424, 2459.1509, 10.5063, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2256.1909, 2459.1509, 10.5063, 180.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][6], 598, 2260.3496, 2459.1509, 10.5063, 180.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][1], 523, 2273.2932, 2459.6533, 10.3454, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][1], 523, 2277.6816, 2459.6533, 10.3454, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][1], 523, 2282.1296, 2459.6533, 10.3454, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][1], 523, 2273.4500, 2476.8589, 10.3454, 180.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][1], 523, 2277.7747, 2476.8589, 10.3454, 180.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][2], 599, 2260.4802, 2477.1255, 10.9150, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][2], 599, 2256.1794, 2477.1255, 10.9150, 180.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][3], 560, 2290.8384, 2459.0513, 10.4306, 180.0000, 0, 1, 600);
			    CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][3], 560, 2290.8384, 2443.2405, 10.4306, 360.0000, 0, 1, 600);
				CreateTeamVehicle(8, 3, OrgInfo[i][oCarRanks][4], 497, 2310.5808, 2449.5376, 10.9516, 180.0000, 0, 1, 600);


				gPDWarehouseText[0] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 3);
				gPDWarehouseText[1] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 4);
                gPDWarehouseText[2] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 5);

				new
				    frmt_balance[128];

				format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[i][oMoney]);

				gFractionMoney[i] = CreateDynamic3DTextLabel(frmt_balance, 0xFFFFFFFF, 229.2159, 125.8560, 1010.7173, 3.0);
			}
			case 9: //Media
			{
			    //============================== Media ЛС ==============================
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1693.0895, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1696.9873, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1704.1243, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1700.5864, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1707.4498, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1710.8470, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1714.1748, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][0], 582, 1668.4730, -1717.5306, 15.5849, 88.9162, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][1], 426, 1671.4811, -1706.1108, 20.1890, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][1], 426, 1671.4811, -1702.1307, 20.1632, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][2], 560, 1671.4811, -1698.2073, 20.1376, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][2], 560, 1671.4811, -1694.4508, 20.1376, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 1, OrgInfo[i][oCarRanks][3], 488, 1671.4811, -1714.2863, 20.5733, 0.0000, 222, 1, 600);
				//============================== Media СФ ==============================
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1798.7307, 796.1849, 24.9006, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1798.7864, 790.9889, 24.8961, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1798.8295, 786.0040, 24.8978, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1798.8022, 781.1253, 24.8959, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1788.1827, 781.1415, 24.8988, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1788.2058, 786.0090, 24.8972, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1788.2263, 790.9981, 24.8999, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][0], 582, -1788.2566, 796.1954, 24.8993, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][1], 426, -1778.6500, 761.5013, 24.5389, 180.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][1], 426, -1773.5737, 761.5013, 24.5389, 180.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][2], 560, -1763.7388, 761.5013, 24.5389, 180.0000, 222, 1, 600);
				CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][2], 560, -1768.7281, 761.5013, 24.5389, 180.0000, 222, 1, 600);
			    CreateTeamVehicle(9, 2, OrgInfo[i][oCarRanks][3], 488, -1737.9757, 755.7883, 25.0600, 92.1408, 222, 1, 600);
				//============================== Media ЛВ ==============================
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2095.8489, 2422.4050, 10.8307, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2095.8489, 2416.5188, 10.8275, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2095.8489, 2410.5459, 10.8311, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2095.8489, 2404.7273, 10.8274, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2086.8491, 2422.5161, 10.8269, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2086.8491, 2416.5173, 10.8258, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2086.8491, 2410.6780, 10.8359, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][0], 582, 2086.8491, 2404.7642, 10.8363, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][1], 426, 2078.6450, 2422.4519, 10.5597, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][1], 426, 2078.6450, 2416.5291, 10.5554, 90.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][2], 560, 2068.4124, 2422.4275, 10.4754, 270.0000, 222, 1, 600);
				CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][2], 560, 2068.4124, 2416.5725, 10.4754, 270.0000, 222, 1, 600);
			    CreateTeamVehicle(9, 3, OrgInfo[i][oCarRanks][3], 488, 2092.6028, 2414.8845, 74.6545, 270.0000, 222, 1, 600);

				new
				    frmt_balance[128];

				format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[i][oMoney]);

				gFractionMoney[i] = CreateDynamic3DTextLabel(frmt_balance, 0xFFFFFFFF, 1740.1466, 159.9764, 1125.9989, 3.0);

			}
			case 10://Правительство
			{
			    //================================= АП =================================
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][0], 579, 1276.7080, -2034.7017, 58.8503, 89.1569, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][0], 579, 1276.7715, -2027.6829, 58.8253, 91.1145, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][1], 490, 1272.0842, -2009.8588, 59.0916, 179.7130, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][1], 490, 1254.9874, -2010.0641, 59.5735, 181.3885, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][2], 560, 1265.7498, -2010.1595, 58.9102, 180.7547, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][2], 560, 1261.2893, -2010.2319, 59.0390, 181.2695, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][3], 409, 1244.4893, -2020.3491, 59.6078, 179.7432, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][4], 426, 1254.2368, -2044.3376, 59.2880, 268.1147, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][4], 426, 1246.1953, -2044.1516, 59.5249, 268.3265, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][5], 487, 1154.0999, -2020.4874, 69.1943, 270.7653, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][5], 487, 1154.1542, -2054.3782, 69.1193, 270.4667, 1, 1, 600);
				
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][4], 426, 1276.9166, -2044.8992, 58.7850, 89.0737, 1, 1, 600);
				CreateTeamVehicle(10, 0, OrgInfo[i][oCarRanks][4], 426, 1277.5840, -2038.2931, 58.7502, 89.3874, 1, 1, 600);
			    //============================== МЭРИЯ ЛС ===============================
				CreateTeamVehicle(10, 1, OrgInfo[i][oCarRanks][6], 400, 1402.6210, -1807.9758, 13.5929, 359.8540, 1, 90, 600);
				CreateTeamVehicle(10, 1, OrgInfo[i][oCarRanks][0], 579, 1407.0085, -1807.6565, 13.4566, 359.3573, 1, 31, 600);
				CreateTeamVehicle(10, 1, OrgInfo[i][oCarRanks][7], 507, 1406.7629, -1783.8611, 13.2517, 89.3391, 1, 8, 600);
				CreateTeamVehicle(10, 1, OrgInfo[i][oCarRanks][7], 507, 1406.7386, -1774.0597, 13.3098, 89.6058, 1, 83, 600);
				CreateTeamVehicle(10, 1, OrgInfo[i][oCarRanks][2], 560, 1406.6398, -1778.6971, 13.1602, 89.7032, 1, 53, 600);
				//============================== МЭРИЯ СФ ===============================
				CreateTeamVehicle(10, 2, OrgInfo[i][oCarRanks][6], 400, -2731.0276, 387.6758, 4.4377, 180.1086, 1, 1, 600);
				CreateTeamVehicle(10, 2, OrgInfo[i][oCarRanks][0], 579, -2731.1987, 364.2547, 4.2583, 1.7560, 1, 42, 600);
				CreateTeamVehicle(10, 2, OrgInfo[i][oCarRanks][7], 507, -2735.4463, 364.1951, 4.1704, 0.2879, 1, 122, 600);
				CreateTeamVehicle(10, 2, OrgInfo[i][oCarRanks][7], 507, -2726.4934, 364.2609, 4.1712, 0.5132, 1, 31, 600);
				CreateTeamVehicle(10, 2, OrgInfo[i][oCarRanks][2], 560, -2737.1101, 387.8209, 4.0008, 179.5477, 1, 126, 600);
				//============================== МЭРИЯ ЛВ ===============================
				CreateTeamVehicle(10, 3, OrgInfo[i][oCarRanks][6], 400, 2529.5947, 2501.4883, 10.8908, 89.4842, 1, 1, 600);
				CreateTeamVehicle(10, 3, OrgInfo[i][oCarRanks][0], 579, 2529.7402, 2506.4907, 10.6693, 91.4400, 1, 1, 600);
				CreateTeamVehicle(10, 3, OrgInfo[i][oCarRanks][7], 507, 2529.5061, 2491.3921, 10.5835, 89.6805, 1, 1, 600);
				CreateTeamVehicle(10, 3, OrgInfo[i][oCarRanks][7], 507, 2529.5364, 2496.4277, 10.5829, 89.8456, 1, 1, 600);
				CreateTeamVehicle(10, 3, OrgInfo[i][oCarRanks][2], 560, 2512.6199, 2494.0469, 10.5143, 270.4176, 1, 1, 600);

				gHallWarehouseText[0] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 6);
				gHallWarehouseText[1] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 7);
                gHallWarehouseText[2] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 8);
                gHallWarehouseText[3] = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 9);
                
				new
				    frmt_balance[128];

				format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[i][oMoney]);

				gFractionMoney[i] = CreateDynamic3DTextLabel(frmt_balance, 0xFFFFFFFF, 1232.0487, -809.1720, 1084.1112, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 5, 1);
				gHallMoneyArea = CreateDynamicSphere(1232.0487, -809.1720, 1084.1112, 2.0, 1, 5);

			}
			case 11://fbi
			{
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][0], 487, -2527.8135, -676.0275, 150.3352, 115.1144, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][1], 482, -2505.5508, -602.1183, 132.8500, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][1], 482, -2501.7871, -602.1183, 132.8453, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][1], 482, -2498.1558, -602.1183, 132.8519, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2535.4019, -602.1183, 132.2129, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2531.6350, -602.1183, 132.2258, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2527.9016, -602.1183, 132.2129, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2524.1318, -602.1183, 132.2129, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2520.4805, -602.1183, 132.2381, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2516.5835, -602.1183, 132.2129, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2512.9729, -602.1183, 132.2139, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][2], 490, -2509.2285, -602.1183, 132.2133, 180.5287, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][3], 426, -2534.7512, -618.2865, 132.3073, 308.0986, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][3], 426, -2529.2097, -618.2584, 132.3206, 308.2877, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][3], 426, -2523.6340, -618.1050, 132.3097, 310.3197, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][4], 560, -2506.5747, -619.2625, 132.2703, 270.6716, 0, 0, 600);
				CreateTeamVehicle(11, 0, OrgInfo[i][oCarRanks][4], 560, -2498.2156, -619.2180, 132.2583, 270.2089, 0, 0, 600);

				gFBIWarehouseText = CreateDynamic3DTextLabel("_", COLOR_WHITE, 312.4241, -165.9406, 1000.3010, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 6, 10);

				new
				    frmt_balance[128];

				format(frmt_balance, sizeof frmt_balance, "На счету организации: {BD4D4D}%d$", OrgInfo[i][oMoney]);

				gFractionMoney[i] = CreateDynamic3DTextLabel(frmt_balance, 0xFFFFFFFF, -1588.3950, -1020.4984, 1362.9705, 3.0);

			}
			case 12://yakuza
			{
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][0], 579, 2603.3396, 1853.0939, 10.6694, 270.0000, 0, 0, 600);
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][0], 579, 2603.3396, 1846.6145, 10.6694, 270.0000, 0, 0, 600);
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][1], 507, 2603.3396, 1840.2623, 10.6694, 270.0000, 0, 0, 600);
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][1], 507, 2603.3396, 1833.8677, 10.6694, 270.0000, 0, 0, 600);
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][2], 562, 2603.3396, 1815.0775, 10.6694, 270.0000, 0, 0, 600);
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][3], 482, 2603.3396, 1808.5912, 10.6694, 270.0000, 0, 0, 600);
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][4], 409, 2630.3030, 1838.8987, 10.6694, 90.0000, 0, 0, 600);
				CreateTeamVehicle(12, 0, OrgInfo[i][oCarRanks][5], 506, 2631.3667, 1845.6760, 10.6694, 90.0000, 0, 0, 600);
			}
			case 13://lcn
			{
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][0], 429, 1494.2018, 2840.5005, 10.5508, 180.0000, 0, 0, 600);
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][1], 559, 1489.4165, 2840.5005, 10.5508, 180.0000, 0, 0, 600);
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][2], 426, 1484.7609, 2840.5005, 10.5508, 180.0000, 0, 0, 600);
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][2], 426, 1479.8907, 2840.5005, 10.5508, 180.0000, 0, 0, 600);
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][3], 579, 1475.0518, 2840.5005, 10.5508, 180.0000, 0, 0, 600);
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][3], 579, 1470.1737, 2840.5005, 10.5508, 180.0000, 0, 0, 600);
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][4], 482, 1460.4313, 2840.5005, 10.5508, 180.0000, 0, 0, 600);
				CreateTeamVehicle(13, 0, OrgInfo[i][oCarRanks][5], 409, 1471.2080, 2773.2439, 10.5508, 180.0000, 0, 0, 600);
			}
			case 14://columbia
			{
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][0], 551, 983.5095, 1746.3445, 8.5041, 90.0000, 0, 0, 600);
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][0], 551, 983.5095, 1742.4260, 8.5041, 90.0000, 0, 0, 600);
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][1], 579, 983.5095, 1724.0902, 8.5041, 90.0000, 0, 0, 600);
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][1], 579, 983.5095, 1720.2020, 8.5041, 90.0000, 0, 0, 600);
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][2], 560, 983.5095, 1730.1931, 8.5041, 90.0000, 0, 0, 600);
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][3], 415, 983.5095, 1735.5778, 8.5041, 90.0000, 0, 0, 600);
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][4], 409, 950.2933, 1752.6538, 8.5041, 180.0000, 0, 0, 600);
				CreateTeamVehicle(14, 0, OrgInfo[i][oCarRanks][5], 482, 953.2805, 1707.5095, 8.5041, 270.0000, 0, 0, 600);
			}
		}
	}
	return true;
}
forward LoadMayor();
public LoadMayor()
{
	new rows, fields;
	cache_get_data(rows, fields);
	
	if(!rows) print("Mayor in the database is not found!");
	else
	{
		new temp_info[256];
		
		Pick = cache_get_field_content_int(0, "pick");

		cache_get_field_content(0, "name", temp_info, mysql, 256);
		sscanf(temp_info, "p<,>s[32]s[32]s[32]s[32]s[32]s[32]s[32]s[32]s[32]", PickName[0], PickName[1], PickName[2], PickName[3], PickName[4], PickName[5], PickName[6], PickName[7], PickName[8]);

		cache_get_field_content(0, "votes", temp_info, mysql, 256);
		sscanf(temp_info, "p<,>a<i>[9]", PickVote);
	}
	printf("LoadMayor - SUCCECC");
	return true;
}
forward LoadDivision();
public LoadDivision()
{
	new rows, fields;
	cache_get_data(rows, fields);

	new
	    divisionranks[24];

	if(!rows)
		return print("Division not found!");

	for(new i; i < 5; i++)
	{
		cache_get_field_content(i, "name", gDivisionName[i], mysql, 10);
		cache_get_field_content(i, "guns", divisionranks, mysql, 25);
		sscanf(divisionranks, "p<|>iiiii", gDivisionGun[i][0], gDivisionGun[i][1], gDivisionGun[i][2], gDivisionGun[i][3], gDivisionGun[i][4]);
	}
	return 1;
}
forward LoadTags();
public LoadTags()
{
	new rows, fields;
	cache_get_data(rows, fields);


	if(!rows)
		return print("Дивизии не найдены!");

	for(new i; i < 5; i++)
	{
		cache_get_field_content(i, "name", gTagName[i], mysql, 10);
	}
	return 1;
}
forward LoadGZ();
public LoadGZ()
{
	new rows, fields;
	cache_get_data(rows, fields);
	for(new gz; gz < MAX_GANGZONE; gz++)
	{
	    GZMZ[gz][gID] = cache_get_field_content_int(gz, "id");
		GZMZ[gz][gCoords][0] = cache_get_field_content_float(gz, "Coords[0]");
	    GZMZ[gz][gCoords][1] = cache_get_field_content_float(gz, "Coords[1]");
	    GZMZ[gz][gCoords][2] = cache_get_field_content_float(gz, "Coords[2]");
	    GZMZ[gz][gCoords][3] = cache_get_field_content_float(gz, "Coords[3]");
	    GZMZ[gz][gGang] = cache_get_field_content_int(gz, "Gang");
		GZMZ[gz][gCreate] = GangZoneCreate(GZMZ[gz][gCoords][0],GZMZ[gz][gCoords][1],GZMZ[gz][gCoords][2],GZMZ[gz][gCoords][3]);
	}
	return print("Территории банд загружены!");
}
forward LoadGangs();
public LoadGangs()
{
	new rows, fields;
	cache_get_data(rows, fields);

	new
	    ranks[300];

	if(!rows)
		return print("Банды не найдены!");
		
    for(new g; g < 5; g++)
    {
    	cache_get_field_content(g, "ranks", ranks, mysql, 255);
		sscanf(ranks, "p<,>s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]",
					gFractionRankName[g+1][0], gFractionRankName[g+1][1], gFractionRankName[g+1][2], gFractionRankName[g+1][3],
					gFractionRankName[g+1][4], gFractionRankName[g+1][5], gFractionRankName[g+1][6], gFractionRankName[g+1][7],
					gFractionRankName[g+1][8], gFractionRankName[g+1][9]);
					
		gGangStorage[g][0] = cache_get_field_content_int(g, "gun");
		gGangStorage[g][1] = cache_get_field_content_int(g, "ammo");
		gGangStorage[g][2] = cache_get_field_content_int(g, "drugs");
		gGangStorage[g][3] = cache_get_field_content_int(g, "money");
		gGangStorageRank[g] = cache_get_field_content_int(g, "storagerank");
		gGangStorageStatus[g] = cache_get_field_content_int(g, "storagestatus");
    }
    UpdateTextGang();
    return true;
}
forward LoadMafia();
public LoadMafia()
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows) return print("Load Mafia not found");

    for(new i; i < 3; i++)
    {
		gMafiaStorage[i][0] = cache_get_field_content_int(i, "gun");
		gMafiaStorage[i][1] = cache_get_field_content_int(i, "ammo");
		gMafiaStorage[i][2] = cache_get_field_content_int(i, "drugs");
		gMafiaStorage[i][3] = cache_get_field_content_int(i, "money");
		gMafiaStorageRank[i] = cache_get_field_content_int(i, "storagerank");
		gMafiaStorageStatus[i] = cache_get_field_content_int(i, "storagestatus");
    }
   	UpdateTextMafia();
   	print("Load Mafia - TRUE");
    return true;
}
stock RandomMassive(massive[], size)
{
	for(new i; i < size; i ++)
	{
	    new rand = random(size), mass = massive[i];
	    massive[i] = massive[rand];
	   	massive[rand] = mass;
	}
}
stock LoadHouses()
{
	new Cache:result = mysql_query(mysql, "SELECT * FROM `houses`");
	OWNABLEHOUSES = cache_get_row_count(mysql);
	new improve[30], skins[30], guns[50];
	for (new i;i < OWNABLEHOUSES;i ++)
	{
		HouseInfo[i][hID] = cache_get_row_int(i, 0, mysql);
		HouseInfo[i][hEnter_X] = cache_get_row_float(i, 1, mysql);
		HouseInfo[i][hEnter_Y] = cache_get_row_float(i, 2, mysql);
		HouseInfo[i][hEnter_Z] = cache_get_row_float(i, 3, mysql);
		HouseInfo[i][hEnter_R] = cache_get_row_float(i, 4, mysql);
		HouseInfo[i][hExit_X] = cache_get_row_float(i, 5, mysql);
		HouseInfo[i][hExit_Y] = cache_get_row_float(i, 6, mysql);
		HouseInfo[i][hExit_Z] = cache_get_row_float(i, 7, mysql);
		HouseInfo[i][hPark_X] = cache_get_row_float(i, 8, mysql);
		HouseInfo[i][hPark_Y] = cache_get_row_float(i, 9, mysql);
		HouseInfo[i][hPark_Z] = cache_get_row_float(i, 10, mysql);
		HouseInfo[i][hPark_R] = cache_get_row_float(i, 11, mysql);
		cache_get_row(i, 12, HouseInfo[i][hOwner], mysql, 24);
		cache_get_row(i, 13, HRoomOwner[i][0], mysql, 24);
		cache_get_row(i, 14, HRoomOwner[i][1], mysql, 24);
		cache_get_row(i, 15, HRoomOwner[i][2], mysql, 24);
		HouseInfo[i][hLevel] = cache_get_row_int(i, 16, mysql);
		HouseInfo[i][hCost] = cache_get_row_int(i, 17, mysql);
		HouseInfo[i][hLock] = cache_get_row_int(i, 18, mysql);
		HouseInfo[i][hInt] = cache_get_row_int(i, 19, mysql);
		HouseInfo[i][hMoney] = cache_get_row_int(i, 20, mysql);
		HouseInfo[i][hDrugs] = cache_get_row_int(i, 21, mysql);
		HouseInfo[i][hMats] = cache_get_row_int(i, 22, mysql);
		cache_get_row(i, 23, skins, mysql);
		sscanf(skins, "p<|>iiii", HouseInfo[i][hSkin][0], HouseInfo[i][hSkin][1], HouseInfo[i][hSkin][2], HouseInfo[i][hSkin][3]);
		
		HouseInfo[i][hDays] = cache_get_row_int(i, 24, mysql);
		cache_get_row(i, 25, improve, mysql);
		sscanf(improve, "p<|>iiii", HouseInfo[i][hImprove][0], HouseInfo[i][hImprove][1], HouseInfo[i][hImprove][2], HouseInfo[i][hImprove][3]);
        HouseInfo[i][hNumInt] = cache_get_row_int(i, 26, mysql);
        HouseInfo[i][hSafeCode] = cache_get_row_int(i, 27, mysql);
        HouseInfo[i][hSeal] = cache_get_row_int(i, 28, mysql);
		cache_get_row(i, 29, guns, mysql);
		sscanf(guns, "p<|>iiiiiiii", HouseInfo[i][hGun][0], HouseInfo[i][hGun][1], HouseInfo[i][hGun][2], HouseInfo[i][hGun][3], HouseInfo[i][hGun][4], HouseInfo[i][hGun][5], HouseInfo[i][hGun][6], HouseInfo[i][hGun][7]);


		HouseArea[i] = CreateDynamicSphere(HouseInfo[i][hEnter_X], HouseInfo[i][hEnter_Y], HouseInfo[i][hEnter_Z], 2.0, 0, 0, -1);
		HintStoreArea[HouseInfo[i][hNumInt]-1] = CreateDynamicSphere(HintStore[HouseInfo[i][hNumInt]-1][0],HintStore[HouseInfo[i][hNumInt]-1][1],HintStore[HouseInfo[i][hNumInt]-1][2],2.0);

		HintSafeArea[HouseInfo[i][hNumInt]-1] = CreateDynamicSphere(HintSafe[HouseInfo[i][hNumInt]-1][0],HintSafe[HouseInfo[i][hNumInt]-1][1],HintSafe[HouseInfo[i][hNumInt]-1][2],2.0);

		//HintFreezArea[HouseInfo[i][hNumInt]-1] = CreateDynamicSphere(HintFreez[HouseInfo[i][hNumInt]-1][0],HintFreez[HouseInfo[i][hNumInt]-1][1],HintFreez[HouseInfo[i][hNumInt]-1][2],2.0);
		LoadImprove(i);
		HouseEstate(i);
		
		if(HouseInfo[i][hSeal])
		{
		    new htime;
			htime = RandomEx(7200000, 79200000);
		    HouseInfo[i][hSellTimer] = SetTimerEx("@__HomeSell",htime, false, "i", i);
		    printf("[SELLHOUSE] ID: %d , TIME: %s, MS %d", i, ConvertMsToTime(htime), htime);
		}
	}
	cache_delete(result, mysql);
	print("LoadHouses");
	return true;
}
stock SaveHouse(houseid)
{
	new string[900], str[300];
	format(str, sizeof(str), "UPDATE `houses` SET");
	strcat(string, str);
	format(str, sizeof(str), "`Enter_X` = '%.4f',`Enter_Y` = '%.4f',`Enter_Z` = '%.4f', `Enter_R` = '%.4f', ",
	HouseInfo[houseid][hEnter_X],
	HouseInfo[houseid][hEnter_Y],
	HouseInfo[houseid][hEnter_Z],
	HouseInfo[houseid][hEnter_R]);
	strcat(string, str);

	format(str, sizeof(str), "`Exit_X` = '%.4f', `Exit_Y` = '%.4f', `Exit_Z` = '%.4f', ",
 	HouseInfo[houseid][hExit_X],
	HouseInfo[houseid][hExit_Y],
	HouseInfo[houseid][hExit_Z]);
	strcat(string, str);
	
	format(str, sizeof(str), "`Park_X` = '%.4f', `Park_Y` = '%.4f', `Park_Z` = '%.4f', `Park_R` = '%.4f', ",
 	HouseInfo[houseid][hPark_X],
	HouseInfo[houseid][hPark_Y],
	HouseInfo[houseid][hPark_Z],
	HouseInfo[houseid][hPark_R]);
	strcat(string, str);
	
	format(str, sizeof(str), "`Owner` = '%s', `Room_Owner_0` = '%s', `Room_Owner_1` = '%s', `Room_Owner_2` = '%s', ",
	HouseInfo[houseid][hOwner],
	HRoomOwner[houseid][0],
	HRoomOwner[houseid][1],
	HRoomOwner[houseid][2]);
	strcat(string, str);

	format(str, sizeof(str), "`Level` = '%d', `Cost` = '%d', `Lock` = '%d', ",
	HouseInfo[houseid][hLevel],
	HouseInfo[houseid][hCost],
	HouseInfo[houseid][hLock]);
	strcat(string, str);

	format(str, sizeof(str), "`Interior` = '%d', `Money` = '%d', `Drugs` = '%d', `Mats` = '%d', ",
	HouseInfo[houseid][hInt],
	HouseInfo[houseid][hMoney],
	HouseInfo[houseid][hDrugs],
	HouseInfo[houseid][hMats]);
	strcat(string, str);

	new
	    save_skin[60];

	for(new i; i < 4; i++)
	{
		if(!i)
			format(save_skin, sizeof save_skin, "%d", HouseInfo[houseid][hSkin][i]);

		else
			format(save_skin, sizeof save_skin, "%s|%d", save_skin, HouseInfo[houseid][hSkin][i]);
	}
	new
	    save_gun[80];

	for(new i; i < 8; i++)
	{
		if(!i)
			format(save_gun, sizeof save_gun, "%d", HouseInfo[houseid][hGun][i]);

		else
			format(save_gun, sizeof save_gun, "%s|%d", save_gun, HouseInfo[houseid][hGun][i]);
	}

	format(str, sizeof(str), "`Skin` = '%s', `Gun` = '%s', ",
	save_skin,
	save_gun);
	strcat(string, str);

	new
	    save_improve[60];
	    
	for(new i; i < 4; i++)
	{
		if(!i)
			format(save_improve, sizeof save_improve, "%d", HouseInfo[houseid][hImprove][i]);
			
		else
			format(save_improve, sizeof save_improve, "%s|%d", save_improve, HouseInfo[houseid][hImprove][i]);
	}


	format(str, sizeof(str), "`Days` = '%d', `Improve` = '%s', `SafeCode` = '%d', `Seal` = '%d' WHERE `ID` = '%i'",
	HouseInfo[houseid][hDays],
	save_improve,
	HouseInfo[houseid][hSafeCode],
	HouseInfo[houseid][hSeal],
	houseid + 1);
	strcat(string, str);
	if(!EXITSAVEMODE)mysql_tquery(mysql, string); else mysql_query(mysql, string, false);
	return true;
}
stock SaveHouses()
{
	for (new i = 0;i < OWNABLEHOUSES;i ++) SaveHouse(i);
	return true;
}
stock LoadImprove(houseid)
{
	new
		hintid = HouseInfo[houseid][hNumInt]-1;
		
	for(new k; k < 4 ; k++) //Улучшения
	{
		if(!HouseInfo[houseid][hImprove][k])
			continue;
			
		switch(k)
		{
			case 1:
			{
				HintSafeObject[houseid] = CreateDynamicObject(2332, HintSafe[hintid][0], HintSafe[hintid][1], HintSafe[hintid][2], HintSafe[hintid][3], HintSafe[hintid][4], HintSafe[hintid][5], houseid+51); //Сейф
				HintSafeText[houseid] = CreateDynamic3DTextLabel("Сейф\n\n{FFFFFF}Введите /safe для взаимодействия", 0x1E90FFFF, HintSafe[hintid][0],HintSafe[hintid][1],HintSafe[hintid][2], 5.0, .worldid = 51+houseid);
			}
			//case 2: CreateDynamicObject(2141, HintFreez[hintid][0], HintFreez[hintid][1], HintFreez[hintid][2], HintFreez[hintid][3], HintFreez[hintid][4], HintFreez[hintid][5], houseid+51);
			case 2:
			{
				HintStoreObject[houseid] = CreateDynamicObject(2708, HintStore[hintid][0], HintStore[hintid][1], HintStore[hintid][2], HintStore[hintid][3], HintStore[hintid][4], HintStore[hintid][5], houseid+51);
				HintStoreText[houseid] = CreateDynamic3DTextLabel("Шкаф\n\n{FFFFFF}Введите /store для взаимодействия", 0x1E90FFFF, HintStore[hintid][0], HintStore[hintid][1]+0.7, HintStore[hintid][2]+1.0, 5.0, .worldid = 51+houseid);

				new cnt;
				
				for(new l;l<4;l++)
				{
					if(HouseInfo[houseid][hSkin][l])
						cnt++;
				}
				
			    if(IsValidDynamicObject(HintDressObject[houseid][0]))
			    	DestroyDynamicObject(HintDressObject[houseid][0]);

			    if(IsValidDynamicObject(HintDressObject[houseid][1]))
			    	DestroyDynamicObject(HintDressObject[houseid][1]);

			    if(IsValidDynamicObject(HintDressObject[houseid][1]))
			    	DestroyDynamicObject(HintDressObject[houseid][2]);

				if(cnt > 0)
				{
					HintDressObject[houseid][0] = CreateDynamicObject(2689,HintDress[hintid][0][0],HintDress[hintid][0][1],HintDress[hintid][0][2],HintDress[hintid][0][3],HintDress[hintid][0][4],HintDress[hintid][0][5],51+houseid);

					if(cnt > 1)
						HintDressObject[houseid][1] = CreateDynamicObject(2704,HintDress[hintid][1][0],HintDress[hintid][1][1],HintDress[hintid][1][2],HintDress[hintid][1][3],HintDress[hintid][1][4],HintDress[hintid][1][5],51+houseid);

					if(cnt > 2)
						HintDressObject[houseid][2] = CreateDynamicObject(2705,HintDress[hintid][2][0],HintDress[hintid][2][1],HintDress[hintid][2][2],HintDress[hintid][2][3],HintDress[hintid][2][4],HintDress[hintid][2][5],51+houseid);

				}
			
				for(new l;l<8;l++)
				{
					if(!HouseInfo[houseid][hGun][l])
						continue;
						
					HouseGunObject[houseid][l] = CreateDynamicObject(HintGunID[l], HintGun[hintid][l][0], HintGun[hintid][l][1], HintGun[hintid][l][2], HintGun[hintid][l][3], HintGun[hintid][l][4], HintGun[hintid][l][5], houseid+51);
				}
			}
		}
	}
}
stock ProxDetectorS(Float:radi, playerid, targetid, spec = 0)
{
    new Float:p[3];
    if(!IsPlayerConnected(playerid)) return false;
    if(!IsPlayerConnected(targetid)) return false;
    if(!spec)
    {
	    if(GetPlayerState(playerid) == 9) return false;
	    if(GetPlayerState(targetid) == 9) return false;
    }
    if(!GetPlayerPos(targetid, p[0], p[1], p[2])) return false;
	if(!IsPlayerInRangeOfPoint(playerid, radi, p[0], p[1], p[2]))
	{
		return false;
	}
	return true;
}
stock GetMonthDays(year, month)
{
	switch(month)
	{
	    case 0:     return 31;
	    case 1: 	return 31;
	    case 2: 	return februarydays(year);
	    case 3: 	return 31;
	    case 4: 	return 30;
	    case 5: 	return 31;
	    case 6: 	return 30;
	    case 7: 	return 31;
	    case 8: 	return 31;
	    case 9: 	return 30;
	    case 10: 	return 31;
	    case 11: 	return 30;
	    case 12: 	return 31;
	    default: 	return -1;
	}
	return -1;
}
stock februarydays(year)
{
	if(!(year % 4)) return 29;
	else return 28;
}

stock CheckMySQLConnection()
{
    if(mysql_ping() == -1) mysql_reconnect();
    return true;
}
stock ini_GetKey( line[] )
{
	new keyRes[128];
	keyRes[0] = 0;
    if ( strfind( line , "=" , true ) == -1 ) return keyRes;
    strmid( keyRes , line , 0 , strfind( line , "=" , true ) , sizeof( keyRes) );
    return keyRes;
}

stock ini_GetValue( line[] )
{
	new valRes[128];
	valRes[0]=0;
	if ( strfind( line , "=" , true ) == -1 ) return valRes;
	strmid( valRes , line , strfind( line , "=" , true )+1 , strlen( line ) , sizeof( valRes ) );
	return valRes;
}
public OnObjectMoved(objectid)
{
	return true;
}
stock StopMoveBox(box, playerid = -1)
{
	return true;
}
stock bool:poscomp(Float:X, Float:Y, Float:Z, Float:X1, Float:Y1, Float:Z1)
{
	return ( floatcomp(X, X1) && floatcomp(Y, Y1) && floatcomp(Z, Z1) ) ? true : false;
}
stock GetIntGHS( interior )
{
	new ghs;
	switch(interior)
	{
		case 1: ghs = 1;
		case 2: ghs = 2;
		case 3: ghs = 3;
		case 4: ghs = 4;
		case 5: ghs = 5;
		case 6: ghs = 6;
		case 7: ghs = 7;
		case 8: ghs = 8;
		case 9: ghs = 9;
		case 10: ghs = 10;
		case 11: ghs = 12;
		case 12: ghs = 15;
		case 13: ghs = 16;
		case 14: ghs = 17;
		case 15: ghs = 18;
		case 16: ghs = 19;
		case 17: ghs = 20;
		case 18: ghs = 21;
		case 19: ghs = 22;
		case 20: ghs = 23;
		case 21: ghs = 24;
		case 22: ghs = 25;
		case 23: ghs = 26;
	}
	return ghs;
}
stock SetHouseInt( houseid, inte )
{
	new i = GetIntGHS(inte);
	SetInHousePos(houseid,GHSPos[i][0],GHSPos[i][1],GHSPos[i][2]);
	HouseInfo[houseid][hInt] = IntInfo[inte][iInterior];
	HouseInfo[houseid][hLevel] = IntInfo[inte][iLevel];
	return true;
}
stock SendHouseMessage(houseid,color,const message[])
{
  	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i)) continue;
		if(PI[i][pHouseKey] != houseid) continue;
		SCM(i,color,message);
	}
	return true;
}
stock ASCMTA(color, const text[])
{
  	foreach(new i : Player)
	{
	    if(!IsPlayerConnected(i))
			continue;
			
	    SendClientMessage(i, color, text);
	}
}
stock RespawnCars(first = 1, endcar = -1)
{
	if(endcar == -1) endcar = ADD_VEHICLES;
	new bool:Occuped[MAX_VEHICLES];
  	foreach(new i : Player)
	{
	    if(IsPlayerConnected(i))
	    {
		    if(IsPlayerInAnyVehicle(i))
		    {
		        new carid = GetPlayerVehicleID(i);
		        Occuped[carid] = true;
		        if(IsTrailerAttachedToVehicle(carid)) Occuped[GetVehicleTrailer(carid)] = true;
		    }
	    }
	}
	for(new i = first; i <= endcar;i ++)
	{
	    if(IsVehicleConnected(i))
	    {
		    if(!Occuped[i])
			{
				SetVehicleToRespawn(i);
			}
	    }
	}
	return true;
}
stock SetInHousePos(houseid,Float:X,Float:Y,Float:Z)
{
    HouseInfo[houseid][hExit_X] = X;
    HouseInfo[houseid][hExit_Y] = Y;
    HouseInfo[houseid][hExit_Z] = Z;
	return true;
}

stock SetPlayerAttachedObjectEx(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0)
{
	SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
	return true;
}

stock IsPlayerToKvadrat(playerid,Float:min_x,Float:min_y,Float:max_x,Float:max_y)
{
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid, x, y, z);
	if((x <= max_x && x >= min_x) && (y <= max_y && y >= min_y)) return 1;
	return 0;
}
stock PlayerToPlayer(playerid, toplayer, Float:radi)
{
	new Float:newposx, Float:newposy, Float:newposz;
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tmpposx, Float:tmpposy, Float:tmpposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	GetPlayerPos(toplayer, newposx, newposy, newposz);
	tmpposx = (oldposx -newposx);
	tmpposy = (oldposy -newposy);
	tmpposz = (oldposz -newposz);
	if (((tmpposx < radi) && (tmpposx > -radi)) && ((tmpposy < radi) && (tmpposy > -radi)) && ((tmpposz < radi) && (tmpposz > -radi)))return 1;
	return 0;
}

forward CheckChangeName(playerid, name[]);
public CheckChangeName(playerid, name[])
{
    new rows, fields;
    cache_get_data(rows, fields);
	if(rows)
    {
		SendClientMessage(playerid,COLOR_GREY,"Этот никнейм уже используется");
	}
	else
	{
		new
			format_change_name[70 + MAX_PLAYER_NAME + MAX_PLAYER_NAME + 4];

		SetString(temp_change_nickname[playerid], name);

		temp_change_nickname_want[playerid] = true;
		SetPVarInt(playerid,"player_name_change",true);
		format(format_change_name,sizeof(format_change_name),"[Смена ника] %s желает сменить нонРП имя на %s [Подтвердить: /okay %d]",PN(playerid),name,playerid);
	    SendAdminsMessage(0x9ACD32AA, format_change_name);
	    SendClientMessage(playerid,COLOR_GREEN,"Ваша заявка на смену ника отправлена Администрации.");
    }
}
forward CheckChangeNameDonate(playerid, name[]);
public CheckChangeNameDonate(playerid, name[])
{
    new
		rows, fields;
		
    cache_get_data(rows, fields);
    
	if(rows)
		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот никнейм уже используется");

	else
	{
		new
			format_change_name[160];

		SetString(pTemp[playerid][pNewNick], name);

		format(format_change_name, sizeof format_change_name, "{FFFFFF}Новый никнейм: {4682B4}%s{FFFFFF}\nБудет снято: 20 рублей\nОстанется на донат счете: %d %s\n\t\tПродолжить?", name, PI[playerid][pVirMoney] - 20, Declension_GetMoney(PI[playerid][pVirMoney] - 20));
		ShowPlayerDialogEx(playerid, 274, DIALOG_STYLE_MSGBOX, "Смена ника", format_change_name, !"Да", !"Нет");
    }
}


public OnPlayerEnterRaceCheckpoint(playerid)
{
	// ================== Развозчик =========================
	if(GetPVarInt(playerid, "ProductLoad") == 18)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(vehicleid) != 456) return SCM(playerid, COLOR_GREY, "Вы должны находиться в специализированном транспорте!");
		if(GetPlayerState(playerid) != 2) return SCM(playerid, COLOR_GREY, "Вы должны быть за рулем т/с");
		new i = ProductInfo[GetPVarInt(playerid, "ProductID")][pBizid]-1, scdplayerid;
		BizInfo[i][bProducts] += ProductInfo[GetPVarInt(playerid, "ProductID")][pTill];
		//////////////////SetBizInt(i, "product", BizInfo[i][bProduct]);
		new lstring[144];
		format(lstring, sizeof(lstring), "{7AC71F}[Успешно] {ffffff}Вы доставили {FFC800}%i продуктов {ffffff}для {FFC800}%s. {ffffff}Заказчик: {FFC800}%s.", ProductInfo[GetPVarInt(playerid, "ProductID")][pTill], BizInfo[i][bName], ProductInfo[GetPVarInt(playerid, "ProductID")][pName]);
		SCM(playerid, COLOR_WHITE, lstring);
		sscanf(ProductInfo[GetPVarInt(playerid, "ProductID")][pName], "u", scdplayerid);
		new salary = ProductInfo[GetPVarInt(playerid, "ProductID")][pPrice] / 2;
		if(salary > 10000) salary = 10000;

		format(lstring, sizeof(lstring), "{FFC800}[Подсказка] {ffffff}Вы заработали {FFC800}%d$.", salary);
		SCM(playerid, -1, lstring);
		DeletePVar(playerid, "ProductLoad");
		
		new mes[14];
		format(mes,sizeof(mes),"~g~+ %d$",salary);
		GameTextForPlayer(playerid, mes, 3000, 1);
		
		DeletePVar(playerid, "ProductInfo");
		DisablePlayerRaceCheckpoint(playerid);
		GiveMoney(playerid,salary);
		SetPVarInt(playerid, "PRODVEH", 0);
		if(IsValidDynamic3DTextLabel(JobText3D[playerid]))
				DestroyDynamic3DTextLabel(JobText3D[playerid]);
		if(IsPlayerConnected(scdplayerid))
		{
			format(lstring, sizeof(lstring), "{FFC800}[Подсказка]{ffffff} Развозчик продуктов {FFC800}%s {ffffff}доставил {FFC800}%i продуктов. {ffffff}Чек: {7AC71F}%i$", PN(playerid),ProductInfo[GetPVarInt(playerid, "ProductID")][pTill],ProductInfo[GetPVarInt(playerid, "ProductID")][pPrice]);
			SCM(scdplayerid, -1, lstring);
		}
		for(new p = 0; p <= MAX_PLAYERS; p++)
		{
			if(!IsPlayerConnected(p) || IsPlayerLogged[p] == false || GetPVarInt(p, "ProductID") == 0) continue;
			if(GetPVarInt(p, "ProductID") > GetPVarInt(playerid, "ProductID")) SetPVarInt(p, "ProductID", GetPVarInt(p, "ProductID") - 1);
		}
		new request[80];
		format(request, sizeof request, "DELETE FROM `product` WHERE `id` = '%d'", ProductInfo[GetPVarInt(playerid, "ProductID")][idxx]);
		mysql_query(mysql, request);
		for(new p = GetPVarInt(playerid, "ProductID"); p </*=*/ TOTALPRODUCT/* - 1*/; p++)
		{
			ProductInfo[p][idxx] = ProductInfo[p+1][idxx];
			strmid(ProductInfo[p][pName], ProductInfo[p+1][pName], 0, strlen(ProductInfo[p+1][pName]), MAX_PLAYER_NAME);
			ProductInfo[p][pBizid] = ProductInfo[p+1][pBizid];
			ProductInfo[p][pPrice] = ProductInfo[p+1][pPrice];
			ProductInfo[p][pTill] = ProductInfo[p+1][pTill];
			ProductInfo[p][pStatus] = ProductInfo[p+1][pStatus];
		}
		TOTALPRODUCT--;
		DeletePVar(playerid, "ProductID");
		DeletePVar(playerid, "ProductJob");
        SetPlayerRaceCheckpoint(playerid, 1, 2785.4731,-2493.4939,13.6531, 0.0, 0.0, 0.0, 5.0);
	}
	// ======================================================
	//--------------event---------------
 	if(GetPlayerVehicleID(playerid) && PI[playerid][pJob] == 1 && temp_bus_id[playerid] != INVALID_VEHICLE_ID && VehicleInfo[GetPlayerVehicleID(playerid)][vBusOwner] == playerid)
	{
		DisablePlayerRaceCheckpoint(playerid);
		BusMoney[playerid] += 45;
		if(PI[playerid][pQuest] == 9 && PI[playerid][pQuestStatus] == 1)
		{
		    PI[playerid][pQuestProcess]++;
		    UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
			if(PI[playerid][pQuestProcess] >= 250)
			{
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		    	SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы проехали 250 чекпоинтов. Отправляйтесь к Линкольну");
			}
		}
		
		new
			pos = temp_bus_pos[playerid],
			route = temp_bus_route[playerid];
			
		if(gBusCPs[route][pos][0] == gBusCPs[route][pos+1][0] && gBusCPs[route][pos][1] == gBusCPs[route][pos+1][1]) //Остановка
		{
			new
				routename[56],
				string[128];
				
			switch(route)
			{
				case 0: strcat(routename, "Лос Сантос - Лас Вентурас");
				case 1: strcat(routename, "Сан Фиерро - Лос Сантос");
                case 2: strcat(routename, "Лос Сантос - Завод автозапчастей");
                case 3: strcat(routename, "Сан Фиерро - Лас Вентурас");
			}
			
			format(string, sizeof string, "Автобус по маршруту %s отправляется через 10 секунд", routename);
			ProxDetector(30.0, playerid, string, 0x44B2FFFF);
			SetTimerEx("BusStop",10000, false, "i", playerid);
			return 1;
		}
		if(pos == 109 || gBusCPs[route][pos+1][0] == 0.0)
		{
		    temp_bus_pos[playerid] = 0;
		    
		    new
		        frmt_msg[60];
		        
			format(frmt_msg, sizeof frmt_msg, "%d$ добавлено к Вашей зарплате", BusMoney[playerid]);
			SendClientMessage(playerid, COLOR_GREEN, frmt_msg);
		}
		else temp_bus_pos[playerid]++;
		SetNextBusCP(playerid, temp_bus_pos[playerid]);
	}
	else if(MechCallTime[playerid] > 0)
	{
		MechCallTime[playerid] = 0;
		SCM(playerid, COLOR_YELLOW, "Вы достигли места назначения.");
		DisablePlayerRaceCheckpoint(playerid);
	}
	return 1;
}
stock GetVehicleType(model)
{
	switch(model)
	{
		case 430,446,452,453,454,472,473,484,493,595: return VEHICLE_TYPE_BOAT;
		case 417,425,447,469,487,488,548,563,460,511,512,513,519,520,553,557,592,593: return VEHICLE_TYPE_PLANE;
		case 448,462,481,509,510: return VEHICLE_TYPE_TWOWEELS;
		default: return VEHICLE_TYPE_CAR;
	}
	return VEHICLE_TYPE_CAR;
}
public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    if(response)
    {
		new mes[500];
		format(mes, sizeof mes , "SetPlayerAttachedObject(playerid, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f", index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ );

        SendClientMessage(playerid, COLOR_WHITE, mes);

    }

    return 1;
}
public OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
   	if(response == EDIT_RESPONSE_FINAL)
	{
	    DestroyObject(objectid);
		CreateObject(GetPVarInt(playerid,"ModelID"),fX,fY,fZ,fRotX,fRotY,fRotZ);
		gLegoObject[objectX] = fX;
		gLegoObject[objectY] = fY;
		gLegoObject[objectZ] = fZ;
		gLegoObject[objectRotX] = fRotX;
		gLegoObject[objectRotY] = fRotY;
		gLegoObject[objectRotZ] = fRotZ;

	}
    return 1;
}
public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
   	if(response == EDIT_RESPONSE_FINAL)
	{
	    DestroyDynamicObject(objectid);
		CreateDynamicObject(GetPVarInt(playerid,"DynamicModelID"),x,y,z,rx,ry,rz);
		gLegoObject[objectModel] = GetPVarInt(playerid,"DynamicModelID");
		gLegoObject[objectX] = x;
		gLegoObject[objectY] = y;
		gLegoObject[objectZ] = z;
		gLegoObject[objectRotX] = rx;
		gLegoObject[objectRotY] = ry;
		gLegoObject[objectRotZ] = rz;
		new File:File_read = fopen("new.txt", io_read);

		new object_list[3480], tempstring[200];

		new length = flength(File_read);
		for(new i; i < length; i++)
		{
			fread(File_read, tempstring);
			strcat(object_list, tempstring);
		}

		fclose(File_read);

		new File:File = fopen("new.txt", io_write);

		new striRng[3480];
		format(striRng, sizeof(striRng),"%sCreateDynamicObject(%d, %f, %f, %f, %f, %f, %f);\n", object_list, gLegoObject[objectModel], gLegoObject[objectX], gLegoObject[objectY], gLegoObject[objectZ], gLegoObject[objectRotX], gLegoObject[objectRotY], gLegoObject[objectRotZ]);

		fwrite(File, striRng);
		fclose(File);
	}
    return 1;
}
public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
{
	//ShowPlayerDialogEx(playerid, 353, DIALOG_STYLE_MSGBOX, !"Действие с объектом", !"Выберите действие с объектом\nВы можете его отредактировать или удалить", !"Изменить", !"Удалить");
	//SetPVarInt(playerid, "SelectedObject", objectid);
	//SetPVarInt(playerid, "ModelID", modelid);
    return 1;
}
public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
    if(!IsValidDynamicObject(objectid)) return true;
	ShowPlayerDialogEx(playerid, 354, DIALOG_STYLE_MSGBOX, !"Действие с объектом", !"Выберите действие с объектом\nВы можете его отредактировать или удалить", !"Изменить", !"Удалить");
	SetPVarInt(playerid, "SelectedDynamicObject", objectid);
	SetPVarInt(playerid, "DynamicModelID", modelid);
	gLegoObject[objectX] = x;
	gLegoObject[objectY] = y;
	gLegoObject[objectZ] = z;
    return 1;
}
//===================================[КОМАНДЫ СЕРВЕРА]===================================
CMD:vibors(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7 || IsPlayerLogged[playerid] == false) return true;
	ShowPlayerDialogEx(playerid, 6003, DIALOG_STYLE_LIST, !"Выборы", !"1. Назначит кандидатов\n2. Начать выборы\n3. Закончить выборы\n4. Посмотреть результаты", !"ОК", !"Отмена");
	return true;
}

CMD:fobject(playerid, params[])
{
    if(PI[playerid][pFamily] == 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только семьям");
    else if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Запрещено использовать в машине");
    if(GetPVarInt(playerid,"objectcop"))
    {
        DestroyDynamicObject(GetPVarInt(playerid,"objectcop"));
		DeletePVar(playerid, "objectcop");
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка]{ffffff} Вы убрали установленный вами объект");
       	if(IsValidDynamic3DTextLabel(JobText3D[playerid]))
			DestroyDynamic3DTextLabel(JobText3D[playerid]);
        JobText3D[playerid] = Text3D:INVALID_3DTEXT_ID;
		return 1;
    }
    ShowPlayerDialogEx(playerid, 5601, DIALOG_STYLE_LIST, !"Обьекты", !"Стул - {FF7319}ID: 2121\nМангал - {FF7319}ID: 19831\nЛежак - {FF7319}ID: 1645\nДрова - {FF7319}ID: 19632\nОгонь - {FF7319}ID: 18689\nСтолик - {FF7319}ID: 1281", !"Выбрать", !"Отмена");
    return 1;
}
CMD:object(playerid, params[])
{
    if(!IsAMafia(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только мафиози");
    else if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Запрещено использовать в машине");
    else if(IsAMafia(playerid) && PI[playerid][pRank] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно с 3 ранга");
    if(GetPVarInt(playerid,"objectcop"))
    {
        DestroyDynamicObject(GetPVarInt(playerid,"objectcop"));
		DeletePVar(playerid, "objectcop");
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка]{ffffff} Вы убрали установленный вами объект");
       	if(IsValidDynamic3DTextLabel(JobText3D[playerid]))
			DestroyDynamic3DTextLabel(JobText3D[playerid]);
        JobText3D[playerid] = Text3D:INVALID_3DTEXT_ID;
		return 1;
    }
    ShowPlayerDialogEx(playerid, 5600, DIALOG_STYLE_LIST, !"Обьекты", !"Столик - {FF7319}ID: 1281\n{ffffff}Табуретка - {FF7319}ID: 1810\n{ffffff}Мангал - {FF7319}ID: 1481\n{ffffff}Нарко - {FF7319}ID: 1279\n{ffffff}Огонь - {FF7319}ID: 18689\n{ffffff}Лежак - {FF7319}ID: 1645", !"Выбрать", !"Отмена");
    return 1;
}
CMD:break(playerid, params[])
{
    if(!IsACop(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в Полиции/ФБР");
    else if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Запрещено использовать в машине");
    else if(IsACop(playerid) && PI[playerid][pRank] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно с 3 ранга");
    if(GetPVarInt(playerid,"objectcop"))
    {
        DestroyDynamicObject(GetPVarInt(playerid,"objectcop"));
		DeletePVar(playerid, "objectcop");
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка]{ffffff} Вы убрали установленный вами объект");
        if(Ships[playerid]) DestroyDynamicArea(Ships[playerid]);
       	if(IsValidDynamic3DTextLabel(JobText3D[playerid]))
			DestroyDynamic3DTextLabel(JobText3D[playerid]);
        JobText3D[playerid] = Text3D:INVALID_3DTEXT_ID;
		return 1;
    }
    ShowPlayerDialogEx(playerid, 5599, DIALOG_STYLE_LIST, !"Обьекты", !"Знак (стоп) - {FF7319}ID: 19966\nЗнак (дорога закрыта) - {FF7319}ID: 19972\nОграда 1 - {FF7319}ID: 994\nОграда 2 - {FF7319}ID: 1424\nТруп - {FF7319}ID: 19944\nШипы (большие) - {FF7319}ID: 2892\nШипы (маленькие) - {FF7319}ID: 2899\nБетонные плиты - {FF7319}ID: 1422\nСтойка - {FF7319}ID: 1282", !"Выбрать", !"Отмена");
    return 1;
}
CMD:sp(playerid, params[])
{
    if(PI[playerid][pAdmin] < 1) return 1;

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/sp [ID игрока]");
	if(!IsPlayerConnected(target) || playerid == target || !IsPlayerLogged[target]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");
    if(IsPlayerInAnyVehicle(playerid)) RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);
	if(PI[target][pAdmin] && (PI[playerid][pAdmin] < PI[target][pAdmin])) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете применить это к администратору старше Вас уровнем");
    HideCarInfo(playerid);
    
    if(PI[playerid][pSpecOn] == 0)
    {
	    new Float:x, Float:y,Float:z;

		GetPlayerPos(playerid, x, y, z);
		SetPVarFloat(playerid, "oldx", x);
		SetPVarFloat(playerid, "oldy", y);
		SetPVarFloat(playerid, "oldz", z);
		SetPVarInt(playerid, "oldint", GetPlayerInterior(playerid));
		SetPVarInt(playerid, "oldworld", GetPlayerVirtualWorld(playerid));
	    StartPlayerSpectate(playerid, target);
	}
    else if(PI[playerid][pSpecOn] == 1)
    {
        new pstate = GetPlayerState(target),vehicleid = GetPlayerVehicleID(target);
        PI[playerid][pSpectating] = true;
        PI[playerid][pSpectatee] = target;
        SetPlayerInterior(playerid, GetPlayerInterior(target));
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(target));
        if(pstate == PLAYER_STATE_DRIVER || pstate == PLAYER_STATE_PASSENGER) PlayerSpectateVehicle(playerid,vehicleid);
        else PlayerSpectatePlayer(playerid, target);
    }
    return true;
}
CMD:offmute(playerid, params[])
{
    if(PI[playerid][pAdmin] < 3) return true;
	new playername[MAX_PLAYER_NAME], time, reason[32];
	if(sscanf(params, "s[24]is[32]", playername, time, reason)) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/offmute [ник игрока] [время] [причина]");
	else if(GetString(reason, "None")) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Укажите другую причину!");
	else if(GetPlayerID(playername) != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Игрок в сети, используйте команду /mute");
	else if(!(10 <= params[1] <= 180)) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Время от 10 до 180 минут!");
	
	new nickname[MAX_PLAYER_NAME];
	mysql_escape_string(playername, nickname);

	new query_offwarn_getid[100];

	format(query_offwarn_getid, sizeof query_offwarn_getid, "SELECT `MuteTime` FROM `accounts` WHERE `NickName` = '%s'", playername);
	new Cache:result = mysql_query(mysql, query_offwarn_getid);

	if(!cache_get_row_count(mysql))
	{
		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный никнейм");
		return cache_delete(result, mysql);
	}
	
	new playermute, strlog[144];
 	playermute = cache_get_row_int(0, 0);
 	if(playermute > 0) return SendClientMessage(playerid, COLOR_GREY, "Игрок уже имеет бан чата!");

	format(strlog, sizeof(strlog), "Игрок %s получил оффлайн бан чата от администратора %s на %i минут. Причина: %s", playername, PN(playerid),time, reason);
	ASCMTA(COLOR_LIGHTRED, strlog);

	mysql_query_string[0] = 0;
	format(mysql_query_string, sizeof(mysql_query_string), "UPDATE `accounts` SET `MuteTime` = '%d' WHERE `NickName` = '%s'",  time*60, playername);
	mysql_tquery(mysql, mysql_query_string, "", "");
	mysql_query_string[0] = 0;
	return 1;
}
CMD:offjail(playerid, params[])
{
    if(PI[playerid][pAdmin] < 3) return true;
	new playername[MAX_PLAYER_NAME], time, reason[32];
	if(sscanf(params, "s[24]is[32]", playername, time, reason)) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/offjail [ник игрока] [время] [причина]");
	else if(GetString(reason, "None")) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Укажите другую причину!");
	else if(GetPlayerID(playername) != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Игрок в сети, используйте команду /prison");
	else if(!(1 <= time <= 180)) return SendClientMessage(playerid, COLOR_GREY, "Время от 1 до 180 минут!");
	
	new nickname[MAX_PLAYER_NAME];
	mysql_escape_string(playername, nickname);

	new query_offwarn_getid[100];

	format(query_offwarn_getid, sizeof query_offwarn_getid, "SELECT `JailTime`, `JailAdmin`,`Wanted`,`Prison` FROM `accounts` WHERE `NickName` = '%s'", playername);
	new Cache:result = mysql_query(mysql, query_offwarn_getid);

	if(!cache_get_row_count(mysql))
	{
		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный никнейм");
		return cache_delete(result, mysql);
	}
	
	new playerjail, strlog[144];
 	playerjail = cache_get_row_int(0, 0);
 	if(playerjail > 0) return SendClientMessage(playerid, COLOR_GREY, "Игрок уже имеет бан чата!");
 	
	format(strlog, sizeof(strlog), "[A] Игрок %s получил оффлайн КПЗ от администратора %s на %i минут. Причина: %s", playername, PN(playerid),time, reason);
	SendAdminsMessage(COLOR_GREY, strlog);
	
	mysql_query_string[0] = 0;
	format(mysql_query_string, sizeof(mysql_query_string), "UPDATE `accounts` SET `JailTime` = '%d',`JailAdmin` = '1',`Wanted` = '0',`Prison` = '4' WHERE `NickName` = '%s'",  time*60, playername);
	mysql_tquery(mysql, mysql_query_string, "", "");
	mysql_query_string[0] = 0;
	return 1;
}
CMD:setskill(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7) return true;
	if(sscanf(params, "udd", params[0], params[1], params[2])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/setskill [id игрока] [id оружия] [навык]");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, COLOR_GREY, "Игрок не в сети");
	if(IsPlayerLogged[params[0]] == false) return SendClientMessage(playerid, COLOR_GREY, "Игрок не авторизовался");
	if(!IsASkillGun(params[1])) return SendClientMessage(playerid, COLOR_GREY, "Введите id оружия, для которого хотите установить навык.");
	if(params[2] > 100 || params[2] < 1) return SendClientMessage(playerid, COLOR_GREY, "Введите уровень навыка от 1 до 100!");
	//PlayerInfo[playerid][pGunSkill][0] = params[2]);
	new guntext[16];
	if(params[1] == 23) {
		PI[params[0]][pSDPistol_Skill] = params[2], format(guntext, sizeof(guntext), "Deagle");
		UpdatePlayerData(params[0], "SDPistol_Skill", PI[params[0]][pSDPistol_Skill]);
	}
	else if(params[1] == 24) {
		PI[params[0]][pEagle_Skill] = params[2], format(guntext, sizeof(guntext), "Deagle");
		UpdatePlayerData(params[0], "Eagle_Skill", PI[params[0]][pEagle_Skill]);
	}
	else if(params[1] == 25) {
		PI[params[0]][pShotGun_Skill] = params[2], format(guntext, sizeof(guntext), "ShotGun");
		UpdatePlayerData(params[0], "ShotGun_Skill", PI[params[0]][pShotGun_Skill]);
	}
	else if(params[1] == 29) {
		PI[params[0]][pMP5_Skill] = params[2], format(guntext, sizeof(guntext), "MP5");
		UpdatePlayerData(params[0], "MP5_Skill", PI[params[0]][pMP5_Skill]);
	}
	else if(params[1] == 30) {
		PI[params[0]][pAK47_Skill] = params[2], format(guntext, sizeof(guntext), "AK-47");
		UpdatePlayerData(params[0], "AK47_Skill", PI[params[0]][pAK47_Skill]);
	}
	else if(params[1] == 31) {
		PI[params[0]][pM4_Skill] = params[2], format(guntext, sizeof(guntext), "M4A1");
		UpdatePlayerData(params[0], "M4_Skill", PI[params[0]][pM4_Skill]);
	}
	SetPlayerSkills(params[0]);
	new lstring[100];
	format(lstring, sizeof(lstring), "{FFC800}[Подсказка] {FFFFFF}Вам установили навык %s на %d процентов.", guntext, params[2]);
	SendClientMessage(params[0], COLOR_WHITE, lstring);
	format(lstring, sizeof(lstring), "Вы установили %s навык %s на %d процентов.", PN(params[0]), guntext, params[2]);
	SendClientMessage(playerid, COLOR_GREEN, lstring);
	return true;
}

CMD:netstats(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7) return true;
	strdel(totalstring, 0, 1024);
	GetNetworkStats(totalstring, 1024);
	ShowPlayerDialogEx(playerid, 0000, 0, "Server NetStats", totalstring, "Закрыть", "");
	strdel(totalstring, 0, 1024);
	return true;
}
CMD:truck(playerid)
{
	if(PI[playerid][pJob] != JOB_TRUCKER) return 1;
	if(temp_gps_checkpoint[playerid])
	{
		DisablePlayerCheckpoint(playerid);
		temp_gps_checkpoint[playerid] = false;
		SendClientMessage(playerid, COLOR_RED, !"Метка {FFFFFF}снята с радара");
	}
	totalstring[0] = 0;
	format(totalstring, 410, "\
	{ffffff}Название\t{ffffff}Стоимость\n\
	{ffffff} Склад города Лос-Сантос\t{42B02C}%d$ {ffffff}за кг.\n\
	{ffffff} Склад города Сан-Фиерро\t{42B02C}%d$ {ffffff}за кг.\n\
	{ffffff} Склад города Лас-Вентурас\t{42B02C}%d$ {ffffff}за кг.\n",k1,k2,k3);
	ShowPlayerDialogEx(playerid, 5559, DIALOG_STYLE_TABLIST_HEADERS, !"GPS: Дальнобойщики", totalstring, !"Далее", !"Отмена");
	return 1;
}
CMD:amusic(playerid, params[])
{
    if(PI[playerid][pAdmin] < 6) return true;
    new Float:X, Float:Y, Float:Z;
    new Float:Distance,reska[128];
    if(sscanf(params,"fs[127]",Distance,reska)) return SendClientMessage(playerid, COLOR_GREY, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /amusic [радиус] [ссылка]");
    if(Distance < 10 || Distance > 100) return SendClientMessage(playerid,COLOR_GREY,"* Радиус от от 10 до 100");
    if(Music == true) return SendClientMessage(playerid,COLOR_GREY,"* Кто-то уже поставил музыку, удалите ее /offamusic");
    
    SendClientMessage(playerid,COLOR_GREY,"[INFO]: Вы запустили поток!");
    GetPlayerPos(playerid, X, Y, Z);
    
    new string[65];
    format(string, sizeof(string), "BoomBox\nУстановил: {FF8300}%s", PN(playerid));
	MusicInfo = CreateDynamic3DTextLabel(string, -1, X, Y, Z+0.1, 5.0);
					
    BoomBoxObject = CreateDynamicObject(2226, X, Y, Z-0.9, 0.0, 0.0, 0.0, -1,-1,-1);
    
    MusicU[4] = Distance;
	MusicU[1] = X;
	MusicU[2] = Y;
	MusicU[3] = Z;
	UMusic = reska;
	Music = true;
    return true;
}
CMD:offamusic(playerid)
{
    if(PI[playerid][pAdmin] < 6) return true;
	if(Music != true) return SendClientMessage(playerid,COLOR_GREY,"* Сначало запустите музыку (/amusic)");
	
	foreach(new i:Player)
	{
		DeletePVar(i,"Music");
		StopAudioStreamForPlayer(i);
	}
	
	DestroyDynamicObject(BoomBoxObject);
	DestroyDynamic3DTextLabel(MusicInfo);
	SendClientMessage(playerid,COLOR_GREY,"[INFO]: Вы остановили поток");
	Music = false;
	return 1;
}
CMD:redpanel(playerid)
{
	if(PI[playerid][pAdmin] < 7) return 1;
 	totalstring[0] = 0;
  	format(totalstring, 128, "{ffffff}Опыт X2\t\t| %s\n{ffffff}Донат X2\t\t| %s",(!exp_x2) ? ("{F04245}Выкл") : ("{63BD4E}Вкл"),(!donate_x2) ? ("{F04245}Выкл") : ("{63BD4E}Вкл"));
	ShowPlayerDialogEx(playerid, 5555, 2, "Настройки сервера", totalstring, "Выбрать", "Назад");
	return 1;
}
CMD:lip(playerid, params[])
{
	if(!IsPlayerConnected(playerid)) return true;
	if(PI[playerid][pAdmin] < 4) return true;
   	if(sscanf(params,"s[16]", params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /lip [IP адрес]");
   	
   	mysql_query_string[0] = 0;
   	mysql_format(mysql, mysql_query_string,128, "SELECT * FROM `accounts` WHERE RegIP = '%e' OR WHERE LastIP = '%e'", params[0], params[0]);
   	mysql_tquery(mysql, mysql_query_string, "OnPlayerSelectPgetip", "is", playerid, params[0]);
	mysql_query_string[0] = 0;
	return true;
}
CMD:acheatctrl(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7)
		return 1;

	extract params -> new code; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/acheatctrl [Код]");

	if(code < 1 || code > 152)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный номер (от 1 до 152)");
	    
	new
	    frmt_acheat_mes[75];
	    
	if(gAntiCheatOff[code-1])
		format(frmt_acheat_mes, sizeof frmt_acheat_mes, "{7AC71F}[Успешно] {FFFFFF}Вы включили кик за №%d код античита", code), gAntiCheatOff[code-1] = false;
		
	else
	    format(frmt_acheat_mes, sizeof frmt_acheat_mes, "{7AC71F}[Успешно] {FFFFFF}Вы отключили кик за №%d код античита", code), gAntiCheatOff[code-1] = true;
	    
	SendClientMessage(playerid, COLOR_WHITE, frmt_acheat_mes);
	return 1;
}
/*CMD:acheatdeb(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7)
		return 1;

    if(!pTemp[playerid][pAntiCheatLogs])
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы включили логирование киков античитом"), gDebAntiCheat = true, pTemp[playerid][pAntiCheatLogs] = true;

	else
	    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выключили логирование киков античитом"), gDebAntiCheat = false, pTemp[playerid][pAntiCheatLogs] = false;

	
	return 1;
}*/
CMD:acheatlogs(playerid)
{
	if(PI[playerid][pAdmin] < 7)
		return 1;

    if(!pTemp[playerid][pAntiCheatLogs])
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы включили логирование киков античитом"), pTemp[playerid][pAntiCheatLogs] = true;
		
	else
	    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выключили логирование киков античитом"), pTemp[playerid][pAntiCheatLogs] = false;
	    
	return 1;
}

CMD:expbonuss(playerid)
{

	if(PI[playerid][pAdmin] < 7)
		return 1;

    if(!gExpBonus)
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы включили x2 exp"), gExpBonus = true;

	else
	    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выключили x2 exp"), gExpBonus = false;


	return 1;
}
CMD:mysqlllog(playerid)
{
	mysql_log(LOG_ALL);

}
CMD:pro(playerid)
{
	Profiler_Dump();
	
	new stats[150];
	mysql_stat(stats);
	SendClientMessage(playerid, -1, stats);
	
	printf("There are %d unprocessed queries.", mysql_unprocessed_queries());

	printf("The query \"SELECT * FROM `data`\" took %d milliseconds / %d microseconds to execute.",
		cache_get_query_exec_time(UNIT_MILLISECONDS), cache_get_query_exec_time(UNIT_MICROSECONDS));
}
CMD:acheatoff(playerid)
{
	if(PI[playerid][pAdmin] < 7)
		return 1;

	if(!gOffAntiCheat)
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выключили античит"), gOffAntiCheat = true;
		
	else
	    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы включили античит"), gOffAntiCheat = false;
    
    return 1;
}
CMD:promoo(playerid)
{
	if(PI[playerid][pAdmin] < 7)
		return 1;

    return 1;
}
CMD:newleader(playerid, params[])
{
    if(!PI[playerid][pFraction])
		return 1;
		
    new fractionid = PI[playerid][pFraction] - 1;
    
    if(PI[playerid][pRank] < gFractionRankCount[fractionid])
		return 1;
		
    new frid = GetSubfractionID(fractionid+1);
    
    if(PI[playerid][pSubfraction] > 0)
		return 1;
  	if(PI[playerid][pAdmin] > 0)
		return 1;
		
    if(PI[playerid][pFraction] == 11)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции нет подфракций");

    if(frid == -1)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции нет подфракций");
		
    if(sscanf(params, "u", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /newleader [ID игрока]");
		
    if(params[0] == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нельзя указывать свой ID");
		
    if(!IsPlayerConnected(params[0]) || !PI[params[0]][pID])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID / игрок не зарегестрирован");
		
    if(PI[params[0]][pFraction] && PI[params[0]][pFraction] != PI[playerid][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже состоит в организации");

	if(PI[params[0]][pv_Fraction])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске");
	    
    new mes[128];
    strcat(mes, "Выберите подфракцию:");
    for(new i = 0; i < 3; i++)
    {
        if(strlen(gSubfractionName[frid][i]))
        {
            strcat(mes, "\n");
            strcat(mes, gSubfractionName[frid][i]);
        }
    }

	temp_newlead_receiver[playerid] = params[0] + 1;
	temp_newlead_sender[params[0]] = playerid + 1;
	temp_newlead_id[params[0]] = fractionid+1;
	
    ShowPlayerDialogEx(playerid, 940, DIALOG_STYLE_LIST, !"Выберите подфракцию:", mes, !"Назначить", !"Отмена");
    return true;
}
CMD:r(playerid, params[])
{
	if(!PI[playerid][pFraction])
		return 1;
		
	if(PI[playerid][pFraction] != 10 && PI[playerid][pFraction] != 11 && !PI[playerid][pSubfraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам недоступна эта функция");

	if(IsAGang(playerid) || IsAMafia(playerid))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам недоступна эта функция");
		
    if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);

	if(PI[playerid][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Используйте команду /rn");

	if(sscanf(params, "s[128]", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /r [текст]");
		
	new
		fractionid = PI[playerid][pFraction]-1,
		rank = PI[playerid][pRank],
		frmt_subfract_chat[128];
		
	SetPlayerChatBubble(playerid, !"Сказал что-то в рацию", 0xDD90FFFF, 10.0, 3000);
	
	format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] %s %s[%d]: %s", gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);
	
	if(fractionid+1 == 10 && !PI[playerid][pSubfraction] && rank <= 9) // для правительства
		format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] %s %s[%d]: %s", gPrezRankName[rank-1], PN(playerid), playerid, params[0]);

	else if(fractionid+1 == 11 && PI[playerid][pDivision] != 0)
		format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] [%s] %s %s[%d]: %s ", gTagName[PI[playerid][pDivision]-1], gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);

  	foreach(new i : Player)
	{
		if(IsPlayerConnected(i) && PI[i][pFraction] == fractionid+1 && PI[i][pSubfraction] == PI[playerid][pSubfraction]
		|| pTemp[i][pEarsFr] == fractionid+1 && pTemp[i][pEarsSub] == PI[playerid][pSubfraction]) SendClientMessage(i, 0xACE600FF, frmt_subfract_chat);
	}
	return true;
}

CMD:f(playerid, params[])
{
    if(!PI[playerid][pFraction])
		return 1;

	if(sscanf(params, "s[128]", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /f [текст]");

    if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);

	if(PI[playerid][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Используйте команду /fn");

	new
		fractionid = PI[playerid][pFraction]-1,
		rank = PI[playerid][pRank],
		frmt_fraction_chat[14 + 120];
		
	SetPlayerChatBubble(playerid, !"Сказал что-то в рацию", 0xDD90FFFF, 10.0, 3000);
	
	format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] %s %s[%d]: %s", gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);
	
	if(fractionid+1 == 10 && !PI[playerid][pSubfraction] && rank <= 9)
		format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] %s %s[%d]: %s", gPrezRankName[rank-1], PN(playerid), playerid, params[0]);

	else if(fractionid+1 == 8 && PI[playerid][pDivision] != 0)
		format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] [%s] %s %s[%d]: %s", gDivisionName[PI[playerid][pDivision]-1], gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);

	else if(fractionid+1 == 11 && PI[playerid][pDivision] != 0)
		format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] [%s] %s %s[%d]: %s", gTagName[PI[playerid][pDivision]-1], gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);

	SendFractionMessage(fractionid+1, 0x4682B4FF, frmt_fraction_chat);

	return true;
}
CMD:rn(playerid, params[])
{
	if(!PI[playerid][pFraction])
		return 1;

	if(PI[playerid][pFraction] != 10 && PI[playerid][pFraction] != 11 && !PI[playerid][pSubfraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам недоступна эта функция");

	if(IsAGang(playerid) || IsAMafia(playerid))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам недоступна эта функция");

    if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);

	if(sscanf(params, "s[128]", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /rn [текст]");

	new
		fractionid = PI[playerid][pFraction]-1,
		rank = PI[playerid][pRank],
		frmt_subfract_chat[128];

	format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] %s %s[%d]: (( %s ))", gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);

	if(fractionid+1 == 10 && !PI[playerid][pSubfraction] && rank <= 9)
		format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] %s %s[%d]: (( %s ))", gPrezRankName[rank-1], PN(playerid), playerid, params[0]);

	else if(fractionid+1 == 11 && PI[playerid][pDivision] != 0)
		format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] [%s] %s %s[%d]: (( %s ))", gTagName[PI[playerid][pDivision]-1], gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);
  	foreach(new i : Player)
	{
		if(IsPlayerConnected(i) && PI[i][pFraction] == fractionid+1 && PI[i][pSubfraction] == PI[playerid][pSubfraction]
		|| pTemp[i][pEarsFr] == fractionid+1 && pTemp[i][pEarsSub] == PI[playerid][pSubfraction]) SendClientMessage(i, 0xACE600FF, frmt_subfract_chat);
	}
	return true;
}

CMD:fn(playerid, params[])
{
    if(!PI[playerid][pFraction])
		return 1;

	if(sscanf(params, "s[128]", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /fn [текст]");

    if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);

	new
		fractionid = PI[playerid][pFraction]-1,
		rank = PI[playerid][pRank],
		frmt_fraction_chat[14 + 120];

	format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] %s %s[%d]: (( %s ))", gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);

	if(fractionid+1 == 10 && !PI[playerid][pSubfraction] && rank <= 9)
		format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] %s %s[%d]: (( %s ))", gPrezRankName[rank-1], PN(playerid), playerid, params[0]);

	else if(fractionid+1 == 8 && PI[playerid][pDivision] != 0)
		format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] [%s] %s %s[%d]: (( %s ))", gDivisionName[PI[playerid][pDivision]-1], gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);

	else if(fractionid+1 == 11 && PI[playerid][pDivision] != 0)
		format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] [%s] %s %s[%d]: (( %s ))", gTagName[PI[playerid][pDivision]-1], gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);

	SendFractionMessage(fractionid+1, 0x4682B4FF, frmt_fraction_chat);
	return true;
}
CMD:lmenu(playerid)
{
	if(!PI[playerid][pFraction]) return 1;
	if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11) return 1;
	if(PI[playerid][pFraction] >= 2 && PI[playerid][pFraction] <= 6)
	{
	    new rank = gGangStorageRank[PI[playerid][pFraction]-2]-1, fractionid = PI[playerid][pFraction]-1;
	    new frmt_lmenu_gang[390];
	        
		format(frmt_lmenu_gang, sizeof frmt_lmenu_gang, "{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников\n{FF7319}4.{FFFFFF} Отправить транспорт на базу организации\n{FF7319}5.{FFFFFF} Изменить названия рангов\n{FF7319}6.{FFFFFF} Доступ к общаку [{66CC00}%s{FFFFFF}]\n{FF7319}7.{FFFFFF} Открыть/Закрыть общак\n{FF7319}8.{FFFFFF} Объявление для сотрудников", gFractionRankName[fractionid][rank]);
		return ShowPlayerDialogEx(playerid, 913, DIALOG_STYLE_LIST, !"Меню лидера", frmt_lmenu_gang, !"OK", !"Отмена");
	}
	else if(IsAMafia(playerid))
	{
	    new rank = gMafiaStorageRank[PI[playerid][pFraction]-12],fractionid = PI[playerid][pFraction]-1;
	    new frmt_lmenu_mafia[360];

		format(frmt_lmenu_mafia, sizeof frmt_lmenu_mafia, "{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников\n{FF7319}4.{FFFFFF} Доступ к общаку [{66CC00}%s{FFFFFF}]\n{FF7319}5.{FFFFFF} Открыть/Закрыть общак\n{FF7319}6.{FFFFFF} Объявление для сотрудников\n{FF7319}7.{FFFFFF} Отправить транспорт на базу организации", gFractionRankName[fractionid][rank-1]);
		return ShowPlayerDialogEx(playerid, 5563, DIALOG_STYLE_LIST, !"Меню лидера", frmt_lmenu_mafia, !"OK", !"Отмена");
	}
	
	else if(PI[playerid][pFraction] == 11 && !PI[playerid][pSubfraction] && PI[playerid][pRank] > 9 && PI[playerid][pRank] != 11)
		return ShowPlayerDialogEx(playerid, 909, DIALOG_STYLE_LIST, !"Меню лидера", !"{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников\n{FF7319}4.{FFFFFF} Сотрудники в отпуске\n{FF7319}5.{FFFFFF} Подразделения\n{FF7319}6.{FFFFFF} Объявление для сотрудников", !"OK", !"Отмена");
	
	else if(PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
		return ShowPlayerDialogEx(playerid, 910, DIALOG_STYLE_LIST, !"Меню лидера", !"{FF7319}1.{FFFFFF} Список всех сотрудников\n{FF7319}2.{FFFFFF} Сотрудники в отпуске\n{FF7319}3.{FFFFFF} Объявление для сотрудников", !"OK", !"Отмена");

	else if(PI[playerid][pFraction] == 7 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
		return ShowPlayerDialogEx(playerid, 909, DIALOG_STYLE_LIST, !"Меню лидера", !"{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников", !"OK", !"Отмена");

	else if(PI[playerid][pFraction] == 10 && PI[playerid][pSubfraction] == 0 && PI[playerid][pRank] == 11)
		return ShowPlayerDialogEx(playerid, 909, DIALOG_STYLE_LIST, !"Меню лидера", !"{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников\n{FF7319}4.{FFFFFF} Сотрудники в отпуске", !"OK", !"Отмена");

	else if(PI[playerid][pFraction] == 1 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
		return ShowPlayerDialogEx(playerid, 909, DIALOG_STYLE_LIST, !"Меню лидера", !"{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников", !"OK", !"Отмена");

	else if(!PI[playerid][pSubfraction] && PI[playerid][pFraction] == 8 && PI[playerid][pRank] == 11)
		return ShowPlayerDialogEx(playerid, 909, DIALOG_STYLE_LIST, !"Меню лидера", !"{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников\n{FF7319}4.{FFFFFF} Подразделения", !"OK", !"Отмена");

	else if(!PI[playerid][pSubfraction] && PI[playerid][pFraction] == 9 && PI[playerid][pRank] == 11)
		return ShowPlayerDialogEx(playerid, 909, DIALOG_STYLE_LIST, !"Меню лидера", !"{FF7319}1.{FFFFFF} Назначить форму сотрудникам\n{FF7319}2.{FFFFFF} Назначить автомобили\n{FF7319}3.{FFFFFF} Список всех сотрудников\n{FF7319}4.{FFFFFF} Регулирование цен", !"OK", !"Отмена");
	return true;
}
CMD:gnews(playerid, params[])
{
	if(!PI[playerid][pFraction]) return 1;
	if(!IsALeader(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть лидером государственной организации");
	if(IsAMafia(playerid) || IsAGang(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть лидером государственной организации");
	extract params -> new string:text[144]; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /gnews [текст]");

	if(strlen(text) > 144)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный текст");

    if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);
		
	if(pTemp[playerid][pGNews] >= 4)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Гос. новости можно подавать 4 раза в минуту");

	totalstring[0] = 0;
	format(totalstring, 200, "[Гос.Новости] %s [%d]: %s", PN(playerid), playerid, text);
	SendClientMessageToAll(0x4466CCFF, totalstring);
	
	pTemp[playerid][pGNews]++;
	pTemp[playerid][pGNewsTime] = 180;
	
	return true;
}
CMD:d(playerid, params[])
{
	if(PI[playerid][pJob] != JOB_TRUCKER) return 1;
	if(sscanf(params, "s[119]", params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /d [текст]");
	if(strlen(params[0]) > 120) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный текст");
    if(PI[playerid][pMuteTime] > 0) return SendMuteMessage(playerid);
   	if(!PI[playerid][pTalkie]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет рации. Вы можете купить её в 24/7");
	if(PI[playerid][pJailTime] > 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в тюрьме");

	totalstring[0] = 0;
	format(totalstring, sizeof(totalstring), "[D] %s[%d]: %s",PN(playerid), playerid, params[0]);
	SendTruckMessage(0x228B22FF, totalstring);
	return true;
}
CMD:dn(playerid, params[])
{
	if(PI[playerid][pJob] != JOB_TRUCKER) return 1;
	if(sscanf(params, "s[119]", params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /dn [текст]");
	if(strlen(params[0]) > 120) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный текст");
    if(PI[playerid][pMuteTime] > 0) return SendMuteMessage(playerid);
    if(!PI[playerid][pTalkie]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет рации. Вы можете купить её в 24/7");
	if(PI[playerid][pJailTime] > 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в тюрьме");

	totalstring[0] = 0;
	format(totalstring, sizeof(totalstring), "[D] %s[%d]: (( %s ))",PN(playerid), playerid, params[0]);
	SendTruckMessage(0x228B22FF, totalstring);
	return true;
}
CMD:rc(playerid, params[])
{
	if(PI[playerid][pJob] != JOB_MECHANIC) return 1;
	if(sscanf(params, "s[119]", params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /rc [текст]");
	if(strlen(params[0]) > 120) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный текст");
    if(PI[playerid][pMuteTime] > 0) return SendMuteMessage(playerid);
   	if(!PI[playerid][pTalkie]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет рации. Вы можете купить её в 24/7");
	if(PI[playerid][pJailTime] > 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в тюрьме");

	totalstring[0] = 0;
	format(totalstring, sizeof(totalstring), "[RC] %s[%d]: %s",PN(playerid), playerid, params[0]);
	SendRepMessage(0xFFA07AFF, totalstring);
	return true;
}
CMD:rcn(playerid, params[])
{
	if(PI[playerid][pJob] != JOB_MECHANIC) return 1;
	if(sscanf(params, "s[119]", params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /rcn [текст]");
	if(strlen(params[0]) > 120) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный текст");
    if(PI[playerid][pMuteTime] > 0) return SendMuteMessage(playerid);
    if(!PI[playerid][pTalkie]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет рации. Вы можете купить её в 24/7");
	if(PI[playerid][pJailTime] > 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в тюрьме");

	totalstring[0] = 0;
	format(totalstring, sizeof(totalstring), "[RC] %s[%d]: (( %s ))",PN(playerid), playerid, params[0]);
	SendRepMessage(0xFFA07AFF, totalstring);
	return true;
}
CMD:l(playerid, params[])
{
	if(!PI[playerid][pFraction]) return 1;
	if(!IsALeader(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть лидером государственной организации");
	if(IsAMafia(playerid) || IsAGang(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть лидером государственной организации");
	if(sscanf(params, "s[101]", params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /l [текст]");
	if(strlen(params[0]) > 100) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный текст");
    if(PI[playerid][pMuteTime] > 0) return SendMuteMessage(playerid);
	if(PI[playerid][pJailTime] > 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в тюрьме");
	
	new
		fractionid = PI[playerid][pFraction]-1,
		rank = PI[playerid][pRank];
		
	new str[200];
	format(str, sizeof(str), "[L] %s %s[%d]: %s", gFractionRankName[fractionid][rank-1], PN(playerid), playerid, params[0]);
	SendLeaderMessage(0xFFEFADFF, str);
	return true;
}
CMD:advert(playerid)
{
	if(!PI[playerid][pFraction])
	    return 1;
	    
	new
	    fractionid = PI[playerid][pFraction]-1,
	    frid = GetSubfractionID(fractionid+1),
	    subid = PI[playerid][pSubfraction]-1;
	    
	if(!PI[playerid][pSubfraction])
	{
		if(!IsPlayerInRangeOfPoint(playerid, 50.0, gFractionSpawnC[fractionid][0], gFractionSpawnC[fractionid][1], gFractionSpawnC[fractionid][2]))
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на базе вашей организации");
	}
	else
	{
		if(!IsPlayerInRangeOfPoint(playerid, 50.0, gSubfractionSpawnC[frid][subid][0], gSubfractionSpawnC[frid][subid][1], gSubfractionSpawnC[frid][subid][2]))
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на базе вашей организации");
	}
	
	if(!strlen(gNotice[fractionid][subid+1][nName]))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Активных объявлений не найдено");

    new
        frmt_notice_text[155];

	format(frmt_notice_text, sizeof frmt_notice_text, "{FFFFFF}%s", gNotice[fractionid][subid+1][nText]);
    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, gNotice[fractionid][subid+1][nName], frmt_notice_text, !"ОК", !"");
    
	return true;
}
CMD:division(playerid, params[])
{
	if(PI[playerid][pFraction] != 8) return 1;

	if(PI[playerid][pRank] < 9) return 1;
		
	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/division [ID игрока]");

	if(!IsPlayerConnected(target) || playerid == target)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pFraction] != PI[playerid][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");

    if(PI[playerid][pSubfraction] > 0 || PI[playerid][pRank] != 11)
        if(PI[target][pSubfraction] != PI[playerid][pSubfraction])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей подфракции");

	if(PI[target][pRank] >= PI[playerid][pRank])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
	temp_division_receiver[playerid] = target + 1;

	new frmt_division_list[113];
	
	for(new i; i < 5; i++)
		format(frmt_division_list, sizeof frmt_division_list, "%s{FF7319}%d.{FFFFFF} %s\n", frmt_division_list, i+1, gDivisionName[i]);
		
	ShowPlayerDialogEx(playerid, 757, DIALOG_STYLE_LIST, !"Выберите подразделение", frmt_division_list, !"Выбор", !"Отмена");
	return true;
}
CMD:invite(playerid, params[])
{
	if(!PI[playerid][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");

	new fractionid = PI[playerid][pFraction]-1;

	if(!IsAbleToHire(playerid))
		return 1;

	if(sscanf(params, "u", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /invite [ID игрока]");

	if(PI[params[0]][pLevel] < 3)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока должен быть 3 уровень");

	if(!IsPlayerConnected(params[0]) && params[0] == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(PI[params[0]][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже состоит в организации");
		
	if(PI[params[0]][pv_Fraction])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске");
		
	if(PI[params[0]][pWarns])
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У игрока есть варн");

	if(PI[params[0]][pAdmin])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете принять во фракцию Администратора");

	if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		
	if(IsPlayerInAnyVehicle(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в машине");

	new
		frmt_invite_send[40 + MAX_PLAYER_NAME],
		frmt_invite_act[45 + MAX_PLAYER_NAME + 20];

	format(frmt_invite_send, sizeof frmt_invite_send, "Вы предложили %s вступить в вашу организацию", PN(params[0]));
	SendClientMessage(playerid, 0x269BD8FF, frmt_invite_send);

	format(frmt_invite_act, sizeof frmt_invite_act, "{FFFFFF}%s предложил Вам вступить в организацию \"%s\"", PN(playerid), gFractionName[fractionid]);

	temp_fraction_receiver[playerid] = params[0] + 1;
	temp_fraction_sender[params[0]] = playerid + 1;
	temp_fraction_id[params[0]] = fractionid+1;

	ShowPlayerDialogEx(params[0], 82, DIALOG_STYLE_MSGBOX, !"Вступление в организацию", frmt_invite_act, !"Вступить", !"Отмена");
	return true;
}
CMD:medcard(playerid, params[])
{
	if(PI[playerid][pFraction] != 1)
		return 1;

	new id;

    if(PI[playerid][pRank] < 3)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

    if(sscanf(params, "d", id))
		return SendClientMessage(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /medcard [ID]");

	if(!ProxDetectorS(3.0, playerid, id, 1))
		return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко от игрока");

	if(!IsPlayerConnected(id) || !IsPlayerLogged[id] || id == playerid)
		return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");
		
	if(PI[id][pMedCard])
		return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже имеется мед. карта");


	new
		string[120 + MAX_PLAYER_NAME + 7];

	format(string, sizeof string, "%s {269BD8}предложил Вам оформить мед. карту за {FF0000}$500{269BD8}.", PN(playerid));
	SendClientMessage(id, COLOR_WHITE, string);
	SendClientMessage(id, COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	format(string, sizeof string, "Вы предложили {FFFFFF}%s {269BD8}оформить мед. карту за {FF0000}$500{269BD8}", PN(id));
	SendClientMessage(playerid, 0x269BD8FF, string);


	temp_sellmed_receiver[playerid] = id+1;
	temp_sellmed_sender[id] = playerid+1;
	temp_sellmed_timer[id] = 60;
	return true;
}

CMD:heal(playerid, params[])
{
	if(PI[playerid][pFraction] != 1)
		return 1;

    if(PI[playerid][pRank] < 2)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
		target;
		
	if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /heal [ID игрока]");

	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	/*if(price < 1 || price > 150)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена от 1$ до 150$");*/

	new
	    carid = GetPlayerVehicleID(playerid);

    if(!IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 50.0, 693.6690, 1527.1469, 1306.1029) || IsPlayerInAnyVehicle(playerid) && VehicleInfo[carid][vTeam] != 1 && GetVehicleModel(carid) != 418)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в карете скорой помощи или в больнице");


	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pHeal] == 100.0)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не нуждается в лечении");

	new
		mes[128];

	format(mes, sizeof mes, "Вы предложили %s купить лекарство за 125$", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, mes);
	format(mes, sizeof mes, "{FFFFFF}%s предлагает Вам купить лекарство за 125$", PN(playerid));
	ShowPlayerDialogEx(target, 177, DIALOG_STYLE_MSGBOX, !"Лекарство", mes, !"Принять", !"Отмена");

	temp_heal_receiver[playerid] = target + 1;
	temp_heal_sender[target] = playerid + 1;
	//temp_heal_price[target] = price;

	return true;
}
CMD:inject(playerid, params[])
{
	if(PI[playerid][pFraction] != 1)
		return 1;

    if(PI[playerid][pRank] < 4)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
	new
		target;

	if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /inject [ID игрока]");

	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(!IsPlayerInDynamicArea(playerid, OperRoom))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в операционной");

	if(!IsPlayerInDynamicArea(target, OperRoom))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок должен быть в операционной");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(!temp_inject_need[target] || temp_inject_timer[target] != 0)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не нуждается в уколе");

    temp_inject_receiver[playerid] = target + 1;
    temp_inject_sender[target] = playerid + 1;
	temp_inject_count[target]++;

    Delete3DTextLabel(temp_disease_text[target]);

	GiveMoney(playerid, 200, "укол");
	
	new
	   	frmt_action[249];

	format(frmt_action, sizeof frmt_action, "%s сделал(а) укол {FF0000}%s{FFFFFF}. Выполнено: {FF0000}%d/5", PN(playerid), PN(target), temp_inject_count[target]);
	ProxDetector(25, target, frmt_action, COLOR_WHITE);

	if(temp_inject_count[target] < 5)
	{
		format(frmt_action, sizeof frmt_action, "{FF0000}%s{FFFFFF} сделал(а) Вам укол. Осталось: {FF0000}%d{FFFFFF} из {FF0000}5", PN(playerid), temp_inject_count[target]);
	    SendClientMessage(target, COLOR_WHITE, frmt_action);
	    temp_inject_timer[target] = 180;
		
	}
	else
	{
		format(frmt_action, sizeof frmt_action, "{FF0000}%s{FFFFFF} сделал(а) Вам укол. Курс лечения завершен", PN(playerid));
	    SendClientMessage(target, COLOR_WHITE, frmt_action);
	    temp_inject_need[target] = false;
		PI[target][pDisease] = 0;
		UpdatePlayerData(target, "Disease", PI[target][pDisease]);
	    temp_inject_receiver[playerid] = INVALID_PLAYER_ID;
	    temp_inject_sender[target] = INVALID_PLAYER_ID;
		temp_inject_count[target] = 0;
	}
	return true;
}

CMD:vac(playerid, params[])
{
	if(PI[playerid][pFraction] != 1)
		return 1;

    if(PI[playerid][pRank] < 4)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
		target;

	if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /vac [ID игрока]");

	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(!IsPlayerInRangeOfPoint(playerid, 50.0, 693.6690, 1527.1469, 1306.1029))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в больнице");
	    
	ShowPlayerDialogEx(playerid, 188, DIALOG_STYLE_LIST, !"Вакцинация", !"Выберите болезнь:\nАнгина\nБронхит\nЯзва желудка\nРевматизм\nАртрит\nАнемия", !"Выбор", !"Отмена");
	
	temp_vac_receiver[playerid] = target + 1;
	
	return true;
}
CMD:setsex(playerid, params[])
{
	if(PI[playerid][pFraction] != 1)
		return 1;

    if(PI[playerid][pRank] < 6)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
		target;

	if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /setsex [ID игрока]");
		
	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(!IsPlayerInDynamicArea(playerid, OperRoom))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в операционной");

	if(!IsPlayerInDynamicArea(target, OperRoom))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок должен быть в операционной");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(temp_setsex_sender[target] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть действующее предложение");
	    
	new
		mes[128];

	format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} пройти операцию по смене пола на {FFFFFF}%s", PN(target), PI[target][pSex] == 2 ? ("Мужской") : ("Женский"));
	SendClientMessage(playerid, 0x269BD8FF, mes);

	format(mes, sizeof mes, "{FFFFFF}%s{269BD8} предлагает Вам пройти операцию по смене пола на {FFFFFF}%s", PN(playerid), PI[target][pSex] == 2 ? ("Мужской") : ("Женский"));
	SendClientMessage(target, 0x269BD8FF, mes);
	
	SendClientMessage(target, 0x269BD8FF, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");


	temp_setsex_receiver[playerid] = target + 1;
	temp_setsex_sender[target] = playerid + 1;
	
	return true;
}
CMD:rang(playerid, params[])
{
	if(!PI[playerid][pFraction] )
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации.");
		
	new fractionid = PI[playerid][pFraction]-1;
	if(!IsAbleToGiveRank(playerid))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
	if(sscanf(params, "u", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /rang [ID игрока]");
		
	if(!IsPlayerConnected(params[0]) || params[0] == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
		
	if(PI[params[0]][pFraction] != PI[playerid][pFraction] || PI[params[0]][pSubfraction] != PI[playerid][pSubfraction] || pTemp[params[0]][pTempLeader])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");
		
    if(PI[playerid][pSubfraction] > 0)
        if(PI[params[0]][pSubfraction] != PI[playerid][pSubfraction])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей подфракции");
		
	if(PI[params[0]][pRank] >= PI[playerid][pRank])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
	if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(IsPlayerInAnyVehicle(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в машине");

		
	temp_setrang_target[playerid] = params[0] + 1;
	
	new
		frmt_rang_act[512],
		m = PI[playerid][pRank] - 1;
		
    if(PI[playerid][pFraction] == 10 && !PI[playerid][pSubfraction]) m = 9;
    for(new i; i < m; i++)
    {
        if(PI[params[0]][pRank] == i+1)
        {
            if(PI[params[0]][pFraction] == 10 && !PI[params[0]][pSubfraction])
            	format(frmt_rang_act, sizeof frmt_rang_act, "%s{66CC00}%s\n", frmt_rang_act, gPrezRankName[i]);
            else format(frmt_rang_act, sizeof frmt_rang_act, "%s{66CC00}%s\n", frmt_rang_act, gFractionRankName[fractionid][i]);
        }
        else
        {
            if(PI[params[0]][pFraction] == 10 && !PI[params[0]][pSubfraction])
            	format(frmt_rang_act, sizeof frmt_rang_act, "%s%s\n", frmt_rang_act, gPrezRankName[i]);
            else format(frmt_rang_act, sizeof frmt_rang_act, "%s%s\n", frmt_rang_act, gFractionRankName[fractionid][i]);
        }
    }
    
	ShowPlayerDialogEx(playerid, 83, DIALOG_STYLE_LIST, !"Смена ранга", frmt_rang_act, !"Сменить", !"Выход");
	return true;
}
CMD:uninvite(playerid, params[])
{
	if(!PI[playerid][pFraction] )
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");
		
	if(!IsAbleToUninvite(playerid))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
	if(sscanf(params, "us[32]", params[0],params[1]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /uninvite [ID игрока] [Причина]");

	if(strlen(params[1]) < 2 || strlen(params[1]) > 32)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Причина от 2 до 32 символов");
		
	if(!IsPlayerConnected(params[0]) || params[0] == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
		
	if(PI[params[0]][pFraction] != PI[playerid][pFraction] || pTemp[params[0]][pTempLeader])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");
		
    if(PI[playerid][pSubfraction] > 0 || PI[playerid][pRank] != 11)
        if(PI[params[0]][pSubfraction] != PI[playerid][pSubfraction])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей подфракции");

	if(PI[params[0]][pRank] >= PI[playerid][pRank])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
 	new
	 	query_uptd[210];

	format(query_uptd, sizeof query_uptd, "UPDATE `accounts` SET `Fraction` = '0', `Rank` = '0', `FractionSkin` = '0', `Subfraction` = '0', `DateInvite` = '00-00-0000', `LastRank` = '00-00-0000', `FWarns` = '0' WHERE `ID` = '%d'", PI[params[0]][pID]);
 	mysql_tquery(mysql, query_uptd);
 	
	SetPlayerHealth(params[0], 0);
	resetgun(params[0]);
	
	if(PI[params[0]][pHouseKey] != 0)
	{
		new houseid = PI[params[0]][pHouseKey] - 1;
		new slot;
		for(new i;i<4;i++)
		{
			if(HouseInfo[houseid][hSkin][i] == PI[params[0]][pFractionSkin])
			{
				slot = i;
				break;
			}
			HouseInfo[houseid][hSkin][slot] = 0;
			UpdateHouseDress(houseid);
		}
	}
			
	PI[params[0]][pFraction] = 0;
	PI[params[0]][pRank] = 0;
	PI[params[0]][pFractionSkin] = 0;
	PI[params[0]][pSubfraction] = 0;
	PI[params[0]][pFWarns] = 0;
	PI[params[0]][pDivision] = 0;
	UpdatePlayerData(params[0], "Division", PI[params[0]][pDivision]);
	SetString(PI[params[0]][pDateInvite], "00-00-0000");
	SetString(PI[params[0]][pLastRank], "00-00-0000");
	PI[params[0]][pPointsOrg] = 0;
	UpdatePlayerData(params[0], "PointsOrg", PI[params[0]][pPointsOrg]);
	
	SetPlayerColor(params[0], 0xFFFFFF11);
	SetPlayerSkin(params[0], PI[params[0]][pSkin]);

	new mes[128];
	format(mes, sizeof mes, "%s уволил Вас из организации. Причина: %s", PN(playerid), params[1]);
	SendClientMessage(params[0], 0xFF182DFF, mes);
	format(mes, sizeof mes, "%s был уволен из организации. Причина: %s", PN(params[0]), params[1]);
	SendClientMessage(playerid, 0x269BD8FF, mes);
	
	format(mes, sizeof mes, "%s уволил %s из организации. Причина: %s", PN(playerid), PN(params[0]), params[1]);
  	foreach(new i : Player)
	{
		if(IsPlayerConnected(i) && PI[i][pFraction] == PI[playerid][pFraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
			SendClientMessage(i, 0xACE600FF, mes);
	}
	
	return true;
}
CMD:leave(playerid, params[])
{
	if(!PI[playerid][pDash])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет улучшения {AFAFAF}\"Решительность\"");
		
	if(!PI[playerid][pFraction] )
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");

	if(IsAbleToUninvite(playerid))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете уволиться из организации");

	extract params -> new string:warning[32]; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /leave [Причина]");

	if(strlen(warning) > 32)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинная причина");

	new mes[128];

	format(mes, sizeof mes, "%s покинул организацию. Причина: %s", PN(playerid), warning);

  	foreach(new i : Player)
	{
		if(IsPlayerConnected(i) && PI[i][pFraction] == PI[playerid][pFraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
			SendClientMessage(i, 0xACE600FF, mes);
	}
	
 	new
	 	query_uptd[210];

	format(query_uptd, sizeof query_uptd, "UPDATE `accounts` SET `Fraction` = '0', `Rank` = '0', `FractionSkin` = '0', `Subfraction` = '0', `DateInvite` = '00-00-0000', `LastRank` = '00-00-0000', `FWarns` = '0' WHERE `ID` = '%d'", PI[playerid][pID]);
 	mysql_tquery(mysql, query_uptd);

	SetArmour(playerid, 0);
	resetgun(playerid);
	
	PI[playerid][pFraction] = 0;
	PI[playerid][pRank] = 0;
	PI[playerid][pFractionSkin] = 0;
	PI[playerid][pSubfraction] = 0;
	PI[playerid][pFWarns] = 0;
	PI[playerid][pDivision] = 0;
	UpdatePlayerData(playerid, "Division", PI[playerid][pDivision]);
	SetString(PI[playerid][pDateInvite], "00-00-0000");
	SetString(PI[playerid][pLastRank], "00-00-0000");
	PI[playerid][pPointsOrg] = 0;
	UpdatePlayerData(playerid, "PointsOrg", PI[playerid][pPointsOrg]);
			
	SetPlayerColor(playerid, 0xFFFFFF11);
	SetPlayerSkin(playerid, PI[playerid][pSkin]);
	
	SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы покинули организацию");


	return true;
}
CMD:uninviteoff(playerid, params[])
{
    if(!PI[playerid][pFraction] ) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");
    if(PI[playerid][pRank] < 9) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

    new nickname[MAX_PLAYER_NAME], warning[33];

    if(sscanf(params, "s[24]s[33]", nickname, warning)) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /uninviteoff [Ник игрока] [Причина]");
    if(strlen(nickname) > 24) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный никнейм");
    if(strlen(warning) < 2 || strlen(warning) > 32) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Причина от 2 до 32 символов");

    new query_getid[92 + MAX_PLAYER_NAME];
    format(query_getid, sizeof query_getid, "SELECT `ID`,`Fraction`,`Rank`,`Subfraction` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", nickname);
    new Cache:getid = mysql_query(mysql, query_getid);

    if(!cache_get_row_count(mysql)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный никнейм"), cache_delete(getid, mysql);
    if(GetPlayerID(nickname) != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в сети");

    new id, fraction, rank, subfraction;

    id = cache_get_row_int(0, 0, mysql);
    fraction = cache_get_row_int(0, 1, mysql);
    rank = cache_get_row_int(0, 2, mysql);
    subfraction = cache_get_row_int(0, 3, mysql);

    if(fraction != PI[playerid][pFraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок с данным никнеймом не состоит в Вашей организации"), cache_delete(getid, mysql);
    if(rank >= PI[playerid][pRank]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен для увольнения данного игрока"), cache_delete(getid, mysql);
    if(subfraction && (subfraction != PI[playerid][pSubfraction] && PI[playerid][pSubfraction])) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок с данным никнеймом не состоит в Вашей организации"), cache_delete(getid, mysql);

    cache_delete(getid, mysql);

    new query_uninvite[195];
    format(query_uninvite, sizeof query_uninvite, "UPDATE `accounts` SET `Fraction` = '0', `Rank` = '0', `FractionSkin` = '0', `Subfraction` = '0', `DateInvite` = '00-00-0000', `LastRank` = '00-00-0000', `FWarns` = '0' WHERE `ID` = '%d'", id);
    new Cache:result = mysql_query(mysql, query_uninvite);
    if(!cache_affected_rows(mysql)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок с данным никнеймом не состоит в Вашей организации"), cache_delete(result, mysql);

    cache_delete(result, mysql);

    new frmt_msg_uninviteoff[125];
    format(frmt_msg_uninviteoff, sizeof frmt_msg_uninviteoff, "%s уволил %s из организации в оффлайне. Причина: %s", PN(playerid), nickname, warning);
    foreach(new i : Player)
    {
        if(PI[i][pFraction] == PI[playerid][pFraction])
        {
            if(PI[playerid][pSubfraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
            {
                SendClientMessage(i, 0x4682B4AA, frmt_msg_uninviteoff);
                continue;
            }
            if(!PI[playerid][pSubfraction])
            {
                SendClientMessage(i, 0x4682B4AA, frmt_msg_uninviteoff);
                continue;
            }
        }
    }
    return true;
}
CMD:unvacation(playerid, params[])
{
	if(!PI[playerid][pFraction] || IsAGang(playerid) || IsAMafia(playerid) )
		return 1;
		
	if((PI[playerid][pFraction] == 1 || PI[playerid][pFraction] >= 7 && PI[playerid][pFraction] <= 9) && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
		return 1;
		
	new fractionid = PI[playerid][pFraction]-1;

	if(PI[playerid][pRank] < 10)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(sscanf(params, "u", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /unvacation [ID игрока]");

	if(PI[params[0]][pLevel] < 3)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока должен быть 3 уровень");

	if(!IsPlayerConnected(params[0]) && params[0] == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
		
	if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[params[0]][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже состоит в организации");

	if(!PI[params[0]][pv_Fraction])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не находится в отпуске");

	if(PI[params[0]][pv_Fraction] != PI[playerid][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске другой организации");

	if(PI[params[0]][pWarns])
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У игрока есть варн");

	if(PI[params[0]][pAdmin])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок администратор");

	if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(IsPlayerInAnyVehicle(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в машине");

	new
		frmt_invite_send[40 + MAX_PLAYER_NAME],
		frmt_invite_act[45 + MAX_PLAYER_NAME + 20];

	format(frmt_invite_send, sizeof frmt_invite_send, "Вы предложили %s выйти с отпуска", PN(params[0]));
	SendClientMessage(playerid, 0x269BD8FF, frmt_invite_send);

	format(frmt_invite_act, sizeof frmt_invite_act, "%s предложил Вам вернуться в организацию \"%s\"", PN(playerid), gFractionName[fractionid]);

	temp_unvac_receiver[playerid] = params[0] + 1;
	temp_unvac_sender[params[0]] = playerid + 1;

	ShowPlayerDialogEx(params[0], 81, DIALOG_STYLE_MSGBOX, !"Выход с отпуска", frmt_invite_act, !"Вернуться", !"Отмена");
	return true;
}
CMD:vacation(playerid, params[])
{
	if(!PI[playerid][pFraction] || IsAGang(playerid) || IsAMafia(playerid) )
		return 1;

	if((PI[playerid][pFraction] == 1 || PI[playerid][pFraction] >= 7 && PI[playerid][pFraction] <= 9) && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
		return 1;


	if(PI[playerid][pRank] < 10)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    target, days;

	if(sscanf(params, "ud", target, days))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /vacation [ID игрока] [Кол-во дней]");

	if(days < 1 || days > 30)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}От 1 до 30 дней");
	    
	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
		
	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pFraction] != PI[playerid][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");

    if(PI[playerid][pSubfraction] > 0 || PI[playerid][pRank] != 11)
        if(PI[target][pSubfraction] != PI[playerid][pSubfraction])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей подфракции");

	if(PI[target][pRank] >= PI[playerid][pRank])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
		msg[165];

	format(msg, sizeof msg, "%s {269BD8}предложил Вам взять отпуск на {33AA33}%d{269BD8} %s.", PN(playerid), days, Declension_GetDays(days));
	SendClientMessage(target, COLOR_WHITE, msg);
	SendClientMessage(target, COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	format(msg, sizeof msg, "Вы предложили {FFFFFF}%s {269BD8} взять отпуск на {33AA33}%d{269BD8} %s", PN(target), days, Declension_GetDays(days));
	SendClientMessage(playerid, 0x269BD8FF, msg);


	temp_vacation_receiver[playerid] = target + 1;
	temp_vacation_sender[target] = playerid + 1;
	temp_vacation_days[target] = days;
    temp_vacation_timer[target] = 60;

	return true;
}
CMD:fwarn(playerid, params[])
{
	if(!PI[playerid][pFraction] || IsAGang(playerid) || IsAMafia(playerid) )
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");

	if(PI[playerid][pRank] < 9)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    target, warning[33];
	    
	if(sscanf(params, "us[33]", target, warning))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /fwarn [ID игрока] [Причина]");

	if(strlen(warning) < 2 || strlen(warning) > 32)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Причина от 2 до 32 символов");

	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(PI[target][pFraction] != PI[playerid][pFraction] || pTemp[target][pTempLeader])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");

    if(PI[playerid][pSubfraction] > 0 || PI[playerid][pRank] != 11)
        if(PI[target][pSubfraction] != PI[playerid][pSubfraction])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей подфракции");

	if(PI[target][pRank] >= PI[playerid][pRank])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
	PI[target][pFWarns]++;
	UpdatePlayerData(target, "FWarns", PI[target][pFWarns]);

	new mes[128];
	format(mes, sizeof mes, "%s выдал вам выговор (%d/3). Причина: %s", PN(playerid), PI[target][pFWarns], warning);
	SendClientMessage(target, 0xFF182DFF, mes);

	format(mes, sizeof mes, "%s получил выговор (%d/3) от %s. Причина: %s", PN(target), PI[target][pFWarns], PN(playerid), warning);
  	foreach(new i : Player)
	{
		if(PI[i][pFraction] == PI[playerid][pFraction])
		{
			if(PI[playerid][pSubfraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
			{
				SendClientMessage(i, 0x4682B4AA, mes);
				continue;
			}
			if(!PI[playerid][pSubfraction])
	 		{
				SendClientMessage(i, 0x4682B4AA, mes);
			    continue;
			}
		}
	}
	
	if(PI[target][pFWarns] == 3)
	{
	 	new
		 	query_uptd[210];

		format(query_uptd, sizeof query_uptd, "UPDATE `accounts` SET `Fraction` = '0', `Rank` = '0', `FractionSkin` = '0', `Subfraction` = '0', `DateInvite` = '00-00-0000', `LastRank` = '00-00-0000', `FWarns` = '0' WHERE `ID` = '%d'", PI[target][pID]);
	 	mysql_tquery(mysql, query_uptd);

		SetPlayerHealth(target, 0);
		resetgun(target);

		PI[target][pFraction] = 0;
		PI[target][pRank] = 0;
		PI[target][pFWarns] = 0;
		PI[target][pFractionSkin] = 0;
		PI[target][pSubfraction] = 0;
		SetString(PI[target][pDateInvite], "00-00-0000");
		SetString(PI[target][pLastRank], "00-00-0000");
		PI[target][pDivision] = 0;
		UpdatePlayerData(target, "Division", PI[target][pDivision]);
		SetPlayerColor(target, 0xFFFFFF11);
		SetPlayerSkin(target, PI[target][pSkin]);

		format(mes, sizeof mes, "%s уволил Вас из организации. Причина: %s", PN(playerid), warning);
		SendClientMessage(target, 0xFF182DFF, mes);

		format(mes, sizeof mes, "%s уволил %s из организации. Причина: %s", PN(playerid), PN(target), warning);
   		foreach(new i : Player)
		{
			if(PI[i][pFraction] == PI[playerid][pFraction])
			{
				if(PI[playerid][pSubfraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
				{
					SendClientMessage(i, 0x4682B4AA, mes);
					continue;
				}
				if(!PI[playerid][pSubfraction])
		 		{
					SendClientMessage(i, 0x4682B4AA, mes);
				    continue;
				}
			}
		}
	}
	return true;
}
CMD:unfwarn(playerid, params[])
{
	if(!PI[playerid][pFraction] || IsAGang(playerid) || IsAMafia(playerid) )
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");

	if(PI[playerid][pRank] < 9)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    target;

	if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /unfwarn [ID игрока]");

	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(PI[target][pFraction] != PI[playerid][pFraction] || pTemp[target][pTempLeader])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");

    if(PI[playerid][pSubfraction] > 0 || PI[playerid][pRank] != 11)
        if(PI[target][pSubfraction] != PI[playerid][pSubfraction])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей подфракции");

	if(PI[target][pRank] >= PI[playerid][pRank])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
		
	if(!PI[target][pFWarns])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет выговоров");

	PI[target][pFWarns]--;
	UpdatePlayerData(target, "FWarns", PI[target][pFWarns]);

	new mes[128];
	format(mes, sizeof mes, "%s снял вам выговор (%d/3)", PN(playerid), PI[target][pFWarns]);
	SendClientMessage(target, 0xFF182DFF, mes);
	format(mes, sizeof mes, "Вы сняли выговор игроку %s (%d/3)", PN(target), PI[target][pFWarns]);
	SendClientMessage(playerid, 0x269BD8FF, mes);
	return true;
}
CMD:fwarnoff(playerid, params[])
{
    if(!PI[playerid][pFraction] || IsAGang(playerid) || IsAMafia(playerid) ) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");
    if(PI[playerid][pRank] < 9) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

    new nickname[MAX_PLAYER_NAME], warning[33];
    if(sscanf(params, "s[24]s[33]", nickname, warning)) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /fwarnoff [Ник игрока] [Причина]");
    if(strlen(nickname) > 24) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный никнейм");
    if(strlen(warning) < 2 || strlen(warning) > 32) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Причина от 2 до 32 символов");

    new query_getid[102 + MAX_PLAYER_NAME];
    format(query_getid, sizeof query_getid, "SELECT `ID`,`FWarns`,`Fraction`,`Rank`,`Subfraction` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", nickname);
    new Cache:getid = mysql_query(mysql, query_getid);

    if(!cache_get_row_count(mysql)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный никнейм"), cache_delete(getid, mysql);
    if(GetPlayerID(nickname) != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в сети");

    new fwarns, id, fraction, rank, subfraction;

    id = cache_get_row_int(0, 0, mysql);
    fwarns = cache_get_row_int(0, 1, mysql);
    fraction = cache_get_row_int(0, 2, mysql);
    rank = cache_get_row_int(0, 3, mysql);
    subfraction = cache_get_row_int(0, 4, mysql);

    if(fraction != PI[playerid][pFraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок с данным никнеймом не состоит в Вашей организации"), cache_delete(getid, mysql);
    if(rank >= PI[playerid][pRank]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен для выдачи выговору данному игрока"), cache_delete(getid, mysql);
    if(subfraction && (subfraction != PI[playerid][pSubfraction] && PI[playerid][pSubfraction])) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок с данным никнеймом не состоит в Вашей организации"), cache_delete(getid, mysql);

    cache_delete(getid, mysql);

    new query_fwarn[71];
    format(query_fwarn, sizeof query_fwarn, "UPDATE `accounts` SET `FWarns` = `FWarns`+1 WHERE `ID` = '%d'", id);
    new Cache:result = mysql_query(mysql, query_fwarn);

    if(!cache_affected_rows(mysql)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка при выдаче выговора в оффлайне"), cache_delete(result, mysql);

    cache_delete(result, mysql);

    new frmt_msg_fwarnoff[124];
    format(frmt_msg_fwarnoff, sizeof frmt_msg_fwarnoff, "%s выдал выговор %s (%d/3) в оффлайне. Причина: %s", PN(playerid), nickname, fwarns+1, warning);
    foreach(new i : Player)
    {
        if(PI[i][pFraction] == PI[playerid][pFraction])
        {
            if(PI[playerid][pSubfraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
            {
                SendClientMessage(i, 0x4682B4AA, frmt_msg_fwarnoff);
                continue;
            }
            if(!PI[playerid][pSubfraction])
            {
                SendClientMessage(i, 0x4682B4AA, frmt_msg_fwarnoff);
                continue;
            }
        }
    }
    if(fwarns+1 == 3)
    {
        new query_uninvite[195];
        format(query_uninvite, sizeof query_uninvite, "UPDATE `accounts` SET `Fraction` = '0', `Rank` = '0', `FractionSkin` = '0', `Subfraction` = '0', `DateInvite` = '00-00-0000', `LastRank` = '00-00-0000', `FWarns` = '0' WHERE `ID` = '%d'", id);
        new Cache:uninvite = mysql_query(mysql, query_uninvite);
        if(!cache_affected_rows(mysql)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка при увольнении"), cache_delete(uninvite, mysql);

        cache_delete(uninvite, mysql);

        new frmt_msg_uninviteoff[125];
        format(frmt_msg_uninviteoff, sizeof frmt_msg_uninviteoff, "%s уволил %s из организации в оффлайне. Причина: %s", PN(playerid), nickname, warning);
        foreach(new i : Player)
        {
            if(PI[i][pFraction] == PI[playerid][pFraction])
            {
                if(PI[playerid][pSubfraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
                {
                    SendClientMessage(i, 0x4682B4AA, frmt_msg_uninviteoff);
                    continue;
                }
                if(!PI[playerid][pSubfraction])
                {
                    SendClientMessage(i, 0x4682B4AA, frmt_msg_uninviteoff);
                    continue;
                }
            }
        }
    }
    return true;
}
CMD:unfwarnoff(playerid, params[])
{
	if(!PI[playerid][pFraction] || IsAGang(playerid) || IsAMafia(playerid) )
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в организации");

	if(PI[playerid][pRank] < 9)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
		nickname[MAX_PLAYER_NAME];

	if(sscanf(params, "s[24]", nickname))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /unfwarnoff [Ник игрока]");

	if(strlen(nickname) > 24)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный никнейм");

    new
        query_getid[70 + MAX_PLAYER_NAME],
		fwarns;

	format(query_getid, sizeof query_getid, "SELECT `ID`, `FWarns` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", nickname);
	new Cache:getid = mysql_query(mysql, query_getid);

	fwarns = cache_get_row_int(0, 1, mysql);

	if(!cache_get_row_count(mysql))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный никнейм"), cache_delete(getid, mysql);

	if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в сети");
		
	if(!fwarns)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет выговоров");
		
	cache_delete(getid, mysql);

	new
	    query_fwarn[286];

	if(PI[playerid][pSubfraction] && PI[playerid][pRank] > 9) format(query_fwarn, sizeof query_fwarn, "UPDATE `accounts` SET `FWarns` = `FWarns`-1 WHERE `NickName` = '%s' AND `Fraction`='%d' AND `Subfraction`='%d' AND `Rank`<'%d'", nickname, PI[playerid][pFraction], PI[playerid][pSubfraction], PI[playerid][pRank]);
	else if(!PI[playerid][pSubfraction] && PI[playerid][pRank] == 11) format(query_fwarn, sizeof query_fwarn, "UPDATE `accounts` SET `FWarns` = `FWarns`-1 WHERE `NickName` = '%s' AND `Fraction`='%d'", nickname, PI[playerid][pFraction]);
	else if(!PI[playerid][pSubfraction] && PI[playerid][pRank] > gFractionRankCount[PI[playerid][pFraction]-1]) format(query_fwarn, sizeof query_fwarn, "UPDATE `accounts` SET `FWarns` = `FWarns`-1 WHERE `NickName` = '%s' AND `Fraction`='%d' AND `Rank`<'%d'", nickname, PI[playerid][pFraction], PI[playerid][pRank]);
	new Cache:result = mysql_query(mysql, query_fwarn);

	if(!cache_affected_rows(mysql)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок с данным никнеймом не состоит в Вашей организации"), cache_delete(result, mysql);

	cache_delete(result, mysql);

	new mes[128];
	format(mes, sizeof mes, "Вы сняли в оффлайне выговор игроку %s (%d/3)", nickname, fwarns-1);
	SendClientMessage(playerid, 0x4682B4AA, mes);


	return true;
}
CMD:makegun(playerid)
{
	if(!IsAGang(playerid) && PI[playerid][pFraction] != 7)
	    return 1;

	if(PI[playerid][pGunLic] != YES_LICENSE) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет лицензии на оружие");
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Выйдите из машины");

	if(IsAGang(playerid))
	{
		for(new i; i < MAX_GANGZONE; i++)
		{
			if(PlayerToKvadrat(playerid, GZMZ[i][gCoords][0], GZMZ[i][gCoords][1], GZMZ[i][gCoords][2], GZMZ[i][gCoords][3]))
			{
			    if(GZMZ[i][gGang] == PI[playerid][pFraction])
					return ShowMakeGunList(playerid);

			    break;
			}
		}
		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться на своей территории");
	}
	else if(PI[playerid][pFraction] == 7)
	{
	    ShowMakeGunList(playerid);
	}
	return true;
}
CMD:givegun(playerid, params[])
{
	if(!IsAGang(playerid) && !IsAMafia(playerid))
	    return 1;

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/givegun [ID игрока]");

	if(!IsPlayerConnected(target) || playerid == target)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");
		
	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		
	new
		weaponid = GetPlayerWeapon(playerid),
		ammo = GetPlayerAmmo(playerid);
		
	if(!weaponid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Возьмите в руку то оружие, которое хотите передать");
		
	SetPlayerAmmo(playerid, weaponid, 0);
	SetPlayerArmedWeapon(playerid, 0);
	_GiveGun(target, weaponid, ammo);
    PI[playerid][pLastGun] = 0;
	PI[playerid][pLastAmmo] = 0;
		
	new
		mes[128];
		
	format(mes, sizeof mes, "%s передал оружие %s", PN(playerid), PN(target));
    ProxDetector(25, playerid, mes, COLOR_ME);
    
    format(mes, sizeof mes, "Вы передали свое оружие %s", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, mes);
    format(mes, sizeof mes, "%s передал Вам свое оружие", PN(playerid));
	SendClientMessage(target, 0x269BD8FF, mes);

	return true;
}
CMD:giveguns(playerid, params[])
{
	if(!IsAGang(playerid) || !IsAMafia(playerid)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/giveguns [id игрока] [количество]");
	else if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы далеко друг от друга");
	else if(params[0] == INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в сети");
	else if(params[0] == playerid) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы указали свой ID");
	else if(!IsPlayerLogged[params[0]]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не авторизовался");
	else if(params[1] < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное количество!");
	else if(PI[playerid][pPackets] < params[1]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет столько ед. оружия!");
	else if(PI[params[0]][pPackets]+params[1] > 500 && !PI[playerid][pBag]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже достаточно ед. оружия!");
	else if(PI[params[0]][pPackets]+params[1] > 1000 && PI[playerid][pBag]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже достаточно ед. оружия!");
	PI[playerid][pPackets] -= params[1];
	PI[params[0]][pPackets] += params[1];
	UpdatePlayerData(playerid, "Packets", PI[playerid][pPackets]);
	UpdatePlayerData(params[0], "Packets", PI[params[0]][pPackets]);
	new string[128];
	format(string, sizeof(string), "%s передал%s ед. оружия %s", PN(playerid), (PI[playerid][pSex]==1)?(""):("а"),PN(params[0]));
	ProxDetector(25, playerid, string, COLOR_ME);
	format(string, sizeof(string), "{7AC71F}[Успешно] {FFFFFF}Вы передали {FFC800}%s %d {ffffff}ед. оружия", PN(params[0]), params[1]);
	SendClientMessage(playerid, 0x7AC71FFF, string);
	format(string, sizeof(string), "{7AC71F}[Успешно] {FFC800}%s {ffffff}передал%s Вам {FFC800}%d {ffffff}ед. оружия", PN(playerid), (PI[playerid][pSex]==1)?(""):("а"), params[1]);
	SendClientMessage(params[0], 0x7AC71FFF, string);
	return 1;
}
CMD:givepatr(playerid, params[])
{
    if(!IsAGang(playerid) || !IsAMafia(playerid)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/givepatr [id игрока] [количество]");
	else if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы далеко друг от друга");
	else if(params[0] == INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в сети");
	else if(!IsPlayerLogged[params[0]]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не авторизовался");
	else if(params[1] < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное количество!");
	else if(params[0] == playerid) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы указали свой ID");
	else if(PI[playerid][pMats] < params[1]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет столько ед. оружия!");
	else if(PI[params[0]][pMats]+params[1] > 500 && !PI[playerid][pBag]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже достаточно ед. оружия!");
	else if(PI[params[0]][pMats]+params[1] > 1000 && PI[playerid][pBag]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже достаточно ед. оружия!");
	PI[playerid][pMats] -= params[1];
	PI[params[0]][pMats] += params[1];
	UpdatePlayerData(playerid, "Mats", PI[playerid][pMats]);
	UpdatePlayerData(params[0], "Mats", PI[params[0]][pMats]);
	new string[128];
	format(string, sizeof(string), "%s передал%s патроны %s", PN(playerid), (PI[playerid][pSex]==1)?(""):("а"),PN(params[0]));
	ProxDetector(25, playerid, string, COLOR_ME);
	format(string, sizeof(string), "{7AC71F}[Успешно] {FFFFFF}Вы передали {FFC800}%s %d {ffffff}пт", PN(params[0]), params[1]);
	SendClientMessage(playerid, 0x7AC71FFF, string);
	format(string, sizeof(string), "{7AC71F}[Успешно] {FFC800}%s {ffffff}передал%s Вам {FFC800}%d {ffffff}пт", PN(playerid), (PI[playerid][pSex]==1)?(""):("а"), params[1]);
	SendClientMessage(params[0], 0x7AC71FFF, string);
	return 1;
}
CMD:sellgun(playerid, params[])
{
	if(!IsAGang(playerid))
	    return 1;

	new
	    bool:check;
	    
	for(new i; i < MAX_GANGZONE; i++)
	{
		if(PlayerToKvadrat(playerid, GZMZ[i][gCoords][0], GZMZ[i][gCoords][1], GZMZ[i][gCoords][2], GZMZ[i][gCoords][3]))
		{
		    check = true;
		    
			extract params -> new player:target, patrs, price; else
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/sellgun [ID игрока] [Кол-во патронов] [Цена]");

			if(PI[playerid][pGunLic] != YES_LICENSE)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет лицензии на оружие");
		        
			if(!IsPlayerConnected(target) || playerid == target)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

			if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

			if(patrs < 1 || patrs > 150)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное количество патронов (от 1 до 150)");

			if(price < 1 || price > 30000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная цена (от 1$ до 30000$)");

            new
				weaponid = GetPlayerWeapon(playerid),
            	ammo = GetPlayerAmmo(playerid);
            	
            if(!weaponid)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Возьмите в руку то оружие, которое хотите продать");
				
            if(ammo < patrs)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно патронов");

			temp_sellgun_receiver[playerid] = target + 1;
			temp_sellgun_sender[target] = playerid + 1;
			temp_sellgun_id[target] = weaponid;
			temp_sellgun_ammo[target] = patrs;
			temp_sellgun_price[target] = price;

           	new
			   	weapname[24];

			GetWeaponName(weaponid, weapname, 24);

			new
				mes[162];
				
		    format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} купить у Вас {FFFFFF}%s{269BD8} за {FFFFFF}%d${269BD8}. Патронов: {FFFFFF}%d", PN(target), weapname, price, patrs);
			SendClientMessage(playerid, 0x269BD8FF, mes);

			format(mes, sizeof mes, "%s{269BD8} предлагает Вам приобрести {FFFFFF}%s{269BD8} за {FFFFFF}%d${269BD8}. Патронов: {FFFFFF}%d", PN(playerid), weapname, price, patrs);
            SendClientMessage(target, COLOR_WHITE, mes);
			SendClientMessage(target, COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

		    break;
		}
	}
	if(!check)
		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться на своей территории");
	return true;
}
CMD:selldrugs(playerid, params[])
{
    if(IsAGang(playerid))
    {
   		new bool:check;
		for(new i; i < MAX_GANGZONE; i++)
		{
			if(PlayerToKvadrat(playerid, GZMZ[i][gCoords][0], GZMZ[i][gCoords][1], GZMZ[i][gCoords][2], GZMZ[i][gCoords][3]))
			{
			    check = true;
				extract params -> new player:target, drugs, price; else
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/selldrugs [ID игрока] [Кол-во наркотиков] [Цена]");

				if(!IsPlayerConnected(target) || playerid == target)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

				if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

				if(drugs < 1 || drugs > 500)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное количество наркотиков (от 1 до 500)");

				if(price < 1 || price > 10000)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная цена (от 1$ до 10000$)");

				if(drugs > PI[playerid][pDrugs])
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет столько наркотиков");

				temp_selldrugs_receiver[playerid] = target + 1;
				temp_selldrugs_sender[target] = playerid + 1;
				temp_selldrugs_value[target] = drugs;
				temp_selldrugs_price[target] = price;

				new
					mes[162];

			    format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} купить у Вас {FFFFFF}%d{269BD8} грамм наркотиков за {FFFFFF}%d${269BD8}", PN(target), drugs, price);
				SendClientMessage(playerid, 0x269BD8FF, mes);

				format(mes, sizeof mes, "%s{269BD8} предлагает Вам приобрести {FFFFFF}%d{269BD8} грамм наркотиков за {FFFFFF}%d${269BD8}", PN(playerid), drugs, price);
	            SendClientMessage(target, COLOR_WHITE, mes);
				SendClientMessage(target, COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");
				break;
			}
		}
		if(!check) SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться на своей территории");
	}
 	else if(IsAMafia(playerid))
    {
    	if(sscanf(params, "udd", params[0], params[1],params[2])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/selldrugs [ID игрока] [Кол-во наркотиков] [Цена]");
		if(!IsPlayerConnected(params[0]) || playerid == params[0]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

		if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		if(params[1] < 1 || params[1] > 500) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное количество наркотиков (от 1 до 500)");
		if(params[2] < 1 || params[2] > 10000) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная цена (от 1$ до 10000$)");
		if(params[1] > PI[playerid][pDrugs]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет столько наркотиков");

		temp_selldrugs_receiver[playerid] = params[0] + 1;
		temp_selldrugs_sender[params[0]] = playerid + 1;
		temp_selldrugs_value[params[0]] = params[1];
		temp_selldrugs_price[params[0]] = params[2];

		new mes[162];

		format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} купить у Вас {FFFFFF}%d{269BD8} грамм наркотиков за {FFFFFF}%d${269BD8}", PN(params[0]), params[1], params[2]);
		SendClientMessage(playerid, 0x269BD8FF, mes);

		format(mes, sizeof mes, "%s{269BD8} предлагает Вам приобрести {FFFFFF}%d{269BD8} грамм наркотиков за {FFFFFF}%d${269BD8}", PN(playerid), params[1], params[2]);
  		SendClientMessage(params[0], COLOR_WHITE, mes);
		SendClientMessage(params[0], COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");
    }
	return true;
}
CMD:usedrugs(playerid, params[])
{
    if(GetPlayerVirtualWorld(playerid)==534)
		return false;

	if(PI[playerid][pDrugs] < 1)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет наркотиков");
		
    if(IsPlayerInRangeOfPoint(playerid, 50.0, 693.6690, 1527.1469, 1306.1029))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в больнице");
		
    if(UseDrugsTime[playerid] > 120)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы недавно употребяли наркотики");
		
    if(GetPVarInt(playerid,"narko") > gettime())
		return 1;
		
    if(GetPVarInt(playerid,"mask") > gettime())
		return 1;

    new
		Float:health;
		
    GetPlayerHealth(playerid, health);
    
	health += 30;
	
	if(health > 100)
		health = 100;
		
    J_SetPlayerHealth(playerid, health);
    
    if(IsPlayerInAnyVehicle(playerid) && temp_tie_sender[playerid] == INVALID_PLAYER_ID)
		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
		
	PI[playerid][pDrugs] --;
	UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);
	UseDrugsTime[playerid] += 60;

	SetPlayerDrunkLevel(playerid, 3900);
	
	new
	    mes[100];
	    
	format(mes, sizeof mes, "%s употребил наркотики", PN(playerid));
	ProxDetector(25, playerid, mes, COLOR_ME);
	
	if(!IsPlayerInAnyVehicle(playerid) && temp_tie_sender[playerid] == INVALID_PLAYER_ID)
		J_ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, 0, 0, 0, 0, 0, 1);
		
	SetPVarInt(playerid, "narko", gettime()+6);
	return true;
}
CMD:dropdrugs(playerid)
{
    PI[playerid][pDrugs] = 0;
	UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);
    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выбросили все свои наркотики");
}
CMD:klist(playerid)
{
	if(!IsAGang(playerid) || !IsAMafia(playerid))
	    return 1;
	    
	if(PI[playerid][pKillList] == 0)
	{
		PI[playerid][pKillList] = 1;
		UpdatePlayerData(playerid, "KillList", PI[playerid][pKillList]);
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы включили отображение убийств");
	}
	else
	{
		PI[playerid][pKillList] = 0;
		UpdatePlayerData(playerid, "KillList", PI[playerid][pKillList]);
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выключили отображение убийств");
	}
    return true;
}


CMD:capture(playerid)
{
	if(IsAGang(playerid))
	{
		new h; gettime(h);

		if(h < 15 || h > 21)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Использовать команду можно только с 15:00 до 22:00");

		if(PI[playerid][pRank] < 9)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Функция доступна с 9 ранга и выше");

		new fraction = PI[playerid][pFraction];

		if(!IsInAllowed(playerid))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваша банда уже участвует в захвате зон");

		if(zGangTime[fraction-1] <= 0)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сегодня ваша банда больше не может участвовать в захвате");

		if(GhettoFreeze)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Гетто заморожено");
			
		if(GhettoRasform)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Гетто заморожено");

		new bool:dostup = false;
		for(new i; i < MAX_GANGZONE; i++)
	    {
		    if(PlayerToKvadrat(playerid, GZMZ[i][gCoords][0], GZMZ[i][gCoords][1], GZMZ[i][gCoords][2], GZMZ[i][gCoords][3]) && ZoneOnBattle[i] == 0)
			{
		        switch(i)
				{
					case 36, 56, 91, 33, 60: dostup = true;
				}
				
				if(dostup == true)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Эту территорию нельзя захватить!");
			}
		}

		if(FrakCD > 0)
		{
		    new
				frmt_relax[128];

		    format(frmt_relax, sizeof frmt_relax, "{FF2222}[Ошибка] {FFFFFF}Ваша банда устала, отдыхайте еще %d минут.", floatround(FrakCD/60));
			SendClientMessage(playerid, COLOR_WHITE, frmt_relax);
			return 1;
		}


		for(new i; i < MAX_GANGZONE; i++)
		{
			if(PlayerToKvadrat(playerid,GZMZ[i][gCoords][0], GZMZ[i][gCoords][1],GZMZ[i][gCoords][2],GZMZ[i][gCoords][3]) && ZoneOnBattle[i] == 0)
			{
				if(IsPlayerInBandOnline(fraction) < 5)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей банде мало игроков онлайн!");

				if(IsPlayerInBandOnline(GZMZ[i][gGang]) < 4)
				{
					new
						frmt_smail_players[28 + 20];

				    format(frmt_smail_players, sizeof frmt_smail_players, "{FF2222}[Ошибка] {FFFFFF}У банды \"%s\" мало игроков!", GetGangName(GZMZ[i][gGang]));
					return SendClientMessage(playerid, COLOR_WHITE, frmt_smail_players);
				}
				if(GZMZ[i][gGang] == fraction)
					return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете захватывать зону вашей банды!");
				if(IsCapture == 1)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже происходит захват одной из зон. Дождитесь окончания!");

				new
				    frmt_dialog_capt[125 + 25 + 25 + 9];

				format(frmt_dialog_capt, sizeof frmt_dialog_capt, "{FFFFFF}Эта территория принадлежит %s\nВы уверены что хотите её захватить?\nЧленов вашей банды: {9ACD32}%d\n{FFFFFF}Членов банды \"%s\": {33AAFF}%d",GetGangName(GZMZ[i][gGang]), IsPlayerInBandOnline(fraction), GetGangName(GZMZ[i][gGang]), IsPlayerInBandOnline(GZMZ[i][gGang]));
				ShowPlayerDialogEx(playerid, 838, DIALOG_STYLE_MSGBOX, !"Захват территории", frmt_dialog_capt, !"Да", !"Нет");
			}
		}

	}
	return true;

}
CMD:sellzone(playerid, params[])
{
	if(!IsAGang(playerid))
		return 1;

	if(PI[playerid][pRank] != 10)
		return 1;

	if(PI[playerid][pSellZones] > 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы продали максимальное кол-во территорий за день");

	if(GhettoRasform)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Гетто заморожено");


	new
	    bool:check,
		bool:dostup;
	    
	for(new i; i < MAX_GANGZONE; i++)
	{
		if(PlayerToKvadrat(playerid,GZMZ[i][gCoords][0], GZMZ[i][gCoords][1],GZMZ[i][gCoords][2],GZMZ[i][gCoords][3]) && ZoneOnBattle[i] == 0)
		{
	        switch(i)
			{
				case 36, 56, 91, 33, 60: dostup = true;
			}

			if(dostup == true)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Эту территорию нельзя продавать!");
				
		    check = true;
			if(GZMZ[i][gGang] != PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Территория не принадлежит Вашей банде");
			    
			extract params -> new player:target, price; else
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/sellzone [ID лидера] [Цена]");
			    
			if(!IsPlayerConnected(target) || playerid == target)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

			if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		
			if(!IsAGang(target) && PI[target][pRank] != 10)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не лидер одной из банд");
			    
			if(price < 1 || price > 1000000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная цена (от 1$ до 1000000$)");
			    
			    
			temp_sellzone_receiver[playerid] = target + 1;
			temp_sellzone_sender[target] = playerid + 1;
			temp_sellzone_id[target] = i+1;
			temp_sellzone_price[target] = price;

			new
				mes[162];

		    format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} купить у Вас территорию за {FFFFFF}%d${269BD8}", PN(target), price);
			SendClientMessage(playerid, 0x269BD8FF, mes);

			format(mes, sizeof mes, "%s{269BD8} предлагает Вам приобрести территорию за {FFFFFF}%d${269BD8}", PN(playerid), price);
            SendClientMessage(target, COLOR_WHITE, mes);
			SendClientMessage(target, COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");
			
			break;
		}
		
	}
	if(!check)
		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться на своей территории");

	return true;
}
CMD:givekey(playerid, params[])
{
	if(!IsAGang(playerid))
		return 1;

	if(PI[playerid][pRank] != 10)
		return 1;

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/givekey [ID игрока]");

	if(!IsPlayerConnected(target) || playerid == target)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		
	if(!PI[target][pGangKey])
		PI[target][pGangKey] = 1, SendClientMessage(target, 0x269BD8FF, !"Вы получили ключи от дома банды"), SendClientMessage(playerid, 0x269BD8FF, !"Вы выдали ключи от дома банды");

	else
		PI[target][pGangKey] = 0, SendClientMessage(target, 0x269BD8FF, !"У Вас забрали ключи от дома банды"), SendClientMessage(playerid, 0x269BD8FF, !"Вы забрали ключи от дома банды");
		
	UpdatePlayerData(target, "GangKey", PI[target][pGangKey]);
	return 1;
}
CMD:mrespawn(playerid)
{
	if(!IsAMafia(playerid))
		return 1;

	if(PI[playerid][pRank] < 9)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Функция доступна с 9 ранга и выше");

    for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++)
    {
        if(VehicleInfo[i][vTeam] != PI[playerid][pFraction] || IsVehicleOccupied(i)) continue;
        SetVehicleToRespawn(i);
    }
    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы отправили незанятый транспорт вашей фракции на респавн!");
    return true;
}
CMD:grespawn(playerid)
{
	if(!IsAGang(playerid)) return 1;
	if(PI[playerid][pRank] < 9) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Функция доступна с 9 ранга и выше");
    for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++)
    {
        if(VehicleInfo[i][vTeam] != PI[playerid][pFraction] || IsVehicleOccupied(i)) continue;
        SetVehicleToRespawn(i);
    }
    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Авто банды зареспавнено");
    return true;
}
CMD:warehouse(playerid)
{
	if(IsAGang(playerid))
	{
		if(PI[playerid][pRank] < 9)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Функция доступна с 9 ранга и выше");

		new
		    gangid = PI[playerid][pFraction]-2,
			frmt_warehouse[25 + MAX_PLAYER_NAME];

	    if(gGangStorageStatus[gangid])
	    {
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Общак банды закрыт");
			format(frmt_warehouse, sizeof frmt_warehouse, "[F] %s закрыл общак банды", PN(playerid));
			FractionChat(gangid+2, 0x4682B4AA, frmt_warehouse);
			gGangStorageStatus[gangid] = 0;
		}
	    else
	    {
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Общак банды открыт");
			format(frmt_warehouse, sizeof frmt_warehouse, "[F] %s открыл общак банды", PN(playerid));
			FractionChat(gangid+2, 0x4682B4AA, frmt_warehouse);
			gGangStorageStatus[gangid] = 1;
		}

		new
			query_storage[80];

		format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `storagestatus` = '%d' WHERE `id` = %d", gGangStorageStatus[gangid], gangid+1);
		mysql_tquery(mysql, query_storage);
	}
	else if(IsAMafia(playerid))
	{
		if(PI[playerid][pRank] < 9)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Функция доступна с 9 ранга и выше");

		new
		    mafiaid = PI[playerid][pFraction]-12,
			frmt_warehouse[25 + MAX_PLAYER_NAME];

	    if(gMafiaStorageStatus[mafiaid])
	    {
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Общак мафии закрыт");
			format(frmt_warehouse, sizeof frmt_warehouse, "[F] %s закрыл общак мафии", PN(playerid));
			FractionChat(mafiaid+12, 0x4682B4AA, frmt_warehouse);
			gMafiaStorageStatus[mafiaid] = 0;
		}
	    else
	    {
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Общак мафии открыт");
			format(frmt_warehouse, sizeof frmt_warehouse, "[F] %s открыл общак мафии", PN(playerid));
			FractionChat(mafiaid+12, 0x4682B4AA, frmt_warehouse);
			gMafiaStorageStatus[mafiaid] = 1;
		}

		new
			query_storage[80];

		format(query_storage, sizeof query_storage, "UPDATE `mafia` SET `storagestatus` = '%d' WHERE `id` = %d", gMafiaStorageStatus[mafiaid], mafiaid+1);
		mysql_tquery(mysql, query_storage);
	}
    return true;
}
CMD:sload(playerid)
{
	if(PI[playerid][pFraction] != 7 && PI[playerid][pSubfraction] != 2) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем военного вертолета");
	new carid = GetPlayerVehicleID(playerid);
	if(VehicleInfo[carid][vTeam] != 7 && VehicleInfo[carid][vSubTeam] != 2 && GetVehicleModel(carid) != 548) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем военного вертолета");
	if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1467.7305, 1488.9410, 8.2501)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на корабле с боеприпасами");
	if(VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");
    
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
	x = x - (-4.0*floatsin(a, degrees));
	y = y - 4.0*floatcos(a, degrees);
	VehicleLoad[carid][vlPickup] = CreateDynamicPickup(2061, 1, x, y, z-1.5);
	VehicleLoad[carid][vlArea] = CreateDynamicSphere(x, y, z-1.5, 1.0);


	new mes[128];
		
	format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[carid][vlLimit]);
	VehicleLoad[carid][vlText] = CreateDynamic3DTextLabel(mes, COLOR_WHITE, x, y, z-1.0, 10.0);
    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали загрузку боеприпасов");
	return true;
}
CMD:sunload(playerid)
{
	if(PI[playerid][pFraction] != 7 && PI[playerid][pSubfraction] != 2) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем военного вертолета");
	new carid = GetPlayerVehicleID(playerid);

	if(VehicleInfo[carid][vTeam] != 7 && VehicleInfo[carid][vSubTeam] != 2 && GetVehicleModel(carid) != 548) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем военного вертолета");
	/*if(!IsPlayerInRangeOfPoint(playerid, 10.0, -1467.7305, 1488.9410, 8.2501))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на корабле с боеприпасами");*/
	if(VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");
    
	VehicleLoad[carid][vlID] = carid;
	VehicleLoad[carid][vlLoading] = false;
	VehicleLoad[carid][vlUnloading] = true;

    RemovePlayerFromVehicle(playerid);
	new
		Float:x,
		Float:y,
		Float:z,
		Float:a;

	GetVehiclePos(carid, x, y, z);
	GetVehicleZAngle(carid, a);
	x = x - (-4.0*floatsin(a, degrees));
	y = y - 4.0*floatcos(a, degrees);
	VehicleLoad[carid][vlPickup] = CreateDynamicPickup(2061, 1, x, y, z-1.5);
	VehicleLoad[carid][vlArea] = CreateDynamicSphere(x, y, z-1.5, 1.0);

	new
		mes[128];

	format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[carid][vlLimit]);
	VehicleLoad[carid][vlText] = CreateDynamic3DTextLabel(mes, COLOR_WHITE, x, y, z-1.0, 10.0);

    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали разгрузку боеприпасов");
	return true;
}
CMD:load(playerid)
{
	if(PI[playerid][pFraction] != 7) return 1;

	if(PI[playerid][pSubfraction] == 1)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем т/с");

		new
		    carid = GetPlayerVehicleID(playerid);

		if(VehicleInfo[carid][vTeam] != 7 || VehicleInfo[carid][vSubTeam] != 1 || GetVehicleModel(carid) != 433)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем машины для перевозки оружия");

		if(VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");

		ShowPlayerDialogEx(playerid, 961, DIALOG_STYLE_LIST, !"Выберите организацию", !"{FF7319}1.{FFFFFF} Полиция Los Santos\n{FF7319}2.{FFFFFF} Полиция San Fierro\n{FF7319}3.{FFFFFF} Полиция Las Venturas\n{FF7319}4.{FFFFFF} ФБР\n{FF7319}5.{FFFFFF} Правительство\n{FF7319}6.{FFFFFF} Мэрия Los Santos\n{FF7319}7.{FFFFFF} Мэрия San Fierro\n{FF7319}8.{FFFFFF} Мэрия Las Venturas", !"Выбор", !"Отмена");
	}
	else if(PI[playerid][pSubfraction] == 2)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем т/с");

		new
		    carid = GetPlayerVehicleID(playerid);

		if(VehicleInfo[carid][vTeam] != 7 || VehicleInfo[carid][vSubTeam] != 2 || GetVehicleModel(carid) != 433 || GetVehicleModel(carid) != 595)
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

	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали загрузку боеприпасов");
      	foreach(new i : Player)
	    {
	        if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
	            continue;
	            
			if(PI[i][pFraction] != 7)
			    continue;
			    
			temp_army_loadfr[i] = 7;
		}
	}
	
	else
	    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в Армии Las Venturas / Армии San Fierro");
	    
	return true;
}
CMD:unload(playerid)
{
	if(PI[playerid][pFraction] != 7)
		return 1;

	if(PI[playerid][pSubfraction] == 1)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем т/с");

		new
		    carid = GetPlayerVehicleID(playerid);

		if(VehicleInfo[carid][vTeam] != 7 || VehicleInfo[carid][vSubTeam] != 1 || GetVehicleModel(carid) != 433)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем машины для перевозки оружия");

		if(VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");

		//ShowPlayerDialogEx(playerid, 961, DIALOG_STYLE_LIST, !"Выберите организацию", !"1. Полиция Los Santos\n2. Полиция San Fierro\n3. Полиция Las Venturas\n4. ФБР\n5. Мэрия Los Santos", !"Выбор", !"Отмена");
		VehicleLoad[carid][vlID] = carid;
		VehicleLoad[carid][vlLoading] = false;
		VehicleLoad[carid][vlUnloading] = true;

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

	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали разгрузку боеприпасов");
	    
	}
	else if(PI[playerid][pSubfraction] == 2)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем т/с");

		new
		    carid = GetPlayerVehicleID(playerid);

		if(VehicleInfo[carid][vTeam] != 7 || VehicleInfo[carid][vSubTeam] != 2 || GetVehicleModel(carid) != 433)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем машины для перевозки оружия");

		if(VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");

		VehicleLoad[carid][vlID] = carid;
		VehicleLoad[carid][vlLoading] = false;
		VehicleLoad[carid][vlUnloading] = true;

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

	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали разгрузку боеприпасов");
	}
	
	else
	    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в Армии Las Venturas / Армии San Fierro");

	return true;
}
CMD:ud(playerid, params[])
{
	if(PI[playerid][pFraction] != 7 && !IsACop(playerid))
		return 1;
		
	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/ud [ID игрока]");

	if(!IsPlayerConnected(target))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(target != playerid)
	{
		new
			frmt_ud_sender[56 + MAX_PLAYER_NAME],
			frmt_ud_receiver[MAX_PLAYER_NAME + 101];

		format(frmt_ud_sender, sizeof frmt_ud_sender, "Вы предложили {FFFFFF}%s {269BD8}показать свое удостоверение", PN(target));
		SendClientMessage(playerid, 0x269BD8FF, frmt_ud_sender);

		format(frmt_ud_receiver, sizeof frmt_ud_receiver, "%s {269BD8}хочет показать Вам удостоверение. Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid));
		SendClientMessage(target, COLOR_WHITE, frmt_ud_receiver);

		temp_ud_sender[target] = playerid + 1;
		temp_ud_receiver[playerid] = target + 1;
	}
	else
	{
		new string[MAX_PLAYER_NAME + 50];
		format(string, sizeof string, "%s достал(а) удостоверение и рассматривает его", cPN(playerid));
		ProxDetector(25, playerid, string, COLOR_ME);

        ShowUdost(playerid, playerid);
	}
	return true;
}
CMD:pt(playerid, params[])
{
	if(!IsACop(playerid)) return 1;
	if(PI[playerid][pRank] < 2) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/pt [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
	if(GetPlayerDistanceToPlayer(playerid, target) > 33.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	if(PI[target][pWanted] < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет розыск");
	if(temp_pursuit_sender[target] != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}За этим игроком уже идет погоня");

    temp_pursuit_sender[target] = playerid + 1;
    temp_pursuit_receiver[playerid] = target + 1;
    
	SendClientMessage(playerid, COLOR_YELLOW, !"Вы начали погоню за преступником!");
	SendClientMessage(target, COLOR_LIGHTRED, !"За вами погоня! Если вы выйдите из игры, вас автоматически посадит в тюрьму!");
	return true;
}
CMD:unpt(playerid, params[])
{
	if(!IsACop(playerid)) return 1;
	if(PI[playerid][pRank] < 2) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	    
	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/unpt [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
	if(GetPlayerDistanceToPlayer(playerid, target) > 33.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	if(temp_pursuit_sender[target] == INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}За этим игроком не ведется погоня");
	if(temp_pursuit_receiver[playerid] != target+1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Погоня не принадлежит Вам");

    temp_pursuit_sender[target] = INVALID_PLAYER_ID;
    temp_pursuit_receiver[playerid] = INVALID_PLAYER_ID;

	SendClientMessage(playerid, COLOR_LIGHTBLUE, !"Погоня прервана");
	SendClientMessage(target, COLOR_LIGHTBLUE, !"Погоня прервана");
    return true;
}
CMD:su(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target, level, string:warning[60]; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/su [ID игрока] [Уровень розыска] [Причина]");
	    
	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(level < 1 || level > 6)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверно указан уровень розыска");
		
	if(strlen(warning) < 2 || strlen(warning) > 30)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинная/короткая причина");

	if(PI[target][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в тюрьме");

	if(PI[target][pWanted] >= 6)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже имеется максимальный уровень розыска");

	PI[target][pWanted] += level;
	
	if(PI[target][pWanted] > 6)
		PI[target][pWanted] = 6;
		
	UpdatePlayerData(target, "Wanted", PI[target][pWanted]);
	SetPlayerWantedLevel(target, PI[target][pWanted]);
	
	new
		mes[256];
		
	format(mes, sizeof mes, "%s объявил Вас в розыск. Причина: %s. Уровень: %d", PN(playerid), warning, level);
	SendClientMessage(target, 0xFF182DFF, mes);
    format(mes, sizeof mes, "[Внимание] %s объявлен в розыск +%d[{FFFFFF}%d{007FFF}]. Обвинитель: %s. Причина: %s", PN(target), level, PI[target][pWanted], PN(playerid), warning);
	CopMes(0x007FFFFF, mes);
	format(mes, sizeof mes, "Вы объявили %s в розыск. Причина: %s. Уровень: %d", PN(target), warning, level);
	SendClientMessage(playerid, COLOR_GREEN, mes);
	return true;
}
CMD:cuff(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/cuff [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок уже находится в тюрьме");

	if(!PI[target][pWanted])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не совершал преступление");

	if(temp_cuffer_sender[target] != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок уже наручниках");
		
	if(IsACop(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нельзя надеть наручники на законника");
		
	if(temp_cuffer_receiver[playerid] != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет больше наручников");

    if(temp_tazer_timer[target])
    {
        temp_tazer_timer[target] = 0;
        f_TogglePlayerControllable(target, true);
        SetPlayerSpecialAction(target, SPECIAL_ACTION_NONE);
    }

    SetPlayerSpecialAction(target, SPECIAL_ACTION_CUFFED);
    SetPlayerAttachedObject(target, 0, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
    
	temp_cuffer_sender[target] = playerid + 1;
	temp_cuffer_receiver[playerid] = target + 1;
	
	new
		frmt_action[100];

	format(frmt_action, sizeof frmt_action, "%s надел(а) наручники на преступника", PN(playerid));
	ProxDetector(25, playerid, frmt_action, COLOR_ME);

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		f_TogglePlayerControllable(target, false);
    
    return true;
}
CMD:uncuff(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/uncuff [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(temp_cuffer_sender[target] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в наручниках");

	new
	    cufferid = temp_cuffer_receiver[playerid]-1;
	    
	SetPlayerSpecialAction(target, SPECIAL_ACTION_NONE);
	RemovePlayerAttachedObject(target, 0);
	
	temp_cuffer_sender[target] = INVALID_PLAYER_ID;
	temp_cuffer_receiver[cufferid] = INVALID_PLAYER_ID;
	temp_cuffer_receiver[playerid] = INVALID_PLAYER_ID;

	f_TogglePlayerControllable(target, true);

	if(GotoInfo[playerid][gtID] == target)
	{
	    CheckPlayerGoCuff(target);
		CheckPlayerGoCuff(playerid);
	}
	new
		frmt_action[100];

	format(frmt_action, sizeof frmt_action, "%s снял(а) наручники с преступника", PN(playerid));
	ProxDetector(25, playerid, frmt_action, COLOR_ME);
	return true;
}
CMD:arrest(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;
		
	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/arrest [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок уже находится в тюрьме");

	if(!PI[target][pWanted])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не совершал преступление");

	if(temp_cuffer_sender[target] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не в наручниках");

    new
		time = PI[target][pWanted] * 300;
		
    if(!IsPlayerInDynamicArea(playerid, gArrestArea[0]) && !IsPlayerInDynamicArea(playerid, gArrestArea[1]) && !IsPlayerInDynamicArea(playerid, gArrestArea[2]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в гараже департамента");
    
    if(temp_cuffer_sender[target] != INVALID_PLAYER_ID)
    {
        new
			cufferid = temp_cuffer_sender[target]-1;
			
        SetPlayerSpecialAction(target, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(target, 0);
        temp_cuffer_sender[target] = INVALID_PLAYER_ID;
        temp_cuffer_receiver[cufferid] = INVALID_PLAYER_ID;
    }
	if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
	{
	    CheckPlayerGoCuff(target);
		CheckPlayerGoCuff(playerid);
	}

    PI[target][pJailTime] = time;
    PI[target][pWanted] = 0;
    SetPlayerWantedLevel(target, 0);
    ResetPlayerWeapons(target);
    SetPlayerSkinEx(target, 42);
    PlayerPlaySound(target, 17004, 0.0, 0.0, 0.0);
    PI[target][pJailAdmin] = 0;
    UpdatePlayerData(target, "JailAdmin", PI[target][pJailAdmin]);
			            
    switch(PI[playerid][pSubfraction])
    {
		case 0..1:
		{
	        new JailedLS = random(4)+1;
		    switch(JailedLS)
		    {
		        case 1: SetPlayerPos(target, 226.9169,109.1662,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 2: SetPlayerPos(target, 222.7322,108.9943,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 3: SetPlayerPos(target, 218.7821,109.3731,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 4: SetPlayerPos(target, 214.7852,108.9267,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
			}
			SetPlayerVirtualWorld(target, 2);
            SetPlayerInterior(target, 10);
            PI[target][pPrison] = 1;
		}
        case 2:
		{
	        new JailedSF = random(4)+1;
		    switch(JailedSF)
		    {
		        case 1: SetPlayerPos(target, 226.9169,109.1662,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 2: SetPlayerPos(target, 222.7322,108.9943,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 3: SetPlayerPos(target, 218.7821,109.3731,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 4: SetPlayerPos(target, 214.7852,108.9267,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
			}
			SetPlayerVirtualWorld(target, 0);
            SetPlayerInterior(target, 10);
            PI[target][pPrison] = 2;
		}
        case 3:
		{
	        new JailedLV = random(4)+1;
		    switch(JailedLV)
		    {
		        case 1: SetPlayerPos(target, 226.9169,109.1662,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 2: SetPlayerPos(target, 222.7322,108.9943,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 3: SetPlayerPos(target, 218.7821,109.3731,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
		        case 4: SetPlayerPos(target, 214.7852,108.9267,999.0156), J_SetPlayerFacingAngle(target, 181.7349);
			}
			SetPlayerVirtualWorld(target, 12);
            SetPlayerInterior(target, 10);
            PI[target][pPrison] = 3;
		}
    }
	GiveMoney(playerid, 250, "премия");
	
    new
		fractionid = PI[playerid][pFraction]-1,
    	rank = PI[playerid][pRank]-1;
    	
    new
		query[128];
		
    format(query, sizeof query, "UPDATE `accounts` SET `JailTime` = '%d', `Prison` = '%d', `Wanted` = '0' WHERE `ID` = '%d'", PI[target][pJailTime], PI[target][pPrison], PI[target][pID]);
    mysql_tquery(mysql, query);
    
    new
		mes[128];
		
    if(PI[playerid][pFraction] == 8)
		format(mes, sizeof mes, "%s %s поместил Вас в КПЗ на %d минут", gFractionRankName[fractionid][rank], PN(playerid), floatround(time/60));

	else if(PI[playerid][pFraction] == 11)
		format(mes, sizeof mes, "%s %s поместил Вас в КПЗ на %d минут", gFractionRankName[fractionid][rank], PN(playerid), floatround(time/60));

	SendClientMessage(target, 0xFF182DFF, mes);
    
    format(mes, sizeof mes, "Вы поместили %s в КПЗ на %d минут", PN(target), floatround(time/60));
    SendClientMessage(playerid, 0x3399FFFF ,mes);
    
    SendClientMessage(target, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы посмотреть сколько Вам осталось сидеть в тюрьме, введите команду {FFFF00}/ptime");
    ResetPlayerWeapons(target);
	if(PI[target][pJailKey])
	{
		PI[target][pJailTime] = 0;
		UpdatePlayerData(target, "JailTime", PI[target][pJailTime]);

		SendClientMessage(target, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У вас были ключи от камеры. Вы были освобождены");

		new
			prison = PI[target][pPrison]-1;

		SetPlayerSkinEx(target, GetSkinOfPlayer(target));
		SetPlayerInterior(target, 0);
		SetPlayerVirtualWorld(target, 0);
		SetPlayerPos(target, gJailExit[prison][0], gJailExit[prison][1], gJailExit[prison][2]);
		J_SetPlayerFacingAngle(target, gJailExit[prison][3]);
		PI[target][pPrison] = 0;
		UpdatePlayerData(target, "Prison", PI[target][pPrison]);
		PI[target][pJailKey] = 0;
		UpdatePlayerData(target, "JailKey", PI[target][pJailKey]);
	}
    return true;
}
CMD:push(playerid, params[])
{
	if(IsACop(playerid))
	{
		if(PI[playerid][pRank] < 3)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

		extract params -> new player:target; else
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/push [ID игрока]");

		if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

		if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

		if(PI[target][pJailTime] > 0)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок уже находится в тюрьме");

		if(!PI[target][pWanted])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не совершал преступление");

		if(temp_cuffer_sender[target] == INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не в наручниках");

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем полицейского транспорта");

		new
		    carid = GetPlayerVehicleID(playerid),
			model = GetVehicleModel(carid);

		if((VehicleInfo[carid][vTeam] == 8 || VehicleInfo[carid][vTeam] == 11)
		&& model == 596 || model == 523 || model == 599 || model == 560 || model == 497 || model == 597 || model == 598 || model == 487 || model == 482 || model == 490 || model == 426)
		{
			new
				seat = GetFreeSeat(carid);

			if(seat == -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В т/с нет свободного места");

            SetPVarInt(target, "anticheat_put", gettime()+3);
			PutPlayerInVehicle(target, carid, seat);

			if(temp_cuffer_sender[target] != INVALID_PLAYER_ID)
				TogglePlayerControllable(target, 0);

			new
				frmt_action[65];

			format(frmt_action, sizeof frmt_action, "%s посадил преступника в транспорт", PN(playerid));
			ProxDetector(25, playerid, frmt_action, COLOR_ME);
		}

		else
			SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем полицейского транспорта");

	}
	if(IsAMafia(playerid))
	{
		if(PI[playerid][pRank] < 3)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

		extract params -> new player:target; else
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/push [ID игрока]");

		if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

		if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем транспорта мафии");

		if(temp_tie_sender[target] == INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не связан");

		new
			carid = GetPlayerVehicleID(playerid);

		if(VehicleInfo[carid][vTeam] != PI[playerid][pFraction])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем транспорта мафии");

		new
			seat = GetFreeSeat(carid);

		if(seat == -1)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В т/с нет свободного места");

        SetPVarInt(target, "anticheat_put", gettime()+3);
		PutPlayerInVehicle(target, carid, seat);

		new
			frmt_action[65];

		format(frmt_action, sizeof frmt_action, "%s посадил(а) в транспорт", PN(playerid));
		ProxDetector(25, playerid, frmt_action, COLOR_ME);
	}
	return true;
}
CMD:ticket(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target, price, string:warning[60]; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/ticket [ID игрока] [Сумма] [Причина]");

	if(strlen(warning) < 2 || strlen(warning) > 30)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинная/короткая причина");

    if(price < 500 || price > 5000)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Штраф можно выписать на сумму от 500 до 5000");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	PI[target][pFine] += price;
    UpdatePlayerData(target, "Fine", PI[target][pFine]);
    
	new
		mes[250];
		
	format(mes, sizeof mes, "%s выписал Вам штраф в размере $%d. Причина: %s", PN(playerid), price, warning);
	SendClientMessage(target, 0xFF182DFF, mes);
	
	format(mes, sizeof mes, "[Внимание] %s выписал %s штраф в размере {FFFFFF}$%d{007FFF}. Причина: {FFFFFF}%s", PN(playerid), PN(target), price, warning);
	CopMes(0x007FFFFF, mes);
	
	SendClientMessage(target, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Оплатить штраф вы можете в одном из ПД");

	format(mes, sizeof mes, "%s выписал штраф", PN(playerid));
	ProxDetector(25, playerid, mes, COLOR_ME);
	return 1;
}
CMD:wanted(playerid)
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    fmrt_wanted_list[1900],
	    color[10],
	    new_page,
		number_wanted;
	    
	strcat(fmrt_wanted_list, "{FFFFFF}№. Никнейм игрока\t{FFFFFF}Уровень розыска\n");
	
   	foreach(new i : Player)
	{
		if(!PI[i][pID] || !PI[i][pWanted])
			continue;
	
	    if(number_wanted > 39 && i > 40)
		{
		    pTemp[playerid][pLastWanted] = i;
		    new_page = true;
			format(fmrt_wanted_list, sizeof fmrt_wanted_list, "%s{FFFFFF}Следующая страница", fmrt_wanted_list);
		    break;
		}

		if(PI[i][pWanted] > 6)
		    strcat(color, "{FF0000}");
			
		format(fmrt_wanted_list, sizeof fmrt_wanted_list, "%s{FFFFFF}%d. %s\t%s%d\n", fmrt_wanted_list, number_wanted+1, PN(i), color, PI[i][pWanted]);
		
		temp_wanted_count[playerid]++;
		number_wanted++;
	}
	if(number_wanted == 0)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Преступников не найдено");

	if(new_page)
		ShowPlayerDialogEx(playerid, 882, DIALOG_STYLE_TABLIST_HEADERS, !"Список преступников", fmrt_wanted_list, !"Далее", !"Закрыть");
	
	else
		ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Список преступников", fmrt_wanted_list, !"Закрыть", !"");

	return 1;
}
CMD:hold(playerid, params[])
{
	if(IsACop(playerid))
	{
		if(PI[playerid][pRank] < 3)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

		extract params -> new player:target; else
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/hold [ID игрока]");

		if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

		if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

		if(PI[target][pJailTime] > 0)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок уже находится в тюрьме");

		if(!PI[target][pWanted])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не совершал преступление");

		if(GotoInfo[target][gtGoID] != INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже преследует кого-то");
			
		if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже ведете кого-то за собой");

		if(temp_cuffer_sender[target] == INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не в наручниках");

		if(PI[playerid][pFraction] == PI[target][pFraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете вести за собой своего сотрудника");
	    CheckPlayerGoCuff(playerid);
	    CheckPlayerGoCuff(target);
	    GotoInfo[target][gtID] = INVALID_PLAYER_ID;
	    GotoInfo[playerid][gtGoID] = INVALID_PLAYER_ID;
	    GotoInfo[playerid][gtID] = target;
	    GotoInfo[target][gtGoID] = playerid;
	    GotoInfo[target][gtState] = GetPlayerState(playerid);
	    GetPlayerPos(target, GotoInfo[target][gtX], GotoInfo[target][gtY], GotoInfo[target][gtZ]);
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы перестать ввести игрока введите {CA6E7E}/unhold");

	    new frmt_action[120];

	    format(frmt_action, sizeof frmt_action, "%s потащил(а) %s за собой", PN(playerid), PN(target));
	    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

	    f_TogglePlayerControllable(target, true);
	}
	if(IsAMafia(playerid))
	{
		if(PI[playerid][pRank] < 3)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

		extract params -> new player:target; else
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/hold [ID игрока]");

		if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

		if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

		if(GotoInfo[target][gtGoID] != INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже преследует кого-то");

		if(temp_tie_sender[target] == INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не связан");

		if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже ведете кого-то за собой");
		if(PI[playerid][pFraction] == PI[target][pFraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете вести за собой своего сотрудника");
	    CheckPlayerGoCuff(playerid);
	    CheckPlayerGoCuff(target);
	    GotoInfo[target][gtID] = INVALID_PLAYER_ID;
	    GotoInfo[playerid][gtGoID] = INVALID_PLAYER_ID;
	    GotoInfo[playerid][gtID] = target;
	    GotoInfo[target][gtGoID] = playerid;
	    GotoInfo[target][gtState] = GetPlayerState(playerid);
	    GetPlayerPos(target, GotoInfo[target][gtX], GotoInfo[target][gtY], GotoInfo[target][gtZ]);
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы перестать ввести игрока введите {CA6E7E}/unhold");

	    new frmt_action[120];

	    format(frmt_action, sizeof frmt_action, "%s потащил(а) %s за собой", PN(playerid), PN(target));
	    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

	    f_TogglePlayerControllable(target, true);
	}
	return 1;
}
CMD:unhold(playerid, params[])
{
	if(IsACop(playerid))
	{
		if(PI[playerid][pRank] < 3)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

		extract params -> new player:target; else
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/unhold [ID игрока]");

		if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

		if(GetPlayerDistanceToPlayer(playerid, target) > 30.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

		if(PI[target][pJailTime] > 0)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок уже находится в тюрьме");

		if(!PI[target][pWanted])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот игрок не совершал преступление");

		if(GotoInfo[target][gtGoID] != playerid)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не преследует Вас");

		f_TogglePlayerControllable(target, true);
		CheckPlayerGoCuff(target);
		CheckPlayerGoCuff(playerid);
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы перестали ввести за собой");
	}
	if(IsAMafia(playerid))
	{
		if(PI[playerid][pRank] < 3)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

		extract params -> new player:target; else
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/unhold [ID игрока]");

		if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

		if(GetPlayerDistanceToPlayer(playerid, target) > 30.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

		if(GotoInfo[target][gtGoID] != playerid)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не преследует Вас");


		f_TogglePlayerControllable(target, true);
		CheckPlayerGoCuff(target);
		CheckPlayerGoCuff(playerid);
		SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы перестали ввести за собой");
	}
	
	return 1;
}
CMD:unmask(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/unmask [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(IsACop(playerid) && PI[target][pRank] > PI[playerid][pRank])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете снять маску этому игроку");

    if(!PI[target][pMaskON])
        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в маске");

	if(PI[target][pFraction])
		SetPlayerColor(target, gFractionColor[PI[target][pFraction] - 1]);

	else
		SetPlayerColor(target, 0xFFFFFF11);

	SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сняли маску игроку");

    PI[target][pMaskON] = 0;
    return 1;
}
CMD:setmark(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(temp_search_player[playerid])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже ищите преступника. Ожидайте ответа от спутника");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/setmark [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Система спутникового поиска преступника активирована. Ожидайте ответа от спутника");
	temp_search_player[playerid] = true;
	
	SetTimerEx("@__setmark",1000*random(10)+1000, 0, "dd", playerid, target);
	return 1;
}
CMD:clear(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 4)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/clear [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(!PI[target][pWanted])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет розыска");
		
	PI[target][pWanted] = 0;
	UpdatePlayerData(target, "Wanted", 0);
	SetPlayerWantedLevel(target, 0);
	
	new
		mes[128];
	
	format(mes, sizeof mes, "%s %s снял розыск у %s", gFractionRankName[PI[playerid][pFraction]-1][PI[playerid][pRank]-1], PN(playerid), PN(target));
	CopMes(0x007FFFFF, mes);
	
	format(mes, sizeof mes, "%s %s снял Вам розыск", gFractionRankName[PI[playerid][pFraction]-1][PI[playerid][pRank]-1], PN(playerid));
	SendClientMessage(target, 0x3399FFFF, mes);
		
    return 1;
}
CMD:frisk(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 4)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/frisk [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(IsACop(playerid) && PI[target][pRank] > PI[playerid][pRank])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете обыскать этого игрока");

	new
		fmrt_frisk_message[80];
	
	if(!PI[target][pDrugs])
		format(fmrt_frisk_message, sizeof fmrt_frisk_message, "Наркотиков не обнаружено");
		
	else
		format(fmrt_frisk_message, sizeof fmrt_frisk_message, "Обнаружено %d грамм наркотиков", PI[target][pDrugs]);
		
	SendClientMessage(playerid, COLOR_YELLOW, fmrt_frisk_message);

	if(!PI[target][pMats])
		format(fmrt_frisk_message, sizeof fmrt_frisk_message, "Патрон не обнаружено");
		
	else
		format(fmrt_frisk_message, sizeof fmrt_frisk_message, "Обнаружено %d патрон", PI[target][pMats]);
		
	SendClientMessage(playerid, COLOR_YELLOW, fmrt_frisk_message);

	new
		frmt_action[110];

	format(frmt_action, sizeof frmt_action, "%s произвёл обыск у %s", PN(playerid), PN(target));
	ProxDetector(25, playerid, frmt_action, COLOR_ME);
	return 1;
}
CMD:take(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 4)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/take [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		
	if(IsACop(playerid) && PI[target][pRank] > PI[playerid][pRank])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете изъять что-либо у этого игроку");

	temp_take_receiver[playerid] = target+1;
	
	new
	    frmt_take_list[400];

	if(PI[target][pDrugs] > 0 || PI[target][pPackets] > 0 || PI[target][pMats] > 0 )
	{
		format(frmt_take_list, sizeof frmt_take_list, "Наркотики {9A0000}[%d гр.]\n{FFFFFF}Ед. оружия {9A0000}[%d шт.]\n{FFFFFF}Патроны {9A0000}[%d шт.]", PI[target][pDrugs], PI[target][pPackets], PI[target][pMats]);
		ShowPlayerDialogEx(playerid, 949, DIALOG_STYLE_LIST, PN(target), frmt_take_list, !"Изъять", !"Отмена");
	}
	
	else
	    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ничего не найдено");
	    
	return 1;
}
CMD:takelic(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target, string:warning[32]; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/takelic [ID игрока] [Причина]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(strlen(warning) < 2 || strlen(warning) > 30)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинная/короткая причина");

	if(PI[target][pCarLic] != YES_LICENSE)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У этого игрока нет лицензии на вождение");

	if(IsACop(playerid) && PI[target][pRank] > PI[playerid][pRank])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете изъять лицензию на вождение у этого игрока");
	if(PI[playerid][pAdmin] != 0)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете изъять лицензию на вождение");
    PI[target][pCarLic] = 0;
    UpdatePlayerData(target, "CarLic", PI[target][pCarLic]);

	new
		frmt_takelic_message[128];

	format(frmt_takelic_message, sizeof frmt_takelic_message, "[Внимание] %s изъял водительское удостоверение у %s. Причина: %s", PN(playerid), PN(target), warning);
	CopMes(0x007FFFFF, frmt_takelic_message);

	format(frmt_takelic_message, sizeof frmt_takelic_message, "%s изъял у вас водительское удостоверение. Причина: %s", PN(playerid), warning);
	SendClientMessage(target, 0xFF5030AA, frmt_takelic_message);
	
	return 1;
}
CMD:m(playerid, params[])
{
	if(!IsACop(playerid))
		return 1;

	if(PI[playerid][pRank] < 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);

	extract params -> new string:text[128]; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/m [Текст]");

	if(strlen(text) < 2 || strlen(text) > 89)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный/короткий текст");

	new
	    carid = GetPlayerVehicleID(playerid),
		model = GetVehicleModel(carid);

	if((VehicleInfo[carid][vTeam] == 8 || VehicleInfo[carid][vTeam] == 11)
	&& model == 596 || model == 523 || model == 599 || model == 560 || model == 497 || model == 597 || model == 598 || model == 487 || model == 482 || model == 490 || model == 426)
	{
		new
			fractionid = PI[playerid][pFraction]-1,
			rank = PI[playerid][pRank],
			frmt_megaphone_message[128];

		format(frmt_megaphone_message, sizeof frmt_megaphone_message, "<<< %s %s: %s >>>", gFractionRankName[fractionid][rank-1], PN(playerid), text);
		
   		foreach(new i : Player)
		{
			if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || !PI[i][pID] || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(i))
				continue;
				
			new
				Float:rdist;
				
			rdist = GetPlayerDistanceToPlayer(playerid, i);
			
			if(rdist > 45.0)
				continue;
				
			SendClientMessage(i, 0xFFFF00AA, frmt_megaphone_message);
		}
	}
	else
		SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем полицейского транспорта");

	return 1;
}
CMD:ptime(playerid)
{
	if(!PI[playerid][pJailTime])
	    return 1;
	    
	new
		frmt_ptime_text[128],
		jailname[12];
		
	switch(PI[playerid][pPrison])
	{
		case 0..1: jailname = "LSPD";
		case 2: jailname = "SFPD";
		case 3: jailname = "LVPD";
		case 4: jailname = "DEMORGAN";
	}
	
	if(PI[playerid][pJailTime] > 60)
		format(frmt_ptime_text, sizeof frmt_ptime_text, "~g~%s~n~~w~REMAIN: ~g~%d ~w~MIN", jailname, PI[playerid][pJailTime]/60);

	else
		format(frmt_ptime_text, sizeof frmt_ptime_text, "~g~%s~n~~w~REMAIN: ~g~%d ~w~SEC", jailname, PI[playerid][pJailTime]);

	GameTextForPlayer(playerid, frmt_ptime_text, 1, 1);
	return 1;
}
CMD:ad(playerid, params[])
{
	if(gAdvertCount >= MAX_ADVERTS)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}К сожалению, очередь на объявления занята, попробуйте позже");
		
	if(!PI[playerid][pPhone])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет телефона. Вы можете купить его в магазине 24/7");
		
	if(PI[playerid][pAdvertTime])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Объявления можно посылать раз в три минуты");

	extract params -> new string:text[100]; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/ad [текст объявления]");

	if(strlen(text) < 2 || strlen(text) > 80)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное объявление");
		
	pTemp[playerid][pAdvertText] = EOS;
	SetString(pTemp[playerid][pAdvertText], text);
	
	new
	    frmt_advert_message[117];
	    
	format(frmt_advert_message, sizeof frmt_advert_message, "{FFFFFF}Цена объявления: {FF0000}%d${FFFFFF}\n\nВы действительно хотите отправить объявление?", gAdvertPrice);
	ShowPlayerDialogEx(playerid, 473, DIALOG_STYLE_MSGBOX, !"Подача объявления", frmt_advert_message, !"Да", !"Нет");
	return 1;
}
CMD:edit(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;
	    
	if(PI[playerid][pRank] < 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	    
	ShowAdvertList(playerid);
	return 1;
}
CMD:ether(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;
	    
	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    carid = GetPlayerVehicleID(playerid);

    if(!IsPlayerInAnyVehicle(playerid) && !IsPlayerInDynamicArea(playerid, gEtherRoom) || IsPlayerInAnyVehicle(playerid) && VehicleInfo[carid][vTeam] != 9 && GetVehicleModel(carid) != 582)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфирной или в рабочем т/с со спутником");


	if(!pTemp[playerid][pEther])
	{
		pTemp[playerid][pEther] = true;
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы успешно вышли в эфир. Введите повторно {FFB0B0}/ether{FFFFFF} для остановки");
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFB0B0}/et{FFFFFF} для того чтобы написать в эфир");
	}
	else
	{
		if(gNewsDialer[PI[playerid][pSubfraction]-1] == playerid)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала завершите прием звонков");

		pTemp[playerid][pEther] = false;
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы вышли из эфира");
	}
	return 1;
}
CMD:et(playerid, params[])
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(!pTemp[playerid][pEther])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфире");

	new
	    carid = GetPlayerVehicleID(playerid);

    if(!IsPlayerInAnyVehicle(playerid) && !IsPlayerInDynamicArea(playerid, gEtherRoom) || IsPlayerInAnyVehicle(playerid) && VehicleInfo[carid][vTeam] != 9 && GetVehicleModel(carid) != 582)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфирной или в рабочем т/с со спутником");

	extract params -> new string:text[120]; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/et [текст]");

	if(strlen(text) < 2 || strlen(text) > 120)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткий/длинный текст");

	new
		fractionid = PI[playerid][pFraction]-1,
		frid = GetSubfractionID(fractionid+1),
		subid = PI[playerid][pSubfraction],
		frmt_ether_message[128];

	format(frmt_ether_message, sizeof frmt_ether_message, "[%s] %s: %s", gSubfractionName[frid][subid-1], PN(playerid), text);

  	foreach(new i : Player)
	{
		if(PI[i][pRadio] != subid)
		  	continue;

		SendClientMessage(i, 0x6B8E23FF, frmt_ether_message);
	}

	return 1;
}
CMD:dial(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(!pTemp[playerid][pEther])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфире, чтобы принимать звонки");

	new
	    carid = GetPlayerVehicleID(playerid),
		subid = PI[playerid][pSubfraction]-1;

    if(!IsPlayerInAnyVehicle(playerid) && !IsPlayerInDynamicArea(playerid, gEtherRoom) || IsPlayerInAnyVehicle(playerid) && VehicleInfo[carid][vTeam] != 9 && GetVehicleModel(carid) != 582)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфирной или в рабочем т/с со спутником");


	if(gNewsDialing[subid])
	{
		new
			frmt_error_dial[128];
			
		format(frmt_error_dial, sizeof frmt_error_dial, "{FF2222}[Ошибка] {FFFFFF}%s уже принимает звонки", PN(gNewsDialer[subid]));
		SendClientMessage(playerid, COLOR_WHITE, frmt_error_dial);
		return 1;
	}
	
	new
		frmt_dial_message[128];
		
	format(frmt_dial_message, sizeof frmt_dial_message, "[R] %s начал принимать звонки. Цена звонка: $%d.", PN(playerid), gEtherPrice);
 	foreach(new i : Player)
	{
		if(PI[i][pFraction] == 9)
		{
			SendClientMessage(i, 0x4682B4AA, frmt_dial_message);
			
			if(subid == 1)
				SendClientMessage(i, 0x4682B4AA, !"[R] Телефон студии: 1100 [LS]");
				
			else if(subid == 2)
				SendClientMessage(i, 0x4682B4AA, !"[R] Телефон студии: 1102 [LV]");
				
			else if(subid == 3)
				SendClientMessage(i, 0x4682B4AA, !"[R] Телефон студии: 1101 [SF]");
		}
	}
	gNewsDialing[subid] = true;
	gNewsDialer[subid] = playerid;
	gNewsDialee[subid] = INVALID_PLAYER_ID;
	return 1;
}
CMD:takecall(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    carid = GetPlayerVehicleID(playerid),
		subid = PI[playerid][pSubfraction]-1;

	if(!gNewsDialing[subid])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны начать принимать звонки");


    if(!IsPlayerInAnyVehicle(playerid) && !IsPlayerInDynamicArea(playerid, gEtherRoom) || IsPlayerInAnyVehicle(playerid) && VehicleInfo[carid][vTeam] != 9 && GetVehicleModel(carid) != 582)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфирной или в рабочем т/с со спутником");


	new
	    frmt_dial_list[1000],
		dial_list;
	    
  	foreach(new i : Player)
	{
	    if(!PI[i][pID] || pTemp[i][pDial] != PI[playerid][pSubfraction])
			continue;

	    if(dial_list > 39 && i > 40)
		{
		    pTemp[playerid][pDialLast] = i;
			format(frmt_dial_list, sizeof frmt_dial_list, "%s{FFFFFF}Следующая страница", frmt_dial_list);
		    break;
		}
		
        format(frmt_dial_list, sizeof frmt_dial_list, "%s%d. %s", frmt_dial_list, dial_list+1, PN(i));
		dial_list++;
	}
	
	if(dial_list == 0)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Звонков не найдено");

	ShowPlayerDialogEx(playerid, 515, DIALOG_STYLE_LIST, !"Список звонков", frmt_dial_list, !"Принять", !"Отмена");

	return 1;
}
CMD:takeoff(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    carid = GetPlayerVehicleID(playerid),
		subid = PI[playerid][pSubfraction]-1;

	if(!gNewsDialing[subid])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны начать принимать звонки");

    if(!IsPlayerInAnyVehicle(playerid) && !IsPlayerInDynamicArea(playerid, gEtherRoom) || IsPlayerInAnyVehicle(playerid) && VehicleInfo[carid][vTeam] != 9 && GetVehicleModel(carid) != 582)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфирной или в рабочем т/с со спутником");


	new
	    target = gNewsDialee[PI[playerid][pSubfraction]-1];
	    
	if(target == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На линии никого нет");

	SendClientMessage(target, COLOR_WHITE, !"Вы были отсоединены ведущим");
	SetPlayerSpecialAction(target, SPECIAL_ACTION_STOPUSECELLPHONE);
	SetTimerEx("@__ClearPhone",2000, false, "i", target);
	gNewsDialee[PI[playerid][pSubfraction]-1] = INVALID_PLAYER_ID;
	SendClientMessage(playerid, COLOR_YELLOW, !"Игрок отсоединен");
	return 1;
}
CMD:stopdial(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
	    carid = GetPlayerVehicleID(playerid),
		subid = PI[playerid][pSubfraction]-1;

	if(!gNewsDialing[subid])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не принимаете звонки");

	if(gNewsDialer[subid] != playerid)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Не вы начали принимать звонки");

    if(!IsPlayerInAnyVehicle(playerid) && !IsPlayerInDynamicArea(playerid, gEtherRoom) || IsPlayerInAnyVehicle(playerid) && VehicleInfo[carid][vTeam] != 9 && GetVehicleModel(carid) != 582)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в эфирной или в рабочем т/с со спутником");


	new
	    target = gNewsDialee[PI[playerid][pSubfraction]-1];

	if(target != INVALID_PLAYER_ID)
	{
		SendClientMessage(target, COLOR_WHITE, !"Вы были отсоединены ведущим");
		SetPlayerSpecialAction(target, SPECIAL_ACTION_STOPUSECELLPHONE);
		SetTimerEx("@__ClearPhone",2000, false, "i", target);
	}
	
	new
		frmt_dial_message[128];

	format(frmt_dial_message, sizeof frmt_dial_message, "[R] %s закончил принимать звонки", PN(playerid));
	FractionChat(9, 0x4682B4AA, frmt_dial_message);
	
	gNewsDialing[PI[playerid][pSubfraction]-1] = false;
	gNewsDialer[PI[playerid][pSubfraction]-1] = INVALID_PLAYER_ID;
	gNewsDialee[PI[playerid][pSubfraction]-1] = INVALID_PLAYER_ID;


	return 1;
}
CMD:makeflyer(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

    if(!IsPlayerInDynamicArea(playerid, gRadioArea))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в радиоцентре");

	ShowPlayerDialogEx(playerid, 950, DIALOG_STYLE_INPUT, !"Создание листовки", !"{FFFFFF}Введите название листовки:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");
	
	return 1;
}
CMD:flyerinfo(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 8)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

    if(!IsPlayerInDynamicArea(playerid, gRadioArea))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в радиоцентре");
	    
	new
	    frmt_flyers_list[2900],
		query_get_list[350],
		name[24],
		id,
		flyers_count;

	format(query_get_list, sizeof query_get_list, "SELECT `id`, `name`, `sender` FROM `flyers` WHERE `checked` = 0 AND `subfraction` = %d LIMIT 0, 41", PI[playerid][pSubfraction]);
	new Cache:result = mysql_query(mysql, query_get_list);
	new flyers = cache_get_row_count(mysql);

	if(flyers == 0)
	  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных листовок для проверки");

    pTemp[playerid][pFlyersList] = 0;
    
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
	return 1;
}
CMD:giveflyer(playerid, params[])
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;
	    
	if(!PI[playerid][pFlyers] || !PI[playerid][pFlyersCount])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет листовок");
	    
	extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /giveflyer [ID игрока]");

	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(temp_flyer_sender[target] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть действующее предложение");

	new
		mes[128];

	format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} взять рекламный флаер", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, mes);

	format(mes, sizeof mes, "{FFFFFF}%s{269BD8} предложил(а) взять вам рекламный флаер", PN(playerid));
	SendClientMessage(target, 0x269BD8FF, mes);

	SendClientMessage(target, 0x269BD8FF, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");


	temp_flyer_receiver[playerid] = target + 1;
	temp_flyer_sender[target] = playerid + 1;
    return 1;
}
CMD:dropflyers(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(!PI[playerid][pFlyers])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет листовок");
	    
    PI[playerid][pFlyers] = 0;
    UpdatePlayerData(playerid, "Flyers", PI[playerid][pFlyers]);
    PI[playerid][pFlyersCount] = 0;
    UpdatePlayerData(playerid, "FlyersCount", PI[playerid][pFlyersCount]);
    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбросили все свои листовки");
    return 1;
}
CMD:unout(playerid, params[])
{
	if(PI[playerid][pFraction] != 10)
	    return 1;

	if(PI[playerid][pRank] < 1 && PI[playerid][pRank] > 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	    
	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/unout [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 30.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(GotoInfo[target][gtGoID] != playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не преследует Вас");

    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы отпустили игрока");
    
	f_TogglePlayerControllable(target, true);
	CheckPlayerGoCuff(target);
	CheckPlayerGoCuff(playerid);
    return 1;
}
CMD:out(playerid, params[])
{
	if(PI[playerid][pFraction] != 10)
	    return 1;
	    
	if(PI[playerid][pRank] < 1 && PI[playerid][pRank] > 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	    
    if(!IsPlayerInDynamicArea(playerid, gHall[PI[playerid][pSubfraction]]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в мэрии/правительстве");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/out [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(GotoInfo[target][gtGoID] != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже преследует кого-то");

	if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже ведете кого-то за собой");

	if(PI[playerid][pFraction] == PI[target][pFraction]) return 1;
    CheckPlayerGoCuff(playerid);
    CheckPlayerGoCuff(target);
    GotoInfo[target][gtID] = INVALID_PLAYER_ID;
    GotoInfo[playerid][gtGoID] = INVALID_PLAYER_ID;
    GotoInfo[playerid][gtID] = target;
    GotoInfo[target][gtGoID] = playerid;
    GotoInfo[target][gtState] = GetPlayerState(playerid);
    GetPlayerPos(target, GotoInfo[target][gtX], GotoInfo[target][gtY], GotoInfo[target][gtZ]);
    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы перестать ввести игрока введите {CA6E7E}/unout");

    new frmt_action[120];

    format(frmt_action, sizeof frmt_action, "%s потащил(а) %s за собой", PN(playerid), PN(target));
    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

    f_TogglePlayerControllable(target, true);
    return 1;
}
CMD:reply(playerid, params[])
{
	if(PI[playerid][pFraction] != 10)
	    return 1;

	if(PI[playerid][pRank] < 3 && PI[playerid][pRank] > 4)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

    if(!IsPlayerInDynamicArea(playerid, gHall[PI[playerid][pSubfraction]]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в мэрии/правительстве");

    if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);

	extract params -> new player:target, string:text[128]; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/reply [ID игрока] [Текст]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(!pTemp[target][pQuestion] || pTemp[target][pHallQuestion] != PI[playerid][pSubfraction])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не задавал вопрос");

	new
	    frmt_reply_message[198];

	foreach(new i : Player)
	{
	    if(!PI[i][pID] || PI[i][pFraction] != 10 || PI[i][pSubfraction] != pTemp[target][pHallQuestion])
			continue;

		format(frmt_reply_message, sizeof frmt_reply_message, "[R] %s[%d] ответил(а) на вопрос %s[%d]: %s", PN(playerid), playerid, PN(target), target, text);

		SendClientMessage(i, 0x4682B4AA, frmt_reply_message);
	}
	format(frmt_reply_message, sizeof frmt_reply_message, "Сотрудник %s[%d] ответил(а) на Ваш вопрос: %s", PN(playerid), playerid, text);
	SendClientMessage(target, 0x4682B4AA, frmt_reply_message);
	pTemp[target][pQuestion] = false;
	pTemp[target][pHallQuestion] = 0;
	return 1;
}
CMD:selllic(playerid, params[])
{
	if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] == 0) return 1;

	if(PI[playerid][pRank] != 4) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только 4-му рангу");
    if(!IsPlayerInDynamicArea(playerid, gHall[PI[playerid][pSubfraction]])) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в мэрии/правительстве");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/selllic [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	if(PI[target][pGunLic] == YES_LICENSE) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть лицензия на оружие");
	if(temp_selllic_sender[target] != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть действующее предложение");

	new mes[128];

	format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} купить лицензию на оружие", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, mes);

	format(mes, sizeof mes, "{FFFFFF}%s{269BD8} предложил(а) Вам купить лицензию на оружие за {33AA33}30000$", PN(playerid));
	SendClientMessage(target, 0x269BD8FF, mes);

	SendClientMessage(target, 0x269BD8FF, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	temp_selllic_receiver[playerid] = target + 1;
	temp_selllic_sender[target] = playerid + 1;
    return 1;
}
CMD:free(playerid, params[])
{
	if(PI[playerid][pFraction] != 10)
	    return 1;

	if(PI[playerid][pRank] != 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только 5-му рангу");

	extract params -> new player:target, price; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/free [ID игрока] [Цена]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(!PI[target][pJailTime])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в тюрьме");

	if(PI[target][pJailAdmin])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выпустить этого игрока");

	if(temp_free_sender[target] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть действующее предложение");

	if(price < 3000 || price > 7000)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сумма должна быть 3000$ до 7000$");

	new
		mes[128];

	format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} выйти из тюрьмы за {33AA33}%d$", PN(target), price);
	SendClientMessage(playerid, 0x269BD8FF, mes);

	format(mes, sizeof mes, "{FFFFFF}%s{269BD8} предложил(а) Вам выйти из тюрьмы за {33AA33}%d$", PN(playerid), price);
	SendClientMessage(target, 0x269BD8FF, mes);

	SendClientMessage(target, 0x269BD8FF, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	temp_free_receiver[playerid] = target + 1;
	temp_free_sender[target] = playerid + 1;
	temp_free_price[target] = price;
    return 1;
}
CMD:sellcard(playerid, params[])
{
	if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] == 0)
	    return 1;

	if(PI[playerid][pRank] != 6)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только 6-му рангу");
	    
    if(!IsPlayerInDynamicArea(playerid, gHall[PI[playerid][pSubfraction]]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в мэрии/правительстве");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/sellcard [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pCard])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть билет рекордсмена");

	if(temp_sellcard_sender[target] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть действующее предложение");

	new
		mes[128];

	format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} купить билет рекордсмена", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, mes);

	format(mes, sizeof mes, "{FFFFFF}%s{269BD8} предложил(а) Вам купить билет рекордсмена за {33AA33}50000$", PN(playerid));
	SendClientMessage(target, 0x269BD8FF, mes);

	SendClientMessage(target, 0x269BD8FF, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	temp_sellcard_receiver[playerid] = target + 1;
	temp_sellcard_sender[target] = playerid + 1;
    return 1;
}
CMD:charity(playerid, params[])
{
	if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] == 0)
	    return 1;

	if(PI[playerid][pRank] != 8)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только 8-му рангу");

    if(!IsPlayerInDynamicArea(playerid, gHall[PI[playerid][pSubfraction]]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в мэрии/правительстве");

	extract params -> new player:target, price; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/charity [ID игрока] [Сумма]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(temp_charity_sender[target] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть действующее предложение");

	if(price < 10000 || price > 10000000)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сумма должна быть от 10000$ до 10000000$");


	new
		mes[128];

	format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} пожертвовать {33AA33}%d$", PN(target), price);
	SendClientMessage(playerid, 0x269BD8FF, mes);

	format(mes, sizeof mes, "{FFFFFF}%s{269BD8} предложил(а) Вам пожертвовать {33AA33}%d$", PN(playerid), price);
	SendClientMessage(target, 0x269BD8FF, mes);

	SendClientMessage(target, 0x269BD8FF, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	temp_charity_receiver[playerid] = target + 1;
	temp_charity_sender[target] = playerid + 1;
	temp_charity_price[target] = price;
    return 1;
}
CMD:rf(playerid, params[])
{
	if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0)
	    return 1;

	if(PI[playerid][pRank] < 4 && PI[playerid][pRank] > 7)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

    if(!pTemp[playerid][pEarsFr] && !pTemp[playerid][pEarsSub])
        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Для начала начните прослушку");
    
    if(PI[playerid][pMuteTime] > 0)
		return SendMuteMessage(playerid);

	if(PI[playerid][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в тюрьме");

	if(sscanf(params, "s[128]", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /rf [текст]");

	new
		fractionid = pTemp[playerid][pEarsFr],
		rank = PI[playerid][pRank],
		frmt_subfract_chat[128];

	SetPlayerChatBubble(playerid, !"Сказал что-то в рацию", 0xDD90FFFF, 10.0, 3000);

	format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] %s %s[%d]: %s", gPrezRankName[rank-1], PN(playerid), playerid, params[0]);

	if(fractionid == 10 && !pTemp[playerid][pEarsSub] && rank <= 9)
		format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] %s %s[%d]: %s", gPrezRankName[rank-1], PN(playerid), playerid, params[0]);

	else if(fractionid == 8 && PI[playerid][pDivision] != 0)
		format(frmt_subfract_chat, sizeof frmt_subfract_chat, "[R] [%s] %s %s[%d]: %s", gDivisionName[PI[playerid][pDivision]-1], gPrezRankName[rank-1], PN(playerid), playerid, params[0]);

  	foreach(new i : Player)
	{
		if(IsPlayerConnected(i) && PI[i][pFraction] == fractionid && PI[i][pSubfraction] == pTemp[playerid][pEarsSub] ||
		pTemp[i][pEarsFr] == fractionid && pTemp[i][pEarsSub] == pTemp[playerid][pEarsSub])
			SendClientMessage(i, 0xACE600FF, frmt_subfract_chat);
	}

	return 1;
}
CMD:rfo(playerid, params[])
{
	if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0)
	    return 1;

	if(PI[playerid][pRank] < 4 && PI[playerid][pRank] > 7)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new subfraction; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/rfo [ID подфракции]");

	if(!pTemp[playerid][pEarsFr] && !pTemp[playerid][pEarsSub])
	{
		new
		    frmt_rf_text[128];

		if(PI[playerid][pRank] == 4)
		{
		    if(subfraction < 1 || subfraction > 3)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный номер подфракции");

	        pTemp[playerid][pEarsFr] = 1;
			pTemp[playerid][pEarsSub] = subfraction;

			format(frmt_rf_text, sizeof frmt_rf_text, "{7AC71F}[Успешно] {FFFFFF}Вы включили подслушку организации %s, подфракции %s", gFractionName[pTemp[playerid][pEarsFr]-1], gSubfractionName[pTemp[playerid][pEarsFr]-1][pTemp[playerid][pEarsSub]-1]);
	        SendClientMessage(playerid, COLOR_WHITE, frmt_rf_text);
		}
		else if(PI[playerid][pRank] == 5)
		{
		    if(subfraction < 1 || subfraction > 3)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный номер подфракции");

	        pTemp[playerid][pEarsFr] = 9;
	        pTemp[playerid][pEarsSub] = subfraction;

			format(frmt_rf_text, sizeof frmt_rf_text, "{7AC71F}[Успешно] {FFFFFF}Вы включили подслушку организации %s, подфракции %s", gFractionName[pTemp[playerid][pEarsFr]-1], gSubfractionName[pTemp[playerid][pEarsFr]-1][pTemp[playerid][pEarsSub]-1]);
	        SendClientMessage(playerid, COLOR_WHITE, frmt_rf_text);
		}
		else if(PI[playerid][pRank] == 6)
		{
		    if(subfraction < 1 || subfraction > 3)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный номер подфракции");

	        pTemp[playerid][pEarsFr] = 8;
	        pTemp[playerid][pEarsSub] = subfraction;

			format(frmt_rf_text, sizeof frmt_rf_text, "{7AC71F}[Успешно] {FFFFFF}Вы включили подслушку организации %s, подфракции %s", gFractionName[pTemp[playerid][pEarsFr]-1], gSubfractionName[pTemp[playerid][pEarsFr]-1][pTemp[playerid][pEarsSub]-1]);
	        SendClientMessage(playerid, COLOR_WHITE, frmt_rf_text);
		}
		else if(PI[playerid][pRank] == 7)
		{
		    if(subfraction < 1 || subfraction > 2)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный номер подфракции");

	        pTemp[playerid][pEarsFr] = 7;
	        pTemp[playerid][pEarsSub] = subfraction;

			format(frmt_rf_text, sizeof frmt_rf_text, "{7AC71F}[Успешно] {FFFFFF}Вы включили подслушку организации %s, подфракции %s", gFractionName[pTemp[playerid][pEarsFr]-1], gSubfractionName[pTemp[playerid][pEarsFr]-1][pTemp[playerid][pEarsSub]-1]);
	        SendClientMessage(playerid, COLOR_WHITE, frmt_rf_text);
		}
		else
	    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	}
	else
	{
        pTemp[playerid][pEarsFr] = 0;
        pTemp[playerid][pEarsSub] = 0;
        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы выключили подслушку организации");
	
	}
	return 1;
}
CMD:bizlist(playerid)
{

	if(!IsAMafia(playerid)) return true;
	if(PI[playerid][pRank] < 8) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	new str[128], count = 0;
	mysql_query_string[0] = 0;
	for(new idx = 1; idx <= OWNABLEBIZES; idx++)
	{
		if(BizInfo[idx][bKrasher] != PI[playerid][pFraction]) continue;
		format(str, sizeof(str), "{FF7319}ID: %d {ffffff}| %s\n", idx, BizInfo[idx][bName]);
		strcat(mysql_query_string, str);
		count++;
	}
	if(!count) return SCM(playerid, COLOR_WHITE, "У вашей мафии нет бизнесов под контролем.");
	new name_dialog[64];
	format(name_dialog, sizeof(name_dialog), "Бизнесы мафии {ffffff}[Кол-во: %d]", count);
	ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_LIST, name_dialog, mysql_query_string, "Закрыть", "");
	mysql_query_string[0] = 0;
    return 1;
}
CMD:mload(playerid)
{
	if(!IsAMafia(playerid)) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем фургона для перевозки патронов");
	new carid = GetPlayerVehicleID(playerid);
	if(VehicleInfo[carid][vTeam] != PI[playerid][pFraction] || GetVehicleModel(carid) != 482 && GetVehicleModel(carid) != 579) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем фургона для перевозки патронов");
	if(VehicleLoad[carid][vlMafLoading] || VehicleLoad[carid][vlMafUnloading]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");

	VehicleLoad[carid][vlID] = carid;
	VehicleLoad[carid][vlMafLoading] = true;
	VehicleLoad[carid][vlMafUnloading] = false;

	RemovePlayerFromVehicle(playerid);

	new Float:x, Float:y, Float:z, Float:a;
	GetVehiclePos(carid, x, y, z);
	GetVehicleZAngle(carid, a);
	x = x - (-3.0*floatsin(a, degrees));
	y = y - 3.0*floatcos(a, degrees);
	VehicleLoad[carid][vlPickup] = CreateDynamicPickup(2061, 1, x, y, z-0.5);
	VehicleLoad[carid][vlArea] = CreateDynamicSphere(x, y, z-0.5, 1.0);
	
	new mes[128];
	format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[carid][vlLimit]);
	VehicleLoad[carid][vlText] = CreateDynamic3DTextLabel(mes, COLOR_WHITE, x, y, z+0.5, 10.0);

    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали загрузку боеприпасов");


  	foreach(new i: Player)
	{
		if(IsPlayerConnected(i) && PI[i][pFraction] == PI[playerid][pFraction])
			pTemp[i][pWarehouseRob] = true;
	}

    return 1;
}
CMD:munload(playerid)
{
	if(!IsAMafia(playerid)) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем фургона для перевозки патронов");
	new carid = GetPlayerVehicleID(playerid);
	if(VehicleInfo[carid][vTeam] != PI[playerid][pFraction] || GetVehicleModel(carid) != 482 && GetVehicleModel(carid) != 579) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем фургона для перевозки патронов");
	if(VehicleLoad[carid][vlMafLoading] || VehicleLoad[carid][vlMafUnloading]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже происходит загрузка / разгрузка");

	VehicleLoad[carid][vlID] = carid;
	VehicleLoad[carid][vlMafLoading] = false;
	VehicleLoad[carid][vlMafUnloading] = true;

    RemovePlayerFromVehicle(playerid);
	new Float:x, Float:y, Float:z, Float:a;

	GetVehiclePos(carid, x, y, z);
	GetVehicleZAngle(carid, a);
	x = x - (-3.0*floatsin(a, degrees));
	y = y - 3.0*floatcos(a, degrees);
	VehicleLoad[carid][vlPickup] = CreateDynamicPickup(2061, 1, x, y, z-0.5);
	VehicleLoad[carid][vlArea] = CreateDynamicSphere(x, y, z-0.5, 1.0);
	
	new
		mes[70];

	format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[carid][vlLimit]);
	VehicleLoad[carid][vlText] = CreateDynamic3DTextLabel(mes, COLOR_WHITE, x, y, z+0.5, 10.0);

    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали разгрузку боеприпасов");

  	foreach(new i: Player)
	{
		if(IsPlayerConnected(i) && PI[i][pFraction] == PI[playerid][pFraction])
			pTemp[i][pWarehouseRob] = false;
	}
    return 1;
}
CMD:rob(playerid, params[])
{
	if(!IsAMafia(playerid)) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_PASSENGER) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на пассажирском месте военной машины для перевозки оружия");
	new carid = GetPlayerVehicleID(playerid);
	if(VehicleInfo[carid][vTeam] != 7 || VehicleInfo[carid][vSubTeam] != 1 || GetVehicleModel(carid) != 433) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на пассажирском месте военной машины для перевозки оружия");
	if(VehicleLoad[carid][vlRob]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже происходит ограбление этого т/с");
	if(VehicleLoad[carid][vlID] == carid)
	{
		if(IsValidDynamic3DTextLabel(VehicleLoad[carid][vlText]))
			DestroyDynamic3DTextLabel(VehicleLoad[carid][vlText]);

		DestroyDynamicArea(VehicleLoad[carid][vlArea]);
		DestroyDynamicPickup(VehicleLoad[carid][vlPickup]);

	    VehicleLoad[carid][vlID] = INVALID_VEHICLE_ID;
		VehicleLoad[carid][vlLoading] = false;
		VehicleLoad[carid][vlUnloading] = false;
		VehicleLoad[carid][vlRob] = false;
		VehicleLoad[carid][vlPickup] = -1;
		VehicleLoad[carid][vlArea] = -1;
		VehicleLoad[carid][vlText] = NONE_3D_TEXT;
	}
	
	VehicleLoad[carid][vlID] = carid;
	VehicleLoad[carid][vlRob] = true;

    RemovePlayerFromVehicle(playerid);
    
	new
		Float:x,
		Float:y,
		Float:z,
		Float:a;

	GetVehiclePos(carid, x, y, z);
	GetVehicleZAngle(carid, a);
	x = x - (-6.0*floatsin(a, degrees));
	y = y - 6.0*floatcos(a, degrees);
	VehicleLoad[carid][vlPickup] = CreateDynamicPickup(2061, 1, x, y, z-0.5);
	VehicleLoad[carid][vlArea] = CreateDynamicSphere(x, y, z-0.5, 1.0);

	new
		mes[128];

	format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[carid][vlLimit]);
	VehicleLoad[carid][vlText] = CreateDynamic3DTextLabel(mes, COLOR_WHITE, x, y, z+0.5, 10.0);

    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали ограбление военной машины");
    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Украдите боеприпасы как можно быстрее и загрузите их себе");
    return 1;
    
}
CMD:tie(playerid, params[])
{
	if(!IsAMafia(playerid)) return 1;
	if(PI[playerid][pRank] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	if(!PI[playerid][pRope]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет веревки");
	extract params -> new player:target; else return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/tie [ID игрока]");
	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(temp_tie_sender[target] != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок связан");

	temp_tie_sender[target] = playerid + 1;
	temp_tie_receiver[playerid] = target + 1;
	
	f_TogglePlayerControllable(target, false);
	
    new frmt_action[120];

    format(frmt_action, sizeof frmt_action, "%s связал(а) %s", PN(playerid), PN(target));
    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
	return 1;
}
CMD:untie(playerid, params[])
{
	if(!IsAMafia(playerid) && !IsACop(playerid))
	    return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	    
	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/untie [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(temp_tie_sender[target] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не связан");
	
	new
	    sender = temp_tie_sender[target]-1;
	    
	temp_tie_sender[target] = INVALID_PLAYER_ID;
	temp_tie_receiver[sender] = INVALID_PLAYER_ID;
	
	f_TogglePlayerControllable(target, true);
	
    new frmt_action[120];

    format(frmt_action, sizeof frmt_action, "%s развязал(а) %s", PN(playerid), PN(target));
    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
	return 1;
}
CMD:bizwar(playerid)
{
	if(!IsAMafia(playerid)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не член мафии");

	if(PI[playerid][pRank] < 9)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	    
	new h; gettime(h);

	if(h < 10 || h > 22)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Использовать команду можно только с 15:00 до 22:00");

	if(IsBizWar)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На данный момент уже идет захват бизнеса!");

	if(MafiaFreeze)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Мафии заморожены");

	new fractionid = PI[playerid][pFraction],business_search;
	
	if(zGangTime[fractionid-1] <= 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сегодня ваша мафия больше не может участвовать в захвате");

    for(new i; i < OWNABLEBIZES; i++)
    {
		if(IsPlayerInRangeOfPoint(playerid, 15.0, BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z]))
		{
		    business_search++;
		    
			if(BizInfo[i][bKrasher] == PI[playerid][pFraction])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот бизнес принадлежит Вашей мафии");

			if(BizInfo[i][bKrasher] == 0)
			{
			    BizInfo[i][bKrasher] = PI[playerid][pFraction];
			    UpdateBiz(i,1);
			    UpdateTextMafia();
			    
				new frmt_fraction_chat[80];
				format(frmt_fraction_chat, sizeof frmt_fraction_chat, "[F] Вы взяли под контроль бизнес \"%s\"", BizInfo[i][bName]);
				for(new b = GetPlayerPoolSize(); b != -1; b--)
				{
					if(PI[b][pFraction] == PI[playerid][pFraction] || pTemp[b][pEars] == PI[playerid][pFraction])
						SendClientMessage(b, 0x4682B4FF, frmt_fraction_chat);
				}
			}
			else
			{
			    new
					mafiastr[35],
					frmt_bizwar_message[180];

				switch(BizInfo[i][bKrasher])
				{
				    case 12: strcat(mafiastr, "Yakuza");
					case 13: strcat(mafiastr, "LCN");
					case 14: strcat(mafiastr, "Колумбийская мафия");
				}

				if(IsPlayerInBandOnline(PI[playerid][pFraction]) < 5)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей мафии мало игроков онлайн!");

				if(IsPlayerInBandOnline(BizInfo[i][bKrasher]) < 5)
				{
				    format(frmt_bizwar_message, sizeof frmt_bizwar_message, "{FF2222}[Ошибка] {FFFFFF}У мафии \"%s\" мало игроков онлайн!", mafiastr);
					return SendClientMessage(playerid, COLOR_WHITE, frmt_bizwar_message);
				}

				format(frmt_bizwar_message, sizeof frmt_bizwar_message, "{FFFFFF}Этот бизнес принадлежит %s\n\nВы действительно хотите начать захват?", mafiastr);
				ShowPlayerDialogEx(playerid, 839, DIALOG_STYLE_MSGBOX, !"Захват бизнеса", frmt_bizwar_message, !"Да", !"Нет");
			}
		}
	}
	
	if(!business_search)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть у бизнеса");

	return 1;
}
CMD:sellmbiz(playerid, params[])
{
	if(!IsAMafia(playerid))
	    return 1;
	    
	if(PI[playerid][pRank] < 10)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(PI[playerid][pSellZones] > 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы продали максимальное кол-во контролей над бизнесом за день");

	if(IsBizWar)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На данный момент идет захват бизнеса!");

	if(MafiaFreeze)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Мафии заморожены");

	new
		business_search;

    for(new i; i < OWNABLEBIZES; i++)
    {
		if(IsPlayerInRangeOfPoint(playerid, 15.0, BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z]))
		{
		    business_search++;

			if(BizInfo[i][bKrasher] != PI[playerid][pFraction])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот бизнес не принадлежит Вашей мафии");


			extract params -> new player:target, price; else
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/sellzone [ID лидера] [Цена]");

			if(!IsPlayerConnected(target) || playerid == target)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

			if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

			if(!IsAMafia(target) && PI[target][pRank] != 10)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не лидер одной из банд");

			if(price < 1 || price > 100000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная цена (от 1$ до 100000$)");

			temp_sellmbiz_receiver[playerid] = target + 1;
			temp_sellmbiz_sender[target] = playerid + 1;
			temp_sellmbiz_id[target] = i+1;
			temp_sellmbiz_price[target] = price;

			new
				mes[280];

		    format(mes, sizeof mes, "Вы предложили {FFFFFF}%s{269BD8} купить у Вас контроль над бизнесом за {FFFFFF}%d${269BD8}", PN(target), price);
			SendClientMessage(playerid, 0x269BD8FF, mes);

			format(mes, sizeof mes, "%s{269BD8} предлагает Вам приобрести контроль над бизнесом за {FFFFFF}%d${269BD8}", PN(playerid), price);
            SendClientMessage(target, COLOR_WHITE, mes);
			SendClientMessage(target, COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

			break;
		}
	}
	
	if(!business_search)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть у бизнеса");

	return true;
}

CMD:disguse(playerid)
{
	if(PI[playerid][pFraction] != 11)
	    return 1;

	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(pTemp[playerid][pDisguse])
	{
        pTemp[playerid][pDisguse] = 0;
        SetPlayerSkinEx(playerid, pTemp[playerid][pDOldSkin]);
        pTemp[playerid][pDOldSkin] = 0;
        SetPlayerColor(playerid, gFractionColor[PI[playerid][pFraction] - 1]);
	    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сняли маскировку");
	}
	
	else
		ShowPlayerDialogEx(playerid, 783, DIALOG_STYLE_LIST, !"Маскировка", !"{FF7319}1.{FFFFFF} The Ballas\n{FF7319}2.{FFFFFF} Grove Street\n{FF7319}3.{FFFFFF} Varios Los Aztecas\n{FF7319}4.{FFFFFF} Los Santos Vagos\n{FF7319}5.{FFFFFF} The Rifa\n{FF7319}6.{FFFFFF} Yakuza\n{FF7319}7.{FFFFFF} LCN\n{FF7319}8.{FFFFFF} Колумбийская мафия\n{FF7319}9.{FFFFFF} Гражданская одежда №1\n{FF7319}10.{FFFFFF} Гражданская одежда №2\n{FF7319}11.{FFFFFF} Гражданская одежда №3", !"Выбор", !"Отмена");

	return 1;
}
CMD:ff(playerid)
{
	if(PI[playerid][pFraction] != 11)
	    return 1;
	    
	if(PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	if(pTemp[playerid][pEars])
	{
        pTemp[playerid][pEars] = 0;
	    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы отключили прослушку");
	}
	
	else
		ShowPlayerDialogEx(playerid, 781, DIALOG_STYLE_LIST, !"Подслушивание", !"{FF7319}1.{FFFFFF} The Ballas\n{FF7319}2.{FFFFFF} Grove Street\n{FF7319}3.{FFFFFF} Varios Los Aztecas\n{FF7319}4.{FFFFFF} Los Santos Vagos\n{FF7319}5.{FFFFFF} The Rifa\n{FF7319}6.{FFFFFF} Yakuza\n{FF7319}7.{FFFFFF} LCN\n{FF7319}8.{FFFFFF} Колумбийская мафия", !"Выбор", !"Отмена");
	return 1;
}
CMD:settag(playerid, params[])
{
	if(PI[playerid][pFraction] != 11)
	    return 1;

	if(PI[playerid][pRank] < 6)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/settag [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pFraction] != PI[playerid][pFraction])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");

	if(PI[target][pRank] >= PI[playerid][pRank])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	temp_division_receiver[playerid] = target + 1;

	new frmt_division_list[113];

	for(new i; i < 5; i++)
		format(frmt_division_list, sizeof frmt_division_list, "%s{FF7319}%d.{FFFFFF} %s\n", frmt_division_list, i+1, gTagName[i]);

	ShowPlayerDialogEx(playerid, 763, DIALOG_STYLE_LIST, !"Выберите подразделение", frmt_division_list, !"Выбор", !"Отмена");
	return 1;
}
CMD:listeners(playerid)
{
	if(PI[playerid][pFraction] != 9)
	    return 1;

	if(!PI[playerid][pSubfraction])
	    return 1;

	if(PI[playerid][pRank] < 5)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

	new
		total_listeners[3],
		frmt_listeners_message[150];
		
  	foreach(new i : Player)
		if(PI[i][pRadio]) total_listeners[PI[i][pRadio]-1]++;

	format(frmt_listeners_message, sizeof frmt_listeners_message, "{FFFFFF}Радио г. Лос-Сантос: %d\nРадио г. Лас-Вентурас: %d\nРадио г. Сан-Фиерро: %d\n", total_listeners[0], total_listeners[1], total_listeners[2]);
	ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Количество слушателей:", frmt_listeners_message, !"ОК", !"");
		
	return 1;
}
CMD:taxi(playerid, params[])
{
	if(PI[playerid][pJob] != 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не водитель такси");

	if(pTemp[playerid][pTaxiID] == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала нужно арендовать такси");

	new
		vehid = GetPlayerVehicleID(playerid);

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || vehid != pTemp[playerid][pTaxiID])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем своего такси");

	extract params -> new player:target; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/taxi [ID игрока]");

	if(!IsPlayerConnected(target) || !IsPlayerLogged[target] || playerid == target)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(GetPlayerState(target) != PLAYER_STATE_PASSENGER || GetPlayerVehicleID(target) != vehid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не Ваш пассажир");

	new
		frmt_taxi_pos[128];
		
	format(frmt_taxi_pos, sizeof frmt_taxi_pos, "%s отправлен запрос на получение данных о месте назначения", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, frmt_taxi_pos);
	
	format(frmt_taxi_pos, sizeof frmt_taxi_pos, "Водитель такси {FFFFFF}%s{269BD8} запросил данные о месте назначения", PN(playerid));
	SendClientMessage(target, 0x269BD8FF, frmt_taxi_pos);
	
	SendClientMessage(target, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Откройте карту и поставьте метку ПКМ на место, куда желаете отправиться");

	pTemp[target][pTaxiSelect] = true;
	pTemp[target][pTaxiDriver] = playerid;
	
	return 1;
}
CMD:untaxi(playerid)
{
	if(PI[playerid][pJob] != 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не водитель такси");

	if(pTemp[playerid][pTaxiID] == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала нужно арендовать такси");

	new
		vehid = GetPlayerVehicleID(playerid);

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || vehid != pTemp[playerid][pTaxiID])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем своего такси");

	RemovePlayerMapIcon(playerid, iconTaxi);

	return 1;
}
CMD:fare(playerid, params[])
{
	if(PI[playerid][pJob] != 2)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не водитель такси");
	    
	if(pTemp[playerid][pTaxiID] == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала нужно арендовать такси");

	new
		vehid = GetPlayerVehicleID(playerid);
		
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || vehid != pTemp[playerid][pTaxiID])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть за рулем своего такси");
	    
	extract params -> new price; else
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/fare [Цена за километр]");

	if(price < 20 || price > 200)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена должна быть от 20 до 200");

	foreach(new i : Player)
    {
		if(i == playerid)
			continue;
			
		if(GetPlayerVehicleID(i) == vehid)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас есть пассажир");
    }

	pTemp[playerid][pTaxiPrice] = price;
	
	new
		frmt_taxi_text[50];
		
	format(frmt_taxi_text, sizeof frmt_taxi_text, "Тариф: {FFEAEA}%d$ за километр", price);
	
	if(IsValidDynamic3DTextLabel(pTemp[playerid][pTaxi3DText]))
		DestroyDynamic3DTextLabel(pTemp[playerid][pTaxi3DText]);
		
	if(!IsValidDynamic3DTextLabel(pTemp[playerid][pTaxi3DText]))
		pTemp[playerid][pTaxi3DText] = CreateDynamic3DTextLabel(frmt_taxi_text, COLOR_WHITE, 0.0, 0.0, 1.5, 20.0, INVALID_PLAYER_ID, vehid);

	return 1;
}
CMD:end(playerid)
{
	if(PI[playerid][pJob] == 1)
	{
		if(temp_bus_id[playerid] != INVALID_VEHICLE_ID)
		{
			new mes[128];
			format(mes, sizeof mes, "{FFFFFF}Вы хотите завершить рабочий день? {66CDAA}$%d{FFFFFF} будет перечислено на Ваш банковский счет", BusMoney[playerid]);
			ShowPlayerDialogEx(playerid, 487, DIALOG_STYLE_MSGBOX, !"Конец рабочего дня", mes, !"Да", !"Нет");
		}
	}
	if(PI[playerid][pJob] == 2)
	{
		if(pTemp[playerid][pTaxiID] != INVALID_VEHICLE_ID)
			ShowPlayerDialogEx(playerid, 494, DIALOG_STYLE_MSGBOX, !"Конец рабочего дня", !"{FFFFFF}Вы хотите завершить рабочий день?", !"Да", !"Нет");
	}
	if(PI[playerid][pJob] == 11)
	{
	    if(pTemp[playerid][pTruckID] != INVALID_VEHICLE_ID)
		ShowPlayerDialogEx(playerid,5558,DIALOG_STYLE_MSGBOX,!"Конец рабочего дня","{FFFFFF}Вы хотите завершить рабочий день?",!"Да",!"Нет");
	}
	if(PI[playerid][pJob] == JOB_MECHANIC)
	{
	    if(pTemp[playerid][pMechID] != INVALID_VEHICLE_ID)
		ShowPlayerDialogEx(playerid,5577,DIALOG_STYLE_MSGBOX,!"Конец рабочего дня","{FFFFFF}Вы хотите завершить рабочий день?",!"Да",!"Нет");
	}
	if(PI[playerid][pJob] == JOB_PRODUCT)
	{
	    if(pTemp[playerid][pProductID] != INVALID_VEHICLE_ID)
		ShowPlayerDialogEx(playerid,5578,DIALOG_STYLE_MSGBOX,!"Конец рабочего дня","{FFFFFF}Вы хотите завершить рабочий день?",!"Да",!"Нет");
	}
	return 1;
}

CMD:getvv(playerid)
{
    if(PI[playerid][pAdmin] < 7) return 1;
	if(ADuty[playerid]!=228) return ShowPlayerDialogEx(playerid,211,1,"Авторизация","{FFFFFF}Введите админ-пароль","Ок","Отмена");
	new string[25];
	format(string,sizeof(string), "Ваш виртуальный мир: %d", GetPlayerVirtualWorld(playerid));
	SCM(playerid, COLOR_WHITE, string);
	return 1;
}
CMD:setvv(playerid, params[])
{
    if(PI[playerid][pAdmin] < 7) return 1;
    if(sscanf(params,"dd",params[0], params[1])) return SCM(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /setvv [id vv]");
    SetPlayerVirtualWorld(playerid, params[1]);
    SCM(playerid, COLOR_WHITE, "Виртуальный мир был изменён");
	return 1;
}



//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
CMD:put(playerid)
{
	if(!temp_eat[playerid])
		return SendClientMessage(playerid, COLOR_GREY, !"У Вас нет продукта.");
		
	new Float: b_pos[4];
	GetPlayerPos(playerid, b_pos[0], b_pos[1], b_pos[2]);
	GetPlayerFacingAngle(playerid, b_pos[3]);
	if(temp_tie_sender[playerid] == INVALID_PLAYER_ID) ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 1, 0, 0, 1000, 1);
	temp_eat[playerid] = 0;
	RemovePlayerAttachedObject(playerid, 0);
	SetPlayerSpecialAction(playerid, 0);
	return true;
}
CMD:eat(playerid)
{
	new hunger,name[32];
	
	switch(temp_eat[playerid])
	{
		case 1: hunger = 20, name = "бургер с курицей", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,2703,6,0.079999,0.065999,0.015999,0.000000,-11.100000,84.900047,1.000000,1.000000,1.000000);
		case 2: hunger = 30, name = "бургер с говядиной", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,2703,6,0.079999,0.065999,0.015999,0.000000,-11.100000,84.900047,1.000000,1.000000,1.000000);
		case 3: hunger = 30, name = "чизбургер", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,2703,6,0.079999,0.065999,0.015999,0.000000,-11.100000,84.900047,1.000000,1.000000,1.000000);
		case 4: hunger = 15, name = "картошка фри";
		case 5: name = "газированный напиток", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,1546,5,0.126999,0.044999,-0.027000,15.999998,-175.499862,1.400000,1.000000,1.000000,1.000000);
		case 6: hunger = 15, name = "пицца Маргарита", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,2702,6,0.049000,0.056000,0.098999,73.800193,-104.900100,-11.700014,1.000000,1.000000,1.000000);
		case 7: hunger = 20, name = "пицца 4 сыра", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,2702,6,0.049000,0.056000,0.098999,73.800193,-104.900100,-11.700014,1.000000,1.000000,1.000000);
		case 8: hunger = 12, name = "кальцоне с ветчиной", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,2702,6,0.049000,0.056000,0.098999,73.800193,-104.900100,-11.700014,1.000000,1.000000,1.000000);
		case 9: name = "газированный напиток", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,1546,5,0.126999,0.044999,-0.027000,15.999998,-175.499862,1.400000,1.000000,1.000000,1.000000);
		case 10: hunger = 20, name = "бургер с курицей", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,2703,6,0.079999,0.065999,0.015999,0.000000,-11.100000,84.900047,1.000000,1.000000,1.000000);
		case 11: hunger = 18, name = "куриные крылышки";
		case 12: hunger = 10, name = "хотдог с куриной сосиской", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,19346,6,0.059000,0.059999,0.000000,-97.399963,0.000000,0.000000);
		case 13: hunger = 8, name = "пирожок с яблоком", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,19883,6,0.079999,0.065999,0.015999,0.000000,-11.100000,84.900047,1.000000,1.000000,1.000000);
		case 14: name = "чай", SetTimerEx("RemovePlayerAttachedObjectDelay",4000,false,"ii",playerid,1), SetPlayerAttachedObject(playerid,100,1546,5,0.126999,0.044999,-0.027000,15.999998,-175.499862,1.400000,1.000000,1.000000,1.000000);
		default: return 1;
	}

	SetPlayerSpecialAction(playerid, 0);
	ClearAnimations(playerid,1);
	RemovePlayerAttachedObject(playerid,0);
	
	if(temp_tie_sender[playerid] == INVALID_PLAYER_ID)
	{
		if(temp_eat[playerid] == 5 || temp_eat[playerid] == 9 || temp_eat[playerid] == 14)
			ApplyAnimation(playerid, "VENDING", "VEND_Drink2_P", 2.0,0,0,0,0,5000,1);

		else
			ApplyAnimation(playerid,"FOOD","EAT_Burger", 2.0,0,0,0,0,5000,1);

	}
    J_SetPlayerHealth(playerid, PI[playerid][pHealth]+hunger);
    
	if(PI[playerid][pHealth] > 100)
		PI[playerid][pHealth] = 100, J_SetPlayerHealth(playerid, 100);
		
	new mes[128];
	format(mes, sizeof mes, "%s съел(-а) %s", PN(playerid), name);

	if(temp_eat[playerid] == 5 || temp_eat[playerid] == 9 || temp_eat[playerid] == 14)
		format(mes, sizeof mes, "%s выпил(-а) %s", PN(playerid), name);
		
	RemovePlayerAttachedObject(playerid,0);
	ProxDetector(25, playerid, mes, COLOR_ME);
	temp_eat[playerid] = 0;
	PI[playerid][pLastEat] = 0;
	UpdatePlayerData(playerid, "LastEat", PI[playerid][pLastEat]);
	
	return 1;
}
CMD:trash(playerid)
{
    if(PI[playerid][pLevel] > 3)
        return 1;

	new
	    frmt_dialog_trash[400];

	format(frmt_dialog_trash, sizeof frmt_dialog_trash, "{FFFFFF}Старых бумажников:\t{00AC77}%d{FFFFFF}\n\
														Пустых бутылок:\t{00AC77}%d{FFFFFF}\n\
														Консервных банок:\t{00AC77}%d{FFFFFF}\n\
														Мятых бумаг:\t{00AC77}%d{FFFFFF}\n\
														Пробок из под бутылок:\t{00AC77}%d{FFFFFF}\n\
														Поломанных телефонов:\t{00AC77}%d{FFFFFF}", PI[playerid][pTrashWallet], PI[playerid][pTrashBottle], PI[playerid][pTrashBank], PI[playerid][pTrashPaper], PI[playerid][pTrashBung], PI[playerid][pTrashPhone]);

	ShowPlayerDialogEx(playerid, 0, DIALOG_STYLE_TABLIST, !"Мусор в рюкзаке", frmt_dialog_trash, !"Отмена", "");
	return 1;
}

CMD:setspawn(playerid, params[])
{
	if(!PI[playerid][pHouseKey])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не проживаете в доме и не арендуете номер в отеле.");

	if(PI[playerid][pFraction] == 7 && PI[playerid][pRank] < 3)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна военным с 3-го ранга");
	    
	if(PI[playerid][pSpawn] == 2)
		ShowPlayerDialogEx(playerid, 916, DIALOG_STYLE_LIST, !"Место появления", !"{FF7319}1.{FFFFFF} Стандартный спавн\n{FF7319}2.{FFFFFF} Дом или отель", !"Выбор", !"Отмена");

	else
		ShowPlayerDialogEx(playerid, 916, DIALOG_STYLE_LIST, !"Место появления", !"{FF7319}1.{FFFFFF} Дом или отель\n{FF7319}2.{FFFFFF} Стандартный спавн", !"Выбор", !"Отмена");
	return true;
}
/*CMD:setcost(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7)
		return 1;

	if(ADuty[playerid] != 228)
		return ShowPlayerDialogEx(playerid, 211, 1, !"Авторизация", !"{FFFFFF}Введите админ-пароль", !"Ок", !"Отмена");

	new id;
	
	if(sscanf(params, "dd", id, params[1]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /setcost [House ID] [цена]");

	if(id < 1 || id > OWNABLEHOUSES)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный House ID");

	new frmt_log[100];
	format(frmt_log, sizeof frmt_log, "{7AC71F}[Успешно] {FFFFFF}Вы изменили цену на дом %d", id);
	SendClientMessage(playerid, COLOR_WHITE, frmt_log);
	
	HouseInfo[id-1][hCost] = params[1];
    UpdateHouse(id-1);
    SaveHouse(id-1);
	return true;
}
CMD:setprice(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7)
		return 1;
	new id;

	if(sscanf(params, "dd", id, params[1]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /setprice [номер бизнеса] [цена]");

	if(id < 1 || id > OWNABLEBIZES)
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный номер бизнеса");

	new frmt_log[100];
	format(frmt_log, sizeof frmt_log, "{7AC71F}[Успешно] {FFFFFF}Вы изменили цену на бизнес %d", id);
	SendClientMessage(playerid, COLOR_WHITE, frmt_log);

	BizInfo[id-1][bCost] = params[1];
    UpdateBiz(id-1);
	return true;
}*/
CMD:setvw(playerid, params[])
{
    if(PI[playerid][pAdmin] < 7) return 1;
    if(sscanf(params,"dd",params[0],params[1])) return 1;
    SetPlayerVirtualWorld(params[0],params[1]);
	return 1;
}
CMD:setint(playerid, params[])
{
    if(PI[playerid][pAdmin] < 7) return 1;
    if(sscanf(params,"dd",params[0],params[1])) return	1;
    SetPlayerInterior(params[0],params[1]);
	return 1;
}
CMD:tpcor(playerid,params[])
{
	if(PI[playerid][pAdmin] < 7) return 1;
	new Float:x,Float:z,Float:y;
	if(sscanf(params,"fff",x,y,z)) return SCM(playerid,-1,"{FFC800}[Подсказка] {FFFFFF}Используйте: /tpcor [x] [y] [z]");
	SetPlayerPos(playerid,Float:x,Float:y,Float:z);
	return 1;
}
CMD:sellsim(playerid, params[])
{
	if(!PI[playerid][pPhone] || !PI[playerid][pTelNum])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет мобильного телефона");
		
	if(!IsPlayerInRangeOfPoint(playerid, 20.0, -28.4828, -82.7246, 1003.5469))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться в 24/7");

	if(sscanf(params,"dd", params[0], params[1]))
        return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /sellsim [ID] [Цена]");
        
	if(!IsPlayerConnected(params[0]) || playerid == params[0])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
		
	if(GetPlayerDistanceToPlayer(playerid, params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(temp_sim_timer[params[0]] != 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игроку уже предложили купить телефон");
		
	if(PI[playerid][pTelNum] < 100000 || PI[playerid][pTelNum] > 999999)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете продать данный номер");
		
	if(PI[playerid][pLevel] < 3)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная команда доступна с 3 уровня");

	new
	    sim_check[7];
	    
	format(sim_check, sizeof sim_check, "%d", PI[playerid][pTelNum]);

	if(sim_check[0] == sim_check[1] && sim_check[1] == sim_check[2] && sim_check[2] == sim_check[3] && sim_check[3] == sim_check[4] && sim_check[4] == sim_check[5] && sim_check[5] == sim_check[1])
	{
		if(params[1] < 500 || params[1] > 5000000)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена не может быть менее $500 и более $5 млн.");
	}
	else if(sim_check[0] > '0' && sim_check[1] == '0' && sim_check[2] == '0' && sim_check[3] == '0' && sim_check[4] == '0' && sim_check[5] == '0')
	{
		if(params[1] < 500 || params[1] > 2000000)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена не может быть менее $500 и более $2 млн.");
	}
	else if(sim_check[0] > '0' && sim_check[1] == sim_check[2] && sim_check[2] == sim_check[3] && sim_check[3] == sim_check[4] && sim_check[4] == sim_check[5] && sim_check[5] == sim_check[1])
	{
		if(params[1] < 500 || params[1] > 1000000)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена не может быть менее $500 и более $1 млн.");
	}
	else if(sim_check[0] == sim_check[1] && sim_check[1] == sim_check[2] && sim_check[2] == sim_check[3] && sim_check[3] == sim_check[4] && sim_check[4] == sim_check[0] && sim_check[5] > '0')
	{
		if(params[1] < 500 || params[1] > 1000000)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена не может быть менее $500 и более $1 млн.");
	}
    else
	{
		if(params[1] < 500 || params[1] > 500000)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена не может быть менее $500 и более $500 тыс.");
    }
    
	if(PI[params[0]][pMoney] < params[1])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока недостаточно денег");

	new
		string[128];
		
	format(string, sizeof string, "Вы предложили {FFFFFF}%s {269BD8} продать ваш номер", PN(params[0]));
	SendClientMessage(playerid, 0x269BD8FF, string);
	
	format(string, sizeof string, "%s {269BD8}предложил Вам купить номер телефона {4271FF}%d{269BD8} за {FF0000}$%d{269BD8}.", PN(playerid), PI[playerid][pTelNum], params[1]);
	SendClientMessage(params[0], COLOR_WHITE, string);

	SendClientMessage(params[0], COLOR_WHITE, !"Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");
	SendClientMessage(params[0], COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}При покупке номера он заменит ваш старый номер.");
	
	temp_sim_seller[params[0]] = playerid + 1;
	temp_sim_buyer[playerid] = params[0] + 1;
	temp_sim_price[params[0]] = params[1];
	temp_sim_num[params[0]] = PI[playerid][pTelNum];
    temp_sim_timer[params[0]] = 60;
    return true;
}
CMD:sellhouse(playerid, params[])
{
	if(!PI[playerid][pHouseKey])
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас нет дома");

	if(!GetString(HouseInfo[PI[playerid][pHouseKey]-1][hOwner],Name(playerid)))
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас нет дома");
				
	if(PI[playerid][pCars])
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас есть машина. Вы должны продать её прежде чем продавать дом");

	new
		houseid = PI[playerid][pHouseKey] - 1;
		
	if(!IsPlayerInRangeOfPoint(playerid, 50.0, HouseInfo[houseid][hEnter_X], HouseInfo[houseid][hEnter_Y], HouseInfo[houseid][hEnter_Z]))
		return SendClientMessage(playerid, COLOR_GREY, !"Вы слишком далеко от своего дома");

	if(sscanf(params,"dD(-1)", params[0], params[1]))
	{
		new str_sell_house[240 + 6];
		format(str_sell_house,sizeof str_sell_house, "{ffffff}Вы хотите продать дом государству за {33aa33}$%d{ffffff} (80# от гос. стоимости)?\n\
		{afafaf}(чтобы продать дом другому игроку введите /sellhouse [ID игрока][Цена])\n\
		{ffffff}Не забудьте забрать денежные средства из своего сейфа", HouseInfo[houseid][hCost]/100*80);
	 	return ShowPlayerDialogEx(playerid, 441, DIALOG_STYLE_MSGBOX, !"Продажа дома", str_sell_house, !"Да", !"Нет");
	}
	
	if(!IsPlayerConnected(params[0]))
		return SendClientMessage(playerid, COLOR_GREY, "Неверный ID игрока");
		
	if(PI[params[0]][pHouseKey])
		return SendClientMessage(playerid, COLOR_GREY, "У игрока уже есть дом");
		
	if(GetPlayerDistanceToPlayer(playerid,params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_GREY, "Вы далеко друг от друга");
		
	if(params[1] < HouseInfo[houseid][hCost] || params [1] > HouseInfo[houseid][hCost]*4)
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Цена не может быть меньше гос. цены дома и больше цены в 4 раза.");

	new
		str_sell_house_params[65 + MAX_PLAYER_NAME + 7];

	format(str_sell_house_params, sizeof str_sell_house_params, "%s {269BD8}предложил Вам купить его дом за {FF0000}$%d{269BD8}.", PN(playerid), params[1]);
	SendClientMessage(params[0], COLOR_WHITE, str_sell_house_params);
	SendClientMessage(params[0], COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	new
		str_sell_house_target[70 + MAX_PLAYER_NAME];

	format(str_sell_house_target, sizeof str_sell_house_target, "Вы предложили {FFFFFF}%s {269BD8} купить ваш дом", PN(params[0]));
	SendClientMessage(playerid, 0x269BD8FF, str_sell_house_target);
	format(str_sell_house_target, sizeof str_sell_house_target, "Вы предложили {FFFFFF}%s{269BD8} купить ваш дом за {33AA33}$%d", PN(params[0]), params[1]);
	SendClientMessage(playerid, COLOR_WHITE, str_sell_house_target);

	temp_house_seller[params[0]] = playerid + 1;
	temp_house_buyer[playerid] = params[0] + 1;
	temp_house_price[params[0]] = params[1];
	temp_house_id[params[0]] = houseid;
    temp_house_timer[params[0]] = 60;
	return true;
}
CMD:sellbusiness(playerid, params[])
{
	if(!PI[playerid][pBizKey] || PI[playerid][pBizKey] > 1000)
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас нет бизнеса");
		
	new
		bizid = PI[playerid][pBizKey] - 1;

	if(!IsPlayerInRangeOfPoint(playerid, 50.0, BizInfo[bizid][bEnter_X], BizInfo[bizid][bEnter_Y], BizInfo[bizid][bEnter_Z]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от своего бизнеса");


	if(sscanf(params,"dd", params[0], params[1]))
        return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /sellbusiness [ID игрока] [Сумма]");


	if(temp_biz_timer[params[0]] > 0)
	    return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У игрока уже есть активное предложение");
	    
	if(!IsPlayerConnected(params[0]))
		return SendClientMessage(playerid, COLOR_GREY, "Неверный ID игрока");

	if(PI[params[0]][pBizKey])
		return SendClientMessage(playerid, COLOR_GREY, "У игрока уже есть бизнес");

	if(pl_afk_time[params[0]] >= 3)
	    return SendClientMessage(playerid, COLOR_GREY, "Этот игрок AFK");

	if(GetPlayerDistanceToPlayer(playerid,params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_GREY, "Вы далеко друг от друга");

	if(params[1] < BizInfo[bizid][bCost] || params [1] > 40000000)
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Цена не может быть меньше гос. цены бизнеса и больше 40 млн.");

	new
		frmt_sell_business[65 + MAX_PLAYER_NAME + 7];

	format(frmt_sell_business, sizeof frmt_sell_business, "%s предложил Вам купить его бизнес за $%d.", PN(playerid), params[1]);
	SendClientMessage(params[0], COLOR_WHITE, frmt_sell_business);
	SendClientMessage(params[0], COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");
	SendClientMessage(params[0], COLOR_WHITE, "/binfo - {269BD8}чтобы посмотреть информацию о предлагаемом бизнесе");

	format(frmt_sell_business, sizeof frmt_sell_business, "Вы предложили %s купить ваш бизнес", PN(params[0]));
	SendClientMessage(playerid, 0x269BD8FF, frmt_sell_business);

	temp_biz_seller[params[0]] = playerid + 1;
	temp_biz_buyer[playerid] = params[0] + 1;
	temp_biz_price[params[0]] = params[1];
	temp_biz_id[params[0]] = bizid;
    temp_biz_timer[params[0]] = 60;
	return true;
}
CMD:sellfilling(playerid, params[])
{
	if(PI[playerid][pBizKey] < 1000)
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас нет АЗС");


	new
		bizid = PI[playerid][pBizKey] - 1000 - 1;

	if(!IsPlayerInRangeOfPoint(playerid, 50.0, gFillingBuy[bizid][0], gFillingBuy[bizid][1], gFillingBuy[bizid][2]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от своего бизнеса");

	if(sscanf(params,"dd", params[0], params[1]))
        return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /sellfilling [ID игрока] [Сумма]");


	if(temp_biz_timer[params[0]] > 0 || temp_fill_timer[params[0]] > 0)
	    return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У игрока уже есть активное предложение");

	if(!IsPlayerConnected(params[0]))
		return SendClientMessage(playerid, COLOR_GREY, "Неверный ID игрока");

	if(PI[params[0]][pBizKey])
		return SendClientMessage(playerid, COLOR_GREY, "У игрока уже есть бизнес");

	if(pl_afk_time[params[0]] > 3)
	    return SendClientMessage(playerid, COLOR_GREY, "Этот игрок AFK");

	if(GetPlayerDistanceToPlayer(playerid,params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_GREY, "Вы далеко друг от друга");

	if(params[1] < gFillings[bizid][fillingPrice] || params [1] > 40000000)
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Цена не может быть меньше гос. цены АЗС и больше 40 млн.");

	new
		frmt_sell_business[65 + MAX_PLAYER_NAME + 7];

	format(frmt_sell_business, sizeof frmt_sell_business, "%s предложил Вам купить его АЗС за $%d.", PN(playerid), params[1]);
	SendClientMessage(params[0], COLOR_WHITE, frmt_sell_business);
	SendClientMessage(params[0], COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");
	SendClientMessage(params[0], COLOR_WHITE, "/binfo - {269BD8}чтобы посмотреть информацию о предлагаемом бизнесе");

	format(frmt_sell_business, sizeof frmt_sell_business, "Вы предложили %s купить вашу АЗС", PN(params[0]));
	SendClientMessage(playerid, 0x269BD8FF, frmt_sell_business);

	temp_fill_seller[params[0]] = playerid + 1;
	temp_fill_buyer[playerid] = params[0] + 1;
	temp_fill_price[params[0]] = params[1];
	temp_fill_id[params[0]] = bizid;
    temp_fill_timer[params[0]] = 60;
	return true;
}
CMD:binfo(playerid)
{
	if(temp_biz_seller[playerid] != INVALID_PLAYER_ID)
	{

		if(!temp_biz_timer[playerid])
		    return 1;

		new
		    id = temp_biz_id[playerid];

	   	new
		   	business_info[390 + 52 + MAX_PLAYER_NAME + 4 + 11 + 11 + 5 + 5 + 5 + 6 + 20 + 80],
			dayprice;

	   	dayprice = BizInfo[id][bCost]/800;

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
	    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Информация о бизнесе", business_info, !"OK", !"");
  	}
  	else if(temp_fill_seller[playerid] != INVALID_PLAYER_ID)
  	{
		if(!temp_fill_timer[playerid])
		    return 1;

		new
		    fillingid = temp_fill_id[playerid];
  	
	    new
	        frmt_filling_info[240 + MAX_PLAYER_NAME + 3 + 8 + 12 + 6 + 6 + 8 + 3];

	    format(frmt_filling_info, sizeof frmt_filling_info, "{FFFFFF}Общая информация:\nВладелец: {269BD8}%s\n{FFFFFF}Кол-во дней: {269BD8}%d\n{FFFFFF}Банк: {269BD8}%d\n{FFFFFF}Состояние: %s\n\n", gFillings[fillingid][fillingOwner], gFillings[fillingid][fillingDay], gFillings[fillingid][fillingBank], (gFillings[fillingid][fillingWorking]) ? ("{33AA33}Работает") : ("{FF0000}Не работает"));
		format(frmt_filling_info, sizeof frmt_filling_info, "%s{4682B4}Количество топлива: %d/%d литров\n{FFFFFF}Оплата: {269BD8}$%d/день", frmt_filling_info, gFillings[fillingid][fillingFuel], gFillings[fillingid][fillingTanks], gFillings[fillingid][fillingPrice]/200);

		ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Информация о АЗС", frmt_filling_info, !"OK", !"");

  	}
	return 1;
}

CMD:sellcar(playerid, params[])
{
	if(!PI[playerid][pCars] || (!PI[playerid][pHouseKey]))
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас нет т/c");

	new
		carID = PI[playerid][pCars],
		slot = GetCarSlot(carID),
		vehicleid = CarInfo[GetCarSlot(carID)][cVehID];

	if(GetPlayerVehicleID(playerid) != vehicleid || GetPlayerState(playerid) != 2)
		return SendClientMessage(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF} Для продажи своего транспорта Вы должны находиться в нём за рулём");

	new
		modelid = GetVehicleModel(vehicleid) - 400;

	if(isnull(params))
	{
	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Для того чтобы продать т/c другому игроку, введите /sellcar [ID игрока] [цена] [0/1 (0 - продажа без номера, 1 - продажа с номером)]");
		new str_sell_car[60 + 6];
		format(str_sell_car,sizeof str_sell_car, "{FFFFFF}Вы хотите продать свое т/c за {33AA33}%d$?", Transport[modelid][trPrice]/100*80);
	 	return ShowPlayerDialogEx(playerid, 440, DIALOG_STYLE_MSGBOX, !"Продажа т/c", str_sell_car, !"Да", !"Нет");
	}
	
	if(sscanf(params, "ddd", params[0], params[1], params[2]))
 		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /sellcar [ID игрока] [цена] [0/1 (0 - продажа без номера, 1 - продажа с номером)]");
	
	if(params[2] < 0 || params[2] > 1)
 		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /sellcar [ID игрока] [цена] [0/1 (0 - продажа без номера, 1 - продажа с номером)]");

	if(0 == strcmp(CarInfo[slot][cNumber], "-") && params[2] == 1 || isnull(CarInfo[slot][cNumber]) && params[2] == 1)
	    return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет номеров");
	

	if(!IsPlayerConnected(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

	if(!PI[params[0]][pHouseKey])
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У игрока нет дома/отеля");

	if(PI[params[0]][pCars])
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У игрока уже есть т/c");

	if(GetPlayerDistanceToPlayer(playerid,params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(params[1] < Transport[modelid][trPrice] || params [1] > Transport[modelid][trPrice]*4)
		return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Цена не может быть меньше гос. цены т/c и больше цены в 4 раза больше.");

	new
		frmt_sellc_params[115 + MAX_PLAYER_NAME + 7];

	if(params[2])
    	format(frmt_sellc_params, sizeof frmt_sellc_params, "%s {269BD8}предложил Вам купить его авто (с номерами %s).", PN(playerid), CarInfo[slot][cNumber]);
    
	else
		format(frmt_sellc_params, sizeof frmt_sellc_params, "%s {269BD8}предложил Вам купить его авто (без номеров).", PN(playerid));
		
	SendClientMessage(params[0], COLOR_WHITE, frmt_sellc_params);
	
	new
	    classname[30];
	    
	switch(Transport[modelid][trClass])
	{
		case 0: format(classname,sizeof classname,"Эконом");
		case 1: format(classname,sizeof classname,"Средний");
		case 2: format(classname,sizeof classname,"Спорт");
		case 3: format(classname,sizeof classname,"Мото");
		case 4: format(classname,sizeof classname,"Воздушный");
	}
	
	format(frmt_sellc_params, sizeof frmt_sellc_params, "Цена: {FF0000}%d${42B02C} | Название: %s | Класс: %s | Пробег: %.0f | Бензобак: %dл. | Расход: %dл/100км", params[1], Transport[modelid][trName], classname, CarInfo[slot][cMilage], Transport[modelid][trTank], Transport[modelid][trConsumption]);
	SendClientMessage(params[0], COLOR_GREEN, frmt_sellc_params);
	SendClientMessage(params[0], COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	new
		frmt_sellc_target[90 + MAX_PLAYER_NAME];

	if(params[2])
		format(frmt_sellc_target, sizeof frmt_sellc_target, "Вы предложили {FFFFFF}%s {269BD8} купить ваше т/c с номерами", PN(params[0]));
		
	else
	    format(frmt_sellc_target, sizeof frmt_sellc_target, "Вы предложили {FFFFFF}%s {269BD8} купить ваше т/c без номеров", PN(params[0]));
	    
	SendClientMessage(playerid, 0x269BD8FF, frmt_sellc_target);

	temp_car_seller[params[0]] = playerid + 1;
	temp_car_buyer[playerid] = params[0] + 1;
	temp_car_price[params[0]] = params[1];
	temp_car_id[params[0]] = carID;
	temp_car_number[params[0]] = params[2];
    temp_car_timer[params[0]] = 60;
	
    return true;
}


CMD:wedding(playerid, params[])
{
	if(PI[playerid][pLevel] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не достигли 3 уровня");
	if(PI[playerid][pWedding]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Превышен лимит свадеб за день");
	if(!IsPlayerInRangeOfPoint(playerid, 20.0, -1989.8998,1117.9297,54.4688)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от церкви");
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /wedding [ID игрока]");
	if(!IsPlayerConnected(params[0]) || params[0] == playerid) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");
	if(PI[params[0]][pLevel] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данный игрок не достиг 3 уровня");
	if(temp_wedding_sender[params[0]] != INVALID_PLAYER_ID || temp_wedding_receiver[playerid] != INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас или у игрока уже есть активное предложение");
	if(GetPlayerDistanceToPlayer(playerid,params[0]) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0])) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	if(strlen(PI[playerid][pMerrit]) > 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже состоите в браке");
	if(PI[playerid][pSex] == 2) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Предложение может отправить только мужчина");
	if(PI[playerid][pSex] == PI[params[0]][pSex]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Однополые браки запрещены!");
	if(strlen(PI[params[0]][pMerrit]) > 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже состоит в браке");
    
	new string[128];

	format(string, sizeof string, "%s предлагает Вам вступить в брак", PN(playerid));
	SendClientMessage(params[0], COLOR_WHITE, string);
	SendClientMessage(params[0], COLOR_WHITE, "Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N");

	format(string, sizeof string, "Вы предложили %s вступить в брак", PN(params[0]));
	SendClientMessage(playerid, 0x269BD8FF, string);

	temp_wedding_sender[params[0]] = playerid + 1;
	temp_wedding_receiver[playerid] = params[0] + 1;
    return true;
}
CMD:divorce(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 20.0, -1989.8998,1117.9297,54.4688)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от церкви");
	if(!strlen(PI[playerid][pMerrit])) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в браке");
	
	new string[128];
	format(string, sizeof string, "{FFFFFF}Вы женаты на: {ADFF2F}%s\n\n{FFFFFF}Желаете расторгнуть брак?", PI[playerid][pMerrit]);
	ShowPlayerDialogEx(playerid, 824, DIALOG_STYLE_MSGBOX, !"Церковь", string, !"Да", !"Отмена");
	return true;
}

CMD:home(playerid, params[])
{
    new house = PI[playerid][pHouseKey]-1;

	if(!IsPlayerLogged[playerid])
		return false;

	if(!PI[playerid][pHouseKey])
		return SendClientMessage(playerid, COLOR_GREY, !"У Вас нет дома");

	new
	    str_frmt[445];
	    
	if(HouseInfo[house][hLevel] > 0)
		format(str_frmt, sizeof str_frmt, "{FF7319}1.{FFFFFF} Открыть / закрыть дом\n{FF7319}2.{FFFFFF} Информация о доме\n{FF7319}3.{FFFFFF} Улучшения\n{FF7319}4.{FFFFFF} Продать домашний транспорт\n{FF7319}5.{FFFFFF} Доставить транспорт к дому {FF5000}1000${FFFFFF}\n{FF7319}6.{FFFFFF} Отметить транспорт на GPS\n{FF7319}7.{FFFFFF} Продать дом\n{FF7319}8.{FFFFFF} Снять тюнинг с транспорта  {FF5000}15.000$\n{FF7319}9.{FFFFFF} Подселить жильцов\n{FF7319}10.{FFFFFF} Список жильцов");
	    
	else
		format(str_frmt, sizeof str_frmt, "{FF7319}1.{FFFFFF} Открыть / закрыть дом\n{FF7319}2.{FFFFFF} Информация о доме\n{FF7319}3.{FFFFFF} Улучшения\n{FF7319}4.{FFFFFF} Продать домашний транспорт\n{FF7319}5.{FFFFFF} Доставить транспорт к дому {FF5000}1000${FFFFFF}\n{FF7319}6.{FFFFFF} Отметить транспорт на GPS\n{FF7319}7.{FFFFFF} Продать дом\n{FF7319}8.{FFFFFF} Снять тюнинг с транспорта  {FF5000}15.000$");

	if(GetString(HouseInfo[house][hOwner], PN(playerid)))
		ShowPlayerDialogEx(playerid, 174, DIALOG_STYLE_LIST, !"Управление домом", str_frmt, !"ОК", !"Отмена");
	
	else
		ShowPlayerDialogEx(playerid, 174, DIALOG_STYLE_LIST, !"Управление домом", !"{FF7319}1.{FFFFFF} Открыть / закрыть дом\n{FF7319}2.{FFFFFF} Информация о доме\n{FF7319}3.{FFFFFF} Улучшения\n{FF7319}4.{FFFFFF} Продать домашний транспорт\n{FF7319}5.{FFFFFF} Доставить транспорт к дому {FF5000}1000${FFFFFF}\n{FF7319}6.{FFFFFF} Отметить транспорт на GPS\n{FF7319}7.{FFFFFF} Продать дом\n{FF7319}8.{FFFFFF} Снять тюнинг с транспорта  {FF5000}15.000$\n{FF7319}9.{FFFFFF} {FF5000}Выселиться", !"ОК", !"Отмена");

	return true;
}
CMD:store(playerid)
{
	if(!HouseEntered[playerid]) return SendClientMessage(playerid, COLOR_GREY, "Вы должны находиться в доме");
	new houseid = HouseEntered[playerid]-1;
	new hintid = HouseInfo[houseid][hNumInt]-1;
	
	if(PI[playerid][pHouseKey] != houseid && !GetString(HouseInfo[houseid][hOwner] , Name(playerid)))
		return SendClientMessage(playerid, COLOR_GREY, "Только владелец дома может пользоваться шкафом");
		
	if(!HouseInfo[houseid][hImprove][2])
		return SendClientMessage(playerid, COLOR_GREY, "У Вас нет шкафа");
		
	if(!IsPlayerInDynamicArea(playerid, HintStoreArea[hintid]))
		return SendClientMessage(playerid,COLOR_GREY,"Вы должны быть возле шкафа");

    ShowPlayerDialogEx(playerid, 540, DIALOG_STYLE_LIST, !"Шкаф", !"Взять оружие\nПоложить оружие\nВыбрать одежду\nВыкинуть одежду", !"Далее", !"Отмена");
    return true;
}
CMD:safe(playerid)
{
	if(!HouseEntered[playerid]) return SendClientMessage(playerid, COLOR_GREY, "Вы должны находиться в доме");
	new houseid = HouseEntered[playerid]-1;
	new hintid = HouseInfo[houseid][hNumInt]-1;

	if(PI[playerid][pHouseKey] != houseid && !GetString(HouseInfo[houseid][hOwner] , Name(playerid)))
		return SendClientMessage(playerid, COLOR_GREY, "Только владелец дома может пользоваться сейфом");

	if(!HouseInfo[houseid][hImprove][1])
		return SendClientMessage(playerid, COLOR_GREY, "У Вас нет сейфа");

	if(!IsPlayerInDynamicArea(playerid, HintSafeArea[hintid]))
		return SendClientMessage(playerid,COLOR_GREY,"Вы должны быть возле сейфа");

    ShowPlayerDialogEx(playerid, 541, DIALOG_STYLE_INPUT, !"Сейф", !"{FFFFFF}Введите код от сейфа:", !"ОК", !"Отмена");
	return true;
}
/*CMD:freez(playerid)
{
	if(!HouseEntered[playerid]) return SendClientMessage(playerid, COLOR_GREY, "Вы должны находиться в доме");
	new houseid = HouseEntered[playerid]-1;
	new hintid = HouseInfo[houseid][hNumInt]-1;

	if(!PI[playerid][pHouseKey])
		if(!GetString(HouseInfo[PI[playerid][pHouseKey]-1][hOwner] , Name(playerid)))
			return SendClientMessage(playerid, COLOR_GREY, "Только владелец дома может пользоваться холодильником");

	if(!HouseInfo[houseid][hImprove][2])
		return SendClientMessage(playerid, COLOR_GREY, "У Вас нет холодильника");

	if(!IsPlayerInDynamicArea(playerid, HintFreezArea[hintid]))
		return SendClientMessage(playerid,COLOR_GREY,"Вы должны быть возле холодильника");

	return true;
}
*/
CMD:healme(playerid)
{
	if(!PI[playerid][pKit])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет аптечек");

    if(pTemp[playerid][pPaintTeam])
        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нельзя использовать во время игры в PaintBall");
    
    if(GetPVarInt(playerid,"narko") > gettime())
		return 1;
		
    if(GetPVarInt(playerid,"healme") > gettime())
		return 1;

    if(GetPVarInt(playerid,"mask") > gettime())
		return 1;

	PI[playerid][pKit]--;
	UpdatePlayerData(playerid, "Kit", PI[playerid][pKit]);
	J_SetPlayerHealth(playerid, 100.0);

	new
	    frmt_healme[MAX_PLAYER_NAME + 40];
	    
    format(frmt_healme, sizeof frmt_healme, "%s перебинтовал рану", PN(playerid));
    SetPlayerChatBubble(playerid, "перебинтовал рану", COLOR_PURPLE, 15.0, 5000);
    ProxDetector(25.0, playerid, frmt_healme, COLOR_ME);
    
	if(temp_tie_sender[playerid] == INVALID_PLAYER_ID) ApplyAnimation(playerid,"ped","gum_eat",4.0,0,0,0,0,0,1);
	
	SetPVarInt(playerid, "healme", gettime()+6);
	return 1;
}
CMD:repair(playerid, params[])
{
	if(PI[playerid][pJob] == JOB_MECHANIC)
	{
		if(GetPlayerState(playerid) != 2) return SCM(playerid, COLOR_GREY, "Вы должны находиться за рулем эвакуатора!");
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(vehicleid) == 525)
		{
   			if(pTemp[playerid][pMechID] != vehicleid) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не начали работу автомеханика.");
			if(sscanf(params, "ui", params[0], params[1])) return SCM(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /repair [id игрока] [Цена]");
			if(!IsPlayerConnected(params[0])) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в сети");
			if(IsPlayerLogged[params[0]] == false) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не авторизовался");
			if(params[1] > 2000 || params[1] < 1) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена может быть от 1 до 2000$");
			if(!IsPlayerInRangeOfPlayer(15.0, playerid, params[0])) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данный игрок слишком далеко!");
			if(GetPlayerState(params[0]) != 2) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок должен находиться за рулем транспорта!");
			if(params[0] == playerid) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы указали свой ID");
			if(temp_repair_sender[params[0]] != INVALID_PLAYER_ID) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данному игроку уже предложили починку/заправку!");
			if(GetMoney(params[0]) < params[1]) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нету денег");
			if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0])) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко от игрока");

			totalstring[0] = 0;
			format(totalstring, 150, "Вы предложили %s починить его т/с за %i$.", PN(params[0]), params[1]);
			SendClientMessage(playerid, 0x269BD8FF, totalstring);

			format(totalstring, 200, "%s {269BD8}хочет починить ваше т/с за %i$. Подтвердить {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid), params[1]);
			SendClientMessage(params[0], COLOR_WHITE, totalstring);

			temp_repair_sender[params[0]] = playerid;
			SetPVarInt(params[0], "MechanicPrice", params[1]);
			totalstring[0] = 0;
		}
		else SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться в эвакуаторе!");
	}
	return true;
}
CMD:refill(playerid, params[])
{
	if(PI[playerid][pJob] == JOB_MECHANIC)
	{
		if(GetPlayerState(playerid) != 2) return SCM(playerid, COLOR_GREY, "Вы должны находиться за рулем эвакуатора!");
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(vehicleid) == 525)
		{
   			if(pTemp[playerid][pMechID] != vehicleid) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не начали работу автомеханика.");
			if(sscanf(params, "udi", params[0], params[1],params[2])) return SCM(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /refill [id игрока] [Кол-во топлива] [Цена]");
			if(!IsPlayerConnected(params[0])) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в сети");
			if(IsPlayerLogged[params[0]] == false) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не авторизовался");
			if(params[2] > 5000 || params[2] < 1) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена может быть от 1 до 5000$");
			if(params[1] < 1 || params[1] > 150) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Введите кол-во топлива от 1 до 150.");
			if(!IsPlayerInRangeOfPlayer(15.0, playerid, params[0])) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данный игрок слишком далеко!");
			if(GetPlayerState(params[0]) != 2) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок должен находиться за рулем транспорта!");
			if(params[0] == playerid) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы указали свой ID");
			if(pTemp[playerid][pMechFuel] < params[1]) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно бензина");
			if(temp_fill_sender[params[0]] != INVALID_PLAYER_ID) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данному игроку уже предложили заправиться!");
			if(GetMoney(params[0]) < params[2]) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нету денег");
			if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0])) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко от игрока");
			
			new vehid = GetPlayerVehicleID(params[0]);
			new modelid = GetVehicleModel(vehid) - 400;
			if(VehicleInfo[vehid][vFuel] + params[1] > Transport[modelid][trTank]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже достаточно топлива");
			if(!Transport[modelid][trFuelable]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Т/С игрока не имеет бензобака");
			
			totalstring[0] = 0;
			format(totalstring, 150, "Вы предложили %s заправить его транспорт на %i литров за %i$.", PN(params[0]), params[1], params[2]);
			SendClientMessage(playerid, 0x269BD8FF, totalstring);

			format(totalstring, 200, "%s {269BD8}хочет заправить ваше т/с на %i литров за %i$. Подтвердить {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid), params[1], params[2]);
			SendClientMessage(params[0], COLOR_WHITE, totalstring);
			
			temp_fill_sender[params[0]] = playerid;
			SetPVarInt(params[0], "MechanicPrice", params[2]);
			SetPVarInt(params[0], "MechanicFuel", params[1]);
			totalstring[0] = 0;
		}
		else SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться в эвакуаторе!");
	}
	return true;
}
CMD:healup(playerid)
{
	if(!BizEntered[playerid])
		return 1;

	if(!BizInfo[BizEntered[playerid]-1][bImprove][0])
	    return 1;

    if(GetPVarInt(playerid,"narko") > gettime())
		return 1;

    if(GetPVarInt(playerid,"healme") > gettime())
		return 1;

    if(GetPVarInt(playerid,"mask") > gettime())
		return 1;

	J_SetPlayerHealth(playerid,100.0);

	new
	    frmt_healme[MAX_PLAYER_NAME + 40];

    format(frmt_healme, sizeof frmt_healme, "%s перебинтовал рану", PN(playerid));
    SetPlayerChatBubble(playerid, "перебинтовал рану", COLOR_PURPLE, 15.0, 5000);
    ProxDetector(25.0, playerid, frmt_healme, COLOR_ME);
    
	GiveMoney(playerid, -150, "покупка аптечки");

	if(BizInfo[BizEntered[playerid]-1][bProducts] - 80 > 0)
	{
		BizInfo[BizEntered[playerid]-1][bProducts] -= 80;
		GiveBusinessMoney(BizEntered[playerid]-1, 110);
		if(BizInfo[BizEntered[playerid]-1][bKrasher]) GiveFracBank(BizInfo[BizEntered[playerid]-1][bKrasher],15);
	}
	UpdateBiz(BizEntered[playerid]-1,1);

	if(temp_tie_sender[playerid] == INVALID_PLAYER_ID) ApplyAnimation(playerid,"ped","gum_eat",4.0,0,0,0,0,0,1);
	SetPVarInt(playerid, "healme", gettime()+6);
	return 1;
}

CMD:exit(playerid)
{
	if(!IsPlayerLogged[playerid])
		return false;
		
	new i = HouseEntered[playerid]-1;
	
    if(IsPlayerInRangeOfPoint(playerid,2.0,HouseInfo[i][hExit_X],HouseInfo[i][hExit_Y],HouseInfo[i][hExit_Z]))
    {
 		if(GetPlayerVirtualWorld(playerid) == (HouseEntered[playerid]+50))
 		{
			justtp_exit[playerid] = true;

         	pTemp[playerid][pAntiAir] += 4;
         	SetPlayerInterior(playerid,0);
         	SetPlayerVirtualWorld(playerid,0);
         	SetPlayerPos(playerid,HouseInfo[i][hEnter_X],HouseInfo[i][hEnter_Y],HouseInfo[i][hEnter_Z]);
         	J_SetPlayerFacingAngle(playerid, HouseInfo[i][hEnter_R]);
         	HouseEntered[playerid] = 0;
         	return true;
 		}
    }
	return true;
}


CMD:lights(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new
			carid = GetPlayerVehicleID(playerid);
			
		if(IsABike(carid))
			return 1;
			
		SetLightsStatus(carid);
	}
	return true;
}

CMD:pass(playerid, params[])
{
    extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /pass [ID игрока]");

	if(!IsPlayerConnected(target))
	    return SendClientMessage(playerid, COLOR_GREY, !"Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_GREY, !"Вы далеко друг от друга");

	if(target != playerid)
	{
		new
			frmt_pass_sender[56 + MAX_PLAYER_NAME],
			frmt_pass_receiver[MAX_PLAYER_NAME + 101];

		format(frmt_pass_sender, sizeof frmt_pass_sender, "Вы предложили {FFFFFF}%s {269BD8}показать свой паспорт", PN(target));
		SendClientMessage(playerid, 0x269BD8FF, frmt_pass_sender);

		format(frmt_pass_receiver, sizeof frmt_pass_receiver, "%s {269BD8}хочет показать Вам паспорт. Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid));
		SendClientMessage(target, COLOR_WHITE, frmt_pass_receiver);

		temp_pass_sender[target] = playerid + 1;
		temp_pass_receiver[playerid] = target + 1;
	}
	else
	{
		new string[MAX_PLAYER_NAME + 50];
		format(string, sizeof string, "%s достал(а) паспорт и рассматривает его", cPN(playerid));
		ProxDetector(25, playerid, string, COLOR_ME);
	
        ShowPass(playerid, playerid);
	}
	return true;
}
CMD:lic(playerid, params[])
{
    extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /lic [ID игрока]");

	if(!IsPlayerConnected(target))
	    return SendClientMessage(playerid, COLOR_GREY, !"Неверный ID");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_GREY, !"Вы далеко друг от друга");

	if(target != playerid)
	{
		new
			frmt_lic_sender[57 + MAX_PLAYER_NAME],
			frmt_lic_receiver[MAX_PLAYER_NAME + 103];

		format(frmt_lic_sender, sizeof frmt_lic_sender, "Вы предложили {FFFFFF}%s {269BD8} показать лицензии", PN(target));
		SendClientMessage(playerid, 0x269BD8FF, frmt_lic_sender);

		format(frmt_lic_receiver, sizeof frmt_lic_receiver, "%s {269BD8}хочет показать Вам лицензии. Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid));
		SendClientMessage(target, COLOR_WHITE, frmt_lic_receiver);

		temp_lic_sender[target] = playerid + 1;
		temp_lic_receiver[playerid] = target + 1;
	}
	else
	{
		new string[MAX_PLAYER_NAME + 70];
		format(string, sizeof string, "%s достал(а) свои лицензии и рассматривает их", cPN(playerid));
		ProxDetector(25, playerid, string, COLOR_ME);

		ShowLic(playerid, playerid);
	}
	return true;
}
CMD:skill(playerid, params[])
{
    extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /skill [ID игрока]");

	if(!IsPlayerConnected(target))
	    return SendClientMessage(playerid, COLOR_GREY, !"Неверный ID игрока");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_GREY, !"Вы далеко друг от друга");

	if(target != playerid)
	{
		new
			frmt_skill_sender[60 + MAX_PLAYER_NAME],
			frmt_skill_receiver[MAX_PLAYER_NAME + 110];

		format(frmt_skill_sender, sizeof frmt_skill_sender, "Вы предложили {FFFFFF}%s{269BD8} показать выписку из тира", PN(target));
		SendClientMessage(playerid, 0x269BD8FF, frmt_skill_sender);

		format(frmt_skill_receiver, sizeof frmt_skill_receiver, "%s {269BD8}хочет показать Вам выписку из тира. Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid));
		SendClientMessage(target, COLOR_WHITE, frmt_skill_receiver);
		
		new string[MAX_PLAYER_NAME + 70];
		format(string, sizeof string, "%s достал(а) свою выписку из тира", cPN(playerid));
		ProxDetector(25, playerid, string, COLOR_ME);
		
		temp_skill_sender[target] = playerid + 1;
		temp_skill_receiver[playerid] = target + 1;
	}
	else
	{
		new string[MAX_PLAYER_NAME + 120];
		format(string, sizeof string, "%s достал(а) выписку из тира и рассматривает ее", cPN(playerid));
		ProxDetector(25, playerid, string, COLOR_ME);
		
        ShowSkill(playerid, playerid);
	}
	return true;
}

CMD:med(playerid, params[])
{
    extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /med [ID]");

	if(!IsPlayerConnected(target))
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в сети");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок слишком далеко");

	if(target != playerid)
	{
		new
			frmt_med_sender[68 + MAX_PLAYER_NAME],
			frmt_med_receiver[MAX_PLAYER_NAME + 117];

		format(frmt_med_sender, sizeof frmt_med_sender, "Вы предложили {FFFFFF}%s {269BD8} показать свою медицинскую карту", PN(target));
		SendClientMessage(playerid, 0x269BD8FF, frmt_med_sender);

		format(frmt_med_receiver, sizeof frmt_med_receiver, "%s {269BD8}хочет показать Вам свою медицинскую карту. Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid));
		SendClientMessage(target, COLOR_WHITE, frmt_med_receiver);

		temp_med_sender[target] = playerid + 1;
		temp_med_receiver[playerid] = target + 1;
	}
	else
	{
		new string[MAX_PLAYER_NAME + 140];
		format(string, sizeof string, "%s достал(а) медицинскую карту и рассматривает ее", cPN(playerid));
		ProxDetector(25, playerid, string, COLOR_ME);
		
        ShowMed(playerid, playerid);
	}
	return true;
}
CMD:pts(playerid, params[])
{
	if(!PI[playerid][pCars])
	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет т/с");

    if(!PI[playerid][pPTS])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет ПТС");

	extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /pts [ID]");

	if(!IsPlayerConnected(target) || !PI[target][pID] || !IsPlayerLogged[target])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		
	/**/
    
	if(target != playerid)
	{
		new
			frmt_pts_sender[68 + MAX_PLAYER_NAME],
			frmt_pts_receiver[MAX_PLAYER_NAME + 117];

		format(frmt_pts_sender, sizeof frmt_pts_sender, "Вы предложили {FFFFFF}%s {269BD8} показать свой ПТС", PN(target));
		SendClientMessage(playerid, 0x269BD8FF, frmt_pts_sender);

		format(frmt_pts_receiver, sizeof frmt_pts_receiver, "%s {269BD8}хочет показать Вам свой ПТС. Чтобы подтвердить нажмите {33AA33}Y{269BD8}, иначе {FF0000}N", PN(playerid));
		SendClientMessage(target, COLOR_WHITE, frmt_pts_receiver);

		temp_pts_sender[target] = playerid + 1;
		temp_pts_receiver[playerid] = target + 1;
	}
	else
	{
		new string[MAX_PLAYER_NAME + 140];
		format(string, sizeof string, "%s достал(а) ПТС и рассматривает его", PN(playerid));
		ProxDetector(25, playerid, string, COLOR_ME);

        ShowPTS(playerid, playerid);
	}
	return 1;
}
CMD:givevkey(playerid, params[])
{
	if(!PI[playerid][pCars])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с");
		
	extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /givevkey [ID]");

	if(!IsPlayerConnected(target) || !PI[target][pID] || target == playerid || !IsPlayerLogged[target])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");
	
	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
		
	if(PI[target][pVehicleKey] != 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть ключи от т/с");
		
	PI[target][pVehicleKey] = PI[playerid][pCars];
	
	UpdatePlayerData(target, "VehicleKey", PI[target][pVehicleKey]);
	
	new string[128];
	format(string, sizeof string, "Вы получили ключи от т/с от {FFFFFF}%s", PN(playerid));
	SendClientMessage(target, 0x269BD8FF, string);
	
	format(string, sizeof string, "Вы выдали {FFFFFF}%s {269BD8} ключи от вашего т/с", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, string);
	return true;
}
CMD:takevkey(playerid, params[])
{
	if(!PI[playerid][pCars])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с");

    extract params -> new player:target; else
		return SendClientMessage(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /takevkey [ID]");

	if(!IsPlayerConnected(target) || !PI[target][pID] || target == playerid || !IsPlayerLogged[target])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

	if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

	if(PI[target][pVehicleKey] != PI[playerid][pCars])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет ключей от вашего т/с");

	PI[target][pVehicleKey] = 0;

	UpdatePlayerData(target, "VehicleKey", 0);

	new string[128];
	format(string, sizeof string, "%s {269BD8}забрал у вас ключи от т/с", PN(playerid));
	SendClientMessage(target, COLOR_WHITE, string);

	format(string, sizeof string, "Вы забрали у {FFFFFF}%s {269BD8} ключи от вашего т/с", PN(target));
	SendClientMessage(playerid, 0x269BD8FF, string);
	
	return true;
}
CMD:dropvkey(playerid)
{
	if(!PI[playerid][pVehicleKey])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет ключей от т/с");

	PI[playerid][pVehicleKey] = 0;
	UpdatePlayerData(playerid, "VehicleKey", 0);
	SendClientMessage(playerid, COLOR_GREEN, !"Вы выбросили ключи от т/с");
	return true;
}


CMD:mask(playerid, params[])
{
	if(GetPVarInt(playerid,"narko") > gettime())
		return 1;

    if(GetPVarInt(playerid,"healme") > gettime())
		return 1;

    if(GetPVarInt(playerid,"mask") > gettime())
		return 1;
		
    if(!pTemp[playerid][pPaintTeam])
    {
		if(!PI[playerid][pMask])
        	return SendClientMessage(playerid, COLOR_GREY, !"У Вас нет маски");

	    if(PI[playerid][pMaskON])
	        return SendClientMessage(playerid, COLOR_GREY, !"Вы уже одели маску");

		SetPlayerColor(playerid, 0x7a766700);
		SendClientMessage(playerid, 0x4682B4AA, "Вы надели маску. Ваше местоположение скрыто (Введите /maskoff, чтобы снять маску)");

		new stringex[100];
		format(stringex,sizeof(stringex),"~b~Mask on");
	    GameTextForPlayer(playerid, stringex, 5000, 3);

	    ApplyAnimation(playerid, !"shop", !"ROB_Shifty", 4.0, 0, 0, 0, 0, 0, 1);
		SetPlayerChatBubble(playerid, "Одевает маску", 0xFF9900AA, 30.0, 10000);

		SetPlayerAttachedObject(playerid, 8, 19801, 2, 0.064999, 0.028999, 0.000000, 0.000000, 80.300003, 178.900009, 1.330000, 1.25, 1.125000);
		PI[playerid][pMask] = 0;
		UpdatePlayerData(playerid, "Mask", PI[playerid][pMask]);
		PI[playerid][pMaskON] = 1;
	}
	else
	{
	    if(PI[playerid][pMaskON])
	        return SendClientMessage(playerid, COLOR_GREY, !"Вы уже одели маску");

		SetPlayerColor(playerid, 0x7a766700);
		SendClientMessage(playerid, 0x4682B4AA, "Вы надели маску. Ваше местоположение скрыто (Введите /maskoff, чтобы снять маску)");

		new stringex[100];
		format(stringex,sizeof(stringex),"~b~Mask on");
	    GameTextForPlayer(playerid, stringex, 5000, 3);

	    ApplyAnimation(playerid, !"shop", !"ROB_Shifty", 4.0, 0, 0, 0, 0, 0, 1);
		SetPlayerChatBubble(playerid, "Одевает маску", 0xFF9900AA, 30.0, 10000);

		SetPlayerAttachedObject(playerid, 8, 19801, 2, 0.064999, 0.028999, 0.000000, 0.000000, 80.300003, 178.900009, 1.330000, 1.25, 1.125000);
		PI[playerid][pMaskON] = 1;
	}
    SetPVarInt(playerid, "mask", gettime()+3);

	return true;
}
CMD:maskoff(playerid, params[])
{
    if(!PI[playerid][pMaskON])
        return SendClientMessage(playerid, COLOR_GREY, !"Вы не в маске");
        
	if(PI[playerid][pFraction])
		SetPlayerColor(playerid, gFractionColor[PI[playerid][pFraction] - 1]);

	else
		SetPlayerColor(playerid, 0xFFFFFF11);

	new stringex[100];
	format(stringex,sizeof(stringex),"~r~Mask off");
    GameTextForPlayer(playerid, stringex, 5000, 3);
    SendClientMessage(playerid, 0x4682B4AA, !"Вы сняли маску.");
    RemovePlayerAttachedObject(playerid, 8);
    PI[playerid][pMaskON] = 0;
	return true;
}
CMD:settime(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7) return false;
    if(ADuty[playerid]!=228) return ShowPlayerDialogEx(playerid,211,1,"Авторизация","{FFFFFF}Введите админ-пароль","Ок","Отмена");
    new hour;
    if(sscanf(params,"d",hour)) return SCM(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /settime [время]");
    SetWorldTime(hour);
	return true;
}

CMD:business(playerid,params[])
{
    if(!IsPlayerLogged[playerid])
		return 1;
    
    if(!PI[playerid][pBizKey])
    	return SCM(playerid, COLOR_GREY, "У вас нет бизнеса");
    	
	if(PI[playerid][pBizKey] > 1000)
		return SCM(playerid, COLOR_GREY, "У вас нет бизнеса (/filling)");
		
	ShowPlayerDialogEx(playerid, 751, DIALOG_STYLE_LIST, !"Управление бизнесом", !"{FF7319}1.{FFFFFF} Управление кассой\n{FF7319}2.{FFFFFF} Заказать продукты\n{FF7319}3.{FFFFFF} Заказать продукты (экспресс)\n{FF7319}4.{FFFFFF} Статистика\n{FF7319}5.{FFFFFF} Улучшения\n{FF7319}6.{FFFFFF} Открыть / закрыть\n{FF7319}7.{FFFFFF} Продать бизнес\n{FF7319}8.{FFFFFF} Установить цену за вход\n{FF7319}9.{FFFFFF} Установить цену за продукты\n{FF7319}10.{FFFFFF} Доходы", !"Выбрать", !"Отмена");
	return 1;
}
CMD:buyfuel(playerid)
{
    if(GetPlayerState(playerid) != 2)
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не должны быть в т/с.");
        
		new fillingid = -1;
	  	for(new i; i < MAX_FILLING; i++)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 10.0, gFuelPumps[i][0][0],gFuelPumps[i][0][1],gFuelPumps[i][0][2])) continue;
			else fillingid = i;
		}
		if(fillingid == -1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на АЗС");
		if(gFillings[fillingid][fillingFuel] < 15) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На АЗС нету топлива");

		SetPVarInt(playerid,"FillID",fillingid);
		ShowPlayerDialogEx(playerid, 782, DIALOG_STYLE_MSGBOX, !"Покупка канистры", !"{FFFFFF}Канистра стоит {FF0000}500$\n{FFFFFF}C ее помощью вы сможете заправить любое т/с на 15 литров\n\nCогласны ли Вы приобрести канистру?", !"Да", !"Нет");
	}
	else
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(vehicleid) != 525) return SCM(playerid, COLOR_GREY, "Вы должны находиться в специализированном транспорте!");
		if(PI[playerid][pJob] != JOB_MECHANIC) return SCM(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам недоступна данная возможность");
	    if(GetPlayerState(playerid) != 2) return SCM(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в машине для покупки топлива для продажи");
	    
		new fillingid = -1;
	  	for(new i; i < MAX_FILLING; i++)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 10.0, gFuelPumps[i][0][0],gFuelPumps[i][0][1],gFuelPumps[i][0][2])) continue;
			else fillingid = i;
		}
		if(fillingid == -1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на АЗС");

		SetPVarInt(playerid,"FillID",fillingid);
		ShowPlayerDialogEx(playerid, 5568, DIALOG_STYLE_INPUT, !"Покупка бензина", !"{ffffff}\nВведите количества бензина, которое хотите приобрести:\n\n", !"Да", !"Нет");
	}
	return 1;
}
CMD:fill(playerid)
{
	if(temp_filling_status[playerid]) return 1;
	new fillingid = -1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в т/с");
	
	new vehicleid = GetPlayerVehicleID(playerid);
	for(new i; i < MAX_FILLING; i++)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 10.0, gFuelPumps[i][0][0],gFuelPumps[i][0][1],gFuelPumps[i][0][2])) continue;
		else fillingid = i;
	}
	if(GetEngineStatus(vehicleid) == 1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Заправляться можно только с заглушенным двигателем");
		
	if(temp_filling_status[playerid]) return 1;
	new modelid = GetVehicleModel(vehicleid) - 400;
	if(Transport[modelid][trTank] <= VehicleInfo[vehicleid][vFuel]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже достаточно топлива");
	if(!Transport[modelid][trFuelable]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваше т/с не имеет бензобака");
	if(fillingid == -1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть на АЗС");

	temp_filling_id[playerid] = fillingid+1;
	temp_filling_status[playerid] = true;
	ShowFillingBar(playerid, vehicleid);
	SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {ffffff}Выберите нужно кол-во бензина: {FFC800}A / D. {ffffff}Заправиться: {FFC800}пробел/левый шифт.");
	f_TogglePlayerControllable(playerid, false);
	return 1;
}
CMD:fillcar(playerid, params[])
{
    if(!temp_canister[playerid]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет канистры!");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, COLOR_GREY, !"Вы не должны быть в т/с.");
    new vehicleid = GetNearestVehicle(playerid, 3.0), modelid = GetVehicleModel(vehicleid) - 400;

	if(vehicleid == INVALID_VEHICLE_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Рядом с Вами нет т/c");
	if(GetEngineStatus(vehicleid) == 1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Заправляться можно только с заглушенным двигателем");
	if(VehicleInfo[vehicleid][vFuel]+15 > Transport[modelid][trTank]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В этом т/c уже достаточно бензина");


	temp_canister[playerid] = false;

	VehicleInfo[vehicleid][vFuel] += 15;

	if(IsPlayerAttachedObjectSlotUsed(playerid, 6))
		RemovePlayerAttachedObject(playerid,6);

	SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно]{ffffff} Вы заправили т/c на 15 литров");
    return true;
}
CMD:filling(playerid)
{
	if(PI[playerid][pBizKey] < 1000) return SendClientMessage(playerid, COLOR_GREY, "У Вас нет АЗС");

	new fillingid = PI[playerid][pBizKey]-1001;

    SetPVarInt(playerid, "fillingid", fillingid);

	ShowPlayerDialogEx(playerid, 982, DIALOG_STYLE_LIST, !"Управление АЗС", !"{FF7319}1.{FFFFFF} Информация\n{FF7319}2.{FFFFFF} Цены\n{FF7319}3.{FFFFFF} Улучшения\n{FF7319}4.{FFFFFF} Заказать топливо\n{FF7319}5.{FFFFFF} Заказать топливо (экспресс)\n{FF7319}6.{FFFFFF} Управление кассой\n{FF7319}7.{FFFFFF} Открыть / закрыть заправку\n{FF7319}8.{FFFFFF} Продать АЗС\n{FF7319}9.{FFFFFF} Посмотреть доходы за 10 дней", !"ОК", !"Отмена");

	return true;
}
CMD:buyfilling(playerid)
{
    new	fillingid = -1;

	for(new i; i < MAX_FILLING; i++)
	{
		if(!IsPlayerInDynamicArea(playerid, gFillingBuyArea[i])) continue;

		else fillingid = i;
	}
	if(fillingid == -1 || GetPVarInt(playerid, "watch_filling")) return SendClientMessage(playerid, COLOR_GREY, !"Вы должны быть на АЗС");

 	temp_filling_buy_id[playerid] = fillingid;

	if(GetString(gFillings[fillingid][fillingOwner], "The State"))
	{
		new frmt_buyfilling[110 + 12];

		format(frmt_buyfilling, sizeof frmt_buyfilling, "\n{FFFFFF}Эта автозаправочная станция продается\n\n{FFFFFF}Номер заправки: {1E90FF}%d\n{FF9900}Цена: {32CD32}%d\n", gFillings[fillingid][fillingID], gFillings[fillingid][fillingPrice]);
		ShowPlayerDialogEx(playerid, 981, DIALOG_STYLE_MSGBOX, !"Автозаправочная станция", frmt_buyfilling, !"Купить", !"Отмена");
	}
	else SendClientMessage(playerid, COLOR_WHITE, !"Эта АЗС не продается");

	return 1;
}

CMD:engine(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);

		if(IsABike(vehicleid))
			return 1;
		
		if(VehicleLoad[vehicleid][vlRob])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете завести данный транспорт");
			
		if(SetEngineStatus(vehicleid) == -1)
		    SendClientMessage(playerid, COLOR_GREY, !"Двигатель не заводится");
			//SendClientMessage(playerid, COLOR_GREY, !"Двигатель не заводится. Вызовите механика {FFFFFF}(( /call (/c) ))");
	}
	return true;
}
CMD:limit(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendClientMessage(playerid, COLOR_GREY, !"Вы должны быть за рулем");

	new
	    limit;

	sscanf(params, "d", limit);

	if(!limit)
	{
		if(PI[playerid][pSLimit])
		{
			PI[playerid][pSLimit] = 0;
			SendClientMessage(playerid, COLOR_GREEN, !"Ограничение скорости снято");
		}
		else SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /limit [скорость]");
		return 1;
	}

	if(limit < 10 || limit > 150)
		return SendClientMessage(playerid, COLOR_GREY, !"Ограничение должно быть от 10 до 150");

	PI[playerid][pSLimit] = limit;

	SendClientMessage(playerid, COLOR_GREEN, !"Установлено ограничение скорости");
	return true;
}

CMD:endskin(playerid)
{
	if(!pTemp[playerid][pTempSkin])
	    return 1;
	    
    if(PI[playerid][pFraction])
		SetPlayerSkinEx(playerid, PI[playerid][pFractionSkin]);
		
	else
		SetPlayerSkinEx(playerid, PI[playerid][pSkin]);

    pTemp[playerid][pTempSkin] = false;
	SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выбросили временную одежду");
	return 1;
}
CMD:givemoney(playerid, params[])
{
	if(PI[playerid][pAdmin] < 7) return false;
    if(ADuty[playerid]!=228) return ShowPlayerDialogEx(playerid,211,1,"Авторизация","{FFFFFF}Введите админ-пароль","Ок","Отмена");
    new id,money,string[90];
    if(sscanf(params,"ud",id,money)) return SCM(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /givemoney [id] [количество денег]");
    if(!IsPlayerConnected(id)) return false;
	GiveMoney(id,money,"/givemoney");
	format(string,sizeof(string),"Вы дали игроку %s %d долларов",Name(id),money);
	SCM(playerid,-1,string);
	return true;
}
CMD:id(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_GREY, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /id [ID / Часть ника]");
	if(!sscanf(params, "u", params[0]))
	{
		if(params[0] == INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {ffffff}Игрок не в сети");
		else if(!IsPlayerLogged[params[0]]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {ffffff}Игрок не авторизовался");
		SendClientMessage(playerid, COLOR_YELLOW, "Игроки онлайн:");
		
  		totalstring[0] = 0;
		if(pl_afk_time[params[0]] >= 3) format(totalstring, sizeof totalstring, "ID: {FF7319}%d{FFFFFF} Имя: {FF7319}%s {FFFFFF}[№:%d] {ffa800}[AFK: %s]", params[0], PN(params[0]), PI[params[0]][pID], Convert(pl_afk_time[params[0]]));
		else format(totalstring, sizeof totalstring, "ID: {FF7319}%d{FFFFFF} Имя: {FF7319}%s {FFFFFF}[№:%d]", params[0], PN(params[0]), PI[params[0]][pID]);
  		SendClientMessage(playerid, COLOR_WHITE, totalstring);
  		totalstring[0] = 0;
	}
	else
	{
		new ids = 0;
		SendClientMessage(playerid, COLOR_YELLOW, "Игроки онлайн:");
	    foreach(new i : Player)
		{
			if(!IsPlayerLogged[i]) continue;
			if(strfind(PN(i), params[0], true) != -1)
			{
			    totalstring[0] = 0;
				if(pl_afk_time[i] >= 3) format(totalstring, sizeof totalstring, "ID: {FF7319}%d{FFFFFF} Имя: {FF7319}%s {FFFFFF}[№:%d] {ffa800}[AFK: %s]", i, PN(i), PI[i][pID], Convert(pl_afk_time[i]));
				else format(totalstring, sizeof totalstring, "ID: {FF7319}%d{FFFFFF} Имя: {FF7319}%s {FFFFFF}[№:%d]", i, PN(i), PI[i][pID]);
			    SendClientMessage(playerid, COLOR_WHITE, totalstring);
			    totalstring[0] = 0;
			    ids++;
			}
		}
		if(ids == 0) SendClientMessage(playerid, COLOR_GREY, "Не найдено");
	}
	return 1;
}
CMD:number(playerid, params[])
{
	if(!PI[playerid][pPhoneBook])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет телефонной книги. Её можно купить в магазине 24/7");
		
	if(sscanf(params, "s[36]", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /number [ Полный ник игрока/ID ]");
		
	new
		player_name[MAX_PLAYER_NAME],
		id,
		phone,
		admin,
		format_number_get[28 + MAX_PLAYER_NAME + 8],
		query_number_get_offline[61 + MAX_PLAYER_NAME];
		
	if(strlen(params[0]) <= 3)
    {
        id = strval(params[0]);
        
		if(!IsPlayerConnected(id) || !IsPlayerLogged[id])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /number [ Полный ник игрока/ID ]");

		if(PI[id][pAdmin])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Номер данного абонента не удалось определить");

		GetPlayerName(id, player_name, MAX_PLAYER_NAME);
		format(format_number_get,sizeof format_number_get,"{33FF1F}Номер %s: {FF5500}%d", player_name, PI[id][pTelNum]);
		SendClientMessage(playerid, COLOR_WHITE, format_number_get);
		SendClientMessage(playerid, 0x9ACD32FF, "Абонент доступен для звонка");
	}
 	else
	{
		if(isNumeric(params[0]))
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Никнейм введён в неверном формате");
			
	    format(query_number_get_offline, sizeof query_number_get_offline, "SELECT `TelNum`,`Admin` FROM `accounts` WHERE `NickName` = '%s'", params[0]);
		new Cache:result = mysql_query(mysql, query_number_get_offline);
		
		if(cache_get_row_count(mysql))
		{
			phone = cache_get_row_int(0, 0);
			admin = cache_get_row_int(0, 1);

	 		if(admin || phone == 0)
			 	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Номер данного абонента не удалось определить");
			 	
			format(format_number_get,sizeof format_number_get,"{33FF1F}Номер %s: {FF5500}%d",params[0],phone);
			SendClientMessage(playerid, COLOR_WHITE, format_number_get);
			
			if(GetPlayerID(params[0]) != INVALID_PLAYER_ID)
			{
	     		SendClientMessage(playerid, 0x9ACD32FF, "Абонент доступен для звонка");
				return 1;
			}
			else SendClientMessage(playerid, 0x33AAFFFF, "Телефон абонента вне зоны доступа");
		}
		else SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данный абонент не найден в базе");
		cache_delete(result, mysql);
	}
	return true;
}

CMD:leaders(playerid)
{
	new
	    frmt_leaders[256],
		string_leaders[2000],
		fractionname[30];

	strcat(string_leaders, !"{FFFF00}Организация - Должность - Имя - Телефон\n\n");

	foreach(Player, i)
	{
	    if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
			continue;

	    if(PI[i][pAdmin] > 0 || pTemp[i][pTempLeader])
			continue;

		if(!PI[i][pFraction])
            continue;

		if(!IsALeader(i))
		    continue;
		
		new
			fractionid = PI[i][pFraction] - 1,
			frid = GetSubfractionID(fractionid+1),
			subid = PI[i][pSubfraction] - 1;

		if(PI[i][pFraction] && PI[i][pSubfraction] >= 1)
			format(fractionname, sizeof fractionname, "%s", gSubfractionName[frid][subid]);

		else if(PI[i][pFraction] && PI[i][pSubfraction] == 0)
			format(fractionname, sizeof fractionname, "%s", gFractionName[fractionid]);

        if(PI[i][pTelNum] > 0)
			if(pl_afk_time[i] > 0)
				format(frmt_leaders, sizeof frmt_leaders, "{FFFFFF}%s - %s - %s [%d] - %d {FFA800}[AFK: %s]{FFFFFF}\n", fractionname, gFractionRankName[PI[i][pFraction]-1][PI[i][pRank]-1], PN(i), i, PI[i][pTelNum], Convert(pl_afk_time[i]));

			else
				format(frmt_leaders, sizeof frmt_leaders, "{FFFFFF}%s - %s - %s [%d] - %d\n", fractionname, gFractionRankName[PI[i][pFraction]-1][PI[i][pRank]-1], PN(i), i, PI[i][pTelNum]);

		else
			if(pl_afk_time[i] > 0)
				format(frmt_leaders, sizeof frmt_leaders, "{FFFFFF}%s - %s - %s [%d] - нет номера {FFA800}[AFK: %s]{FFFFFF}\n", fractionname, gFractionRankName[PI[i][pFraction]-1][PI[i][pRank]-1], PN(i), i, PI[i][pTelNum], Convert(pl_afk_time[i]));

			else
				format(frmt_leaders, sizeof frmt_leaders, "{FFFFFF}%s - %s - %s [%d] - нет номера\n", fractionname, gFractionRankName[PI[i][pFraction]-1][PI[i][pRank]-1], PN(i), i, PI[i][pTelNum]);

		
        strcat(string_leaders, frmt_leaders);
	}
	ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Лидеры", string_leaders, !"Закрыть", !"");

	return 1;
}
CMD:find(playerid)
{
    if(!PI[playerid][pFraction])
		return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите в организации");

	new
     	frmt_find[256],
		string_find[3000],
		total_online;

	new
		fractionid = PI[playerid][pFraction] - 1,
		subfractionid = PI[playerid][pSubfraction] - 1,
		subid = GetSubfraction(fractionid+1);
		
    if(PI[playerid][pRank] == 11)
    {
        format(frmt_find, sizeof frmt_find, "%s{FF7319}1.{FFFFFF} %s\n", frmt_find, gFractionName[fractionid]);

        for(new i; i < subid; i++)
            format(frmt_find, sizeof frmt_find, "%s{FF7319}%d.{FFFFFF} %s\n", frmt_find, i+2, gSubfractionName[fractionid][i]);

        ShowPlayerDialogEx(playerid, 288, DIALOG_STYLE_LIST, !"Выберите подфракцию", frmt_find, !"Выбор", !"Отмена");
    }
	else
	{
   		foreach( new i: Player)
		{
		    if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
				continue;

		    if(PI[i][pAdmin] > 0)
				continue;

		    if(PI[i][pFraction] != fractionid+1 || PI[i][pSubfraction] != subfractionid + 1)
				continue;

			total_online++;
		}


		format(frmt_find, sizeof frmt_find,"{FFFFFF}Всего Online: {FF9900}%d\n", total_online);
		strcat(string_find, frmt_find);
		strcat(string_find, !"{FFFFFF}ID\tУровень\tТелефон\tРанг\tВыговоры\tИмя игрока\n\n");

   		foreach( new i: Player)
		{
		    if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
				continue;

		    if(PI[i][pAdmin] > 0 || pTemp[i][pTempLeader])
				continue;

		    if(PI[i][pFraction] != fractionid+1 || PI[i][pSubfraction] != subfractionid + 1)
				continue;

		    if(PI[i][pTelNum] > 0)
				if(pl_afk_time[i] >= 3)
					format(frmt_find, sizeof frmt_find, "{FFFFFF}%d\t%d\t\t%i\t\t%d\t%d/3\t\t%s {FFA800}[AFK: %s]{FFFFFF}\n", i, PI[i][pLevel], PI[i][pTelNum], PI[i][pRank], PI[i][pFWarns], PN(i), Convert(pl_afk_time[i]));
				else
				    format(frmt_find, sizeof frmt_find, "{FFFFFF}%d\t%d\t\t%i\t\t%d\t%d/3\t\t%s\n", i, PI[i][pLevel], PI[i][pTelNum], PI[i][pRank], PI[i][pFWarns], PN(i));

			else
			    if(pl_afk_time[i] >= 3)
					format(frmt_find, sizeof frmt_find, "{FFFFFF}%d\t%d\t\tнет номера\t\t%d\t%d/3\t\t%s {FFA800}[AFK: %s]{FFFFFF}\n", i, PI[i][pLevel], PI[i][pRank], PI[i][pFWarns], PN(i), Convert(pl_afk_time[i]));
				else
					format(frmt_find, sizeof frmt_find, "{FFFFFF}%d\t%d\t\tнет номера\t\t%d\t%d/3\t\t%s\n", i, PI[i][pLevel], PI[i][pRank], PI[i][pFWarns], PN(i));

			strcat(string_find, frmt_find);
		}

		ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Члены организации онлайн", string_find, "Закрыть", "");
	}
	return 1;
}
CMD:play(playerid)
	ShowPlayerDialogEx(playerid, 94, DIALOG_STYLE_LIST, !"Онлайн радио", !"1. Zaycev FM\n2. Radio ROKS\n3. Радио Шансон\n4. Радио Рекорд\n5. DFM Radio\n6. Европа +", !"Принять", !"Отмена");
	
CMD:stop(playerid)
{
	StopAudioStreamForPlayer(playerid);
	SendClientMessage(playerid, COLOR_GREEN, !"Онлайн-Радио выключено");
}

CMD:settings(playerid, params[])
{
	ShowUpdateSettings(playerid);
}
CMD:mn(playerid, params[])
{
	return callcmd::menu(playerid,params);
}
CMD:inv(playerid)
{
    if(!IsPlayerLogged[playerid])
		return false;
		
    Myitems(playerid);
    return 1;
}
/*CMD:priz(playerid)
{
	new
		query_get_priz[160];
		
	format(query_get_priz, sizeof query_get_priz, "SELECT `name`, `count` FROM `roulett` WHERE `ownerid` = '%d'", PI[playerid][pID]);
	new Cache:result = mysql_query(mysql, query_get_priz);

	if(!cache_get_row_count(mysql))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет доступных выигрышей"), cache_delete(result, mysql);

	new
	    frmt_priz_list[350],
		name[64],
		count;

	for(new p; p < cache_get_row_count(mysql) ; p ++ )
	{
	    cache_get_row(p, 0, name, mysql);
		count = cache_get_row_int(p, 1);
	    
	    format(frmt_priz_list, sizeof frmt_priz_list, "%s{FF7319}%d.{FFFFFF} %s [{FF9900}%d{FFFFFF}]\n", frmt_priz_list, p+1, name, count);
	}
	
	ShowPlayerDialogEx(playerid, 199, DIALOG_STYLE_LIST, !"Инвентарь рулетки", frmt_priz_list, !"Далее", !"Отмена");
    return 1;
}*/
CMD:animlist(playerid, params[])
{
	return callcmd::anim(playerid,params);
}

CMD:rep(playerid, params[])
{
	return callcmd::report(playerid,"");
}
CMD:c(playerid, params[])
	return callcmd::call(playerid, params);

CMD:t(playerid, params[])
	return callcmd::sms(playerid, params);

CMD:namestore(playerid, params[])
{
    if(sscanf(params, "s[36]", params[0]))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте: /namestore [ Ник/ID ]");


	new
        query_namestore_get[49 + 9],
		frmt_nickname[MAX_PLAYER_NAME],
		newname[MAX_PLAYER_NAME],
		data[16],
  		str_namestore[MAX_PLAYER_NAME + 19 + 16],
		string[2000],
		query_get_name[55 + MAX_PLAYER_NAME];

	if(strlen(params[0]) <= 3 && isNumeric(params[0]))
    {
        new
			player_id = strval(params[0]);

		if(!IsPlayerConnected(player_id))
			return SendClientMessage(playerid, COLOR_WHITE, "{FFC800}[Подсказка] {FFFFFF}Используйте: /namestore [ Ник/ID ]");

		format(query_namestore_get, sizeof query_namestore_get, "SELECT * FROM `namestore` WHERE `account_id` = '%d'", PI[player_id][pID]);
		new
			Cache:result = mysql_query(mysql, query_namestore_get),
			rows,
			fields;

		cache_get_data(rows,fields);

		if(!cache_get_row_count(mysql))
		{
			format(frmt_nickname, sizeof frmt_nickname, "%s", PN(player_id));
			ShowPlayerDialogEx(playerid, 1488, DIALOG_STYLE_MSGBOX, frmt_nickname, !"{ffffff}Этот игрок не менял ника", !"OK", !"");
		    cache_delete(result, mysql);
		}
		else
		{
			format(frmt_nickname, sizeof frmt_nickname, "%s", PN(player_id));

			format(str_namestore, sizeof str_namestore, "История ников:");
			strcat(string, str_namestore);

			for(new ns = 0 ; ns < rows ; ns ++ )
			{
				cache_get_row(ns, 2, newname, mysql, MAX_PLAYER_NAME);
				cache_get_row(ns, 3, data, mysql, 16);
				if(strlen(newname) || strlen(data))
					format(str_namestore, sizeof str_namestore, "\n{FFFF00}%s\t{FFFFFF}%s", newname, data);

				strcat(string, str_namestore);
			}

			ShowPlayerDialogEx(playerid, 1488, DIALOG_STYLE_MSGBOX, frmt_nickname, string, !"OK", !"");
		    cache_delete(result, mysql);
		}
	}
	else
	{
	    format(query_get_name, sizeof query_get_name, "SELECT `id` FROM `accounts` WHERE `NickName` = '%s'", params[0]);

		new Cache:result = mysql_query(mysql, query_get_name);
		if(cache_get_row_count(mysql))
		{
			new
				id = cache_get_row_int(0, 0);

		    format(query_namestore_get, sizeof query_namestore_get, "SELECT * FROM `namestore` WHERE `account_id` = '%d'", id);

			new
				Cache:r_get_nick = mysql_query(mysql, query_namestore_get),
				rows,
				fields;

			cache_get_data(rows,fields);

			if(!cache_get_row_count(mysql))
			{
				format(frmt_nickname, sizeof frmt_nickname, params[0]);
				ShowPlayerDialogEx(playerid, 1488, DIALOG_STYLE_MSGBOX, frmt_nickname, !"{ffffff}Этот игрок не менял ника", !"OK", !"");
			    cache_delete(r_get_nick, mysql);
			}
			else
			{
				format(frmt_nickname, sizeof frmt_nickname, params[0]);

				format(str_namestore, sizeof str_namestore, "История ников:");
				strcat(string, str_namestore);

				for(new ns = 0 ; ns < rows ; ns ++ )
				{
					cache_get_row(ns, 2, newname, mysql, MAX_PLAYER_NAME);
					cache_get_row(ns, 3, data, mysql, 16);
					if(strlen(newname) || strlen(data))
						format(str_namestore, sizeof str_namestore, "\n{FFFF00}%s\t{FFFFFF}%s", newname, data);

					strcat(string, str_namestore);
				}

				ShowPlayerDialogEx(playerid, 1488, DIALOG_STYLE_MSGBOX, frmt_nickname, string, !"OK", !"");
			    cache_delete(r_get_nick, mysql);
			}
		}
		else SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный никнейм");

		cache_delete(result, mysql);
	}
	return 1;
}
CMD:menu(playerid, params[])
{
    if(Clother[playerid] != -1)
		return false;

	if(!IsPlayerLogged[playerid])
		return false;
		
	//ShowPlayerDialogEx(playerid, 722, 2, "Игровое меню", "{FF7319}1){FFFFFF} Действие персонажа\n{FF7319}2){FFFFFF} Навыки персонажа\n{FF7319}3){FFFFFF} Связь с администрацией\n{FF7319}4){FFFFFF} Помощь по серверу\n{FF7319}5){FFFFFF} Настройки персонажа\n{FF7319}6){FFFFFF} Донат\n{FF7319}7){FFFFFF} Телефон\n{FF7319}8){FFFFFF} Безопасность", "Выбор", "Отмена");
	ShowPlayerDialogEx(playerid, 722, DIALOG_STYLE_LIST, !"Меню игрока", !"{FF7319}1.{FFFFFF} Статистика\n{FF7319}2.{FFFFFF} Настройки персонажа\n{FF7319}3.{FFFFFF} Безопасность\n{FF7319}4. {FFFFFF}Навыки персонажа\n{FF7319}5.{FFFFFF} Список команд\n{FF7319}6.{FFFFFF} Связь с администрацией\n{FF7319}7.{FFFFFF} Смена нонРП ника\n{FF7319}8.{FFFFFF} Донат\n{FF7319}9.{FFFFFF} Улучшения\n{FF7319}10.{FFFFFF} Активное задание\n{FF7319}11.{FFFFFF} Промокод", !"Выбор", !"Отмена");

	return true;
}
CMD:promo(playerid)
{
	if(!PI[playerid][pCPromo])
	    return 1;
	    
	new
	    promoid = PI[playerid][pCPromo]-1;
	    
	if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
	    return 1;
	    
	new
	    frmt_promo_menu[290];
	    
    format(frmt_promo_menu, sizeof frmt_promo_menu, "На счету: {33AA33}%d$\n{FF7319}1.{FFFFFF} Информация о промокоде\n{FF7319}2.{FFFFFF} Список использовавших\n{FF7319}3.{FFFFFF} Список использовавших {00CC00}Online\n{FF7319}4.{FFFFFF} Настройка вознаграждений\n{FF7319}5.{FFFFFF} Управление банком промокода", gPromo[promoid][pcBank]);
	    
    ShowPlayerDialogEx(playerid, 341, DIALOG_STYLE_LIST, !"Управление промокодом", frmt_promo_menu, !"Выбор", !"Отмена");
	return 1;
}
CMD:togphone(playerid)
{
	if(!PI[playerid][pPhone])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет телефона. Вы можете купить его в 24/7");

	if(!PI[playerid][pOnPhone])
	{
		PI[playerid][pOnPhone] = true;
		SendClientMessage(playerid, COLOR_GREEN, !"Телефон включен");
	}
	else
	{
		PI[playerid][pOnPhone] = false;
		SendClientMessage(playerid, COLOR_GREEN, !"Телефон выключен");
	}
	
	return true;
}
CMD:call(playerid, params[])
{
	if(PI[playerid][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы в тюрьме");

	if(!PI[playerid][pPhone])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет телефона. Вы можете купить его в 24/7");

	if(!PI[playerid][pOnPhone])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала нужно включить телефон");

	if(PI[playerid][pIn_Skill] < 5)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На счету недостаточно средств");

	if(gCalls[playerid][gCaller] != INVALID_PLAYER_ID || gCalls[playerid][gCallee] != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сначала завершите текущий разговор (/h)");

	if(sscanf(params, "d", params[0]) || strlen(params[0]) < 3)
	{
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}/c [номер телефона]");
		SendClientMessage(playerid, COLOR_GREY, !"Скорая помощь/Полиция/Механики - 911");
		SendClientMessage(playerid, COLOR_GREY, !"Такси - 555");
		SendClientMessage(playerid, COLOR_GREY, !"Радиоцентр LS/SF/LV - 1100 / 1101 / 1102");
		SendClientMessage(playerid, COLOR_GREY, !"Мэрия LS/SF/LV - 111 / 222 / 333");
		return SendClientMessage(playerid, COLOR_GREY, !"Администрация губернатора - 777");
	}
	
	if(params[0] == 911)
	    return ShowPlayerDialogEx(playerid, 615, DIALOG_STYLE_LIST, !"Экстренные службы", !"{FF7319}1.{FFFFFF} Полиция\n{FF7319}2.{FFFFFF} Скорая помощь\n{FF7319}3.{ffffff}Механики", !"Далее", !"Отмена");
	if(params[0] == 555)
		return ShowPlayerDialogEx(playerid, 504, DIALOG_STYLE_INPUT, !"Таксопарк", !"{FFFFFF}Вы позвонили в службу такси, опишите своё местоположение", !"Вызов", !"Отмена");
	    
	if(params[0] >= 1100 && params[0] <= 1102)
	{
	    if(PI[playerid][pFraction] == 9)
	        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете звонить в свою организацию");

		if(pTemp[playerid][pDial] != 0)
	        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже звоните в эфир");

		switch(params[0])
		{
			case 1100:
			{
				if(!gNewsDialing[0])
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Звонки не принимаются");

				if(gNewsDialee[0] != INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Линия занята");

				if(PI[playerid][pMoney] < gEtherPrice)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

                pTemp[playerid][pEtherCall] = 1;
			}
			case 1101:
			{
				if(!gNewsDialing[1])
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Звонки не принимаются");

				if(gNewsDialee[1] != INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Линия занята");

				if(PI[playerid][pMoney] < gEtherPrice)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

                pTemp[playerid][pEtherCall] = 2;
			}
			case 1102:
			{
				if(!gNewsDialing[2])
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Звонки не принимаются");

				if(gNewsDialee[2] != INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Линия занята");

				if(PI[playerid][pMoney] < gEtherPrice)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

				pTemp[playerid][pEtherCall] = 3;
			}
		}
  		new frmt_dial_message[128];

		format(frmt_dial_message, sizeof frmt_dial_message, "{FFFFFF}Стоимость звонка: {FF0000}$%d\n\n{FFFFFF}Вы действительно хотите позвонить?", gEtherPrice);
		ShowPlayerDialogEx(playerid, 514, DIALOG_STYLE_MSGBOX, !"Эфир", frmt_dial_message, !"Да", !"Нет");
		return 1;
	}
	if(params[0] == 111 || params[0] == 222 || params[0] == 333 || params[0] == 777)
	{
	    if(pTemp[playerid][pQuestion])
	        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже задавали вопрос. Дождитесь ответа");
	        
  		new
		  	frmt_quest_message[128],
		  	fraction_text[60],
		  	subid;

		if(params[0] == 111)
		    strcat(fraction_text, "Мэрии Лос Сантос"), subid = 1;
		    
		else if(params[0] == 222)
		    strcat(fraction_text, "Мэрии Сан Фиерро"), subid = 2;

		else if(params[0] == 333)
		    strcat(fraction_text, "Мэрии Лас Вентурас"), subid = 3;
		    
		else if(params[0] == 777)
		    strcat(fraction_text, "Правительства"), subid = 0;
		    
        pTemp[playerid][pHallQuestion] = subid;

		format(frmt_quest_message, sizeof frmt_quest_message, "{FFFFFF}Введите Ваш вопрос для %s:", fraction_text);
		ShowPlayerDialogEx(playerid, 534, DIALOG_STYLE_INPUT, !"Вопрос", frmt_quest_message, !"Отправить", !"Отмена");
		return 1;
	}
	new id = -1;

  	foreach(new i : Player)
	{
		if(!IsPlayerConnected(i))
			continue;

		if(PI[i][pTelNum] == params[0])
		{
			id = i;
			break;
		}
	}

	if(id == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели свой номер");

	if(id == -1)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрока с этим номером нет на сервере");

	if(!PI[id][pPhone])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока нет телефона");

	if(!PI[id][pOnPhone])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока выключен телефон");
		
	if(gCalls[id][gCaller] != INVALID_PLAYER_ID || gCalls[id][gCallee] != INVALID_PLAYER_ID || id == playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Занято...");
		
	if(PI[id][pJailTime] > 0)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в тюрьме");

	gCalls[playerid][gCaller] = playerid;
	gCalls[playerid][gCallee] = id;
	gCalls[id][gCaller] = playerid;
	gCalls[id][gCallee] = id;

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	SetPlayerAttachedObject(playerid, 9, 330, 6);
	
	new
		fmrt_call_msg[120];
		
	format(fmrt_call_msg, sizeof fmrt_call_msg, "%s(тел. %d) звонит Вам на моб. телефон. {AFAFAF}(/p - ответить, /h - отклонить)", PN(playerid), PI[playerid][pTelNum]);
	SendClientMessage(id, COLOR_WHITE, fmrt_call_msg);
	return true;
}
CMD:mc(playerid)
{
	new
		subfraction = PI[playerid][pSubfraction];
		
	if(PI[playerid][pFraction] != 1)
		return 1;
		
	new
		caller = gEmCall[1];

	if(caller == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вызовов не поступало");
		
	gEmCall[1] = INVALID_PLAYER_ID;
	
	if(caller == INVALID_PLAYER_ID || !IsPlayerConnected(caller))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел");
		
	new Float:x, Float:y, Float:z;
	GetPlayerPos(caller, x, y, z);
	SetPlayerCheckpointEx(playerid, x, y, z, 4.0);

	new mes[128];
	
	if(subfraction)
		format(mes,sizeof(mes),"%s (%s) принял вызов", PN(playerid), gSubfractionName[0][subfraction-1]);
		
	else
	    format(mes,sizeof(mes),"%s принял вызов", PN(playerid));
	    
	SendClientMessage(caller, 0x269BD8FF, mes);
	DepartmentChat(0x007FFFFF, mes, 1, 0, 0, 0, 0);
	SendClientMessage(playerid, 0x269BD8FF, "Метка установлена на радаре. Чтобы убрать введите {FFFFFF}/gps");
	return 1;
}
CMD:pc(playerid)
{
	new
		subfraction = PI[playerid][pSubfraction];

	if(!IsACop(playerid))
		return 1;

	new
		caller = gEmCall[0];

	if(caller == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вызовов не поступало");

	gEmCall[0] = INVALID_PLAYER_ID;

	if(caller == INVALID_PLAYER_ID || !IsPlayerConnected(caller))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(caller, x, y, z);
	SetPlayerCheckpointEx(playerid, x, y, z, 4.0);

	new mes[128];
	if(subfraction) format(mes,sizeof(mes),"%s (%s) принял вызов", PN(playerid), gSubfractionName[2][subfraction-1]);
	else format(mes,sizeof(mes),"ФБР (%s) принял вызов", PN(playerid));
	SendClientMessage(caller, 0x269BD8FF, mes);
	DepartmentChat(0x007FFFFF, mes, 0, 0, 1, 1, 0);
	SendClientMessage(playerid, 0x269BD8FF, "Метка установлена на радаре. Чтобы убрать введите {FFFFFF}/gps");
	return 1;
}
CMD:p(playerid)
{
	if(gCalls[playerid][gCallee] != playerid)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам никто не звонит");

	if(pTemp[playerid][pEther])
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нельзя во время эфира");
		
	new
		caller = gCalls[playerid][gCaller];
		
	if(caller == INVALID_PLAYER_ID || !IsPlayerConnected(caller))
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Собеседник вышел из игры");
		
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
	SetPlayerAttachedObject(playerid,9,330,6);
	SendClientMessage(caller, COLOR_YELLOW,"Собеседник поднял телефон");
	temp_call[playerid] = true;
	temp_call[caller] = true;
	return true;
}
CMD:h(playerid)
{
    for(new i; i < sizeof gNewsDialee; i++)
	{
    	if(gNewsDialee[i] == playerid)
		{
			SendClientMessage(playerid, COLOR_YELLOW, !"Вы повесили трубку");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			SetTimerEx("@__ClearPhone",2000,false,"i",playerid);
			gNewsDialee[i] = INVALID_PLAYER_ID;
			SendClientMessage(gNewsDialer[i], COLOR_YELLOW, !"Игрок положил трубку");
			return 1;
		}
	}
	
	if(gCalls[playerid][gCaller] == INVALID_PLAYER_ID && gCalls[playerid][gCallee] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не используете телефон");
		
	new
		id;
		
	if(gCalls[playerid][gCaller] == playerid)
		id = gCalls[playerid][gCallee];
	
	else if(gCalls[playerid][gCallee] == playerid)
		id = gCalls[playerid][gCaller];
		
	else
	{
	    gCalls[playerid][gCaller] = INVALID_PLAYER_ID;
	    gCalls[playerid][gCallee] = INVALID_PLAYER_ID;
		return 1;
	}
	
	SendClientMessage(playerid, COLOR_YELLOW, !"Вы повесили трубку");
	SendClientMessage(id, COLOR_YELLOW, !"Собеседник повесил трубку");
	
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
	SetTimerEx("@__ClearPhone",2000,false,"i",playerid);
	
	SetPlayerSpecialAction(id,SPECIAL_ACTION_STOPUSECELLPHONE);
	SetTimerEx("@__ClearPhone",2000,false,"i",id);
	
	gCalls[playerid][gCaller] = INVALID_PLAYER_ID;
	gCalls[playerid][gCallee] = INVALID_PLAYER_ID;
	gCalls[id][gCaller] = INVALID_PLAYER_ID;
	gCalls[id][gCallee] = INVALID_PLAYER_ID;
	temp_call[playerid] = false;
	temp_call[id] = false;
	return true;
}