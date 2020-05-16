// Second File to translate
public SetBuyGunCamera(playerid)
{
	SetPlayerCameraPos(playerid, 295.1925, -36.7806, 1002.9);
	SetPlayerCameraLookAt(playerid, 295.1925, -39.7806, 1002.9);
	InterpolateCameraPos(playerid, 295.1925, -35.7806, 1002.9, 295.1925, -38.7, 1002.9, 1000);
	InterpolateCameraLookAt(playerid, 295.1925, -38.7, 1002.9, 295.20001221, -39.29999924, 1001.59997559, 1000, CAMERA_MOVE);
	return true;
}
public OnPlayerEnterCheckpoint(playerid)
{
	if(temp_gps_checkpoint[playerid])
	{
		DisablePlayerCheckpoint(playerid);
		temp_gps_checkpoint[playerid] = false;
		SendClientMessage(playerid, 0x97D324FF, "Вы достигли места назначения");
	}
	if(temp_quest_checkpoint[playerid])
	{
		DisablePlayerCheckpoint(playerid);
		temp_gps_checkpoint[playerid] = false;
		SendClientMessage(playerid, 0x97D324FF, "Вы достигли места назначения");

	}

	return 1;
}
public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(checkpointid == NomerCP)
	{
	    if(!IsPlayerInAnyVehicle(playerid)) return 1;
	    if(!PI[playerid][pCars]) return 1;
		if(PI[playerid][pPTS] == 1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть ПТС");
		if(temp_car_num_get[playerid]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже установили номер");
			
		new
			slot = GetCarSlot(PI[playerid][pCars]),
			player_car = CarInfo[slot][cVehID];
			
	    if(GetPlayerVehicleID(playerid) == player_car && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	        ShowPlayerDialogEx(playerid, 203, DIALOG_STYLE_MSGBOX, !"Получение номера", !"\n\n{FFFFFF}Вы точно хотите получить государственный номер на свой автомобиль?\n\n", !"Да", !"Нет");

		else SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть в личном т/с");
		return 1;
	}

	if(InJob[playerid] == 5 && temp_job_status[playerid] == 2)
	{
	    if(checkpointid == gRoadCP[RoadCP[playerid]-1] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	    {


		    f_TogglePlayerControllable(playerid, false);
		    ApplyAnimation(playerid, "CAR_CHAT", "CAR_Sc4_BL", 4.0, 1, 1, 1, 0, 1000, 0);

		    SetTimerEx("@__roadput", 1000,false, "i", playerid);
		    TogglePlayerDynamicCP(playerid, gRoadCP[RoadCP[playerid]-1], false);
	    }
	}
	if(InJob[playerid] == 5 && temp_job_status[playerid] == 1)
	{
	    if(checkpointid == gRoadGet[RoadGet[playerid]-1] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	    {
			SetPVarInt(playerid,"UseAnim",1);
	        SetTimerEx("@__roadget",4000, false, "i", playerid);

			RemovePlayerAttachedObject(playerid,0);
			RemovePlayerAttachedObject(playerid,1);
			SetPlayerAttachedObject(playerid, 0, 1458, 1, -1.034844, 1.116571, -0.065124, 76.480148, 75.781570, 280.952545, 0.575599, 0.604554, 0.624122);
			ClearAnimations(playerid);
			ApplyAnimation(playerid, "PED", "IDLE_chat", 5.0, 0, 0, 0, 1, 5000, 1);
			TogglePlayerDynamicCP(playerid, gRoadGet[RoadGet[playerid]-1], false);
		    
	    }
	}

	////////////////
	if(checkpointid >= PorterLoad[0] && checkpointid <= PorterLoad[5])
	{
		if(InJob[playerid] == 6 && temp_porter_status[playerid] == 1)
		{
			if(temp_porter_time[playerid] > 0)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"Вы были кикнуты по подозрению в читерстве [№750]");
				J_Kick(playerid);
				return 1;
			}
			
		    for(new i = 0; i < 6; i ++)
		    	TogglePlayerDynamicCP(playerid, PorterLoad[i], false);

	    	new porter_unload = RandomEx(0,4);
	    	
   			TogglePlayerDynamicCP(playerid, PorterUnload[porter_unload], true);
    			
			ClearAnimations(playerid);
			ApplyAnimation(playerid, !"CARRY", !"liftup", 1.0, 0, 1, 1, 0, 0, 1);
			SetTimerEx("@__CarryDelay",1000, false, "i", playerid);
            //SetPlayerAttachedObject(playerid, 0, 19636, 6, -0.2, 0.10, -0.2, -110.0, 0.0, 78.0);
            SetPlayerAttachedObject(playerid, 0, 19636, 6, 0.06, -0.00, -0.17, -110.0, 0.0, -12.0);
            SendClientMessage(playerid, -1, !"Теперь отнесите ящик на склад. Место отмечено на карте");
            temp_porter_status[playerid] = 2;
            temp_porter_time[playerid] = 3;
		}
	}

	if(checkpointid >= PorterUnload[0] && checkpointid <= PorterUnload[4])
	{
		if(InJob[playerid] == 6 && temp_porter_status[playerid] == 2)
		{
			if(temp_porter_time[playerid] > 0)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"Вы были кикнуты по подозрению в читерстве [№751]");
				J_Kick(playerid);
				return 1;
			}
			
		    for(new i = 0; i < 5; i ++)
		    	TogglePlayerDynamicCP(playerid, PorterUnload[i], false);

			ClearAnimations(playerid);
			ApplyAnimation(playerid, !"CARRY", !"putdwn", 4.0, 0, 1, 1, 0, 0, 1);

            temp_porter_time[playerid] = 3;
            
            if(PI[playerid][pDaysSalary] > 0)
            	temp_porter_amount[playerid] += 280;
            	
			else
  				temp_porter_amount[playerid] += 140;
            
		    new
		        frmt_worked[100];

			if(PI[playerid][pDaysSalary] > 0)
				format(frmt_worked, sizeof frmt_worked, "Вы положили ящик. {42B02C}+$280{FFFFFF} к зарплате. Заработано: {8D2424}$%d", temp_porter_amount[playerid]);

			else
				format(frmt_worked, sizeof frmt_worked, "Вы положили ящик. {42B02C}+$140{FFFFFF} к зарплате. Заработано: {8D2424}$%d", temp_porter_amount[playerid]);

		    SendClientMessage(playerid, COLOR_WHITE, frmt_worked);

			PI[playerid][pPointsLoader] += 3;
			UpdatePlayerData(playerid, "PointsLoader", PI[playerid][pPointsLoader]);

			if(PI[playerid][pQuest] == 3 && PI[playerid][pQuestStatus] == 1)
			{
			    PI[playerid][pQuestProcess]++;
			    UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
				if(PI[playerid][pQuestProcess] >= 20)
				{
			        PI[playerid][pQuestStatus] = 0;
			        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
			    	SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы перенесли 20 ящиков с грузом. Отправляйтесь к Саймону");
				}
			}
		
			new job_cp = RandomEx(0,5);

			TogglePlayerDynamicCP(playerid, PorterLoad[job_cp], true);
			RemovePlayerAttachedObjectEx(playerid, 0);
			temp_porter_status[playerid] = 1;
		}
	}
	if(checkpointid == gArmyShip)
	{
		if(PI[playerid][pFraction] == 7)
		{
		    if(GetPVarInt(playerid, "carrygun"))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть ящик с оружием");
				
			if(!GetPVarInt(playerid, "carrygun"))
			{
				ClearAnimations(playerid);
				ApplyAnimation(playerid, !"CARRY", !"liftup", 1.0, 0, 1, 1, 0, 0, 1);
				SetTimerEx("@__CarryDelay",1000, false, "i", playerid);
				SetPlayerAttachedObject(playerid, 3, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0);
				SetPVarInt(playerid, "carrygun", 300);
				SetPVarInt(playerid, "carryammo", 300);
			}

			
		}
	}
    if(checkpointid >= gArmyStockArea[0] && checkpointid <= gArmyStockArea[1])
	{
		new armyid = GetPlayerVirtualWorld(playerid)-1;
		if(PI[playerid][pFraction] >= 2 && PI[playerid][pFraction] <= 7)
			StealMats(playerid, armyid);
			


	}
	return false;
}
stock GetVehicleMaxSeat(vehicleid)
{
    static MaxSeats[] =
	{
		3,1,1,1,3,3,0,1,1,3,1,1,1,3,1,1,3,1,3,1,3,
		3,1,1,1,0,3,3,3,1,0,8,0,1,1,15,1,8,3,1,3,0,
		1,1,1,3,0,1,0,1,15,1,0,0,0,1,1,1,3,3,1,1,1,
		1,1,1,3,3,1,1,3,1,0,0,1,1,0,1,1,3,1,0,3,1,
		0,0,0,3,1,1,3,1,3,0,1,1,1,3,3,1,1,1,1,1,1,
		1,1,3,1,0,0,1,0,0,1,1,3,1,1,0,0,1,1,1,1,1,
		1,1,1,3,0,0,0,1,1,1,1,2,2,0,3,1,1,1,1,1,3,
		3,1,1,3,3,1,0,1,1,1,1,1,1,3,3,1,1,0,1,3,3,
		0,15,1,0,0,1,0,1,1,1,1,3,3,1,3,0,15,3,1,1,1,
		1,15,15,1,1,1,0,3,3,3,1,1,1,1,1,3,1,15,15,15,3,
		15,15
	};
	new model = GetVehicleModel(vehicleid) - 400;
	if(model >= 0) return MaxSeats[model];
	return -1;
}
public OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
	return true;
}
////


////////
stock SetPlayerBuySkin(playerid)
{
	new race = PI[playerid][pRace];
    SetPlayerPos(playerid, -2237.3521, -1717.8398, 480.8685);
    SetPlayerFacingAngle(playerid, 8.8798);
    SetPlayerCameraPos(playerid, -2238.258789, -1712.989746, 481.049804);
    SetPlayerCameraLookAt(playerid, -2237.401611, -1717.915527, 481.003967);
    if(PI[playerid][pSex] <= 1) SetPlayerSkinEx(playerid,MBomzSkins[race][0]);
	else SetPlayerSkinEx(playerid,GBomzSkins[race][0]);

	PI[playerid][pOldSkin] = GetPlayerSkin(playerid);
	SetPlayerVirtualWorld(playerid,playerid + 5);
	SetPlayerInterior(playerid, 0);
	f_TogglePlayerControllable(playerid, false);

	for(new i; i < 13; i++)
		TextDrawShowForPlayer(playerid, select_skin[i]);

 	SelectTextDraw(playerid, 0xFF9B44FF);
 	//SelectTextDraw(playerid, 0xFFFFFF00);

	return true;
}
public OnPlayerEnterDynamicRaceCP(playerid, checkpointid)
{

	return true;
}
/*stock LoadFactory()
{
	new Cache:result = mysql_query(mysql,"SELECT * FROM `Factory` WHERE `ID` = '1'" );
	print("Загрузка завода");
	if(cache_get_row_count(mysql) > 0)
	{
		FactoryFerum = cache_get_row_int(0, 1, mysql);
		FactoryMats = cache_get_row_int(0, 2, mysql);
		FactoryFuel = cache_get_row_int(0, 3, mysql);
	}
	cache_delete(result, mysql);
	if(FactoryFerum < 10000) FactoryFerum = 40000;
	if(FactoryMats < 10000) FactoryMats = 40000;
	if(FactoryFuel < 10000) FactoryFuel = 40000;
	return true;
}
stock SaveFactory()
{
	new string[130];
	format(string, sizeof(string), "UPDATE `Factory` SET `Ferum` = '%i', `Materials` = '%i', `Fuel` = '%i' WHERE `ID` = '1'",
	FactoryFerum, FactoryMats, FactoryFuel);
	if(!EXITSAVEMODE)mysql_tquery(mysql, string); else mysql_query(mysql, string, false);
	print("mysql Сохранение завода");
	return true;
}*/
public OnPlayerLeaveDynamicRaceCP(playerid, checkpointid)
{
	return true;
}
public OnRconCommand(cmd[])
{
	return true;
}
public OnPlayerObjectMoved(playerid, objectid)
{
	return true;
}


stock AddBusinessList(playerid, string[], size, str[], biz, listitem)
{
	strcat(string, str, size);
	BizList[playerid][biz] = listitem;

	return true;
}
stock ShowBusinessList(playerid)
{
	new
	    frmt_biz_gps[80],
	    countgps,
		frmt_business_gps[1000];

	for(new b; b < MAX_BIZ; b++)
		if(BizList[playerid][b] != -1)
		    BizList[playerid][b] = -1;
	

	for(new b; b < MAX_BIZ; b++)
	{
    	if(!GetString(BizInfo[b][bOwner], "The State") && BizInfo[b][bImprove][2] && (BizInfo[b][bState] != 2 || BizInfo[b][bState] != 3 || BizInfo[b][bState] != 4 || BizInfo[b][bState] != 5 || BizInfo[b][bState] != 6))
		{
			if(countgps > 80)
			{
			    format(frmt_business_gps, sizeof frmt_business_gps, "%sДалее",frmt_business_gps);
				break;
			}
			
    	    format(frmt_biz_gps, sizeof frmt_biz_gps, "{FF7319}%d.{FFFFFF} %s\n", countgps+1, BizInfo[b][bName]);
			
            AddBusinessList(playerid, frmt_business_gps, sizeof frmt_business_gps, frmt_biz_gps, BizInfo[b][bID], countgps);
            countgps++;
		}
	}
	
	if(!countgps)
		return SendClientMessage(playerid, COLOR_GREY, !"Локации отсутствуют.");

	ShowPlayerDialogEx(playerid, 525, DIALOG_STYLE_LIST, !"GPS", frmt_business_gps, !"Отметить", !"Назад");
	
	return 1;
}
stock ShowEatBusinessList(playerid)
{
	new
	    frmt_biz_gps[80],
	    countgps,
		frmt_business_gps[800];

	for(new b; b < MAX_BIZ; b++)
		if(BizList[playerid][b] != -1)
		    BizList[playerid][b] = -1;


	for(new b; b < MAX_BIZ; b++)
	{
    	if(!GetString(BizInfo[b][bOwner], "The State") && BizInfo[b][bImprove][2] && (BizInfo[b][bState] == 2 || BizInfo[b][bState] == 3 || BizInfo[b][bState] == 4 || BizInfo[b][bState] == 5 || BizInfo[b][bState] == 6))
		{
			if(countgps > 80)
			{
			    format(frmt_business_gps, sizeof frmt_business_gps, "%sДалее",frmt_business_gps);
				break;
			}

    	    format(frmt_biz_gps, sizeof frmt_biz_gps, "{FF7319}%d.{FFFFFF} %s\n", countgps+1, BizInfo[b][bName]);

            AddBusinessList(playerid, frmt_business_gps, sizeof frmt_business_gps, frmt_biz_gps, BizInfo[b][bID], countgps);
            countgps++;
		}
	}

	if(!countgps)
		return SendClientMessage(playerid, COLOR_GREY, !"Локации отсутствуют.");

	ShowPlayerDialogEx(playerid, 525, DIALOG_STYLE_LIST, !"GPS", frmt_business_gps, !"Отметить", !"Назад");

	return 1;
}
stock AddFamilyList(playerid, string[], size, str[], fid, listitem)
{
	strcat(string, str, size);
	FamilyList[playerid][fid] = listitem;
	return true;
}
stock ShowFamilyList(playerid)
{
    new
        frmt_family_list[1900],
		family_name[64],
        frmt_family[130],
		family_total,
		id;

	new Cache:result = mysql_query(mysql, "SELECT `ID`, `Name` FROM `family` LIMIT 21");
    new rows = cache_get_row_count(mysql);

	if(!rows)
		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет созданных семей");

	for(new f; f < rows; f++)
		if(FamilyList[playerid][f] != -1)
		    FamilyList[playerid][f] = -1;

	family_list[playerid] = rows;
	
	for(new i; i < rows; i++)
	{
		id = cache_get_row_int(i, 0);
		cache_get_row(i, 1, family_name, mysql);
	    
	    if(family_total > 19 && strlen(family_name) != 0)
	    {
	        format(frmt_family_list, sizeof frmt_family_list, "%s>> Следующая страница", frmt_family_list);
	        pTemp[playerid][pFamLast] = id;
	        pTemp[playerid][pFamCount] = family_total;
	        break;
	    }
	    format(frmt_family, sizeof frmt_family, "{FF7319}%d.{FFFFFF} %s\n", i+1, family_name);
	    
	    AddFamilyList(playerid, frmt_family_list, sizeof frmt_family_list, frmt_family, id-1, family_total);
	    family_total++;
	    
	}
	ShowPlayerDialogEx(playerid, 603, DIALOG_STYLE_LIST, !"Список семей", frmt_family_list, !"Далее", !"Закрыть");
	cache_delete(result, mysql);
	return 1;
}
public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	return true;
}
stock CreatePickupEx(model,type,Float:X,Float:Y,Float:Z, Virtualworld)
{
    new pickupid = CreatePickup(model,type,X,Y,Z,Virtualworld);
    Pickups[pickupid][0] = X;
    Pickups[pickupid][1] = Y;
    Pickups[pickupid][2] = Z;
    return pickupid;
}
stock GetPickupPos(pickupid,&Float:X,&Float:Y,&Float:Z)
{
    X = Pickups[pickupid][0];
    Y = Pickups[pickupid][1];
    Z = Pickups[pickupid][2];
    return true;
}
public OnPlayerPickUpPickup(playerid, pickupid)
{
	return true;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if(!PI[playerid][pCars])
		return 1;

	new
		carID = GetCarSlot(PI[playerid][pCars]);
		
	if(carID == -1)
		return 1;
	
	if(GetPlayerVehicleID(playerid) != CarInfo[carID][cVehID])
		return 1;
		
	ShowPlayerDialogEx(playerid, 669, DIALOG_STYLE_MSGBOX, !"Сохранение тюнинга", !"{FFFFFF}Вы хотите купить данный элемент тюнинга?\nТюнинг не исчезнет с Вашей машины до её продажи или снятия всего тюнинга\n\nЦена: {33AA00}10000$", !"Да", !"Нет");

	pTemp[playerid][pTuningID] = vehicleid;
	pTemp[playerid][pTuningComponent] = componentid;
	
	return true;
}
public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	if(!PI[playerid][pCars])
		return 1;

	new
		carID = GetCarSlot(PI[playerid][pCars]);
		
	if(carID == -1)
		return 1;
	
	if(GetPlayerVehicleID(playerid) != CarInfo[carID][cVehID])
		return 1;

	for(new i; i < sizeof CarInfo; i++)
	{
		if(CarInfo[i][cVehID] != vehicleid)
			continue;
			
		CarInfo[i][cColor_1] = color1;
		CarInfo[i][cColor_2] = color2;
	}
	SaveOwnableCar(playerid, vehicleid);
    return 1;
}
public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if(!PI[playerid][pCars])
		return 1;

	new
		carID = GetCarSlot(PI[playerid][pCars]);

	if(carID == -1)
		return 1;

	if(GetPlayerVehicleID(playerid) != CarInfo[carID][cVehID])
		return 1;

	ShowPlayerDialogEx(playerid, 671, DIALOG_STYLE_MSGBOX, !"Сохранение тюнинга", !"{FFFFFF}Вы хотите купить данный элемент тюнинга?\nТюнинг не исчезнет с Вашей машины до её продажи или снятия всего тюнинга\n\nЦена: {33AA00}15000$", !"Да", !"Нет");

	pTemp[playerid][pTuningID] = vehicleid;
	pTemp[playerid][pTuningPaintjob] = paintjobid+1;
	
	/*for(new i; i < sizeof CarInfo; i++)
	{
		if(CarInfo[i][cVehID] != vehicleid)
			continue;

		CarInfo[i][cPaintJob] = paintjobid;
	}
	SaveOwnableCar(playerid, vehicleid);*/
    return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid)
{
	new Float:health, Float:armour;
	GetPlayerHealth(damagedid, health);
	GetPlayerArmour(damagedid, armour);
	if(weaponid != 0) pTemp[damagedid][pTakeShot] += 1;
	if(damagedid != INVALID_PLAYER_ID && (temp_tazer_timer[damagedid] || temp_cuffer_sender[damagedid] != INVALID_PLAYER_ID))
	{
		health -= amount;
		if(health < 0.0) health = 0.0;
		return SetPlayerHealth(damagedid, health);
	}
	if(pTemp[playerid][pPaintTeam])
	{
		if(damagedid != INVALID_PLAYER_ID && pTemp[playerid][pPaintTeam] == pTemp[damagedid][pPaintTeam])
		{
			SendClientMessage(playerid, COLOR_RED, !"Прекратите стрельбу по союзнику");
			ApplyAnimation(playerid, "FAT", "IDLE_tired", 4.0, 0, 0, 0, 0, 6000);
			return SetPlayerHealth(damagedid, amount);
		}
	}

	return true;
}
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	pTemp[playerid][pTakeDmg] += 1;
	    
	pTemp[playerid][pAllDmg] += amount;
	
	if(amount > 0)
 	{
		if(issuerid != INVALID_PLAYER_ID)
			SetPlayerSkills(issuerid);
	}
	if(weaponid == 3 && !IsPlayerInAnyVehicle(issuerid) && !pTemp[issuerid][pPaintTeam])
	{
	    if(IsACop(issuerid) || PI[issuerid][pFraction] == 10)
	    {
			if(PI[issuerid][pFraction] == PI[playerid][pFraction]) return SendClientMessage(issuerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Оглушение на вашего сотрудника не будет действовать");
			if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(issuerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в машине!");
			if(temp_tazer_timer[playerid] > 0 || temp_cuffer_sender[playerid] != INVALID_PLAYER_ID) return SendClientMessage(issuerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже оглушен / в наручниках");

			new
			    temp_tazer_message[128];

			format(temp_tazer_message, sizeof temp_tazer_message, "%s оглушил(а) подозреваемого %s", PN(issuerid), PN(playerid));
			ProxDetector(25, playerid, temp_tazer_message, COLOR_ME);

			f_TogglePlayerControllable(playerid, false);
			GoAnim(playerid, "CRACK", "Crckidle2", 4.1, 1, 0, 0, 0, 0, 0);
			temp_tazer_timer[playerid] = 15;
		}
	}
	if(weaponid == 23 && !IsPlayerInAnyVehicle(issuerid) && !pTemp[issuerid][pPaintTeam])
	{
	    if(IsACop(issuerid))
	    {
	        if(temp_tazer_gun[issuerid] == false) return 1;
			if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(issuerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок в машине!");
			if(temp_tazer_timer[playerid] > 0 || temp_cuffer_sender[playerid] != INVALID_PLAYER_ID) return SendClientMessage(issuerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже оглушен / в наручниках");

			new
			    temp_tazer_message[128];

			format(temp_tazer_message, sizeof temp_tazer_message, "%s оглушил(а) подозреваемого %s", PN(issuerid), PN(playerid));
			ProxDetector(25, playerid, temp_tazer_message, COLOR_ME);

			f_TogglePlayerControllable(playerid, false);
			GoAnim(playerid, "CRACK", "Crckidle2", 4.1, 1, 0, 0, 0, 0, 0);
			temp_tazer_timer[playerid] = 15;
		}
	}
	return true;
}

forward OnPlayerAmmoChange(playerid, newammo, oldammo);
public OnPlayerAmmoChange(playerid, newammo, oldammo)
{
	if(newammo < oldammo)
	{
		switch(GetPlayerWeapon(playerid))
		{
			case 24:
			{
				SetPVarInt(playerid, "SkillD",GetPVarInt(playerid, "SkillD") +1);
				if(GetPVarInt(playerid, "SkillD") >= 14 && PI[playerid][pEagle_Skill] < 100)
				{
					PI[playerid][pEagle_Skill]++;
					SetPVarInt(playerid, "SkillD",0);
				}
				if(PI[playerid][pQuest] == 12 && PI[playerid][pQuestStatus] == 1)
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, 801.6865, 1676.1392, 5.2813))
					{
					    PI[playerid][pQuestProcess]++;
					    UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
						if(PI[playerid][pQuestProcess] >= 200)
						{
					        PI[playerid][pQuestStatus] = 0;
					        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
					    	SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выстрелили 200 патронов из Desert Eagle. Отправляйтесь к Линкольну");
						}
					}
				}
			}
			case 23:
			{
				SetPVarInt(playerid, "SkillSD",GetPVarInt(playerid, "SkillSD") +1);
				if(GetPVarInt(playerid, "SkillSD")>= 12 && PI[playerid][pSDPistol_Skill] < 100)
				{
					PI[playerid][pSDPistol_Skill]++;
					SetPVarInt(playerid, "SkillSD",0);
				}
			}
			case 25:
			{
				SetPVarInt(playerid, "SkillShot",GetPVarInt(playerid, "SkillShot") +1);
				if(GetPVarInt(playerid, "SkillShot") >= 8 && PI[playerid][pShotGun_Skill] < 100)
				{
					PI[playerid][pShotGun_Skill]++;
					SetPVarInt(playerid, "SkillShot",0);
				}
			}
			case 29:
			{
				SetPVarInt(playerid, "SkillMP5",GetPVarInt(playerid, "SkillMP5") +1);
				if(GetPVarInt(playerid, "SkillMP5") >= 25 && PI[playerid][pMP5_Skill] < 100)
				{
					PI[playerid][pMP5_Skill]++;
					SetPVarInt(playerid, "SkillMP5",0);
				}
			}
			case 30:
			{
				SetPVarInt(playerid, "SkillAk47",GetPVarInt(playerid, "SkillAk47") +1);
				if(GetPVarInt(playerid, "SkillAk47") >= 30 && PI[playerid][pAK47_Skill] < 100)
				{
					PI[playerid][pAK47_Skill]++;
					SetPVarInt(playerid, "SkillAk47",0);
				}
			}
			case 31:
			{
				SetPVarInt(playerid, "SkillM4",GetPVarInt(playerid, "SkillM4") +1);
				if(GetPVarInt(playerid, "SkillM4") >= 30 && PI[playerid][pM4_Skill] < 100)
				{
					PI[playerid][pM4_Skill]++;
					SetPVarInt(playerid, "SkillM4",0);
				}
			}
		}
	}
	return true;
}

stock SetPlayerSkills(playerid)
{
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 	PI[playerid][pSDPistol_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 	PI[playerid][pEagle_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 			PI[playerid][pShotGun_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 				PI[playerid][pMP5_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 			PI[playerid][pAK47_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 				PI[playerid][pM4_Skill]*10);
	return true;
}
stock UpdateWeaponSkill(playerid)
{
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 	PI[playerid][pSDPistol_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 	PI[playerid][pEagle_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 			PI[playerid][pShotGun_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 				PI[playerid][pMP5_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 			PI[playerid][pAK47_Skill]*10);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 				PI[playerid][pM4_Skill]*10);
	return true;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return true;
}
public EngineVehicle(playerid, vehicleid)
{
	if(IsPlayerInVehicle(playerid,vehicleid))
	{
	   //if(!IsAOwnableCar(vehicleid) || CarInfo[GetVehicleID(vehicleid)][cKeyIN])
	    //{
	        new Float:Health;
			AntiCheatGetVehicleHealth(vehicleid, Health);
			if(Health > 1000.0) Health = 1000.0;
		    SetEngineStatus(vehicleid);
		//}
	}
	return true;
}
stock MuchNumber(...)
{
	new count = numargs(), maxnum;
	for(new i; i < count; i ++)
	{
	    new temp = getarg(i);
	    if(temp > maxnum) maxnum = temp;
	}
	return maxnum;
}

stock bool:bollean(value)
{
	return value?true:false;
}

stock PreloadAnimLib(playerid, animlib[]) {      ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);      return true; }
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerVirtualWorld(playerid)==1228)return 1;

	if(!IsPlayerInAnyVehicle(playerid))
	{
	    if((newkeys & KEY_FIRE || (oldkeys & 128 && newkeys & 16)) || (newkeys & KEY_HANDBRAKE && !(oldkeys & KEY_HANDBRAKE)))
	    {
			if(GetPlayerWeapon(playerid) != 43 && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DRINK_SPRUNK && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DRINK_WINE && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_SMOKE_CIGGY && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DRINK_BEER)
			{
				for(new i; i < sizeof(gGreenZone); i++)
				{
					if(IsPlayerInDynamicArea(playerid, gGreenZone[i]) && GetPVarInt(playerid, "antidm") < gettime())
					{
					    if(PI[playerid][pAdmin] < 3)
					    {
							temp_green_zone_warning[playerid] += 1;
							SetPVarInt(playerid, "antidm", gettime()+1);
							if(temp_green_zone_warning[playerid] >= 5)
							{
								SendClientMessage(playerid, 0xFF182DFF, !"Вы были кикнуты за ДМ");
								J_Kick(playerid);
							}
							else
							{
								new
									format_green_zone_warning[64];

								format(format_green_zone_warning, sizeof format_green_zone_warning, "{FFFFFF}ДМ в зеленых зонах запрещен (%d/5)", temp_green_zone_warning[playerid]);
								ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Предупреждение", format_green_zone_warning, !"ОК",!"");

								if(temp_tie_sender[playerid] == INVALID_PLAYER_ID)
								{
									ApplyAnimation(playerid, !"FAT", !"IDLE_tired", 3.0, 1, 0, 0, 0, 3000);
									SetPVarInt(playerid, "anim_antidm", gettime()+3);
									SetTimerEx("@__UnFreez",3000, false, "i", playerid);
								}
								pTemp[playerid][pAntiDM] += 3;
							}
						}
					}
				}
				if(IsPlayerInDynamicArea(playerid, gDemorgan) && GetPVarInt(playerid, "antidm") < gettime())
				{
					SetPVarInt(playerid, "antidm", gettime()+1);
					if(temp_tie_sender[playerid] == INVALID_PLAYER_ID)
					{
						ApplyAnimation(playerid, !"FAT", !"IDLE_tired", 3.0, 1, 0, 0, 0, 3000);
						SetPVarInt(playerid, "anim_antidm", gettime()+3);
						SetTimerEx("@__UnFreez",3000, false, "i", playerid);
					}
				}
			}
		}
	}
	if (newkeys & KEY_SPRINT)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && PI[playerid][pSpectatee] != INVALID_PLAYER_ID) StopPlayerSpectate(playerid);
		if(PI[playerid][pSelectStoreGun])
		{
			new gunname[32],mes[128];
			GetWeaponName(HintGunID[PI[playerid][pStoreGun]],gunname,32);
			format(mes,sizeof(mes),"{FFFFFF}Укажите сколько патронов{33AA33}%s{FFFFFF} Вы хотите взять:");
			ShowPlayerDialogEx(playerid,537,1,"Шкаф",mes,"Взять","Отмена");
			return 1;
		}
		new vehicleid = GetPlayerVehicleID(playerid);
		if(temp_filling_status[playerid])
		{
			new
				fillingid = temp_filling_id[playerid]-1,
 				Float:getfuel;

			getfuel = temp_filling_amount[playerid] - VehicleInfo[vehicleid][vFuel];

			if(!GetString(gFillings[fillingid][fillingOwner], "The State"))
			{
				if(gFillings[fillingid][fillingFuel] < getfuel)
				{
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
					SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На заправке недостаточно топлива.");
					return 1;
				}
				if(!gFillings[fillingid][fillingWorking])
				{
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
					SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Заправка закрыта");
					return 1;
				}
			}
			UpdateFillingBar(playerid, vehicleid);

			if(temp_filling_price[playerid] < 0)
			{
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
			 	SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка. Попробуйте выбрать меньше количество бензина");
			 	return 1;
			}
			if(PI[playerid][pMoney] < temp_filling_price[playerid])
			{
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
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				return 1;
			}
			if(!GetString(gFillings[fillingid][fillingOwner], "The State"))
				GiveFillingMoney(fillingid, temp_filling_price[playerid]);

			SendClientMessage(playerid, COLOR_WHITE,"{FFC800}[Подсказка] {FFFFFF}Ждите, идет заправка");

			if(!GetString(gFillings[fillingid][fillingOwner], "The State"))
				gFillings[fillingid][fillingFuel] -= floatround(getfuel);

			SaveFilling(fillingid);

			GiveMoney(playerid, -temp_filling_price[playerid], "заправка");

			temp_filling_status[playerid] = false;
			HideFillingBar(playerid);
			temp_filling_going[playerid] = true;
			return 1;
		}
		if(GetBarrierID(playerid) != -1)
		{
		    if(GetBarrierID(playerid) >= 0 && GetBarrierID(playerid) <= 11)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;
					
				if(PI[playerid][pFraction] != 1)
				    return 1;

				switch(GetPlayerVirtualWorld(playerid))
				{
				    case 1: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
				    case 2: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
				    case 3: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
				}
                SetPVarInt(playerid, "doortext", false);
                DeletePVar(playerid, "open_time");
                
		        if(gBarrier_Status[GetBarrierID(playerid)])
					gBarrier_Status[GetBarrierID(playerid)] = 0, CloseBarrier(GetBarrierID(playerid));
					
		        else
					gBarrier_Status[GetBarrierID(playerid)] = 1, OpenBarrier(GetBarrierID(playerid));

                SetPVarInt(playerid, "open_time", gettime()+3);
			}
		    if(GetBarrierID(playerid) >= 12 && GetBarrierID(playerid) <= 23)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;
					
				if(PI[playerid][pFraction] != 8)
				    return 1;

				switch(GetPlayerVirtualWorld(playerid))
				{
				    case 2: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
				    case 0: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
				    case 12: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
				}
				
                SetPVarInt(playerid, "doortext", false);
                DeletePVar(playerid, "open_time");

		        if(gBarrier_Status[GetBarrierID(playerid)])
					gBarrier_Status[GetBarrierID(playerid)] = 0, CloseBarrier(GetBarrierID(playerid));

		        else
					gBarrier_Status[GetBarrierID(playerid)] = 1, OpenBarrier(GetBarrierID(playerid));

                SetPVarInt(playerid, "open_time", gettime()+1);
			}
		    if(GetBarrierID(playerid) >= 24 && GetBarrierID(playerid) <= 35)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;

				if(PI[playerid][pFraction] != 9)
				    return 1;

				switch(GetPlayerVirtualWorld(playerid))
				{
				    case 1: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
				    case 2: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
				    case 3: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
				}
					
                SetPVarInt(playerid, "doortext", false);
                DeletePVar(playerid, "open_time");

		        if(gBarrier_Status[GetBarrierID(playerid)])
					gBarrier_Status[GetBarrierID(playerid)] = 0, CloseBarrier(GetBarrierID(playerid));

		        else
					gBarrier_Status[GetBarrierID(playerid)] = 1, OpenBarrier(GetBarrierID(playerid));

                SetPVarInt(playerid, "open_time", gettime()+3);
			}
		    if(GetBarrierID(playerid) >= 36 && GetBarrierID(playerid) <= 39)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;

				if(PI[playerid][pFraction] != 11)
				    return 1;

                SetPVarInt(playerid, "doortext", false);
                DeletePVar(playerid, "open_time");

		        if(gBarrier_Status[GetBarrierID(playerid)])
					gBarrier_Status[GetBarrierID(playerid)] = 0, CloseBarrier(GetBarrierID(playerid));

		        else
					gBarrier_Status[GetBarrierID(playerid)] = 1, OpenBarrier(GetBarrierID(playerid));

                SetPVarInt(playerid, "open_time", gettime()+3);
			}
		}
		// риэлторка возвращение
		if(!IsPlayerInAnyVehicle(playerid))
		{
		    if(GetPVarInt(playerid, "watch_house"))
		    {
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "housephoto_world"));
				SetCameraBehindPlayer(playerid);
				f_TogglePlayerControllable(playerid, true);
				SetPlayerPos(playerid, -2164.1838, 641.7682, 1052.3750);
				DeletePVar(playerid, "watch_house");
				DeletePVar(playerid, "housephoto_world");
				f_TogglePlayerControllable(playerid, true);

			    new
					frmt_house_info[240],
					classname[20],
					hid = pTemp[playerid][pEstateHouseInfo],
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
			else if(GetPVarInt(playerid, "watch_business"))
			{
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "businessphoto_world"));
				SetCameraBehindPlayer(playerid);
				f_TogglePlayerControllable(playerid, true);
				SetPlayerPos(playerid, -2164.1838, 641.7682, 1052.3750);
				DeletePVar(playerid, "watch_business");
				DeletePVar(playerid, "businessphoto_world");
				f_TogglePlayerControllable(playerid, true);

			    new
					frmt_biz_info[240],
					bid = pTemp[playerid][pEstateBizInfo],
	    			rent = floatround(BizInfo[bid-1][bCost] / 800);

			    format(frmt_biz_info, sizeof frmt_biz_info, "{FFFFFF}Номер: %d\n{FFFFFF}Название: %s\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию бизнеса\n{ED6160} > Отметить бизнес на GPS", bid, BizInfo[bid-1][bName], BizInfo[bid-1][bCost], rent);
			    ShowPlayerDialogEx(playerid, 383, DIALOG_STYLE_LIST, !"Информация о бизнесе", frmt_biz_info, !"Выбор", !"Назад");
			    return 1;
			}
			else if(GetPVarInt(playerid, "watch_filling"))
			{
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "fillingphoto_world"));
				SetCameraBehindPlayer(playerid);
				f_TogglePlayerControllable(playerid, true);
				SetPlayerPos(playerid, -2164.1838, 641.7682, 1052.3750);
				DeletePVar(playerid, "watch_filling");
				DeletePVar(playerid, "fillingphoto_world");
				f_TogglePlayerControllable(playerid, true);

		    	new
					frmt_fill_info[240],
					fid = pTemp[playerid][pEstateFillInfo],
	    			rent = floatround(gFillings[fid-1][fillingPrice]/200);

			    format(frmt_fill_info, sizeof frmt_fill_info, "{FFFFFF}Номер: %d\n{FFFFFF}Цена: {33AA33}%d$\n{FFFFFF}Стоимость платы за сутки: {33AA33}%d$\n{ED6160} > Просмотреть фотографию АЗС\n{ED6160} > Отметить АЗС на GPS", fid, gFillings[fid-1][fillingPrice], rent);
			    ShowPlayerDialogEx(playerid, 386, DIALOG_STYLE_LIST, !"Информация о АЗС", frmt_fill_info, !"Выбор", !"Назад");
			    return 1;
			}
		}
		return 1;
	}
	if (newkeys & KEY_SECONDARY_ATTACK)
	{
        if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 1;
		if(PI[playerid][pSelectStoreGun])
		{
			new Float:x, Float:y, Float:z, Float:x1, Float:y1, Float:z1;
			x = GetPVarFloat(playerid,"oldcx");
			y = GetPVarFloat(playerid,"oldcy");
			z = GetPVarFloat(playerid,"oldcz");
			GetPlayerCameraPos(playerid,x1,y1,z1);
			InterpolateCameraPos(playerid,x1,y1,z1,x,y,z,700,CAMERA_MOVE);
			SetTimerEx("SetCameraBehindPlayerDelay",1000,false,"i",playerid);
			//SetCameraBehindPlayer(playerid);
			PI[playerid][pSelectStoreGun] = false;
			PI[playerid][pStoreGun] = 0;
			GameTextForPlayer(playerid," ",100,3);
			TogglePlayerControllable(playerid,1);
		}
        for(new t; t < sizeof(gCasinoTable); t++)
        {
            if(IsPlayerInDynamicArea(playerid, gCasinoTable[t]))
            {
                if(InJob[playerid] == 8)
                {
                    if(gTable[t][tCrup] != INVALID_PLAYER_ID)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}За этим столом уже есть крупье");
						
                    gTable[t][tCrup] = playerid;
                    
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Для того чтобы изменить ставку нажмите кнопку {FF4B0F}BET{FFFFFF}, для начала игры нажмите кнопку {5CFFD6}DEAL");

					for(new td = 0; td < 13; td++)
						TextDrawShowForPlayer(playerid, crupie_table[t][td]);
						
                    SelectTextDraw(playerid, 0xFFFFFFFF), temp_table[playerid] = t;
                    
				    new
						frmt_bet[26];

				    format(frmt_bet, sizeof frmt_bet, "%d$", gTable[t][tBet]);
				    TextDrawSetString(crupie_table[t][5], frmt_bet);
				    format(frmt_bet, sizeof frmt_bet, "%d/4", Casino_TotalPlayer(t));
				    TextDrawSetString(crupie_table[t][6], frmt_bet);
                }
                else
				{
					for(new td = 0; td < 22; td++)
						PlayerTextDrawShow(playerid, casino_table[t][td]);

					SelectTextDraw(playerid, 0xFFFFFFFF), temp_table[playerid] = t;
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Для того чтобы сделать ставку нажмите кнопку {FF4B0F}SET BET{FFFFFF}, для выхода нажмите кнопку {5E29FF}EXIT");
					
				    new
						frmt_bet[26];

				    format(frmt_bet, sizeof frmt_bet, "%d$", gTable[t][tBet]);
				    PlayerTextDrawSetString(playerid, casino_table[t][16], frmt_bet);
				    format(frmt_bet, sizeof frmt_bet, "%d$", gTable[t][tBet]*Casino_TotalPlayer(t));
				    PlayerTextDrawSetString(playerid, casino_table[t][17], frmt_bet);

				    new frmt_player_bet[20 + MAX_PLAYER_NAME];

				    /* foreach(new i : Player)
				    {
					    if(temp_table[i] == t && Casino_GetPlayerID(t, i) != -1)
                    		gTable[t][tPlayers][Casino_GetSlot(t)] = i;
                    }*/
                    
				    new
				        check[4];

					for(new tc; tc < 4; tc++)
						check[tc] = INVALID_PLAYER_ID;

					for(new tc; tc < 4; tc++)
					{
                        if(gTable[t][tPlayers][tc] != INVALID_PLAYER_ID)
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~1. ~w~%s", PN(gTable[t][tPlayers][tc]));
							PlayerTextDrawSetString(playerid, casino_table[t][8], frmt_player_bet);
							check[0] = gTable[t][tPlayers][tc];
							break;
						}
					}
					for(new tc; tc < 4; tc++)
					{
                        if(gTable[t][tPlayers][tc] != INVALID_PLAYER_ID && check[0] != gTable[t][tPlayers][tc])
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~2. ~w~%s", PN(gTable[t][tPlayers][tc]));
							PlayerTextDrawSetString(playerid, casino_table[t][9], frmt_player_bet);
							check[1] = gTable[t][tPlayers][tc];
							break;
						}
					}
					for(new tc; tc < 4; tc++)
					{
                        if(gTable[t][tPlayers][tc] != INVALID_PLAYER_ID && check[0] != gTable[t][tPlayers][tc] && check[1] != gTable[t][tPlayers][tc])
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~3. ~w~%s", PN(gTable[t][tPlayers][tc]));
							PlayerTextDrawSetString(playerid, casino_table[t][10], frmt_player_bet);
							check[2] = gTable[t][tPlayers][tc];
							break;
						}
					}
					for(new tc; tc < 4; tc++)
					{
                        if(gTable[t][tPlayers][tc] != INVALID_PLAYER_ID && check[0] != gTable[t][tPlayers][tc] && check[1] != gTable[t][tPlayers][tc] && check[2] != gTable[t][tPlayers][tc])
                        {
							format(frmt_player_bet,sizeof frmt_player_bet,"~b~4. ~w~%s", PN(gTable[t][tPlayers][tc]));
							PlayerTextDrawSetString(playerid, casino_table[t][11], frmt_player_bet);
							check[3] = gTable[t][tPlayers][tc];
							break;
						}
					}

					if(check[0] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(playerid, casino_table[t][8], "-");

					if(check[1] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(playerid, casino_table[t][9], "-");

					if(check[2] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(playerid, casino_table[t][10], "-");

					if(check[3] == INVALID_PLAYER_ID)
						PlayerTextDrawSetString(playerid, casino_table[t][11], "-");

				}
            }
        }
	}

    if((newkeys & KEY_SECONDARY_ATTACK && GetPVarInt(playerid,"Animation") == 1))
    {
	    ClearAnimations(playerid);
	    DeletePVar(playerid,"Animation");
		TextDrawHideForPlayer(playerid, AnimDraw);
    }
    if(newkeys & KEY_JUMP && InJob[playerid] == 5 && temp_job_status[playerid] == 2 ||
	newkeys & KEY_FIRE && InJob[playerid] == 5 && temp_job_status[playerid] == 2)
	{
		SendClientMessage(playerid, COLOR_GREY, !"Вы уронили щебень");
		
		new
		    checkpoint = RandomEx(0, 3);

	    TogglePlayerDynamicCP(playerid, gRoadGet[checkpoint], true);
	    RoadGet[playerid] = checkpoint+1;
	    for(new i; i < 3; i++) TogglePlayerDynamicCP(playerid, gRoadCP[i], false);
		temp_job_status[playerid] = 1;
		
	    RemovePlayerAttachedObjectEx(playerid, 0);
	    RemovePlayerAttachedObjectEx(playerid, 1);
	}
    if(newkeys & KEY_JUMP && InJob[playerid] == 6 && temp_porter_status[playerid] == 2 ||
	newkeys & KEY_FIRE && InJob[playerid] == 6 && temp_porter_status[playerid] == 2)
	{
		SendClientMessage(playerid, COLOR_GREY, !"Вы уронили ящик");
		temp_porter_status[playerid] = 1;
		
	    for(new i = 0; i < 5; i ++)
	    	TogglePlayerDynamicCP(playerid, PorterUnload[i], false);

		ClearAnimations(playerid);

		new job_cp = RandomEx(0,5);
		TogglePlayerDynamicCP(playerid, PorterLoad[job_cp], true);
	    RemovePlayerAttachedObjectEx(playerid, 0);
	}
    if(newkeys & KEY_JUMP)
	{
		if(InJob[playerid] == 7 && temp_auto_amount[playerid] == 3)
		{
		    SendClientMessage(playerid, COLOR_GREY, !"Вы уронили запчасть");
		    ClearAnimations(playerid);
			RemovePlayerAttachedObject(playerid, 0);
			temp_auto_amount[playerid] = 1;
			DisablePlayerCheckpoint(playerid);
		}
	}
    if(temp_cuffer_sender[playerid] != INVALID_PLAYER_ID)
    {
		if(!IsPlayerInAnyVehicle(playerid))
		{
			if((newkeys & KEY_JUMP || newkeys & KEY_FIRE || newkeys & KEY_CROUCH || (newkeys & KEY_HANDBRAKE && newkeys & KEY_SECONDARY_ATTACK)))
			{
				ClearAnimations(playerid, 1);
				ApplyAnimation(playerid, !"FAT", !"IDLE_tired", 3.0, 1, 0, 0, 0, 3000, 1);
				SendClientMessage(playerid, COLOR_GREY, !"Вы не можете использовать это действие так как Вы в наручниках.");
			}
		}
	}

	if(newkeys & KEY_NO)
	{
	    if(GetPVarInt(playerid, "NeedMech") == 1) DeletePVar(playerid, "NeedMech"), SCM(playerid, COLOR_WHITE, "Вы отказались от вызова.");
		if(temp_fill_sender[playerid] != INVALID_PLAYER_ID)
		{
			new scdplayerid = temp_fill_sender[playerid], price = GetPVarInt(playerid, "MechanicPrice");
			new lstring[144];
			format(lstring, sizeof(lstring), "{FF2222}[Ошибка] {FFC800}%s {ffffff}отклонил предложение заправить транспорт за {FFC800}$%i.", PN(playerid), price);
			SCM(scdplayerid, COLOR_WHITE, lstring);
			SendClientMessage(playerid,-1,"Вы оклонили предложение");
			DeletePVar(playerid, "MechanicPrice");
			DeletePVar(playerid, "MechanicFuel");
			temp_fill_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_repair_sender[playerid] != INVALID_PLAYER_ID)
		{
			new scdplayerid = temp_repair_sender[playerid], price = GetPVarInt(playerid, "MechanicPrice");
			new lstring[144];
			format(lstring, sizeof(lstring), "{FF2222}[Ошибка] {FFC800}%s {ffffff}отклонил предложение починить транспорт за {FFC800}$%i.", PN(playerid), price);
			SCM(scdplayerid, COLOR_WHITE, lstring);
			SendClientMessage(playerid,-1,"Вы оклонили предложение");
			DeletePVar(playerid, "MechanicPrice");
			temp_repair_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_house_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_house_timer[playerid])
			    return 1;
		
			new
				sellerid = temp_house_seller[playerid]-1;

			SendClientMessage(playerid, COLOR_GREY, !"Вы отказались от покупки дома");
			SendClientMessage(sellerid, COLOR_GREY, !"Покупатель отказался покупать дом");
			temp_house_seller[playerid] = INVALID_PLAYER_ID;
			temp_house_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_house_id[playerid] = 0;
			temp_house_price[playerid] = 0;
			temp_house_timer[playerid] = 0;
		}
		
		if(temp_car_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_car_timer[playerid])
			    return 1;
			    
			new
				sellerid = temp_car_seller[playerid]-1;

			SendClientMessage(playerid, COLOR_GREY, !"Вы отказались от покупки т/c");
			SendClientMessage(sellerid, COLOR_GREY, !"Покупатель отказался покупать т/c");
			temp_car_seller[playerid] = INVALID_PLAYER_ID;
			temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_car_id[playerid] = 0;
			temp_car_number[playerid] = 0;
			temp_car_price[playerid] = 0;
			temp_car_timer[playerid] = 0;
		}
		if(temp_biz_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_biz_timer[playerid])
			    return 1;

			new
				sellerid = temp_biz_seller[playerid]-1;

			SendClientMessage(playerid, COLOR_GREY, !"Вы отказались от покупки бизнеса");
			SendClientMessage(sellerid, COLOR_GREY, !"Покупатель отказался покупать бизнес");
			temp_biz_seller[playerid] = INVALID_PLAYER_ID;
			temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_biz_id[playerid] = 0;
			temp_biz_price[playerid] = 0;
			temp_biz_timer[playerid] = 0;
		}
		if(temp_fill_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_fill_timer[playerid])
			    return 1;

			new
				sellerid = temp_fill_seller[playerid]-1;

			SendClientMessage(playerid, COLOR_GREY, !"Вы отказались от покупки АЗС");
			SendClientMessage(sellerid, COLOR_GREY, !"Покупатель отказался покупать АЗС");
			temp_fill_seller[playerid] = INVALID_PLAYER_ID;
			temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_fill_id[playerid] = 0;
			temp_fill_price[playerid] = 0;
			temp_fill_timer[playerid] = 0;
		}
		if(temp_sim_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_sim_timer[playerid])
			    return 1;

			new
				sellerid = temp_sim_seller[playerid]-1;

			SendClientMessage(playerid, COLOR_GREY, !"Вы отказались от покупки SIM-карты");
			SendClientMessage(sellerid, COLOR_GREY, !"Покупатель отказался покупать SIM-карту");
			temp_sim_seller[playerid] = INVALID_PLAYER_ID;
			temp_sim_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_sim_num[playerid] = 0;
			temp_sim_price[playerid] = 0;
			temp_sim_timer[playerid] = 0;
		}
		if(temp_pass_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_pass_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

            temp_pass_receiver[receiver] = INVALID_PLAYER_ID;
            temp_pass_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_pts_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_pts_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

            temp_pts_receiver[receiver] = INVALID_PLAYER_ID;
            temp_pts_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_wedding_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_wedding_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_lic_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_lic_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

            temp_lic_receiver[receiver] = INVALID_PLAYER_ID;
            temp_lic_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_skill_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_skill_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

            temp_skill_receiver[receiver] = INVALID_PLAYER_ID;
            temp_skill_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_sellmed_sender[playerid] != INVALID_PLAYER_ID)
		{
		    if(!temp_sellmed_timer[playerid])
		        return 1;
		        
		    new
		        receiver = temp_sellmed_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

            temp_sellmed_receiver[receiver] = INVALID_PLAYER_ID;
            temp_sellmed_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_med_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_med_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

            temp_med_receiver[receiver] = INVALID_PLAYER_ID;
            temp_med_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_vacation_sender[playerid] != INVALID_PLAYER_ID)
		{
		    if(!temp_vacation_timer[playerid])
		        return 1;
		        
		    new
		        receiver = temp_vacation_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от отпуска");
			SendClientMessage(receiver, -1, !"Игрок отказался от отпуска");

	        temp_vacation_receiver[receiver] = INVALID_PLAYER_ID;
	        temp_vacation_sender[playerid] = INVALID_PLAYER_ID;
			temp_vacation_days[playerid] = 0;
			temp_vacation_timer[playerid] = 0;
		}
		if(temp_vac_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_vac_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от вакцинации");
			SendClientMessage(receiver, -1, !"Игрок отказался от вакцинации");
			
		    temp_vac_receiver[receiver] = INVALID_PLAYER_ID;
		    temp_vac_sender[playerid] = INVALID_PLAYER_ID;
		    temp_vac_id[playerid] = 0;
		}
		if(temp_setsex_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_setsex_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

		    temp_setsex_receiver[receiver] = INVALID_PLAYER_ID;
		    temp_setsex_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_sellgun_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellgun_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_sellgun_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellgun_sender[playerid] = INVALID_PLAYER_ID;
			temp_sellgun_id[playerid] = 0;
			temp_sellgun_ammo[playerid] = 0;
			temp_sellgun_price[playerid] = 0;
		}
		if(temp_selldrugs_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_selldrugs_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_selldrugs_receiver[receiver] = INVALID_PLAYER_ID;
			temp_selldrugs_sender[playerid] = INVALID_PLAYER_ID;
			temp_selldrugs_value[playerid] = 0;
			temp_selldrugs_price[playerid] = 0;
		}
		if(temp_sellzone_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellzone_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
			temp_sellzone_id[playerid] = 0;
			temp_sellzone_price[playerid] = 0;
		}
		if(temp_sellmbiz_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellmbiz_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
			temp_sellmbiz_id[playerid] = 0;
			temp_sellmbiz_price[playerid] = 0;
		}
		if(temp_ud_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_ud_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_ud_receiver[receiver] = INVALID_PLAYER_ID;
			temp_ud_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_flyer_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_flyer_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_flyer_receiver[receiver] = INVALID_PLAYER_ID;
			temp_flyer_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_selllic_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_selllic_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_selllic_receiver[receiver] = INVALID_PLAYER_ID;
			temp_selllic_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_free_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_free_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_free_receiver[receiver] = INVALID_PLAYER_ID;
			temp_free_sender[playerid] = INVALID_PLAYER_ID;
			temp_free_price[playerid] = 0;
		}
		if(temp_sellcard_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellcard_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_sellcard_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellcard_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_charity_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_charity_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");

			temp_charity_receiver[receiver] = INVALID_PLAYER_ID;
			temp_charity_sender[playerid] = INVALID_PLAYER_ID;
			temp_charity_price[playerid] = 0;
		}
		if(temp_finvite_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_finvite_sender[playerid] - 1;

			SendClientMessage(playerid, -1, !"Вы отказались от предложения");
			SendClientMessage(receiver, -1, !"Игрок отказался от предложения");
			
		    temp_finvite_receiver[receiver] = INVALID_PLAYER_ID;
		    temp_finvite_sender[playerid] = INVALID_PLAYER_ID;
		    temp_finvite_id[playerid] = 0;
		}
	}
	if(newkeys & KEY_YES)
	{
		if(IsPlayerInRangeOfPoint(playerid, 25.0, 2785.4731,-2493.4939,13.6531)  && PI[playerid][pJob] == JOB_PRODUCT)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			if(GetVehicleModel(vehicleid) != 456) return SCM(playerid, COLOR_GREY, "Вы должны находиться в специализированном транспорте!");
			if(GetPlayerState(playerid) != 2) return SCM(playerid, COLOR_GREY, "Вы должны быть за рулем т/с");
			if(GetPVarInt(playerid, "ProductID") > 0) return SCM(playerid, COLOR_GREY, "В данный момент вы уже выполняете заказ!");
			DisablePlayerRaceCheckpoint(playerid);
			ProductList(playerid);
		}
		if(GetPVarInt(playerid, "NeedMech") == 1)
		{
			if(MechCallTime[playerid] > 0) return SCM(playerid, COLOR_GREY, "Вы уже приняли вызов!");
			if(MechCall == -1) return SCM(playerid, COLOR_GREY, "Никто не вызывал механика!");
			if(!IsPlayerConnected(MechCall)) return SCM(playerid, COLOR_GREY, "Игрок не найден!");
			new lstring[144];
			format(lstring, sizeof(lstring), "{FFC800}[Подсказка]{ffffff} Автомеханик {FFC800}%s {ffffff}принял ваш вызов, оставайтесь на месте.", PN(playerid));
			SCM(MechCall, COLOR_WHITE, lstring);
			format(lstring, sizeof(lstring), "{7AC71F}[Успешно]{ffffff} Вы приняли вызов от {FFC800}%s. {ffffff}Направляйтесь к метке, указанной в GPS.", PN(MechCall));
			SCM(playerid, -1, lstring);
			new Float:X, Float:Y, Float:Z;
			GetPlayerPos(MechCall, X, Y, Z);
			SetPlayerRaceCheckpoint(playerid, 1, X, Y, Z, 0.0, 0.0, 0.0, 5);
			SetPVarInt(MechCall, "CallMech", gettime() + 180);
			MechCallTime[playerid] = 180;
			MechCall = -1;
			DeletePVar(playerid, "NeedMech");
		}
		if(temp_fill_sender[playerid] != INVALID_PLAYER_ID)
		{
			if(GetPlayerState(playerid) == 2)
			{
				new scdplayerid = temp_fill_sender[playerid], price = GetPVarInt(playerid, "MechanicPrice"), fuel = GetPVarInt(playerid, "MechanicFuel");
				new vehicleid = GetPlayerVehicleID(playerid);
				if(GetMoney(playerid) < price)
				{
					SendClientMessage(scdplayerid,-1,!"{FFC800}[Подсказка]{ffffff}У игрока недостаточно денег");
					DeletePVar(playerid, "MechanicPrice");
					DeletePVar(playerid, "MechanicFuel");
					temp_fill_sender[playerid] = INVALID_PLAYER_ID;
					return 1;
				}
				new lstring[144];
				format(lstring, sizeof(lstring), "{7AC71F}[Успешно]{ffffff} Автомеханик {FFC800}%s {ffffff}заправил ваше т/с за {FFC800}%d$.", PN(scdplayerid), price);
				SCM(playerid, COLOR_WHITE, lstring);
				format(lstring, sizeof(lstring), "{7AC71F}[Успешно]{ffffff} Вы заправили т/с {FFC800}%s {ffffff}за {FFC800}%d$.", PN(playerid), price);
				SCM(scdplayerid, COLOR_WHITE, lstring);

				pTemp[scdplayerid][pMechFuel] -= fuel;
				new mes[30];
				format(mes,sizeof mes,"Бензин: %d/500",pTemp[scdplayerid][pMechFuel]);
				UpdateDynamic3DTextLabelText(pTemp[scdplayerid][pMechText],0xFFFFFFFF,mes);
			
                VehicleInfo[vehicleid][vFuel] += float(fuel);
				DeletePVar(playerid, "MechanicPrice");
				DeletePVar(playerid, "MechanicFuel");
				GiveMoney(playerid, -price);
				GiveMoney(scdplayerid, price);
				temp_fill_sender[playerid] = INVALID_PLAYER_ID;
			}
			else SCM(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться в транспорте.");
		}
		if(temp_repair_sender[playerid] != INVALID_PLAYER_ID)
		{
			if(GetPlayerState(playerid) == 2)
			{
				new scdplayerid = temp_repair_sender[playerid], price = GetPVarInt(playerid, "MechanicPrice");
				new vehicleid = GetPlayerVehicleID(playerid);
				if(GetMoney(playerid) < price)
				{
					SendClientMessage(scdplayerid,-1,!"{FFC800}[Подсказка]{ffffff}У игрока недостаточно денег");
					DeletePVar(playerid, "MechanicPrice");
					DeletePVar(playerid, "MechanicRepair");
					temp_repair_sender[playerid] = INVALID_PLAYER_ID;
					return 1;
				}
				new lstring[144];
				format(lstring, sizeof(lstring), "{7AC71F}[Успешно]{ffffff} Автомеханик {FFC800}%s {ffffff}отремонтировал ваше т/с за {FFC800}%d$.", PN(scdplayerid), price);
				SCM(playerid, COLOR_WHITE, lstring);
				format(lstring, sizeof(lstring), "{7AC71F}[Успешно]{ffffff} Вы отремонтировали т/с {FFC800}%s {ffffff}за {FFC800}%d$.", PN(playerid), price);
				SCM(scdplayerid, COLOR_WHITE, lstring);
    			J_SetVehicleHealth(vehicleid, 1000);
				RepairVehicle(vehicleid);
				DeletePVar(playerid, "MechanicRepair");
				GiveMoney(playerid, -price);
				GiveMoney(scdplayerid, price);
				temp_repair_sender[playerid] = INVALID_PLAYER_ID;
			}
			else SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны находиться в транспорте.");
		}
		if(temp_house_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_house_timer[playerid])
			    return 1;
		
			new
				sellerid = temp_house_seller[playerid]-1,
				price = temp_house_price[playerid],
				houseid = temp_house_id[playerid];

			if(PI[sellerid][pHouseKey] != houseid+1)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Дом был продан в гос. владельцем");
				temp_house_seller[playerid] = INVALID_PLAYER_ID;
				temp_house_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_house_id[playerid] = 0;
				temp_house_price[playerid] = 0;
		        temp_house_timer[playerid] = 0;
				return 1;
			}
			
			if(sellerid == INVALID_PLAYER_ID || !IsPlayerConnected(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Продавец вышел из игры, либо продал дом другому игроку");
				temp_house_seller[playerid] = INVALID_PLAYER_ID;
				temp_house_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_house_id[playerid] = 0;
				temp_house_price[playerid] = 0;
				temp_house_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_house_seller[playerid] = INVALID_PLAYER_ID;
				temp_house_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_house_id[playerid] = 0;
				temp_house_price[playerid] = 0;
				temp_house_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pHouseKey])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть дом");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя уже есть дом");
				temp_house_seller[playerid] = INVALID_PLAYER_ID;
				temp_house_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_house_id[playerid] = 0;
				temp_house_price[playerid] = 0;
				temp_house_timer[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, sellerid) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_house_seller[playerid] = INVALID_PLAYER_ID;
				temp_house_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_house_id[playerid] = 0;
				temp_house_price[playerid] = 0;
				temp_house_timer[playerid] = 0;
				return 1;
			}
            PI[playerid][pHouseKey] = HouseInfo[houseid][hID];
            PI[sellerid][pHouseKey] = 0;
            

            
            if(HouseInfo[houseid][hDays] == 0)
          	 	HouseInfo[houseid][hDays] += 1;

     		HouseInfo[houseid][hSafeCode] = 0;
     		HouseInfo[houseid][hSkin][0] = 0;
     		HouseInfo[houseid][hSkin][1] = 0;
     		HouseInfo[houseid][hSkin][2] = 0;
     		HouseInfo[houseid][hSkin][3] = 0;
     		HouseInfo[houseid][hMoney] = 0;
     		
    		UpdateHouseDress(houseid);
     		UpdateHouseGun(houseid);
     		
     		for(new i;i<8;i++)
     		{
     		    HouseInfo[houseid][hGun][i] = 0;
				DestroyDynamicObject(HouseGunObject[houseid][i]);
				HouseGunObject[houseid][i] = 0;
			}
     		    
 		    if(IsValidDynamicObject(HintDressObject[houseid][0]))
		    	DestroyDynamicObject(HintDressObject[houseid][0]);
		    if(IsValidDynamicObject(HintDressObject[houseid][1]))
		    	DestroyDynamicObject(HintDressObject[houseid][1]);
		    if(IsValidDynamicObject(HintDressObject[houseid][2]))
		    	DestroyDynamicObject(HintDressObject[houseid][2]);

			if(IsValidDynamic3DTextLabel(HintStoreText[houseid]))
			    DestroyDynamic3DTextLabel(HintStoreText[houseid]);

			if(IsValidDynamic3DTextLabel(HintSafeText[houseid]))
			    DestroyDynamic3DTextLabel(HintSafeText[houseid]);

			if(IsValidDynamicObject(HintStoreObject[houseid]))
			    DestroyDynamicObject(HintStoreObject[houseid]);

			if(IsValidDynamicObject(HintSafeObject[houseid]))
			    DestroyDynamicObject(HintSafeObject[houseid]);
			    
       	 	SetString(HouseInfo[houseid][hOwner], PN(playerid));
       	 	UpdateHouse(houseid);
            SendClientMessage(playerid, COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Поздравляем, Вы купили дом! Не забывайте проплачивать его в банке!");
            SendClientMessage(sellerid, COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Дом продан");
            
            new
                improve;
                
			for(new i; i < 4; i++)
			{
			    if(HouseInfo[houseid][hImprove][i])
			    {
					HouseInfo[houseid][hImprove][i] = 0;
					improve += HouseImprovePrice[i];
				}
			}
			
			if(improve)
			    GiveMoney(sellerid, improve/100*80, "возврат денег за улучшения"), SendClientMessage(sellerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF} Вам было возвращено 80 процентов от купленных улучшений");
				

            PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
            UpdatePlayerData(playerid, "HouseKey", PI[playerid][pHouseKey]);
            UpdatePlayerData(sellerid, "HouseKey", PI[sellerid][pHouseKey]);
            //SaveAccount(playerid);

 			GiveMoney(playerid, -price, "покупка дома у игрока");
 			GiveMoney(sellerid, price, "продажа дома игроку");


			
			temp_house_seller[playerid] = INVALID_PLAYER_ID;
			temp_house_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_house_id[playerid] = 0;
			temp_house_price[playerid] = 0;
			temp_house_timer[playerid] = 0;

		}
		if(temp_car_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_car_timer[playerid])
			    return 1;
			    
			new
				sellerid = temp_car_seller[playerid]-1,
				price = temp_car_price[playerid],
				carid = temp_car_id[playerid],
				number = temp_car_number[playerid];

			if(PI[sellerid][pCars] != carid)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Т/C было продано в гос. владельцем");
				temp_car_seller[playerid] =
				temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_car_id[playerid] =
				temp_car_number[playerid] =
				temp_car_price[playerid] =
				temp_car_timer[playerid] = 0;
				return 1;
			}
			if(!PI[playerid][pHouseKey])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет дома");
				temp_car_seller[playerid] =
				temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_car_id[playerid] =
				temp_car_number[playerid] =
				temp_car_price[playerid] =
				temp_car_timer[playerid] = 0;
				return 1;
			}
			if(sellerid == INVALID_PLAYER_ID || !IsPlayerConnected(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Продавец вышел из игры, либо продал Т/C другому игроку");
				temp_car_seller[playerid] =
				temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_car_id[playerid] =
				temp_car_number[playerid] =
				temp_car_price[playerid] =
				temp_car_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_car_seller[playerid] =
				temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_car_id[playerid] =
				temp_car_number[playerid] =
				temp_car_price[playerid] =
				temp_car_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pCars])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже Т/C");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя уже есть Т/C");
				temp_car_seller[playerid] =
				temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_car_id[playerid] =
				temp_car_number[playerid] =
				temp_car_price[playerid] =
				temp_car_timer[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, sellerid) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_car_seller[playerid] =
				temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_car_id[playerid] =
				temp_car_number[playerid] =
				temp_car_price[playerid] =
				temp_car_timer[playerid] = 0;
				return 1;
			}
			new
			    query_car[120],
				houseid = PI[playerid][pHouseKey]-1;
			    
			if(number)
				format(query_car, sizeof query_car, "UPDATE `cars` SET `cOwnerID` = '%d' WHERE `cID` = '%d'", PI[playerid][pID], PI[sellerid][pCars]);
				
			else
  				format(query_car, sizeof query_car, "UPDATE `cars` SET `cOwnerID` = '%d', `cNumber` = '-' WHERE `cID` = '%d'", PI[playerid][pID], PI[sellerid][pCars]);
  				
			mysql_tquery(mysql, query_car);
			
			CarInfo[GetCarSlot(carid)][cOwnerID] = PI[playerid][pID];
			
    		foreach(new i : Player)
           	{
		    	if(PI[i][pVehicleKey] == PI[sellerid][pCars])
		    	{
	        	    PI[i][pVehicleKey] = 0;
	            	UpdatePlayerData(i, "VehicleKey", 0);
				}
			}

            PI[playerid][pCars] = PI[sellerid][pCars];
            UpdatePlayerData(playerid, "Cars", PI[playerid][pCars]);
            PI[sellerid][pCars] = 0;
            UpdatePlayerData(sellerid, "Cars", PI[sellerid][pCars]);
            
            if(number)
            {
				PI[playerid][pPTS] = 1;
	            UpdatePlayerData(playerid, "PTS", PI[playerid][pPTS]);
            }
            else
            {
				PI[playerid][pPTS] = 0;
	            UpdatePlayerData(playerid, "PTS", PI[playerid][pPTS]);
            }
            
            PI[sellerid][pPTS] = 0;
            UpdatePlayerData(sellerid, "PTS", PI[sellerid][pPTS]);
            temp_car_num_get[playerid] =
            temp_car_num_get[sellerid] = 0;
            
           
            
			new
			    modelid = CarInfo[GetCarSlot(carid)][cModelID];
			    
			SendClientMessage(playerid, COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Поздравляем, Вы купили т/c.");
			SendClientMessage(sellerid, COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Ваш автомобиль продан");
            PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
            //SaveAccount(playerid);
            if(!number)
				SetString(CarInfo[GetCarSlot(carid)][cNumber], "-"), SetString(CarInfo[GetCarSlot(carid)][cDate], "00.00.0000");

			else
			{
				new year, month, day;
				getdate(year, month, day);
				new date[20];
				format(date, sizeof date, "%02d.%02d.%02d", day, month, year);
	          	SetString(CarInfo[GetCarSlot(carid)][cDate], date);
			}
			DestroyVehicle(CarInfo[GetCarSlot(carid)][cVehID]);

          	

			new
				vehicleid = CreateVehicle(Transport[modelid][trModel], HouseInfo[houseid][hPark_X], HouseInfo[houseid][hPark_Y], HouseInfo[houseid][hPark_Z], HouseInfo[houseid][hPark_R], CarInfo[GetCarSlot(carid)][cColor_1], CarInfo[GetCarSlot(carid)][cColor_2], -1);

            VehicleInfo[vehicleid][vLock] = 1;
			CarInfo[GetCarSlot(carid)][cVehID] = vehicleid;
			
			SetVehicleNumberPlate(vehicleid, CarInfo[GetCarSlot(carid)][cNumber]);
			
			if(CarInfo[GetCarSlot(carid)][cHealth] < 300.0)
				CarInfo[GetCarSlot(carid)][cHealth] = 300.0;
				
            CarInfo[GetCarSlot(carid)][cFuel] = 15.0;
			J_SetVehicleHealth(vehicleid, CarInfo[GetCarSlot(carid)][cHealth]);
			SetVehicleNumberPlate(vehicleid, CarInfo[GetCarSlot(carid)][cNumber]);
				
 			GiveMoney(playerid, -price, "покупка тс у игрока");
 			GiveMoney(sellerid, price, "продажа тс игроку");
				
			for(new tn; tn < 14; tn++)
				if(CarInfo[GetCarSlot(carid)][cTuning][tn] != 0) AddVehicleComponent(vehicleid, CarInfo[GetCarSlot(carid)][cTuning][tn]);

			ChangeVehiclePaintjob(vehicleid, CarInfo[GetCarSlot(carid)][cPaintJob]);

			temp_car_seller[playerid] =
			temp_car_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_car_id[playerid] =
			temp_car_number[playerid] =
			temp_car_price[playerid] =
			temp_car_timer[playerid] = 0;
		}
		if(temp_biz_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_biz_timer[playerid])
	 			return 1;

			new
				sellerid = temp_biz_seller[playerid]-1,
				price = temp_biz_price[playerid],
				bizid = temp_biz_id[playerid];


			if(PI[sellerid][pBizKey] != bizid+1)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Бизнес был продан в гос. владельцем");
				temp_biz_seller[playerid] = INVALID_PLAYER_ID;
				temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_biz_id[playerid] = 0;
				temp_biz_price[playerid] = 0;
				temp_biz_timer[playerid] = 0;
				return 1;
			}
			if(sellerid == INVALID_PLAYER_ID || !IsPlayerConnected(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Продавец вышел из игры, либо продал бизнес другому игроку");
				temp_biz_seller[playerid] = INVALID_PLAYER_ID;
				temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_biz_id[playerid] = 0;
				temp_biz_price[playerid] = 0;
				temp_biz_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_biz_seller[playerid] = INVALID_PLAYER_ID;
				temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_biz_id[playerid] = 0;
				temp_biz_price[playerid] = 0;
				temp_biz_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pBizKey])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть бизнес");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя уже есть бизнес");
				temp_biz_seller[playerid] = INVALID_PLAYER_ID;
				temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_biz_id[playerid] = 0;
				temp_biz_price[playerid] = 0;
				temp_biz_timer[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, sellerid) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_biz_seller[playerid] = INVALID_PLAYER_ID;
				temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_biz_id[playerid] = 0;
				temp_biz_price[playerid] = 0;
				temp_biz_timer[playerid] = 0;
				return 1;
			}
			if(!IsPlayerInRangeOfPoint(playerid, 50.0, BizInfo[bizid][bEnter_X], BizInfo[bizid][bEnter_Y], BizInfo[bizid][bEnter_Z]))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от бизнеса");
				temp_biz_seller[playerid] = INVALID_PLAYER_ID;
				temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_biz_id[playerid] = 0;
				temp_biz_price[playerid] = 0;
				temp_biz_timer[playerid] = 0;
				return 1;
			}
			
            PI[playerid][pBizKey] = BizInfo[bizid][bID];
            PI[sellerid][pBizKey] = 0;

            if(BizInfo[bizid][bDays] == 0)
          	 	BizInfo[bizid][bDays] += 1;

       	 	SetString(BizInfo[bizid][bOwner], PN(playerid));
       	 	UpdateBiz(bizid,1);
			SendClientMessage(playerid,COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Поздравляем, Вы купили бизнес. Не забывайте оплачивать его, иначе его продадут государству!");
			SendClientMessage(playerid,COLOR_WHITE,"{FFC800}[Подсказка] {FFFFFF}/business {ffffff}- панель управления бизнесом");
			
            SendClientMessage(sellerid, COLOR_GREEN, !"Бизнес продан");
            PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
            UpdatePlayerData(playerid, "BizKey", PI[playerid][pBizKey]);
            UpdatePlayerData(sellerid, "BizKey", PI[sellerid][pBizKey]);
            //SaveAccount(playerid);

 			GiveMoney(playerid, -price, "покупка бизнеса у игрока");
 			GiveMoney(sellerid, price, "продажа бизнеса игроку");
 			
			temp_biz_seller[playerid] = INVALID_PLAYER_ID;
			temp_biz_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_biz_id[playerid] = 0;
			temp_biz_price[playerid] = 0;
			temp_biz_timer[playerid] = 0;
		}
		if(temp_fill_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_fill_timer[playerid])
	 			return 1;

			new
				sellerid = temp_fill_seller[playerid]-1,
				price = temp_fill_price[playerid],
				bizid = temp_fill_id[playerid];

			if(PI[sellerid][pBizKey] != bizid+1+1000)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}АЗС было продано в гос. владельцем");
				temp_fill_seller[playerid] = INVALID_PLAYER_ID;
				temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_fill_id[playerid] = 0;
				temp_fill_price[playerid] = 0;
				temp_fill_timer[playerid] = 0;
				return 1;
			}
			if(sellerid == INVALID_PLAYER_ID || !IsPlayerConnected(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Продавец вышел из игры, либо продал АЗС другому игроку");
				temp_fill_seller[playerid] = INVALID_PLAYER_ID;
				temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_fill_id[playerid] = 0;
				temp_fill_price[playerid] = 0;
				temp_fill_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_fill_seller[playerid] = INVALID_PLAYER_ID;
				temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_fill_id[playerid] = 0;
				temp_fill_price[playerid] = 0;
				temp_fill_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pBizKey])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть бизнес");
				SendClientMessage(sellerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя уже есть бизнес");
				temp_fill_seller[playerid] = INVALID_PLAYER_ID;
				temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_fill_id[playerid] = 0;
				temp_fill_price[playerid] = 0;
				temp_fill_timer[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, sellerid) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_fill_seller[playerid] = INVALID_PLAYER_ID;
				temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_fill_id[playerid] = 0;
				temp_fill_price[playerid] = 0;
				temp_fill_timer[playerid] = 0;
				return 1;
			}
			if(!IsPlayerInRangeOfPoint(playerid, 50.0, gFillingBuy[bizid][0], gFillingBuy[bizid][1], gFillingBuy[bizid][2]))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от бизнеса");
				temp_fill_seller[playerid] = INVALID_PLAYER_ID;
				temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
				temp_fill_id[playerid] = 0;
				temp_fill_price[playerid] = 0;
				temp_fill_timer[playerid] = 0;
				return 1;
			}
			
            PI[playerid][pBizKey] = bizid+1000+1;
            PI[sellerid][pBizKey] = 0;

            if(gFillings[bizid][fillingDay] == 0)
          	 	gFillings[bizid][fillingDay] += 1;

       	 	SetString(gFillings[bizid][fillingOwner], PN(playerid));
 
			SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем вы купили АЗС.");
			SendClientMessage(playerid, COLOR_GREEN, !"Меню управления АЗС {FFFFFF}\"/filling\"");

			UpdateFillingText(bizid);
			
            SendClientMessage(sellerid, COLOR_GREEN, !"АЗС продано");
            PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
            UpdatePlayerData(playerid, "BizKey", PI[playerid][pBizKey]);
            UpdatePlayerData(sellerid, "BizKey", PI[sellerid][pBizKey]);
            //SaveAccount(playerid);

 			GiveMoney(playerid, -price, "покупка АЗС у игрока");
 			GiveMoney(sellerid, price, "продажа АЗС игроку");

			temp_fill_seller[playerid] = INVALID_PLAYER_ID;
			temp_fill_buyer[sellerid] = INVALID_PLAYER_ID;
			temp_fill_id[playerid] = 0;
			temp_fill_price[playerid] = 0;
			temp_fill_timer[playerid] = 0;
		}
		if(temp_sim_seller[playerid] != INVALID_PLAYER_ID)
		{
			if(!temp_sim_timer[playerid])
			    return 1;
			
			new
				sellerid = temp_sim_seller[playerid]-1,
				frmt_buysim[150];
				
			if(GetPlayerDistanceToPlayer(playerid, sellerid) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(sellerid))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				return 1;
			}
			
			format(frmt_buysim, sizeof frmt_buysim, "{FFFFFF}Вы хотите купить SIM-карту {FFFF00}%d{FFFFFF} у {FF0000}%s{FFFFFF} за {C6EEDE}$%d{FFFFFF}?", temp_sim_num[playerid], PN(sellerid), temp_sim_price[playerid]);
			ShowPlayerDialogEx(playerid, 828, DIALOG_STYLE_MSGBOX, !"Покупка SIM-карты", frmt_buysim, !"Купить", !"Отмена");
		}
		if(temp_pass_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_pass_sender[playerid] - 1;


			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_pass_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_pass_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_pass_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_pass_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	frmt_action[MAX_PLAYER_NAME + 40 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s достал паспорт и показал(а) его %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);
			
			ShowPass(receiver, playerid);

            temp_pass_receiver[receiver] = INVALID_PLAYER_ID;
            temp_pass_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_pts_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_pts_sender[playerid] - 1;


			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_pts_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_pts_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_pts_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_pts_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}

       		new
			   	frmt_action[MAX_PLAYER_NAME + 40 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s достал ПТС и показал(а) его %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			ShowPTS(receiver, playerid);

            temp_pts_receiver[receiver] = INVALID_PLAYER_ID;
            temp_pts_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_wedding_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_wedding_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(!IsPlayerInRangeOfPoint(playerid, 20.0, -1989.8998,1117.9297,54.4688))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы слишком далеко от церкви");
	            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pMerrit] > 0)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже состоите в браке");
	            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[receiver][pMerrit] > 0)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок уже состоит в браке");
	            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pSex] == PI[receiver][pSex] || PI[receiver][pSex] == 2)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок сменил пол");
	            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pSex] == 1)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы сменили пол");
	            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pWedding])
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Превышен лимит свадеб за день");
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	weddingstr[128];

			format(weddingstr, sizeof weddingstr, "%s и %s вступили в брак", PN(receiver), PN(playerid));
			SendClientMessageToAll(0xCC33FFFF, weddingstr);
			
			format(weddingstr, sizeof weddingstr, "Вы вступили в брак с %s", PN(receiver));
			SendClientMessage(playerid, COLOR_GREEN, weddingstr);
			
			format(weddingstr, sizeof weddingstr, "Ваше предожение вступить в брак принято. Ваша супруга: %s", PN(playerid));
			SendClientMessage(receiver, COLOR_GREEN, weddingstr);

			PI[playerid][pMerrit] = PI[receiver][pID];
			UpdatePlayerData(playerid, "Merrit", PI[playerid][pMerrit]);
			PI[receiver][pMerrit] = PI[playerid][pID];
            UpdatePlayerData(receiver, "Merrit", PI[receiver][pMerrit]);
			
			PI[playerid][pWedding] = 1;
			UpdatePlayerData(playerid, "Wedding", PI[playerid][pWedding]);
			PI[receiver][pWedding] = 1;
			UpdatePlayerData(receiver, "Wedding", PI[receiver][pWedding]);
			
            temp_wedding_receiver[receiver] = INVALID_PLAYER_ID;
            temp_wedding_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_lic_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_lic_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_lic_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_lic_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_lic_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_lic_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	frmt_action[30 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s показал(а) лицензии %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			ShowLic(receiver, playerid);

            temp_lic_receiver[receiver] = INVALID_PLAYER_ID;
            temp_lic_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_skill_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_skill_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_skill_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_skill_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_skill_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_skill_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	frmt_action[45 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s показал(а) выписку из тира %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			ShowSkill(receiver, playerid);

            temp_skill_receiver[receiver] = INVALID_PLAYER_ID;
            temp_skill_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_sellmed_sender[playerid] != INVALID_PLAYER_ID)
		{
		    if(!temp_sellmed_timer[playerid])
		        return 1;

		    new
		        receiver = temp_sellmed_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_sellmed_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_sellmed_sender[playerid] = INVALID_PLAYER_ID;
	            temp_sellmed_timer[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < 500)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
	            temp_sellmed_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_sellmed_sender[playerid] = INVALID_PLAYER_ID;
	            temp_sellmed_timer[playerid] = 0;
			    return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_sellmed_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_sellmed_sender[playerid] = INVALID_PLAYER_ID;
	            temp_sellmed_timer[playerid] = 0;
				return 1;
			}
			
       		new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s продал(а) медицинскую карту %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			GiveMoney(playerid, -500, "покупка мед");
			GiveMoney(receiver, 250, "продажа мед");
			OrgInfo[0][oMoney] += 250;
			
			SendClientMessage(playerid, COLOR_GREEN, !"Вы получили медицинскую карту. Используйте /med, чтобы показать её");
			SendClientMessage(receiver, COLOR_GREEN, !"Медицинская карта продана");
			PI[playerid][pMedCard] = 1;
			UpdatePlayerData(playerid, "MedCard", PI[playerid][pMedCard]);

			if(PI[playerid][pQuest] == 10 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
			}
			
            temp_sellmed_receiver[receiver] = INVALID_PLAYER_ID;
            temp_sellmed_sender[playerid] = INVALID_PLAYER_ID;
            temp_sellmed_timer[playerid] = 0;
		}
		if(temp_med_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_med_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_med_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_med_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_med_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_med_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s показал(а) медицинскую карту %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			ShowMed(receiver, playerid);

            temp_med_receiver[receiver] = INVALID_PLAYER_ID;
            temp_med_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_vacation_sender[playerid] != INVALID_PLAYER_ID)
		{
		    if(!temp_vacation_timer[playerid])
		        return 1;
		        
		    new
		        receiver = temp_vacation_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
	            temp_vacation_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_vacation_sender[playerid] = INVALID_PLAYER_ID;
				temp_vacation_days[playerid] = 0;
				temp_vacation_timer[playerid] = 0;
				return 1;
			}
			if(!PI[playerid][pFraction] || !PI[receiver][pFraction])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Не найдена фракция");
	            temp_vacation_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_vacation_sender[playerid] = INVALID_PLAYER_ID;
				temp_vacation_days[playerid] = 0;
				temp_vacation_timer[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
	            temp_vacation_receiver[receiver] = INVALID_PLAYER_ID;
	            temp_vacation_sender[playerid] = INVALID_PLAYER_ID;
				temp_vacation_days[playerid] = 0;
				temp_vacation_timer[playerid] = 0;
				return 1;
			}
			
			PI[playerid][pv_Fraction] = PI[playerid][pFraction];
			PI[playerid][pv_Subfraction] = PI[playerid][pSubfraction];
			PI[playerid][pv_Rank] = PI[playerid][pRank];
			PI[playerid][pv_FWarns] = PI[playerid][pFWarns];
			PI[playerid][pv_Days] = temp_vacation_days[playerid];
			PI[playerid][pv_FractionSkin] = PI[playerid][pFractionSkin];
			
			new mes[128];
			format(mes, sizeof mes, "%s отправил сотрудника %s в отпуск на %d %s", PN(receiver), PN(playerid), temp_vacation_days[playerid], Declension_GetDays(temp_vacation_days[playerid]));

    		foreach(new i : Player)
			{
				if(PI[i][pFraction] == PI[playerid][pFraction])
				{
					if(PI[playerid][pSubfraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
					{
						SendClientMessage(i, COLOR_YELLOW, mes);
						continue;
					}
					if(!PI[playerid][pSubfraction])
			 		{
						SendClientMessage(i, COLOR_YELLOW, mes);
					    continue;
					}
				}
			}
			
			PI[playerid][pFraction] = 0;
			PI[playerid][pSubfraction] = 0;
			PI[playerid][pRank] = 0;
			PI[playerid][pFWarns] = 0;
			PI[playerid][pFractionSkin] = 0;
			PI[playerid][pDivision] = 0;

			new
				query_fraction_save[300];

			format(query_fraction_save, sizeof query_fraction_save, "UPDATE `accounts` SET `v_Fraction` = '%d', `v_Subfraction` = '%d', `v_Rank` = '%d', `v_FWarns` = '%d', `v_Days` = '%d', `v_FractionSkin` = '%d', `Fraction` = '0', `Subfraction` = '0', `Rank` = '0', `FWarns` = '0', `FractionSkin` = '0', `Division` = '0' WHERE `ID` = '%d'",
																	PI[playerid][pv_Fraction], PI[playerid][pv_Subfraction], PI[playerid][pv_Rank], PI[playerid][pv_FWarns], PI[playerid][pv_Days], PI[playerid][pv_FractionSkin], PI[playerid][pID]);

			mysql_tquery(mysql, query_fraction_save, "", "");
			
			SetPlayerHealth(playerid, 0);
			resetgun(playerid);

			SetPlayerColor(playerid, 0xFFFFFF11);
			SetPlayerSkin(playerid, PI[playerid][pSkin]);


            temp_vacation_receiver[receiver] = INVALID_PLAYER_ID;
            temp_vacation_sender[playerid] = INVALID_PLAYER_ID;
			temp_vacation_days[playerid] = 0;
			temp_vacation_timer[playerid] = 0;
			
			
		}
		if(temp_vac_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_vac_sender[playerid] - 1,
				vacid = temp_vac_id[playerid]-1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Продавец вышел из игры");
			    temp_vac_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_vac_sender[playerid] = INVALID_PLAYER_ID;
			    temp_vac_id[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < 1500)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
			    temp_vac_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_vac_sender[playerid] = INVALID_PLAYER_ID;
			    temp_vac_id[playerid] = 0;
			    return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
			    temp_vac_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_vac_sender[playerid] = INVALID_PLAYER_ID;
			    temp_vac_id[playerid] = 0;
				return 1;
			}
			
       		new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME],
				query_vac[150];

			format(frmt_action, sizeof frmt_action, "%s провел(а) вакцинацию %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			
			PI[playerid][pVaccine][vacid] = 30;

			format(query_vac, sizeof query_vac, "UPDATE `accounts` SET `Vaccine[%d]` = '%d' WHERE `ID` = '%d'", vacid, PI[playerid][pVaccine][vacid], PI[playerid][pID]);
			mysql_tquery(mysql, query_vac);

			GiveMoney(playerid, -1500, "вакцина");
			GiveMoney(receiver, 750, "вакцина");
			OrgInfo[0][oMoney] += 750;
			
			new
				mes[128];

			format(mes, sizeof mes, "Вы прошли вакцинацию от болезни %s", gDiseaseName[vacid]);
			SendClientMessage(playerid, COLOR_GREEN, mes);

		    temp_vac_receiver[receiver] = INVALID_PLAYER_ID;
		    temp_vac_sender[playerid] = INVALID_PLAYER_ID;
		    temp_vac_id[playerid] = 0;
		}
		if(temp_setsex_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_setsex_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Врач вышел из игры");
			    temp_setsex_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_setsex_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
			    temp_setsex_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_setsex_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s сделал(а) операцию %s по смене пола", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			if(PI[playerid][pSex] == 1)
				PI[playerid][pSex] = 2;

			else if(PI[playerid][pSex] == 2)
				PI[playerid][pSex] = 1;
				
				
			UpdatePlayerData(playerid, "Sex", PI[playerid][pSex]);
			
			new
				mes[128];

			format(mes, sizeof mes, "Вы успешно сменили пол на %s", PI[playerid][pSex] == 1 ? ("Мужской") : ("Женский"));
			SendClientMessage(playerid, COLOR_GREEN, mes);
			
			
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
			
			
			
		    temp_setsex_receiver[receiver] = INVALID_PLAYER_ID;
		    temp_setsex_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_sellgun_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellgun_sender[playerid] - 1,
				price = temp_sellgun_price[playerid];

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел");
				temp_sellgun_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellgun_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellgun_id[playerid] = 0;
				temp_sellgun_ammo[playerid] = 0;
				temp_sellgun_price[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_sellgun_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellgun_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellgun_id[playerid] = 0;
				temp_sellgun_ammo[playerid] = 0;
				temp_sellgun_price[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_sellgun_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellgun_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellgun_id[playerid] = 0;
				temp_sellgun_ammo[playerid] = 0;
				temp_sellgun_price[playerid] = 0;
				return 1;
			}
			new
				slot = GetWeaponSlot(temp_sellgun_id[playerid]),
				weapon, ammo;
				
			GetPlayerWeaponData(receiver, slot, weapon, ammo);
			if(weapon != temp_sellgun_id[playerid] || ammo < temp_sellgun_ammo[playerid])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У продавца закончилось оружие");
				temp_sellgun_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellgun_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellgun_id[playerid] = 0;
				temp_sellgun_ammo[playerid] = 0;
				temp_sellgun_price[playerid] = 0;
				return 1;
			}

			new remain = ammo - temp_sellgun_ammo[playerid];
			if(remain > ammo)
			{
				temp_sellgun_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellgun_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellgun_id[playerid] = 0;
				temp_sellgun_ammo[playerid] = 0;
				temp_sellgun_price[playerid] = 0;
				return 1;
			}
			_GiveGun(playerid, temp_sellgun_id[playerid], temp_sellgun_ammo[playerid]);
			SetPlayerAmmo(receiver, temp_sellgun_id[playerid], 0);
			_GiveGun(receiver, temp_sellgun_id[playerid], remain);
			
			GiveMoney(playerid, -price, "покупка гана");
			GiveMoney(receiver, price, "продажа гана");
			
			new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s продал(а) оружие %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);
			
			temp_sellgun_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellgun_sender[playerid] = INVALID_PLAYER_ID;
			temp_sellgun_id[playerid] = 0;
			temp_sellgun_ammo[playerid] = 0;
			temp_sellgun_price[playerid] = 0;
			
		}
		if(temp_selldrugs_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_selldrugs_sender[playerid] - 1,
				price = temp_selldrugs_price[playerid];

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел");
				temp_selldrugs_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selldrugs_sender[playerid] = INVALID_PLAYER_ID;
				temp_selldrugs_value[playerid] = 0;
				temp_selldrugs_price[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_selldrugs_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selldrugs_sender[playerid] = INVALID_PLAYER_ID;
				temp_selldrugs_value[playerid] = 0;
				temp_selldrugs_price[playerid] = 0;
				return 1;
			}
			if(PI[receiver][pDrugs] < temp_selldrugs_value[playerid])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У продавца закончились наркотики");
				temp_selldrugs_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selldrugs_sender[playerid] = INVALID_PLAYER_ID;
				temp_selldrugs_value[playerid] = 0;
				temp_selldrugs_price[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pDrugs]+temp_selldrugs_value[playerid] > 500)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете пронести больше чем 500 гр.");
				temp_selldrugs_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selldrugs_sender[playerid] = INVALID_PLAYER_ID;
				temp_selldrugs_value[playerid] = 0;
				temp_selldrugs_price[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_selldrugs_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selldrugs_sender[playerid] = INVALID_PLAYER_ID;
				temp_selldrugs_value[playerid] = 0;
				temp_selldrugs_price[playerid] = 0;
				return 1;
			}
			PI[playerid][pDrugs] += temp_selldrugs_value[playerid];
			PI[receiver][pDrugs] -= temp_selldrugs_value[playerid];
			UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);
			UpdatePlayerData(receiver, "Drugs", PI[receiver][pDrugs]);
			
			GiveMoney(playerid, -price, "покупка drugs");
			GiveMoney(receiver, price, "продажа drugs");

			new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s продал(а) наркотики %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);


			temp_selldrugs_receiver[receiver] = INVALID_PLAYER_ID;
			temp_selldrugs_sender[playerid] = INVALID_PLAYER_ID;
			temp_selldrugs_value[playerid] = 0;
			temp_selldrugs_price[playerid] = 0;
		}
		if(temp_sellzone_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellzone_sender[playerid] - 1,
				id = temp_sellzone_id[playerid]-1,
				price = temp_sellzone_price[playerid];
				
			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
			}
            if(IsCapture == 1)
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент проходит захват территории");
   				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент проходит захват территории");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
            }
			if(GZMZ[id][gGang] != PI[receiver][pFraction])
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Территория не найдена");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
			}
			if(!IsAGang(receiver) || PI[receiver][pRank] != 10)
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Лидер покинул банду");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
			}
			if(!IsAGang(playerid) || PI[playerid][pRank] != 10)
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы покинули банду");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
			}
			if(PI[receiver][pSellZones] > 2)
			{
   				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы продали больше чем две территории за день");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellzone_id[playerid] = 0;
				temp_sellzone_price[playerid] = 0;
				return 1;
			}
			GiveMoney(playerid, -price, "покупка территории");
			GiveMoney(receiver, price, "продажа территории");

			new
			    frmt_sellzone[80];
			    
			format(frmt_sellzone, sizeof frmt_sellzone, "Банда %s купила территорию у банды %s", gFractionName[PI[playerid][pFraction]-1], gFractionName[PI[receiver][pFraction]-1]);
			
			FractionChat(F_GROVE, 0xFF2400FF, frmt_sellzone);
			FractionChat(F_BALLAS, 0xFF2400FF, frmt_sellzone);
			FractionChat(F_AZTEC, 0xFF2400FF, frmt_sellzone);
			FractionChat(F_RIFA, 0xFF2400FF, frmt_sellzone);
			FractionChat(F_VAGOS, 0xFF2400FF, frmt_sellzone);


			new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s продал(а) территория %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);
			
			PI[receiver][pSellZones]++;
			UpdatePlayerData(receiver, "SellZones", PI[receiver][pSellZones]);
			
            GZMZ[id][gGang] = PI[playerid][pFraction];
			GangZoneHideForAll(GZMZ[id][gID]);
			GangZoneShowForAll(GZMZ[id][gID], GetGangZoneColor(id));
			SaveGZ(id);
            UpdateTextGang();
				
			temp_sellzone_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellzone_sender[playerid] = INVALID_PLAYER_ID;
			temp_sellzone_id[playerid] = 0;
			temp_sellzone_price[playerid] = 0;
		}
		if(temp_sellmbiz_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellmbiz_sender[playerid] - 1,
				id = temp_sellmbiz_id[playerid]-1,
				price = temp_sellmbiz_price[playerid];

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
			}
            if(IsBizWar == 1)
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент проходит захват бизнеса");
   				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент проходит захват бизнеса");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
            }
			if(BizInfo[id][bKrasher] != PI[receiver][pFraction])
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Бизнес не найден");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
			}
			if(!IsAMafia(receiver) || PI[receiver][pRank] != 10)
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Лидер покинул банду");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
			}
			if(!IsAMafia(playerid) || PI[playerid][pRank] != 10)
			{
   				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы покинули банду");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
			}
			if(PI[receiver][pSellZones] > 2)
			{
   				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы продали больше чем два контроля за день");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
				temp_sellmbiz_id[playerid] = 0;
				temp_sellmbiz_price[playerid] = 0;
				return 1;
			}
			GiveMoney(playerid, -price, "покупка контроля биз");
			GiveMoney(receiver, price, "продажа контроля биз");

			new
			    frmt_sellmbiz[80];

			format(frmt_sellmbiz, sizeof frmt_sellmbiz, "Мафия %s купила контроль над бизнесом у мафии %s", gFractionName[PI[playerid][pFraction]-1], gFractionName[PI[receiver][pFraction]-1]);

			FractionChat(12, 0xFF2400FF, frmt_sellmbiz);
			FractionChat(13, 0xFF2400FF, frmt_sellmbiz);
			FractionChat(14, 0xFF2400FF, frmt_sellmbiz);


			new
			   	frmt_action[55 + MAX_PLAYER_NAME + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s продал(а) контроль %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			PI[receiver][pSellZones]++;
			UpdatePlayerData(receiver, "SellZones", PI[receiver][pSellZones]);

            BizInfo[id][bKrasher] = PI[playerid][pFraction];
			UpdateBiz(id,1);
            UpdateTextMafia();

			temp_sellmbiz_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellmbiz_sender[playerid] = INVALID_PLAYER_ID;
			temp_sellmbiz_id[playerid] = 0;
			temp_sellmbiz_price[playerid] = 0;
		}
		if(temp_ud_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_ud_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
				temp_ud_receiver[receiver] = INVALID_PLAYER_ID;
				temp_ud_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_ud_receiver[receiver] = INVALID_PLAYER_ID;
				temp_ud_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
       		new
			   	frmt_action[MAX_PLAYER_NAME + 40 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s показал(а) своё удостоверние %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			ShowUdost(receiver, playerid);

			temp_ud_receiver[receiver] = INVALID_PLAYER_ID;
			temp_ud_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_flyer_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_flyer_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
				temp_flyer_receiver[receiver] = INVALID_PLAYER_ID;
				temp_flyer_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(!PI[receiver][pFlyers] && !PI[receiver][pFlyersCount])
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Листовки не найдены");
				temp_flyer_receiver[receiver] = INVALID_PLAYER_ID;
				temp_flyer_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_flyer_receiver[receiver] = INVALID_PLAYER_ID;
				temp_flyer_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			new
				query_flyer_info[350],
				frmt_flyer_info[400],
				name[24],
				text[128];

			format(query_flyer_info, sizeof query_flyer_info, "SELECT `name`, `text` FROM `flyers` WHERE `checked` = 1 AND `subfraction` = %d AND `id` = %d", PI[receiver][pSubfraction], PI[receiver][pFlyers]);
			new Cache:result = mysql_query(mysql, query_flyer_info);
			new flyers = cache_get_row_count(mysql);

			if(flyers == 0)
			  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Листовка не найдена");

            cache_get_row(0, 0, name, mysql);
			cache_get_row(0, 1, text, mysql);

			format(frmt_flyer_info, sizeof frmt_flyer_info, "{FFFFFF}Название: {4EAAFF}%s\n\n{FFFFFF}Текст: {4EAAFF}%s", name, text);

			ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Рекламный флаер", frmt_flyer_info, !"Закрыть", !"");
			cache_delete(result, mysql);

			if(PI[receiver][pFlyersCount]-1 > 0)
			{
				PI[receiver][pFlyersCount]--;
			 	UpdatePlayerData(receiver, "FlyersCount", PI[receiver][pFlyersCount]);
			}
			
			else if(PI[receiver][pFlyersCount]-1 <= 0)
			{
			    PI[receiver][pFlyers] = 0;
				UpdatePlayerData(receiver, "Flyers", PI[receiver][pFlyers]);
				PI[receiver][pFlyersCount] = 0;
				UpdatePlayerData(receiver, "FlyersCount", PI[receiver][pFlyersCount]);
			}
       		new
			   	frmt_action[MAX_PLAYER_NAME + 40 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s передал(а) рекламный флаер %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

		    new
		        frmt_flyer_create[110];

			format(frmt_flyer_create, sizeof frmt_flyer_create, "{FFC800}[Подсказка] {FFFFFF}Вы передали листовку %s. Осталось: %d штук", PN(playerid), PI[receiver][pFlyersCount]);
		    SendClientMessage(receiver, COLOR_WHITE, frmt_flyer_create);


			temp_flyer_receiver[receiver] = INVALID_PLAYER_ID;
			temp_flyer_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_selllic_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_selllic_sender[playerid] - 1;

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
				temp_selllic_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selllic_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pGunLic] == YES_LICENSE)
			{
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть лицензия");
				temp_selllic_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selllic_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_selllic_receiver[receiver] = INVALID_PLAYER_ID;
				temp_selllic_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pMoney] < 30000)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_selllic_sender[receiver] = INVALID_PLAYER_ID;
				temp_selllic_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	frmt_action[MAX_PLAYER_NAME + 60 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s продал(а) лицензию на оружие %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);
			
			PI[playerid][pGunLic] = YES_LICENSE;
			UpdatePlayerData(playerid, "GunLic", PI[playerid][pGunLic]);

            GiveMoney(receiver, 4500, "продажа лицензии");
			GiveMoney(playerid, -30000, "покупка лицензии");

			SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем, Вы приобрели лицензию на оружие");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFCC00}/lic [ID игрока]{FFFFFF}, для показа лицензий другому игроку");

			if(PI[playerid][pQuest] == 11 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
			}
			
			temp_selllic_receiver[receiver] = INVALID_PLAYER_ID;
			temp_selllic_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_free_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_free_sender[playerid] - 1,
				price = temp_free_price[playerid];

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
				temp_free_receiver[receiver] = INVALID_PLAYER_ID;
				temp_free_sender[playerid] = INVALID_PLAYER_ID;
				temp_free_price[playerid] = 0;
				return 1;
			}
			if(!PI[playerid][pJailTime])
			{
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не в тюрьме");
				temp_free_receiver[receiver] = INVALID_PLAYER_ID;
				temp_free_sender[playerid] = INVALID_PLAYER_ID;
				temp_free_price[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_free_receiver[receiver] = INVALID_PLAYER_ID;
				temp_free_sender[playerid] = INVALID_PLAYER_ID;
				temp_free_price[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_free_receiver[receiver] = INVALID_PLAYER_ID;
				temp_free_sender[playerid] = INVALID_PLAYER_ID;
				temp_free_price[playerid] = 0;
				return 1;
			}

       		new
			   	frmt_action[MAX_PLAYER_NAME + 60 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s выпустил(а) из тюрьмы %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			new salary = (price/100) * 25;
			
            GiveMoney(receiver, salary, "выход из тюрьмы");
			GiveMoney(playerid, -price, "выход из тюрьмы");
			
			PI[playerid][pJailTime] = 0;
			UpdatePlayerData(playerid, "JailTime", PI[playerid][pJailTime]);

            PI[playerid][pJailAdmin] = 0;
            UpdatePlayerData(playerid, "JailAdmin", PI[playerid][pJailAdmin]);

			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы были освобождены");

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

			temp_free_receiver[receiver] = INVALID_PLAYER_ID;
			temp_free_sender[playerid] = INVALID_PLAYER_ID;
			temp_free_price[playerid] = 0;
		}
		if(temp_sellcard_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_sellcard_sender[playerid] - 1;
		        
			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
				temp_sellcard_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellcard_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pCard])
			{
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У игрока уже есть карта рекордсмена");
				temp_sellcard_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellcard_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_sellcard_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellcard_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			if(PI[playerid][pMoney] < 50000)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_sellcard_receiver[receiver] = INVALID_PLAYER_ID;
				temp_sellcard_sender[playerid] = INVALID_PLAYER_ID;
				return 1;
			}
			
       		new
			   	frmt_action[MAX_PLAYER_NAME + 60 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s продал(а) билет рекордсмена %s", PN(receiver), PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);
			
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Теперь все ваши рекорды записываются! У Вас появился шанс попасть на Аллею Славы!");


            GiveMoney(receiver, 5000, "продажа билета рекордсмена");
			GiveMoney(playerid, -50000, "покупка билета рекордсмена");
			
			PI[playerid][pCard] = 1;
			UpdatePlayerData(playerid, "Card", PI[playerid][pCard]);

			temp_sellcard_receiver[receiver] = INVALID_PLAYER_ID;
			temp_sellcard_sender[playerid] = INVALID_PLAYER_ID;
		}
		if(temp_charity_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_charity_sender[playerid] - 1,
				price = temp_charity_price[playerid];

			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
				temp_charity_receiver[receiver] = INVALID_PLAYER_ID;
				temp_charity_sender[playerid] = INVALID_PLAYER_ID;
				temp_charity_price[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
				temp_charity_receiver[receiver] = INVALID_PLAYER_ID;
				temp_charity_sender[playerid] = INVALID_PLAYER_ID;
				temp_charity_price[playerid] = 0;
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				SendClientMessage(receiver, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У покупателя недостаточно денег");
				temp_charity_receiver[receiver] = INVALID_PLAYER_ID;
				temp_charity_sender[playerid] = INVALID_PLAYER_ID;
				temp_charity_price[playerid] = 0;
				return 1;
			}

       		new
			   	frmt_action[MAX_PLAYER_NAME + 60 + MAX_PLAYER_NAME];

			format(frmt_action, sizeof frmt_action, "%s совершил(а) пожертвование", PN(playerid));
			ProxDetector(25, receiver, frmt_action, COLOR_ME);

			new
			    frmt_charity_message[130];

			format(frmt_charity_message, sizeof frmt_charity_message, "{FFC800}[Подсказка] {FFFFFF}Вы пожертвовали %d$ в фонд штата!", price);
			SendClientMessage(playerid, COLOR_WHITE, frmt_charity_message);

			GiveMoney(playerid, -price, "пожертвование");
			OrgInfo[9][oMoney] += price;
			PI[playerid][pCharity] += price;
			UpdatePlayerData(playerid, "Charity", PI[playerid][pCharity]);
			
			
			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);
			
			if(price >= 5000000)
			{

			    format(frmt_charity_message, sizeof frmt_charity_message, "%s{FF182D} пожертвовал в фонд штата {FFFFFF}%d$", PN(playerid), price);
			    SendClientMessageToAll(0xFFFFFFFF, frmt_charity_message);
			    SendClientMessageToAll(COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Совершить пожертвование вы можете в любой Мэрии");
			}
			
			temp_charity_receiver[receiver] = INVALID_PLAYER_ID;
			temp_charity_sender[playerid] = INVALID_PLAYER_ID;
			temp_charity_price[playerid] = 0;
		}
		if(temp_finvite_sender[playerid] != INVALID_PLAYER_ID)
		{
		    new
		        receiver = temp_finvite_sender[playerid] - 1,
				id = temp_finvite_id[playerid];
				
			if(receiver == INVALID_PLAYER_ID || !IsPlayerConnected(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок вышел из игры");
			    temp_finvite_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_finvite_sender[playerid] = INVALID_PLAYER_ID;
			    temp_finvite_id[playerid] = 0;
				return 1;
			}
			if(GetPlayerDistanceToPlayer(playerid, receiver) > 10.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(receiver))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
			    temp_finvite_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_finvite_sender[playerid] = INVALID_PLAYER_ID;
			    temp_finvite_id[playerid] = 0;
				return 1;
			}
			if(PI[receiver][pFamily] != id)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Семья не найдена");
			    temp_finvite_receiver[receiver] = INVALID_PLAYER_ID;
			    temp_finvite_sender[playerid] = INVALID_PLAYER_ID;
			    temp_finvite_id[playerid] = 0;
				return 1;
			}


			PI[playerid][pFamily] = id;
			UpdatePlayerData(playerid, "Family", PI[playerid][pFamily]);

			new
				frmt_family_chat[180];

			format(frmt_family_chat, sizeof frmt_family_chat, "{%s}[%s]{FFCC99} %s[%d] вступил(а) в семью", gFamilyColor[gFamily[id-1][fColor]], gFamily[id-1][fName], PN(playerid), playerid);

    		foreach(new i : Player)
			{
				if(IsPlayerConnected(i) && PI[i][pFamily] == id)
					SendClientMessage(i, 0xFFCC99FF, frmt_family_chat);
			}


			new
				query_family_save[170];

			format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `Members` = `Members`+1 WHERE `ID` = '%d'", id);
	        mysql_tquery(mysql, query_family_save);

			gFamily[id-1][fMembers]++;
			gFamily[id-1][fOnline]++;
					
		    temp_finvite_receiver[receiver] = INVALID_PLAYER_ID;
		    temp_finvite_sender[playerid] = INVALID_PLAYER_ID;
		    temp_finvite_id[playerid] = 0;
		}
	}


 	if(newkeys & KEY_WALK && !IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	{
		if(IsAtBankomat(playerid,2.0))
			return ShowPlayerDialogEx(playerid, 893, DIALOG_STYLE_LIST, !"Банкомат", !"{FF7319}1.{FFFFFF} Узнать баланс счета\n{FF7319}2.{FFFFFF} Снять деньги\n{FF7319}3.{FFFFFF} Положить деньги\n{FF7319}4.{FFFFFF} Пополнить баланс телефона\n{FF7319}5.{FFFFFF} Управление кассой бизнеса", !"Принять", !"Отмена");

	    if(HouseEntered[playerid] != 0)
	    {
	        new i = HouseEntered[playerid]-1;

	        if(HouseInfo[i][hImprove][0])
	        {
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
	        }
	    }
	    
	    if(GetBarrierID(playerid) == 40)
	    {
	        if(GetPVarInt(playerid, "open_time") > gettime())
				return 1;

			if(PI[playerid][pFraction] != 11)
			    return 1;

            SetPVarInt(playerid, "doortext", false);
            DeletePVar(playerid, "open_time");
			OpenBarrier(GetBarrierID(playerid));

            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

            SetPVarInt(playerid, "open_time", gettime()+13);
		}
	    if(GetBarrierID(playerid) == 41 || GetBarrierID(playerid) == 43 || GetBarrierID(playerid) == 45 || GetBarrierID(playerid) == 47)
	    {
	        if(GetPVarInt(playerid, "open_time") > gettime())
				return 1;

			if(PI[playerid][pFraction] != 7 && (PI[playerid][pSubfraction] != 1 || PI[playerid][pRank] != 11))
			    return 1;

            SetPVarInt(playerid, "doortext", false);
            DeletePVar(playerid, "open_time");
			OpenBarrier(GetBarrierID(playerid));

            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

            SetPVarInt(playerid, "open_time", gettime()+13);
		}
	    if(GetBarrierID(playerid) == 44)
	    {
	        if(GetPVarInt(playerid, "open_time") > gettime())
				return 1;

			if(PI[playerid][pFraction] != 7 && (PI[playerid][pSubfraction] != 2 || PI[playerid][pRank] != 11))
			    return 1;

            SetPVarInt(playerid, "doortext", false);
            DeletePVar(playerid, "open_time");
			OpenBarrier(GetBarrierID(playerid));

            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

            SetPVarInt(playerid, "open_time", gettime()+13);
		}
	    if(GetBarrierID(playerid) == 49)
	    {
	        if(GetPVarInt(playerid, "open_time") > gettime())
				return 1;

			if(PI[playerid][pFraction] != 8 && (PI[playerid][pSubfraction] != 3 || PI[playerid][pRank] != 11))
			    return 1;

            SetPVarInt(playerid, "doortext", false);
            DeletePVar(playerid, "open_time");
			OpenBarrier(GetBarrierID(playerid));

            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

            SetPVarInt(playerid, "open_time", gettime()+13);
		}
	    if(GetBarrierID(playerid) == 50 || GetBarrierID(playerid) == 51)
	    {
	        if(GetPVarInt(playerid, "open_time") > gettime())
				return 1;

			if(PI[playerid][pFraction] != 8 && (PI[playerid][pSubfraction] != 2 || PI[playerid][pRank] != 11))
			    return 1;

            SetPVarInt(playerid, "doortext", false);
            DeletePVar(playerid, "open_time");
			OpenBarrier(GetBarrierID(playerid));

            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

            SetPVarInt(playerid, "open_time", gettime()+13);
		}
	}
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(((newkeys & (KEY_FIRE)) == (KEY_FIRE)) && ((oldkeys & (KEY_FIRE)) != (KEY_FIRE)))
		{
			callcmd::lights(playerid);
			return true;
		}
		if(((newkeys & (KEY_ACTION)) == (KEY_ACTION)) && ((oldkeys & (KEY_ACTION)) != (KEY_ACTION)))
		{
			callcmd::engine(playerid);
			return true;
    	}
    	
    	if(PRESSED(KEY_CROUCH))
		{
		    if(IsPlayerInDynamicArea(playerid,arTruckLoadOne) || IsPlayerInDynamicArea(playerid,arTruckLoadTwo) || IsPlayerInDynamicArea(playerid,arTruckLoadThree))
			{
			    if(GetPVarInt(playerid,"mesto") == 1) return SendClientMessage(playerid,COLOR_WHITE,!"{FF2222}[Ошибка] {FFFFFF}Вы уже находитесь в очереди");
				new loadid = 0;
				if(IsPlayerInDynamicArea(playerid,arTruckLoadTwo)) loadid = 1;
				else if(IsPlayerInDynamicArea(playerid,arTruckLoadThree)) loadid = 3;
				if(PI[playerid][pJob] == JOB_TRUCKER && pTemp[playerid][pTruckID] != INVALID_VEHICLE_ID && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && pTemp[playerid][pTruckWagonID] == INVALID_VEHICLE_ID)
				{
					new vehicleid = GetPlayerVehicleID(playerid);
					new model = GetVehicleModel(vehicleid);
					switch(model)
					{
						case 403,514,515:
						{
							new maxcount, level, string[128];
							level = GetPlayerTruckLevel(playerid);
							maxcount = (level == 1) ? (TRUCK_LOAD_1) : (level == 2) ? (TRUCK_LOAD_2) : (TRUCK_LOAD_3);
							SetPVarInt(playerid,"maxamount",maxcount);
							SetPVarInt(playerid,"loadid",loadid);
							switch(loadid)
							{
								case 0:
								{
									format(string, sizeof(string), "{FFFFFF}Сколько киллограмм вы хотите загрузить?\nМаксимальная грузоподьемность {FF2222}%d", maxcount);
									ShowPlayerDialogEx(playerid, 5557, 1, "Загрузка", string, "Принять", "Отмена");
								}
								case 1:
								{
									format(string, sizeof(string), "{FFFFFF}Сколько киллограмм вы хотите загрузить?\nМаксимальная грузоподьемность {FF2222}%d", maxcount);
									ShowPlayerDialogEx(playerid, 5557, 1, "Загрузка", string, "Принять", "Отмена");
								}
								case 3:
								{
									format(string, sizeof(string), "{FFFFFF}Сколько киллограмм вы хотите загрузить?\nМаксимальная грузоподьемность {FF2222}%d", maxcount);
									ShowPlayerDialogEx(playerid, 5557, 1, "Загрузка", string, "Принять", "Отмена");
								}
							}
						}
					}
				}
			}
			for(new i; i < 2; i++)
			{
				if(IsPlayerInDynamicArea(playerid,arTruckUnload))
				{
					if(PI[playerid][pJob] == JOB_TRUCKER && pTemp[playerid][pTruckID] != INVALID_VEHICLE_ID && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && pTemp[playerid][pTruckWagonID] != INVALID_VEHICLE_ID)
					{
						new vehicleid = GetPlayerVehicleID(playerid);
						if(!IsTrailerAttachedToVehicle(vehicleid))
						{
							SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы потеряли прицеп. Заказ аннулирован");
							if(IsValidDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]))
							{
								DestroyDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]);
								pTemp[playerid][pTruckWagonText] = Text3D:INVALID_3DTEXT_ID;
							}
							if(pTemp[playerid][pTruckWagonID] != INVALID_VEHICLE_ID) DestroyVehicle(pTemp[playerid][pTruckWagonID]);
							pTemp[playerid][pTruckWagonID] = INVALID_VEHICLE_ID;
							pTemp[playerid][pTruckWagonTime] = 0;
							pTemp[playerid][pTruckWeight] = 0;
							pTemp[playerid][pTruckLoadID] = 0;
							return 1;
						}
						new amount = floatround(pTemp[playerid][pTruckWeight]);
						new loadid = GetPVarInt(playerid,"loadid");
						
						new price;
						if(loadid == 0) price = (k1+1)*amount;
						if(loadid == 1) price = (k2+1)*amount;
						if(loadid == 3) price = (k3+1)*amount;
						
						new mes[128];
						format(mes,sizeof(mes),"{FFC800}[Подсказка] {FFFFFF}%d кг груза было продано за {63BD4E}%d$",amount,price);
						SendClientMessage(playerid,COLOR_WHITE,mes);
						GiveMoney(playerid,price,"Получил за привезённый груз");
						
						new mess[25];
						format(mess,sizeof mess,"~g~ +%d$",price);
						GameTextForPlayer(playerid,mess,2100,1);
					
						PI[playerid][pTruckSkill] +=  1;
      					UpdatePlayerData(playerid,"TruckSkill",PI[playerid][pTruckSkill]);
						
						if(IsValidDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]))
						{
							DestroyDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]);
							pTemp[playerid][pTruckWagonText] = Text3D:INVALID_3DTEXT_ID;
						}
						DetachTrailerFromVehicle(vehicleid);
						DestroyVehicle(pTemp[playerid][pTruckWagonID]);
						pTemp[playerid][pTruckWagonID] = INVALID_VEHICLE_ID;
						pTemp[playerid][pTruckWagonTime] = 0;
						pTemp[playerid][pTruckWeight] = 0;
						pTemp[playerid][pTruckLoadID] = 0;
						SetPVarInt(playerid,"informed",0);
						DeletePVar(playerid,"loadid");
					}
				}
			}
		    if(GetBarrierID(playerid) == 40)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;

				if(PI[playerid][pFraction] != 11)
				    return 1;

	            SetPVarInt(playerid, "doortext", false);
	            DeletePVar(playerid, "open_time");
				OpenBarrier(GetBarrierID(playerid));

	            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

	            SetPVarInt(playerid, "open_time", gettime()+13);
            }
		    if(GetBarrierID(playerid) == 41 || GetBarrierID(playerid) == 43 || GetBarrierID(playerid) == 45 || GetBarrierID(playerid) == 47)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;

				if(PI[playerid][pFraction] != 7 && (PI[playerid][pSubfraction] != 1 || PI[playerid][pRank] != 11))
				    return 1;

	            SetPVarInt(playerid, "doortext", false);
	            DeletePVar(playerid, "open_time");
				OpenBarrier(GetBarrierID(playerid));

	            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

	            SetPVarInt(playerid, "open_time", gettime()+13);
			}
		    if(GetBarrierID(playerid) == 44)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;

				if(PI[playerid][pFraction] != 7 && (PI[playerid][pSubfraction] != 2 || PI[playerid][pRank] != 11))
				    return 1;

	            SetPVarInt(playerid, "doortext", false);
	            DeletePVar(playerid, "open_time");
				OpenBarrier(GetBarrierID(playerid));

	            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

	            SetPVarInt(playerid, "open_time", gettime()+13);
			}
		    if(GetBarrierID(playerid) == 49)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;

				if(PI[playerid][pFraction] != 8 && (PI[playerid][pSubfraction] != 3 || PI[playerid][pRank] != 11))
				    return 1;

	            SetPVarInt(playerid, "doortext", false);
	            DeletePVar(playerid, "open_time");
				OpenBarrier(GetBarrierID(playerid));

	            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

	            SetPVarInt(playerid, "open_time", gettime()+13);
			}
		    if(GetBarrierID(playerid) == 50 || GetBarrierID(playerid) == 51)
		    {
		        if(GetPVarInt(playerid, "open_time") > gettime())
					return 1;

				if(PI[playerid][pFraction] != 8 && (PI[playerid][pSubfraction] != 2 || PI[playerid][pRank] != 11))
				    return 1;

	            SetPVarInt(playerid, "doortext", false);
	            DeletePVar(playerid, "open_time");
				OpenBarrier(GetBarrierID(playerid));

	            SetTimerEx("@__CloseBarrier",13000, false, "d", GetBarrierID(playerid));

	            SetPVarInt(playerid, "open_time", gettime()+13);
			}
		}
	}
	if(!IsPlayerInAnyVehicle(playerid))
	{
	    if(PRESSED(KEY_NO))
	    {
	        /*for(new t; t < sizeof(TrashCanArea); t++)
	        {
	            if(IsPlayerInDynamicArea(playerid, TrashCanArea[t]))
	            {
	                if(PI[playerid][pLevel] > 3)
	                    return 1;

					if(PI[playerid][pTrashCheck][t])
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже рылись в этом мусорном баке, подойдите к другому!");

					PI[playerid][pTrashCheck][t] = true;

					new
						trashstr[140],
						query_trash[280];
						
					format(trashstr, sizeof trashstr, "%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i", 	PI[playerid][pTrashCheck][0], PI[playerid][pTrashCheck][1], PI[playerid][pTrashCheck][2],
																														PI[playerid][pTrashCheck][3], PI[playerid][pTrashCheck][4], PI[playerid][pTrashCheck][5],
																														PI[playerid][pTrashCheck][6], PI[playerid][pTrashCheck][7], PI[playerid][pTrashCheck][8],
																														PI[playerid][pTrashCheck][9], PI[playerid][pTrashCheck][10], PI[playerid][pTrashCheck][11],
																														PI[playerid][pTrashCheck][12], PI[playerid][pTrashCheck][13], PI[playerid][pTrashCheck][14],
																														PI[playerid][pTrashCheck][15], PI[playerid][pTrashCheck][16], PI[playerid][pTrashCheck][17],
																														PI[playerid][pTrashCheck][18], PI[playerid][pTrashCheck][19], PI[playerid][pTrashCheck][20]);

					format(query_trash, sizeof query_trash, "UPDATE `accounts` SET `TrashCheck` = '%s' WHERE `ID` = '%d'", trashstr, PI[playerid][pID]);
					mysql_tquery(mysql, query_trash);
					
                    J_ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 1, 0, 0, 1, 0, 1);
                    SetPVarInt(playerid, "trash", gettime()+2);
					SetCameraBehindPlayer(playerid);
                    temp_search_timer[playerid] = SetTimerEx("@__SearchTrash", 1000, true, "i", playerid);
				}
			}
			if(IsPlayerInDynamicArea(playerid, TrashArea))
			{
	            if(PI[playerid][pLevel] > 3)
	                return 1;

	            new
	                frmt_text_dialog[450],
					amount;

	            amount = 	PI[playerid][pTrashWallet]*120
							+ PI[playerid][pTrashBottle]*90
							+ PI[playerid][pTrashBank]*75
							+ PI[playerid][pTrashPaper]*60
						 	+ PI[playerid][pTrashBung]*55
						 	+ PI[playerid][pTrashPhone]*350;

				format(frmt_text_dialog, sizeof frmt_text_dialog, "\n\n{FFFFFF}Собрано мусора:\n\n\
																	Старых бумажников: {00AC77}%d{FFFFFF}\n\
																	Пустых бутылок: {00AC77}%d{FFFFFF}\n\
																	Консервных банок: {00AC77}%d{FFFFFF}\n\
																	Мятых бумаг: {00AC77}%d{FFFFFF}\n", PI[playerid][pTrashWallet], PI[playerid][pTrashBottle], PI[playerid][pTrashBank], PI[playerid][pTrashPaper]);

				format(frmt_text_dialog, sizeof frmt_text_dialog, "%sПробок из под бутылок: {00AC77}%d{FFFFFF}\n\
																	Поломанных телефонов: {00AC77}%d{FFFFFF}\n\n\n\
																	Вы можете продать за {00AC77}$%d\n\n", frmt_text_dialog, PI[playerid][pTrashBung], PI[playerid][pTrashPhone], amount);


				ShowPlayerDialogEx(playerid, 412, DIALOG_STYLE_MSGBOX, !"Пункт приема мусора", frmt_text_dialog, !"Продать", !"Отмена");
			}
   */
	    }
	}
	if(GotoInfo[playerid][gtGoID] == INVALID_PLAYER_ID)
	{
	    if(!IsPlayerInAnyVehicle(playerid))
	    {
			if(newkeys & KEY_SPRINT && newkeys & KEY_JUMP)
			{
				new index = GetPlayerAnimationIndex(playerid);
				if(index == 1224 || index == 1247 || index == 1257 || index == 1249 || index == 1196 || index == 1249)
				{
				    if(timeforcd[playerid] > gettime()) return 1;
					new keys,ud,lr;
					GetPlayerKeys(playerid,keys,ud,lr);
					if(ud != 0 || lr != 0) ClearAnimations(playerid);
					timeforcd[playerid] = 10;
				}
			}
			if(IsPlayerInDynamicArea(playerid, gCasinoArea))
			{
				if(newkeys & KEY_JUMP && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) ClearAnimations(playerid);
			}
			if(PI[playerid][pDisease] == 4 && newkeys & KEY_JUMP && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			{
				ClearAnimations(playerid);
				ApplyAnimation(playerid, "FAT", "IDLE_tired", 3.0, 0, 0, 0, 0, 3000);
			}
			if(PI[playerid][pDisease] == 6 && newkeys & KEY_JUMP && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			{
				ClearAnimations(playerid);
				ApplyAnimation(playerid, "FAT", "IDLE_tired", 3.0, 0, 0, 0, 0, 3000);
			}
		}
	}
	return true;
}
stock EnterBiz(playerid,bizid)
{
    if(!IsNoEnterBiz(bizid))
	{
		if(!BizInfo[bizid][bLock])
		{
		    if(GetPlayerVirtualWorld(playerid)!=0)return 1;
			BizEntered[playerid] = bizid;
			pTemp[playerid][pAntiAir] += 4;
			//SetPlayerInterior(playerid,BizInfo[bizid][bInt]);
			SetPlayerVirtualWorld(playerid,(bizid+100));
			//SetPlayerPos(playerid,BizInfo[bizid][bExit_X],BizInfo[bizid][bExit_Y],BizInfo[bizid][bExit_Z]);
			NoEnterPickup[playerid] =2;
	    	f_TogglePlayerControllable(playerid,false);
	    	SetCameraBehindPlayer(playerid);
			BizInfo[bizid][bVisit] ++;
		}
		else SCM(playerid,COLOR_LIGHTRED,"[Ошибка] {FFFFFF}Дверь закрыта, невозможно зайти");
	}
	return true;
}
public ClearAnims(playerid)
{
	return ApplyAnimation(playerid, "BD_FIRE", "BD_Fire1", 4.1, 0, 0, 0, 0, 1, 1);
}

stock IsNoEnterBiz(bizid)
{
	//if(BizInfo[bizid][bExit_X] == 0.0 && BizInfo[bizid][bExit_Y] == 0.0 && BizInfo[bizid][bExit_Z] == 0.0) return true;
	return false;
}
public OnRconLoginAttempt(ip[], password[], success)
{

    return 1;
}
stock CheatMessage(playerid)
{
	SCM(playerid,COLOR_LIGHTRED,"[Информация] {FFFFFF}Вы были кикнуты по подозрению в читерстве");
	ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, 0, "Вы были кикнуты","{FFFFFF}Вы были кикнуты по подозрению в читерстве","Ок","");
	return true;
}
public OnPlayerUpdate(playerid)
{
 	if(IsPlayerConnected(playerid))
	{
	    if(IsPlayerLogged[playerid] == true)
	    {
	        pl_afk_time[playerid] = -1;
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				new vehid = GetPlayerVehicleID(playerid);
				if(PI[playerid][pJob] == JOB_TRUCKER && IsTrailerAttachedToVehicle(vehid))
				{
					new trailerid = GetVehicleTrailer(vehid);
					if(pTemp[playerid][pTruckWagonID] != trailerid)
					{
						DetachTrailerFromVehicle(vehid);
						new Float:x, Float:y, Float:z;
						GetVehiclePos(vehid,x,y,z);
						y -= 1.0;
						J_SetVehiclePos(vehid,x,y,z);
					}
					else if(pTemp[playerid][pTruckWeight] < GetPVarInt(playerid,"truckamount"))
					{
						DetachTrailerFromVehicle(vehid);
						SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Прицеп еще не загружен полностью");
						new Float:x, Float:y, Float:z;
						GetVehiclePos(vehid,x,y,z);
						y -= 1.0;
						J_SetVehiclePos(vehid,x,y,z);
					}
					else if(!GetPVarInt(playerid,"informed"))
					{
						pTemp[playerid][pTruckWagonTime] = 60;
						SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}У вас есть 1 минута чтобы покинуть место загрузки иначе заказ аннулируется");
						SetPVarInt(playerid,"informed",1);
					}
				}
			}
		}
	}
   	if(!IsPlayerNPC(playerid))
    {
	    if(IsPlayerConnected(playerid)&& IsPlayerLogged[playerid])
	    {
			if(temp_tazer_timer[playerid] > 0)
				GoAnim(playerid, "CRACK", "Crckidle2", 4.1, 1, 0, 0, 0, 0, 0);

			//тренировки
			//if(GetPlayerVehicleSpeedZ(playerid)>360)J_Kick(playerid);
            new index = GetPlayerAnimationIndex(playerid);
			if(PI[playerid][pSelectStoreGun])
			{
				new newkeys,ud,lr;
				GetPlayerKeys(playerid,newkeys,ud,lr);
				if (lr > 0)
				{
					new id = PI[playerid][pStoreGun];
					if(id == 7) id = 0;
					else id++;
					new houseid = PI[playerid][pHouseKey]-1;
					new hintid = HouseInfo[houseid][hNumInt]-1;
					for(new i=id;i<8;i++)
					{
						if(HouseInfo[houseid][hGun][i])
						{
							new Float:x, Float:y, Float:z, Float:x2, Float:y2, Float:z2;
							GetPlayerCameraPos(playerid,x,y,z);
							GetGunCameraOffset(HintGun[hintid][i][0], HintGun[hintid][i][1], HintStore[hintid][5],x2,y2);
							z2 = HintGun[hintid][i][2] + 0.4;
							InterpolateCameraPos(playerid,x,y,z,x2,y2,z2,700,CAMERA_MOVE);
							GetPlayerCameraFrontVector(playerid,x2,y2,z2);
							x += x2;
							y += y2;
							z += z2;
							InterpolateCameraLookAt(playerid,x,y,z, HintGun[hintid][i][0], HintGun[hintid][i][1], HintGun[hintid][i][2],700,CAMERA_MOVE);
							PI[playerid][pStoreGun] = i;
							PI[playerid][pSelectStoreGun] = false;
							SetTimerEx("@__SelectStoreGun",1000,false,"i",playerid);
							new gunname[32],mes[48];
							GetWeaponName(GetStoreGunID(i),gunname,32);
							format(mes,48,"~w~%s (~g~%d~w~)",gunname,HouseInfo[houseid][hGun][i]);
							GameTextForPlayer(playerid,mes,100000,3);
							break;
						}
						if(i == 7) i = 0;
					}
				}
				if (lr < 0)
				{
					new id = PI[playerid][pStoreGun];
					if(id == 0) id = 7;
					else id--;
					new houseid = PI[playerid][pHouseKey]-1;
					new hintid = HouseInfo[houseid][hNumInt]-1;
					for(new i=id;i>=0;i--)
					{
						if(HouseInfo[houseid][hGun][i])
						{
							new Float:x, Float:y, Float:z, Float:x2, Float:y2, Float:z2;
							GetPlayerCameraPos(playerid,x,y,z);
							GetGunCameraOffset(HintGun[hintid][i][0],HintGun[hintid][i][1],HintStore[hintid][5],x2,y2);
							z2 = HintGun[hintid][i][2] + 0.4;
							InterpolateCameraPos(playerid,x,y,z,x2,y2,z2,700,CAMERA_MOVE);
							GetPlayerCameraFrontVector(playerid,x2,y2,z2);
							x += x2;
							y += y2;
							z += z2;
							InterpolateCameraLookAt(playerid,x,y,z, HintGun[hintid][i][0], HintGun[hintid][i][1], HintGun[hintid][i][2],700,CAMERA_MOVE);
							PI[playerid][pStoreGun] = i;
							PI[playerid][pSelectStoreGun] = false;
							SetTimerEx("@__SelectStoreGun",1000,false,"i",playerid);
							new gunname[32],mes[48];
							GetWeaponName(GetStoreGunID(i),gunname,32);
							format(mes,48,"~w~%s (~g~%d~w~)",gunname,HouseInfo[houseid][hGun][i]);
							GameTextForPlayer(playerid,mes,100000,3);
							break;
						}
						if(i == 0) i = 7;
					}
				}
			}
		    if(InJob[playerid] == 5 && temp_job_status[playerid] == 2)
			{
				if(index != 1224 && index != 1189 && index != 280 && index != 1184 && index != 1269 && index != 471 && index != 1276 && index != 1283 && index != 1277 && index != 1287 && index != 1275)
				{
					SendClientMessage(playerid, COLOR_GREY, !"Вы уронили щебень");
					new
					    checkpoint = RandomEx(0, 3);

				    TogglePlayerDynamicCP(playerid, gRoadGet[checkpoint], true);
				    RoadGet[playerid] = checkpoint+1;

                    for(new i; i < 3; i++) TogglePlayerDynamicCP(playerid, gRoadCP[i], false);
					temp_job_status[playerid] = 1;

				    RemovePlayerAttachedObjectEx(playerid, 0);
				    RemovePlayerAttachedObjectEx(playerid, 1);
			    }
			}
			
			iNewPlayerAmmo[playerid] = GetPlayerAmmo(playerid);
			if(iNewPlayerAmmo[playerid] != iPlayerAmmo[playerid])
			{
				OnPlayerAmmoChange(playerid, iNewPlayerAmmo[playerid], iPlayerAmmo[playerid]);
				iPlayerAmmo[playerid] = iNewPlayerAmmo[playerid];
			}
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			{
				new newkeys,ud,lr;
				GetPlayerKeys(playerid,newkeys,ud,lr);
				if((ud || lr) && temp_cuffer_sender[playerid] != INVALID_PLAYER_ID && (!(newkeys & KEY_WALK) || newkeys & KEY_SPRINT))
				{
				    if(GetPVarInt(playerid, "naruch") == 0)
				    {
						ApplyAnimation(playerid, "FAT", "IDLE_tired", 3.0, 1, 0, 0, 0, 3000);
						SendClientMessage(playerid, COLOR_GREY, !"Вы не можете бегать в наручниках. Зажмите клавишу ALT и идите шагом");
						SetPVarInt(playerid, "naruch", 1);
					}
					else
						ApplyAnimation(playerid, "FAT", "IDLE_tired", 3.0, 1, 0, 0, 0, 3000);
				}

			}


		}
	}
	new string[55];
	new vehicleid = GetPlayerVehicleID(PI[playerid][pSpectatee]);
	new targer = PI[playerid][pSpectatee];
	if(targer != INVALID_PLAYER_ID && GetPlayerState(targer) == PLAYER_STATE_DRIVER && SpeedVehicle(targer) > 15)
	format(string, sizeof(string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%d~n~~w~Fuel: %.0f",
	SpeedVehicle(targer),VehicleInfo[vehicleid][vFuel]);
	GameTextForPlayer(PI[playerid][pSpeddShow], string, 250, 3);
	return true;
}
stock ShowLoginDialog(playerid)
{
    new str[250],string[350];
	DisableAllRaceCPs(playerid);
	ResetDynamicCPs(playerid);
	strcat(string,"{FFFFFF}Добро пожаловать на {00BFFF}Virtual. Role Play{FFFFFF}\n\n");
    format(str,sizeof(str),"{FFFFFF}Игровой ник: {28910B}%s{FFFFFF}\n",Name(playerid));
	strcat(string,str);
	strcat(string,"Статус аккаунта: {28910B}зарегистрирован\n\n");
	strcat(string,"{FFFFFF}Введите пароль от аккаунта\n");
	format(str,sizeof(str),"{FFFFFF}Попыток для ввода пароля: {00FF00}%d\n\n",gPlayerLogTries[playerid]);
	strcat(string,str);
    ShowPlayerDialogEx(playerid, 2, DIALOG_STYLE_INPUT, !"{74FFA0}Авторизация", string, !"Войти", !"Отмена");
	return true;
}
public OnPlayerStreamIn(playerid, forplayerid)
{
	return true;
}
public OnPlayerStreamOut(playerid, forplayerid)
{
	return true;
}

stock GetPlayerSex(playerid)
{
   return PI[playerid][pSex];
}
public OnVehicleStreamIn(vehicleid, forplayerid)
{
	if(VehicleInfo[vehicleid][vLock]) SetVehicleParamsForPlayer(vehicleid,forplayerid,0,1);
	else SetVehicleParamsForPlayer(vehicleid,forplayerid,0,0);
	GetVehiclePos(vehicleid, VehicleInfo[vehicleid][vX], VehicleInfo[vehicleid][vY], VehicleInfo[vehicleid][vZ]);
	GetVehicleZAngle(vehicleid, VehicleInfo[vehicleid][vA]);
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return true;
}

stock TextFind(text[],findtext[])
{
    return strfind(text, findtext) != -1;
}
stock ShowUpdateSettings(playerid)
{
	new
	    frmt_settings[125];
	    
	format(frmt_settings, sizeof frmt_settings, "{FF7319}1.{FFFFFF} Отображение ников [%s{FFFFFF}]\n{FF7319}2.{FFFFFF} Убрать кейс [%s{FFFFFF}]", PI[playerid][pShowName] ? ("{33AA33}Вкл") : ("{FF0000}Выкл"), PI[playerid][pShowCase] ? ("{33AA33}Вкл") : ("{FF0000}Выкл"));
 	return ShowPlayerDialogEx(playerid, 154, DIALOG_STYLE_LIST, !"Выберите настройку", frmt_settings, !"Изменить", !"Отмена");
}
stock ShowSafety(playerid)
{
	if(0 == PI[playerid][pGoogleAuthCheck])
		ShowPlayerDialogEx(playerid, 789, DIALOG_STYLE_LIST, !"Выберите пункт", "{FF7319}1.{FFFFFF} Изменить код безопасности\n{FF7319}2.{FFFFFF} Изменить пароль\n{FF7319}3.{FFFFFF} Защита Google Authenticator\n{FF7319}4.{FFFFFF} Запрос кода Google Authenticator при каждом входе в игру", !"Выбрать", !"Отмена");

	else
		ShowPlayerDialogEx(playerid, 789, DIALOG_STYLE_LIST, !"Выберите пункт", "{FF7319}1.{FFFFFF} Изменить код безопасности\n{FF7319}2.{FFFFFF} Изменить пароль\n{FF7319}3.{FFFFFF} Защита Google Authenticator\n{FF7319}4.{FFFFFF} Запрос кода Google Authenticator при изменение IP", !"Выбрать", !"Отмена");

	return 1;
}

stock ResetSpawnInfo(playerid, team)
{
	new skin = GetSkinOfPlayer(playerid);
	SetSpawnInfo( playerid, 255, skin, gFractionSpawnC[team][0], gFractionSpawnC[team][1], gFractionSpawnC[team][2], gFractionSpawnC[team][3], 0, 0, 0, 0, 0, 0);
	return true;
}

stock EvenNumber(text[])
{
	return !(strlen(text) % 2);
}
stock ShowGrandRegiserDialog(playerid)
{
	ResetDynamicCPs(playerid);
	DisableAllRaceCPs(playerid);
	new str[100],string[400];
	strcat(string,"{FFFFFF}Добро пожаловать на {00BFFF}Virtual. Role Play{FFFFFF}\n\n");
    format(str,sizeof(str),"{FFFFFF}Игровой ник: {28910B}%s{FFFFFF}\n",Name(playerid));
	strcat(string,str);
	strcat(string,"Статус аккаунта: {FF4500}не зарегистрирован{FFFFFF}\n\n");
	strcat(string,"Для регистрации введите пароль\n");
	strcat(string,"Он будет использоваться для авторизации на сервере\n\n");
	return ShowPlayerDialogEx(playerid,1,DIALOG_STYLE_INPUT,"Пароль",string,"Принять","Выход");
}
stock ShowRegisterDialog(playerid, rstate)
{
	switch(rstate)
	{
	    case 1: ShowGrandRegiserDialog(playerid);
	    case 2: ShowPlayerDialogEx(playerid, 1, DIALOG_STYLE_INPUT, !"Введите почту", !"{FFFFFF}Введите свой E-Mail адрес\n\n{FF0000}Внимание!\nВведите свой существующий E-Mail адрес, поскольку он может Вам пригодится в будущем!", !"Ввод", !"Выход");
	    case 3: ShowPlayerDialogEx(playerid, 1, DIALOG_STYLE_LIST, !"Выберите ваш пол", !"Мужчина\nЖенщина", !"Принять", !"Выход");
		case 4: ShowPlayerDialogEx(playerid, 1, DIALOG_STYLE_LIST, !"Выберите цвет кожи", !"Светлый\nТёмный", !"Принять", !"Выход");
		case 5: ShowPlayerDialogEx(playerid, 1, DIALOG_STYLE_LIST, !"Введите вашу национальность", !"Американец\nРусский\nФранцуз\nМексиканец\nЛатиноамериканец\nИспанец\nПортугалец\nЯпонец\nИтальянец\nАнгличанин", !"Принять", !"Выход");
		case 6: ShowPlayerDialogEx(playerid, 1, DIALOG_STYLE_INPUT, !"Введите ваш возраст", !"{FFFFFF}Введите возраст вашего персонажа:\n\n{EFEFEF}(от 16 до 80 лет)", !"Ввод", !"Выход");
        default: return false;
	}
	return true;
}
forward OnPlayerChangedState(playerid, oldstate, newstate);
public OnPlayerChangedState(playerid, oldstate, newstate)
{
	return true;
}
stock CheckPassword(pass[])
{
	for(new i; i < strlen(pass); i ++)
	{
	    if( (pass[i] >= 'a' && pass[i] <= 'z') ||
		(pass[i] >= 'A' && pass[i] <= 'Z') ||
		(pass[i] >= '0' && pass[i] <= '9')  ) continue;
		else return false;
	}
	return true;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	strreplace(inputtext, '%', '#');

	new inputtextsave[256];
	new correct;
	for(new i; i<strlen(inputtext); i++)
	{
	    switch(inputtext[i])
	    {
	        case 'A'..'Z', 'a'..'z', 'А'..'Я', 'а'..'я', '0'..'9', ' ', '>', '<', '(', ')', '/', '+', '-','_', '?', '!', '.', ',', '@':inputtextsave[i-correct]=inputtext[i];
	        default: correct++;
	    }
	}
	if(strlen(inputtextsave)>0)mysql_escape_string(inputtextsave, inputtextsave, mysql ,256);
	new string[2024], bool:olddialog=true , str1[256];
	if(dialogid != OldDialogID[playerid]) olddialog=false;
	if(!olddialog) format(str1, sizeof(str1), "<!> "); else format(str1, sizeof(str1), "");
	if(!olddialog) return 1;
	OldDialogID[playerid]                       = INVALID_DIALOG_ID;
    PI[playerid][pDialog] = false;
    
	//PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	for(new i;i < strlen(inputtextsave);i ++)
	{
     	if(inputtextsave[i] == '%') inputtextsave[i] = '#';
     	else if(inputtextsave[i] == '{' && inputtextsave[i+7] == '}') strdel(inputtextsave,i,i+8);
	}
	//============API===========
	new inputtextsaveEx[256];
	if(!strlen(inputtextsave)) inputtextsaveEx[0]='|'; else format(inputtextsaveEx, sizeof(inputtextsave), "%s", inputtextsave);
	if(CallRemoteFunction("OnDialogResponseAUX","dddds", playerid, dialogid, response, listitem, inputtextsaveEx))return 1;
	//-----------API------------
	QuestDialog(playerid, dialogid, response);
	//DialogTruck(playerid, dialogid, response, listitem);

	switch(dialogid)
	{
		case 6003:
		{
			if(!response) return true; // 1. Назначит кандидатов\n2. Начать выборы\n3. Закончить выборы
			switch(listitem)
			{
				case 0:
				{
					if(Pick == 0) return SCM(playerid, COLOR_GREY, "В штате нет выборов!");
					new str[90], lstring[512];
					for(new i = 0; i <= 8; i++)
					{
						format(str, sizeof(str), "Слот #%i | %s\n", i, PickName[i]);
						strcat(lstring, str);
					}
					ShowPlayerDialogEx(playerid, 6001, 2, "Кандидаты", lstring, "ОК", "Отмена");
				}
				case 1:
				{
					if(Pick == 1) return SCM(playerid, COLOR_GREY, "В штате уже проходят выборы!");
					SendClientMessageToAll(-1, "Внимание! В штате начались выборы. Проголосовать можно в любой Мэрии Штата");
					Pick = true;
					totalstring[0] = 0;
					format(totalstring, 300, "UPDATE `mayor` SET `pick` = '1', `name` = 'None, None, None, None, None, None, None, None, None', `votes` = '0, 0, 0, 0, 0, 0, 0,0,0'");
					mysql_tquery(mysql, totalstring);
					for(new i = 0; i < 9; i++) { strmid(PickName[i], "None", 0, strlen("None"), MAX_PLAYER_NAME); PickVote[i] = 0; }
				}
				case 2:
				{
					if(Pick == 0) return SCM(playerid, COLOR_GREY, "В штате нет выборов!");
					SendClientMessageToAll(-1, "Внимание! Выборы завершены!");
					ResetPick();
				}
				case 3: GetPick(playerid);
			}
		}
		case 6001:
		{
			if(!response) return true;
			format(string, 90, "{ffffff}Введите имя кандидата на слот номер #%i:", listitem);
			ShowPlayerDialogEx(playerid, 6000, 1, "Кандидат", string, "ОК", "Отмена");
			SetPVarInt(playerid, "NumberPick", listitem);
		}
		case 6000:
		{
			if(!response) { DeletePVar(playerid, "NumberPick"); return true; }
			new c = GetPVarInt(playerid, "NumberPick");
			if(sscanf(inputtext, "s[32]", PickName[c])) { format(string, 168, "{ffffff}Введите имя кандидата на слот номер #%i:", c); return ShowPlayerDialogEx(playerid, 5563, 1, "Кандидат", string, "ОК", "Отмена"); }
            if(!strlen(inputtext) || strlen(inputtext) < 4 || strlen(inputtext) > 32) { format(string, 168, "{ffffff}Введите имя кандидата на слот номер #%i:\n\nОшибка: Длина имени должна быть от 4 до 32 символов.", c); return ShowPlayerDialogEx(playerid, 6000, 1, "Кандидат", string, "ОК", "Отмена"); }
            totalstring[0] = 0;
			format(totalstring, 300, "UPDATE `mayor` SET `Name` = '%s, %s, %s, %s, %s, %s, %s, %s, %s'", PickName[0], PickName[1], PickName[2], PickName[3], PickName[4], PickName[5], PickName[6], PickName[7], PickName[8]);
			mysql_tquery(mysql, totalstring);
			new lstring[100];
			format(lstring, sizeof(lstring), "Игрок %s внесен в список кандидатов.", PickName[c]);
			SCM(playerid, -1, lstring);
			DeletePVar(playerid, "NumberPick");
		}
 		case 5601:
	    {
     		if(!response) return 1;
		    new Float:X, Float:Y, Float:Z, Float:YZ;
			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid, YZ);
			if(floatabs(Z) > 300 || GetPlayerInterior(playerid) != 0 ||  GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Выйдите на улицу для установки объектов");
			switch(listitem)
			{
				case 0: SetPVarInt(playerid,"objectcop", CreateDynamicObject(2121, X, Y, Z+0.2, 0, 0, YZ));
				case 1: SetPVarInt(playerid,"objectcop", CreateDynamicObject(19831, X, Y, Z-1.0, 0, 0, YZ));
				case 2: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1645, X, Y, Z-0.67, 0, 0, YZ));
				case 3: SetPVarInt(playerid,"objectcop", CreateDynamicObject(19632, X, Y, Z-1.0, 0, 0, YZ));
				case 4: SetPVarInt(playerid,"objectcop", CreateDynamicObject(18689, X, Y, Z-2.0, 0, 0, YZ));
				case 5: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1281, X, Y, Z-0.1, 0, 0, YZ));
			}
			if(JobText3D[playerid] == Text3D:INVALID_3DTEXT_ID)
			{
			    new stringer[8];
				format(stringer, sizeof(stringer), "ID: %d", playerid);
				JobText3D[playerid] = CreateDynamic3DTextLabel(stringer, 0xFFFFFFAA, X, Y, Z, 3.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,100.0);
			}
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);
			SendClientMessage(playerid, -1, !"{7AC71F}[Успешно] {ffffff}Вы установили объект");
			return 1;
	    }
	    case 5600:
	    {
     		if(!response) return 1;
		    new Float:X, Float:Y, Float:Z, Float:YZ;
			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid, YZ);
			if(floatabs(Z) > 300 || GetPlayerInterior(playerid) != 0 ||  GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Выйдите на улицу для установки объектов");
			switch(listitem)
			{
				case 0: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1281, X, Y, Z-0.1, 0, 0, YZ));
				case 1: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1810, X, Y, Z-1.0, 0, 0, YZ));
				case 2: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1481, X, Y, Z-0.5, 0, 0, YZ));
				case 3: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1279, X, Y, Z-1.0, 0, 0, YZ));
				case 4: SetPVarInt(playerid,"objectcop", CreateDynamicObject(18689, X, Y, Z-2.0, 0, 0, YZ));
				case 5: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1645, X, Y, Z-0.67, 0, 0, YZ));
			}
			if(JobText3D[playerid] == Text3D:INVALID_3DTEXT_ID)
			{
			    new stringer[8];
				format(stringer, sizeof(stringer), "ID: %d", playerid);
				JobText3D[playerid] = CreateDynamic3DTextLabel(stringer, 0xFFFFFFAA, X, Y, Z, 3.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,100.0);
			}
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);
			SendClientMessage(playerid, -1, !"{7AC71F}[Успешно] {ffffff}Вы установили объект");
			return 1;
	    }
	    case 5599:
	    {
	        if(!response) return 1;
		    new Float:X, Float:Y, Float:Z, Float:YZ;
			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid, YZ);
			if(floatabs(Z) > 300 || GetPlayerInterior(playerid) != 0 ||  GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Выйдите на улицу для установки объектов");
			switch(listitem)
			{
				case 0: SetPVarInt(playerid,"objectcop", CreateDynamicObject(19966, X, Y, Z-1.0, 0, 0, YZ));
				case 1: SetPVarInt(playerid,"objectcop", CreateDynamicObject(19972, X, Y, Z-1.0, 0, 0, YZ));
				case 2: SetPVarInt(playerid,"objectcop", CreateDynamicObject(994, X, Y, Z-1.0, 0, 0, YZ));
				case 3: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1424, X, Y, Z-0.2, 0, 0, YZ));
				case 4: SetPVarInt(playerid,"objectcop", CreateDynamicObject(19944, X, Y, Z-1.0, 0, 0, YZ));
				case 5:
				{
					SetPVarInt(playerid,"objectcop", CreateDynamicObject(2892, X, Y, Z-1.0, 0, 0, YZ));
					Ships[playerid] = CreateDynamicSphere(X, Y, Z, 3.0, -1, -1, -1);
				}
				case 6:
				{
					SetPVarInt(playerid,"objectcop", CreateDynamicObject(2899, X, Y, Z-0.85, 0, 0, YZ));
					Ships[playerid] = CreateDynamicSphere(X, Y, Z, 3.0, -1, -1, -1);
				}
				case 7: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1422, X, Y, Z-0.8, 0, 0, YZ));
				case 8: SetPVarInt(playerid,"objectcop", CreateDynamicObject(1282, X, Y, Z-0.4, 0, 0, YZ));
			}
			if(JobText3D[playerid] == Text3D:INVALID_3DTEXT_ID)
			{
			    new stringer[8];
				format(stringer, sizeof(stringer), "ID: %d", playerid);
				JobText3D[playerid] = CreateDynamic3DTextLabel(stringer, 0xFFFFFFAA, X, Y, Z, 3.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,0,-1,100.0);
			}
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);
			SendClientMessage(playerid, -1, !"{7AC71F}[Успешно] {ffffff}Вы установили объект");
			return 1;
	    }
		case 5572:
		{
			if(!response) { DeletePVar(playerid, "ProductID"); return ProductList(playerid); }
			if(ProductInfo[GetPVarInt(playerid, "ProductID")][pStatus] == 1) { SCM(playerid, COLOR_GREY, "Заказ уже выполняется другим работником!"); DeletePVar(playerid, "ProductID"); return ProductList(playerid); }
			new Float:VPos[3], i = ProductInfo[GetPVarInt(playerid, "ProductID")][pBizid]-1;
			new lstring[144];
			if(GetPlayerState(playerid) !=2) return SCM(playerid, COLOR_GREY, "Вы должны находиться в специальном фургоне, чтобы загрузить продукты.");
			format(lstring, sizeof(lstring), "{7AC71F}[Успешно] {ffffff}Вы приняли заказ от {FFC800}%s.", ProductInfo[GetPVarInt(playerid, "ProductID")][pName]);
			SCM(playerid, -1, lstring);
			DisablePlayerRaceCheckpoint(playerid);
			ProductInfo[GetPVarInt(playerid, "ProductID")][pStatus] = 1;
			GetPlayerPos(playerid, VPos[0], VPos[1], VPos[2]);
			SetPlayerRaceCheckpoint(playerid, 1, BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z], 0.0, 0.0, 0.0, 6);
			format(lstring, sizeof(lstring), "{FFC800}[Подсказка] {FFFFFF}%s отмечен на GPS. Отправляйтесь к бизнесу для доставки продуктов", BizInfo[i][bName]);
			SCM(playerid, -1, lstring);
			format(string, 64, "{ffffff}Продуктов: {FFC800}%i", ProductInfo[GetPVarInt(playerid, "ProductID")][pTill]);
			JobText3D[playerid] = CreateDynamic3DTextLabel(string, -1, 0.0, 0.0, 0.0, 30.0, INVALID_PLAYER_ID, GetPlayerVehicleID(playerid));
			Attach3DTextLabelToVehicle(JobText3D[playerid], GetPlayerVehicleID(playerid), 0, -1.0, 2.6);
			SetPVarInt(playerid, "ProductLoad", 18);
			SetPVarInt(playerid, "ProductInfo", 1);
			SetPVarInt(playerid, "ProductJob", 1);
		}
		case 5570:
		{
			if(!response) return RemovePlayerFromVehicle(playerid);
			if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не в машине");
			if(PI[playerid][pMoney] < 200)
			{
				RemovePlayerFromVehicle(playerid);
				SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Недостаточно денег");
				return true;
			}
			new vehicleid = GetPlayerVehicleID(playerid);
			if(PI[playerid][pJob] == JOB_PRODUCT)
			{
				foreach(new i:Player) if(GetPVarInt(i, "CarProduct") == vehicleid) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот транспорт уже арендован."), RemovePlayerFromVehicle(playerid);
			    SetPVarInt(playerid, "CarProduct", vehicleid);
			    pTemp[playerid][pProductID] = vehicleid;
				SCM(playerid, COLOR_WHITE,!"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь на склад продуктов. Для проверки заказов нажмите {FFC800}Y {ffffff}около него.");
				SetPlayerRaceCheckpoint(playerid, 1, 2785.4731,-2493.4939,13.6531, 0.0, 0.0, 0.0, 5.0);
			}
			GiveMoney(playerid, -200);
			SCM(playerid, COLOR_WHITE, "{7AC71F}[Успешно] {ffffff}Вы арендовали транспортное средство, используйте {FFC800}/end {ffffff}чтобы завершить работу");
			return true;
		}
		case 5571:
		{
			if(!response) return true;
			SetPVarInt(playerid, "ProductID", listitem+1);
			new salary = ProductInfo[GetPVarInt(playerid, "ProductID")][pPrice] / 2;
			if(salary > 5000) salary = 5000;
			format(string, 256, "{ffffff}Номер заказа \t\t#%i %s\n\n{ffffff}Заказал:\t\t{FFC800}%s\n{ffffff}Куда:\t\t\t{FFA07A}%s\n{ffffff}Количество:\t\t{00BFFF}%i продуктов\n{ffffff}Оплата:\t\t{32CD32}%d${ffffff}",
			listitem+1, (!ProductInfo[listitem+1][pStatus]) ? ("{7AC71F}[Доступен]") : ("{FF2222}[Выполняется]"), ProductInfo[listitem+1][pName], BizInfo[ProductInfo[listitem+1][pBizid]-1][bName], ProductInfo[listitem+1][pTill], salary);
			ShowPlayerDialogEx(playerid, 5572, 0, "Заказ", string, "ОК", "Назад");
		}
	    case 5563:
	    {
	    	if(!response) return 1;

			new fractionid = PI[playerid][pFraction]-1;
			if(!PI[playerid][pFraction]) return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");
			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11) return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			switch(listitem)
			{
			    case 0:
			    {
					if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
     					return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

					new
					    frmt_rank_name[700];

					strcat(frmt_rank_name, "{FFFFFF}№. Название\t{FFFFFF}Мужской\t{FFFFFF}Женский\n");


					if(PI[playerid][pFraction] == 10 && !PI[playerid][pSubfraction])
						return ShowPlayerDialogEx(playerid, 915, DIALOG_STYLE_LIST, !"Выберите фракцию", !"{FF7319}1.{FFFFFF} Правительство\n{FF7319}2.{FFFFFF} Мэрии", !"Далее", !"Назад");

					else if(PI[playerid][pFraction] != 10 && !PI[playerid][pSubfraction])
					{
						for(new i; i < gFractionRankCount[PI[playerid][pFraction]-1]; i++)
							format(frmt_rank_name, sizeof frmt_rank_name, "%s{FF7319}%d. {FFFFFF}%s\t{00a768}%d\t{00a768}%d\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i], OrgInfo[fractionid][oMSkins][i], OrgInfo[fractionid][oWSkins][i]);
					}

			        ShowPlayerDialogEx(playerid, 914, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить форму сотрудникам", frmt_rank_name, !"Далее", !"Назад");
			    }
			    case 1:
			    {
					if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
     					return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

					new
					    frmt_car_list[600];

					strcat(frmt_car_list, "{FFFFFF}№. Название\t             {FFFFFF}Минимальный ранг\n");

					for(new i; i < gFractionCarCount[PI[playerid][pFraction]-1]; i++)
						format(frmt_car_list, sizeof frmt_car_list, "%s{FF7319}%d. {FFFFFF}%s (%d)\t             {00A768}%d\n", frmt_car_list, i+1, Transport[gFractionCar[fractionid][i]-400][trName], gFractionCar[fractionid][i], OrgInfo[fractionid][oCarRanks][i]);

			        ShowPlayerDialogEx(playerid, 919, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить автомобили", frmt_car_list, !"Далее", !"Назад");

			    }
				case 2:
				{
					temp_showall_count[playerid] = 0;

					new
					    frmt_showall[2900],
						query_get_list[380],
						nickname[MAX_PLAYER_NAME],
						lastlogin[10],
						status[40],
						rang,
						vac,
						showall_count;

					format(query_get_list, sizeof query_get_list, "SELECT `NickName`, IF(`v_Days`>0, `v_Rank`, `Rank`), `LastLogin`, `v_Days` FROM `accounts` WHERE IF(`v_Days`>0, `v_Fraction` = '%d' AND `v_Subfraction` = '%d', `Fraction` = '%d' AND `Subfraction` = '%d') ORDER BY IF(`v_Days`>0, `v_Rank`, `Rank`) AND `Admin` = '0' ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction], fractionid+1, PI[playerid][pSubfraction]);
					new Cache:result = mysql_query(mysql, query_get_list);
		      		new accounts = cache_get_row_count(mysql);

		      		if(accounts == 0)
					  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции никто не состоит");

					strcat(frmt_showall, "№ Ник игрока\tРанг\tПоследний заход\tСтатус\n");

		      		for(new i; i < accounts; i ++)
		      		{
		      		    if(showall_count > 39 && accounts > 40)
						{
							format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
						    break;
						}
			  			cache_get_row(i, 0, nickname, mysql);
			  			rang = cache_get_row_int(i, 1, mysql);
	                    cache_get_row(i, 2, lastlogin, mysql);
	                    vac = cache_get_row_int(i, 3, mysql);

						if(vac)
						    SetString(status, "{FFA500}[В отпуске]");

						else if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
						    SetString(status, "{00CC44}[В сети]");

						else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
						    SetString(status, "{CD0000}[Не в сети]");

		      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%s\t%s\n", frmt_showall, i+1, nickname, rang, lastlogin, status);
			            temp_showall_count[playerid]++;
			            showall_count++;

		      		}
		      		ShowPlayerDialogEx(playerid, 921, DIALOG_STYLE_TABLIST_HEADERS, !"Список сотрудников", frmt_showall, !"Далее", !"Назад");
		      		cache_delete(result, mysql);
				}
				case 3:
				{
				    if(PI[playerid][pFraction] >= 12 && PI[playerid][pFraction] <= 14)
				    {
						new
							frmt_rank_name[256];

						for(new i;i<10;i++)
							format(frmt_rank_name, sizeof frmt_rank_name, "%s%d.%s\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i]);

						return ShowPlayerDialogEx(playerid, 988, DIALOG_STYLE_LIST, !"Выберите ранг", frmt_rank_name, !"Изменить", !"Отмена");

				    }
				    else if(PI[playerid][pFraction] == 8 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
				    {
						new frmt_division_list[143];

						for(new i; i < 5; i++) format(frmt_division_list, sizeof frmt_division_list, "%s{FF7319}%d.{FFFFFF} %s\n", frmt_division_list, i+1, gDivisionName[i]);

						return ShowPlayerDialogEx(playerid, 758, DIALOG_STYLE_LIST, !"Выберите подразделение", frmt_division_list, !"Выбор", !"Отмена");
					}
					else if(PI[playerid][pFraction] == 9 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
					{
					    new
					        frmt_price_list[120];

						format(frmt_price_list, sizeof frmt_price_list, "{FF7319}1.{FFFFFF} Объявление [{008B00}%d${FFFFFF}]\n{FF7319}2.{FFFFFF} Эфир [{008B00}%d${FFFFFF}]", gAdvertPrice, gEtherPrice);
						return ShowPlayerDialogEx(playerid, 511, DIALOG_STYLE_LIST, !"Регулирование цен", frmt_price_list, !"Изменить", !"Отмена");
					}

					if((PI[playerid][pFraction] == 1 || PI[playerid][pFraction] >= 7 && PI[playerid][pFraction] <= 9) && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
						return 1;

    				temp_showall_count[playerid] = 0;

					new
					    frmt_showall[2900],
						query_get_list[190],
						nickname[MAX_PLAYER_NAME],
						days,
						rang,
						showall_count;

					format(query_get_list, sizeof query_get_list, "SELECT `NickName`, `v_Rank`, `v_Days` FROM `accounts` WHERE `v_Fraction` = '%d' AND `v_Subfraction` = '%d' AND `v_Days` > 0 AND `Admin` = '0' ORDER BY `v_Rank` ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction]);
					new Cache:result = mysql_query(mysql, query_get_list);
		      		new accounts = cache_get_row_count(mysql);

		      		if(accounts == 0)
					  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет сотрудников в отпуске");

					strcat(frmt_showall, "{FFFFFF}№ Ник игрока\t{FFFFFF}Ранг\t{FFFFFF}Осталось в отпуске\n");

		      		for(new i; i < accounts; i ++)
		      		{
		      		    if(showall_count > 39 && accounts > 40)
						{
							format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
						    break;
						}
			  			cache_get_row(i, 0, nickname, mysql);
			  			rang = cache_get_row_int(i, 1, mysql);
                        days = cache_get_row_int(i, 2, mysql);


		      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%d %s\n", frmt_showall, i+1, nickname, rang, days, Declension_GetDays(days));
			            temp_showall_count[playerid]++;
			            showall_count++;

		      		}
		      		ShowPlayerDialogEx(playerid, 930, DIALOG_STYLE_TABLIST_HEADERS, !"Сотрудники в отпуске", frmt_showall, !"Далее", !"Назад");
		      		cache_delete(result, mysql);
				}
				case 4:
				{
	   				if(PI[playerid][pFraction] == 11 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 10)
				    {
						new frmt_division_list[113];

						for(new i; i < 5; i++)
							format(frmt_division_list, sizeof frmt_division_list, "%s{FF7319}%d.{FFFFFF} %s\n", frmt_division_list, i+1, gTagName[i]);

						return ShowPlayerDialogEx(playerid, 778, DIALOG_STYLE_LIST, !"Выберите подразделение", frmt_division_list, !"Выбор", !"Отмена");
					}

					else if(PI[playerid][pFraction] >= 12 && PI[playerid][pFraction] <= 14)
				        callcmd::warehouse(playerid);

				}
				case 5: ShowPlayerDialogEx(playerid, 976, DIALOG_STYLE_LIST, !"Объявление для сотрудников", !"{FF7319}1.{FFFFFF} Создать объявление\n{FF7319}2.{FFFFFF} Удалить объявление\n{FF7319}3.{FFFFFF} Просмотреть объявление", !"Далее", !"Отмена");
				case 6:
				{
				    for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++)
				    {
				        if(VehicleInfo[i][vTeam] != PI[playerid][pFraction] || IsVehicleOccupied(i)) continue;
				        SetVehicleToRespawn(i);
				    }
				    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Авто мафии зареспавнено");
				}
			}
		}
	    case 5562:
	    {
     		if(!response) return 1;
	        switch(listitem)
	        {
	            case 0: SetPlayerCheckpointEx(playerid, 2200.2737,-2236.7378,13.5469, 4.0);
				case 1: SetPlayerCheckpointEx(playerid, -1727.7521,-130.6874,3.5547, 4.0);
				case 2: SetPlayerCheckpointEx(playerid, 2816.9790,921.3257,10.7500, 4.0);
				case 3: SetPlayerCheckpointEx(playerid, 65.9495,-244.0107,2.1663, 10.0);
				case 4: SetPlayerCheckpointEx(playerid, -29.3832,-318.0885,5.1610, 4.0);
	        }
			return 1;
	    }
	    case 5569:
	    {
     		if(!response) return 1;
	        switch(listitem)
	        {
	            case 0: SetPlayerCheckpointEx(playerid, 1637.2380,-1117.3322,23.9063, 4.0);
				case 1: SetPlayerCheckpointEx(playerid, -2264.0349,167.7004,35.1641, 4.0);
				case 2: SetPlayerCheckpointEx(playerid, 2167.1677,987.3502,10.8130, 4.0);
	        }
			return 1;
	    }
 		case 5561:
	    {
	        if(!response) return 1;
	        if(PI[playerid][pTruckSkill] >= 500) return SendClientMessage(playerid,COLOR_WHITE,!"{FF2222}[Ошибка] {FFFFFF}У вас максимальный навык");
	        PI[playerid][pVirMoney] -= 100;
	        PI[playerid][pTruckSkill] = 500;
	        UpdatePlayerData(playerid,"TruckSkill",PI[playerid][pTruckSkill]);
	        UpdatePlayerData(playerid,"VirMoney",PI[playerid][pVirMoney]);
	        SendClientMessage(playerid,COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Вы приобрели максимальный навык дальнобойщика!");
			return 1;
	    }
	    case 5559:
	    {
	        if(!response) return 1;
	        switch(listitem)
	        {
	            case 0:
	            {
	                SetPlayerCheckpointEx(playerid, 2200.2737,-2236.7378,13.5469, 4.0);
	            }
				case 1:
				{
					SetPlayerCheckpointEx(playerid, -1727.7521,-130.6874,3.5547, 4.0);
				}
				case 2:
				{
					SetPlayerCheckpointEx(playerid, 2816.9790,921.3257,10.7500, 4.0);
				}
	        }
			return 1;
	    }
		case 5556:
	    {
	        new vehicleid = GetPlayerVehicleID(playerid);
			new price = GetPVarInt(playerid,"truckprice");
			DeletePVar(playerid,"truckprice");
			if(GetMoney(playerid) < price) return SendClientMessage(playerid,COLOR_GREY,"У Вас недостаточно денег");
			if(!response || vehicleid == INVALID_VEHICLE_ID) return RemovePlayerFromVehicle(playerid);
			pTemp[playerid][pTruckID] = vehicleid;
			VehicleInfo[vehicleid][vTruckOwner] = playerid;
			GiveMoney(playerid,-price);
			SendClientMessage(playerid,COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Вы арендовали грузовик. Используйте {FFC800}/truck {ffffff}чтобы посмотреть места загрузки");
			return 1;
	    }
        case 5557:
		{
			if(!response) return 1;
			new amount = strval(inputtext);
			new maxamount = GetPVarInt(playerid,"maxamount");
			new loadid = GetPVarInt(playerid,"loadid");
			if(!(1 <= amount <= maxamount))
			{
			    totalstring[0] = 0;
			    format(totalstring, 80,"{FFC800}[Подсказка] {FFFFFF}Значение должно быть от 1 до %d",maxamount);
				SendClientMessage(playerid,COLOR_WHITE,totalstring);
				totalstring[0] = 0;
				switch(loadid)
				{
					case 0:
					{
					    totalstring[0] = 0;
						format(totalstring, 100, "{FFFFFF}Сколько киллограмм вы хотите загрузить?\nМаксимальная грузоподьемность {FF2222}%d", maxamount);
						ShowPlayerDialogEx(playerid, 5557, 1, "Загрузка", totalstring, "Принять", "Отмена");
						totalstring[0] = 0;
					}
					case 1:
					{
					    totalstring[0] = 0;
						format(totalstring, 100, "{FFFFFF}Сколько киллограмм вы хотите загрузить?\nМаксимальная грузоподьемность {FF2222}%d", maxamount);
						ShowPlayerDialogEx(playerid, 5557, 1, "Загрузка", totalstring, "Принять", "Отмена");
						totalstring[0] = 0;
					}
					case 3:
					{
					    totalstring[0] = 0;
						format(totalstring, 100, "{FFFFFF}Сколько киллограмм вы хотите загрузить?\nМаксимальная грузоподьемность {FF2222}%d", maxamount);
						ShowPlayerDialogEx(playerid, 5557, 1, "Загрузка", totalstring, "Принять", "Отмена");
						totalstring[0] = 0;
					}
				}
				return 1;
			}
			new price;
			if(loadid == 0) price = k1*amount;
			else if(loadid == 1) price = k2*amount;
			else if(loadid == 3) price = k3*amount;
			
			if(GetMoney(playerid) < price) return SendClientMessage(playerid,COLOR_GREY,"У вас недостаточно денег");
			new ll;
			for (new i;i<10;i++)
			{
				if(gTruckLoadTurn[loadid][i] == INVALID_PLAYER_ID || i == playerid) continue;
				ll += GetPVarInt(gTruckLoadTurn[loadid][i],"truckamount");
			}
			for(new i;i<10;i++)
			{
				if(gTruckLoadTurn[loadid][i] == INVALID_PLAYER_ID)
				{
					gTruckLoadTurn[loadid][i] = playerid;
					format(string,sizeof(string),"{FFC800}[Подсказка] {FFFFFF}Вы номер %d в очереди на загрузку",i+1);
					SendClientMessage(playerid,COLOR_WHITE,string);
					SetPVarInt(playerid,"truckamount",amount);
					SetPVarInt(playerid,"truckonroad",0);
					SetPVarInt(playerid,"waitgruz",0);
					SetPVarInt(playerid,"mesto",1);
					GiveMoney(playerid,-price,"стал в очеред [truck]");
					DeletePVar(playerid,"maxamount");
					
					new mes[25];
					format(mes,sizeof mes,"~r~ -%d$",price);
					GameTextForPlayer(playerid,mes,2100,1);
					return 1;
				}
			}
			SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет места в очереди. Подождите пожалуйста");
		}
	    case 5558:
		{
		    if(!response) return 1;
	    	TruckerSpawnEx(playerid);
	    	return 1;
 		}
 		case 5577:
 		{
 		    if(!response) return 1;
  			MechSpawnEx(playerid);
	    	return 1;
 		}
 		case 5578:
 		{
 		    if(!response) return 1;
  			ProductSpawnEx(playerid);
	    	return 1;
 		}
		case 288:
        {
            if(!response)
                return 1;

            if(!PI[playerid][pFraction])
                return 1;

            if(PI[playerid][pRank] != 11)
                return 1;

            new
                fractionid = PI[playerid][pFraction]-1,
                frmt_find[256],
                string_find[3000],
                total_online;


            foreach(new i: Player)
            {
                if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
                    continue;

                if(PI[i][pAdmin] > 0 || pTemp[i][pTempLeader])
                    continue;

                if(PI[i][pFraction] != fractionid+1 || PI[i][pSubfraction] != listitem)
                    continue;

                total_online++;
            }


            format(frmt_find, sizeof frmt_find,"{FFFFFF}Всего Online: {FF9900}%d\n", total_online);
            strcat(string_find, frmt_find);
            strcat(string_find, !"{FFFFFF}ID\tУровень\tТелефон\tРанг\tВыговоры\tИмя игрока\n\n");

            foreach(new i: Player)
            {
                if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
                    continue;

                if(PI[i][pAdmin] > 0 || pTemp[i][pTempLeader])
                    continue;

                if(PI[i][pFraction] != fractionid+1 || PI[i][pSubfraction] != listitem)
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
            return 1;
        }
	    case 5555:
	    {
	        if(!response) return 1;
	        switch(listitem)
	        {
     			case 0:
				{
					if(exp_x2 == 1)
					{
					    SendRconCommand("hostname Virtual. Role Play");
						exp_x2 = 0;
					}
					else if(exp_x2 == 0)
					{
						exp_x2 = 1;
						SendRconCommand("hostname Virtual. Role Play | x2 EXP");
					}
					
					totalstring[0] = 0;
					format(totalstring,128,"Вы %s X2 EXP",(exp_x2 != 1)?("деактивировали"):("активировали"));
					SendClientMessage(playerid, -1, totalstring);
					totalstring[0] = 0;
					
					update_bonus("expx2",exp_x2);
				}
        		case 1:
				{
					if(donate_x2 == 1)
					{
					    SendRconCommand("hostname Virtual. Role Play");
						donate_x2 = 0;
					}
					else if(donate_x2 == 0)
					{
						donate_x2 = 1;
						SendRconCommand("hostname Virtual. Role Play | x2 донат");
					}
					totalstring[0] = 0;
					format(totalstring,128,"Вы %s X2 DONATE",(donate_x2 != 1)?("деактивировали"):("активировали"));
					SendClientMessage(playerid,-1,totalstring);
					totalstring[0] = 0;
					update_bonus("donatex2",donate_x2);
				}
			}
	    }
	    case 1:
	    {
			if(response)
			{
			    //PlayerPlaySound(playerid, 1136, 0.0, 0.0, 0.0);
			    switch(RegisterState[playerid])
			    {
				    case 1:
				    {
						if(strlen(inputtextsave) < 6 || strlen(inputtext) > 22)
							return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Длина пароля должна быть от 6-и до 22-х символов"), ShowRegisterDialog(playerid, RegisterState[playerid]);
							
						else if(!CheckPassword(inputtextsave))
						    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В пароле найдены запрещенные символы"), ShowRegisterDialog(playerid, RegisterState[playerid]);

						RegisterState[playerid] = 2;
						mysql_real_escape_string(inputtextsave, RegPass[playerid]);
						ShowRegisterDialog(playerid,RegisterState[playerid]);
					}
					case 2:
					{
					    if(strfind(inputtext,"|") != -1)
							return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас в почте присутствуют запрещенные символы"), ShowRegisterDialog(playerid, RegisterState[playerid]);

			            if(strlen(inputtext) < 7 || strfind(inputtext, "@", true) == -1 || strfind(inputtext, ".", true) == -1)
							return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}E-Mail неверный. Повторите ввод"), ShowRegisterDialog(playerid, RegisterState[playerid]);

			            if(strlen(inputtext) > 49)
							return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}E-Mail неверный. Повторите ввод"), ShowRegisterDialog(playerid, RegisterState[playerid]);


					    mysql_real_escape_string(inputtextsave, RegEmail[playerid]);
					    RegisterState[playerid] = 3;
				        ShowRegisterDialog(playerid,RegisterState[playerid]);
					}
					case 3:
					{
					    RegisterState[playerid] = 4;
				        ShowRegisterDialog(playerid,RegisterState[playerid]);
				        RegSex[playerid] = listitem+1;
					}
					case 4:
					{
					    RegisterState[playerid] = 5;
				        ShowRegisterDialog(playerid, RegisterState[playerid]);
				        RegRace[playerid] = listitem;
					}
					case 5:
					{
					    RegisterState[playerid] = 6;
				        ShowRegisterDialog(playerid, RegisterState[playerid]);
				        RegNation[playerid] = listitem+1;
					}
					case 6:
					{
						if(!strlen(inputtextsave))
						    return ShowRegisterDialog(playerid, RegisterState[playerid]);

						if(!isNumeric(inputtextsave))
						    return SendClientMessage(playerid,COLOR_GREY,"Возраст персонажа должен содержать только цифры\nНапример: 17"), ShowRegisterDialog(playerid, RegisterState[playerid]);

						if(strval(inputtext) < 16 || strval(inputtext) > 80)
							return SendClientMessage(playerid,COLOR_GREY,"Возраст пероснажа не может быть меньше 16 и больше 80"), ShowRegisterDialog(playerid, RegisterState[playerid]);

					    RegisterState[playerid] = 0;
				        ShowRegisterDialog(playerid, RegisterState[playerid]);
				        RegAge[playerid] = strval(inputtextsave);
					    OnPlayerRegister(playerid, RegPass[playerid]);
					   	PI[playerid][pMoney]+=600;
					   	PI[playerid][pZKP]=0;
					   	PI[playerid][pRadio]=1;
					   	J_SetPlayerHealth(playerid,100);
					}
				    default: return false;
				}
			}
			else
			{
		        if(RegisterState[playerid] > 1)
		        {
		       	 	RegisterState[playerid] --;
					ShowRegisterDialog(playerid,RegisterState[playerid]);
				}
				else SendClientMessage(playerid, COLOR_WHITE, "Введите /q чтобы Выйти"), J_Kick(playerid);
			}
			return true;
		}

		case 3861:
		{
		    if(response)
		    {
		        new hotworld;
		        switch(listitem)
		        {
		            case 0: hotworld = 11;
		            case 1:hotworld = 12;
		            case 2:hotworld = 13;
		            case 3:hotworld = 14;
		            case 4:hotworld = 15;
		            case 5:hotworld = 16;
		        }
		        pTemp[playerid][pAntiAir] += 4;
				SetPlayerVirtualWorld(playerid,hotworld);
				SetPlayerInterior(playerid,1);
				SetPlayerPos(playerid,1121.4690,-2590.3865,1221.5060);
				J_SetPlayerFacingAngle(playerid,91.1574);
			}
		}
		case 359:
		{
			if(!response)
				return 1;
				
			new color;
			switch(listitem)
			{
				case 0: color = 1;
				case 1: color = 0;
				case 2: color = 2;
				case 3: color = 3;
				case 4: color = 6;
				case 5: color = 103;
				case 6: color = 33;
				case 7: color = 126;
				case 8: color = 102;
				case 9: color = 85;
				default: return ShowPlayerDialogEx(playerid, 360, 1, !"Выбор цвета номер 1", !"Введите ID цвета номер 1:", !"ОК", !"Назад");
			}
			SetPVarInt(playerid,"pbuycarC1",color);
			
			ShowPlayerDialogEx(playerid, 361, 2, !"Выберите цвет номер 2", !"1.Белый\n{505050}2.Черный\n{33CCFF}3.Голубой\n{FF0000}4.Красный\n{FFFF00}5.Желтый\n{0066FF}6. Синий\n{AFAFAF}7.Серый\n{E75480}8. Розовый\n{f5f5dc}9.Бежевый\n{ff00ff}10.Пурпурный\n{FFFFFF}Другой...", !"OK", !"Выход");
		}
		case 360:
		{
			if(!response)
				return ShowPlayerDialogEx(playerid, 359, 2, !"Выберите цвет номер 1", !"1.Белый\n{505050}2.Черный\n{33CCFF}3.Голубой\n{FF0000}4.Красный\n{FFFF00}5.Желтый\n{0066FF}6. Синий\n{AFAFAF}7.Серый\n{E75480}8. Розовый\n{f5f5dc}9.Бежевый\n{ff00ff}10.Пурпурный\n{FFFFFF}Другой...", !"OK", !"Выход");

			if(!strval(inputtextsave))
			{
				SendClientMessage(playerid, COLOR_GREY, !"Вы должны указать ID цвета авто");
				return ShowPlayerDialogEx(playerid, 360, 1, !"Выбор цвета номер 1", !"Введите ID цвета номер 1:", !"ОК", !"Назад");
			}
			for(new i;i < strlen(inputtextsave);i ++)
			{
			    if(inputtextsave[i] < '0' || inputtextsave[i] > '9')
			    {
					SendClientMessage(playerid, COLOR_GREY, !"Вы должны указать ID цвета авто");
					return ShowPlayerDialogEx(playerid, 360, 1, !"Выбор цвета номер 1", !"Введите ID цвета номер 1:", !"ОК", !"Назад");
				}
			}
			
			SetPVarInt(playerid,"pbuycarC1",strval(inputtext));
			ShowPlayerDialogEx(playerid, 361, 2, !"Выберите цвет номер 2", !"1.Белый\n{505050}2.Черный\n{33CCFF}3.Голубой\n{FF0000}4.Красный\n{FFFF00}5.Желтый\n{0066FF}6. Синий\n{AFAFAF}7.Серый\n{E75480}8. Розовый\n{f5f5dc}9.Бежевый\n{ff00ff}10.Пурпурный\n{FFFFFF}Другой...", !"OK", !"Выход");
		}
		case 361:
		{
			if(!response) 
				return ShowPlayerDialogEx(playerid, 361, 2, !"Выберите цвет номер 2", !"1.Белый\n{505050}2.Черный\n{33CCFF}3.Голубой\n{FF0000}4.Красный\n{FFFF00}5.Желтый\n{0066FF}6. Синий\n{AFAFAF}7.Серый\n{E75480}8. Розовый\n{f5f5dc}9.Бежевый\n{ff00ff}10.Пурпурный\n{FFFFFF}Другой...", !"OK", !"Выход");

			new color;
			switch(listitem)
			{
				case 0: color = 1;
				case 1: color = 0;
				case 2: color = 2;
				case 3: color = 3;
				case 4: color = 6;
				case 5: color = 103;
				case 6: color = 33;
				case 7: color = 126;
				case 8: color = 102;
				case 9: color = 85;
				default: return ShowPlayerDialogEx(playerid, 362, 1, !"Выбор цвета номер 2", !"Введите ID цвета номер 2:", !"ОК", !"Назад");
			}
			SetPVarInt(playerid,"pbuycarC2",color);
   			ShowPlayerDialogEx(playerid, 363, 0, !"Покупка авто", !"{FFFFFF}Вы действительно хотите купить этот автомобиль?", !"Да", !"Нет");
		}
		case 362:
		{
			if(!response)
				return ShowPlayerDialogEx(playerid, 361, 2, !"Выберите цвет номер 2", !"1.Белый\n{505050}2.Черный\n{33CCFF}3.Голубой\n{FF0000}4.Красный\n{FFFF00}5.Желтый\n{0066FF}6. Синий\n{AFAFAF}7.Серый\n{E75480}8. Розовый\n{f5f5dc}9.Бежевый\n{ff00ff}10.Пурпурный\n{FFFFFF}Другой...", !"OK", !"Выход");

			if(!strval(inputtextsave))
			{
				SendClientMessage(playerid, COLOR_GREY, !"Вы должны указать ID цвета авто");
				return ShowPlayerDialogEx(playerid, 362, 1, !"Выбор цвета номер 2", !"Введите ID цвета номер 2:", !"ОК", !"Назад");
			}
			for(new i;i < strlen(inputtextsave);i ++)
			{
			    if(inputtextsave[i] < '0' || inputtextsave[i] > '9')
			    {
					SendClientMessage(playerid, COLOR_GREY, !"Вы должны указать ID цвета авто");
					return ShowPlayerDialogEx(playerid, 362, 1, !"Выбор цвета номер 2", !"Введите ID цвета номер 2:", !"ОК", !"Назад");
				}
			}
			
			SetPVarInt(playerid,"pbuycarC2",strval(inputtext));
   			ShowPlayerDialogEx(playerid, 363, 0, !"Покупка авто", !"{FFFFFF}Вы действительно хотите купить этот автомобиль?", !"Да", !"Нет");
		}
		case 363:
		{
			if(!response)
				return 1;

			new
				carid = VehicleToBuy[playerid],
				color1 = GetPVarInt(playerid,"pbuycarC1"),
				color2 = GetPVarInt(playerid,"pbuycarC2"),
				model = GetVehicleModel(carid),
				modelid = model - 400,
				houseid = PI[playerid][pHouseKey]-1,
				price = Transport[modelid][trPrice];
				
			if(PI[playerid][pMoney] < price)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				
	        if(VehicleToBuy[playerid] != INVALID_VEHICLE_ID) DestroyVehicle(VehicleToBuy[playerid]);
	        VehicleToBuy[playerid] = INVALID_VEHICLE_ID;
	        BuyCar[playerid] = -1;
			f_TogglePlayerControllable(playerid, true);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid,0);
			SetCameraBehindPlayer(playerid);
			CancelSelectTextDraw(playerid);
            temp_buying_car[playerid] = false;
            
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
	        
	        
			if(PI[playerid][pHouseKey] != 0)
			{
				if(GetString(HouseInfo[PI[playerid][pHouseKey]-1][hOwner],Name(playerid)))
				{
					new slot = -1;
					for(new i;i<MAX_VEHICLES;i++)
					{
						if(CarInfo[i][cOwnerID] == 0)
						{
							slot = i;
							break;
						}
					}

					if(slot == -1)
						return SendClientMessage(playerid, COLOR_RED, "Ошибка слота (#01)");

					new query_buycar[256];
					format(query_buycar, sizeof query_buycar, "INSERT INTO `cars` VALUES ('', '%d', '%d', '%d', '%d', '-', '%.0f', '1000.0', '0.0', '00.00.0000', '0|0|0|0|0|0|0|0|0|0|0|0|0|0', '5', '0')", PI[playerid][pID], modelid, color1, color2, Transport[modelid][trTank]+0.0);
					new Cache:result = mysql_query(mysql, query_buycar);
					new id = cache_insert_id(mysql);


					PI[playerid][pCars] = id;
					UpdatePlayerData(playerid, "Cars", id);
					CarInfo[slot][cID] = id;
					CarInfo[slot][cOwnerID] = PI[playerid][pID];
					CarInfo[slot][cModelID] = modelid;
					CarInfo[slot][cFuel] = 40;
					CarInfo[slot][cMilage] = 0.0;
					CarInfo[slot][cHealth] = 1000.0;
					CarInfo[slot][cColor_1] = color1;
					CarInfo[slot][cColor_2] = color2;
					SetString(CarInfo[slot][cDate], "00.00.0000");
					cache_delete(result, mysql);

					new vehicleid = CreateVehicle(Transport[modelid][trModel], HouseInfo[houseid][hPark_X], HouseInfo[houseid][hPark_Y], HouseInfo[houseid][hPark_Z], HouseInfo[houseid][hPark_R], CarInfo[slot][cColor_1], CarInfo[slot][cColor_2], -1);
					CarInfo[slot][cVehID] = vehicleid;

					for(new tn; tn < 14; tn++)
						if(CarInfo[slot][cTuning][tn] != 0) RemoveVehicleComponent(CarInfo[slot][cVehID], CarInfo[slot][cTuning][tn]), CarInfo[slot][cTuning][tn] = 0;

					ChangeVehiclePaintjob(CarInfo[slot][cVehID], 5);
					
					SetVehicleNumberPlate(CarInfo[slot][cVehID], CarInfo[slot][cNumber]);

                    ToggleLock(vehicleid);
					VehicleInfo[vehicleid][vFuel] = CarInfo[slot][cFuel];
					VehicleInfo[vehicleid][vMillage] = CarInfo[slot][cMilage];
					VehicleInfo[vehicleid][vHealth] = CarInfo[slot][cHealth];
					VehicleInfo[vehicleid][vOwnerid] = CarInfo[slot][cOwnerID];
					VehicleInfo[vehicleid][vX] = HouseInfo[houseid][hPark_X];
					VehicleInfo[vehicleid][vY] = HouseInfo[houseid][hPark_Y];
					VehicleInfo[vehicleid][vZ] = HouseInfo[houseid][hPark_Z];
					VehicleInfo[vehicleid][vProbability] = 0;
					VehicleInfo[vehicleid][vLock] = 1;
					SetDoorsStatus(vehicleid, 1);
		            PI[playerid][pPTS] = 0;
		            UpdatePlayerData(playerid, "PTS", PI[playerid][pPTS]);
		            temp_car_num_get[playerid] = 0;

            
					SendClientMessage(playerid,COLOR_GREEN,"Поздравляем Вы купили т/с. Оно доставлено к вашему дому/отелю");//Зеленым 0xFF4000FF
					SendClientMessage(playerid,COLOR_WHITE,"{FFC800}[Подсказка] {FFFFFF}Для получения ПТС на Ваш автомобиль, Вы должны получить номерные знаки в пункте выдачи.");
					SendClientMessage(playerid,COLOR_WHITE,"{FFC800}[Подсказка] {FFFFFF}Пункт выдачи находится /gps -> Авторынки/Тюнинги -> Пункт выдачи номерных знаков.");
					GiveMoney(playerid, -price, "buycar");

					if(BuyCar_Class[playerid] == 0)
					{
					    if(BizInfo[56][bProducts] - 35 > 0)
					    {
						    BizInfo[56][bProducts] -= 35;
							GiveBusinessMoney(56, price/100*10);
							if(BizInfo[56][bKrasher]) GiveFracBank(BizInfo[56][bKrasher],price/100*10);
						}
					}
					
 					else if(BuyCar_Class[playerid] == 1)
					{
					    if(BizInfo[57][bProducts] - 35 > 0)
					    {
					        BizInfo[57][bProducts] -= 35;
							GiveBusinessMoney(57, price/100*5);
							if(BizInfo[57][bKrasher]) GiveFracBank(BizInfo[57][bKrasher],price/100*10);
						}
					}
 					else if(BuyCar_Class[playerid] == 2)
 					{
					    if(BizInfo[58][bProducts] - 35 > 0)
					    {
					        BizInfo[58][bProducts] -= 35;
							GiveBusinessMoney(58, price/100*1);
							if(BizInfo[58][bKrasher]) GiveFracBank(BizInfo[58][bKrasher],price/100*10);
						}
					}
					
 					else if(BuyCar_Class[playerid] == 3)
 					{
					    if(BizInfo[59][bProducts] - 35 > 0)
					    {
					        BizInfo[59][bProducts] -= 35;
							GiveBusinessMoney(59, price/100*5);
							if(BizInfo[59][bKrasher]) GiveFracBank(BizInfo[59][bKrasher],price/100*10);
						}
					}
				}
				else
				    return SendClientMessage(playerid, COLOR_GREY, !"Доступно только владельцу дома");
			}
			
			else
				SendClientMessage(playerid, COLOR_GREY, !"Купите дом или арендуйте комнату в отеле");

			BuyCar_Class[playerid] = -1;

		}
		case 940:
		{
			if(!response)
				return 1;
				
			if(!listitem)
				return 1;
				
			new
				id = temp_newlead_receiver[playerid]-1,
				subid = listitem-1,
				fractionid = temp_newlead_id[id] - 1,
				frid = GetSubfractionID(fractionid+1);
				
			temp_newlead_subid[id] = subid+1;
			
			if(!IsPlayerConnected(id) || !PI[id][pID])
				return SendClientMessage(playerid, COLOR_GREY, !"Неверный ID");
				
			new mes[128];
			format(mes, sizeof mes, "Вы предложили %s стать лидером \"%s\"", PN(id), gSubfractionName[frid][subid]);
			SendClientMessage(playerid, 0x269BD8FF, mes);

			format(mes, sizeof mes, "{FFFFFF}%s предложил Вам стать лидером \"%s\"", PN(playerid), gSubfractionName[frid][subid]);
			ShowPlayerDialogEx(id, 941, DIALOG_STYLE_MSGBOX, !"Лидерство", mes, !"Вступить", !"Отмена");

		}
		case 941:
		{
		    new id = temp_newlead_sender[playerid] - 1,
				fractionid = temp_newlead_id[playerid] - 1,
				skinid,
				subid = temp_newlead_subid[playerid] - 1,
				frid = GetSubfractionID(fractionid+1),
				query_upd_fraction[270];

			if(PI[playerid][pSex] == 1)
			    skinid = OrgInfo[fractionid][oMSkins][9];

			else if(PI[playerid][pSex] == 2)
			    skinid = OrgInfo[fractionid][oWSkins][9];

			new Year, Month, Day, date[25];
			getdate(Year, Month, Day);
			format(date, sizeof date, "%d-%d-%d", Day, Month, Year);
			SetString(PI[playerid][pDateInvite], date);
			SetString(PI[playerid][pLastRank], date);
			
			format(query_upd_fraction, sizeof query_upd_fraction, "UPDATE `accounts` SET `Fraction` = '%d', `Rank` = '10', `FractionSkin` = '%d', `Subfraction` = '%d', `DateInvite` = '%s', `LastRank` = '%d' WHERE `ID` = '%d'", fractionid+1, skinid, subid+1, date, date, PI[playerid][pID]);
			mysql_tquery(mysql, query_upd_fraction);

			PI[playerid][pFraction] = fractionid+1;
			PI[playerid][pRank] = 10;
			PI[playerid][pFractionSkin] = skinid;
			PI[playerid][pSubfraction] = subid+1;
			PI[playerid][pJob] = 0;
			UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			PI[playerid][pPointsOrg] = 0;
			UpdatePlayerData(playerid, "PointsOrg", PI[playerid][pPointsOrg]);
			PI[playerid][pDivision] = 0;
			UpdatePlayerData(playerid, "Division", PI[playerid][pDivision]);

			SetPlayerColor(playerid, gFractionColor[fractionid]);
			SetPlayerSkinEx(playerid, skinid);

			
			new mes[128];
			format(mes, sizeof mes, "%s назначил вас лидером подфракции %s: \"%s\"", PN(id), gFractionName[fractionid], gSubfractionName[frid][subid]);
			SendClientMessage(playerid, COLOR_YELLOW, mes);
			format(mes, sizeof mes, "Вы назначили %s управлять подфракцией: \"%s\"", PN(playerid), gSubfractionName[frid][subid]);
			SendClientMessage(id, COLOR_YELLOW, mes);
		}
		case 912:
		{
			if(!response)
				return 1;

			if(listitem == 0)
			{
			    temp_makelead_fraction[playerid] = listitem+1;
			    
				ShowPlayerDialogEx(playerid, 911, DIALOG_STYLE_LIST, !"Выберите подфракцию", !"Министр Здравоохранения\nДиректор больницы LS\nДиректор больницы SF\nДиректор больницы LV", !"Выбрать", !"Отмена");
			    return 1;
			}
			else if(listitem == 6)
			{
				temp_makelead_fraction[playerid] = listitem+1;

				ShowPlayerDialogEx(playerid, 911, DIALOG_STYLE_LIST, !"Выберите подфракцию", !"Министр Обороны\nГенерал LV\nГенерал SF", !"Выбрать", !"Отмена");
			    return 1;
			}
			else if(listitem == 7)
			{
			    temp_makelead_fraction[playerid] = listitem+1;

				ShowPlayerDialogEx(playerid, 911, DIALOG_STYLE_LIST, !"Выберите подфракцию", !"Комиссар полиции\nШеф департамента LS\nШеф департамента SF\nШеф департамента LV", !"Выбрать", !"Отмена");
			    return 1;
			}
			else if(listitem == 8)
			{
			    temp_makelead_fraction[playerid] = listitem+1;
			    
				ShowPlayerDialogEx(playerid, 911, DIALOG_STYLE_LIST, !"Выберите подфракцию", !"Директор Virtual. Media\nГлавный редактор LS\nГлавный редактор SF\nГлавный редактор LV", !"Выбрать", !"Отмена");
			    return 1;
			}
			else if(listitem == 9)
			{
				temp_makelead_fraction[playerid] = listitem+1;

				ShowPlayerDialogEx(playerid, 911, DIALOG_STYLE_LIST, !"Выберите подфракцию", !"Губернатор\nМэр LS\nМэр SF\nМэр LV", !"Выбрать", !"Отмена");
			    return 1;
			}
			new
			    target = temp_makelead[playerid],
				fractionid = listitem,
				skinid,
				rank = gFractionRankCount[fractionid],
				query_upd_fraction[190 + 20];
			
			if(PI[target][pSex] == 1)
			    skinid = OrgInfo[fractionid][oMSkins][rank-1];
			    
			else if(PI[target][pSex] == 2)
			    skinid = OrgInfo[fractionid][oWSkins][rank-1];
			
			new Year, Month, Day, date[25];
			getdate(Year, Month, Day);
			format(date, sizeof date, "%d-%d-%d", Day, Month, Year);
			SetString(PI[target][pDateInvite], date);
			SetString(PI[target][pLastRank], date);

			format(query_upd_fraction, sizeof query_upd_fraction, "UPDATE `accounts` SET `Fraction` = '%d', `Rank` = '%d', `FractionSkin` = '%d', `Subfraction` = '0', `DateInvite` = '%s', `LastRank` = '%s' WHERE `ID` = '%d'", listitem+1, rank, skinid, date, date, PI[target][pID]);
			mysql_tquery(mysql, query_upd_fraction);

			PI[target][pFraction] = listitem+1;
			PI[target][pRank] = rank;
			PI[target][pFractionSkin] = skinid;
			PI[target][pSubfraction] = 0;
			PI[target][pPointsOrg] = 0;
			UpdatePlayerData(target, "PointsOrg", PI[target][pPointsOrg]);
			PI[target][pDivision] = 0;
			UpdatePlayerData(target, "Division", PI[target][pDivision]);
		    PI[target][pSpawn] = 1;
		    UpdatePlayerData(target, "Spawn", 1);

			SetPlayerColor(target, gFractionColor[listitem]);
			SetPlayerSkinEx(target, skinid);

			new
				frmt_message_newlead[128];


			format(frmt_message_newlead, sizeof frmt_message_newlead, "Администратор %s назначил вас лидером организации \"%s\"", PN(playerid), gFractionName[listitem]);
			SendClientMessage(target, COLOR_YELLOW, frmt_message_newlead);

			format(frmt_message_newlead,sizeof frmt_message_newlead, "Администратор %s назначил %s лидером организации \"%s\"", PN(playerid), PN(target), gFractionName[listitem]);
			SendAdminsMessage(COLOR_RED, frmt_message_newlead);
		}
		case 911:
		{
		    if(!response)
		        return 1;
		        
			new
			    target = temp_makelead[playerid],
				fractionid = temp_makelead_fraction[playerid] - 1,
				skinid,
				query_upd_fraction[250 + 20]
			;
			
			if(listitem == 0)
			{
				if(PI[target][pSex] == 1)
				    skinid = OrgInfo[fractionid][oMSkins][10];

				else if(PI[target][pSex] == 2)
				    skinid = OrgInfo[fractionid][oWSkins][10];

				new Year, Month, Day, date[25];
				getdate(Year, Month, Day);
				format(date, sizeof date, "%d-%d-%d", Day, Month, Year);
				SetString(PI[target][pDateInvite], date);
				SetString(PI[target][pLastRank], date);
			
				format(query_upd_fraction, sizeof query_upd_fraction, "UPDATE `accounts` SET `Fraction` = '%d', `Rank` = '11', `FractionSkin` = '%d', `Subfraction` = '0', `DateInvite` = '%s', `LastRank` = '%s' WHERE `ID` = '%d'", fractionid+1, skinid, date, date, PI[target][pID]);
				mysql_tquery(mysql, query_upd_fraction);

				PI[target][pFraction] = fractionid+1;
				PI[target][pRank] = 11;
				PI[target][pFractionSkin] = skinid;
				PI[target][pSubfraction] = 0;
				PI[target][pDivision] = 0;
				SetPlayerColor(target, gFractionColor[fractionid]);
				SetPlayerSkinEx(target, skinid);
				PI[target][pPointsOrg] = 0;
				UpdatePlayerData(target, "PointsOrg", PI[target][pPointsOrg]);
				UpdatePlayerData(target, "Division", PI[target][pDivision]);
			    PI[target][pSpawn] = 1;
			    UpdatePlayerData(target, "Spawn", 1);

				if(PI[playerid][pHouseKey] != 0)
				{
					new houseid = PI[playerid][pHouseKey] - 1;
					new slot;
					for(new i;i<4;i++)
					{
						if(!HouseInfo[houseid][hSkin][i])
						{
							slot = i;
							break;
						}
						HouseInfo[houseid][hSkin][slot] = skinid;
						UpdateHouseDress(houseid);
					}
				}
				
				new
					frmt_message_newlead[128];


				format(frmt_message_newlead, sizeof frmt_message_newlead, "Администратор %s назначил вас лидером организации \"%s\"", PN(playerid), gFractionName[fractionid]);
				SendClientMessage(target, COLOR_YELLOW, frmt_message_newlead);

				format(frmt_message_newlead,sizeof frmt_message_newlead, "Администратор %s назначил %s лидером организации \"%s\"", PN(playerid), PN(target), gFractionName[fractionid]);
				SendAdminsMessage(COLOR_RED, frmt_message_newlead);
			}
			else
			{
				new
					frid = GetSubfractionID(fractionid+1);

				if(PI[target][pSex] == 1)
				    skinid = OrgInfo[fractionid][oMSkins][9];

				else if(PI[target][pSex] == 2)
				    skinid = OrgInfo[fractionid][oWSkins][9];

				new Year, Month, Day, date[25];
				getdate(Year, Month, Day);
				format(date, sizeof date, "%d-%d-%d", Day, Month, Year);
				SetString(PI[target][pDateInvite], date);
				SetString(PI[target][pLastRank], date);
				
				format(query_upd_fraction, sizeof query_upd_fraction, "UPDATE `accounts` SET `Fraction` = '%d', `Rank` = '10', `FractionSkin` = '%d', `Subfraction` = '%d', `DateInvite` = '%s', `LastRank` = '%s' WHERE `ID` = '%d'", fractionid+1, skinid, listitem, date, date, PI[target][pID]);
				mysql_tquery(mysql, query_upd_fraction);

				PI[target][pFraction] = fractionid+1;
				PI[target][pRank] = 10;
				PI[target][pFractionSkin] = skinid;
				PI[target][pSubfraction] = listitem;
				PI[target][pJob] = 0;
				UpdatePlayerData(target, "Job", PI[target][pJob]);
				PI[target][pPointsOrg] = 0;
				UpdatePlayerData(target, "PointsOrg", PI[target][pPointsOrg]);
				PI[target][pDivision] = 0;
				UpdatePlayerData(target, "Division", PI[target][pDivision]);
				PI[target][pSpawn] = 1;
			    UpdatePlayerData(target, "Spawn", 1);
			    
				SetPlayerColor(target, gFractionColor[fractionid]);
				SetPlayerSkinEx(target, skinid);

				new
					frmt_message_newlead[128];

				format(frmt_message_newlead, sizeof frmt_message_newlead, "Администратор %s назначил вас лидером подфракции \"%s\"", PN(playerid), gSubfractionName[frid][listitem-1]);
				SendClientMessage(target, COLOR_YELLOW, frmt_message_newlead);

				format(frmt_message_newlead,sizeof frmt_message_newlead, "Администратор %s назначил %s лидером подфракции \"%s\"", PN(playerid), PN(target), gSubfractionName[frid][listitem-1]);
				SendAdminsMessage(COLOR_RED, frmt_message_newlead);
			}
		}
		case 81:
		{
			if(!response)
				return 1;

			new
				target = temp_unvac_sender[playerid] - 1,
				fractionid = PI[playerid][pv_Fraction]-1,
				rankid = PI[playerid][pv_Rank],
				skinid;

			if(PI[target][pFraction] != fractionid+1)
				return SendClientMessage(playerid, COLOR_GREY, !"Ошибка #001");

			if(PI[playerid][pSex] == 1)
			    skinid = OrgInfo[fractionid][oMSkins][rankid-1];

			else if(PI[playerid][pSex] == 2)
			    skinid = OrgInfo[fractionid][oWSkins][rankid-1];

			PI[playerid][pFraction] = PI[playerid][pv_Fraction];
			PI[playerid][pRank] = PI[playerid][pv_Rank];
			PI[playerid][pFractionSkin] = skinid;
			PI[playerid][pSubfraction] = PI[playerid][pv_Subfraction];
			PI[playerid][pJob] = 0;
			UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			PI[playerid][pDivision] = 0;
			UpdatePlayerData(playerid, "Division", PI[playerid][pDivision]);
			SetPlayerColor(playerid, gFractionColor[fractionid]);
			SetPlayerSkinEx(playerid, skinid);
			
			new
				query_invite[190 + 9 + 4 + 4 + 4];

			format(query_invite, sizeof query_invite, "UPDATE `accounts` SET `Fraction` = '%d', `Rank` = '1', `FractionSkin` = '%d', `Subfraction` = '%d', `Job` = '0' WHERE `ID` = '%d'", PI[playerid][pFraction], skinid, PI[playerid][pSubfraction], PI[playerid][pID]);
			mysql_tquery(mysql, query_invite);

			UpdatePlayerData(playerid, "Subfraction", PI[playerid][pSubfraction]);


			PI[playerid][pv_Fraction] = 0;
			UpdatePlayerData(playerid, "v_Fraction", PI[playerid][pv_Fraction]);
			PI[playerid][pv_Subfraction] = 0;
			UpdatePlayerData(playerid, "v_Subfraction", PI[playerid][pv_Subfraction]);
			PI[playerid][pv_Rank] = 0;
			UpdatePlayerData(playerid, "v_Rank", PI[playerid][pv_Rank]);
			PI[playerid][pv_FWarns] = 0;
			UpdatePlayerData(playerid, "v_FWarns", PI[playerid][pv_FWarns]);
			PI[playerid][pv_Days] = 0;
			UpdatePlayerData(playerid, "v_Days", PI[playerid][pv_Days]);
			PI[playerid][pv_FractionSkin] = 0;
			UpdatePlayerData(playerid, "v_FractionSkin", PI[playerid][pv_FractionSkin]);
		    PI[playerid][pSpawn] = 1;
		    UpdatePlayerData(playerid, "Spawn", 1);

			new
				frmt_invite_mes[70 + 50];

			format(frmt_invite_mes, sizeof frmt_invite_mes, "%s вышел с отпуска", PN(playerid));
			SendClientMessage(target, 0x269BD8FF, frmt_invite_mes);
			SendClientMessage(playerid, 0x269BD8FF, "Вы вышли с отпуска");
		}
		case 1881:
		{
			if(!response)
				return 1;

			new
				nickname[MAX_PLAYER_NAME],
				frmt_nom_message[950];

			switch(listitem)
			{
			    case 0:
			    {
					new
						days;

					new Cache:result = mysql_query(mysql, "SELECT `NickName`, `AlleyDays` FROM `accounts` WHERE `Alley` = 1 AND `AlleyDays` > 0 ORDER BY `AlleyDays` DESC LIMIT 10");

					strcat(frmt_nom_message, "{FFDA00}ТОП 10{FFFFFF}\n\n");
					for(new i; i < 10; i++)
					{
					    cache_get_row(i, 0, nickname, mysql, 24);
					    days = cache_get_row_int(i, 1);

					    if(GetString(nickname, "NULL"))
					        format(frmt_nom_message, sizeof frmt_nom_message, "%s-\n", frmt_nom_message);

					    else
			            	format(frmt_nom_message, sizeof frmt_nom_message, "%s%s - %d %s\n", frmt_nom_message, nickname, days, Declension_GetDays(days));
					}
				    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Аллея славы", frmt_nom_message, !"Закрыть", !"");
				    cache_delete(result, mysql);
			    }
			    case 1..16:
			    {
			        format(frmt_nom_message, sizeof frmt_nom_message, "{FFDA00}%s{FFFFFF}\n\n", gNominationName[listitem-1]);
					for(new i; i < 10; i++)
					{
					    if(GetString(gNickNomination[listitem-1][i], "The State"))
					        format(frmt_nom_message, sizeof frmt_nom_message, "%s-\n", frmt_nom_message);

					    else
						{
						    if(listitem-1 == 0)
			            		format(frmt_nom_message, sizeof frmt_nom_message, "%s%s - %d лет в штате\n", frmt_nom_message, gNickNomination[listitem-1][i], gPointsNomination[listitem-1][i]);

						    else if(listitem-1 == 1 || listitem-1 == 7 || listitem-1 == 8)
			            		format(frmt_nom_message, sizeof frmt_nom_message, "%s%s - %d$\n", frmt_nom_message, gNickNomination[listitem-1][i], gPointsNomination[listitem-1][i]);

							else if(listitem-1 == 9)
			            		format(frmt_nom_message, sizeof frmt_nom_message, "%s%s - %d рублей\n", frmt_nom_message, gNickNomination[listitem-1][i], gPointsNomination[listitem-1][i]);

							else
			            		format(frmt_nom_message, sizeof frmt_nom_message, "%s%s - %d балл(ов)\n", frmt_nom_message, gNickNomination[listitem-1][i], gPointsNomination[listitem-1][i]);

					    }
					}
			        ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Аллея славы", frmt_nom_message, !"Закрыть", !"");
			    }
		    }
		}
		case 177:
		{
			if(!response)
				return 1;
				
			new
			    sender = temp_heal_sender[playerid] - 1;
			//	price = temp_heal_price[playerid] ;
			    
			    
			if(sender != INVALID_PLAYER_ID)
			{
				if(!response)
					return SendClientMessage(sender, COLOR_GREY, !"Пациент отказался от лечения");

				if(PI[playerid][pMoney] < 125)
					return SendClientMessage(playerid, COLOR_GREY, !"У Вас недостаточно денег");

				J_SetPlayerHealth(playerid, 100.0);
				GiveMoney(playerid, -125, "лечение");
				GiveMoney(sender, 62, "лечение");
				OrgInfo[0][oMoney] += 63;
				SendClientMessage(sender, COLOR_GREEN, !"Пациент согласился на лечение");
			}
		}
		case 82:
		{
			if(!response)
				return 1;
				
			new
				target = temp_fraction_sender[playerid] - 1,
				fractionid = temp_fraction_id[playerid]-1,
				skinid;
				
			if(PI[target][pFraction] != fractionid+1)
				return SendClientMessage(playerid, COLOR_GREY, !"Ошибка #001");

				
			if(PI[playerid][pSex] == 1)
			    skinid = OrgInfo[fractionid][oMSkins][0];

			else if(PI[playerid][pSex] == 2)
			    skinid = OrgInfo[fractionid][oWSkins][0];


			PI[playerid][pFraction] = fractionid+1;
			PI[playerid][pRank] = 1;
			PI[playerid][pFractionSkin] = skinid;
			PI[playerid][pSubfraction] = PI[target][pSubfraction];
			PI[playerid][pJob] = 0;
			UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			PI[playerid][pPointsOrg] = 0;
			UpdatePlayerData(playerid, "PointsOrg", PI[playerid][pPointsOrg]);
			PI[playerid][pDivision] = 0;
			UpdatePlayerData(playerid, "Division", PI[playerid][pDivision]);
		    PI[playerid][pSpawn] = 1;
		    UpdatePlayerData(playerid, "Spawn", 1);
			
			SetPlayerColor(playerid, gFractionColor[fractionid]);
			SetPlayerSkinEx(playerid, skinid);
			
			new Year, Month, Day, date[25];
			getdate(Year, Month, Day);
			format(date, sizeof date, "%d-%d-%d", Day, Month, Year);
			SetString(PI[playerid][pDateInvite], date);
			SetString(PI[playerid][pLastRank], date);
				
			new
				query_invite[240];
				
			format(query_invite, sizeof query_invite, "UPDATE `accounts` SET `Fraction` = '%d', `Rank` = '1', `FractionSkin` = '%d', `Subfraction` = '%d', `Job` = '0', `DateInvite` = '%s', `LastRank` = '%s' WHERE `ID` = '%d'", PI[playerid][pFraction], PI[playerid][pFractionSkin], PI[playerid][pSubfraction], date, date, PI[playerid][pID]);
			mysql_tquery(mysql, query_invite);

			UpdatePlayerData(playerid, "Subfraction", PI[playerid][pSubfraction]);

	
			new
				frmt_invite_mes[70 + 50];

			format(frmt_invite_mes, sizeof frmt_invite_mes, "%s был принят в организацию \"%s\"", PN(playerid), gFractionName[fractionid]);
			SendClientMessage(target, 0x269BD8FF, frmt_invite_mes);

			format(frmt_invite_mes,sizeof frmt_invite_mes, "Вы были приняты в организацию \"%s\"", gFractionName[fractionid]);
			SendClientMessage(playerid, 0x269BD8FF, frmt_invite_mes);

			if(PI[playerid][pQuest] == 16 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuest] = 0;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        GiveMoney(playerid, 35000, "квест 16");
		        if(PI[playerid][pPromo])
		        {
		            new promoid = PI[playerid][pPromo]-1;
		            GivePromoMoney(playerid, promoid, 5250);
		        }
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили все задания в этой квестовой линии. Вам начислено {33AA33}35000$");
			}
		}
		case 83:
		{
			if(!response)
				return 1;
				
			new
				target = temp_setrang_target[playerid]-1,
				fractionid = PI[playerid][pFraction] - 1;
				
			if(!IsPlayerConnected(playerid))
				return 1;

			new rank = listitem+1,
				action[16],
				action2[16];
				
			if(rank == PI[target][pRank]) return 1;
			else if(rank < PI[target][pRank]) action = "понизили";
			else action = "повысили";
			if(rank == PI[target][pRank]) return 1;
			else if(rank < PI[target][pRank]) action2 = "понизил";
			else action2 = "повысил";
			UpdatePlayerData(target,"Rank",rank);
			PI[target][pRank] = rank;
			
			new Year, Month, Day, date[25];
			getdate(Year, Month, Day);
			format(date, sizeof date, "%d-%d-%d", Day, Month, Year);
			SetString(PI[target][pLastRank], date);

			new
				query_rank[120];

			format(query_rank, sizeof query_rank, "UPDATE `accounts` SET `LastRank` = '%s' WHERE `ID` = '%d'", date, PI[target][pID]);
			mysql_tquery(mysql, query_rank);
			
			new mes[128];
			format(mes,sizeof(mes),"Вы %s %s до ранга: \"%s\"",action,PN(target),gFractionRankName[fractionid][rank-1]);
			if(fractionid+1 == 10 && !PI[target][pSubfraction] && rank <= 9)
				format(mes,sizeof(mes),"Вы %s %s до ранга: \"%s\"",action,PN(target),gPrezRankName[rank-1]);

            SendClientMessage(playerid,0x269BD8FF,mes);

			format(mes,sizeof(mes),"%s %s Вас до ранга: \"%s\"",PN(playerid),action2,gFractionRankName[fractionid][rank-1]);
            if(fractionid+1 == 10 && !PI[target][pSubfraction] && rank <= 9)
            	format(mes,sizeof(mes),"%s %s Вас до ранга: \"%s\"",PN(playerid),action2,gPrezRankName[rank-1]);
			SendClientMessage(target,0x269BD8FF,mes);
			
			new skinid;
			
			if(PI[target][pSex] == 1)
			    skinid = OrgInfo[fractionid][oMSkins][rank-1];
			    
			else if(PI[target][pSex] == 2)
			    skinid = OrgInfo[fractionid][oWSkins][rank-1];
			    
			SetPlayerSkinEx(target, skinid);
			PI[target][pFractionSkin] = skinid;
			UpdatePlayerData(target,"FractionSkin",skinid);
		}
		case 909:
		{
			if(!response)
				return 1;

			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");


			switch(listitem)
			{
			    case 0:
			    {
					if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
     					return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

					new
					    frmt_rank_name[700];

					strcat(frmt_rank_name, "{FFFFFF}№. Название\t{FFFFFF}Мужской\t{FFFFFF}Женский\n");


					if(PI[playerid][pFraction] == 10 && !PI[playerid][pSubfraction])
						return ShowPlayerDialogEx(playerid, 915, DIALOG_STYLE_LIST, !"Выберите фракцию", !"{FF7319}1.{FFFFFF} Правительство\n{FF7319}2.{FFFFFF} Мэрии", !"Далее", !"Назад");

					else if(PI[playerid][pFraction] != 10 && !PI[playerid][pSubfraction])
					{
						for(new i; i < gFractionRankCount[PI[playerid][pFraction]-1]; i++)
							format(frmt_rank_name, sizeof frmt_rank_name, "%s{FF7319}%d. {FFFFFF}%s\t{00a768}%d\t{00a768}%d\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i], OrgInfo[fractionid][oMSkins][i], OrgInfo[fractionid][oWSkins][i]);
					}

			        ShowPlayerDialogEx(playerid, 914, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить форму сотрудникам", frmt_rank_name, !"Далее", !"Назад");
			    }
			    case 1:
			    {
					if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
     					return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

					new
					    frmt_car_list[600];

					strcat(frmt_car_list, "{FFFFFF}№. Название\t             {FFFFFF}Минимальный ранг\n");

					for(new i; i < gFractionCarCount[PI[playerid][pFraction]-1]; i++)
						format(frmt_car_list, sizeof frmt_car_list, "%s{FF7319}%d. {FFFFFF}%s (%d)\t             {00A768}%d\n", frmt_car_list, i+1, Transport[gFractionCar[fractionid][i]-400][trName], gFractionCar[fractionid][i], OrgInfo[fractionid][oCarRanks][i]);

			        ShowPlayerDialogEx(playerid, 919, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить автомобили", frmt_car_list, !"Далее", !"Назад");

			    }
				case 2:
				{
					temp_showall_count[playerid] = 0;

					new
					    frmt_showall[2900],
						query_get_list[380],
						nickname[MAX_PLAYER_NAME],
						lastlogin[10],
						status[40],
						rang,
						vac,
						showall_count;

					format(query_get_list, sizeof query_get_list, "SELECT `NickName`, IF(`v_Days`>0, `v_Rank`, `Rank`), `LastLogin`, `v_Days` FROM `accounts` WHERE IF(`v_Days`>0, `v_Fraction` = '%d' AND `v_Subfraction` = '%d', `Fraction` = '%d' AND `Subfraction` = '%d') ORDER BY IF(`v_Days`>0, `v_Rank`, `Rank`) AND `Admin` = '0' ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction], fractionid+1, PI[playerid][pSubfraction]);
					new Cache:result = mysql_query(mysql, query_get_list);
		      		new accounts = cache_get_row_count(mysql);

		      		if(accounts == 0)
					  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции никто не состоит");

					strcat(frmt_showall, "№ Ник игрока\tРанг\tПоследний заход\tСтатус\n");

		      		for(new i; i < accounts; i ++)
		      		{
		      		    if(showall_count > 39 && accounts > 40)
						{
							format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
						    break;
						}
			  			cache_get_row(i, 0, nickname, mysql);
			  			rang = cache_get_row_int(i, 1, mysql);
	                    cache_get_row(i, 2, lastlogin, mysql);
	                    vac = cache_get_row_int(i, 3, mysql);

						if(vac)
						    SetString(status, "{FFA500}[В отпуске]");

						else if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
						    SetString(status, "{00CC44}[В сети]");

						else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
						    SetString(status, "{CD0000}[Не в сети]");

		      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%s\t%s\n", frmt_showall, i+1, nickname, rang, lastlogin, status);
			            temp_showall_count[playerid]++;
			            showall_count++;

		      		}
		      		ShowPlayerDialogEx(playerid, 921, DIALOG_STYLE_TABLIST_HEADERS, !"Список сотрудников", frmt_showall, !"Далее", !"Назад");
		      		cache_delete(result, mysql);
				}
				case 3:
				{
				    if(PI[playerid][pFraction] >= 12 && PI[playerid][pFraction] <= 14)
				    {
						new
							frmt_rank_name[256];

						for(new i;i<10;i++)
							format(frmt_rank_name, sizeof frmt_rank_name, "%s%d.%s\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i]);

						return ShowPlayerDialogEx(playerid, 988, DIALOG_STYLE_LIST, !"Выберите ранг", frmt_rank_name, !"Изменить", !"Отмена");

				    }
				    else if(PI[playerid][pFraction] == 8 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
				    {
						new frmt_division_list[143];

						for(new i; i < 5; i++)
							format(frmt_division_list, sizeof frmt_division_list, "%s{FF7319}%d.{FFFFFF} %s\n", frmt_division_list, i+1, gDivisionName[i]);

						return ShowPlayerDialogEx(playerid, 758, DIALOG_STYLE_LIST, !"Выберите подразделение", frmt_division_list, !"Выбор", !"Отмена");
					}
					else if(PI[playerid][pFraction] == 9 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
					{
					    new
					        frmt_price_list[120];

						format(frmt_price_list, sizeof frmt_price_list, "{FF7319}1.{FFFFFF} Объявление [{008B00}%d${FFFFFF}]\n{FF7319}2.{FFFFFF} Эфир [{008B00}%d${FFFFFF}]", gAdvertPrice, gEtherPrice);
						return ShowPlayerDialogEx(playerid, 511, DIALOG_STYLE_LIST, !"Регулирование цен", frmt_price_list, !"Изменить", !"Отмена");
					}


					
					if((PI[playerid][pFraction] == 1 || PI[playerid][pFraction] >= 7 && PI[playerid][pFraction] <= 9) && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
						return 1;
						
    				temp_showall_count[playerid] = 0;

					new
					    frmt_showall[2900],
						query_get_list[190],
						nickname[MAX_PLAYER_NAME],
						days,
						rang,
						showall_count;

					format(query_get_list, sizeof query_get_list, "SELECT `NickName`, `v_Rank`, `v_Days` FROM `accounts` WHERE `v_Fraction` = '%d' AND `v_Subfraction` = '%d' AND `v_Days` > 0 AND `Admin` = '0' ORDER BY `v_Rank` ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction]);
					new Cache:result = mysql_query(mysql, query_get_list);
		      		new accounts = cache_get_row_count(mysql);

		      		if(accounts == 0)
					  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет сотрудников в отпуске");

					strcat(frmt_showall, "{FFFFFF}№ Ник игрока\t{FFFFFF}Ранг\t{FFFFFF}Осталось в отпуске\n");

		      		for(new i; i < accounts; i ++)
		      		{
		      		    if(showall_count > 39 && accounts > 40)
						{
							format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
						    break;
						}
			  			cache_get_row(i, 0, nickname, mysql);
			  			rang = cache_get_row_int(i, 1, mysql);
                        days = cache_get_row_int(i, 2, mysql);


		      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%d %s\n", frmt_showall, i+1, nickname, rang, days, Declension_GetDays(days));
			            temp_showall_count[playerid]++;
			            showall_count++;

		      		}
		      		ShowPlayerDialogEx(playerid, 930, DIALOG_STYLE_TABLIST_HEADERS, !"Сотрудники в отпуске", frmt_showall, !"Далее", !"Назад");
		      		cache_delete(result, mysql);
				}
				case 4:
				{
	   				if(PI[playerid][pFraction] == 11 && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 10)
				    {
						new frmt_division_list[113];

						for(new i; i < 5; i++)
							format(frmt_division_list, sizeof frmt_division_list, "%s{FF7319}%d.{FFFFFF} %s\n", frmt_division_list, i+1, gTagName[i]);

						return ShowPlayerDialogEx(playerid, 778, DIALOG_STYLE_LIST, !"Выберите подразделение", frmt_division_list, !"Выбор", !"Отмена");
					}
					
					else if(PI[playerid][pFraction] >= 12 && PI[playerid][pFraction] <= 14)
				        callcmd::warehouse(playerid);

				}
				case 5: ShowPlayerDialogEx(playerid, 976, DIALOG_STYLE_LIST, !"Объявление для сотрудников", !"{FF7319}1.{FFFFFF} Создать объявление\n{FF7319}2.{FFFFFF} Удалить объявление\n{FF7319}3.{FFFFFF} Просмотреть объявление", !"Далее", !"Отмена");

			}

		}
		case 919:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);
		        
			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите во фракции");

			if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

			new
			    frmt_rank_name[500];

			temp_lmenu_car[playerid] = listitem+1;

			if(PI[playerid][pFraction] == 10 && !PI[playerid][pSubfraction])
				return ShowPlayerDialogEx(playerid, 935, DIALOG_STYLE_LIST, !"Выберите фракцию", !"{FF7319}1.{FFFFFF} Правительство\n{FF7319}2.{FFFFFF} Мэрии", !"Далее", !"Назад");

			else if(PI[playerid][pFraction] != 10 && !PI[playerid][pSubfraction])
			{
				for(new i; i < gFractionRankCount[PI[playerid][pFraction]-1]; i++)
					format(frmt_rank_name, sizeof frmt_rank_name, "%s%d. %s\n", frmt_rank_name, i+1, gFractionRankName[PI[playerid][pFraction]-1][i]);
			}
			ShowPlayerDialogEx(playerid, 920, DIALOG_STYLE_LIST, !"Выберите минимальный ранг", frmt_rank_name, !"Выбор", !"Назад");
			
		}
		case 920:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);
		        
			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите во фракции");

			if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");
				

			new
			    carid = temp_lmenu_car[playerid]-1,
				fid = PI[playerid][pFraction]-1,
				query_cars[140],
				data[70],
				frmt_msg[180];
			    
			OrgInfo[fid][oCarRanks][carid] = listitem+1;

			for(new i; i < 11; i++)
			{
				if(!i) format(data, sizeof data, "%d", OrgInfo[fid][oCarRanks][i]);
				else format(data, sizeof data, "%s|%d", data, OrgInfo[fid][oCarRanks][i]);
			}

			format(query_cars, sizeof query_cars, "UPDATE `orginfo` SET `cars_rank` = '%s' WHERE `fraction` = '%d'", data, fid+1);
			mysql_tquery(mysql, query_cars);

			format(frmt_msg, sizeof frmt_msg, "[F] %s изменил минимальный ранг для использования т/с %s", gFractionRankName[fid][PI[playerid][pRank]-1], Transport[gFractionCar[fid][carid]-400][trName]);
			FractionChat(fid+1, 0x4682B4AA, frmt_msg);
			format(frmt_msg, sizeof frmt_msg, "[F] Теперь этот транспорт доступен с %d ранга", listitem+1);
			FractionChat(fid+1, 0x4682B4AA, frmt_msg);
			
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Изменения будут применены после респавна т/с");
		}
		case 935:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);

			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

			new
			    frmt_rank_name[500];

			if(listitem == 0)
			{
				for(new i; i < 9; i++)
					format(frmt_rank_name, sizeof frmt_rank_name, "%s%d. %s\n", frmt_rank_name, i+1, gPrezRankName[i]);

				new
				    frmt_rank_last[100];

				format(frmt_rank_last, sizeof frmt_rank_last, "10. %s\n11. %s", gFractionRankName[fractionid][9], gFractionRankName[fractionid][10]);
				strcat(frmt_rank_name, frmt_rank_last);

                ShowPlayerDialogEx(playerid, 920, DIALOG_STYLE_LIST, !"Выберите минимальный ранг", frmt_rank_name, !"Выбор", !"Назад");
			}
			else if(listitem == 1)
			{
				for(new i; i < 10; i++)
					format(frmt_rank_name, sizeof frmt_rank_name, "%s%d. %s\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i]);

                ShowPlayerDialogEx(playerid, 920, DIALOG_STYLE_LIST, !"Выберите минимальный ранг", frmt_rank_name, !"Выбор", !"Назад");
			}
		}
		case 930:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);

			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите во фракции");

			if(listitem != 40)
			{
			    new nickname[MAX_PLAYER_NAME];

			    sscanf(inputtextsave, "{s[6]}s[24]", nickname);

			    new
			        query_getid[70 + MAX_PLAYER_NAME];

				format(query_getid, sizeof query_getid, "SELECT `ID` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", nickname);
				new Cache:result = mysql_query(mysql, query_getid);

				if(cache_get_row_count(mysql))
				{
					temp_lmenu_sel[playerid] = cache_get_row_int(0, 0, mysql);
					ShowPlayerDialogEx(playerid, 931, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Вернуть из отпуска", !"Далее", !"Назад");

				}
				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

			    cache_delete(result, mysql);
			}
			else if(listitem == 40)
			{
				new
				    frmt_showall[2900],
					query_get_list[200],
					nickname[MAX_PLAYER_NAME],
					days,
					rang,
					showall_count;

				format(query_get_list, sizeof query_get_list, "SELECT `NickName`, `v_Rank`, `v_Days` FROM `accounts` WHERE `v_Fraction` = '%d' AND `v_Subfraction` = '%d' AND `v_Days` > 0 AND `Admin` = '0' ORDER BY `v_Rank` ASC LIMIT %d, 41", fractionid+1, PI[playerid][pSubfraction], temp_showall_count[playerid]);
				new Cache:result = mysql_query(mysql, query_get_list);
	      		new accounts = cache_get_row_count(mysql);

	      		if(accounts == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет сотрудников в отпуске");

				strcat(frmt_showall, "{FFFFFF}№ Ник игрока\t{FFFFFF}Ранг\t{FFFFFF}Осталось в отпуске\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(showall_count > 39 && accounts > 40)
					{
						format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
		  			rang = cache_get_row_int(i, 1, mysql);
		  			days = cache_get_row_int(i, 2, mysql);

	      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%d %s\n", frmt_showall, temp_showall_count[playerid]+1, nickname, rang, days, Declension_GetDays(days));
		            temp_showall_count[playerid]++;
		            showall_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 930, DIALOG_STYLE_TABLIST_HEADERS, !"Сотрудники в отпуске", frmt_showall, !"Далее", !"Назад");
	      		cache_delete(result, mysql);
      		}
		}
		case 931:
		{
		    if(!response)
			{
			    new fractionid = PI[playerid][pFraction]-1;

				temp_showall_count[playerid] = 0;

				new
				    frmt_showall[2900],
					query_get_list[190],
					nickname[MAX_PLAYER_NAME],
					days,
					rang,
					showall_count;

				format(query_get_list, sizeof query_get_list, "SELECT `NickName`, `v_Rank`, `v_Days` FROM `accounts` WHERE `v_Fraction` = '%d' AND `v_Subfraction` = '%d' AND `Admin` = '0' ORDER BY `v_Rank` ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction]);
				new Cache:result = mysql_query(mysql, query_get_list);
	      		new accounts = cache_get_row_count(mysql);

	      		if(accounts == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет сотрудников в отпуске");

				strcat(frmt_showall, "{FFFFFF}№ Ник игрока\t{FFFFFF}Ранг\t{FFFFFF}Осталось в отпуске\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(showall_count > 39 && accounts > 40)
					{
						format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
		  			rang = cache_get_row_int(i, 1, mysql);
                    days = cache_get_row_int(i, 2, mysql);


	      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%d %s\n", frmt_showall, i+1, nickname, rang, days, Declension_GetDays(days));
		            temp_showall_count[playerid]++;
		            showall_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 930, DIALOG_STYLE_TABLIST_HEADERS, !"Сотрудники в отпуске", frmt_showall, !"Далее", !"Назад");
	      		cache_delete(result, mysql);

	      		return 1;
			}

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите во фракции");

			if(listitem == 0)
			{
				new
					query_check[270];

				format(query_check, sizeof query_check, "SELECT `NickName`, `v_Rank`, `Level`, `v_FWarns`, `ZKP`, `TelNum` FROM `accounts` WHERE `ID` = '%d' AND `Admin` = '0'", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_check);

				if(!cache_get_row_count(mysql))
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Аккаунт ненайден в базе данных"), cache_delete(result, mysql);

				new
				    frmt_info[600],
				    nickname[MAX_PLAYER_NAME],
				    rang,
				    level,
				    warns,
				    zkp,
				    number;

	  			cache_get_row(0, 0, nickname, mysql);
	  			rang = cache_get_row_int(0, 1, mysql);
	  			level = cache_get_row_int(0, 2, mysql);
	  			warns = cache_get_row_int(0, 3, mysql);
	  			zkp = cache_get_row_int(0, 4, mysql);
	  			number = cache_get_row_int(0, 5, mysql);

				format(frmt_info, sizeof frmt_info, "{FFFFFF}Имя: {269BD8}%s\n{FFFFFF}Ранг: {269BD8}%d\n{FFFFFF}Выговоры: {269BD8}%d/3\n{FFFFFF}Лет в штате: {269BD8}%d\n{FFFFFF}Законопослушность: {269BD8}%d\n{FFFFFF}Номер телефона: {269BD8}%d", nickname, rang, warns, level, zkp, number);
				ShowPlayerDialogEx(playerid, 932, DIALOG_STYLE_MSGBOX, !"Информация о сотруднике", frmt_info, !"Закрыть", !"");
				cache_delete(result, mysql);
			}
			else if(listitem == 1)
			{
			    new
			        query_getnick[70];

				format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
				    new nickname[MAX_PLAYER_NAME];
					cache_get_row(0, 0, nickname, mysql);

					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					{
						new unvac[40];
						format(unvac, sizeof unvac, "%d", GetPlayerID(nickname));
					    callcmd::unvacation(playerid, unvac);
					}
					
					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
						SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок оффлайн");
				}
				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

			    cache_delete(result, mysql);
			}
		}
		case 932:
		{
		    new
		        query_getnick[90];

			format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' AND `Admin` = '0' LIMIT 1", temp_lmenu_sel[playerid]);
			new Cache:result = mysql_query(mysql, query_getnick);

			if(cache_get_row_count(mysql))
			{
			    new nickname[MAX_PLAYER_NAME];
				cache_get_row(0, 0, nickname, mysql);
				ShowPlayerDialogEx(playerid, 931, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Вернуть из отпуска", !"Далее", !"Назад");
			}
			else
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

		    cache_delete(result, mysql);
		}
		case 916:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pSpawn] == 2)
					{
					    PI[playerid][pSpawn] = 1;
					    UpdatePlayerData(playerid, "Spawn", 1);
					    SendClientMessage(playerid, COLOR_GREEN, !"Теперь вы будете появляться на базе вашей организации");
					}
					else
					{
						PI[playerid][pSpawn] = 2;
					    UpdatePlayerData(playerid, "Spawn", 2);
					    SendClientMessage(playerid, COLOR_GREEN, !"Теперь вы будете появляться в доме / отеле");
					}
				}
				case 1:
				{
					if(PI[playerid][pSpawn] == 2)
					{
						PI[playerid][pSpawn] = 2;
					    UpdatePlayerData(playerid, "Spawn", 2);
					    SendClientMessage(playerid, COLOR_GREEN, !"Теперь вы будете появляться в доме / отеле");
					}
					else
					{
					    PI[playerid][pSpawn] = 1;
					    UpdatePlayerData(playerid, "Spawn", 1);
					    SendClientMessage(playerid, COLOR_GREEN, !"Теперь вы будете появляться на базе вашей организации");
					}

				}
			}
		}
		case 910:
		{
			if(!response)
				return 1;
				
			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			if(listitem == 0)
			{
				temp_showall_count[playerid] = 0;

				new
				    frmt_showall[2900],
					query_get_list[370],
					nickname[MAX_PLAYER_NAME],
					lastlogin[10],
					status[40],
					rang,
					vac,
					showall_count;

				format(query_get_list, sizeof query_get_list, "SELECT `NickName`, IF(`v_Days`>0, `v_Rank`, `Rank`), `LastLogin`, `v_Days` FROM `accounts` WHERE IF(`v_Days`>0, `v_Fraction` = '%d' AND `v_Subfraction` = '%d', `Fraction` = '%d' AND `Subfraction` = '%d') AND `Admin` = '0' ORDER BY IF(`v_Days`>0, `v_Rank`, `Rank`) ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction], fractionid+1, PI[playerid][pSubfraction]);
				new Cache:result = mysql_query(mysql, query_get_list);
	      		new accounts = cache_get_row_count(mysql);

	      		if(accounts == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции никто не состоит");

				strcat(frmt_showall, "№ Ник игрока\tРанг\tПоследний заход\tСтатус\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(showall_count > 39 && accounts > 40)
					{
						format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
		  			rang = cache_get_row_int(i, 1, mysql);
                    cache_get_row(i, 2, lastlogin, mysql);
                    vac = cache_get_row_int(i, 3, mysql);

					if(vac)
					    SetString(status, "{FFA500}[В отпуске]");
					    
					else if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					    SetString(status, "{00CC44}[В сети]");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					    SetString(status, "{CD0000}[Не в сети]");

	      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%s\t%s\n", frmt_showall, i+1, nickname, rang, lastlogin, status);
		            temp_showall_count[playerid]++;
		            showall_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 921, DIALOG_STYLE_TABLIST_HEADERS, !"Список сотрудников", frmt_showall, !"Далее", !"Назад");
	      		cache_delete(result, mysql);
			}
			else if(listitem == 1)
			{
				temp_showall_count[playerid] = 0;

				new
				    frmt_showall[2900],
					query_get_list[190],
					nickname[MAX_PLAYER_NAME],
					days,
					rang,
					showall_count;

				format(query_get_list, sizeof query_get_list, "SELECT `NickName`, `v_Rank`, `v_Days` FROM `accounts` WHERE `v_Fraction` = '%d' AND `v_Subfraction` = '%d' AND `Admin` = '0' ORDER BY `v_Rank` ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction]);
				new Cache:result = mysql_query(mysql, query_get_list);
	      		new accounts = cache_get_row_count(mysql);

	      		if(accounts == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет сотрудников в отпуске");

				strcat(frmt_showall, "{FFFFFF}№ Ник игрока\t{FFFFFF}Ранг\t{FFFFFF}Осталось в отпуске\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(showall_count > 39 && accounts > 40)
					{
						format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
		  			rang = cache_get_row_int(i, 1, mysql);
                    days = cache_get_row_int(i, 2, mysql);


	      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%d %s\n", frmt_showall, i+1, nickname, rang, days, Declension_GetDays(days));
		            temp_showall_count[playerid]++;
		            showall_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 930, DIALOG_STYLE_TABLIST_HEADERS, !"Сотрудники в отпуске", frmt_showall, !"Далее", !"Назад");
	      		cache_delete(result, mysql);
			}
			else if(listitem == 2)
			    ShowPlayerDialogEx(playerid, 976, DIALOG_STYLE_LIST, !"Объявление для сотрудников", !"{FF7319}1.{FFFFFF} Создать объявление\n{FF7319}2.{FFFFFF} Удалить объявление\n{FF7319}3.{FFFFFF} Просмотреть объявление", !"Далее", !"Отмена");

		}
		case 913:
		{
			if(!response)
				return 1;

			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");


			switch(listitem)
			{
			    case 0:
			    {
					if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
     					return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");
					
					new
					    frmt_rank_name[700];
					    
					strcat(frmt_rank_name, "{FFFFFF}№. Название\t{FFFFFF}Мужской\t{FFFFFF}Женский\n");


					if(PI[playerid][pFraction] == 10 && !PI[playerid][pSubfraction])
						return ShowPlayerDialogEx(playerid, 915, DIALOG_STYLE_LIST, !"Выберите фракцию", !"{FF7319}1.{FFFFFF} Правительство\n{FF7319}2.{FFFFFF} Мэрии", !"Далее", !"Назад");

					else if(PI[playerid][pFraction] != 10 && !PI[playerid][pSubfraction])
					{
						for(new i; i < gFractionRankCount[PI[playerid][pFraction]-1]; i++)
							format(frmt_rank_name, sizeof frmt_rank_name, "%s{FF7319}%d. {FFFFFF}%s\t{00a768}%d\t{00a768}%d\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i], OrgInfo[fractionid][oMSkins][i], OrgInfo[fractionid][oWSkins][i]);
					}
					
			        ShowPlayerDialogEx(playerid, 914, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить форму сотрудникам", frmt_rank_name, !"Далее", !"Назад");
			    }
			    case 1:
			    {
					if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
     					return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

					new
					    frmt_car_list[600];

					strcat(frmt_car_list, "{FFFFFF}№. Название\t             {FFFFFF}Минимальный ранг\n");

					for(new i; i < gFractionCarCount[PI[playerid][pFraction]-1]; i++)
						format(frmt_car_list, sizeof frmt_car_list, "%s{FF7319}%d. {FFFFFF}%s (%d)\t             {00A768}%d\n", frmt_car_list, i+1, Transport[gFractionCar[fractionid][i]-400][trName], gFractionCar[fractionid][i], OrgInfo[fractionid][oCarRanks][i]);

			        ShowPlayerDialogEx(playerid, 919, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить автомобили", frmt_car_list, !"Далее", !"Назад");
					
			    }
				case 2:
				{
					temp_showall_count[playerid] = 0;

					new
					    frmt_showall[2900],
						query_get_list[370],
						nickname[MAX_PLAYER_NAME],
						lastlogin[10],
						status[40],
						rang,
						vac,
						showall_count;

					format(query_get_list, sizeof query_get_list, "SELECT `NickName`, IF(`v_Days`>0, `v_Rank`, `Rank`), `LastLogin`, `v_Days` FROM `accounts` WHERE IF(`v_Days`>0, `v_Fraction` = '%d' AND `v_Subfraction` = '%d', `Fraction` = '%d' AND `Subfraction` = '%d') AND `Admin` = '0' ORDER BY IF(`v_Days`>0, `v_Rank`, `Rank`) ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction], fractionid+1, PI[playerid][pSubfraction]);
					new Cache:result = mysql_query(mysql, query_get_list);
		      		new accounts = cache_get_row_count(mysql);

		      		if(accounts == 0)
					  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции никто не состоит");

					strcat(frmt_showall, "№ Ник игрока\tРанг\tПоследний заход\tСтатус\n");

		      		for(new i; i < accounts; i ++)
		      		{
		      		    if(showall_count > 39 && accounts > 40)
						{
							format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
						    break;
						}
			  			cache_get_row(i, 0, nickname, mysql);
			  			rang = cache_get_row_int(i, 1, mysql);
	                    cache_get_row(i, 2, lastlogin, mysql);
	                    vac = cache_get_row_int(i, 3, mysql);

						if(vac)
						    SetString(status, "{FFA500}[В отпуске]");

						else if(GetPlayerID(nickname) != INVALID_PLAYER_ID && !vac)
						    SetString(status, "{00CC44}[В сети]");

						else if(GetPlayerID(nickname) == INVALID_PLAYER_ID && !vac)
						    SetString(status, "{CD0000}[Не в сети]");


		      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%s\t%s\n", frmt_showall, i+1, nickname, rang, lastlogin, status);
			            temp_showall_count[playerid]++;
			            showall_count++;

		      		}
		      		ShowPlayerDialogEx(playerid, 921, DIALOG_STYLE_TABLIST_HEADERS, !"Список сотрудников", frmt_showall, !"Далее", !"Назад");
		      		cache_delete(result, mysql);
				}
				case 3:
				{
				    for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++)
				    {
				        if(VehicleInfo[i][vTeam] != PI[playerid][pFraction] || IsVehicleOccupied(i)) continue;
				        SetVehicleToRespawn(i);
				    }
				    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Авто банды зареспавнено");
				}
				case 4:
				{
					new
						frmt_rank_name[256];

					for(new i;i<10;i++)
						format(frmt_rank_name, sizeof frmt_rank_name, "%s%d.%s\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i]);

					ShowPlayerDialogEx(playerid, 901, DIALOG_STYLE_LIST, !"Выберите ранг", frmt_rank_name, !"Изменить", !"Отмена");
				}
				case 5:
				{
					new
						frmt_rank_name[256];

					for(new i;i<10;i++)
						format(frmt_rank_name, sizeof frmt_rank_name, "%s%d.%s\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i]);

					ShowPlayerDialogEx(playerid, 987, DIALOG_STYLE_LIST, !"Выберите ранг", frmt_rank_name, !"Изменить", !"Отмена");

				}
				case 6: callcmd::warehouse(playerid);
				case 7: ShowPlayerDialogEx(playerid, 976, DIALOG_STYLE_LIST, !"Объявление для сотрудников", !"{FF7319}1.{FFFFFF} Создать объявление\n{FF7319}2.{FFFFFF} Удалить объявление\n{FF7319}3.{FFFFFF} Просмотреть объявление", !"Далее", !"Отмена");

			}
		}
		case 987:
		{
			if(!response)
				return 1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			new
				gangid = PI[playerid][pFraction] - 2,
				query_update_rank[70];

			gGangStorageRank[gangid] = listitem+1;
			
			format(query_update_rank, sizeof query_update_rank, "UPDATE `gangs` SET `storagerank` = '%d' WHERE `id` = '%d'", listitem+1, gangid+1);
			mysql_tquery(mysql, query_update_rank);
			SendClientMessage(playerid, COLOR_GREEN, !"Вы изменили ранг для доступа к общаку");

		}
		case 988:
		{
			if(!response)
				return 1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			new
				mafiaid = PI[playerid][pFraction] - 12,
				query_update_rank[70];

			gMafiaStorageRank[mafiaid] = listitem+1;

			format(query_update_rank, sizeof query_update_rank, "UPDATE `mafia` SET `storagerank` = '%d' WHERE `id` = '%d'", listitem+1, mafiaid+1);
			mysql_tquery(mysql, query_update_rank);
			SendClientMessage(playerid, COLOR_GREEN, !"Вы изменили ранг для доступа к общаку");

		}
		case 901:
		{
			if(!response)
				return 1;

			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			new
				frmt_change_rank[50 + 25];

			SetPVarInt(playerid, "selectedrank", listitem+1);
			format(frmt_change_rank, sizeof frmt_change_rank, "{FFFFFF}Введите новое название ранга '%s [%d]'", gFractionRankName[fractionid][listitem], listitem+1);
			ShowPlayerDialogEx(playerid, 902, DIALOG_STYLE_INPUT, !"Название ранга", frmt_change_rank, !"Изменить", !"Отмена");
		}
		case 902:
		{
			if(!response)
				return 1;

			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			new
				rankid = GetPVarInt(playerid,"selectedrank") - 1;
				
			if(rankid < 0)
				return 1;
				
			if(strlen(inputtext) < 1 || strlen(inputtext) > 20)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Название ранга должно содержать от 1 до 20 символов");
				new frmt_change_rank[50 + 25];
				format(frmt_change_rank, sizeof frmt_change_rank, "{FFFFFF}Введите новое название ранга '%s [%d]'", gFractionRankName[fractionid][listitem], listitem+1);
				ShowPlayerDialogEx(playerid, 902, DIALOG_STYLE_INPUT, !"Название ранга", frmt_change_rank, !"Изменить", !"Отмена");
				return 1;
			}
			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
				

			SetString(gFractionRankName[fractionid][rankid], inputtext);
			new query_update_rank[280],data[220];
			for(new i;i<10;i++)
			{
				if(!i) format(data,sizeof(data),"%s",gFractionRankName[fractionid][i]);
				else format(data,sizeof(data),"%s,%s",data,gFractionRankName[fractionid][i]);
			}
			format(query_update_rank,sizeof query_update_rank,"UPDATE `gangs` SET `ranks` = '%s' WHERE `id` = '%d'",data, fractionid-1);
			mysql_tquery(mysql, query_update_rank);
			SendClientMessage(playerid, COLOR_GREEN, !"Вы изменили название ранга");
			
			new
				frmt_rank_name[256];

			for(new i;i<10;i++)
				format(frmt_rank_name, sizeof frmt_rank_name, "%s%d.%s\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i]);

			ShowPlayerDialogEx(playerid, 901, DIALOG_STYLE_LIST, !"Выберите ранг", frmt_rank_name, !"Изменить", !"Отмена");
		}
		case 975:
		{
		    if(!response)
		        return 1;

			new fractionid = PI[playerid][pFraction]-1,
				subid = PI[playerid][pSubfraction];

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			if(!strlen(gNotice[fractionid][subid][nName]))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Объявление не найдено");

            strdel(gNotice[fractionid][subid][nName], 0, 24);
            strdel(gNotice[fractionid][subid][nText], 0, 128);
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы удалили текущее объявление");
		}
		case 976:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);

			new fractionid = PI[playerid][pFraction]-1,
				subid = PI[playerid][pSubfraction];

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			switch(listitem)
			{
			    case 0:
				{
					if(strlen(gNotice[fractionid][subid][nName]))
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже существует объявление. Удалите его для создания нового");
					    
					ShowPlayerDialogEx(playerid, 977, DIALOG_STYLE_INPUT, !"Создание объявления", !"{FFFFFF}Введите название объявления:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");
				}
				case 1:
				{
					if(!strlen(gNotice[fractionid][subid][nName]))
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Объявление не найдено");

					ShowPlayerDialogEx(playerid, 975, DIALOG_STYLE_MSGBOX, !"Удаление объявления", !"{FFFFFF}Вы действительно хотите удалить текущее объявление?", !"Да", !"Отмена");
				}
				case 2:
				{
					if(!strlen(gNotice[fractionid][subid][nName]))
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Объявление не найдено");

				    new
				        frmt_notice_text[310];

					format(frmt_notice_text, sizeof frmt_notice_text, "{FFFFFF}Название: {4EAAFF}%s\n\n{FFFFFF}Текст: {4EAAFF}%s", gNotice[fractionid][subid][nName], gNotice[fractionid][subid][nText]);
				    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Предпросмотр", frmt_notice_text, !"ОК", !"");
				}
			}
		}
		case 977:
		{
		    if(!response)
		        return 1;

			new fractionid = PI[playerid][pFraction]-1,
				subid = PI[playerid][pSubfraction];
				
			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			if(strlen(gNotice[fractionid][subid][nName]))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже существует объявление. Удалите его для создания нового");

			if(!strlen(inputtext) || strlen(inputtext) < 4 || strlen(inputtext) > 20)
				return ShowPlayerDialogEx(playerid, 977, DIALOG_STYLE_INPUT, !"Создание объявления", !"{FFFFFF}Введите название объявления:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			SetString(pTemp[playerid][pNoticeName], inputtext);
            strdel(pTemp[playerid][pNoticeText], 0, 128);

            new
				notice_text[128];

			if(!strlen(pTemp[playerid][pNoticeText]))
			    format(notice_text, sizeof notice_text, "{FF0000}-{FFFFFF}");

			new
			    frmt_notice_list[200];

			format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр", pTemp[playerid][pNoticeName], notice_text);
			ShowPlayerDialogEx(playerid, 978, DIALOG_STYLE_LIST, !"Создание объявления", frmt_notice_list, !"Далее", !"Отмена");
		}
		case 978:
		{
		    if(!response)
		    {
				strdel(pTemp[playerid][pNoticeName], 0, 24);
	            strdel(pTemp[playerid][pNoticeText], 0, 128);
				return 1;
		    }

			new fractionid = PI[playerid][pFraction]-1,
				subid = PI[playerid][pSubfraction];

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			if(strlen(gNotice[fractionid][subid][nName]))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже существует объявление. Удалите его для создания нового");

			switch(listitem)
			{
				case 0: ShowPlayerDialogEx(playerid, 979, DIALOG_STYLE_INPUT, !"Создание объявления", !"{FFFFFF}Введите название объявления:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");
			    case 1: ShowPlayerDialogEx(playerid, 980, DIALOG_STYLE_INPUT, !"Создание объявления", !"{FFFFFF}Введите текст:\n\n{AFAFAF}Он должен быть от 10-и до 120-и символов", !"Далее", !"Отмена");
				case 2:
				{
				    new
				        frmt_notice_text[310];

					format(frmt_notice_text, sizeof frmt_notice_text, "{FFFFFF}Название: {4EAAFF}%s\n\n{FFFFFF}Текст: {4EAAFF}%s", pTemp[playerid][pNoticeName], pTemp[playerid][pNoticeText]);
				    ShowPlayerDialogEx(playerid, 947, DIALOG_STYLE_MSGBOX, !"Предпросмотр", frmt_notice_text, !"ОК", !"");
				}
				case 3:
				{
				    new
				        frmt_notice_create[190];

					format(frmt_notice_create, sizeof frmt_notice_create, "{FFC800}[Подсказка] {FFFFFF}Вы создали объявление под названием {4EAAFF}\"%s\"", pTemp[playerid][pNoticeName]);
				    SendClientMessage(playerid, COLOR_WHITE, frmt_notice_create);
				    
					for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++)
					{
					    if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
					        continue;
					        
						if(PI[i][pFraction] == PI[playerid][pFraction] && PI[i][pSubfraction] == PI[playerid][pSubfraction])
					    {
					        SendClientMessage(i, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Глава вашей организации создал объявление");
					        SendClientMessage(i, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFFF00}/advert{FFFFFF} на базе организации для просмотра объявления");
					    }
					}

                    SetString(gNotice[fractionid][subid][nName], pTemp[playerid][pNoticeName]);
                    SetString(gNotice[fractionid][subid][nText], pTemp[playerid][pNoticeText]);

					strdel(pTemp[playerid][pNoticeName], 0, 24);
		            strdel(pTemp[playerid][pNoticeText], 0, 128);
				}

			}
		}
		case 979:
		{
		    if(!response)
		    {
	            new
					notice_text[128];

				if(strlen(pTemp[playerid][pNoticeText]) > 12)
				{
					strmid(notice_text, pTemp[playerid][pNoticeText], 0, 12, 128);
					format(notice_text, sizeof notice_text, "%s...", notice_text);
				}
				else if(!strlen(pTemp[playerid][pNoticeText]))
				    format(notice_text, sizeof notice_text, "{FF0000}-{FFFFFF}");

				else if(strlen(pTemp[playerid][pNoticeText]) < 12)
				    SetString(notice_text, pTemp[playerid][pNoticeText]);

				new
				    frmt_notice_list[200];

				if(strlen(pTemp[playerid][pNoticeText]) && strlen(pTemp[playerid][pNoticeName]))
					format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр\n{FF7319}4.{FFFFFF} Создать", pTemp[playerid][pNoticeName], notice_text);

				else
					format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр", pTemp[playerid][pNoticeName], notice_text);

				ShowPlayerDialogEx(playerid, 978, DIALOG_STYLE_LIST, !"Создание объявления", frmt_notice_list, !"Далее", !"Отмена");
				return 1;
		    }
		    
			new fractionid = PI[playerid][pFraction]-1,
				subid = PI[playerid][pSubfraction];

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			if(strlen(gNotice[fractionid][subid][nName]))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже существует объявление. Удалите его для создания нового");

			if(!strlen(inputtext) || strlen(inputtext) < 4 || strlen(inputtext) > 20)
				return ShowPlayerDialogEx(playerid, 979, DIALOG_STYLE_INPUT, !"Создание объявления", !"{FFFFFF}Введите название объявления:\n\n{AFAFAF}Текст должен быть от 4-х до 20-и символов", !"Далее", !"Отмена");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            SetString(pTemp[playerid][pNoticeName], inputtext);
            
            new
				notice_text[128];

			if(strlen(pTemp[playerid][pNoticeText]) > 12)
			{
				strmid(notice_text, pTemp[playerid][pNoticeText], 0, 12, 128);
				format(notice_text, sizeof notice_text, "%s...", notice_text);
			}
			else if(!strlen(pTemp[playerid][pNoticeText]))
			    format(notice_text, sizeof notice_text, "{FF0000}-{FFFFFF}");

			else if(strlen(pTemp[playerid][pNoticeText]) < 12)
			    SetString(notice_text, pTemp[playerid][pNoticeText]);
				    
			new
			    frmt_notice_list[200];

			if(strlen(pTemp[playerid][pNoticeText]) && strlen(pTemp[playerid][pNoticeName]))
				format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр\n{FF7319}4.{FFFFFF} Создать", pTemp[playerid][pNoticeName], notice_text);

			else
				format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр", pTemp[playerid][pNoticeName], notice_text);

			ShowPlayerDialogEx(playerid, 978, DIALOG_STYLE_LIST, !"Создание объявления", frmt_notice_list, !"Далее", !"Отмена");
		}
		case 980:
		{
		    if(!response)
		    {
	            new
					notice_text[128];

				if(strlen(pTemp[playerid][pNoticeText]) > 12)
				{
					strmid(notice_text, pTemp[playerid][pNoticeText], 0, 12, 128);
					format(notice_text, sizeof notice_text, "%s...", notice_text);
				}
				else if(!strlen(pTemp[playerid][pNoticeText]))
				    format(notice_text, sizeof notice_text, "{FF0000}-{FFFFFF}");

				else if(strlen(pTemp[playerid][pNoticeText]) < 12)
				    SetString(notice_text, pTemp[playerid][pNoticeText]);

				new
				    frmt_notice_list[200];

				if(strlen(pTemp[playerid][pNoticeText]) && strlen(pTemp[playerid][pNoticeName]))
					format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр\n{FF7319}4.{FFFFFF} Создать", pTemp[playerid][pNoticeName], notice_text);

				else
					format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр", pTemp[playerid][pNoticeName], notice_text);

				ShowPlayerDialogEx(playerid, 978, DIALOG_STYLE_LIST, !"Создание объявления", frmt_notice_list, !"Далее", !"Отмена");
				return 1;
		    }

			new fractionid = PI[playerid][pFraction]-1,
				subid = PI[playerid][pSubfraction];

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			if(strlen(gNotice[fractionid][subid][nName]))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже существует объявление. Удалите его для создания нового");

			if(!strlen(inputtext) || strlen(inputtext) < 10 || strlen(inputtext) > 120)
                return ShowPlayerDialogEx(playerid, 980, DIALOG_STYLE_INPUT, !"Создание объявления", !"{FFFFFF}Введите текст:\n\n{AFAFAF}Он должен быть от 10-и до 120-и символов", !"Далее", !"Отмена");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            SetString(pTemp[playerid][pNoticeText], inputtext);
            
            new
				notice_text[128];

			if(strlen(pTemp[playerid][pNoticeText]) > 12)
			{
				strmid(notice_text, pTemp[playerid][pNoticeText], 0, 12, 128);
				format(notice_text, sizeof notice_text, "%s...", notice_text);
			}
			else if(!strlen(pTemp[playerid][pNoticeText]))
			    format(notice_text, sizeof notice_text, "{FF0000}-{FFFFFF}");

			else if(strlen(pTemp[playerid][pNoticeText]) < 12)
			    SetString(notice_text, pTemp[playerid][pNoticeText]);

			new
			    frmt_notice_list[200];

			if(strlen(pTemp[playerid][pNoticeText]) && strlen(pTemp[playerid][pNoticeName]))
				format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр\n{FF7319}4.{FFFFFF} Создать", pTemp[playerid][pNoticeName], notice_text);

			else
				format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр", pTemp[playerid][pNoticeName], notice_text);

			ShowPlayerDialogEx(playerid, 978, DIALOG_STYLE_LIST, !"Создание объявления", frmt_notice_list, !"Далее", !"Отмена");
		}
		case 947:
		{
			new fractionid = PI[playerid][pFraction]-1,
				subid = PI[playerid][pSubfraction];

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(PI[playerid][pRank] != 10 && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только лидеру.");

			if(strlen(gNotice[fractionid][subid][nName]))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Уже существует объявление. Удалите его для создания нового");

            new
				notice_text[128];

			if(strlen(pTemp[playerid][pNoticeText]) > 12)
			{
				strmid(notice_text, pTemp[playerid][pNoticeText], 0, 12, 128);
				format(notice_text, sizeof notice_text, "%s...", notice_text);
			}
			else if(!strlen(pTemp[playerid][pNoticeText]))
			    format(notice_text, sizeof notice_text, "{FF0000}-{FFFFFF}");

			else if(strlen(pTemp[playerid][pNoticeText]) < 12)
			    SetString(notice_text, pTemp[playerid][pNoticeText]);

			new
			    frmt_notice_list[200];

			if(strlen(pTemp[playerid][pNoticeText]) && strlen(pTemp[playerid][pNoticeName]))
				format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр\n{FF7319}4.{FFFFFF} Создать", pTemp[playerid][pNoticeName], notice_text);

			else
				format(frmt_notice_list, sizeof frmt_notice_list, "{FF7319}1.{FFFFFF} Название [%s]\n{FF7319}2.{FFFFFF} Текст [%s]\n{FF7319}3.{FFFFFF} Предпросмотр", pTemp[playerid][pNoticeName], notice_text);

			ShowPlayerDialogEx(playerid, 978, DIALOG_STYLE_LIST, !"Создание объявления", frmt_notice_list, !"Далее", !"Отмена");

		}
		case 921:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);

			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите во фракции");

			if(listitem != 40)
			{
			    new nickname[MAX_PLAYER_NAME], warns, vac;
					
			    sscanf(inputtextsave, "{s[6]}s[24]", nickname);
			    
			    new
			        query_getid[90 + MAX_PLAYER_NAME];
			        
				format(query_getid, sizeof query_getid, "SELECT `ID`, `FWarns`, `v_Days` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", nickname);
				new Cache:result = mysql_query(mysql, query_getid);
				
				if(cache_get_row_count(mysql))
				{
					temp_lmenu_sel[playerid] = cache_get_row_int(0, 0, mysql);
					warns = cache_get_row_int(0, 1, mysql);
					vac = cache_get_row_int(0, 2, mysql);
					if(IsAGang(playerid) || IsAMafia(playerid))
						ShowPlayerDialogEx(playerid, 929, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Уволить сотрудника", !"Далее", !"Назад");

					else
					{
						if(vac)
						    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске");

						if(!warns)
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск", !"Далее", !"Назад");

						else
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск\n{FF7319}5.{FFFFFF} Снять выговор", !"Далее", !"Назад");

					}

				}
				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

			    cache_delete(result, mysql);
			}
			else if(listitem == 40)
			{
				new
				    frmt_showall[2900],
					query_get_list[370],
					nickname[MAX_PLAYER_NAME],
					lastlogin[10],
					status[40],
					rang,
					vac,
					showall_count;

				format(query_get_list, sizeof query_get_list, "SELECT `NickName`, IF(`v_Days`>0, `v_Rank`, `Rank`), `LastLogin`, `v_Days` FROM `accounts` WHERE IF(`v_Days`>0, `v_Fraction` = '%d' AND `v_Subfraction` = '%d', `Fraction` = '%d' AND `Subfraction` = '%d') AND `Admin` = '0' ORDER BY IF(`v_Days`>0, `v_Rank`, `Rank`) ASC LIMIT %d, 41", fractionid+1, PI[playerid][pSubfraction], fractionid+1, PI[playerid][pSubfraction], temp_showall_count[playerid]);
				new Cache:result = mysql_query(mysql, query_get_list);
	      		new accounts = cache_get_row_count(mysql);

	      		if(accounts == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции никто не состоит");

				strcat(frmt_showall, "№ Ник игрока\tРанг\tПоследний заход\tСтатус\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(showall_count > 39 && accounts > 40)
					{
						format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
		  			rang = cache_get_row_int(i, 1, mysql);
	                cache_get_row(i, 2, lastlogin, mysql);
	                vac = cache_get_row_int(i, 3, mysql);

					if(vac)
					    SetString(status, "{FFA500}[В отпуске]");
						    
					else if(GetPlayerID(nickname) != INVALID_PLAYER_ID && !vac)
					    SetString(status, "{00CC44}[В сети]");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID && !vac)
					    SetString(status, "{CD0000}[Не в сети]");

	      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%s\t%s\n", frmt_showall, temp_showall_count[playerid]+1, nickname, rang, lastlogin, status);
		            temp_showall_count[playerid]++;
		            showall_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 921, DIALOG_STYLE_TABLIST_HEADERS, !"Список сотрудников", frmt_showall, !"Далее", !"Назад");
	      		cache_delete(result, mysql);
      		}
		}
		case 922:
		{
		    if(!response)
			{
			    new fractionid = PI[playerid][pFraction]-1;
			    
				temp_showall_count[playerid] = 0;

				new
				    frmt_showall[2900],
					query_get_list[390],
					nickname[MAX_PLAYER_NAME],
					lastlogin[10],
					status[40],
					rang,
					vac,
					showall_count;

				format(query_get_list, sizeof query_get_list, "SELECT `NickName`, IF(`v_Days`>0, `v_Rank`, `Rank`), `LastLogin`, `v_Days` FROM `accounts` WHERE IF(`v_Days`>0, `v_Fraction` = '%d' AND `v_Subfraction` = '%d', `Fraction` = '%d' AND `Subfraction` = '%d') AND `Admin` = '0' ORDER BY IF(`v_Days`>0, `v_Rank`, `Rank`) ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction], fractionid+1, PI[playerid][pSubfraction]);
				new Cache:result = mysql_query(mysql, query_get_list);
	      		new accounts = cache_get_row_count(mysql);

	      		if(accounts == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции никто не состоит");

				strcat(frmt_showall, "№ Ник игрока\tРанг\tПоследний заход\tСтатус\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(showall_count > 39 && accounts > 40)
					{
						format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
		  			rang = cache_get_row_int(i, 1, mysql);
                    cache_get_row(i, 2, lastlogin, mysql);
                    vac = cache_get_row_int(i, 3, mysql);

					if(vac)
					    SetString(status, "{FFA500}[В отпуске]");

					else if(GetPlayerID(nickname) != INVALID_PLAYER_ID && !vac)
					    SetString(status, "{00CC44}[В сети]");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID && !vac)
					    SetString(status, "{CD0000}[Не в сети]");

	      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%s\t%s\n", frmt_showall, i+1, nickname, rang, lastlogin, status);
		            temp_showall_count[playerid]++;
		            showall_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 921, DIALOG_STYLE_TABLIST_HEADERS, !"Список сотрудников", frmt_showall, !"Далее", !"Назад");
	      		cache_delete(result, mysql);
	      		return 1;
			}
			
			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(listitem == 0)
			{
				new
					query_check[240];

				format(query_check, sizeof query_check, "SELECT `NickName`, `Rank`, `Level`, `FWarns`, `ZKP`, `TelNum`, `DateInvite`, `LastRank` FROM `accounts` WHERE `ID` = '%d'", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_check);

				if(!cache_get_row_count(mysql))
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Аккаунт ненайден в базе данных"), cache_delete(result, mysql);

				new
				    frmt_info[600],
				    nickname[MAX_PLAYER_NAME],
				    rang,
				    level,
				    warns,
				    zkp,
				    number,
				    dateinvite[24],
				    lastrank[24];

	  			cache_get_row(0, 0, nickname, mysql);
	  			rang = cache_get_row_int(0, 1, mysql);
	  			level = cache_get_row_int(0, 2, mysql);
	  			warns = cache_get_row_int(0, 3, mysql);
	  			zkp = cache_get_row_int(0, 4, mysql);
	  			number = cache_get_row_int(0, 5, mysql);
	            cache_get_row(0, 6, dateinvite, mysql);
	            cache_get_row(0, 7, lastrank, mysql);
				format(frmt_info, sizeof frmt_info, "{FFFFFF}Имя: {269BD8}%s\n{FFFFFF}Ранг: {269BD8}%d\n{FFFFFF}Выговоры: {269BD8}%d/3\n{FFFFFF}Лет в штате: {269BD8}%d\n{FFFFFF}Законопослушность: {269BD8}%d\n{FFFFFF}Номер телефона: {269BD8}%d\n{FFFFFF}Дата вступления в организацию: {269BD8}%s\n{FFFFFF}Дата последнего повышения: {269BD8}%s", nickname, rang, warns, level, zkp, number, dateinvite, lastrank);
				ShowPlayerDialogEx(playerid, 923, DIALOG_STYLE_MSGBOX, !"Информация о сотруднике", frmt_info, !"Закрыть", !"");
				cache_delete(result, mysql);
			}
			else if(listitem == 1)
			{
			    new
			        frmt_info[180],
			        query_getnick[120],
					nickname[MAX_PLAYER_NAME],
					status[40],
					warns;

				format(query_getnick, sizeof query_getnick, "SELECT `NickName`, `FWarns` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);
				
				if(cache_get_row_count(mysql))
				{
					cache_get_row(0, 0, nickname, mysql);
					warns = cache_get_row_int(0, 1, mysql);

					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					    SetString(status, "{00CC44}В сети");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					    SetString(status, "{CD0000}Не в сети");

					format(frmt_info, sizeof frmt_info, "{FFFFFF}Имя: {269BD8}%s\n{FFFFFF}Выговоры: {269BD8}%d/3\n{FFFFFF}Статус: {269BD8}%s\n\n{FFFFFF}Введите причину для выдачи выговора:", nickname, warns, status);

				    ShowPlayerDialogEx(playerid, 925, DIALOG_STYLE_INPUT, !"Выдача выговора", frmt_info, !"Выдать", !"Назад");
				}

				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

				cache_delete(result, mysql);
			}
			else if(listitem == 2)
			{
			    new
			        frmt_info[160],
			        query_getnick[90],
					nickname[MAX_PLAYER_NAME],
					status[40];
			        
				format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
					cache_get_row(0, 0, nickname, mysql);
					
					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					    SetString(status, "{00CC44}В сети");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					    SetString(status, "{CD0000}Не в сети");
					
					format(frmt_info, sizeof frmt_info, "{FFFFFF}Имя: {269BD8}%s\n{FFFFFF}Статус: {269BD8}%s\n\n{FFFFFF}Введите причину для увольнения:", nickname, status);

				    ShowPlayerDialogEx(playerid, 924, DIALOG_STYLE_INPUT, !"Увольнение сотрудника", frmt_info, !"Уволить", !"Назад");
				}
				
				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");
				    
				cache_delete(result, mysql);
			}
			else if(listitem == 3)
			{
				if((PI[playerid][pFraction] == 1 || PI[playerid][pFraction] >= 7 && PI[playerid][pFraction] <= 9) && !PI[playerid][pSubfraction] && PI[playerid][pRank] == 11)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция недоступна министру");
		
			    new
			        frmt_info[180],
			        query_getnick[90],
					nickname[MAX_PLAYER_NAME],
					status[40];

				format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
					cache_get_row(0, 0, nickname, mysql);

					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					    SetString(status, "{00CC44}В сети");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					    SetString(status, "{CD0000}Не в сети");

					format(frmt_info, sizeof frmt_info, "{FFFFFF}Имя: {269BD8}%s\n{FFFFFF}Статус: {269BD8}%s\n\n{FFFFFF}Введите количество дней отпуска (от 1 до 30):", nickname, status);

				    ShowPlayerDialogEx(playerid, 926, DIALOG_STYLE_INPUT, !"Отправление в отпуск", frmt_info, !"Готово", !"Назад");
				}

				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

				cache_delete(result, mysql);
			}
			else if(listitem == 4)
			{
			    new
			        query_getnick[70];

				format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
				    new nickname[MAX_PLAYER_NAME];
					cache_get_row(0, 0, nickname, mysql);

					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					{
						new online[40];
						format(online, sizeof online, "%d %s", GetPlayerID(nickname), inputtextsave);
					    callcmd::unfwarn(playerid, online);
					}
					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					{
						new offline[60];
						format(offline, sizeof offline, "%s %s", nickname, inputtextsave);
					    callcmd::unfwarnoff(playerid, offline);
					}
				}
				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

			    cache_delete(result, mysql);
			}
		}
		case 929:
		{
		    if(!response)
			{
			    new fractionid = PI[playerid][pFraction]-1;

				temp_showall_count[playerid] = 0;

				new
				    frmt_showall[2900],
					query_get_list[390],
					nickname[MAX_PLAYER_NAME],
					lastlogin[10],
					status[40],
					rang,
					vac,
					showall_count;

				format(query_get_list, sizeof query_get_list, "SELECT `NickName`, IF(`v_Days`>0, `v_Rank`, `Rank`), `LastLogin`, `v_Days` FROM `accounts` WHERE IF(`v_Days`>0, `v_Fraction` = '%d' AND `v_Subfraction` = '%d', `Fraction` = '%d' AND `Subfraction` = '%d') AND `Admin` = '0' ORDER BY IF(`v_Days`>0, `v_Rank`, `Rank`) ASC LIMIT 0, 41", fractionid+1, PI[playerid][pSubfraction], fractionid+1, PI[playerid][pSubfraction]);
				new Cache:result = mysql_query(mysql, query_get_list);
	      		new accounts = cache_get_row_count(mysql);

	      		if(accounts == 0)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей фракции никто не состоит");

				strcat(frmt_showall, "№ Ник игрока\tРанг\tПоследний заход\tСтатус\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(showall_count > 39 && accounts > 40)
					{
						format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}Следующая страница", frmt_showall);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
		  			rang = cache_get_row_int(i, 1, mysql);
                    cache_get_row(i, 2, lastlogin, mysql);
                    vac = cache_get_row_int(i, 3, mysql);

					if(vac)
					    SetString(status, "{FFA500}[В отпуске]");

					else if(GetPlayerID(nickname) != INVALID_PLAYER_ID && !vac)
					    SetString(status, "{00CC44}[В сети]");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID && !vac)
					    SetString(status, "{CD0000}[Не в сети]");

	      			format(frmt_showall, sizeof frmt_showall, "%s{FFFFFF}%d. %s\t%d\t%s\t%s\n", frmt_showall, i+1, nickname, rang, lastlogin, status);
		            temp_showall_count[playerid]++;
		            showall_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 921, DIALOG_STYLE_TABLIST_HEADERS, !"Список сотрудников", frmt_showall, !"Далее", !"Назад");
	      		cache_delete(result, mysql);
	      		return 1;
			}

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if(listitem == 0)
			{
				new
					query_check[240];

				format(query_check, sizeof query_check, "SELECT `NickName`, `Rank`, `Level`, `FWarns`, `ZKP`, `TelNum`, `DateInvite`, `LastRank` FROM `accounts` WHERE `ID` = '%d'", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_check);

				if(!cache_get_row_count(mysql))
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Аккаунт ненайден в базе данных"), cache_delete(result, mysql);

				new
				    frmt_info[600],
				    nickname[MAX_PLAYER_NAME],
				    rang,
				    level,
				    warns,
				    zkp,
				    number,
				    dateinvite[24],
				    lastrank[24];

	  			cache_get_row(0, 0, nickname, mysql);
	  			rang = cache_get_row_int(0, 1, mysql);
	  			level = cache_get_row_int(0, 2, mysql);
	  			warns = cache_get_row_int(0, 3, mysql);
	  			zkp = cache_get_row_int(0, 4, mysql);
	  			number = cache_get_row_int(0, 5, mysql);
	            cache_get_row(0, 6, dateinvite, mysql);
	            cache_get_row(0, 7, lastrank, mysql);
				format(frmt_info, sizeof frmt_info, "{FFFFFF}Имя: {269BD8}%s\n{FFFFFF}Ранг: {269BD8}%d\n{FFFFFF}Выговоры: {269BD8}%d/3\n{FFFFFF}Лет в штате: {269BD8}%d\n{FFFFFF}Законопослушность: {269BD8}%d\n{FFFFFF}Номер телефона: {269BD8}%d\n{FFFFFF}Дата вступления в организацию: {269BD8}%s\n{FFFFFF}Дата последнего повышения: {269BD8}%s", nickname, rang, warns, level, zkp, number, dateinvite, lastrank);
				ShowPlayerDialogEx(playerid, 923, DIALOG_STYLE_MSGBOX, !"Информация о сотруднике", frmt_info, !"Закрыть", !"");
				cache_delete(result, mysql);
			}
			else if(listitem == 1)
			{
			    new
			        frmt_info[160],
			        query_getnick[90],
					nickname[MAX_PLAYER_NAME],
					status[40];

				format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
					cache_get_row(0, 0, nickname, mysql);

					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					    SetString(status, "{00CC44}В сети");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					    SetString(status, "{CD0000}Не в сети");

					format(frmt_info, sizeof frmt_info, "{FFFFFF}Имя: {269BD8}%s\n{FFFFFF}Статус: {269BD8}%s\n\n{FFFFFF}Введите причину для увольнения:", nickname, status);

				    ShowPlayerDialogEx(playerid, 924, DIALOG_STYLE_INPUT, !"Увольнение сотрудника", frmt_info, !"Уволить", !"Назад");
				}

				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных");

				cache_delete(result, mysql);
			}
		}
		case 923:
		{
		    new
		        query_getnick[90];

			format(query_getnick, sizeof query_getnick, "SELECT `NickName`, `FWarns`, `v_Days` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
			new Cache:result = mysql_query(mysql, query_getnick);

			if(cache_get_row_count(mysql))
			{
			    new nickname[MAX_PLAYER_NAME], warns, vac;
				cache_get_row(0, 0, nickname, mysql);
				warns = cache_get_row_int(0, 1, mysql);
				vac = cache_get_row_int(0, 2, mysql);
				
				if(IsAGang(playerid) || IsAMafia(playerid))
					ShowPlayerDialogEx(playerid, 929, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Уволить сотрудника", !"Далее", !"Назад");

				else
				{
					if(vac)
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске");

					if(!warns)
						ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск", !"Далее", !"Назад");

					else
						ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск\n{FF7319}5.{FFFFFF} Снять выговор", !"Далее", !"Назад");

				}
			}
			else
			    SendClientMessage(playerid, COLOR_GREY, !"Произошла ошибка в базе данных");

		    cache_delete(result, mysql);
		}
		case 924:
		{
			if(!response)
			{
			    new
			        query_getnick[90];

				format(query_getnick, sizeof query_getnick, "SELECT `NickName`, `FWarns`, `v_Days` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
				    new nickname[MAX_PLAYER_NAME], warns, vac;
					cache_get_row(0, 0, nickname, mysql);
					warns = cache_get_row_int(0, 1, mysql);
					vac = cache_get_row_int(0, 2, mysql);
					if(IsAGang(playerid) || IsAMafia(playerid))
						ShowPlayerDialogEx(playerid, 929, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Уволить сотрудника", !"Далее", !"Назад");

					else
					{
						if(vac)
						    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске");

						if(!warns)
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск", !"Далее", !"Назад");

						else
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск\n{FF7319}5.{FFFFFF} Снять выговор", !"Далее", !"Назад");

					}
				}
				else
				    SendClientMessage(playerid, COLOR_GREY, !"Произошла ошибка в базе данных");

			    cache_delete(result, mysql);
			    return 1;
			}
			
			if(strlen(inputtextsave) < 2 || strlen(inputtextsave) > 32)
	    		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Причина от 2 до 32 символов");
	    
		    new
		        query_getnick[70];

			format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
			new Cache:result = mysql_query(mysql, query_getnick);

			if(cache_get_row_count(mysql))
			{
			    new nickname[MAX_PLAYER_NAME];
				cache_get_row(0, 0, nickname, mysql);
				
				if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
				{
					new online[40];
					format(online, sizeof online, "%d %s", GetPlayerID(nickname), inputtextsave);
				    callcmd::uninvite(playerid, online);
				}
				else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
				{
					new offline[60];
					format(offline, sizeof offline, "%s %s", nickname, inputtextsave);
				    callcmd::uninviteoff(playerid, offline);
				}
			}
			else
			    SendClientMessage(playerid, COLOR_GREY, !"Произошла ошибка в базе данных");
			    


		    cache_delete(result, mysql);
		}
		case 925:
		{
			if(!response)
			{
			    new
			        query_getnick[90];

				format(query_getnick, sizeof query_getnick, "SELECT `NickName`, `FWarns`, `v_Days` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
				    new nickname[MAX_PLAYER_NAME], warns, vac;
					cache_get_row(0, 0, nickname, mysql);
					warns = cache_get_row_int(0, 1, mysql);
					vac = cache_get_row_int(0, 2, mysql);

					if(IsAGang(playerid) || IsAMafia(playerid))
						ShowPlayerDialogEx(playerid, 929, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Уволить сотрудника", !"Далее", !"Назад");

					else
					{
						if(vac)
						    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске");

						if(!warns)
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск", !"Далее", !"Назад");

						else
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск\n{FF7319}5.{FFFFFF} Снять выговор", !"Далее", !"Назад");

					}
				}
				else
				    SendClientMessage(playerid, COLOR_GREY, !"Произошла ошибка в базе данных");

			    cache_delete(result, mysql);
			    return 1;
			}

			if(strlen(inputtextsave) < 2 || strlen(inputtextsave) > 32)
	    		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Причина от 2 до 32 символов");

		    new
		        query_getnick[70];

			format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
			new Cache:result = mysql_query(mysql, query_getnick);

			if(cache_get_row_count(mysql))
			{
			    new nickname[MAX_PLAYER_NAME];
				cache_get_row(0, 0, nickname, mysql);

				if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
				{
					new online[40];
					format(online, sizeof online, "%d %s", GetPlayerID(nickname), inputtextsave);
				    callcmd::fwarn(playerid, online);
				}
				else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
				{
					new offline[60];
					format(offline, sizeof offline, "%s %s", nickname, inputtextsave);
				    callcmd::fwarnoff(playerid, offline);
				}
			}
			else
			    SendClientMessage(playerid, COLOR_GREY, !"Произошла ошибка в базе данных");

		    cache_delete(result, mysql);
		}
		case 926:
		{
			if(!response)
			{
			    new
			        query_getnick[90];

				format(query_getnick, sizeof query_getnick, "SELECT `NickName`, `FWarns`, `v_Days` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
				new Cache:result = mysql_query(mysql, query_getnick);

				if(cache_get_row_count(mysql))
				{
				    new nickname[MAX_PLAYER_NAME], warns, vac;
					cache_get_row(0, 0, nickname, mysql);
					warns = cache_get_row_int(0, 1, mysql);
					vac = cache_get_row_int(0, 2, mysql);

					if(IsAGang(playerid) || IsAMafia(playerid))
						ShowPlayerDialogEx(playerid, 929, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Уволить сотрудника", !"Далее", !"Назад");
						
					else
					{
						if(vac)
						    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок находится в отпуске");

						if(!warns)
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск", !"Далее", !"Назад");

						else
							ShowPlayerDialogEx(playerid, 922, DIALOG_STYLE_LIST, nickname, !"{FF7319}1.{FFFFFF} Информация о сотруднике\n{FF7319}2.{FFFFFF} Выдать выговор\n{FF7319}3.{FFFFFF} Уволить сотрудника\n{FF7319}4.{FFFFFF} Отправить в отпуск\n{FF7319}5.{FFFFFF} Снять выговор", !"Далее", !"Назад");

					}
				}
				else
				    SendClientMessage(playerid, COLOR_GREY, !"Произошла ошибка в базе данных");

			    cache_delete(result, mysql);
			    return 1;
			}
			
			if(strval(inputtextsave) < 1 || strval(inputtextsave) > 30)
	    		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное количество дней");

		    new
		        query_getnick[70];

			format(query_getnick, sizeof query_getnick, "SELECT `NickName` FROM `accounts` WHERE `ID` = '%d' LIMIT 1", temp_lmenu_sel[playerid]);
			new Cache:result = mysql_query(mysql, query_getnick);

			if(cache_get_row_count(mysql))
			{
			    new nickname[MAX_PLAYER_NAME];
				cache_get_row(0, 0, nickname, mysql);

				if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
				{
					new vacation[60];
					format(vacation, sizeof vacation, "%d %d", GetPlayerID(nickname), strval(inputtextsave));
			    	callcmd::vacation(playerid, vacation);
				}
				
				else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок оффлайн");

			}
			else
			    SendClientMessage(playerid, COLOR_GREY, !"Произошла ошибка в базе данных");

		    cache_delete(result, mysql);
		}
		case 914:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");
				
			temp_lmenu_rang[playerid] = listitem+1;
			
			ShowPlayerDialogEx(playerid, 917, DIALOG_STYLE_LIST, !"Выберите пол", !"Мужской\nЖенский", !"Далее", !"Назад");
			
		}
		case 915:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);
		        
			new fractionid = PI[playerid][pFraction]-1;

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

			new
			    frmt_rank_name[700];

			strcat(frmt_rank_name, "{FFFFFF}№. Название\t{FFFFFF}Мужской\t{FFFFFF}Женский\n");
					
			if(listitem == 0)
			{
				for(new i; i < 9; i++)
					format(frmt_rank_name, sizeof frmt_rank_name, "%s{FF7319}%d. {FFFFFF}%s\t{00a768}%d\t{00a768}%d\n", frmt_rank_name, i+1, gPrezRankName[i], OrgInfo[fractionid][oMSkins][i], OrgInfo[fractionid][oWSkins][i]);

				new
				    frmt_rank_last[270];
				    
				format(frmt_rank_last, sizeof frmt_rank_last, "{FF7319}10. {FFFFFF}%s\t{00a768}%d\t{00a768}%d\n{FF7319}11. {FFFFFF}%s\t{00a768}%d\t{00a768}%d", gFractionRankName[fractionid][9], OrgInfo[fractionid][oMSkins][9], OrgInfo[fractionid][oWSkins][9], gFractionRankName[fractionid][10], OrgInfo[fractionid][oMSkins][10], OrgInfo[fractionid][oWSkins][10]);
				strcat(frmt_rank_name, frmt_rank_last);
				
                ShowPlayerDialogEx(playerid, 914, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить форму сотрудникам", frmt_rank_name, !"Далее", !"Назад");
			}
			else if(listitem == 1)
			{
				for(new i; i < 10; i++)
					format(frmt_rank_name, sizeof frmt_rank_name, "%s{FF7319}%d. {FFFFFF}%s\t{00a768}%d\t{00a768}%d\n", frmt_rank_name, i+1, gFractionRankName[fractionid][i], OrgInfo[fractionid][oMSkins][i], OrgInfo[fractionid][oWSkins][i]);

                ShowPlayerDialogEx(playerid, 914, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить форму сотрудникам", frmt_rank_name, !"Далее", !"Назад");
			}
		}
		case 917:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");
				
			new
				fid = PI[playerid][pFraction]-1,
				frmt_skinlist[70];
				
			temp_lmenu_sex[playerid] = listitem+1;

			if(listitem == 0)
			{
				for(new i; i < 15; i++)
				    if(gFractionSkinMan[fid][i] != 0)
				    	format(frmt_skinlist, sizeof frmt_skinlist, "%s%d\n", frmt_skinlist, gFractionSkinMan[fid][i]);
					
                ShowPlayerDialogEx(playerid, 918, DIALOG_STYLE_LIST, !"Выберите номер скина", frmt_skinlist, !"Выбрать", !"Назад");
			}
			if(listitem == 1)
			{
				for(new i; i < 4; i++)
				    if(gFractionSkinWomen[fid][i] != 0)
				    	format(frmt_skinlist, sizeof frmt_skinlist, "%s%d\n", frmt_skinlist, gFractionSkinWomen[fid][i]);

                ShowPlayerDialogEx(playerid, 918, DIALOG_STYLE_LIST, !"Выберите номер скина", frmt_skinlist, !"Выбрать", !"Назад");
			}
		}
		case 918:
		{
		    if(!response)
		        return callcmd::lmenu(playerid);

			if(!PI[playerid][pFraction])
			    return SendClientMessage(playerid, COLOR_GREY, !"Вы не состоите во фракции");

			if((PI[playerid][pFraction] != 1 || PI[playerid][pFraction] <= 7 && PI[playerid][pFraction] >= 10) && PI[playerid][pSubfraction] && PI[playerid][pRank] != 11)
				return SendClientMessage(playerid, COLOR_GREY, !"Меню доступно только министру.");

			new
				fid = PI[playerid][pFraction]-1,
				rang = temp_lmenu_rang[playerid]-1,
				sex = temp_lmenu_sex[playerid],
				frmt_msg[120 + MAX_PLAYER_NAME],
				query_skin[190],
				data[70];
				
			if(sex == 1)
			{
				OrgInfo[fid][oMSkins][rang] = gFractionSkinMan[fid][listitem];

				for(new i; i < 11; i++)
				{
					if(!i) format(data, sizeof data, "%d", OrgInfo[fid][oMSkins][i]);
					else format(data, sizeof data, "%s|%d", data, OrgInfo[fid][oMSkins][i]);
				}
				
				format(query_skin, sizeof query_skin, "UPDATE `orginfo` SET `skins_men` = '%s' WHERE `fraction` = '%d'", data, fid+1);
				mysql_tquery(mysql, query_skin);

				format(frmt_msg, sizeof frmt_msg, "[F] %s изменил форму мужского пола для должности \"%s\" на %d номер", gFractionRankName[fid][PI[playerid][pRank]-1], gFractionRankName[fid][rang], OrgInfo[fid][oMSkins][rang]);
				FractionChat(fid+1, 0x4682B4AA, frmt_msg);
				
     			foreach(new i : Player)
				{
					if(PI[i][pFraction] == PI[playerid][pFraction] && PI[i][pRank] == rang+1 && PI[i][pSex] == 1)
					{
						if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
							continue;

						PI[i][pFractionSkin] = OrgInfo[fid][oMSkins][rang];
						UpdatePlayerData(i, "FractionSkin", PI[i][pFractionSkin]);
						SendClientMessage(i, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Скин изменится после перезахода");
					}
				}

				format(query_skin, sizeof query_skin, "UPDATE `accounts` SET `FractionSkin` = '%d' WHERE `Fraction` = '%d' AND `Rank` = '%d' AND `Sex` = '1'", OrgInfo[fid][oMSkins][rang], fid+1, rang+1);
				mysql_tquery(mysql, query_skin);
			}
			else if(sex == 2)
			{
			    OrgInfo[fid][oWSkins][rang] = gFractionSkinWomen[fid][listitem];

				for(new i; i < 11; i++)
				{
					if(!i) format(data, sizeof data, "%d", OrgInfo[fid][oWSkins][i]);
					else format(data, sizeof data, "%s|%d", data, OrgInfo[fid][oWSkins][i]);
				}

				format(query_skin, sizeof query_skin, "UPDATE `orginfo` SET `skins_women` = '%s' WHERE `fraction` = '%d'", data, fid+1);
				mysql_tquery(mysql, query_skin);

				format(frmt_msg, sizeof frmt_msg, "[F] %s изменил форму женского пола для должности \"%s\" на %d номер", gFractionRankName[fid][PI[playerid][pRank]-1], gFractionRankName[fid][rang], OrgInfo[fid][oWSkins][rang]);
				FractionChat(fid+1, 0x4682B4AA, frmt_msg);
						
     			foreach(new i : Player)
				{
					if(PI[i][pFraction] == PI[playerid][pFraction] && PI[i][pRank] == rang+1 && PI[i][pSex] == 2)
					{
						if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
							continue;
						
						PI[i][pFractionSkin] = OrgInfo[fid][oWSkins][rang];
						UpdatePlayerData(i, "FractionSkin", PI[i][pFractionSkin]);
						SendClientMessage(i, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Скин изменится после перезахода");
					}
				}
				
				format(query_skin, sizeof query_skin, "UPDATE `accounts` SET `FractionSkin` = '%d' WHERE `Fraction` = '%d' AND `Rank` = '%d' AND `Sex` = '2'", OrgInfo[fid][oWSkins][rang], fid+1, rang+1);
				mysql_tquery(mysql, query_skin);
			}
			
			new
			    frmt_rank_name[700];

			strcat(frmt_rank_name, "{FFFFFF}№. Название\t{FFFFFF}Мужской\t{FFFFFF}Женский\n");


			if(PI[playerid][pFraction] == 10 && !PI[playerid][pSubfraction])
				return ShowPlayerDialogEx(playerid, 915, DIALOG_STYLE_LIST, !"Выберите фракцию", !"{FF7319}1.{FFFFFF} Правительство\n{FF7319}2.{FFFFFF} Мэрии", !"Далее", !"Назад");

			else if(PI[playerid][pFraction] != 10 && !PI[playerid][pSubfraction])
			{
				for(new i; i < gFractionRankCount[PI[playerid][pFraction]-1]; i++)
					format(frmt_rank_name, sizeof frmt_rank_name, "%s{FF7319}%d. {FFFFFF}%s\t{00a768}%d\t{00a768}%d\n", frmt_rank_name, i+1, gFractionRankName[fid][i], OrgInfo[fid][oMSkins][i], OrgInfo[fid][oWSkins][i]);
			}

	        ShowPlayerDialogEx(playerid, 914, DIALOG_STYLE_TABLIST_HEADERS, !"Назначить форму сотрудникам", frmt_rank_name, !"Далее", !"Назад");
			temp_lmenu_rang[playerid] = 0;
			temp_lmenu_sex[playerid] = 0;
			return 1;
		}
		case 757:
		{
		    if(!response) return 1;
			if(PI[playerid][pFraction] != 8) return 1;
			    
			new target = temp_division_receiver[playerid]-1;
			if(!IsPlayerConnected(target) || playerid == target) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");
			if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target)) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");
			if(PI[target][pFraction] != PI[playerid][pFraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");
		    if(PI[playerid][pSubfraction] > 0 || PI[playerid][pRank] != 11)
		        if(PI[target][pSubfraction] != PI[playerid][pSubfraction])
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей подфракции");

			if(PI[target][pRank] >= PI[playerid][pRank]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
			new frmt_division_message[120];
			
			format(frmt_division_message, sizeof frmt_division_message, "Вы изменили подразделение игроку %s на \"%s\"", PN(target), gDivisionName[listitem]);
			SendClientMessage(playerid, COLOR_GREEN, frmt_division_message);

			format(frmt_division_message, sizeof frmt_division_message, "%s изменил Вам подразделение на \"%s\"", PN(playerid), gDivisionName[listitem]);
			SendClientMessage(target, COLOR_GREEN, frmt_division_message);
			
			PI[target][pDivision] = listitem+1;
			UpdatePlayerData(target, "Division", PI[target][pDivision]);
			return 1;
		}
		case 763:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 11)
			    return 1;

			new
			    target = temp_division_receiver[playerid]-1;

			if(!IsPlayerConnected(target) || playerid == target)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID");

			if(GetPlayerDistanceToPlayer(playerid, target) > 3.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы далеко друг от друга");

			if(PI[target][pFraction] != PI[playerid][pFraction])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит в вашей организации");

			if(PI[target][pRank] >= PI[playerid][pRank])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			new
				frmt_division_message[120];

			format(frmt_division_message, sizeof frmt_division_message, "Вы изменили подразделение игроку %s на \"%s\"", PN(target), gTagName[listitem]);
			SendClientMessage(playerid, COLOR_GREEN, frmt_division_message);

			format(frmt_division_message, sizeof frmt_division_message, "%s изменил Вам подразделение на \"%s\"", PN(playerid), gTagName[listitem]);
			SendClientMessage(target, COLOR_GREEN, frmt_division_message);

			PI[target][pDivision] = listitem+1;
			UpdatePlayerData(target, "Division", PI[target][pDivision]);


		}
		
		case 758:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 8 || PI[playerid][pRank] != 11)
			    return 1;
			    
			ShowPlayerDialogEx(playerid, 759, DIALOG_STYLE_LIST, gDivisionName[listitem], !"{FF7319}1.{FFFFFF} Переименовать\n{FF7319}2.{FFFFFF} Доступ к складу", !"Далее", !"Отмена");
            SetPVarInt(playerid, "seldivision", listitem);
            
			/*new
			    frmt_division_rename[130];
			    
			format(frmt_division_rename, sizeof frmt_division_rename, "\n\n{FFFFFF}Введите новое название подразделения \"\"\n\n{AEAEAE}Оно должно быть от 2-х до 6-и символов\n\n", gDivisionName[listitem]);
			ShowPlayerDialogEx(playerid, 759, DIALOG_STYLE_INPUT, !"Смена названия", frmt_division_rename, !"Готово", !"Отмена");
			*/
		}
		case 759:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 8 || PI[playerid][pRank] != 11)
			    return 1;

			new
			    divisionid = GetPVarInt(playerid, "seldivision");

			switch(listitem)
			{
				case 0:
				{
					new
					    frmt_division_rename[150];

					format(frmt_division_rename, sizeof frmt_division_rename, "\n\n{FFFFFF}Введите новое название подразделения \"%s\"\n\n{AEAEAE}Оно должно быть от 2-х до 6-и символов\n\n", gDivisionName[divisionid]);
					ShowPlayerDialogEx(playerid, 762, DIALOG_STYLE_INPUT, !"Смена названия", frmt_division_rename, !"Готово", !"Отмена");
				}
				case 1:
				{
					new
					    frmt_division_guns[260],
						gunid[5] = {23, 24, 29, 25, 31};


					for(new i; i < 5; i++)
					{
						new
							gunname[24],
							status[12];
							
						if(gDivisionGun[divisionid][i])
						    strcat(status, "{33AA33}+");
						    
						else
						    strcat(status, "{FF0000}-");
						    
						GetWeaponName(gunid[i], gunname, 24);
						format(frmt_division_guns, sizeof frmt_division_guns, "%s{FF7319}%d.{FFFFFF} %s [%s{FFFFFF}]\n", frmt_division_guns, i+1, gunname, status);
					}
					ShowPlayerDialogEx(playerid, 761, DIALOG_STYLE_LIST, !"Доступ к оружию", frmt_division_guns, !"Изменить", !"Отмена");
					
				}
			}
			return 1;
		}
		case 778:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 11 || PI[playerid][pRank] != 10)
			    return 1;

			new
			    frmt_division_rename[130];

			format(frmt_division_rename, sizeof frmt_division_rename, "\n\n{FFFFFF}Введите новое название подразделения \"%s\"\n\n{AEAEAE}Оно должно быть от 2-х до 6-и символов\n\n", gTagName[listitem]);
			ShowPlayerDialogEx(playerid, 779, DIALOG_STYLE_INPUT, !"Смена названия", frmt_division_rename, !"Готово", !"Отмена");
			SetPVarInt(playerid, "seldivision", listitem);

		}
		case 779:
		{
		    if(!response)
		        return 1;
		        
			if(PI[playerid][pFraction] != 11 || PI[playerid][pRank] != 10)
			    return 1;

			new
			    divisionid = GetPVarInt(playerid, "seldivision");

			if(!strlen(inputtext) || strlen(inputtext) < 2 || strlen(inputtext) > 6)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Название подразделения должно содержать от 2 до 6 символов");
				
				new
				    frmt_division_rename[130];

				format(frmt_division_rename, sizeof frmt_division_rename, "\n\n{FFFFFF}Введите новое название подразделения \"%s\"\n\n{AEAEAE}Оно должно быть от 2-х до 6-и символов\n\n", gTagName[divisionid]);
				ShowPlayerDialogEx(playerid, 779, DIALOG_STYLE_INPUT, !"Смена названия", frmt_division_rename, !"Готово", !"Отмена");
				return 1;

			}
			if(strfind(inputtext,"|") != -1 || isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");


			SetString(gTagName[divisionid], inputtext);

			new
				query_update_division[160];

			format(query_update_division, sizeof query_update_division, "UPDATE `tags` SET `name` = '%s' WHERE `id` = '%d'", inputtext, divisionid+1);
			mysql_tquery(mysql, query_update_division);

			SendClientMessage(playerid, COLOR_GREEN, !"Вы изменили название подразделения");
		}
		case 781:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 11)
			    return 1;

			if(PI[playerid][pRank] < 3)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");
	    
			new
			    fractionid;
			    
			switch(listitem)
			{
			    case 0: fractionid = 2;
				case 1: fractionid = 3;
				case 2: fractionid = 4;
				case 3: fractionid = 5;
				case 4: fractionid = 6;
    			case 5: fractionid = 12;
    			case 6: fractionid = 13;
    			case 7: fractionid = 14;
			}
			
			new
			    frmt_ears_text[85];
			    
			format(frmt_ears_text, sizeof frmt_ears_text, "{7AC71F}[Успешно] {FFFFFF}Вы включили подслушку организации %s", gFractionName[fractionid-1]);
	        SendClientMessage(playerid, COLOR_WHITE, frmt_ears_text);
	        
		    pTemp[playerid][pEars] = fractionid;
		}
		case 783:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 11)
			    return 1;

			if(PI[playerid][pRank] < 3)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			switch(listitem)
			{
			    case 0:
			    {
				    pTemp[playerid][pDisguse] = 2;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 102);
					    
					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 195);

					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);
					
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"The Ballas\"");
				}
				case 1:
				{
				    pTemp[playerid][pDisguse] = 3;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 106);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 13);

					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);
					
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Grove Street\"");
				}
				case 2:
				{
				    pTemp[playerid][pDisguse] = 4;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 115);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 226);

					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);
					    
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Varios Los Aztecas\"");
				}
				case 3:
				{
				    pTemp[playerid][pDisguse] = 5;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 108);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 90);

					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);
					
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Los Santos Vagos\"");
				}
				case 4:
				{
				    pTemp[playerid][pDisguse] = 6;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 175);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 56);
					    
					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);
					
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"The Rifa\"");
				}
				case 5:
				{
				    pTemp[playerid][pDisguse] = 12;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 117);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 263);
					    
					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);
					
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Yakuza\"");
				}
				case 6:
				{
				    pTemp[playerid][pDisguse] = 13;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 124);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 40);

					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);

					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"LCN\"");
				}
				case 7:
				{
				    pTemp[playerid][pDisguse] = 14;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 111);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 12);

					SetPlayerHealth(playerid, 0);
					SetPlayerColor(playerid, gFractionColor[pTemp[playerid][pDisguse] - 1]);

					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Колумбийская мафия\"");
				}
				case 8:
				{
				    pTemp[playerid][pDisguse] = 15;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 46);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 69);

					SetPlayerHealth(playerid, 0);
                    SetPlayerColor(playerid, 0xFFFFFF11);
                    
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Гражданская одежда №1\"");
				}
				case 9:
				{
				    pTemp[playerid][pDisguse] = 15;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 101);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 41);

					SetPlayerHealth(playerid, 0);
                    SetPlayerColor(playerid, 0xFFFFFF11);
                    
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Гражданская одежда №2\"");
				}
				case 10:
				{
				    pTemp[playerid][pDisguse] = 15;
                    pTemp[playerid][pDOldSkin] = GetPlayerSkin(playerid);

					if(PI[playerid][pSex] == 1)
					    SetPlayerSkinEx(playerid, 23);

					else if(PI[playerid][pSex] == 2)
					    SetPlayerSkinEx(playerid, 88);

					SetPlayerHealth(playerid, 0);
                    SetPlayerColor(playerid, 0xFFFFFF11);
                    
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы выбрали маскировку \"Гражданская одежда №3\"");
				}
			}

		}
		case 761:
		{
		    if(!response) return 1;
			if(PI[playerid][pFraction] != 8 || PI[playerid][pRank] != 11) return 1;
			new divisionid = GetPVarInt(playerid, "seldivision");
			    
            if(gDivisionGun[divisionid][listitem])
				gDivisionGun[divisionid][listitem] = 0, SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы запретили брать оружие выбранному подразделению");

			else
			    gDivisionGun[divisionid][listitem] = 1, SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы разрешили брать оружие выбранному подразделению");
			    
			new
				query_update_division[160],
				data[24];
				
			for(new i; i < 5; i++)
			{
				if(!i) format(data, sizeof data, "%d", gDivisionGun[divisionid][i]);
				else format(data, sizeof data, "%s|%d", data, gDivisionGun[divisionid][i]);
			}

			format(query_update_division, sizeof query_update_division, "UPDATE `divisions` SET `guns` = '%s' WHERE `id` = '%d'", data, divisionid+1);
			mysql_tquery(mysql, query_update_division);


			new
			    frmt_division_guns[260],
				gunid[5] = {23, 24, 29, 25, 31};


			for(new i; i < 5; i++)
			{
				new
					gunname[24],
					status[12];

				if(gDivisionGun[divisionid][i]) strcat(status, "{33AA33}+");
				else strcat(status, "{FF0000}-");

				GetWeaponName(gunid[i], gunname, 24);
				format(frmt_division_guns, sizeof frmt_division_guns, "%s{FF7319}%d.{FFFFFF} %s [%s{FFFFFF}]\n", frmt_division_guns, i+1, gunname, status);
			}
			ShowPlayerDialogEx(playerid, 761, DIALOG_STYLE_LIST, !"Доступ к оружию", frmt_division_guns, !"Изменить", !"Отмена");
			return 1;
		}
		case 762:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 8 || PI[playerid][pRank] != 11)
			    return 1;
			    
			new
			    divisionid = GetPVarInt(playerid, "seldivision");

			if(!strlen(inputtext) || strlen(inputtext) < 2 || strlen(inputtext) > 6)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Название подразделения должно содержать от 2 до 6 символов");
				new
				    frmt_division_rename[130];

				format(frmt_division_rename, sizeof frmt_division_rename, "\n\n{FFFFFF}Введите новое название подразделения \"%s\"\n\n{AEAEAE}Оно должно быть от 2-х до 6-и символов\n\n", gDivisionName[listitem]);
				ShowPlayerDialogEx(playerid, 762, DIALOG_STYLE_INPUT, !"Смена названия", frmt_division_rename, !"Готово", !"Отмена");
				return 1;

			}
			if(strfind(inputtext,"|") != -1 || isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");


			SetString(gDivisionName[divisionid], inputtext);
			
			new
				query_update_division[160];

			format(query_update_division, sizeof query_update_division, "UPDATE `divisions` SET `name` = '%s' WHERE `id` = '%d'", inputtext, divisionid+1);
			mysql_tquery(mysql, query_update_division);
			
			SendClientMessage(playerid, COLOR_GREEN, !"Вы изменили название подразделения");
			return 1;
		}
		case 511:
		{
		    if(!response)
		        return 1;
		        
			if(PI[playerid][pFraction] != 9 || PI[playerid][pRank] != 11)
			    return 1;
			    
			if(listitem == 0)
			{
			    new
					frmt_advert_message[150];
					
				format(frmt_advert_message, sizeof frmt_advert_message, "{FFFFFF}Введите новую стоимость подачи объявления\nТекущая: {008B00}%d$\n\n{AFAFAF}Сумма должна быть от 200$ до 300$", gAdvertPrice);
			    ShowPlayerDialogEx(playerid, 512, DIALOG_STYLE_INPUT, !"Объявление", frmt_advert_message, !"Установить", !"Отмена");
			    
			}
			else if(listitem == 1)
			{
			    new
					frmt_ether_message[150];

				format(frmt_ether_message, sizeof frmt_ether_message, "{FFFFFF}Введите новую стоимость звонка в эфир\nТекущая: {008B00}%d$\n\n{AFAFAF}Сумма должна быть 50$ до 150$", gEtherPrice);
			    ShowPlayerDialogEx(playerid, 513, DIALOG_STYLE_INPUT, !"Эфир", frmt_ether_message, !"Установить", !"Отмена");
			}
			return 1;
		}
		case 512:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 9 || PI[playerid][pRank] != 11)
			    return 1;
			    
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 200 || strval(inputtext) > 300)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная стоимость (от 200$ до 300$)");
			    
			    new
					frmt_advert_message[150];

				format(frmt_advert_message, sizeof frmt_advert_message, "{FFFFFF}Введите новую стоимость подачи объявления\nТекущая: {008B00}%d$\n\n{AFAFAF}Сумма должна быть 200$ до 300$", gAdvertPrice);
			    ShowPlayerDialogEx(playerid, 512, DIALOG_STYLE_INPUT, !"Объявление", frmt_advert_message, !"Установить", !"Отмена");
			    return 1;
			}
			
			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			gAdvertPrice = strval(inputtext);
			SendClientMessage(playerid, COLOR_GREEN, !"Новая стоимость за подачу объявления установлена");
			return 1;
		}
		case 513:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 9 || PI[playerid][pRank] != 11)
			    return 1;

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 50 || strval(inputtext) > 150)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная стоимость (от 50$ до 150$)");

			    new
					frmt_ether_message[150];

				format(frmt_ether_message, sizeof frmt_ether_message, "{FFFFFF}Введите новую стоимость звонка в эфир\nТекущая: {008B00}%d$\n\n{AFAFAF}Сумма должна быть 50$ до 150$", gEtherPrice);
			    ShowPlayerDialogEx(playerid, 513, DIALOG_STYLE_INPUT, !"Эфир", frmt_ether_message, !"Установить", !"Отмена");
			    return 1;
			}

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			gEtherPrice = strval(inputtext);
			SendClientMessage(playerid, COLOR_GREEN, !"Новая стоимость за звонок в эфир установлена");
			return 1;
		}
		case 514:
		{
		    if(!response)
		        return 1;
			
			new
			    ndial = pTemp[playerid][pEtherCall]-1;
			    
			if(PI[playerid][pMoney] < gEtherPrice)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно денег");

			if(!gNewsDialing[ndial])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Звонки не принимаются");

			if(gNewsDialee[ndial] != INVALID_PLAYER_ID)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Линия занята");
				
			GiveMoney(playerid, -gEtherPrice, "звонок в эфир");
			OrgInfo[8][oMoney] += gEtherPrice;
             
            pTemp[playerid][pDial] = ndial+1;
            pTemp[playerid][pEtherCall] = 0;
            
            
			//gNewsDialMoney[ndial] += gNewsDialPrice[ndial];
			
			//SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
			//SetPlayerAttachedObject(playerid,0,330,6);
			//gNewsDialee[ndial] = playerid;
			return 1;
		}
		case 515:
		{
		    if(!response)
		        return 1;
		        
			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(!PI[playerid][pSubfraction])
			    return 1;

			if(PI[playerid][pRank] < 5)
			    return 1;

			if(listitem < 40)
			{
			    new
					nickname[MAX_PLAYER_NAME];

			    sscanf(inputtextsave, "{s[6]}s[24]", nickname);
			    
				if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не найден");

				new
					target = GetPlayerID(nickname);

				SetPlayerSpecialAction(target, SPECIAL_ACTION_USECELLPHONE);
				SetPlayerAttachedObject(target, 9, 330, 6);
                gNewsDialee[PI[playerid][pSubfraction]-1] = target;
                SendClientMessage(target, COLOR_GREEN, !"Радиоцентр принял ваш звонок");
                
                new
                    frmt_message[68];
                    
				format(frmt_message, sizeof frmt_message, "Вы приняли звонок от %s", PN(target));
				SendClientMessage(playerid, COLOR_GREEN, frmt_message);
			}
			else if(listitem == 40)
			{
				new
				    frmt_dial_list[1000],
					dial_list;

			    for(new i = pTemp[playerid][pDialLast], j = GetPlayerPoolSize(); i <= j; i++)
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
			}
			return 1;
		}
		case 529:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 9)
			    return 1;

			if(PI[playerid][pRank] < 8)
			    return 1;

			new
			    subid = PI[playerid][pSubfraction]-1,
				total_board;

		    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 1723.2936, 182.3722, 1125.9989))
			    return 1;
				
			if(!strlen(inputtext) || strlen(inputtext) < 2 || strlen(inputtext) > 90)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткий/длинный текст");


			for(new i; i < strlen(inputtext); i ++)
			{
			    if(inputtext[i] == '|')
			        total_board++;
			}
	
		    if(total_board >= 5)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы используете слишком много символов переноса");

	
			if(strfind(inputtext,"|") != -1)
			{
			    new
			        board_text[100];

                strreplace(inputtext, '|', '\n');
				format(board_text, sizeof board_text, "%s", inputtext);
				SetDynamicObjectMaterialText(gBoard[subid], 0, board_text, 130, "Ariel", 50, 1, 0xFF000000, 0x00000000, 1);
				return 1;
			}

            SetDynamicObjectMaterialText(gBoard[subid], 0, inputtext, 130, "Ariel", 50, 1, 0xFF000000, 0x00000000, 1);
		}
		case 534:
		{
		    if(!response)
		        return 1;
		        
			if(pTemp[playerid][pQuestion])
			    return 1;
			    
			if(!strlen(inputtext) || strlen(inputtext) < 2 || strlen(inputtext) > 70)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткий/длинный текст");
				
			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найден запрещенный символ");

			new
			    frmt_question_message[128];
				    
       		foreach(new i : Player)
			{
			    if(!PI[i][pID] || PI[i][pFraction] != 10 || PI[i][pSubfraction] != pTemp[playerid][pHallQuestion])
					continue;
					
				format(frmt_question_message, sizeof frmt_question_message, "[R] Вопрос от %s[%d]: %s", PN(playerid), playerid, inputtext);
				
				SendClientMessage(i, 0x4682B4AA, frmt_question_message);
			}
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы отправили вопрос. Ожидайте ответа");
			
            pTemp[playerid][pQuestion] = true;
		}
		case 612:
		{
		    if(!response)
		        return 1;
		        
			if(!IsAGang(playerid))
				return 1;
				
			new
			    gangid = PI[playerid][pFraction] - 2;
				
			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

			switch(listitem)
			{
				case 0: ShowPlayerDialogEx(playerid, 613, DIALOG_STYLE_LIST, !"Общак", !"Положить ед. оружия\nВзять ед. оружия", !"Далее", !"Назад");
				case 1: ShowPlayerDialogEx(playerid, 626, DIALOG_STYLE_LIST, !"Общак", !"Положить патроны\nВзять патроны", !"Далее", !"Назад");
				case 2: ShowPlayerDialogEx(playerid, 619, DIALOG_STYLE_LIST, !"Общак", !"Положить деньги\nВзять деньги", !"Далее", !"Назад");
				case 3: ShowPlayerDialogEx(playerid, 629, DIALOG_STYLE_LIST, !"Общак", !"Положить наркотики\nВзять наркотики", !"Далее", !"Назад");
			}
		}
		case 613:
		{
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 612, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;
				
			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 614, DIALOG_STYLE_INPUT, !"Положить ед.оружия", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] < gGangStorageRank[gangid])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");
				        
					ShowPlayerDialogEx(playerid, 625, DIALOG_STYLE_INPUT, !"Взять ед.оружия", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}

			}
		}
		case 614:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;
				
            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 500)");

			if(PI[playerid][pPackets] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно ед. оружия");

			if(gGangStorage[gangid][0] + strval(inputtext) > 50000)
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак полон");
                
			PI[playerid][pPackets] -= strval(inputtext);
			UpdatePlayerData(playerid, "Packets", PI[playerid][pPackets]);
			
			gGangStorage[gangid][0] += strval(inputtext);
			UpdateTextGang();

			new
			    frmt_storage[85], query_storage[80];
			    
			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `gun` = '%d' WHERE `id` = %d", gGangStorage[gangid][0], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} ед. оружия", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил ед. оружия в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 625:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

			if(!gGangStorageStatus[gangid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");
			    
		    if(PI[playerid][pRank] < gGangStorageRank[gangid])
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
			
			if(gGangStorage[gangid][0] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно ед. оружия");

			PI[playerid][pPackets] += strval(inputtext);
			UpdatePlayerData(playerid, "Packets", PI[playerid][pPackets]);

            gGangStorage[gangid][0] -= strval(inputtext);
            UpdateTextGang();
            
			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `gun` = '%d' WHERE `id` = %d", gGangStorage[gangid][0], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} ед. оружия", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял ед. оружия из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

		}
		case 626:
		{
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 612, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;
				
			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 617, DIALOG_STYLE_INPUT, !"Положить патроны", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] < gGangStorageRank[gangid])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

					ShowPlayerDialogEx(playerid, 618, DIALOG_STYLE_INPUT, !"Взять патроны", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}
			}

		}
		case 617:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");
				
			if(strval(inputtext) < 1 || strval(inputtext) > 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 500)");

			if(PI[playerid][pMats] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно патронов");

			if(gGangStorage[gangid][1] + strval(inputtext) > 50000)
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак полон");
                
			PI[playerid][pMats] -= strval(inputtext);
			UpdatePlayerData(playerid, "Mats", PI[playerid][pMats]);

            gGangStorage[gangid][1] += strval(inputtext);
            UpdateTextGang();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `ammo` = '%d' WHERE `id` = %d", gGangStorage[gangid][1], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} патронов", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);
			
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил патроны в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

		}
		case 618:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

			if(!gGangStorageStatus[gangid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

		    if(PI[playerid][pRank] < gGangStorageRank[gangid])
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
			if(gGangStorage[gangid][1] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно патронов");
                
			PI[playerid][pMats] += strval(inputtext);
			UpdatePlayerData(playerid, "Mats", PI[playerid][pMats]);

            gGangStorage[gangid][1] -= strval(inputtext);
            UpdateTextGang();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `ammo` = '%d' WHERE `id` = %d", gGangStorage[gangid][1], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} патронов", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);
			
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял патроны из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);

		}
		case 619:
		{
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 612, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 620, DIALOG_STYLE_INPUT, !"Положить деньги", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] != 10)
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только лидеру");

					ShowPlayerDialogEx(playerid, 621, DIALOG_STYLE_INPUT, !"Взять деньги", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}
			}

		}
		case 620:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 100000)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 100000)");

			if(PI[playerid][pMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
                
			GiveMoney(playerid, -strval(inputtext), "склад");

            gGangStorage[gangid][3] += strval(inputtext);
            UpdateTextGang();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `money` = '%d' WHERE `id` = %d", gGangStorage[gangid][3], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} $", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);
			
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил деньги в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 621:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

			if(!gGangStorageStatus[gangid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

		    if(PI[playerid][pRank] != 10)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только лидеру");

			if(strval(inputtext) < 1 || strval(inputtext) > 100000)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 100000)");

			if(gGangStorage[gangid][3] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно денег");
                
			GiveMoney(playerid, strval(inputtext), "склад");
			
            gGangStorage[gangid][3] -= strval(inputtext);
            UpdateTextGang();
            
			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `money` = '%d' WHERE `id` = %d", gGangStorage[gangid][3], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} $", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);
			
		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял деньги из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 629:
		{
		    if(!response)
		        return ShowPlayerDialogEx(playerid, 612, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 623, DIALOG_STYLE_INPUT, !"Положить наркотики", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
			    case 1:
				{
				    if(PI[playerid][pRank] < gGangStorageRank[gangid])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");

					ShowPlayerDialogEx(playerid, 624, DIALOG_STYLE_INPUT, !"Взять наркотики", !"\n\n{FFFFFF}Введите количество\n\n\n", !"Далее", !"Назад");
				}
			}

		}
		case 623:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strval(inputtext) < 1 || strval(inputtext) > 100000)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение (от 1 до 100000)");

			if(PI[playerid][pDrugs] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно наркотиков");

			if(gGangStorage[gangid][2] + strval(inputtext) > 25000)
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак полон");
                
			PI[playerid][pDrugs] -= strval(inputtext);
			UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);

            gGangStorage[gangid][2] += strval(inputtext);
            UpdateTextGang();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `drugs` = '%d' WHERE `id` = %d", gGangStorage[gangid][2], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}положил в общак {FFFFFF}%d{4682B4} грамм наркотиков", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s положил наркотики в общак", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 624:
		{
		    if(!response)
		        return 1;

			if(!IsAGang(playerid))
				return 1;

			new
			    gangid = PI[playerid][pFraction] - 2;

			if(!IsPlayerInDynamicArea(playerid, gGangStockArea) && GetPlayerVirtualWorld(playerid) != gangid+1)
				return 1;
				
			if(!gGangStorageStatus[gangid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

            if(!strlen(inputtext) || !isNumeric(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

		    if(PI[playerid][pRank] < gGangStorageRank[gangid])
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
			
			if(gGangStorage[gangid][2] < strval(inputtext))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В общаке недостаточно наркотиков");
                
			PI[playerid][pDrugs] += strval(inputtext);
			UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);

            gGangStorage[gangid][2] -= strval(inputtext);
            UpdateTextGang();

			new
			    frmt_storage[85], query_storage[80];

			format(query_storage, sizeof query_storage, "UPDATE `gangs` SET `drugs` = '%d' WHERE `id` = %d", gGangStorage[gangid][2], gangid+1);
			mysql_tquery(mysql, query_storage);
			format(frmt_storage, sizeof frmt_storage, "%s {4682B4}взял с общака {FFFFFF}%d{4682B4} грамм наркотиков", PN(playerid), strval(inputtext));
			FractionChat(gangid+2, COLOR_WHITE, frmt_storage);

		    new
				frmt_action[60];

			format(frmt_action, sizeof frmt_action, "%s взял наркотики из общака", PN(playerid));
		    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
		}
		case 436:
		{
			if(!response)
			    return 1;

			if(!IsPlayerInDynamicArea(playerid, gFBIGunArea) && PI[playerid][pFraction] != 11)
				return 1;

            new
				weapon,
				ammo;

			switch(listitem)
			{
			    case 0:
			    {
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

			        if(gFBIWarehouse[0] - 10 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gFBIWarehouse[1] - 20 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(23), weapon, ammo);

					if(ammo > 60 && weapon == 23)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 23, 20);
                    temp_tazer_gun[playerid] = true;

                    gFBIWarehouse[0] -= 10;
                    gFBIWarehouse[1] -= 20;
                    WHDataUpdate();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Silenced Pistol");
			    }
			    case 1:
			    {
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

			        if(gFBIWarehouse[0] - 15 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gFBIWarehouse[1] - 40 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(24), weapon, ammo);

					if(ammo > 120 && weapon == 24)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 24, 40);

                    gFBIWarehouse[0] -= 15;
                    gFBIWarehouse[1] -= 40;
                    WHDataUpdate();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Desert Eagle");
			    }
			    case 2:
			    {
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

			        if(gFBIWarehouse[0] - 15 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gFBIWarehouse[1] - 50 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(29), weapon, ammo);

					if(ammo > 150 && weapon == 29)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 29, 50);

                    gFBIWarehouse[0] -= 15;
                    gFBIWarehouse[1] -= 50;
                    WHDataUpdate();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли MP5");
			    }
			    case 3:
			    {
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

			        if(gFBIWarehouse[0] - 22 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gFBIWarehouse[1] - 50 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(25), weapon, ammo);

					if(ammo > 150 && weapon == 25)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 25, 50);

                    gFBIWarehouse[0] -= 22;
                    gFBIWarehouse[1] -= 50;
                    WHDataUpdate();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Shotgun");
			    }
			    case 4:
			    {
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

			        if(gFBIWarehouse[0] - 20 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gFBIWarehouse[1] - 100 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(31), weapon, ammo);

					if(ammo > 300 && weapon == 31)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 31, 100);

                    gFBIWarehouse[0] -= 20;
                    gFBIWarehouse[1] -= 100;
                    WHDataUpdate();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли M4");
			    }
			    case 5:
			    {
			        if(gFBIWarehouse[0] - 1 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gFBIWarehouse[1] - 1 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(3), weapon, ammo);

					if(ammo > 0)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 3, 1);

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Дубинку");
			    }
		 		case 6:
				{
					SetPlayerHealth(playerid, 100);
					SetArmour(playerid, 100);
					SendClientMessage(playerid, COLOR_GREEN, !"Вы надели Бронежилет");
				}
			}

		}
		case 437:
		{
			if(!response) return 1;
			new divisionid = PI[playerid][pDivision]-1;
			new pdid = -1;
			
			switch(GetPlayerVirtualWorld(playerid))
			{
			    case 3: pdid = 1;
			    case 4: pdid = 2;
			    case 5: pdid = 3;
			}
			
			if(pdid == -1) return 1;
			if(!IsPlayerInDynamicArea(playerid, gPDGunArea[pdid-1]) || PI[playerid][pSubfraction] != pdid) return 1;
			switch(listitem)
			{
			    case 0:
			    {
			        if(timeforcd[playerid] > gettime()) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы можете брать оружие раз в 30 секунд");
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

					if(!PI[playerid][pDivision] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					if(!gDivisionGun[divisionid][0] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
			        if(gPDWarehouse[pdid][0] - 10 <= 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gPDWarehouse[pdid][1] - 20 <= 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

                    _GiveGun(playerid, 23, 20);
                    temp_tazer_gun[playerid] = true;

                    gPDWarehouse[pdid][0] -= 10;
                    gPDWarehouse[pdid][1] -= 20;
                    WHDataUpdate();
	
                    timeforcd[playerid] = 30;
					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Silenced Pistol");
					return 1;
			    }
			    case 1:
			    {
			        if(timeforcd[playerid] > gettime()) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы можете брать оружие раз в 30 секунд");
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

					if(!PI[playerid][pDivision] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					if(!gDivisionGun[divisionid][1] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					
			        if(gPDWarehouse[pdid][0] - 15 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gPDWarehouse[pdid][1] - 40 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

                    _GiveGun(playerid, 24, 40);
                    
                    gPDWarehouse[pdid][0] -= 15;
                    gPDWarehouse[pdid][1] -= 40;
                    WHDataUpdate();

					timeforcd[playerid] = 30;

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Desert Eagle");
					return 1;
			    }
			    case 2:
			    {
			        if(timeforcd[playerid] > gettime()) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы можете брать оружие раз в 30 секунд");
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

					if(!PI[playerid][pDivision] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					if(!gDivisionGun[divisionid][2] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					
			        if(gPDWarehouse[pdid][0] - 15 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gPDWarehouse[pdid][1] - 50 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

                    _GiveGun(playerid, 29, 50);
                    
                    gPDWarehouse[pdid][0] -= 15;
                    gPDWarehouse[pdid][1] -= 50;
                    WHDataUpdate();
                    
                    timeforcd[playerid] = 30;
                    
					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли MP5");
					return 1;
			    }
			    case 3:
			    {
			        if(timeforcd[playerid] > gettime()) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы можете брать оружие раз в 30 секунд");
				    if(PI[playerid][pRank] < 2 )
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

					if(!PI[playerid][pDivision] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					if(!gDivisionGun[divisionid][3] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					
			        if(gPDWarehouse[pdid][0] - 22 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gPDWarehouse[pdid][1] - 50 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

                    _GiveGun(playerid, 25, 50);

                    gPDWarehouse[pdid][0] -= 22;
                    gPDWarehouse[pdid][1] -= 50;
                    WHDataUpdate();
                    
                    timeforcd[playerid] = 30;
                    
					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Shotgun");
					return 1;
			    }
			    case 4:
			    {
			        if(timeforcd[playerid] > gettime()) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы можете брать оружие раз в 30 секунд");
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

					if(!PI[playerid][pDivision] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					if(!gDivisionGun[divisionid][4] && PI[playerid][pRank] != 10) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");
					
			        if(gPDWarehouse[pdid][0] - 20 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gPDWarehouse[pdid][1] - 100 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

                    _GiveGun(playerid, 31, 100);

                    gPDWarehouse[pdid][0] -= 20;
                    gPDWarehouse[pdid][1] -= 100;
                    WHDataUpdate();

                    timeforcd[playerid] = 30;
                    
					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли M4");
					return 1 ;
			    }
			    case 5:
			    {
			        if(timeforcd[playerid] > gettime()) return SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы можете брать оружие раз в 30 секунд");
			        if(gPDWarehouse[pdid][0] - 1 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");
			            
			        if(gPDWarehouse[pdid][1] - 1 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");
						
                    _GiveGun(playerid, 3, 1);
                    
                    timeforcd[playerid] = 30;
					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Дубинку");
					return 1;
			    }
		 		case 6:
				{
					SetPlayerHealth(playerid, 100);
					SetArmour(playerid, 100);
					SendClientMessage(playerid, COLOR_GREEN, !"Вы надели Бронежилет");
					return 1;
				}
			}
		
		}
		case 446:
		{
			if(!response)
			    return 1;

			new mafiaid = GetPlayerVirtualWorld(playerid)-1;

			if(!IsPlayerInDynamicArea(playerid, gMafiaGunArea[mafiaid]) && PI[playerid][pFraction] != 11+mafiaid)
				return 1;

			if(!gMafiaStorageStatus[mafiaid])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Общак закрыт");

		    if(PI[playerid][pRank] < gMafiaStorageRank[mafiaid])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к общаку");
		        
            new
				weapon,
				ammo;

			switch(listitem)
			{
			    case 0:
			    {
			        if(gMafiaStorage[mafiaid][0] - 180 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gMafiaStorage[mafiaid][1] - 70 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(24), weapon, ammo);

					if(ammo > 210 && weapon == 24)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 24, 70);

                    gMafiaStorage[mafiaid][0] -= 180;
                    gMafiaStorage[mafiaid][1] -= 70;
                    UpdateTextMafia();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Desert Eagle");
			    }
			    case 1:
			    {
			        if(gMafiaStorage[mafiaid][0] - 200 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gMafiaStorage[mafiaid][1] - 50 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(29), weapon, ammo);

					if(ammo > 150 && weapon == 29)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 29, 50);

                    gMafiaStorage[mafiaid][0] -= 200;
                    gMafiaStorage[mafiaid][1] -= 50;
                    UpdateTextMafia();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли MP5");
			    }
			    case 2:
			    {
			        if(gMafiaStorage[mafiaid][0] - 280 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gMafiaStorage[mafiaid][1] - 50 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(25), weapon, ammo);

					if(ammo > 150 && weapon == 25)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 25, 50);

					gMafiaStorage[mafiaid][0] -= 280;
					gMafiaStorage[mafiaid][1] -= 50;
					UpdateTextMafia();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Shotgun");
			    }
			    case 3:
			    {
			        if(gMafiaStorage[mafiaid][0] - 350 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gMafiaStorage[mafiaid][1] - 200 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(31), weapon, ammo);

					if(ammo > 400 && weapon == 31)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 31, 200);

                    gMafiaStorage[mafiaid][0] -= 350;
                    gMafiaStorage[mafiaid][1] -= 200;
                    UpdateTextMafia();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли M4");
			    }
			    case 4:
			    {
			        if(gMafiaStorage[mafiaid][0] - 380 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gMafiaStorage[mafiaid][1] - 40 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(33), weapon, ammo);

					if(ammo > 120 && weapon == 33)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 33, 40);

                    gMafiaStorage[mafiaid][0] -= 380;
                    gMafiaStorage[mafiaid][1] -= 40;
                    UpdateTextMafia();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Country Rifle");
			    }

			}
		}
		case 438:
		{
			if(!response)
			    return 1;

			new
			    hallid = -1,
				areaid = -1;

			switch(GetPlayerVirtualWorld(playerid))
			{
			    case 6: hallid = 1, areaid = 0;
			    case 7: hallid = 2, areaid = 1;
			    case 8: hallid = 3, areaid = 2;
			    case 9: hallid = 0, areaid = 3;
			}
			
			if(PI[playerid][pFraction] != 10)
			    return 1;

			if(PI[playerid][pSubfraction] != hallid)
			    return 1;

			if(!IsPlayerInDynamicArea(playerid, gHallGunArea[areaid]))
				return 1;

            new
				weapon,
				ammo;

			switch(listitem)
			{
			    case 0:
			    {
			        if(gHallWarehouse[areaid][0] - 15 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gHallWarehouse[areaid][1] - 40 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(24), weapon, ammo);

					if(ammo > 120 && weapon == 24)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 24, 40);

                    gHallWarehouse[areaid][0] -= 15;
                    gHallWarehouse[areaid][1] -= 40;
                    WHDataUpdate();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Desert Eagle");
			    }
			    case 1:
			    {
				    if(PI[playerid][pRank] < 2)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет доступа к этому оружию");

			        if(gHallWarehouse[areaid][0] - 22 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gHallWarehouse[areaid][1] - 50 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

			        GetPlayerWeaponData(playerid, GetWeaponSlot(25), weapon, ammo);

					if(ammo > 150 && weapon == 25)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 25, 50);

                    gHallWarehouse[areaid][0] -= 22;
                    gHallWarehouse[areaid][1] -= 50;
                    WHDataUpdate();

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Shotgun");
			    }
			    case 2:
			    {
			        if(gHallWarehouse[areaid][0] - 1 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно единиц оружия");

			        if(gHallWarehouse[areaid][1] - 1 <= 0)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов");

					if(PI[playerid][pRank] < 1 && PI[playerid][pRank] > 2)
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данное оружие Вам недоступно");


			        GetPlayerWeaponData(playerid, GetWeaponSlot(3), weapon, ammo);

					if(ammo > 0)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть это оружие!");

                    _GiveGun(playerid, 3, 1);

					SendClientMessage(playerid, COLOR_GREEN, !"Вы взяли Дубинку");
			    }
		 		case 3:
				{
					if(PI[playerid][pRank] < 1 && PI[playerid][pRank] > 2)
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Бронежилет Вам недоступен");

					SetPlayerHealth(playerid, 100);
					SetArmour(playerid, 100);
					SendClientMessage(playerid, COLOR_GREEN, !"Вы надели Бронежилет");
				}
			}

		}
		//======RACE case 5001:  case 5002:  case 5003:  case 5004:  case 5005:

		case 2:
		{
			if(response)
			{
				if(!strlen(inputtext))
					return ShowLoginDialog(playerid);
					
				if(!strcmp(inputtext, PI[playerid][pPassword], false, 32))
				{
				    new nowip[24];
				    GetPlayerIp(playerid, nowip, 24);

					if(strlen(PI[playerid][pCode]))
						ShowPlayerDialogEx(playerid, 391, DIALOG_STYLE_INPUT, !"Код безопасности", !"{FFFFFF}Введите код безопасности:", !"Ввод", !"Отмена");

				    else if(strlen(PI[playerid][pGoogleAuth]) && PI[playerid][pGoogleAuthCheck] || PI[playerid][pGoogleAuthStatus] && strcmp(PI[playerid][pLastIP], nowip, false))
				    	pTemp[playerid][pAuthTimeout] = 0, ShowPlayerDialogEx(playerid, 392, DIALOG_STYLE_INPUT, !"Google Authenticator", !"{FFFFFF}Введите одноразовый пароль из приложения Google Authenticator, установленного у Вас", !"Ввод", !"Отмена");

					else if(!strlen(PI[playerid][pGoogleAuth]) && (PI[playerid][pGoogleAuthCheck] || PI[playerid][pGoogleAuthStatus]))
					{
						PI[playerid][pGoogleAuthCheck] = 0;
						UpdatePlayerData(playerid, "GoogleAuthCheck", PI[playerid][pGoogleAuthCheck]);
						PI[playerid][pGoogleAuthStatus] = 0;
						UpdatePlayerData(playerid, "GoogleAuthStatus", PI[playerid][pGoogleAuthStatus]);
						new query_del[70];
						format(query_del, sizeof query_del, "UPDATE `accounts` SET `GoogleAuth` = '' WHERE `ID` = '%d'", PI[playerid][pID]);
						strdel(PI[playerid][pGoogleAuth], 0, 18);
						OnPlayerLogin(playerid);
					}
				    else OnPlayerLogin(playerid);
				}
				else
				{
					gPlayerLogTries[playerid] --;

					if(gPlayerLogTries[playerid] <= 0)
					{
						SendClientMessage(playerid, COLOR_WHITE, !"Введите /q чтобы Выйти");
						return J_Kick(playerid);
					}

					new
						frmt_pass_warning[90];

					format(frmt_pass_warning, sizeof frmt_pass_warning, "\n{FF0000}Пароль введён неверно\n{FFFFFF}Попыток для ввода пароля: {28910B}%d\n\n", gPlayerLogTries[playerid]);
				    return ShowPlayerDialogEx(playerid, 2, DIALOG_STYLE_PASSWORD, !"{74FFA0}Авторизация", frmt_pass_warning, !"Войти", !"Отмена");
				}
			}
   			else
			   	SendClientMessage(playerid, COLOR_WHITE, !"Введите /q чтобы Выйти"), J_Kick(playerid);
		}
		case 391:
		{
		    if(!response)
		        return SendClientMessage(playerid, COLOR_WHITE, !"Введите /q чтобы Выйти"), J_Kick(playerid);


			if(!strcmp(inputtextsave, PI[playerid][pCode], false) && strlen(inputtextsave))
			{
			    new nowip[24];
			    GetPlayerIp(playerid, nowip, 24);
			    
			    if(strlen(PI[playerid][pGoogleAuth]) && PI[playerid][pGoogleAuthCheck] || PI[playerid][pGoogleAuthStatus] && strcmp(PI[playerid][pLastIP], nowip, false))
			    	pTemp[playerid][pAuthTimeout] = 0, ShowPlayerDialogEx(playerid, 392, DIALOG_STYLE_INPUT, !"Google Authenticator", !"{FFFFFF}Введите одноразовый пароль из приложения Google Authenticator, установленного у Вас", !"Ввод", !"Отмена");

				else if(!strlen(PI[playerid][pGoogleAuth]) && (PI[playerid][pGoogleAuthCheck] || PI[playerid][pGoogleAuthStatus]))
				{
					PI[playerid][pGoogleAuthCheck] = 0;
					UpdatePlayerData(playerid, "GoogleAuthCheck", PI[playerid][pGoogleAuthCheck]);
					PI[playerid][pGoogleAuthStatus] = 0;
					UpdatePlayerData(playerid, "GoogleAuthStatus", PI[playerid][pGoogleAuthStatus]);
					new query_del[70];
					format(query_del, sizeof query_del, "UPDATE `accounts` SET `GoogleAuth` = '' WHERE `ID` = '%d'", PI[playerid][pID]);
					strdel(PI[playerid][pGoogleAuth], 0, 18);
					OnPlayerLogin(playerid);
				}
					
			    else OnPlayerLogin(playerid);
			}
			
			else
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Код безопасности введен неверно"), SendClientMessage(playerid, COLOR_WHITE, !"Введите /q чтобы Выйти"), J_Kick(playerid);
		}
		case 392:
		{
		    if(!response)
		        return SendClientMessage(playerid, COLOR_WHITE, !"Введите /q чтобы Выйти"), J_Kick(playerid);

			if(!strlen(inputtext) || !isNumeric(inputtext) || strlen(inputtext) != 6)
			{
				ShowPlayerDialogEx(playerid, 392, DIALOG_STYLE_INPUT, !"Google Authenticator", !"{FFFFFF}Введите одноразовый пароль из приложения Google Authenticator, установленного у Вас", !"Ввод", !"Отмена");
				return 1;
	        }
	        
	        if(PI[playerid][pGoogleAuth] == '\0')
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка в базе данных"), J_Kick(playerid);

			if(!PI[playerid][pGoogleAuthStatus])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла ошибка"), J_Kick(playerid);

	        new
				getcode = GoogleAuthenticatorCode(PI[playerid][pGoogleAuth], gettime());

			if(strval(inputtext) != getcode)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверный одноразовый пароль из приложения Google Authenticatior");
			    J_Kick(playerid);
			    return 1;
			}
			
            OnPlayerLogin(playerid);
		}
		case 3:
		{
		    if(response) J_Kick(playerid);
		    else Autorisation(playerid);
		}
		case 4:
		{
		    if(response)
			{
				switch(listitem)
				{
				    case 0: ShowPlayerDialogEx(playerid,3,0,"","{FFFFFF}Вы собрались покинуть сервер.\nЕсли хотете сделать это нажмите 'Покинуть'.\nВ ином случае нажмите 'Отмена'","Принять","Выход");
					case 2: ShowLoginDialog(playerid);
					default: return false;
				}
			}
			else Autorisation(playerid);
		}


		case 7: Autorisation(playerid);

		case 17:
		{
		    if(response)
		    {
		        new house = InfoHouse[playerid];
		        if(InfoHouse[playerid]+1 != 0)
		        {
		            switch(listitem)
		            {
		                case 0:
		                {
		                    if(IsPlayerInRangeOfPoint(playerid,2.0,HouseInfo[house][hEnter_X],HouseInfo[house][hEnter_Y],HouseInfo[house][hEnter_Z]))
					        {
					            if(HouseInfo[house][hLock]>0) return SCM(playerid,COLOR_LIGHTRED,"[Ошибка] {FFFFFF}Дверь закрыта, невозможно зайти");
				                pTemp[playerid][pAntiAir] += 4;
				                HouseEntered[playerid] = HouseInfo[house][hID];
				                SetPlayerInterior(playerid,HouseInfo[house][hInt]);
				                SetPlayerVirtualWorld(playerid, (HouseEntered[playerid]+50) );
				                SetPlayerPos(playerid,HouseInfo[house][hExit_X],HouseInfo[house][hExit_Y],HouseInfo[house][hExit_Z]);

					        }
					        else InfoHouse[playerid] = 0;
		                }
		                case 1:
		                {
		                    if(IsPlayerInRangeOfPoint(playerid,2.0,HouseInfo[house][hEnter_X],HouseInfo[house][hEnter_Y],HouseInfo[house][hEnter_Z]))
					        {
								new classname[40];
								switch(HouseInfo[house][hLevel])
								{
									case 0: classname = "Эконом";
									case 1: classname = "Cредний";
									case 2: classname = "Элитный";
									case 3: classname = "Особняк";
									default: classname = "Неизвестно";
								}
			                    if(GetString(HouseInfo[house][hOwner],"The State"))
								{
									format(string,sizeof(string),"\
									{FFFFFF}House ID: \t{1E90FF}%d\n\
									{FFFFFF}Цена дома: \t{1E90FF}$%d\n\
									{FFFFFF}Класс: \t\t{1E90FF}%s\n\n\
									{FFFFFF}Для покупки нажмите {34C924}Купить",HouseInfo[house][hID],HouseInfo[house][hCost],classname);
									return ShowPlayerDialogEx(playerid,29,0,"Дом продается",string,"Купить","Отмена");
								}
								else
								{
									format(string,sizeof(string), "\
									{FFFFFF}House ID: \t{1E90FF}%d\n\
									{FFFFFF}Цена дома: \t{1E90FF}$%d\n\
									{FFFFFF}Владелец: \t{1E90FF}%s\n\
									{FFFFFF}Класс: \t\t{1E90FF}%s\n\n\
									{FFFFFF}Для входа нажмите {34C924}Войти",HouseInfo[house][hID],HouseInfo[house][hCost],HouseInfo[house][hOwner],classname);
								    return ShowPlayerDialogEx(playerid,30,0,"Вход",string,"Войти","Отмена");
								}
							}
							else InfoHouse[playerid] = 0;
		                }
		                default: return false;
		            }
		        }
		    }
		}
		case 999:
		{
			if(!response)
			    return 1;

			switch (listitem)
			{
				case 0: SetWeather(1);
				case 1: SetWeather(2);
				case 2: SetWeather(3);
				case 3: SetWeather(4);
				case 4: SetWeather(5);
				case 5: SetWeather(6);
				case 6: SetWeather(7);
				case 7: SetWeather(8);
				case 8: SetWeather(9);
				case 9: SetWeather(10);
				case 10: SetWeather(11);
				case 11: SetWeather(12);
				case 12: SetWeather(13);
				case 13: SetWeather(14);
				case 14: SetWeather(15);
				case 15: SetWeather(16);
				case 16: SetWeather(17);
				case 17: SetWeather(18);
				case 18: SetWeather(19);
				case 19: SetWeather(20);
				case 20: SetWeather(21);
				case 21: SetWeather(22);
				case 22: SetWeather(23);
				case 23: SetWeather(26);
				case 24: SetWeather(27);
				case 25: SetWeather(29);
				case 26: SetWeather(30);
				case 27: SetWeather(32);
				case 28: SetWeather(33);
				case 29: SetWeather(34);
				case 30: SetWeather(35);
				case 31: SetWeather(36);
				case 32: SetWeather(38);
				case 33: SetWeather(39);
				case 34: SetWeather(40);
				case 35: SetWeather(42);
				case 36: SetWeather(43);
				case 37: SetWeather(44);
				case 38: SetWeather(45);
				case 39: SetWeather(81);
				case 40: SetWeather(91);
				case 41: SetWeather(200);
			}
			SendClientMessage(playerid, COLOR_GREEN, "Погода установлена");

		}
		case 414:
		{
		    if(!response)
				return 1;

			if(temp_mp_status == true)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент уже проводится мероприятие");

		    if(!strlen(inputtext) || strlen(inputtext) < 5)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое описание");

		    if(!strlen(inputtext) || strlen(inputtext) > 100)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинное описание");

		    new
				Float:x,
				Float:y,
				Float:z;

			GetPlayerPos(playerid, x, y, z);

			temp_mp_pos_x = x;
			temp_mp_pos_y = y;
			temp_mp_pos_z = z+1;
			temp_mp_status = true;
			temp_mp_interior = GetPlayerInterior(playerid);
			temp_mp_world = GetPlayerVirtualWorld(playerid);
			temp_mp_ongame = 0;

			new
				frmt_startmp[144];

			format(frmt_startmp, sizeof frmt_startmp, "%s открыл телепорт на МП", PN(playerid));
			SendAdminsMessage(0x037AFAFF, frmt_startmp);
			format(frmt_startmp, sizeof frmt_startmp, "Уважаемые игроки, администратор {A8A8FF}%s{FFFFCC} приглашает вас принять участие в мероприятии:", PN(playerid));
			SendClientMessageToAll(0xFFFFCCFF, frmt_startmp);
			format(frmt_startmp, sizeof frmt_startmp, "%s", inputtext);
			SendClientMessageToAll(0xFFFFCCFF, frmt_startmp);
			format(frmt_startmp, sizeof frmt_startmp, "Для участия введите команду {A8A8FF}/mp{FFFFCC}, кол-во участников {C7FF8F}%d{FFFFCC} человек.", temp_mp_players);
			SendClientMessageToAll(0xFFFFCCFF, frmt_startmp);

		}
		case 400:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: ShowPlayerDialogEx(playerid, 401, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Казино\n{FF7319}2.{FFFFFF} Автошкола\n{FF7319}3.{FFFFFF} Военкомат\n{FF7319}4.{FFFFFF} Строитель дорог\n{FF7319}5.{FFFFFF} Грузчик\n{FF7319}6.{FFFFFF} Завод автозапчастей\n{FF7319}7.{FFFFFF} Центр развлечений\n{FF7319}8.{FFFFFF} Аллея Славы", !"Телепорт", !"Отмена");
			    case 1: ShowPlayerDialogEx(playerid, 402, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Ж/Д вокзал Los Santos\n{FF7319}2.{FFFFFF} Ж/Д вокзал San Fierro\n{FF7319}3.{FFFFFF} Ж/Д вокзал Las Venturas\n{FF7319}4.{FFFFFF} Автовокзал Los Santos", !"Телепорт", !"Отмена");
			    case 2: ShowPlayerDialogEx(playerid, 403, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Администрация Губернатора\n{FF7319}2.{FFFFFF} Мэрия Los Santos\n{FF7319}3.{FFFFFF} Мэрия San Fierro\n{FF7319}4.{FFFFFF} Мэрия Las Venturas", !"Телепорт", !"Отмена");
			    case 3: ShowPlayerDialogEx(playerid, 404, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Полиция Los Santos\n{FF7319}2.{FFFFFF} Полиция San Fierro\n{FF7319}3.{FFFFFF} Полиция Las Venturas\n{FF7319}4.{FFFFFF} FBI", !"Телепорт", !"Отмена");
			    case 4: ShowPlayerDialogEx(playerid, 405, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Больница Los Santos\n{FF7319}2.{FFFFFF} Больница San Fierro\n{FF7319}3.{FFFFFF} Больница Las Venturas", !"Телепорт", !"Отмена");
				case 5: ShowPlayerDialogEx(playerid, 406, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Радиоцентр Los Santos\n{FF7319}2.{FFFFFF} Радиоцентр San Fierro\n{FF7319}3.{FFFFFF} Радиоцентр Las Venturas", !"Телепорт", !"Отмена");
				case 6: ShowPlayerDialogEx(playerid, 407, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Армия San Fierro\n{FF7319}2.{FFFFFF} Армия Las Venturas", !"Телепорт", !"Отмена");
				case 7: ShowPlayerDialogEx(playerid, 408, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Ballas\n{FF7319}2.{FFFFFF} Groove\n{FF7319}3.{FFFFFF} Vagos\n{FF7319}4.{FFFFFF} Aztec\n{FF7319}5.{FFFFFF} Rifa", !"Телепорт", !"Отмена");
	            case 8: ShowPlayerDialogEx(playerid, 409, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Yakuza\n{FF7319}2.{FFFFFF} Cosa Nostra\n{FF7319}3.{FFFFFF} Колумбия", !"Телепорт", !"Отмена");
				case 9: ShowPlayerDialogEx(playerid, 399, DIALOG_STYLE_LIST, !"Телепорты", !"{FF7319}1.{FFFFFF} Банк Los Santos\n{FF7319}2.{FFFFFF} Банк San Fierro\n{FF7319}3.{FFFFFF} Банк Las Venturas", !"Телепорт", !"Отмена");
			}
		}
		case 401:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 2031.2733,1008.8214,10.8203);
			    case 1: J_SetPlayerPos(playerid, -2032.2695,-95.8899,35.1641);
			    case 2: J_SetPlayerPos(playerid, 1164.6606,1369.4958,10.8203);
			    case 3: J_SetPlayerPos(playerid, 799.3996,-1674.3801,13.3695);
			    case 4: J_SetPlayerPos(playerid, 2796.0354,-2398.2195,13.6316);
			    case 5: J_SetPlayerPos(playerid, -92.9191,-314.8379,1.4297);
			    case 6: J_SetPlayerPos(playerid, 1768.6985,-1669.7769,14.4136);
			    case 7: J_SetPlayerPos(playerid, 836.7547,-1826.5155,12.2052);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
		}
		case 402:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 1780.7449,-1896.5653,13.3899);
			    case 1: J_SetPlayerPos(playerid, -1973.5854,137.7679,27.6875);
			    case 2: J_SetPlayerPos(playerid, 2828.6465,1290.8163,10.7703);
			    case 3: J_SetPlayerPos(playerid, 1154.8931,-1749.4983,13.5703);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
		}
		case 403:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 1137.3126,-2036.8060,69.0078);
			    case 1: J_SetPlayerPos(playerid, 1479.7399,-1741.6711,13.5469);
			    case 2: J_SetPlayerPos(playerid, -2755.4285,376.1216,4.3359);
			    case 3: J_SetPlayerPos(playerid, 2378.2515,2471.3547,10.8203);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 404:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 1542.4440,-1675.9539,13.5545);
			    case 1: J_SetPlayerPos(playerid, -1606.0771,720.2507,12.0639);
			    case 2: J_SetPlayerPos(playerid, 2304.8572,2428.2212,10.8203);
			    case 3: J_SetPlayerPos(playerid, -2514.8325,-616.8726,132.5625);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 405:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 1185.1757,-1323.1595,13.5726);
			    case 1: J_SetPlayerPos(playerid, -2657.9438,623.1844,14.4531);
			    case 2: J_SetPlayerPos(playerid, 1605.9449,1828.4265,10.8203);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 406:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 1654.9655,-1668.1196,21.4375);
			    case 1: J_SetPlayerPos(playerid, -1729.4141,784.9946,24.8906);
			    case 2: J_SetPlayerPos(playerid, 2127.6594,2365.3293,10.8203);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 407:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, -1543.9860,411.9844,7.1875);
			    case 1: J_SetPlayerPos(playerid, 246.2262,1946.7273,17.6406);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 408:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 2000.1473,-1130.4432,25.4955);
			    case 1: J_SetPlayerPos(playerid, 2495.4172,-1675.5280,13.3359);
			    case 2: J_SetPlayerPos(playerid, 2786.9475,-1618.1743,10.9219);
			    case 3: J_SetPlayerPos(playerid, 2183.7473,-1804.1757,13.3698);
			    case 4: J_SetPlayerPos(playerid, 2725.3398,-1949.9189,13.5469);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 409:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 2614.0103,1824.5020,10.8203);
			    case 1: J_SetPlayerPos(playerid, 1479.2434,2773.3562,10.8203);
			    case 2: J_SetPlayerPos(playerid, 961.9321,1732.1504,8.6484);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 399:
		{
		    if(!response)
				return 1;

			switch(listitem)
			{
			    case 0: J_SetPlayerPos(playerid, 1310.2046,-1380.4156,13.7072);
			    case 1: J_SetPlayerPos(playerid, -2656.7207,375.8087,4.3341);
			    case 2: J_SetPlayerPos(playerid, 2355.3093,2378.1030,10.8203);
			}
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

		}
		case 2038:
		{
			if(!response)
				return true;
				
			StartChosingVehicle(playerid);
			return true;
		}
		case 203:
		{
		    if(!response)
				return 1;
				
		    if(!IsPlayerInAnyVehicle(playerid))
				return 1;

		    if(!PI[playerid][pCars])
		        return 1;
		        
			new
				slot = GetCarSlot(PI[playerid][pCars]),
				player_car = CarInfo[slot][cVehID],
				Float:health;

		    if(GetPlayerVehicleID(playerid) != player_car)
		        return 1;

			new
			    letters[26][] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"},
				number[7];

			format(number, sizeof number, "%s%d%d%d%s%s", letters[random(sizeof(letters))], random(9), random(9), random(9), letters[random(sizeof(letters))], letters[random(sizeof(letters))]);

			new query_check_num[65];

			format(query_check_num, sizeof query_check_num, "SELECT `cNumber` FROM `cars` WHERE `cNumber` = '%s'", number);

			new
				Cache:result = mysql_query(mysql, query_check_num);
				
			if(cache_get_row_count(mysql))
			{
			    return SendClientMessage(playerid, COLOR_RED, !"Повторите попытку"), cache_delete(result, mysql);
			}
			cache_delete(result, mysql);
					
			new frmt_num[120];
			format(frmt_num, sizeof frmt_num, "{7AC71F}[Успешно] {FFFFFF}Поздравляем, Вы получили номер {FFFF00}%s{FFFFFF} для своего т/c", number);
			SendClientMessage(playerid, COLOR_WHITE, frmt_num);

            SetPVarInt(playerid, "anticheat_put", gettime()+3);

			new vehicleid = GetPlayerVehicleID(playerid), Float:x, Float:y, Float:z, Float:ang;
			SetVehicleNumberPlate(vehicleid, number);
			GetVehiclePos(vehicleid, x,y,z);
			GetVehicleZAngle(vehicleid,ang);
			AntiCheatGetVehicleHealth(vehicleid, health);
			SetVehicleToRespawn(vehicleid);
			J_SetVehicleHealth(vehicleid, health);
			CarInfo[slot][cVehID] = vehicleid;
			VehicleInfo[vehicleid][vFuel] = CarInfo[slot][cFuel];
			VehicleInfo[vehicleid][vLock] = 1;
			
			for(new tn; tn < 14; tn++)
				if(CarInfo[slot][cTuning][tn] != 0) AddVehicleComponent(vehicleid, CarInfo[slot][cTuning][tn]);

			ChangeVehiclePaintjob(vehicleid, CarInfo[slot][cPaintJob]);

			SetVehiclePos(vehicleid,x,y,z);
			
			PutPlayerInVehicle(playerid,vehicleid,0);
			SetVehicleZAngle(vehicleid,ang);
			new year, month, day;
			getdate(year, month, day);
			new date[20];
			format(date, sizeof date, "%02d.%02d.%02d", day, month, year);
			
			new query_save[120];
			format(query_save, sizeof query_save, "UPDATE `cars` SET `cNumber` = '%s', `cDate` = '%s' WHERE `cID` = '%d'", number, date, PI[playerid][pCars]);
			mysql_tquery(mysql, query_save);
		
          	SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Для завершения регистрации вашего автомобиля, отправляйтесь в отделение полиции и получите ПТС");
          	temp_car_num_get[playerid] = player_car;
          	SetString(CarInfo[slot][cDate], date);
          	SetString(CarInfo[slot][cNumber], number);
          	
		}
		case 210:
		{
		    if(!response)
				return 1;

		    if(!PI[playerid][pCars])
		        return 1;

			new
				carID = GetCarSlot(PI[playerid][pCars]);

			if(carID == -1)
				return 1;
			
			switch(listitem)
			{
			    case 0:
			    {
			        if(CarInfo[carID][cSignal])
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже установлена сигнализация");

					ShowPlayerDialogEx(playerid, 209, DIALOG_STYLE_MSGBOX, !"Покупка сигнализации", !"{FFFFFF}Вы хотите установить сигнализацию за {33AA00}5000${FFFFFF}", !"Да", !"Отмена");
			    }
			    case 1:	ShowPlayerDialogEx(playerid, 212, DIALOG_STYLE_INPUT, !"Перекраска", !"{FFFFFF}Стоимость изменения основного цвета т/с {33AA00}2000${FFFFFF}\nВведите ID цвета:\n{AFAFAF}Значение должно быть от 0 до 250", !"Купить", !"Выход");
			    case 2:	ShowPlayerDialogEx(playerid, 214, DIALOG_STYLE_INPUT, !"Перекраска", !"{FFFFFF}Стоимость изменения дополнительного цвета т/с {33AA00}1000${FFFFFF}\nВведите ID цвета:\n{AFAFAF}Значение должно быть от 0 до 250", !"Купить", !"Выход");
			}
		}
		case 209:
		{
		    if(!response) return 1;
		    if(!PI[playerid][pCars]) return 1;
			new carID = GetCarSlot(PI[playerid][pCars]), bizid = pTemp[playerid][pCarBiz];
			if(carID == -1) return 1;
	        if(CarInfo[carID][cSignal]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже установлена сигнализация");
			if(PI[playerid][pMoney] < 5000) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
            CarInfo[carID][cSignal] = 1;
			new query_signal_add[85];

			format(query_signal_add, sizeof query_signal_add, "UPDATE `cars` SET `cSignal` = '1' WHERE `cOwnerID` = %d", PI[playerid][pID]);
			mysql_tquery(mysql, query_signal_add);
			
			GiveMoney(playerid, -5000, "сигнализация");

		    if(BizInfo[bizid][bProducts] - 20 > 0)
		    {
			    BizInfo[bizid][bProducts] -= 20;
				GiveBusinessMoney(bizid, 5000);
				if(BizInfo[bizid][bKrasher]) GiveFracBank(BizInfo[bizid][bKrasher],5000/100*10);
			}
			
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Сигнализация установлена на Ваш автомобиль");
		}
		case 212:
		{
		    if(!response) return 1;
		    if(!PI[playerid][pCars]) return 1;

			new
				carID = GetCarSlot(PI[playerid][pCars]),
				vehicleid = CarInfo[carID][cVehID],
				bizid = pTemp[playerid][pCarBiz];
				
			if(carID == -1) return 1;
			if(PI[playerid][pMoney] < 2000) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 250) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");
			if(strfind(inputtext,"|") != -1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            GiveMoney(playerid, -2000, "покраска");

		    if(BizInfo[bizid][bProducts] - 15 > 0)
		    {
			    BizInfo[bizid][bProducts] -= 15;
				GiveBusinessMoney(bizid, 2000);
				if(BizInfo[bizid][bKrasher]) GiveFracBank(BizInfo[bizid][bKrasher],2000/100*10);
			}
			
			CarInfo[carID][cColor_1] = strval(inputtext);
			
			ChangeVehicleColor(vehicleid, CarInfo[carID][cColor_1], CarInfo[carID][cColor_2]);

			new
				query_change_color[85];

			format(query_change_color, sizeof query_change_color, "UPDATE `cars` SET `cColor_1` = '%d' WHERE `cOwnerID` = %d", CarInfo[carID][cColor_1], PI[playerid][pID]);
			mysql_tquery(mysql, query_change_color);

            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Ваш автомобиль перекрашен в новый цвет");
		}
		case 214:
		{
		    if(!response) return 1;
		    if(!PI[playerid][pCars]) return 1;
			new
				carID = GetCarSlot(PI[playerid][pCars]),
				vehicleid = CarInfo[carID][cVehID],
				bizid = pTemp[playerid][pCarBiz];

			if(carID == -1) return 1;
			if(PI[playerid][pMoney] < 1000) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 250) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");
			if(strfind(inputtext,"|") != -1) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            GiveMoney(playerid, -1000, "покраска");

		    if(BizInfo[bizid][bProducts] - 15 > 0)
		    {
			    BizInfo[bizid][bProducts] -= 15;
				GiveBusinessMoney(bizid, 1000);
				if(BizInfo[bizid][bKrasher]) GiveFracBank(BizInfo[bizid][bKrasher],1000/100*10);
			}

			CarInfo[carID][cColor_2] = strval(inputtext);

			ChangeVehicleColor(vehicleid, CarInfo[carID][cColor_1], CarInfo[carID][cColor_2]);

			new
				query_change_color[85];

			format(query_change_color, sizeof query_change_color, "UPDATE `cars` SET `cColor_2` = '%d' WHERE `cOwnerID` = %d", CarInfo[carID][cColor_2], PI[playerid][pID]);
			mysql_tquery(mysql, query_change_color);

            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Ваш автомобиль перекрашен в новый цвет");
		}
		case 112:
		{
		    if(!response)
		        return RemovePlayerFromVehicle(playerid);
		        
	        new
				arid = GetArendCarID(GetPlayerVehicleID(playerid)),
				bizid = ArendInfo[arid][aClass]+56;
				
	        if(arid == -1)
	            return RemovePlayerFromVehicle(playerid);
	            
			if(pTemp[playerid][pArendKey] != INVALID_VEHICLE_ID)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете транспортное средство"), RemovePlayerFromVehicle(playerid);
	        
            if(ArendInfo[arid][aPlayerID] != INVALID_PLAYER_ID || IsPlayerConnected(ArendInfo[arid][aPlayerID]))
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот транспорт уже арендуют"), RemovePlayerFromVehicle(playerid);
                
			if(PI[playerid][pMoney] < ArendInfo[arid][aCost])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег"), RemovePlayerFromVehicle(playerid);

            pTemp[playerid][pArendKey] = arid;
            GiveMoney(playerid, -ArendInfo[arid][aCost], "аренда тс");

		    if(BizInfo[bizid][bProducts] - 15 > 0)
		    {
			    BizInfo[bizid][bProducts] -= 15;
				GiveBusinessMoney(bizid, (ArendInfo[arid][aCost]/100)*18);
				if(BizInfo[bizid][bKrasher]) GiveFracBank(BizInfo[bizid][bKrasher],(ArendInfo[arid][aCost]/100)/100*10);
			}
            ArendInfo[arid][aPlayerID] = playerid;
            
            
            if(IsABike(GetPlayerVehicleID(playerid)))
				SetEngineStatus(GetPlayerVehicleID(playerid));
            
            SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно арендовали это транспортное средство");
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}{FFFF00}/lock 3{FFFFFF} - открыть/закрыть арендованное т/с");
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}{FFFF00}/unrent{FFFFFF} - отказаться от аренды");
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Аренда прекратится, если Вы отойдете слишком далеко от т/с");
            return 1;
		}
		case 31:
		{
		    if(!response)
		        return 1;
		        
	        new
				house = InfoHouse[playerid];
				
			if(house < 0)
		 		return 1;
				
			if(!IsPlayerInRangeOfPoint(playerid, 4.0, HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z]))
			    return 1;
			    
	        if(PI[playerid][pHouseKey])
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть дом/либо вы арендуете чей-то");
	        
		    if(!GetString(HouseInfo[house][hOwner], "The State"))
	     	    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот дом уже куплен");
	     	    
 	        if(PI[playerid][pMoney] < HouseInfo[house][hCost])
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
	     	        
            HouseEntered[playerid] = HouseInfo[house][hID];
			PI[playerid][pSpawn] = 2;
			UpdatePlayerData(playerid, "Spawn", 2);
			
			new
				moneylog[24];
				
			format(moneylog, sizeof moneylog, "покупка дома (№%d)", house);
            GiveMoney(playerid, -HouseInfo[house][hCost], moneylog);
            
            PI[playerid][pHouseKey] = HouseInfo[house][hID];
            UpdatePlayerData(playerid, "HouseKey", PI[playerid][pHouseKey]);
            HouseInfo[house][hDays] = 3;

            pTemp[playerid][pAntiAir] += 4;
            SetPlayerInterior(playerid,HouseInfo[house][hInt]);
       	 	SetPlayerVirtualWorld(playerid,HouseEntered[playerid]+50);
            SetPlayerPos(playerid,HouseInfo[house][hExit_X],HouseInfo[house][hExit_Y],HouseInfo[house][hExit_Z]);
       	 	SetString(HouseInfo[house][hOwner], PN(playerid));

			for(new i; i < 4; i++)
				HouseInfo[house][hImprove][i] = 0;

            House_Log(playerid,HouseInfo[house][hID]);

       	 	UpdateHouse(house);
            SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем, Вы купили дом! Не забывайте проплачивать его в банке!");
            PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
		}
		case 30:
		{
		    if(!response)
		        return 1;
		        
	        new
				house = InfoHouse[playerid];

			if(house < 0)
		 		return 1;

			if(!IsPlayerInRangeOfPoint(playerid, 4.0, HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z]))
			    return 1;
			    
	        if(HouseInfo[house][hLock] > 0)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Дверь дома закрыта");
				
			HouseEntered[playerid] = HouseInfo[house][hID];
			pTemp[playerid][pAntiAir] += 4;
			SetPlayerInterior(playerid, HouseInfo[house][hInt]);
			SetPlayerVirtualWorld(playerid, (HouseEntered[playerid]+50) );
			SetPlayerPos(playerid, HouseInfo[house][hExit_X], HouseInfo[house][hExit_Y], HouseInfo[house][hExit_Z]);
		}
		case 29:
		{
			if(!response)
			    return 1;
			    
	        new
				house = InfoHouse[playerid];

			if(house < 0)
		 		return 1;

			if(!IsPlayerInRangeOfPoint(playerid, 4.0, HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z]))
			    return 1;
		    
	        if(GetString(HouseInfo[house][hOwner],"The State"))
     	    {
				if(PI[playerid][pHouseKey])
			 		return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть дом");
			 		
				new str_dialog_buyhouse[69 + 9];
				format(str_dialog_buyhouse, sizeof(str_dialog_buyhouse), "{FFFFFF}Вы действительно хотите купить этот дом за {33AA33}$%d?", HouseInfo[house][hCost]);
				ShowPlayerDialogEx(playerid, 31, DIALOG_STYLE_MSGBOX, !"Частный дом", str_dialog_buyhouse, !"Да", !"Нет");
			}
			else
			{
		        if(HouseInfo[house][hLock] > 0)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Дверь дома закрыта");
					
                pTemp[playerid][pAntiAir] += 4;
                HouseEntered[playerid] = HouseInfo[house][hID];
                SetPlayerInterior(playerid,HouseInfo[house][hInt]);
                SetPlayerVirtualWorld(playerid, (HouseEntered[playerid]+50) );
                SetPlayerPos(playerid,HouseInfo[house][hExit_X],HouseInfo[house][hExit_Y],HouseInfo[house][hExit_Z]);
			}
		}
		case 32:
		{
		    if(!response)
		        return 1;
		        
	        if(!strlen(inputtext))
	        {
	            ShowReportDialog(playerid);
				return true;
	        }
	        
	        if(strfind(inputtext, "{") != -1 || strfind(inputtext, "}") != -1)
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы используете запрещенные символы"), ShowReportDialog(playerid);
	        
	        format(string, sizeof string, "%s[%d]: {FFCD00}%s", PN(playerid), playerid, inputtext);
	        SendAdminsMessage(0xFF4F00FF, string, 1);
	        format(string, sizeof string, "%s[%d]: {FFCD00}%s", PN(playerid), playerid, inputtext);
	        SendClientMessage(playerid, COLOR_GREEN, string);

	        SendClientMessage(playerid, COLOR_GREEN, !"Ожидайте, администрация Вам скоро ответит.");

	        pTemp[playerid][pReport] = gettime()+60;
		}

		case 481:
		{
		    if(!response)
				return RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);

            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return 1;
				
			new
			    vehid = GetPlayerVehicleID(playerid);

			if(IsValidDynamic3DTextLabel(temp_bus_text[playerid])) DestroyDynamic3DTextLabel(temp_bus_text[playerid]);
			temp_bus_text[playerid] = NONE_3D_TEXT;
			if(PI[playerid][pJob] != 1)
		        return 1;
		        
			if(temp_bus_id[playerid] != INVALID_VEHICLE_ID && temp_bus_id[playerid] != vehid)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете автобус"), RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);
				
			ShowPlayerDialogEx(playerid, 482, DIALOG_STYLE_LIST, !"Выберите маршрут", !"{FF7319}1.{FFFFFF} Лос Сантос - Лас Вентурас\n{FF7319}2.{FFFFFF} Сан Фиерро - Лос Сантос\n{FF7319}3.{FFFFFF} Лос Сантос - Завод автозапчастей\n{FF7319}4.{FFFFFF} Сан Фиерро - Лас Вентурас", !"Выбор", !"Отмена");
		}
		case 482:
		{
		    if(!response)
				return RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);

            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return 1;
				
			new
			    vehid = GetPlayerVehicleID(playerid);

			if(PI[playerid][pJob] != 1)
		        return 1;

			if(temp_bus_id[playerid] != INVALID_VEHICLE_ID && temp_bus_id[playerid] != vehid)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете автобус"), RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);

			ShowPlayerDialogEx(playerid, 483, DIALOG_STYLE_INPUT, !"Стоимость проезда", !"{FFFFFF}Введите стоимость проезда\n\n{AEAEAE}Значение должно быть от 1$ до 100$", !"Ввод", !"Отмена");
            SetPVarInt(playerid, "pbusroute", listitem);
		}
		case 483:
		{
		    if(!response)
				return RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);

            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return 1;
				
			new
			    vehid = GetPlayerVehicleID(playerid);

			if(PI[playerid][pJob] != 1)
		        return 1;

			if(VehicleInfo[vehid][vBusOwner] != INVALID_PLAYER_ID)
			    return 1;

			if(temp_bus_id[playerid] != INVALID_VEHICLE_ID && temp_bus_id[playerid] != vehid)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете автобус"), RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);

			if(PI[playerid][pMoney] < 200)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно 200$ для аренды автобуса");
				RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);
				return 1;
			}

			if(!strlen(inputtext) || !isNumeric(inputtext))
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Цена должна быть указана цифрами");
				return ShowPlayerDialogEx(playerid, 483, DIALOG_STYLE_INPUT, !"Стоимость проезда", !"{FFFFFF}Введите стоимость проезда\n\n{AEAEAE}От 1$ до 100$", !"Выбор", !"Отмена");
			}
			new price = strval(inputtext);
			
			if(price < 0 || price > 100)
				return ShowPlayerDialogEx(playerid, 483, DIALOG_STYLE_INPUT, !"Стоимость проезда", !"{FFFFFF}Введите стоимость проезда\n\n{AEAEAE}От 1$ до 100$", !"Выбор", !"Отмена");

			new model = GetVehicleModel(vehid),
				route = GetPVarInt(playerid,"pbusroute");
				
  	 		DeletePVar(playerid,"pbusroute");
			
			if(vehid == INVALID_VEHICLE_ID || (model != 431 && model != 437))
				return 1;
				
			GiveMoney(playerid, -200, "аренда автобуса");
			
			new
				routename[150];
				
			switch(route)
			{
				case 0: strcat(routename, "{FFEAEA}Лос Сантос - Лас Вентурас");
				case 1: strcat(routename, "{FFEAEA}Сан Фиерро - Лос Сантос");
                case 2: strcat(routename, "{FFEAEA}Лос Сантос - Завод автозапчастей");
                case 3: strcat(routename, "{FFEAEA}Сан Фиерро - Лас Вентурас");
			}
			
			new
				mes[128];
				
			format(mes, sizeof mes, "%s\n{FFFFFF}Стоимость проезда: %d$", routename, price);
			
			if(!IsValidDynamic3DTextLabel(temp_bus_text[playerid]))
				temp_bus_text[playerid] = CreateDynamic3DTextLabel(mes, COLOR_WHITE, 0.0, 0.0, 3.0, 40.0, INVALID_PLAYER_ID, vehid);
				
			temp_bus_id[playerid] = vehid;
			temp_bus_route[playerid] = route;
			temp_bus_price[playerid] = price;
			temp_bus_pos[playerid] = 0;
			temp_bus_damage[playerid] = 1000.0;
			VehicleInfo[vehid][vBusOwner] = playerid;
			SetNextBusCP(playerid, 0);
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы начали работу");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь на отмеченную метку. Введите {FFFF99}/end{FFFFFF} для завершения работы");
		}
		case 484:
		{
		    if(!response)
				return RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);

            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return 1;
				
			new
			    vehid = GetPlayerVehicleID(playerid);

			if(PI[playerid][pJob] != 2)
		        return 1;

			if(pTemp[playerid][pTaxiID] != INVALID_VEHICLE_ID && pTemp[playerid][pTaxiID] != vehid)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете такси"), RemovePlayerFromVehicle(playerid), HideCarInfo(playerid);

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы арендовали такси. Ожидайте вызовы");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}{FFFF99}/taxi{FFFFFF} - запросить у пассажира место назначения");
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}{FFFF99}/fare{FFFFFF} - установить тариф");
            
            pTemp[playerid][pTaxiID] = vehid;
            GiveMoney(playerid, -200, "аренда такси");
		}
		case 494:
		{
			if(!response)
				return 1;
				
			if(PI[playerid][pJob] == 2 && pTemp[playerid][pTaxiID] != INVALID_VEHICLE_ID)
				SetVehicleToRespawnEx(pTemp[playerid][pTaxiID]);
		
		}
		case 487:
		{
			if(!response)
				return 1;

			if(PI[playerid][pJob] == 1 && temp_bus_id[playerid] != INVALID_VEHICLE_ID)
			{
				DisablePlayerRaceCheckpoint(playerid);
                BusSpawnEx(temp_bus_id[playerid]);
			}
		}
		case 838:
		{
			if(!response)
				return 1;

			if(!IsAGang(playerid))
				return 1;
			
			if(PI[playerid][pRank] < 9)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Функция доступна с 9 ранга и выше");

			new h; gettime(h);

			if(h < 15 || h > 21)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Использовать команду можно только с 15:00 до 22:00");

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

			new fraction = PI[playerid][pFraction];
			
			if(!IsInAllowed(playerid))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваша банда уже участвует в захвате зон");

			if(zGangTime[fraction-1] <= 0)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сегодня ваша банда больше не может участвовать в захвате");

			for(new i; i < MAX_GANGZONE; i++)
			{
				if(PlayerToKvadrat(playerid, GZMZ[i][gCoords][0], GZMZ[i][gCoords][1], GZMZ[i][gCoords][2], GZMZ[i][gCoords][3]) && ZoneOnBattle[i] == 0)
				{
					if(GZMZ[i][gGang] == fraction)
						return SendClientMessage(playerid, COLOR_GREY, !"Вы не можете захватывать зону вашей банды!");

					if(IsPlayerInBandOnline(fraction) < 5)
						return SendClientMessage(playerid, COLOR_GREY, !"В вашей банде мало игроков онлайн!");

					if(IsPlayerInBandOnline(GZMZ[i][gGang]) < 4)
					{
						new
							frmt_smail_players[28 + 20];

					    format(frmt_smail_players, sizeof frmt_smail_players, "У банды \"%s\" мало игроков!", GetGangName(GZMZ[i][gGang]));
						return SendClientMessage(playerid, COLOR_GREY, frmt_smail_players);
					}

					if(IsCapture == 1)
						return SendClientMessage(playerid, COLOR_GREY, !"Уже происходит захват одной из зон. Дождитесь окончания!");

					GangZoneFlashForAll(GZMZ[i][gID], GetGZColorF(fraction));
					captureID = i;
					GZSafeTime[i] = 360;
					FrakCD = 900;
					GZMZ[i][gNapad] = fraction;
					ZoneOnBattle[i] = 1;
					IsCapture = 1;
					zGangTime[fraction-1]--;
					GangInfo[fraction][gCapture] = 1;
					GangInfo[GZMZ[i][gGang]][gCapture] = 1;
					GangInfo[GZMZ[i][gGang]][gCaptureID] = fraction;
					GangInfo[fraction][gCaptureID] = fraction;
					GangInfo[fraction][gGangNumber] = 1;
					GangInfo[GZMZ[i][gGang]][gGangNumber] = 0;
					CaptureStart(fraction, GZMZ[i][gGang]);
				}
			}
		}
		case 839:
		{
			if(!response)
				return 1;

			if(!IsAMafia(playerid))
			    return 1;

			if(PI[playerid][pRank] < 8)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			if(MafiaFreeze)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Мафии заморожены");

			new h; gettime(h);
			
			new fraction = PI[playerid][pFraction];

			if(h < 15 || h > 21)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Использовать команду можно только с 15:00 до 22:00");

			if(IsBizWar)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На данный момент уже идет захват бизнеса!");

			if(zGangTime[fraction-1] <= 0)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Сегодня ваша мафия больше не может участвовать в захвате");

			ShowPlayerDialogEx(playerid, 840, DIALOG_STYLE_LIST, !"Выберите локацию", !"Метеостанция\nВестоун\nЗаброшенная деревня\nКаменная деревня\nШахта", !"Выбор", !"Отмена");
		}
		case 840:
		{
			if(!response)
				return 1;

			if(!IsAMafia(playerid))
			    return 1;

			if(PI[playerid][pRank] < 8)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш ранг недостаточен");

			if(MafiaFreeze)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Мафии заморожены");

			new h; gettime(h);
			new fraction = PI[playerid][pFraction],
				business_search;

			if(h < 15 || h > 21)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Использовать команду можно только с 15:00 до 22:00");

			if(IsBizWar)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На данный момент уже идет захват бизнеса!");

			if(zGangTime[fraction-1] <= 0)
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
						switch(listitem)
						{
						    case 0: gMafiaZone = GangZoneCreate(-405.6193,1521.4493,-237.4637,1616.5543), gBizWarArea = CreateDynamicRectangle(-405.6193,1521.4493,-237.4637,1616.5543);
						    case 1: gMafiaZone = GangZoneCreate(-1472.5155,-1604.3209,-1404.4091,-1437.5681), gBizWarArea = CreateDynamicRectangle(-1472.5155,-1604.3209,-1404.4091,-1437.5681);
						    case 2: gMafiaZone = GangZoneCreate(-455.5065,2176.9976,-354.0084,2273.6135), gBizWarArea = CreateDynamicRectangle(-455.5065,2176.9976,-354.0084,2273.6135);
						    case 3: gMafiaZone = GangZoneCreate(-1334.5273,2477.8606,-1279.6411,2566.1240), gBizWarArea = CreateDynamicRectangle(1334.5273,2477.8606,-1279.6411,2566.1240);
						    case 4: gMafiaZone = GangZoneCreate(-1947.4587,-1794.0580,-1773.7360,-1581.5946), gBizWarArea = CreateDynamicRectangle(-1947.4587,-1794.0580,-1773.7360,-1581.5946);
						}
					    for(new b = 0, j = GetPlayerPoolSize(); b <= j; b++)
						{
							if(IsAMafia(b))
							{
								GangZoneShowForPlayer(b, gMafiaZone, 0xFF0000AA);
								TextDrawShowForPlayer(b, BizWarTimer);
							}
						}
						FractionChat(BizInfo[i][bKrasher], 0xFF2400FF, "На бизнес Вашей мафии напали. Откройте карту и посмотрите место проведения стрелы");
                        FractionChat(BizInfo[i][bKrasher], 0xFF2400FF, "Время до начала захвата - 10 минут. Отсчет отображается вверху экрана");
						FractionChat(PI[playerid][pFraction], 0xFF2400FF, "Ваша мафия напала на бизнес. Откройте карту и посмотрите место проведения стрелы");
                        FractionChat(PI[playerid][pFraction], 0xFF2400FF, "Время до начала захвата - 10 минут. Отсчет отображается вверху экрана");
						IsBizWar = 1;
						gBizWarTimer = 600;
						gNapadMafia = BizInfo[i][bKrasher];
						gMafiaID = PI[playerid][pFraction];
						gBizWarScore[0] = 0;
						gBizWarScore[1] = 0;
						gBizWarBizID = i;
					}
				}
			}
			
			if(!business_search)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны быть у бизнеса");

		}
		case 485:
		{
			if(!response)
				return 1;
				
			SetPVarInt(playerid, "makegunid", listitem);
			
			new needgun = gGunAmount[listitem],
				bool:noneedgun;
				
			SetPVarInt(playerid, "noneedgun", 0);
			for(new i; i < 12; i++)
			{
				new
					weapid, ammot;
					
				GetPlayerWeaponData(playerid, i, weapid, ammot);
				if(weapid == gGunID[listitem])
				{
					noneedgun = true;
					SetPVarInt(playerid,"noneedgun",1);
					break;
				}
			}
			if(PI[playerid][pPackets] < needgun && !noneedgun)
			{
				new
				    fmrt_info_eds[120];
				    
				format(fmrt_info_eds, sizeof fmrt_info_eds, "{FF2222}[Ошибка] {FFFFFF}Вам нужно %d ед. оружия для сборки этого оружия", needgun);
				SendClientMessage(playerid, COLOR_WHITE, fmrt_info_eds);
				ShowMakeGunList(playerid);
				return 1;
			}
			
			if(listitem != 7)
				ShowPlayerDialogEx(playerid, 486, DIALOG_STYLE_INPUT, !"Сборка оружия", !"{FFFFFF}Сколько патронов вы хотите использовать для этого оружия?", !"Собрать", !"Отмена");

			else
			{
				if(PI[playerid][pMats] < 1)
					return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно патронов");

				PI[playerid][pPackets] -= 10;
				PI[playerid][pMats] -= 1;

				UpdatePlayerData(playerid, "Mats", PI[playerid][pMats]);
				UpdatePlayerData(playerid, "Packets", PI[playerid][pPackets]);

				_GiveGun(playerid, 5, 1);

			}
		}
		case 486:
		{
			if(!response)
				return 1;
				
			new
				ammo = strval(inputtext);
				
			if(ammo < 1 || ammo > 500)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное к-во патронов");
				ShowMakeGunList(playerid);
				return 1;
			}
			
			new
				gunid = GetPVarInt(playerid,"makegunid"),
				needgun = gGunAmount[gunid],
				weaponid = gGunID[gunid];
				
			if(PI[playerid][pMats] < ammo)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас недостаточно патронов");
				
			if(!GetPVarInt(playerid,"noneedgun"))
				PI[playerid][pPackets] -= needgun;
				
			SetPVarInt(playerid,"noneedgun",0);
			PI[playerid][pMats] -= ammo;
			
			UpdatePlayerData(playerid, "Mats", PI[playerid][pMats]);
			UpdatePlayerData(playerid, "Packets", PI[playerid][pPackets]);
			
			_GiveGun(playerid, weaponid, ammo);
		}
		case 440:
		{
		    if(!response)
				return 1;

			if(!PI[playerid][pCars])
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет т/c");

			new
			    carid = PI[playerid][pCars],
			    slot = GetCarSlot(carid),
				vehicleid = CarInfo[GetCarSlot(carid)][cVehID];

			if(GetPlayerVehicleID(playerid) != vehicleid || GetPlayerState(playerid) != 2)
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}Для продажи своего транспорта Вы должны находиться в нём за рулём");
			
			
			CarInfo[slot][cColor_1] = 0;
			CarInfo[slot][cColor_2] = 0;
			CarInfo[slot][cOwnerID] = 0;
			strdel(CarInfo[slot][cNumber], 0, 12);
			strdel(CarInfo[slot][cDate], 0, 20);
			CarInfo[slot][cFuel] = 0.0;
			CarInfo[slot][cHealth] = 0.0;
			CarInfo[slot][cMilage] = 0.0;
            CarInfo[slot][cVehID] = INVALID_VEHICLE_ID;
            
            VehicleInfo[vehicleid][vLock] = 0;
            
            DestroyVehicle(vehicleid);
            
            SendClientMessage(playerid, COLOR_GREEN, !"Автомобиль продан");

            GiveMoney(playerid, Transport[CarInfo[slot][cModelID]][trPrice]/100*80, "продажа авто");
            CarInfo[slot][cModelID] = 0;
            CarInfo[slot][cID] = 0;

			
			for(new tn; tn < 14; tn++)
				if(CarInfo[slot][cTuning][tn] != 0) RemoveVehicleComponent(CarInfo[slot][cVehID], CarInfo[slot][cTuning][tn]), CarInfo[slot][cTuning][tn] = 0;

			ChangeVehiclePaintjob(CarInfo[slot][cVehID], 5);

			CarInfo[slot][cPaintJob] = 5;
			CarInfo[slot][cSignal] = 0;


			new
				query_car[256];

			format(query_car, sizeof query_car, "DELETE FROM `cars` WHERE `cID` = '%d'", PI[playerid][pCars]);

			mysql_tquery(mysql, query_car);
			
            PI[playerid][pCars] = 0;
            UpdatePlayerData(playerid, "Cars", PI[playerid][pCars]);
            PI[playerid][pPTS] = 0;
            UpdatePlayerData(playerid, "PTS", PI[playerid][pPTS]);
            temp_car_num_get[playerid] = 0;

		}
		case 441:
		{
		    if(!response)
				return 1;
				
			if(!PI[playerid][pHouseKey])
			    return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У вас нет дома");

			if(!GetString(HouseInfo[PI[playerid][pHouseKey]-1][hOwner],Name(playerid)))
				return SendClientMessage(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}У Вас нет дома");
		
			new
				houseid = PI[playerid][pHouseKey]-1;
			
			new
				query_house[136 + 5];
				
			format(query_house, sizeof query_house, "UPDATE `houses` SET `Owner` = 'The State', `Days` = '0', `Improve` = '0|0|0|0' WHERE `ID` = '%d'", HouseInfo[houseid][hID]);
			mysql_tquery(mysql, query_house);
			
			GiveMoney(playerid, HouseInfo[houseid][hCost]/100*80, "продажа дома");
			
			
			if(IsValidDynamic3DTextLabel(HintStoreText[houseid]))
			    DestroyDynamic3DTextLabel(HintStoreText[houseid]);
			    
			if(IsValidDynamic3DTextLabel(HintSafeText[houseid]))
			    DestroyDynamic3DTextLabel(HintSafeText[houseid]);
			    
			if(IsValidDynamicObject(HintStoreObject[houseid]))
			    DestroyDynamicObject(HintStoreObject[houseid]);

			if(IsValidDynamicObject(HintSafeObject[houseid]))
			    DestroyDynamicObject(HintSafeObject[houseid]);
			    
			SetString(HouseInfo[houseid][hOwner], "The State");

				
     		HouseInfo[houseid][hSafeCode] = 0;
     		HouseInfo[houseid][hSkin][1] = 0;
     		HouseInfo[houseid][hSkin][2] = 0;
     		HouseInfo[houseid][hSkin][3] = 0;
     		HouseInfo[houseid][hSkin][0] = 0;
     		HouseInfo[houseid][hMoney] = 0;
     		
     		UpdateHouseDress(houseid);
     		UpdateHouseGun(houseid);
     		
     		for(new i;i<8;i++)
     		{
     		    HouseInfo[houseid][hGun][i] = 0;
				DestroyDynamicObject(HouseGunObject[houseid][i]);
				HouseGunObject[houseid][i] = 0;
			}
			
		    if(IsValidDynamicObject(HintDressObject[houseid][0]))
		    	DestroyDynamicObject(HintDressObject[houseid][0]);
		    if(IsValidDynamicObject(HintDressObject[houseid][1]))
		    	DestroyDynamicObject(HintDressObject[houseid][1]);
		    if(IsValidDynamicObject(HintDressObject[houseid][2]))
		    	DestroyDynamicObject(HintDressObject[houseid][2]);

     		
			UpdateHouse(houseid);
			SendClientMessage(playerid, COLOR_GREEN, !"Дом продан");
			
            new
                improve;

			for(new i; i < 4; i++)
			{
			    if(HouseInfo[houseid][hImprove][i])
			    {
					HouseInfo[houseid][hImprove][i] = 0;
					improve += HouseImprovePrice[i];
				}
			}

			if(improve)
			    GiveMoney(playerid, improve/100*80, "возврат денег за улучшения"), SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF} Вам было возвращено 80 процентов от купленных улучшений");

			
			PI[playerid][pHouseKey] = 0;
			UpdatePlayerData(playerid, "HouseKey", PI[playerid][pHouseKey]);
				
		}
		case 410:
		{
		    if(!response)
		        return 1;
		        
			if(InJob[playerid] != 0)
				return SCM(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}В данный момент вы уже где-то работаете!");

			
			InJob[playerid] = 5;
            temp_job_status[playerid] = 1;
            temp_job_amount[playerid] = 0;
            
            if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
				RemovePlayerAttachedObject(playerid, 9);
            
 	 		PI[playerid][pOldSkin] = GetPlayerSkin(playerid);
            
            if(PI[playerid][pSex] == 1)
				SetPlayerSkinEx(playerid, 27);
				
			else if(PI[playerid][pSex] == 2)
			    SetPlayerSkinEx(playerid, 69);
			
			new
			    checkpoint = RandomEx(0, 3);

		    TogglePlayerDynamicCP(playerid, gRoadGet[checkpoint], true);
		    RoadGet[playerid] = checkpoint+1;

			SendClientMessage(playerid, COLOR_WHITE, !"Вы устроились на работу {ABD1BB}строителя дорог");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь на место загрузки щебня");
			temp_job_time[playerid] = 3;
		}
		case 411:
		{
		    if(!response)
		        return 1;
		        
            if(InJob[playerid] != 5)
                return 1;


                
            InJob[playerid] = 0;
            temp_job_status[playerid] = 0;
 
            
	    	if(IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid,0);
	    	if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid,1);
	    	
	    	
			new
			    frmt_worked[90],
				frmt_gametext[15];

			if(temp_job_amount[playerid])
				format(frmt_worked, sizeof frmt_worked, "Вы закончили работу {ABD1BB}строителя дорог. {FFFFFF}Заработано: {8D2424}$%d", temp_job_amount[playerid]), SendClientMessage(playerid, COLOR_WHITE, frmt_worked);

			else
			    SendClientMessage(playerid, COLOR_WHITE, !"Вы закончили работу {ABD1BB}строителя дорог.");
			    
			GiveMoney(playerid, temp_job_amount[playerid], "работа строителем");


            if(temp_job_amount[playerid])
            {
				format(frmt_gametext, sizeof frmt_gametext, "~g~+$%d", temp_job_amount[playerid]);
				GameTextForPlayer(playerid, frmt_gametext, 1000, 1);
			}

			for(new i = 0; i < 4; i++)
				TogglePlayerDynamicCP(playerid, gRoadGet[i], false),
				TogglePlayerDynamicCP(playerid, gRoadCP[i], false);

		    RoadGet[playerid] = 0;
		    RoadCP[playerid] = 0;
			
			temp_job_amount[playerid] = 0;
			temp_job_time[playerid] = 3;
			SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);
			
		}
		case 415:
		{
		    if(!response)
		        return 1;

			if(InJob[playerid] != 0)
				return SCM(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}В данный момент вы уже где-то работаете!");


			InJob[playerid] = 6;
            temp_porter_status[playerid] = 1;
            temp_porter_amount[playerid] = 0;

            if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
				RemovePlayerAttachedObject(playerid, 9);

 	 		PI[playerid][pOldSkin] = GetPlayerSkin(playerid);

            if(PI[playerid][pSex] == 1)
				SetPlayerSkinEx(playerid, 27);

			else if(PI[playerid][pSex] == 2)
			    SetPlayerSkinEx(playerid, 69);

			new job_cp = RandomEx(0,5);
			
			TogglePlayerDynamicCP(playerid, PorterLoad[job_cp], true);
			
			SendClientMessage(playerid, COLOR_WHITE, !"Вы устроились на работу {ABD1BB}грузчиком");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь на отмеченное место на карте");
			temp_porter_time[playerid] = 3;
		}
		case 416:
		{
		    if(!response)
		        return 1;

            if(InJob[playerid] != 6)
                return 1;


            InJob[playerid] = 0;
            temp_porter_status[playerid] = 0;
            

	    	if(IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid,0);

	    	for(new i = 0; i < 6; i++)
    			TogglePlayerDynamicCP(playerid, PorterLoad[i], false);

	    	for(new i = 0; i < 5; i++)
    			TogglePlayerDynamicCP(playerid, PorterUnload[i], false);
    			
			new
			    frmt_worked[90],
				frmt_gametext[15];

			if(temp_porter_amount[playerid])
				format(frmt_worked, sizeof frmt_worked, "Вы закончили работу {ABD1BB}грузчиком. {FFFFFF}Заработано: {8D2424}$%d", temp_porter_amount[playerid]), SendClientMessage(playerid, COLOR_WHITE, frmt_worked);

			else
				SendClientMessage(playerid, COLOR_WHITE, !"Вы закончили работу {ABD1BB}грузчиком.");


			GiveMoney(playerid, temp_porter_amount[playerid], "работа грузчиком");

            if(temp_porter_amount[playerid])
            {
				format(frmt_gametext, sizeof frmt_gametext, "~g~+$%d", temp_porter_amount[playerid]);
				GameTextForPlayer(playerid, frmt_gametext, 1000, 1);
			}
			
			temp_porter_amount[playerid] = 0;
			temp_porter_time[playerid] = 1;

			SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);

		}
		case 417:
		{
		    if(!response)
		        return 1;

			if(InJob[playerid] != 0)
				return SCM(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}В данный момент вы уже где-то работаете!");


			InJob[playerid] = 7;
            temp_auto_amount[playerid] = 1;
            temp_auto_amount[playerid] = 1;

            if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
				RemovePlayerAttachedObject(playerid, 0);
				
			if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
            	RemovePlayerAttachedObject(playerid, 9);
            	
 	 		PI[playerid][pOldSkin] = GetPlayerSkin(playerid);

            if(PI[playerid][pSex] == 1)
				SetPlayerSkinEx(playerid, 27);

			else if(PI[playerid][pSex] == 2)
			    SetPlayerSkinEx(playerid, 69);

			SendClientMessage(playerid, COLOR_WHITE, !"Вы устроились на работу {ABD1BB}сборщика автозапчастей");
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Теперь идите на {FFFF00}желтый маркер{FFFFFF}, чтобы взять детали.");

			temp_auto_varioty[playerid] = 5;
		}
		case 428:
		{
		    if(!response)
		        return 1;

            if(InJob[playerid] != 7)
                return 1;

            InJob[playerid] = 0;
            temp_auto_amount[playerid] = 0;


	    	if(IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid,0);

			new
			    frmt_worked[90],
				frmt_gametext[15];

			if(temp_auto_salary[playerid])
				format(frmt_worked, sizeof frmt_worked, "Вы закончили работу {ABD1BB}сборщика автозапчастей. {FFFFFF}Заработано: {8D2424}$%d", temp_auto_salary[playerid]), SendClientMessage(playerid, COLOR_WHITE, frmt_worked);
			else
			    SendClientMessage(playerid, COLOR_WHITE, !"Вы закончили работу {ABD1BB}сборщика автозапчастей.");
			    
			GiveMoney(playerid, temp_auto_salary[playerid], "работа авто");

			if(temp_auto_salary[playerid])
			{
				format(frmt_gametext, sizeof frmt_gametext, "~g~+$%d", temp_auto_salary[playerid]);
				GameTextForPlayer(playerid, frmt_gametext, 1000, 1);
			}
			temp_auto_salary[playerid] = 0;
			temp_auto_time[playerid] = 1;
			SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);
			if(temp_auto_object[playerid])
			{
				if(IsValidDynamicObject(temp_auto_object[playerid]))
					DestroyDynamicObject(temp_auto_object[playerid]);

				temp_auto_object[playerid] = 0;
			}

			temp_auto_varioty[playerid] = 0;
			DisablePlayerCheckpoint(playerid);
		}
		case 439:
		{
		    if(!response)
		        return 1;

			if(InJob[playerid] != 0)
				return SCM(playerid, COLOR_WHITE, "{FF2222}[Ошибка] {FFFFFF}В данный момент вы уже где-то работаете!");
				
			if(PI[playerid][pFraction])
	        	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы состоите во фракции");

			if(TotalCrupie > 4)
	        	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент казино не требуется крупье");

	 		PI[playerid][pOldSkin] = GetPlayerSkin(playerid);

	        if(PI[playerid][pSex] == 1)
				SetPlayerSkinEx(playerid, 171);

			else if(PI[playerid][pSex] == 2)
			    SetPlayerSkinEx(playerid, 172);
			    
            TotalCrupie++;
            InJob[playerid] = 8;

			SendClientMessage(playerid, COLOR_WHITE, !"Вы устроились на работу {FF0000}крупье{FFFFFF}. Крутите рулетку за столом");
		
		}
		case 442:
		{
		    if(!response)
		        return 1;

			if(InJob[playerid] != 8)
				return 1;

		    if(temp_table[playerid] != -1)
		    {
		        new table = temp_table[playerid];

                gTable[table][tCrup] = INVALID_PLAYER_ID;
                temp_table[playerid] = -1;

			}
			
			SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);

            TotalCrupie--;
            InJob[playerid] = 0;

			SendClientMessage(playerid, COLOR_GREEN, !"Вы закончили работу крупье");

		}
		case 699:
		{
		    if(!response)
		        return 1;

			if(InJob[playerid] != 0)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент вы уже где-то работаете!");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 5 || strval(inputtext) > 20)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное количество");
			
			if(PI[playerid][pMoney] < strval(inputtext)*1000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				
			InJob[playerid] = 9;

 	 		PI[playerid][pOldSkin] = GetPlayerSkin(playerid);

            if(PI[playerid][pSex] == 1)
				SetPlayerSkinEx(playerid, 158);

			else if(PI[playerid][pSex] == 2)
			    SetPlayerSkinEx(playerid, 157);

            pTemp[playerid][pFermTime] = strval(inputtext)*60;
            pTemp[playerid][pGrass] = 0;
            
            GiveMoney(playerid, -strval(inputtext)*1000, "аренда поля");
            
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы арендовали поле, собирайте наркотики с кустов");
		}
		case 700:
		{
		    if(!response)
		        return 1;

			if(InJob[playerid] != 9)
				return 1;

			SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);

            InJob[playerid] = 0;
            pTemp[playerid][pFermTime] = 0;
            pTemp[playerid][pGrass] = 0;
            
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы закончили аренду поля");
		}
		case 346:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;

			switch(listitem)
			{
			    case 0:
			    {
			        if(temp_bus_id[playerid] != INVALID_VEHICLE_ID) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Закончите работу (/end)");
					if(PI[playerid][pLevel] < 2) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Работа доступна с двух лет в штате");

			        PI[playerid][pJob] = 1;
			        UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы устроились водителем автобуса");
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь на ЛС/СФ вокзал и арендуйте автобус");
			    }
			    case 1:
			    {
					if(PI[playerid][pLevel] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Работа доступна с трех лет в штате");

			        PI[playerid][pJob] = 2;
			        UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы устроились таксистом");
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь на любой вокзал и арендуйте такси");
			    }
			    case 2:
			    {
					if(PI[playerid][pLevel] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Работа доступна с трех лет в штате");

			        PI[playerid][pJob] = JOB_MECHANIC;
			        UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы устроились работать механиком");
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь к машинам для начала работы (/gps - Работы - Механики)");
			    }
			    case 3:
			    {
					if(PI[playerid][pLevel] < 3) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Работа доступна с четырех лет в штате");

			        PI[playerid][pJob] = JOB_PRODUCT;
			        UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы устроились развозчикам заказов");
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь к машинам для начала работы (/gps - Работы - Развозчик заказов)");
			    }
			    case 4:
			    {
					if(PI[playerid][pLevel] < 4) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Работа доступна с четырех лет в штате");

			        PI[playerid][pJob] = 11;
			        UpdatePlayerData(playerid, "Job", PI[playerid][pJob]);
			        SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы устроились дальнобойщиком");
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь к машинам для начала работы (/gps - Работы - Дальнобойщики)");
			    }
			}
		
		}
		case 576:
		{
			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;
			    
            ShowPlayerDialogEx(playerid, 577, DIALOG_STYLE_LIST, !"Пожертвование", !"{FF7319}1.{FFFFFF} Пожертвовать средства\n{FF7319}2.{FFFFFF} Список крупнейших благотворителей", !"Далее", !"Закрыть");
		
		}
		case 577:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;

			switch(listitem)
			{
			    case 0:
			    {
				    new
				        search_player;

         			foreach(new i : Player)
					{
					    if(!PI[i][pID] || PI[i][pFraction] != 10)
							continue;

						if(!PI[i][pSubfraction])
							continue;
							
						if(PI[i][pRank] != 6)
						    continue;
						    
						search_player++;
					}

					if(search_player)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Пожертвование недоступно, т.к в Штате есть сотрудники мэрии");

					ShowPlayerDialogEx(playerid, 578, DIALOG_STYLE_INPUT, !"Пожертвование", !"{FFFFFF}Введите сумму для пожертвования:\n\n{AFAFAF}Значение от 10000$ до 10000000$", !"ОК", !"Отмена");
			    }
			    case 1:
			    {
					new
					    frmt_nom_message[950];
					    
			        strcat(frmt_nom_message, "{FFDA00}ТОП-10 крупнейших благотворителей{FFFFFF}\n\n");
					for(new i; i < 10; i++)
					{
					    if(GetString(gNickNomination[1][i], "The State"))
					        format(frmt_nom_message, sizeof frmt_nom_message, "%s-\n", frmt_nom_message);

					    else
							format(frmt_nom_message, sizeof frmt_nom_message, "%s%s - %d$\n", frmt_nom_message, gNickNomination[1][i], gPointsNomination[1][i]);
							
					}
			        ShowPlayerDialogEx(playerid, 576, DIALOG_STYLE_MSGBOX, !"Пожертвование", frmt_nom_message, !"Закрыть", !"");
			    }
			}
		}
		case 578:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;
			    
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 10000 || strval(inputtext) > 10000000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(PI[playerid][pMoney] < strval(inputtext))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

		    new
		        search_player;

       		foreach(new i : Player)
			{
			    if(!PI[i][pID] || PI[i][pFraction] != 10)
					continue;
					
				if(!PI[i][pSubfraction])
					continue;

				if(PI[i][pRank] != 8)
				    continue;
				    
				search_player++;
			}

			if(search_player)
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Пожертвование недоступно, т.к в Штате есть сотрудники мэрии");

			new
			    frmt_charity_message[130];

			format(frmt_charity_message, sizeof frmt_charity_message, "{FFC800}[Подсказка] {FFFFFF}Вы пожертвовали %d$ в фонд штата!", strval(inputtext));
			SendClientMessage(playerid, COLOR_WHITE, frmt_charity_message);
			
			GiveMoney(playerid, -strval(inputtext), "пожертвование");
			OrgInfo[9][oMoney] += strval(inputtext);
			PI[playerid][pCharity] += strval(inputtext);
			UpdatePlayerData(playerid, "Charity", PI[playerid][pCharity]);
			
			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);

			if(strval(inputtext) >= 5000000)
			{
			    format(frmt_charity_message, sizeof frmt_charity_message, "%s{FF182D} пожертвовал в фонд штата {FFFFFF}%d$", PN(playerid), strval(inputtext));
			    SendClientMessageToAll(0xFFFFFFFF, frmt_charity_message);
			    SendClientMessageToAll(COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Совершить пожертвование вы можете в любой Мэрии");
			}
		}
		case 571:
		{
		    if(!response)
		        return 1;
		
			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;

		    switch(listitem)
		    {
		        case 0:
				{
					if(PI[playerid][pGunLic] == YES_LICENSE)
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть лицензия на оружие");

				    new
				        search_player;

         			foreach(new i : Player)
					{
					    if(!PI[i][pID] || PI[i][pFraction] != 10)
							continue;
							
						if(!PI[i][pSubfraction])
							continue;

						if(PI[i][pRank] != 4)
						    continue;

						search_player++;
					}

					if(search_player)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Покупка недоступна, т.к в Штате есть сотрудники мэрии");


					ShowPlayerDialogEx(playerid, 572, DIALOG_STYLE_MSGBOX, !"Покупка лицензии на оружие", !"{FFFFFF}Стоимость лицензии: {FF0000}30000${FFFFFF}\nС помощью его Вы сможете пользоваться оружием", !"Купить", !"Отмена");
				}
				case 1:
				{
					if(PI[playerid][pCard])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть билет рекордсмена");

				    new
				        search_player;

         			foreach(new i : Player)
					{
					    if(!PI[i][pID] || PI[i][pFraction] != 10)
							continue;

						if(!PI[i][pSubfraction])
							continue;

						if(PI[i][pRank] != 6)
						    continue;

						search_player++;
					}

					if(search_player)
			            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Покупка недоступна, т.к в Штате есть сотрудники мэрии");


					ShowPlayerDialogEx(playerid, 579, DIALOG_STYLE_MSGBOX, !"Покупка билета рекордсмена", !"{FFFFFF}Стоимость билета: {FF0000}50000${FFFFFF}\nС помощью его Вы сможете участвовать в номинациях Аллеи Славы", !"Купить", !"Отмена");

				}
			}
		}
		case 635:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gFBIElevator[0]) && !IsPlayerInDynamicArea(playerid, gFBIElevator[1]) && !IsPlayerInDynamicArea(playerid, gFBIElevator[2]))
			    return 1;
			    
			if(listitem == 0)
			{
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, 2);
		        J_SetPlayerPos(playerid, -1587.8937,-1009.1750,1362.9705);
				J_SetPlayerFacingAngle(playerid, 271.1492);
				pTemp[playerid][pAntiAir] += 4;
			}
			else if(listitem == 1)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
		        J_SetPlayerPos(playerid, -2522.3201,-631.7582,148.1517);
				J_SetPlayerFacingAngle(playerid, 180.0000);
				pTemp[playerid][pAntiAir] += 4;
			}
		}
		case 636:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gFBIElevator[0]) && !IsPlayerInDynamicArea(playerid, gFBIElevator[1]) && !IsPlayerInDynamicArea(playerid, gFBIElevator[2]))
			    return 1;

			if(listitem == 0)
			{
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, 2);
		        J_SetPlayerPos(playerid, -1571.5186,-1003.0488,1441.7311);
				J_SetPlayerFacingAngle(playerid, 271.1492);
				pTemp[playerid][pAntiAir] += 4;
			}
			else if(listitem == 1)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
		        J_SetPlayerPos(playerid, -2522.3201,-631.7582,148.1517);
				J_SetPlayerFacingAngle(playerid, 180.0000);
				pTemp[playerid][pAntiAir] += 4;
			}
		}
		case 637:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gFBIElevator[0]) && !IsPlayerInDynamicArea(playerid, gFBIElevator[1]) && !IsPlayerInDynamicArea(playerid, gFBIElevator[2]))
			    return 1;

			if(listitem == 0)
			{
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, 2);
		        J_SetPlayerPos(playerid, -1571.5186,-1003.0488,1441.7311);
				J_SetPlayerFacingAngle(playerid, 271.1492);
				pTemp[playerid][pAntiAir] += 4;
			}
			else if(listitem == 1)
			{
				SetPlayerInterior(playerid, 1);
				SetPlayerVirtualWorld(playerid, 2);
		        J_SetPlayerPos(playerid, -1587.8937,-1009.1750,1362.9705);
				J_SetPlayerFacingAngle(playerid, 271.1492);
				pTemp[playerid][pAntiAir] += 4;
			}
		}
		case 572:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;
			    
			if(PI[playerid][pGunLic] == YES_LICENSE)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть лицензия на оружие");

			if(PI[playerid][pMoney] < 30000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

		    new
		        search_player;

       		foreach(new i : Player)
			{
			    if(!PI[i][pID] || PI[i][pFraction] != 10)
					continue;

				if(!PI[i][pSubfraction])
					continue;

				if(PI[i][pRank] != 4)
				    continue;

				search_player++;
			}

			if(search_player)
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Покупка недоступна, т.к в Штате есть сотрудники мэрии");

            PI[playerid][pGunLic] = YES_LICENSE;
            UpdatePlayerData(playerid, "GunLic", PI[playerid][pGunLic]);

            GiveMoney(playerid, -30000, "покупка лицензии на оружие");

			SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем, Вы приобрели лицензию на оружие");
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFCC00}/lic [ID игрока]{FFFFFF}, для показа лицензий другому игроку");

 			if(PI[playerid][pQuest] == 11 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			{
		        PI[playerid][pQuestProcess] = 1;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы выполнили задание, отправляйтесь к Линкольну");
			}
		}
		case 579:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;
			    
		    if(PI[playerid][pCard])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть билет рекордсмена");

			if(PI[playerid][pMoney] < 50000)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
			
		    new
		        search_player;

       		foreach(new i : Player)
			{
			    if(!PI[i][pID] || PI[i][pFraction] != 10)
					continue;

				if(!PI[i][pSubfraction])
					continue;

				if(PI[i][pRank] != 6)
				    continue;
			    
				search_player++;
			}

			if(search_player)
	            return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Покупка недоступна, т.к в Штате есть сотрудники мэрии");

            PI[playerid][pCard] = 1;
            UpdatePlayerData(playerid, "Card", PI[playerid][pCard]);
            
            GiveMoney(playerid, -50000, "покупка билета рекордсмена");
 			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Теперь все ваши рекорды записываются! У Вас появился шанс попасть на Аллею Славы!");

		}
		case 580:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;
			    
		    switch(listitem)
		    {
		        case 0:
				{
				    new
				        frmt_family_message[120];
				        
					new Cache:result = mysql_query(mysql, "SELECT `ID` FROM `family`");
					new total_family = cache_get_row_count(mysql);
					
					if(!total_family)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет созданных семей");
					
					format(frmt_family_message, sizeof frmt_family_message, "{FFFFFF}Зарегистрировано семей: {FF2222}%d{FFFFFF}\n\nВведите название семьи:\n\n", total_family);
					ShowPlayerDialogEx(playerid, 601, DIALOG_STYLE_INPUT, !"Поиск семьи", frmt_family_message, !"Поиск", !"Закрыть");
					
					cache_delete(result, mysql);
				}
				case 1:
				{
				    ShowPlayerDialogEx(playerid, 602, DIALOG_STYLE_INPUT, !"Создание семьи", !"{FFFFFF}Стоимость создания семьи: {33AA33}500{FFFFFF} рублей\n\nВведите название семьи:\n\n", !"Далее", !"Закрыть");
				}
				case 2: ShowFamilyList(playerid);
		    }
		}
		case 601:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;

			if(strfind(inputtext,"{") == -1 && strfind(inputtext,"}") == -1)
			{
				if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 26)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное название семьи");
			}
			else
			{
				if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 40)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное название семьи");
			}
			
			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
				
			new
			    query_family_search[130],
				frmt_family_info[590],
				nation[35],
				owner[24],
				subowner[24];
			    
			format(query_family_search, sizeof query_family_search, "SELECT `ID` FROM `family` WHERE `Name` = '%s'", inputtext);
			new Cache:result = mysql_query(mysql, query_family_search);
			
			if(!cache_get_row_count(mysql))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное название семьи"), cache_delete(result, mysql);
			    
			new fid = cache_get_row_int(0, 0);

		    switch(gFamily[fid-1][fNation])
			{
				case 1: strcat(nation,"Американцы");
				case 2: strcat(nation,"Русские");
				case 3: strcat(nation,"Французы");
				case 4: strcat(nation,"Мексиканцы");
				case 5: strcat(nation,"Латиноамериканцы");
				case 6: strcat(nation,"Испанцы");
				case 7: strcat(nation,"Португальцы");
				case 8: strcat(nation,"Японцы");
				case 9: strcat(nation,"Итальянцы");
				case 10: strcat(nation,"Англичане");
			}
			if(GetString(gFamily[fid-1][fOwner], "The State"))
				strcat(owner, "-");

			else
			    strcat(owner, gFamily[fid-1][fOwner]);

			if(GetString(gFamily[fid-1][fSubOwner], "The State"))
				strcat(subowner, "-");

			else
			    strcat(subowner, gFamily[fid-1][fSubOwner]);

			format(frmt_family_info, sizeof frmt_family_info, "\n\n\n{FFFFFF}Семья: {%s}%s\n\n{FFFFFF}Национальность: {FFC0CB}%s\n{FFFFFF}Состав семьи: {FFC0CB}%d{FFFFFF} игрок(ов)\n{FFFFFF}Онлайн: {FFC0CB}%d{FFFFFF} игрок(ов)\nДата образования: {FFC0CB}%s\n\n{FFFFFF}Создатель семьи: {F96161}%s\n{FFFFFF}Заместитель семьи: {F96161}%s", gFamilyColor[gFamily[fid-1][fColor]], gFamily[fid-1][fName], nation, gFamily[fid-1][fMembers], gFamily[fid-1][fOnline], gFamily[fid-1][fDate], owner, subowner);
			ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Информация о семье", frmt_family_info, !"Закрыть", !"");
			    
            cache_delete(result, mysql);
		
		}
		case 602:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;
			    
		    if(PI[playerid][pVirMoney] < 500)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Недостаточно средств на донат счете");
		        
		    if(PI[playerid][pFamily])
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть семья");
		        
			if(strfind(inputtext,"{") == -1 && strfind(inputtext,"}") == -1)
			{
				if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 26)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное название семьи");
			}
			else
			{
				if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 40)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное название семьи");
			}
			
			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			new Year, Month, Day, date[25], query_create[140];
			getdate(Year, Month, Day);
			format(date, sizeof date, "%d-%d-%d", Day, Month, Year);

            format(query_create, sizeof query_create, "INSERT INTO `family` VALUES ('', '%s', '%s', '%s', '%d', '1', '1', 'The State', '-1')", inputtext, PN(playerid), date, PI[playerid][pNation]);
			new Cache:result = mysql_query(mysql, query_create);
			new id = cache_insert_id(mysql);
			
			PI[playerid][pFamily] = id;
			UpdatePlayerData(playerid, "Family", PI[playerid][pFamily]);
			
			SetString(gFamily[id-1][fName], inputtext);
			SetString(gFamily[id-1][fOwner], PN(playerid));
			SetString(gFamily[id-1][fSubOwner], "The State");
			SetString(gFamily[id-1][fDate], date);
			gFamily[id-1][fNation] = PI[playerid][pNation];
			gFamily[id-1][fColor] = 1;
			gFamily[id-1][fOnline]++;
			gFamily[id-1][fMembers]++;
			gFamily[id-1][fPromo] = -1;
			
			family_count++;
			
			new
			    frmt_family_message[160];
			    
			format(frmt_family_message, sizeof frmt_family_message, "{7AC71F}[Успешно] {FFFFFF}Вы создали семью под названием \"%s\". Используйте /family для управления", inputtext);
			SendClientMessage(playerid, COLOR_WHITE, frmt_family_message);
			
			PI[playerid][pVirMoney] -= 500;
			UpdatePlayerData(playerid, "VirMoney", PI[playerid][pVirMoney]);
			
			cache_delete(result, mysql);
		}
		case 603:
		{
		    if(!response)
		        return 1;

			if(!IsPlayerInDynamicArea(playerid, gHall[0]) && !IsPlayerInDynamicArea(playerid, gHall[1]) && !IsPlayerInDynamicArea(playerid, gHall[2]) && !IsPlayerInDynamicArea(playerid, gHall[3]))
			    return 1;
			    
			switch(listitem)
			{
			    case 0..19:
			    {
			        new
			            frmt_family_info[540],
						nation[35],
						owner[24],
						subowner[24];
			    
				    for(new f; f < family_list[playerid]; f++)
					{
				    	if(listitem == FamilyList[playerid][f])
				    	{
						    switch(gFamily[f][fNation])
							{
								case 1: strcat(nation,"Американцы");
								case 2: strcat(nation,"Русские");
								case 3: strcat(nation,"Французы");
								case 4: strcat(nation,"Мексиканцы");
								case 5: strcat(nation,"Латиноамериканцы");
								case 6: strcat(nation,"Испанцы");
								case 7: strcat(nation,"Португальцы");
								case 8: strcat(nation,"Японцы");
								case 9: strcat(nation,"Итальянцы");
								case 10: strcat(nation,"Англичане");
							}
							if(GetString(gFamily[f][fOwner], "The State"))
								strcat(owner, "-");
								
							else
							    strcat(owner, gFamily[f][fOwner]);

							if(GetString(gFamily[f][fSubOwner], "The State"))
								strcat(subowner, "-");

							else
							    strcat(subowner, gFamily[f][fSubOwner]);

							format(frmt_family_info, sizeof frmt_family_info, "\n\n\n{FFFFFF}Семья: {%s}%s\n\n{FFFFFF}Национальность: {FFC0CB}%s\n{FFFFFF}Состав семьи: {FFC0CB}%d{FFFFFF} игрок(ов)\n{FFFFFF}Онлайн: {FFC0CB}%d{FFFFFF} игрок(ов)\nДата образования: {FFC0CB}%s\n\n{FFFFFF}Создатель семьи: {F96161}%s\n{FFFFFF}Заместитель семьи: {F96161}%s", gFamilyColor[gFamily[f][fColor]], gFamily[f][fName], nation, gFamily[f][fMembers], gFamily[f][fOnline], gFamily[f][fDate], owner, subowner);
							ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Информация о семье", frmt_family_info, !"Закрыть", !"");
							break;
				    	}
					}
			    }
			    case 20:
			    {
				    new
				        frmt_family_list[1900],
						family_name[64],
						query_family[140],
						frmt_family[100],
						family_total,
						id;

					format(query_family, sizeof query_family, "SELECT `ID`, `Name` FROM `family` WHERE `ID` > '%d' LIMIT 21", pTemp[playerid][pFamLast]-1);
					new Cache:result = mysql_query(mysql, query_family);
                    new rows = cache_get_row_count(mysql);

					if(!rows)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Нет созданных семей");

                    family_list[playerid] = rows;
					for(new i; i < rows; i++)
					{
    					id = cache_get_row_int(i, 0);
						cache_get_row(i, 1, family_name, mysql);

					    if(family_total > 19 && strlen(family_name) != 0)
					    {
					        format(frmt_family_list, sizeof frmt_family_list, "%s>> Следующая страница", frmt_family_list);
					        pTemp[playerid][pFamLast] = id;
					        break;
					    }
					    pTemp[playerid][pFamCount]++;
					    format(frmt_family, sizeof frmt_family, "{FF7319}%d.{FFFFFF} %s\n", pTemp[playerid][pFamCount]+1, family_name);

					    AddFamilyList(playerid, frmt_family_list, sizeof frmt_family_list, frmt_family, gFamily[i][fID], family_total);
					    family_total++;
					}
					ShowPlayerDialogEx(playerid, 603, DIALOG_STYLE_LIST, !"Список семей", frmt_family_list, !"Далее", !"Закрыть");
					cache_delete(result, mysql);
			    }
			}
		}
		case 604:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1;

			switch(listitem)
			{
			    case 0:
				{
				    new
				        nation[25],
						owner[MAX_PLAYER_NAME],
						subowner[MAX_PLAYER_NAME],
						frmt_family_info[550];
				        
				    switch(gFamily[famid][fNation])
					{
						case 1: strcat(nation,"Американцы");
						case 2: strcat(nation,"Русские");
						case 3: strcat(nation,"Французы");
						case 4: strcat(nation,"Мексиканцы");
						case 5: strcat(nation,"Латиноамериканцы");
						case 6: strcat(nation,"Испанцы");
						case 7: strcat(nation,"Португальцы");
						case 8: strcat(nation,"Японцы");
						case 9: strcat(nation,"Итальянцы");
						case 10: strcat(nation,"Англичане");
					}
					if(GetString(gFamily[famid][fOwner], "The State"))
						strcat(owner, "-");

					else
					    strcat(owner, gFamily[famid][fOwner]);

					if(GetString(gFamily[famid][fSubOwner], "The State"))
						strcat(subowner, "-");

					else
					    strcat(subowner, gFamily[famid][fSubOwner]);

					format(frmt_family_info, sizeof frmt_family_info, "\n\n\n{FFFFFF}Семья: {%s}%s\n\n{FFFFFF}Национальность: {FFC0CB}%s\n{FFFFFF}Состав семьи: {FFC0CB}%d{FFFFFF} игрок(ов)\n{FFFFFF}Онлайн: {FFC0CB}%d{FFFFFF} игрок(ов)\nДата образования: {FFC0CB}%s\n\n{FFFFFF}Создатель семьи: {F96161}%s\n{FFFFFF}Заместитель семьи: {F96161}%s", gFamilyColor[gFamily[famid][fColor]], gFamily[famid][fName], nation, gFamily[famid][fMembers], gFamily[famid][fOnline], gFamily[famid][fDate], owner, subowner);
					ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Информация о семье", frmt_family_info, !"Закрыть", !"");
				}
			    case 1:
			    {
                    pTemp[playerid][pLastIDFam] = 0;
                    
					new
						query_family_list[140],
						list_count,
						status[40],
						frmt_family_list[1900],
						nickname[MAX_PLAYER_NAME],
						lastlogin[10],
						bool:new_page;

					format(query_family_list, sizeof query_family_list, "SELECT `NickName`, `LastLogin` FROM `accounts` WHERE `Family` = '%d' LIMIT 0, 41", famid+1);
					new Cache:result = mysql_query(mysql, query_family_list);
                    new accounts = cache_get_row_count(mysql);

		      		if(0 == accounts)
					  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей семье никто не состоит");

					strcat(frmt_family_list, "№ Ник игрока\tПоследний заход\tСтатус\n");

		      		for(new i; i < accounts; i ++)
		      		{
		      		    if(list_count > 39 && accounts > 40)
						{
							format(frmt_family_list, sizeof frmt_family_list, "%s{FFFFFF}Следующая страница", frmt_family_list);
							new_page = true;
							
						    break;
						}
			  			cache_get_row(i, 0, nickname, mysql);
	                    cache_get_row(i, 1, lastlogin, mysql);

						if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
						    SetString(status, "{00CC44}[В сети]");

						else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
						    SetString(status, "{CD0000}[Не в сети]");

		      			format(frmt_family_list, sizeof frmt_family_list, "%s{FFFFFF}%d. %s\t%s\t%s\n", frmt_family_list, i+1, nickname, lastlogin, status);
			            list_count++;

		      		}
		      		if(new_page)
					  	ShowPlayerDialogEx(playerid, 605, DIALOG_STYLE_TABLIST_HEADERS, !"Состав семьи", frmt_family_list, !"Далее", !"Закрыть");

					else
					    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Состав семьи", frmt_family_list, !"Закрыть", !"");
					    
			        cache_delete(result, mysql);
			    }
			    case 2:
			    {
			        pTemp[playerid][pListFam] = 0;
			        
					new
					    frmt_online_list[1900],
						list_count,
						status[40],
						bool:new_page;

                    strcat(frmt_online_list, "ID\tНик игрока\tСтатус\n");
                    
      				foreach(new i : Player)
					{
					    if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
					        continue;
					        
						if(PI[i][pFamily] != famid+1)
						    continue;
						    
						list_count++;
						
						if(list_count > 40)
						{
							format(frmt_online_list, sizeof frmt_online_list, "%s{FFFFFF}Следующая страница", frmt_online_list);
							new_page = true;
							pTemp[playerid][pLastIDFam] = i+1;
						    break;
						}

						if(pl_afk_time[i] >= 3)
							format(status, sizeof status, "{FFA500}[AFK: %s]", Convert(pl_afk_time[i]));
						
						else
						    SetString(status, "{00CC44}[В сети]");
						    
						    
						format(frmt_online_list, sizeof frmt_online_list, "%s%d\t%s\t%s\n", frmt_online_list, i, PN(i), status);
						pTemp[playerid][pListFam]++;
						
					}
					if(!list_count)
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В семье нет никого онлайн");
					    
		      		if(new_page)
					  	ShowPlayerDialogEx(playerid, 606, DIALOG_STYLE_TABLIST_HEADERS, !"Состав семьи {00CC44}Online", frmt_online_list, !"Далее", !"Закрыть");

					else
					    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Состав семьи {00CC44}Online", frmt_online_list, !"Закрыть", !"");

			    }
				case 3:
				{
				    if(!GetString(gFamily[famid][fOwner], PN(playerid)) && !GetString(gFamily[famid][fSubOwner], PN(playerid)))
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу или заместителю семьи");

					ShowPlayerDialogEx(playerid, 607, DIALOG_STYLE_LIST, !"Выберите цвет:", !"1. Белый\n{505050}2. Черный\n{33CCFF}3. Голубой\n{FF0000}4. Красный\n{FFFF00}5. Желтый\n{0066FF}6. Синий\n{AFAFAF}7. Серый\n{E75480}8. Розовый\n{F5F5DC}9. Бежевый\n{FF00FF}10. Пурпурный", !"Выбор", !"Отмена");
				}
				case 4:
				{
				    if(!GetString(gFamily[famid][fOwner], PN(playerid)) && !GetString(gFamily[famid][fSubOwner], PN(playerid)))
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу или заместителю семьи");

					ShowPlayerDialogEx(playerid, 608, DIALOG_STYLE_LIST, !"Выберите национальность:", !"Американцы\nРусские\nФранцузы\nМексиканцы\nЛатиноамериканцы\nИспанцы\nПортугальцы\nЯпонцы\nИтальянцы\nАнгличане", !"Выбор", !"Отмена");
				}
				case 5:
				{
					new
						frmt_nation_change[90],
						nation[30];

				    switch(gFamily[famid][fNation])
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

					format(frmt_nation_change, sizeof frmt_nation_change, "{FFFFFF}Вы действительно хотите сменить свою национальность на \"%s\"?", nation);
				    ShowPlayerDialogEx(playerid, 609, DIALOG_STYLE_MSGBOX, !"Смена национальности", frmt_nation_change, !"Да", !"Отмена");
				
				}
				case 6:
				{
				    if(!GetString(gFamily[famid][fOwner], PN(playerid)) && !GetString(gFamily[famid][fSubOwner], PN(playerid)))
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу или заместителю семьи");

				    ShowPlayerDialogEx(playerid, 610, DIALOG_STYLE_INPUT, !"Смена названия семьи", !"{FFFFFF}Введите новое название семьи:\n\n{AFAFAF}Значение должно быть не более 16 символов", !"Сменить", !"Отмена");
				}
				case 7:
				{
				    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу семьи");

				    if(gFamily[famid][fPromo] == -1)
				    {
				        ShowPlayerDialogEx(playerid, 640, DIALOG_STYLE_INPUT, !"Создание промокода", !"{FFFFFF}Введите название промокода:\n\n{AFAFAF}Значение должно быть не более 24 символов", !"Создать", !"Отмена");
				    }
				    else
				    {
				        new
				            promoid = gFamily[famid][fPromo]-1;
				            
						if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
						    return 1;

						new
						    frmt_promo_menu[290];

					    format(frmt_promo_menu, sizeof frmt_promo_menu, "На счету: {33AA33}%d$\n{FF7319}1.{FFFFFF} Информация о промокоде\n{FF7319}2.{FFFFFF} Список использовавших\n{FF7319}3.{FFFFFF} Список использовавших {00CC00}Online\n{FF7319}4.{FFFFFF} Настройка вознаграждений\n{FF7319}5.{FFFFFF} Управление банком промокода", gPromo[promoid][pcBank]);

					    ShowPlayerDialogEx(playerid, 341, DIALOG_STYLE_LIST, !"Управление промокодом", frmt_promo_menu, !"Выбор", !"Отмена");
				    
				    }
				}
				case 8:
				{
				    if(GetString(gFamily[famid][fOwner], PN(playerid)))
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Владелец не может покинуть семью");

                    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы покинули семью");
                    
					new
						frmt_family_chat[180];

					format(frmt_family_chat, sizeof frmt_family_chat, "{%s}[%s]{FFCC99} %s[%d] покинул(а) семью", gFamilyColor[gFamily[famid][fColor]], gFamily[famid][fName], PN(playerid), playerid);

      				foreach(new i : Player)
					{
						if(IsPlayerConnected(i) && PI[i][pFamily] == famid+1)
							SendClientMessage(i, 0xFFCC99FF, frmt_family_chat);
					}
					

					gFamily[famid][fMembers]--;
					gFamily[famid][fOnline]--;

					if(GetString(gFamily[famid][fSubOwner], PN(playerid)))
					    SetString(gFamily[famid][fSubOwner], "The State");

					new
						query_family_save[170];

					format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `SubOwner` = '%s', `Members` = `Members`-1 WHERE `ID` = '%d'", gFamily[famid][fSubOwner], famid+1);
		            mysql_tquery(mysql, query_family_save);

					PI[playerid][pFamily] = 0;
					UpdatePlayerData(playerid, "Family", PI[playerid][pFamily]);
				}
			}
		
		}
		case 640:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1;
			    
		    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу семьи");

			if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 24)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное название промокода");

			new regex:r = regex_new("^[a-zA-Z_]+$");

			if(!regex_check(PN(playerid), r))
			{
		        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы! Доступны только буквы");
				J_Kick(playerid);
				return 1;
			}
		    regex_delete(r);
		    
			new Year, Month, Day, date[25], query_create[140];
			getdate(Year, Month, Day);
			format(date, sizeof date, "%d-%d-%d", Day, Month, Year);

            format(query_create, sizeof query_create, "INSERT INTO `promoyt` VALUES ('', '%s', '0', '0', '0', '1|1|4|50000', '%d')", inputtext, PI[playerid][pFamily]);
			new Cache:result = mysql_query(mysql, query_create);
			new id = cache_insert_id(mysql);

			SetString(gPromo[id-1][pcName], inputtext);
			gPromo[id-1][pcUsed] = 0;
			gPromo[id-1][pcOnline] = 0;
			gPromo[id-1][pcBank] = 0;
            gPromo[id-1][pcSettings][0] = 1;
            gPromo[id-1][pcSettings][1] = 1;
            gPromo[id-1][pcSettings][2] = 4;
            gPromo[id-1][pcSettings][3] = 50000;
            gPromo[id-1][pcOwnerID] = 0;
            gPromo[id-1][pcFOwnerID] = PI[playerid][pFamily];
			gFamily[PI[playerid][pFamily]-1][fPromo] = id;
			
			new
			    query_family_promo[70];
			    
			format(query_family_promo, sizeof query_family_promo, "UPDATE `family` SET `Promo` = '%d' WHERE `ID` = '%d'", id, PI[playerid][pFamily]);
			mysql_tquery(mysql, query_family_promo);


			new
			    frmt_family_message[160];

			format(frmt_family_message, sizeof frmt_family_message, "{7AC71F}[Успешно] {FFFFFF}Вы создали промокод под названием \"%s\". Используйте /family для управления", inputtext);
			SendClientMessage(playerid, COLOR_WHITE, frmt_family_message);

			cache_delete(result, mysql);
		}
		case 605:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1;

			if(listitem == 40)
			{
				new
					query_family_list[140],
					list_count,
					status[40],
					frmt_family_list[1900],
					nickname[MAX_PLAYER_NAME],
					lastlogin[10];

				format(query_family_list, sizeof query_family_list, "SELECT `NickName`, `LastLogin` FROM `accounts` WHERE `Family` = '%d' LIMIT %d, 41", famid+1, pTemp[playerid][pListFam]);
				new Cache:result = mysql_query(mysql, query_family_list);
                new accounts = cache_get_row_count(mysql);

	      		if(0 == accounts)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В вашей семье никто не состоит");

				strcat(frmt_family_list, "№ Ник игрока\tПоследний заход\tСтатус\n");

	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(list_count > 39 && accounts > 40)
					{
						format(frmt_family_list, sizeof frmt_family_list, "%s{FFFFFF}Следующая страница", frmt_family_list);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
                    cache_get_row(i, 1, lastlogin, mysql);

					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					    SetString(status, "{00CC44}[В сети]");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					    SetString(status, "{CD0000}[Не в сети]");

	      			format(frmt_family_list, sizeof frmt_family_list, "%s{FFFFFF}%d. %s\t%s\t%s\n", frmt_family_list, i+1, nickname, lastlogin, status);
		            pTemp[playerid][pListFam]++;
		            list_count++;

	      		}
	      		ShowPlayerDialogEx(playerid, 605, DIALOG_STYLE_TABLIST_HEADERS, !"Состав семьи", frmt_family_list, !"Далее", !"Назад");

		        cache_delete(result, mysql);
			}
		
		}
		case 606:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1;

			if(listitem == 40)
			{

				new
				    frmt_online_list[1900],
					list_count,
					status[40],
					bool:new_page,
					lastid = pTemp[playerid][pLastIDFam]-1;

                strcat(frmt_online_list, "ID\tНик игрока\tСтатус\n");

				for(new i = lastid, j = GetPlayerPoolSize(); i <= j; i++)
				{
				    if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
				        continue;

					if(PI[i][pFamily] != famid+1)
					    continue;

					list_count++;

					if(list_count > 40)
					{
						format(frmt_online_list, sizeof frmt_online_list, "%s{FFFFFF}Следующая страница", frmt_online_list);
						new_page = true;
						pTemp[playerid][pLastIDFam] = i+1;
					    break;
					}

					if(pl_afk_time[i] >= 3)
						format(status, sizeof status, "{FFA500}[AFK: %s]", Convert(pl_afk_time[i]));

					else
					    SetString(status, "{00CC44}[В сети]");


					format(frmt_online_list, sizeof frmt_online_list, "%s%d\t%s\t%s\n", frmt_online_list, i, PN(i), status);
					pTemp[playerid][pListFam]++;

				}
				if(0 == list_count)
				    return 1;

	      		if(new_page)
				  	ShowPlayerDialogEx(playerid, 606, DIALOG_STYLE_TABLIST_HEADERS, !"Состав семьи {00CC44}Online", frmt_online_list, !"Далее", !"Закрыть");

				else
				    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Состав семьи {00CC44}Online", frmt_online_list, !"Закрыть", !"");
			}
		}
		case 607:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1,
				query_family_save[110];

		    if(!GetString(gFamily[famid][fOwner], PN(playerid)) && !GetString(gFamily[famid][fSubOwner], PN(playerid)))
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу или заместителю семьи");

			gFamily[famid][fColor] = listitem;
			format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `Color` = '%d' WHERE `ID` = '%d'", gFamily[famid][fColor], famid+1);
			mysql_tquery(mysql, query_family_save);
			
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы изменили цвет рации семьи");
		}
		case 608:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1,
				query_family_save[110];

		    if(!GetString(gFamily[famid][fOwner], PN(playerid)) && !GetString(gFamily[famid][fSubOwner], PN(playerid)))
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу или заместителю семьи");

			gFamily[famid][fNation] = listitem+1;
			format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `Nation` = '%d' WHERE `ID` = '%d'", gFamily[famid][fNation], famid+1);
            mysql_tquery(mysql, query_family_save);
            
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы изменили национальность семьи");
		}
		case 609:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1;
			    
		    PI[playerid][pNation] = gFamily[famid][fNation];
		    UpdatePlayerData(playerid, "Nation", PI[playerid][pNation]);
		    
		    SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы изменили свою национальность на семейную");
		}
		case 610:
		{
		    if(!response)
		        return 1;

			if(!PI[playerid][pFamily])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не состоите в семье");

			new
			    famid = PI[playerid][pFamily]-1;
			    
		    if(!GetString(gFamily[famid][fOwner], PN(playerid)) && !GetString(gFamily[famid][fSubOwner], PN(playerid)))
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данная функция доступна владельцу или заместителю семьи");

			if(strfind(inputtext,"{") == -1 && strfind(inputtext,"}") == -1)
			{
				if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 26)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное название семьи");
			}
			else
			{
				if(!strlen(inputtext) || strlen(inputtext) < 3 || strlen(inputtext) > 40)
				    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком короткое/длинное название семьи");
			}
			
			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			new	query_family_save[130];

			SetString(gFamily[famid][fName], inputtext);
			format(query_family_save, sizeof query_family_save, "UPDATE `family` SET `Name` = '%s' WHERE `ID` = '%d'", inputtext, famid+1);
            mysql_tquery(mysql, query_family_save);

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы изменили название семьи");
		
		}
		case 341:
		{
		    if(!response)
		        return 1;
		        
			new
			    promoid = -1;
			    
			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;
			        
			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}
			
			if(promoid == -1)
			    return 1;
	    
			switch(listitem)
			{
			    case 0:
			    {
					new
					    frmt_promo_menu[290];

				    format(frmt_promo_menu, sizeof frmt_promo_menu, "На счету: {33AA33}%d$\n{FF7319}1.{FFFFFF} Информация о промокоде\n{FF7319}2.{FFFFFF} Список использовавших\n{FF7319}3.{FFFFFF} Список использовавших {00CC00}Online\n{FF7319}4.{FFFFFF} Настройка вознаграждений\n{FF7319}5.{FFFFFF} Управление банком промокода", gPromo[promoid][pcBank]);

				    ShowPlayerDialogEx(playerid, 341, DIALOG_STYLE_LIST, !"Управление промокодом", frmt_promo_menu, !"Выбор", !"Отмена");
			    }
			    case 1:
			    {
				    new
						frmt_promo_info[550],
						nickname[50];
						
                    if(PI[playerid][pCPromo])
						GetPlayerNameByID(gPromo[promoid][pcOwnerID], nickname);
						
					else
					    SetString(nickname, gFamily[PI[playerid][pFamily]-1][fName]);

					format(frmt_promo_info, sizeof frmt_promo_info, "\n\n\n{FFFFFF}Промокод: %s\n\n{FFFFFF}Количество использовавших: {FFC0CB}%d{FFFFFF} игрок(ов)\n{FFFFFF}Онлайн: {FFC0CB}%d{FFFFFF} игрок(ов)\n\n{FFFFFF}Владелец промокода: {F96161}%s", gPromo[promoid][pcName], gPromo[promoid][pcUsed], gPromo[promoid][pcOnline], nickname);
					ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Информация о промокоде", frmt_promo_info, !"Закрыть", !"");
			    }
			    case 2:
			    {
                    pTemp[playerid][pListPromo] = 0;

					new
						query_promo_list[140],
						list_count,
						status[40],
						frmt_promo_list[2900],
						nickname[MAX_PLAYER_NAME],
						salary,
						bool:new_page;

					format(query_promo_list, sizeof query_promo_list, "SELECT `NickName`, `PromoSalary` FROM `accounts` WHERE `Promo` = '%d' LIMIT 0, 41", promoid+1);
					new Cache:result = mysql_query(mysql, query_promo_list);
                    new accounts = cache_get_row_count(mysql);

		      		if(0 == accounts)
					  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш промокод никто не использовал");

					strcat(frmt_promo_list, "№ Ник игрока\tЗаработано в банк\tСтатус\n");

		      		for(new i; i < accounts; i ++)
		      		{
		      		    if(list_count > 39 && accounts > 40)
						{
							format(frmt_promo_list, sizeof frmt_promo_list, "%s{FFFFFF}Следующая страница", frmt_promo_list);
							new_page = true;

						    break;
						}
			  			cache_get_row(i, 0, nickname, mysql);
	                    salary = cache_get_row_int(i, 1);

						if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
						    SetString(status, "{00CC44}[В сети]");

						else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
						    SetString(status, "{CD0000}[Не в сети]");

		      			format(frmt_promo_list, sizeof frmt_promo_list, "%s{FFFFFF}%d. %s\t{33AA33}%d${FFFFFF}\t%s\n", frmt_promo_list, i+1, nickname, salary, status);
			            list_count++;

		      		}
		      		if(new_page)
					  	ShowPlayerDialogEx(playerid, 342, DIALOG_STYLE_TABLIST_HEADERS, !"Список использовавших", frmt_promo_list, !"Далее", !"Закрыть");

					else
					    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Список использовавших", frmt_promo_list, !"Закрыть", !"");

			        cache_delete(result, mysql);
			    
			    }
			    case 3:
			    {
			        pTemp[playerid][pListPromo] = 0;

					new
					    frmt_online_list[2900],
						list_count,
						status[40],
						bool:new_page;

                    strcat(frmt_online_list, "ID\tНик игрока\tЗаработано в банк\tСтатус\n");

      				foreach(new i : Player)
					{
					    if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
					        continue;
					
						if(PI[i][pPromo] != promoid+1)
						    continue;

						list_count++;

						if(list_count > 40)
						{
							format(frmt_online_list, sizeof frmt_online_list, "%s{FFFFFF}Следующая страница", frmt_online_list);
							new_page = true;
							pTemp[playerid][pListPromo] = i+1;
						    break;
						}

						if(pl_afk_time[i] >= 3)
							format(status, sizeof status, "{FFA500}[AFK: %s]", Convert(pl_afk_time[i]));

						else
						    SetString(status, "{00CC44}[В сети]");


						format(frmt_online_list, sizeof frmt_online_list, "%s%d\t%s\t{33AA33}%d${FFFFFF}\t%s\n", frmt_online_list, i, PN(i), PI[i][pPromoSalary], status);
						pTemp[playerid][pListPromo]++;

					}
					if(!list_count)
					    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Среди использовавших Ваш промокод нет никого онлайн");

		      		if(new_page)
					  	ShowPlayerDialogEx(playerid, 343, DIALOG_STYLE_TABLIST_HEADERS, !"Список использовавших {00CC44}Online", frmt_online_list, !"Далее", !"Закрыть");

					else
					    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Список использовавших {00CC44}Online", frmt_online_list, !"Закрыть", !"");
			    
			    }
			    case 4:
			    {
					new
					    frmt_promo_settings[390];
					    
					format(frmt_promo_settings, sizeof frmt_promo_settings, "{FF7319}1.{FFFFFF} Удвоенный опыт %s\n{FF7319}2.{FFFFFF} Удвоенная зарплата %s\n{FF7319}3.{FFFFFF} Уровень для получения бонуса [{FF9900}%d{FFFFFF}]\n{FF7319}4.{FFFFFF} Сумма бонуса [{33AA33}%d${FFFFFF}]", gPromo[promoid][pcSettings][0] ? ("[{33AA33}Включен{FFFFFF}]") : ("[{FF0000}Выключен{FFFFFF}]"), gPromo[promoid][pcSettings][1] ? ("[{33AA33}Включен{FFFFFF}]") : ("[{FF0000}Выключен{FFFFFF}]"), gPromo[promoid][pcSettings][2], gPromo[promoid][pcSettings][3]);
			        ShowPlayerDialogEx(playerid, 344, DIALOG_STYLE_LIST, !"Настройка вознаграждения", frmt_promo_settings, !"Выбор", !"Отмена");
			    }
			    case 5:
			    {
			        ShowPlayerDialogEx(playerid, 347, DIALOG_STYLE_LIST, !"Управление банком промокода", !"{FF7319}1.{FFFFFF} Положить деньги\n{FF7319}2.{FFFFFF} Снять деньги", !"Выбор", !"Отмена");
			    }
			}
	    
		}
		case 342:
		{
		    if(!response)
		        return 1;
		        
			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;
			    
			    
			if(listitem == 40)
			{
				new
					query_promo_list[140],
					list_count,
					status[40],
					frmt_promo_list[2900],
					nickname[MAX_PLAYER_NAME],
					salary;

				format(query_promo_list, sizeof query_promo_list, "SELECT `NickName`, `PromoSalary` FROM `accounts` WHERE `Promo` = '%d' LIMIT %d, 41", promoid+1, pTemp[playerid][pListPromo]);
				new Cache:result = mysql_query(mysql, query_promo_list);
                new accounts = cache_get_row_count(mysql);

	      		if(0 == accounts)
				  	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш промокод никто не использовал");

				strcat(frmt_promo_list, "№ Ник игрока\tЗаработано в банк\tСтатус\n");


	      		for(new i; i < accounts; i ++)
	      		{
	      		    if(list_count > 39 && accounts > 40)
					{
						format(frmt_promo_list, sizeof frmt_promo_list, "%s{FFFFFF}Следующая страница", frmt_promo_list);
					    break;
					}
		  			cache_get_row(i, 0, nickname, mysql);
                    salary = cache_get_row_int(i, 1);

					if(GetPlayerID(nickname) != INVALID_PLAYER_ID)
					    SetString(status, "{00CC44}[В сети]");

					else if(GetPlayerID(nickname) == INVALID_PLAYER_ID)
					    SetString(status, "{CD0000}[Не в сети]");

	      			format(frmt_promo_list, sizeof frmt_promo_list, "%s{FFFFFF}%d. %s\t{33AA33}%d${FFFFFF}\t%s\n", frmt_promo_list, i+1, nickname, salary, status);
		            pTemp[playerid][pListPromo]++;
		            list_count++;
	      		}
	      		ShowPlayerDialogEx(playerid, 342, DIALOG_STYLE_TABLIST_HEADERS, !"Список использовавших", frmt_promo_list, !"Далее", !"Назад");

		        cache_delete(result, mysql);
			}
			
		}
		case 343:
		{
		    if(!response)
		        return 1;

			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;
			    
			if(listitem == 40)
			{

				new
				    frmt_online_list[2900],
					list_count,
					status[40],
					bool:new_page,
					lastid = pTemp[playerid][pListPromo]-1;

                strcat(frmt_online_list, "ID\tНик игрока\tЗаработано в банк\tСтатус\n");

				for(new i = lastid, j = GetPlayerPoolSize(); i <= j; i++)
				{
				    if(!IsPlayerConnected(i) || !IsPlayerLogged[i] || IsPlayerNPC(i))
				        continue;

					if(PI[i][pPromo] != promoid+1)
					    continue;

					list_count++;

					if(list_count > 40)
					{
						format(frmt_online_list, sizeof frmt_online_list, "%s{FFFFFF}Следующая страница", frmt_online_list);
						new_page = true;
						pTemp[playerid][pListPromo] = i+1;
					    break;
					}

					if(pl_afk_time[i] >= 3)
						format(status, sizeof status, "{FFA500}[AFK: %s]", Convert(pl_afk_time[i]));

					else
					    SetString(status, "{00CC44}[В сети]");


					format(frmt_online_list, sizeof frmt_online_list, "%s%d\t%s\t{33AA33}%d${FFFFFF}\t%s\n", frmt_online_list, i, PN(i), PI[i][pPromoSalary], status);
					pTemp[playerid][pListPromo]++;

				}
				if(0 == list_count)
				    return 1;

	      		if(new_page)
				  	ShowPlayerDialogEx(playerid, 343, DIALOG_STYLE_TABLIST_HEADERS, !"Список использовавших {00CC44}Online", frmt_online_list, !"Далее", !"Закрыть");

				else
				    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, !"Список использовавших {00CC44}Online", frmt_online_list, !"Закрыть", !"");
			}
		}
		case 344:
		{
		    if(!response)
		        return 1;

			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;
			    
			switch(listitem)
			{
			    case 0:
			    {
			        if(gPromo[promoid][pcSettings][0])
			            gPromo[promoid][pcSettings][0] = 0, SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно отключили удвоенный опыт при активации промокода");
			        
			        else
			            gPromo[promoid][pcSettings][0] = 1, SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно включили удвоенный опыт при активации промокода");
			    }
			    case 1:
			    {
			        if(gPromo[promoid][pcSettings][1])
			            gPromo[promoid][pcSettings][1] = 0, SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно отключили удвоенную зарплату при активации промокода");

			        else
			            gPromo[promoid][pcSettings][1] = 1, SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно включили удвоенную зарплату при активации промокода");

			    }
			    case 2: ShowPlayerDialogEx(playerid, 345, DIALOG_STYLE_INPUT, !"Настройка вознаграждения", !"{FFFFFF}Введите уровень, при достижении которого игрок получит бонус:\n\n{AFAFAF}Значение должно быть от 3-х до 7-и", !"Принять", !"Отмена");
			    case 3: ShowPlayerDialogEx(playerid, 340, DIALOG_STYLE_INPUT, !"Настройка вознаграждения", !"{FFFFFF}Введите сумму бонуса, которую получит игрок при достижении требуемого уровня:\n\n{AFAFAF}Значение должно быть от 10000$ до 55000$", !"Принять", !"Отмена");
				
			}
			
		    new
		        query_save_settings[100];
		        
			format(query_save_settings, sizeof query_save_settings, "UPDATE `promoyt` SET `pcSettings` = '%d|%d|%d|%d' WHERE `pcID` = %d", gPromo[promoid][pcSettings][0], gPromo[promoid][pcSettings][1], gPromo[promoid][pcSettings][2], gPromo[promoid][pcSettings][3], promoid+1);
			mysql_tquery(mysql, query_save_settings);
		}
		case 345:
		{
		    if(!response)
		        return 1;

			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;

		    if(!strlen(inputtext) || !isNumeric(inputtext))
		        return ShowPlayerDialogEx(playerid, 345, DIALOG_STYLE_INPUT, !"Настройка вознаграждения", !"{FF0000}Вы ввели неверное значение\n\n{FFFFFF}Введите уровень, при достижении которого игрок получит бонус:\n\n{AFAFAF}Значение должно быть от 3-х до 7-и", !"Принять", !"Отмена");
		        
			if(strval(inputtext) < 3 || strval(inputtext) > 7)
		        return ShowPlayerDialogEx(playerid, 345, DIALOG_STYLE_INPUT, !"Настройка вознаграждения", !"{FF0000}Вы ввели неверное значение\n\n{FFFFFF}Введите уровень, при достижении которого игрок получит бонус:\n\n{AFAFAF}Значение должно быть от 3-х до 7-и", !"Принять", !"Отмена");

            gPromo[promoid][pcSettings][2] = strval(inputtext);
            SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили уровень для получения бонуса");
            
		    new
		        query_save_settings[100];

			format(query_save_settings, sizeof query_save_settings, "UPDATE `promoyt` SET `pcSettings` = '%d|%d|%d|%d' WHERE `pcID` = %d", gPromo[promoid][pcSettings][0], gPromo[promoid][pcSettings][1], gPromo[promoid][pcSettings][2], gPromo[promoid][pcSettings][3], promoid+1);
			mysql_tquery(mysql, query_save_settings);
			
		}
		case 340:
		{
		    if(!response)
		        return 1;

			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;

		    if(!strlen(inputtext) || !isNumeric(inputtext))
				return ShowPlayerDialogEx(playerid, 340, DIALOG_STYLE_INPUT, !"Настройка вознаграждения", !"{FF0000}Вы ввели неверное значение\n\n{FFFFFF}Введите сумму бонуса, которую получит игрок при достижении требуемого уровня:\n\n{AFAFAF}Значение должно быть от 10000$ до 55000$", !"Принять", !"Отмена");

			if(strval(inputtext) < 10000 || strval(inputtext) > 55000)
		        return ShowPlayerDialogEx(playerid, 340, DIALOG_STYLE_INPUT, !"Настройка вознаграждения", !"{FF0000}Вы ввели неверное значение\n\n{FFFFFF}Введите сумму бонуса, которую получит игрок при достижении требуемого уровня:\n\n{AFAFAF}Значение должно быть от 10000$ до 55000$", !"Принять", !"Отмена");

            gPromo[promoid][pcSettings][3] = strval(inputtext);
            SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили сумму бонуса");

		    new
		        query_save_settings[100];

			format(query_save_settings, sizeof query_save_settings, "UPDATE `promoyt` SET `pcSettings` = '%d|%d|%d|%d' WHERE `pcID` = %d", gPromo[promoid][pcSettings][0], gPromo[promoid][pcSettings][1], gPromo[promoid][pcSettings][2], gPromo[promoid][pcSettings][3], promoid+1);
			mysql_tquery(mysql, query_save_settings);

		}
		case 347:
		{
		    if(!response)
		        return 1;

			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;
			    
			    
			if(listitem == 0)
			    ShowPlayerDialogEx(playerid, 364, DIALOG_STYLE_INPUT, !"Положить деньги", !"{FFFFFF}Введите сумму:\n\n{AFAFAF}Значение должно быть от 1$ до 100000$", !"ОК", !"Отмена");
			    
			else if(listitem == 1)
			{
				new h, m, s, year, month, day;
				gettime(h,m,s);
				getdate(year, month, day);

				ShowPlayerDialogEx(playerid, 365, DIALOG_STYLE_INPUT, !"Снять деньги", !"{FFFFFF}Введите сумму:\n\n{AFAFAF}Значение должно быть от 1$ до 100000$", !"ОК", !"Отмена");
			}
		}
		case 364:
		{
		    if(!response)
		        return 1;

			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;

		    if(!strlen(inputtext) || !isNumeric(inputtext))
			    return ShowPlayerDialogEx(playerid, 364, DIALOG_STYLE_INPUT, !"Положить деньги", !"{FFFFFF}Введите сумму:\n\n{AFAFAF}Значение должно быть от 1$ до 100000$", !"ОК", !"Отмена");

			if(strval(inputtext) < 1 || strval(inputtext) > 100000)
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверную сумму");
                
			if(PI[playerid][pMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
			    
			GiveMoney(playerid, -strval(inputtext), "банк промо");
			
			gPromo[promoid][pcBank] += strval(inputtext);
			
		    new
		        query_save_bank[100];

			format(query_save_bank, sizeof query_save_bank, "UPDATE `promoyt` SET `pcBank` = '%d' WHERE `pcID` = %d", gPromo[promoid][pcBank], promoid+1);
			mysql_tquery(mysql, query_save_bank);
			
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы положили деньги в банк промокода");
			
			callcmd::promo(playerid);
		}
		case 365:
		{
		    if(!response)
		        return 1;

			new
			    promoid = -1;

			if(PI[playerid][pCPromo])
			{
			    promoid = PI[playerid][pCPromo]-1;

				if(gPromo[promoid][pcOwnerID] != PI[playerid][pID])
				    return 1;
			}
			else
			{
			    new
			        famid = PI[playerid][pFamily]-1;

			    if(!GetString(gFamily[famid][fOwner], PN(playerid)))
			        return 1;

			    if(gFamily[famid][fPromo] == -1)
			        return 1;

				promoid = gFamily[famid][fPromo]-1;

				if(gPromo[promoid][pcFOwnerID] != PI[playerid][pFamily])
				    return 1;
			}

			if(promoid == -1)
			    return 1;
			    


		    if(!strlen(inputtext) || !isNumeric(inputtext))
			    return ShowPlayerDialogEx(playerid, 365, DIALOG_STYLE_INPUT, !"Взять деньги", !"{FFFFFF}Введите сумму:\n\n{AFAFAF}Значение должно быть от 1$ до 100000$", !"ОК", !"Отмена");

			if(strval(inputtext) < 1 || strval(inputtext) > 100000)
                return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы ввели неверную сумму");
                
			if(gPromo[promoid][pcBank] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На счету промокода недостаточно средств");

			GiveMoney(playerid, strval(inputtext), "банк промо");

			gPromo[promoid][pcBank] -= strval(inputtext);

		    new
		        query_save_bank[100];

			format(query_save_bank, sizeof query_save_bank, "UPDATE `promoyt` SET `pcBank` = '%d' WHERE `pcID` = %d", gPromo[promoid][pcBank], promoid+1);
			mysql_tquery(mysql, query_save_bank);
			
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы сняли деньги с банка промокода");

			callcmd::promo(playerid);
		}
		case 479:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

		    switch(listitem)
		    {
				case 0:
				{
				    new
						frmt_kazna_list[640];

					format(frmt_kazna_list, sizeof frmt_kazna_list, "{FF7319}1.{FFFFFF} Министерство здравоохранения\t[{FFB0B0}%d${FFFFFF}]\n{FF7319}2.{FFFFFF} Министерство обороны\t\t[{FFB0B0}%d${FFFFFF}]\n{FF7319}3.{FFFFFF} Министерство внутренних дел\t[{FFB0B0}%d${FFFFFF}]\n{FF7319}4.{FFFFFF} Virtual. Media\t\t\t[{FFB0B0}%d${FFFFFF}]\n{FF7319}5.{FFFFFF} ФБР\t\t\t\t\t[{FFB0B0}%d${FFFFFF}]", OrgInfo[0][oMoney], OrgInfo[6][oMoney], OrgInfo[7][oMoney], OrgInfo[8][oMoney], OrgInfo[10][oMoney]);
					
					ShowPlayerDialogEx(playerid, 480, DIALOG_STYLE_LIST, !"Бюджет организаций", frmt_kazna_list, !"Далее", !"Отмена");
				}
				case 1: ShowPlayerDialogEx(playerid, 581, DIALOG_STYLE_LIST, !"Пенсионный фонд", !"{FF7319}1.{FFFFFF} Изменить пенсионный возраст\n{FF7319}2.{FFFFFF} Изменить пенсию", !"Далее", !"Отмена");
				case 2: ShowPlayerDialogEx(playerid, 587, DIALOG_STYLE_LIST, !"Выдача премий", !"{FF7319}1.{FFFFFF} Выдать премию организации\n{FF7319}2.{FFFFFF} Выдать премию игроку", !"Далее", !"Отмена");
				case 3: ShowPlayerDialogEx(playerid, 594, DIALOG_STYLE_LIST, !"Изменение налогообложения", !"{FF7319}1.{FFFFFF} Изменить налог на бизнес\n{FF7319}2.{FFFFFF} Изменить налог на зарплаты гос. огранизаций", !"Далее", !"Отмена");

		    }
		
		}
		case 480:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;
				
			new
			    frmt_kazna_pay[500];
			    
		    switch(listitem)
		    {
		        case 0:
		        {
		            format(frmt_kazna_pay, sizeof frmt_kazna_pay, "{FFFFFF}Выделение денег организации Министерство здравоохранения\n\nБюджет казны штата: {33AA00}%d${FFFFFF}\n\nБюджет Министерства здравоохранения: {33AA00}%d${FFFFFF}\n\n{AFAFAF}Максимальная сумма для выделения: 5000000$", OrgInfo[9][oMoney], OrgInfo[0][oMoney]);
		            ShowPlayerDialogEx(playerid, 582, DIALOG_STYLE_INPUT, !"Выделение денег", frmt_kazna_pay, !"Перевод", !"Отмена");
		        }
		        case 1:
		        {
		            format(frmt_kazna_pay, sizeof frmt_kazna_pay, "{FFFFFF}Выделение денег организации Министерство обороны\n\nБюджет казны штата: {33AA00}%d${FFFFFF}\n\nБюджет Министерства обороны: {33AA00}%d${FFFFFF}\n\n{AFAFAF}Максимальная сумма для выделения: 5000000$", OrgInfo[9][oMoney], OrgInfo[6][oMoney]);
		            ShowPlayerDialogEx(playerid, 583, DIALOG_STYLE_INPUT, !"Выделение денег", frmt_kazna_pay, !"Перевод", !"Отмена");
		        }
		        case 2:
		        {
		            format(frmt_kazna_pay, sizeof frmt_kazna_pay, "{FFFFFF}Выделение денег организации Министерство внутренних дел\n\nБюджет казны штата: {33AA00}%d${FFFFFF}\n\nБюджет Министерства внутренних дел: {33AA00}%d${FFFFFF}\n\n{AFAFAF}Максимальная сумма для выделения: 5000000$", OrgInfo[9][oMoney], OrgInfo[7][oMoney]);
		            ShowPlayerDialogEx(playerid, 584, DIALOG_STYLE_INPUT, !"Выделение денег", frmt_kazna_pay, !"Перевод", !"Отмена");
		        }
		        case 3:
		        {
		            format(frmt_kazna_pay, sizeof frmt_kazna_pay, "{FFFFFF}Выделение денег организации Virtual. Media\n\nБюджет казны штата: {33AA00}%d${FFFFFF}\n\nБюджет Virtual. Media: {33AA00}%d${FFFFFF}\n\n{AFAFAF}Максимальная сумма для выделения: 5000000$", OrgInfo[9][oMoney], OrgInfo[8][oMoney]);
		            ShowPlayerDialogEx(playerid, 585, DIALOG_STYLE_INPUT, !"Выделение денег", frmt_kazna_pay, !"Перевод", !"Отмена");
		        }
		        case 4:
		        {
		            format(frmt_kazna_pay, sizeof frmt_kazna_pay, "{FFFFFF}Выделение денег организации ФБР\n\nБюджет казны штата: {33AA00}%d${FFFFFF}\n\nБюджет ФБР: {33AA00}%d${FFFFFF}\n\n{AFAFAF}Максимальная сумма для выделения: 5000000$", OrgInfo[9][oMoney], OrgInfo[10][oMoney]);
		            ShowPlayerDialogEx(playerid, 586, DIALOG_STYLE_INPUT, !"Выделение денег", frmt_kazna_pay, !"Перевод", !"Отмена");
		        }
		    }
		}
		case 594:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;
				
			if(listitem == 0)
			{
			    new
			        frmt_change_business[180];

				format(frmt_change_business, sizeof frmt_change_business, "{FFFFFF}Введите новый процент налогообложения бизнесов\n\nТекущий: {FF0000}%d%%\n\n{AFAFAF}Значение должно быть от 0 до 8", gBusinessNalog);
				ShowPlayerDialogEx(playerid, 595, DIALOG_STYLE_INPUT, !"Изменение процента налогообложения", frmt_change_business, !"Изменить", !"Отмена");
			}
			else if(listitem == 1)
			{
			    new
			        frmt_change_salary[180];

				format(frmt_change_salary, sizeof frmt_change_salary, "{FFFFFF}Введите новый процент налогообложения сотрудников гос. организаций\n\nТекущий: {FF0000}%d%%\n\n{AFAFAF}Значение должно быть от 0 до 10", gSalaryNalog);
				ShowPlayerDialogEx(playerid, 596, DIALOG_STYLE_INPUT, !"Изменение процента налогообложения", frmt_change_salary, !"Изменить", !"Отмена");
			}
		}
		case 595:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 8)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный процент");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
				
			gBusinessNalog = strval(inputtext);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили процент налогообложения бизнесов");
		}
		case 596:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 10)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный процент");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			gSalaryNalog = strval(inputtext);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили процент налогообложения сотрудников гос. организаций");
		}
		case 581:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(listitem == 0)
			{
			    new
			        frmt_change_age[180];
			        
				format(frmt_change_age, sizeof frmt_change_age, "{FFFFFF}Введите минимальный возраст для получения пенсии\nТекущий возраст: %d лет в штате\n{AFAFAF}Значение должно быть не больше 30 и не меньше 15", gPensionAge);
				ShowPlayerDialogEx(playerid, 588, DIALOG_STYLE_INPUT, !"Изменение пенсионного возраста", frmt_change_age, !"Изменить", !"Отмена");
			}
		    else if(listitem == 1)
		    {
			    new
			        frmt_change_pension[140];

				format(frmt_change_pension, sizeof frmt_change_pension, "{FFFFFF}Введите сумму пенсии\nТекущая сумма: %d$\n{AFAFAF}Значение должно быть не больше 3000$ и не меньше 1500$", gPension);
				ShowPlayerDialogEx(playerid, 589, DIALOG_STYLE_INPUT, !"Изменение пенсии", frmt_change_pension, !"Изменить", !"Отмена");
		    }
		}
		case 587:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;
				
			if(listitem == 0)
				ShowPlayerDialogEx(playerid, 590, DIALOG_STYLE_LIST, !"Выберите организацию", !"{FF7319}1.{FFFFFF} Больница ЛС\n{FF7319}2.{FFFFFF} Больница СФ\n{FF7319}3.{FFFFFF} Больница ЛВ\n{FF7319}4.{FFFFFF} Армия ЛС\n{FF7319}5.{FFFFFF} Армия СФ\n{FF7319}6.{FFFFFF} LSPD\n{FF7319}7.{FFFFFF} SFPD\n{FF7319}8.{FFFFFF} LVPD\n{FF7319}9.{FFFFFF} Правительство\n{FF7319}10.{FFFFFF} Мэрия ЛС\n{FF7319}11.{FFFFFF} Мэрия СФ\n{FF7319}12.{FFFFFF} Мэрия ЛВ\n{FF7319}13.{FFFFFF} Радиоцентр ЛС\n{FF7319}14.{FFFFFF} Радиоцентр СФ\n{FF7319}15.{FFFFFF} Радиоцентр ЛВ\n{FF7319}16.{FFFFFF} ФБР", !"Далее", !"Отмена");

			else if(listitem == 1)
				ShowPlayerDialogEx(playerid, 591, DIALOG_STYLE_INPUT, !"Выдача премии игроку", !"{FFFFFF}Введите ID игрока, которому хотите выдать премию:", !"Далее", !"Отмена");

		}
		case 590:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gBonusSend > 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы выдали максимальное число премий за день");

			switch(listitem)
			{
			    case 0: pTemp[playerid][pBonusFraction] = 1, pTemp[playerid][pBonusSubfraction] = 1;
			    case 1: pTemp[playerid][pBonusFraction] = 1, pTemp[playerid][pBonusSubfraction] = 2;
				case 2: pTemp[playerid][pBonusFraction] = 1, pTemp[playerid][pBonusSubfraction] = 3;
				case 3: pTemp[playerid][pBonusFraction] = 7, pTemp[playerid][pBonusSubfraction] = 1;
				case 4: pTemp[playerid][pBonusFraction] = 7, pTemp[playerid][pBonusSubfraction] = 2;
				case 5: pTemp[playerid][pBonusFraction] = 8, pTemp[playerid][pBonusSubfraction] = 1;
				case 6: pTemp[playerid][pBonusFraction] = 8, pTemp[playerid][pBonusSubfraction] = 2;
				case 7: pTemp[playerid][pBonusFraction] = 8, pTemp[playerid][pBonusSubfraction] = 3;
				case 8: pTemp[playerid][pBonusFraction] = 10, pTemp[playerid][pBonusSubfraction] = 0;
				case 9: pTemp[playerid][pBonusFraction] = 10, pTemp[playerid][pBonusSubfraction] = 1;
				case 10: pTemp[playerid][pBonusFraction] = 10, pTemp[playerid][pBonusSubfraction] = 2;
				case 11: pTemp[playerid][pBonusFraction] = 10, pTemp[playerid][pBonusSubfraction] = 3;
				case 12: pTemp[playerid][pBonusFraction] = 9, pTemp[playerid][pBonusSubfraction] = 1;
				case 13: pTemp[playerid][pBonusFraction] = 9, pTemp[playerid][pBonusSubfraction] = 2;
				case 14: pTemp[playerid][pBonusFraction] = 9, pTemp[playerid][pBonusSubfraction] = 3;
				case 15: pTemp[playerid][pBonusFraction] = 11, pTemp[playerid][pBonusSubfraction] = 0;
			}
			ShowPlayerDialogEx(playerid, 592, DIALOG_STYLE_INPUT, !"Выдача премии", !"{FFFFFF}Введите сумму премии:\n\n{AFAFAF}Значение должно быть не больше 10000$ и не меньше 2000$", !"Выдать", !"Отмена");
		
		}
		case 592:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gBonusSend > 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы выдали максимальное число премий за день");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 2000 || strval(inputtext) > 10000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма");

			if(OrgInfo[9][oMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете недостаточно средств");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			new
			    frid = pTemp[playerid][pBonusFraction],
			    subid = pTemp[playerid][pBonusSubfraction],
				frmt_bonus_message[100];
			    
			format(frmt_bonus_message, sizeof frmt_bonus_message, "{FFD1DC}%s{FFFFFF} выдал премию вашей организации в размере {819d97}%d$", PN(playerid), strval(inputtext));
   			foreach(new i : Player)
            {
                if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
					continue;
					
                if(PI[i][pFraction] == frid && PI[i][pSubfraction] == subid)
                {
                    SendClientMessage(i, COLOR_WHITE, frmt_bonus_message);
				 	OrgInfo[9][oMoney] -= strval(inputtext);
      				PI[i][pBonus] = strval(inputtext);
		            UpdatePlayerData(i, "Bonus", PI[i][pBonus]);

				}

            }
            
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выдали премию сотрудникам организации");
			gBonusSend++;

			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);

		}
		case 591:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gBonusSend > 3)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы выдали максимальное число премий за день");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) == INVALID_PLAYER_ID || !IsPlayerConnected(strval(inputtext)) || !IsPlayerLogged[strval(inputtext)])
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверный ID игрока");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
				
			new
				target = strval(inputtext);
				
		    pTemp[playerid][pBonusPlayerID] = target;
		    
		    if(!PI[target][pFraction])
		    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит во фракции");

			switch(PI[target][pFraction])
			{
			    case 1: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 7: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 8: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 9: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 10: if(PI[target][pSubfraction] < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 11: if(PI[target][pSubfraction] != 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				default: return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
			}
			ShowPlayerDialogEx(playerid, 593, DIALOG_STYLE_INPUT, !"Выдача премии игроку", !"{FFFFFF}Введите сумму премии:\n\n{AFAFAF}Значение должно быть не больше 10000$ и 2000$", !"Выдать", !"Отмена");
		}
		case 593:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gBonusSend > 3)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы выдали максимальное число премий за день");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 2000 || strval(inputtext) > 10000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма");

			if(OrgInfo[9][oMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете недостаточно средств");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");
				
			new
				target = pTemp[playerid][pBonusPlayerID];

		    if(!PI[target][pFraction])
		    	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Игрок не состоит во фракции");

			switch(PI[target][pFraction])
			{
			    case 1: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 7: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 8: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 9: if(!PI[target][pSubfraction]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 10: if(PI[target][pSubfraction] < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				case 11: if(PI[target][pSubfraction] != 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
				default: return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выдать премию данному игроку");
			}
		    OrgInfo[9][oMoney] -= strval(inputtext);

			new
				frmt_bonus_message[100];

			format(frmt_bonus_message, sizeof frmt_bonus_message, "{FFD1DC}%s{FFFFFF} выдал Вам премию в размере {819d97}%d$", PN(playerid), strval(inputtext));
			SendClientMessage(target, COLOR_WHITE, frmt_bonus_message);

			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);
			
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выдали премию сотруднику организации");
			PI[target][pBonus] = strval(inputtext);
            UpdatePlayerData(target, "Bonus", PI[target][pBonus]);
            gBonusSend++;
		}
		case 582:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gKaznaSend[0] > 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы превысили лимит переводов в день");
			    
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 5000000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма");
			    
			if(OrgInfo[9][oMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете недостаточно средств");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            OrgInfo[9][oMoney] -= strval(inputtext);
            OrgInfo[0][oMoney] += strval(inputtext);

			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);
			
            new
                query_money_upt[100];
                
			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 1", OrgInfo[0][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 10", OrgInfo[9][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выделили деньги организации Министерство здравоохранения");
			gKaznaSend[0]++;
		}
		case 583:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gKaznaSend[6] > 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы превысили лимит переводов в день");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 5000000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма");

			if(OrgInfo[9][oMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете недостаточно средств");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            OrgInfo[9][oMoney] -= strval(inputtext);
            OrgInfo[6][oMoney] += strval(inputtext);

			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);
			
            new
                query_money_upt[100];

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 7", OrgInfo[6][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 10", OrgInfo[9][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выделили деньги организации Министерство обороны");
			gKaznaSend[6]++;
		}
		case 584:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gKaznaSend[7] > 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы превысили лимит переводов в день");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 5000000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма");

			if(OrgInfo[9][oMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете недостаточно средств");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            OrgInfo[9][oMoney] -= strval(inputtext);
            OrgInfo[7][oMoney] += strval(inputtext);

			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);
			
            new
                query_money_upt[100];

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 8", OrgInfo[7][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 10", OrgInfo[9][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выделили деньги организации Министерство внутренних дел");
			gKaznaSend[7]++;

		}
		case 585:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(gKaznaSend[8] > 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы превысили лимит переводов в день");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 5000000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма");

			if(OrgInfo[9][oMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете недостаточно средств");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            OrgInfo[9][oMoney] -= strval(inputtext);
            OrgInfo[8][oMoney] += strval(inputtext);

			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);
			
            new
                query_money_upt[100];

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 9", OrgInfo[8][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 10", OrgInfo[9][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выделили деньги организации Virtual. Media");
			gKaznaSend[8]++;
		}
		case 586:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;
				
			if(gKaznaSend[10] > 2)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы превысили лимит переводов в день");

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 5000000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверная сумма");

			if(OrgInfo[9][oMoney] < strval(inputtext))
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В бюджете недостаточно средств");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

            OrgInfo[9][oMoney] -= strval(inputtext);
            OrgInfo[10][oMoney] += strval(inputtext);

			new
			    frmt_balance[128];

			format(frmt_balance, sizeof frmt_balance, "Бюджет штата: {BD4D4D}%d$", OrgInfo[9][oMoney]);
			UpdateDynamic3DTextLabelText(gFractionMoney[9], 0xFFFFFFFF, frmt_balance);
			
            new
                query_money_upt[100];

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 11", OrgInfo[10][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			format(query_money_upt, sizeof query_money_upt, "UPDATE `orginfo` SET `money` = '%d' WHERE `id` = 10", OrgInfo[9][oMoney]);
			mysql_tquery(mysql, query_money_upt);

			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно выделили деньги организации ФБР");
			gKaznaSend[10]++;
		}
		case 588:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;
				
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 15 || strval(inputtext) > 30)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			gPensionAge = strval(inputtext);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили минимальный пенсионный возраст");
		}
		case 589:
		{
		    if(!response)
		        return 1;

			if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
			    return 1;

            if(!IsPlayerInDynamicArea(playerid, gHallMoneyArea))
				return 1;

			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext) < 1500 || strval(inputtext) > 3000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Неверное значение");

			if(strfind(inputtext,"|") != -1)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Найдены запрещенные символы");

			gPension = strval(inputtext);
			SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно изменили сумму выплачиваемой пенсии");
		}
		case 412:
		{
		    if(!response)
		        return 1;

            if(!IsPlayerInDynamicArea(playerid, TrashArea))
				return 1;

			new
				amount = PI[playerid][pTrashWallet]*120 + PI[playerid][pTrashBottle]*90 + PI[playerid][pTrashBank]*75 + PI[playerid][pTrashPaper]*60 + PI[playerid][pTrashBung]*55 + PI[playerid][pTrashPhone]*350;

			GiveMoney(playerid, amount, "выдача мусора");
			
			new
			    frmt_trash_message[100];
			    
			format(frmt_trash_message, sizeof frmt_trash_message, "{7AC71F}[Успешно] {FFFFFF}Вы успешно продали весь имеющийся на руках мусор за %d$", amount);
			SendClientMessage(playerid, COLOR_WHITE, frmt_trash_message);

			
			PI[playerid][pTrashWallet] = 0;
			UpdatePlayerData(playerid, "TrashWallet", PI[playerid][pTrashWallet]);
			PI[playerid][pTrashBottle] = 0;
			UpdatePlayerData(playerid, "TrashBottle", PI[playerid][pTrashBottle]);
			PI[playerid][pTrashBank] = 0;
			UpdatePlayerData(playerid, "TrashBank", PI[playerid][pTrashBank]);
			PI[playerid][pTrashPaper] = 0;
			UpdatePlayerData(playerid, "TrashPaper", PI[playerid][pTrashPaper]);
			PI[playerid][pTrashBung] = 0;
			UpdatePlayerData(playerid, "TrashBung", PI[playerid][pTrashBung]);
			PI[playerid][pTrashPhone] = 0;
			UpdatePlayerData(playerid, "TrashPhone", PI[playerid][pTrashPhone]);
			return 1;
		}
		case 642:
		{
		    new businessid = InfoBiz[playerid];
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, BizInfo[businessid][bEnter_X],BizInfo[businessid][bEnter_Y],BizInfo[businessid][bEnter_Z])) return 1;
			if(!response)
			{
				if(businessid < 0) return 1;
				if(!GetString(BizInfo[businessid][bOwner],"The State")) return SendClientMessage(playerid, -1, "{AFAFAF}Ошибка: Этот бизнес уже кто-то купил.");
				new format_business_buy_accept[76];
				format(format_business_buy_accept, sizeof format_business_buy_accept, "{FFFFFF}Вы действительно хотите купить этот бизнес за {FF0000}$%d?", BizInfo[businessid][bCost]);
				ShowPlayerDialogEx(playerid, 643, DIALOG_STYLE_MSGBOX, "Бизнес", format_business_buy_accept, !"Да", !"Нет");
			}
			else
			{
			
			    if(BizInfo[businessid][bState] == 16 && PI[playerid][pAge] < 18)
			        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете зайти в этот бизнес так как Вам меньше 18-ти лет");

			    new bint = BizInfo[businessid][bBint]-1;
			    
				if(bint < 0 || bint >= MAX_BINTS)
					return SendClientMessage(playerid,COLOR_GREY,"Ошибка (#99)");

				if(BizInfo[businessid][bState] == 8)
					return ShowPlayerDialogEx(playerid, 740, DIALOG_STYLE_MSGBOX, !"Автосалон", !"{FFFFFF}Вы хотите войти в автосалон класса: Эконом?", !"Да", !"Нет");

				if(BizInfo[businessid][bState] == 9)
					return ShowPlayerDialogEx(playerid, 741, DIALOG_STYLE_MSGBOX, !"Автосалон", !"{FFFFFF}Вы хотите войти в автосалон класса: Средний?", !"Да", !"Нет");

				if(BizInfo[businessid][bState] == 10)
					return ShowPlayerDialogEx(playerid, 742, DIALOG_STYLE_MSGBOX, !"Автосалон", !"{FFFFFF}Вы хотите войти в автосалон класса: Элитный?", !"Да", !"Нет");

				if(BizInfo[businessid][bState] == 11)
					return ShowPlayerDialogEx(playerid, 743, DIALOG_STYLE_MSGBOX, !"Мотосалон", !"{FFFFFF}Вы хотите войти в мотосалон?", !"Да", !"Нет");

					
                justtp_exit[playerid] = true;

   				SetPlayerPos(playerid, BizInts[bint][bintX], BizInts[bint][bintY], BizInts[bint][bintZ]);
				    
				SetPlayerInterior(playerid, BizInts[bint][bintInterior]);
				SetPlayerVirtualWorld(playerid, businessid+1);

				SetPlayerFacingAngle(playerid, BizInts[bint][bintR]);
                BizEntered[playerid] = BizInfo[businessid][bID];
                BizInfo[businessid][bVisit] ++;
				if(BizInfo[businessid][bImprove][0])
					SendClientMessage(playerid, COLOR_GREY, !"В этом бизнесе имеется аптечка. Чтобы восстановить здоровье используйте {FFFFFF}/healup ({00CC00}$150{FFFFFF})");

			}
		}
		case 643:
		{
			if(!response)
				return 1;
				
			new
				businessid = InfoBiz[playerid];
				
			if(businessid < 0)
		 		return 1;
		 		
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, BizInfo[businessid][bEnter_X],BizInfo[businessid][bEnter_Y],BizInfo[businessid][bEnter_Z]))
				return 1;
				
			if(!GetString(BizInfo[businessid][bOwner],"The State"))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот бизнес уже кто-то купил.");

			if(PI[playerid][pMoney] < BizInfo[businessid][bCost])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
				
			if(PI[playerid][pBizKey])
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас уже есть бизнес");
				
			new query_business_buy[64 + 6 + 12];
			format(query_business_buy,sizeof(query_business_buy),"UPDATE `business` SET `Owner` = '%s' WHERE `id` = '%d'", PN(playerid), businessid+1);
			mysql_tquery(mysql, query_business_buy);
			
			SetString(BizInfo[businessid][bOwner],PN(playerid));
			SendClientMessage(playerid,COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Поздравляем, Вы купили бизнес. Не забывайте оплачивать его, иначе его продадут государству!");
			SendClientMessage(playerid,COLOR_WHITE,"{FFC800}[Подсказка] {FFFFFF}/business {ffffff}- панель управления бизнесом");
			BizInfo[businessid][bMoney] = 0;
			BizInfo[businessid][bDays] = 3;
			BizInfo[businessid][bProducts] = 100;
			KillTimer(BizInfo[businessid][bOrderTimer]);
			BizInfo[businessid][bProductsOrder] = 0;
			PI[playerid][pBizKey] = businessid+1;
			UpdatePlayerData(playerid, "BizKey", PI[playerid][pBizKey]);
   			PlayerPlaySound(playerid, 30800, 0.0, 0.0, 0.0);
			UpdateBiz(businessid,1);
			
            GiveMoney(playerid,-BizInfo[businessid][bCost]);
		}



		case 516:
		{
		    if(!response)
		        return 1;
		
		    switch(listitem)
		    {
		        case 0: FindTheNearestFilling(playerid);
		        case 1: FindTheNearestShop(playerid);
				case 2: FindTheNearestATM(playerid);
		        case 3: ShowPlayerDialogEx(playerid, 517, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Строитель дорог\n{FF7319}2.{FFFFFF} Грузчик\n{FF7319}3.{FFFFFF} Сборщик автозапчастей\n{FF7319}4.{FFFFFF} Дальнобойщик\n{FF7319}5.{FFFFFF} Стоянка механиков\n{FF7319}6.{FFFFFF} Стоянка развозчиков", !"Отметить", !"Назад");
		        case 4: ShowPlayerDialogEx(playerid, 518, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Ж/Д вокзал г. Лос Сантос\n{FF7319}2.{FFFFFF} Ж/Д вокзал г. Сан Фиерро\n{FF7319}3.{FFFFFF} Ж/Д вокзал г. Лас Вентурас\n{FF7319}4.{FFFFFF} Автовокзал г. Лос Сантос\n{FF7319}5.{FFFFFF} Автошкола\n{FF7319}6.{FFFFFF} Военкомат\n{FF7319}7.{FFFFFF} Церковь\n{FF7319}8.{FFFFFF} Полигон для стрельбы\n{FF7319}9.{FFFFFF} Казино Four Dragons\n{FF7319}10.{FFFFFF} Центр развлечений\n{FF7319}11.{FFFFFF} Пункт приема мусора", !"Отметить", !"Назад");
		        case 5: ShowPlayerDialogEx(playerid, 519, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Пункт выдачи номеров\n{FF7319}2.{FFFFFF} Автосалон эконом класса\n{FF7319}3.{FFFFFF} Автосалон среднего класса\n{FF7319}4.{FFFFFF} Автосалон спорт класса\n{FF7319}5.{FFFFFF} Моторынок\n{FF7319}6.{FFFFFF} Прокат лодок\n{FF7319}7.{FFFFFF} Тюнинг лоурайдерских авто\n{FF7319}8.{FFFFFF} Тюнинг авто эконом класса\n{FF7319}9.{FFFFFF} Тюнинг авто среднего класса\n{FF7319}10.{FFFFFF} Тюнинг авто спорт класса", !"Отметить", !"Назад");
		        case 6: ShowPlayerDialogEx(playerid, 520, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Администрация Губернатора\n{FF7319}2.{FFFFFF} Мэрия г. Лос Сантос\n{FF7319}3.{FFFFFF} Мэрия г. Сан Фиерро\n{FF7319}4.{FFFFFF} Мэрия г. Лас Вентурас\n{FF7319}5.{FFFFFF} Полиция г. Лос Сантос\n{FF7319}6.{FFFFFF} Полиция г. Сан Фиерро\n{FF7319}7.{FFFFFF} Полиция г. Лас Вентурас\n{FF7319}8.{FFFFFF} Федеральное Бюро Расследований\n{FF7319}9.{FFFFFF} Больница г. Лос Сантос\n{FF7319}10.{FFFFFF} Больница г. Сан Фиерро\n{FF7319}11.{FFFFFF} Больница г. Лас Вентурас\n{FF7319}12.{FFFFFF} Армия г. Сан Фиерро\n{FF7319}13.{FFFFFF} Армия г. Лас Вентурас\n{FF7319}14.{FFFFFF} Радиоцентр г. Лос Сантос\n{FF7319}15.{FFFFFF} Радиоцентр г. Сан Фиерро\n{FF7319}16.{FFFFFF} Радиоцентр г. Лас Вентурас\n{FF7319}17.{FFFFFF} Склад оружия", !"Отметить", !"Назад");
		        case 7: ShowPlayerDialogEx(playerid, 521, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Колумбийская мафия\n{FF7319}2.{FFFFFF} Cosa Nostra\n{FF7319}3.{FFFFFF} Якудза\n{FF7319}4.{FFFFFF} Ферма наркотиков\n{FF7319}5.{FFFFFF} Grove Street\n{FF7319}6.{FFFFFF} The Ballas\n{FF7319}7.{FFFFFF} Los Santos Vagos\n{FF7319}8.{FFFFFF} The Rifa\n{FF7319}9.{FFFFFF} Varios Los Aztecas", !"Отметить", !"Назад");
		        case 8: ShowPlayerDialogEx(playerid, 522, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Банк г. Лос Сантос\n{FF7319}2.{FFFFFF} Банк г. Сан Фиерро\n{FF7319}3.{FFFFFF} Банк г. Лас Вентурас", !"Отметить", !"Назад");
                case 9: ShowPlayerDialogEx(playerid, 523, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Отель г. Лос Сантос\n{FF7319}2.{FFFFFF} Отель г. Сан Фиерро\n{FF7319}3.{FFFFFF} Отель г. Лас Вентурас", !"Отметить", !"Назад");
				case 10: ShowBusinessList(playerid);
				case 11: ShowEatBusinessList(playerid);
				case 12:
				{
    				new
						frmt_fillings_gps[520 + 8];

				    for(new f; f < MAX_FILLING; f++)
			    	    format(frmt_fillings_gps, sizeof frmt_fillings_gps, "%s{FF7319}%d.{FFFFFF} АЗС №%d\n", frmt_fillings_gps, f+1, f+1);

				    ShowPlayerDialogEx(playerid, 524, DIALOG_STYLE_LIST, !"GPS", frmt_fillings_gps, !"Отметить", !"Назад");
				}
				case 13: ShowPlayerDialogEx(playerid, 526, DIALOG_STYLE_LIST, !"GPS", !"{FF7319}1.{FFFFFF} Саймон\n{FF7319}2.{FFFFFF} Линкольн", !"Отметить", !"Назад");
				case 14: SetPlayerCheckpointEx(playerid, 836.4671,-1857.3822,12.8672, 4.0);

		    }
		}
		case 526:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 1771.3352, -1884.2300, 13.5528, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, 380.8920, -2021.7834, 7.8359, 4.0);
			}
		}
		case 517:
		{
			if(!response)
			    return callcmd::gps(playerid);
			    
			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 793.9272, -1677.9297, 13.3386, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, 2804.0767, -2393.1914, 13.6297, 4.0);
			    case 2: SetPlayerCheckpointEx(playerid, -89.0521, -300.4857, 2.7646, 4.0);
			    case 3: ShowPlayerDialogEx(playerid, 5562, DIALOG_STYLE_LIST, !"GPS: Дальнобойщики", !"{FF7319}1.{ffffff} Склад города Лос-Сантос\n{FF7319}2. {ffffff}Склад города Сан-Фиерро\n{FF7319}3. {ffffff}Склад города Лас-Вентурас\n{FF7319}4. {ffffff}Место разгрузки\n{FF7319}5. {ffffff}Фуры дальнобойщиков", !"ОК", !"Отмена");
			    case 4: ShowPlayerDialogEx(playerid, 5569, DIALOG_STYLE_LIST, !"GPS: Стоянка механиков", !"{FF7319}1.{ffffff} Стоянка города Лос-Сантос\n{FF7319}2. {ffffff}Стоянка города Сан-Фиерро\n{FF7319}3. {ffffff}Стоянка города Лас-Вентурас", !"ОК", !"Отмена");
			    case 5: return SCM(playerid,-1,"Еще не добавлено");
			}
		}
		case 518:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 1769.7192,-1895.9072,13.5637, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, -1986.0857,138.2838,27.6875, 4.0);
			    case 2: SetPlayerCheckpointEx(playerid, 2840.1794,1290.6329,11.3906, 4.0);
			    case 3: SetPlayerCheckpointEx(playerid, 1154.4963,-1756.6682,13.6407, 4.0);
			    case 4: SetPlayerCheckpointEx(playerid, -2026.7058,-97.5154,35.1641, 4.0);
			    case 5: SetPlayerCheckpointEx(playerid, 1168.9066,1368.4146,10.8125, 4.0);
			    case 6: SetPlayerCheckpointEx(playerid, -1981.8387,1118.2524,53.1262, 4.0);
			    case 7: SetPlayerCheckpointEx(playerid, 802.5800,1679.5624,5.2813, 4.0);
			    case 8: SetPlayerCheckpointEx(playerid, 2028.2135,1007.9943,10.8203, 4.0);
			    case 9: SetPlayerCheckpointEx(playerid, 1770.4630,-1657.3369,14.4205, 4.0);
				case 10: SetPlayerCheckpointEx(playerid, 2135.7051, -1994.8478, 13.5469, 4.0);
			}
		}
		case 519:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 2310.3735,1786.5581,10.8203, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, 555.4962,-1287.9098,17.2482, 4.0);
			    case 2: SetPlayerCheckpointEx(playerid, -1969.2944,293.9325,35.1719, 4.0);
			    case 3: SetPlayerCheckpointEx(playerid, 1658.5321,2194.6401,10.8203, 4.0);
			    case 4: SetPlayerCheckpointEx(playerid, 2131.8174,-1145.1947,24.7219, 4.0);
			    case 5: SetPlayerCheckpointEx(playerid, 145.5798,-1812.8430,4.3668, 4.0);
			    case 6: SetPlayerCheckpointEx(playerid, 2644.6074,-2017.5452,13.5526, 4.0);
			    case 7: SetPlayerCheckpointEx(playerid, 1041.8275,-1031.9730,32.0430, 4.0);
			    case 8: SetPlayerCheckpointEx(playerid, -1935.5466,235.1082,34.3125, 4.0);
			    case 9: SetPlayerCheckpointEx(playerid, 2386.7634,1040.4299,10.8203, 4.0);
			}
		}
		case 520:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 1132.2310,-2036.9891,69.0078, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, 1481.2008,-1765.9036,18.7958, 4.0);
			    case 2: SetPlayerCheckpointEx(playerid, -2756.8206,375.7390,4.3343, 4.0);
			    case 3: SetPlayerCheckpointEx(playerid, 2385.2861,2465.8862,10.8203, 4.0);
			    case 4: SetPlayerCheckpointEx(playerid, 1545.5983,-1675.6794,13.5607, 4.0);
			    case 5: SetPlayerCheckpointEx(playerid, -1605.6273,717.3768,11.9977, 4.0);
			    case 6: SetPlayerCheckpointEx(playerid, 2287.0237,2426.2883,10.8203, 4.0);
			    case 7: SetPlayerCheckpointEx(playerid, -2520.6541,-621.7458,132.7392, 4.0);
			    case 8: SetPlayerCheckpointEx(playerid, 1178.3281,-1323.3054,14.1146, 4.0);
			    case 9: SetPlayerCheckpointEx(playerid, -2668.0662,632.3565,14.4531, 4.0);
			    case 10: SetPlayerCheckpointEx(playerid, 1607.5425,1823.4816,10.8203, 4.0);
			    case 11: SetPlayerCheckpointEx(playerid, -1529.5449,496.2219,7.1797, 4.0);
			    case 12: SetPlayerCheckpointEx(playerid, 353.1764,1785.9203,17.7430, 4.0);
			    //case 13: SetPlayerCheckpointEx(playerid, 157.3419,-330.6845,1.5781, 4.0);
			    case 13: SetPlayerCheckpointEx(playerid, 1654.2029,-1660.5878,22.5156, 4.0);
			    case 14: SetPlayerCheckpointEx(playerid, -1731.3290,789.9044,24.8921, 4.0);
			    case 15: SetPlayerCheckpointEx(playerid, 2127.5146,2364.5249,10.8203, 4.0);
			    case 16: SetPlayerCheckpointEx(playerid, -1468.1636,1489.6763,8.2578, 4.0);
			}
		}
		case 521:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 948.0238,1730.8521,8.8516, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, 1462.1313,2773.2864,10.8203, 4.0);
			    case 2: SetPlayerCheckpointEx(playerid, 2625.1777,1824.4978,11.0234, 4.0);
			    case 3: SetPlayerCheckpointEx(playerid, -1055.3300,-1195.6033,129.0935, 4.0);
			    case 4: SetPlayerCheckpointEx(playerid, 2492.0212,-1667.2654,13.3438, 4.0);
			    case 5: SetPlayerCheckpointEx(playerid, 2000.9445,-1128.1959,25.4809, 4.0);
			    case 6: SetPlayerCheckpointEx(playerid, 2787.3621,-1613.9683,10.9219, 4.0);
			    case 7: SetPlayerCheckpointEx(playerid, 2733.8882,-1952.4766,13.5469, 4.0);
			    case 8: SetPlayerCheckpointEx(playerid, 2186.0835,-1807.5199,13.3730, 4.0);
			}
		}
		case 522:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 1310.1263,-1379.6600,13.6971, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, -2655.7751,375.9885,4.3336, 4.0);
			    case 2: SetPlayerCheckpointEx(playerid, 2360.1951,2377.6501,10.8203, 4.0);

			}
		}
		case 523:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
			    case 0: SetPlayerCheckpointEx(playerid, 331.5169,-1517.6132,35.8672, 4.0);
			    case 1: SetPlayerCheckpointEx(playerid, -2724.8394,-314.3097,7.1875, 4.0);
			    case 2: SetPlayerCheckpointEx(playerid, 1973.8182,1623.2810,12.8616, 4.0);
			}
		}
		case 524:
		{
			if(!response)
			    return callcmd::gps(playerid);

			switch(listitem)
			{
				case 0..18:
				    SetPlayerCheckpointEx(playerid, gFillingBuy[listitem][0], gFillingBuy[listitem][1], gFillingBuy[listitem][2], 4.0);
			}
		}
		case 525:
		{
			if(!response)
			    return callcmd::gps(playerid);

		    for(new b; b < MAX_BIZ; b++)
			{
		    	if(listitem == BizList[playerid][b])
		    	{
			    	SetPlayerCheckpointEx(playerid, BizInfo[b-1][bEnter_X], BizInfo[b-1][bEnter_Y], BizInfo[b-1][bEnter_Z], 4.0);
			    	break;
		    	}
			}
		}
		case 217:
		{
		    if(!response)
				return 1;

			new
				businessid = BizEntered[playerid]-1;

			if(businessid < 0)
				return 1;

			switch(listitem)
			{
				case 0:
				{
					if(PI[playerid][pMoney] < 2500)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 20 > 0)
					{
						BizInfo[businessid][bProducts] -= 20;
						GiveBusinessMoney(businessid, 875);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],875/100*10);
					}
					UpdateBiz(businessid,1);
					
					GiveMoney(playerid, -2500, "имитатор");
					
					_GiveGun(playerid, 13, 1);

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели игрушку {86B9FF}\"Имитатор №1\"{FFFFFF}");
				}
				case 1:
				{
					if(PI[playerid][pMoney] < 3200)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 25 > 0)
					{
						BizInfo[businessid][bProducts] -= 25;
						GiveBusinessMoney(businessid, 1120);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],1120/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -3200, "имитатор");

					_GiveGun(playerid, 11, 1);

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели игрушку {86B9FF}\"Имитатор №2\"{FFFFFF}");
				}
				case 2:
				{
					if(PI[playerid][pMoney] < 4000)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 30 > 0)
					{
						BizInfo[businessid][bProducts] -= 30;
						GiveBusinessMoney(businessid, 1400);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],1400/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -4000, "имитатор");

					_GiveGun(playerid, 12, 1);

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели игрушку {86B9FF}\"Имитатор №3\"{FFFFFF}");
				}
				case 3:
				{
					if(PI[playerid][pMoney] < 5500)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 35 > 0)
					{
						BizInfo[businessid][bProducts] -= 35;
						GiveBusinessMoney(businessid, 1925);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],1925/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -5500, "имитатор");

					_GiveGun(playerid, 10, 1);

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели игрушку {86B9FF}\"Имитатор №4\"{FFFFFF}");
				}
				case 4:
				{
					if(PI[playerid][pMoney] < 15000)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 100 > 0)
					{
						BizInfo[businessid][bProducts] -= 100;
						GiveBusinessMoney(businessid, 5250);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],5250/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -15000, "сексшоп");

					SetPlayerSkinEx(playerid, 87);
					pTemp[playerid][pTempSkin] = true;

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели временную одежду {86B9FF}\"Пламенная душа\"{FFFFFF}");
                    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFFF00}/endskin{FFFFFF} чтобы выбросить одежду");
				}
				case 5:
				{
					if(PI[playerid][pMoney] < 17000)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 110 > 0)
					{
						BizInfo[businessid][bProducts] -= 110;
						GiveBusinessMoney(businessid, 5950);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],5950/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -17000, "сексшоп");

					SetPlayerSkinEx(playerid, 244);
					pTemp[playerid][pTempSkin] = true;

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели временную одежду {86B9FF}\"Ненасытная клубничка\"{FFFFFF}");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFFF00}/endskin{FFFFFF} чтобы выбросить одежду");
				}
				case 6:
				{
					if(PI[playerid][pMoney] < 20000)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 120 > 0)
					{
						BizInfo[businessid][bProducts] -= 120;
						GiveBusinessMoney(businessid, 7000);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],7000/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -20000, "сексшоп");

					SetPlayerSkinEx(playerid, 246);
					pTemp[playerid][pTempSkin] = true;

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели временную одежду {86B9FF}\"Плохой полицейский\"{FFFFFF}");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFFF00}/endskin{FFFFFF} чтобы выбросить одежду");
				}
				case 7:
				{
					if(PI[playerid][pMoney] < 20000)
						return SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");

					if(BizInfo[businessid][bProducts] - 130 > 0)
					{
						BizInfo[businessid][bProducts] -= 130;
						GiveBusinessMoney(businessid, 7000);
						if(BizInfo[businessid][bKrasher]) GiveFracBank(BizInfo[businessid][bKrasher],7000/100*10);
					}
					UpdateBiz(businessid,1);

					GiveMoney(playerid, -20000, "сексшоп");

					SetPlayerSkinEx(playerid, 178);
					pTemp[playerid][pTempSkin] = true;

					SendClientMessage(playerid, COLOR_WHITE, !"{7AC71F}[Успешно] {FFFFFF}Вы успешно приобрели временную одежду {86B9FF}\"Женщина кошка\"{FFFFFF}");
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Используйте {FFFF00}/endskin{FFFFFF} чтобы выбросить одежду");
				}
		    }
		}
		case 981:
		{
		    if(!response)
				return 1;

			new
				fillingid = temp_filling_buy_id[playerid];

			if(!GetString(gFillings[fillingid][fillingOwner], "The State"))
			    return SendClientMessage(playerid, COLOR_GREY, !"Данная АЗС уже приобретена кем-то");

			if(PI[playerid][pBizKey])
				return SendClientMessage(playerid, COLOR_GREY, !"У вас уже есть бизнес");

			if(PI[playerid][pMoney] < gFillings[fillingid][fillingPrice])
				return SendClientMessage(playerid, COLOR_GREY, !"У вас недостаточно денег");

			new
				query_buyfilling[135 + 5 + MAX_PLAYER_NAME + 16];

			format(query_buyfilling, sizeof query_buyfilling, "UPDATE `fillings` SET `OwnerID` = '%d', `Owner` = '%s', `Working` = '1', `Bank` = '0' WHERE `ID` = '%d'", PI[playerid][pID], PN(playerid), fillingid+1);
			mysql_tquery(mysql, query_buyfilling);

			PI[playerid][pBizKey] = fillingid + 1 + 1000;
			UpdatePlayerData(playerid, "BizKey", PI[playerid][pBizKey]);

			gFillings[fillingid][fillingOwnerID] = PI[playerid][pID];
			SetString(gFillings[fillingid][fillingOwner], PN(playerid));
			gFillings[fillingid][fillingWorking] = true;
			gFillings[fillingid][fillingBank] = 0;
			gFillings[fillingid][fillingDay] = 3;

            new
				frmt_transfer_log[60];

            format(frmt_transfer_log, sizeof frmt_transfer_log, "покупка АЗС(№%d)", fillingid);
			GiveMoney(playerid, -gFillings[fillingid][fillingPrice], frmt_transfer_log);

			SendClientMessage(playerid, COLOR_GREEN, !"Поздравляем вы купили АЗС.");
			SendClientMessage(playerid, COLOR_GREEN, !"Меню управления АЗС {FFFFFF}\"/filling\"");

			UpdateFillingText(fillingid);
			SaveFilling(fillingid);
		}
		case 982:
		{
		    if(!response)
				return 1;

			new
			    fillingid = GetPVarInt(playerid,"fillingid");

			switch(listitem)
			{
				case 0:
				{
				    new
				        frmt_filling_info[240 + MAX_PLAYER_NAME + 3 + 8 + 12 + 6 + 6 + 8 + 3];

				    format(frmt_filling_info, sizeof frmt_filling_info, "{FFFFFF}Общая информация:\nВладелец: {269BD8}%s\n{FFFFFF}Кол-во дней: {269BD8}%d\n{FFFFFF}Банк: {269BD8}%d$\n{FFFFFF}Состояние: %s\n\n", gFillings[fillingid][fillingOwner], gFillings[fillingid][fillingDay], gFillings[fillingid][fillingBank], (gFillings[fillingid][fillingWorking]) ? ("{33AA33}Работает") : ("{FF0000}Не работает"));
					format(frmt_filling_info, sizeof frmt_filling_info, "%s{4682B4}Количество топлива: %d/%d литров\n{FFFFFF}Оплата: {269BD8}$%d/день", frmt_filling_info, gFillings[fillingid][fillingFuel], gFillings[fillingid][fillingTanks], gFillings[fillingid][fillingPrice]/200);

					ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Управление АЗС", frmt_filling_info, !"OK", !"");
				}
				case 1:
				{
					new
						frmt_filling_price[95];

					format(frmt_filling_price, sizeof frmt_filling_price, "{FFFFFF}Установите новую цену для топлива (от 5$ до 100$)\nТекущая цена: ({33AA33}%d{FFFFFF})", gFillings[fillingid][fillingFuelPrice]);

					ShowPlayerDialogEx(playerid, 983, DIALOG_STYLE_INPUT, !"Управление АЗС", frmt_filling_price, !"Изменить", !"Назад");
				}
				case 2:
				    ShowPlayerDialogEx(playerid, 984, DIALOG_STYLE_LIST, !"Управление АЗС", !"{FF7319}1. {FFFFFF}Увеличить объем цистерны до 10000 литров {33AA33}125000$", !"Далее", !"Назад");
				    
				case 3:
				{
					new
					    frmt_filling_fuel[140];
					    
					format(frmt_filling_fuel, sizeof frmt_filling_fuel, "{FFFFFF}Укажите, сколько литров топлива вы хотите заказать\n\nЦена за 1 литр = 2$\nКоличество топлива: %d/%d литров", gFillings[fillingid][fillingFuel], gFillings[fillingid][fillingTanks]);
				    ShowPlayerDialogEx(playerid, 985, DIALOG_STYLE_INPUT, !"Заказ топлива", frmt_filling_fuel, !"ОК", !"Отмена");
				}
				
				case 4:
				{
					new
					    frmt_filling_fuel[140];

					format(frmt_filling_fuel, sizeof frmt_filling_fuel, "{FFFFFF}Укажите, сколько литров топлива вы хотите заказать\n\nЦена за 1 литр = 4$ (экспресс)\nКоличество топлива: %d/%d литров", gFillings[fillingid][fillingFuel], gFillings[fillingid][fillingTanks]);
				    ShowPlayerDialogEx(playerid, 972, DIALOG_STYLE_INPUT, !"Заказ топлива", frmt_filling_fuel, !"ОК", !"Отмена");
				}
				
				case 5:
				    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Управление АЗС", !"{FFFFFF}Для управления кассой воспользуйтесь {527DFF}банком{FFFFFF} или {527DFF}банкоматом", !"Закрыть", !"");

				case 6:
				{
					if(!gFillings[fillingid][fillingWorking])
					{
						gFillings[fillingid][fillingWorking] = true;
						GameTextForPlayer(playerid, "~g~open", 3000, 3);
						UpdateFillingText(fillingid);
					}
					else
					{
						gFillings[fillingid][fillingWorking] = false;
						GameTextForPlayer(playerid, "~r~close", 3000, 3);
						UpdateFillingText(fillingid);
					}
					callcmd::filling(playerid);
				}
				case 7:
				{
					new
					    frmt_filling_sell[112 + 8];

					format(frmt_filling_sell, sizeof frmt_filling_sell, "{FFFFFF}Вы хотите продать свою АЗС за $%d\n{AFAFAF}(Если хотите продать другому игроку используйте /sellfilling)", gFillings[fillingid][fillingPrice]);
					ShowPlayerDialogEx(playerid, 986, DIALOG_STYLE_MSGBOX, !"Управление АЗС", frmt_filling_sell, !"Да", !"Нет");
				}
				case 8: ShowFinancStatDialog(playerid, (fillingid+1)+1000);
			}
		}
		
