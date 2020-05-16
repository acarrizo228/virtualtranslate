// First File to Translate
public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	new model = GetVehicleModel(GetPlayerVehicleID(playerid));
    AntiCheatOFF[playerid][VEH_ROOT_HACK] = 2;
    pTemp[playerid][pAntiAir] = 4;
	foreach(new id: Player)
	{
	    if(GetPlayerVehicleID(playerid) == GetPlayerVehicleID(id)) pTemp[id][pAntiAir] = 4;
	}
    if(interiorid > 0 && strcmp(CarsInfo[model][csCategory], "Lowriders", true) == 0) SCM(playerid, 0xFF0000FF, "Внимание! В данный момент этот вид транспорта нельзя тюнинговать");
    return true;
}
stock ToggleTextDrawForPlayer(playerid, Text:textdraw, toggle)
{
	if(toggle) TextDrawShowForPlayer(playerid, textdraw);
	else TextDrawHideForPlayer(playerid, textdraw);
	return true;
}
stock PlayerTextDrawToggle(playerid, PlayerText:textdraw, toggle)
{
	if(toggle) PlayerTextDrawShow(playerid, textdraw);
	else PlayerTextDrawHide(playerid, textdraw);
	return true;
}
stock Float:fmax(Float:v1, Float:v2)
{
	return v1 > v2?v1:v2;
}
stock Float:fmin(Float:v1, Float:v2)
{
	return v1 < v2?v1:v2;
}
stock Float:jfloatsub(Float:value1, Float:value2)
{
	new Float:num1 = fmax(value1, value2);
	new Float:num2 = fmin(value1, value2);
	new Float:diff = (num1 - num2);
	if(diff > 300.0) diff = ( 360.0 - num1 ) + num2;
	return diff;
}

stock ResetDoorsStatus(carid)
{
	new status;
	//if(!IsAOwnableCar(carid)) status = false;
	//else status = CarInfo[GetVehicleID(carid)][cLock];
	SetDoorsStatus(carid, status);
	return status;
}


stock DeleteFromList(list[],templist[],name[])
{
	new ReadText[30];
    new File: file = fopen(list, io_read);
    new File: tempFile = fopen(templist, io_write);
	if (file)
	{
	    while( fread(file, ReadText, sizeof(ReadText)) )
		{
			if(!GetString(ReadText,name)) fwrite(tempFile, ReadText);
		}
		fclose(file);
		fclose(tempFile);
		fremove(list);
		file = fopen(list, io_write);
    	tempFile = fopen(templist, io_read);
    	while( fread(tempFile, ReadText, sizeof(ReadText)) ) fwrite(file, ReadText);
		fclose(file);
		fclose(tempFile);
		fremove(templist);
		return true;
	}
	return false;
}
stock AddFromList(list[], name[])
{
    new File: file = fopen(list, io_append);
	new string[256];
	format(string, sizeof(string), "%s\n", name);
	fwrite(file, string);
	fclose(file);
	return true;
}
stock VehicleSeatState(seat)
{
	new seatstate;
	switch(seat)
	{
	    case 0: seatstate = 2;
	    default: seatstate = PLAYER_STATE_PASSENGER;
	}
	return seatstate;
}
stock GetVehicleSeat(vehicleid, seatid)
{
	new playerid = VehicleSeat[vehicleid][seatid];
	if(IsPlayerInVehicle(playerid, vehicleid))
	{
	    if(GetPlayerState(playerid) == VehicleSeatState(seatid)) return playerid;
	}
	VehicleSeat[vehicleid][seatid] = INVALID_PLAYER_ID;
	return VehicleSeat[vehicleid][seatid];
}
public OnPlayerDisconnect(playerid, reason)
{
    for(new i = 0; i < total_players; i++)
    {
        if(iter_players[i] == playerid)
        {
            iter_players[i] = iter_players[--total_players];
            iter_players[total_players] = -1;
            break;
        }
    }
	RemovePlayerAttachedObject(playerid, 0);
	RemovePlayerAttachedObject(playerid, 1);
    if(IsPlayerNPC(playerid))return 1;
    if(IsPlayerLogged[playerid])aml(-2, playerid, "", PlayerIp[playerid],0); else aml(-4, playerid, "", PlayerIp[playerid],0);
	pTemp[playerid][pAntiAir] = 3;

	if(GetPVarInt(playerid,"objectcop"))
	{
		DestroyDynamicObject(GetPVarInt(playerid,"objectcop"));
  		if(Ships[playerid]) DestroyDynamicArea(Ships[playerid]);
       	if(IsValidDynamic3DTextLabel(JobText3D[playerid]))
			DestroyDynamic3DTextLabel(JobText3D[playerid]);
	}
	// обнуление стола для крупье
	if(InJob[playerid] == 8)
	{
		if(temp_table[playerid] != -1)
	  	{
	   		new table = temp_table[playerid];

			gTable[table][tCrup] = INVALID_PLAYER_ID;
	  		temp_table[playerid] = -1;

	  		InJob[playerid] = 0;
	  		TotalCrupie--;
		}
	}
	if(IsValidDynamic3DTextLabel(temp_bus_text[playerid])) DestroyDynamic3DTextLabel(temp_bus_text[playerid]);
	temp_bus_text[playerid] = NONE_3D_TEXT;
	if(PI[playerid][plveh]!=-1)
	{
		DestroyVehicle(PI[playerid][plveh]);
		PI[playerid][plveh]= -1;
	}
 	temp_godmode_target[playerid] = INVALID_PLAYER_ID;
    temp_godmode_health[playerid] = 0.0;
    temp_godmode_armour[playerid] = 0.0;
    if(temp_godmode_timer[playerid]) KillTimer(temp_godmode_timer[playerid]);
    if(PI[playerid][pCars] != 0)
    {
		new slot = GetCarSlot(PI[playerid][pCars]),vehicleid = CarInfo[slot][cVehID];

		CarInfo[slot][cFuel] = VehicleInfo[vehicleid][vFuel];
		CarInfo[slot][cMilage] = VehicleInfo[vehicleid][vMillage];

		mysql_query_string[0] = 0;
		format(mysql_query_string, sizeof mysql_query_string, "UPDATE `cars` SET `cFuel` = '%.2f', `cMilage` = '%.2f' WHERE `cOwnerID` = '%d'", CarInfo[slot][cFuel], CarInfo[slot][cMilage], PI[playerid][pID]);
		mysql_tquery(mysql, mysql_query_string);

        SaveOwnableCar(playerid, vehicleid);

		for(new tn; tn < 14; tn++)
			if(CarInfo[slot][cTuning][tn] != 0) RemoveVehicleComponent(CarInfo[slot][cVehID], CarInfo[slot][cTuning][tn]);

		ChangeVehiclePaintjob(CarInfo[slot][cVehID], 5);

    	VehicleInfo[vehicleid][vLock] = 0;
   		DestroyVehicle(vehicleid);
   		CarInfo[slot][cVehID] = INVALID_VEHICLE_ID;
	}
	if(pTemp[playerid][pSpecID] != INVALID_PLAYER_ID)
	{
	    new player = pTemp[playerid][pSpecID];
	    StopPlayerSpectate(player);
	}
	if(PI[playerid][pFamily]) gFamily[PI[playerid][pFamily]-1][fOnline]--;
	if(PI[playerid][pPromo]) gPromo[PI[playerid][pPromo]-1][pcOnline]++;
	PlayerTextDrawDestroy(playerid, Spectate[playerid]);
	DestroyActor(aActorJoin[playerid]);

	if(PI[playerid][pJob] == 1 && temp_bus_id[playerid] != INVALID_VEHICLE_ID)
		SetVehicleToRespawnEx(temp_bus_id[playerid]);

	if(pTemp[playerid][pArendKey] != INVALID_VEHICLE_ID)
	{
		new
			v = pTemp[playerid][pArendKey];
			
		if(ArendInfo[v][aPlayerID] == playerid)
		{
			ArendInfo[v][aPlayerID] = INVALID_PLAYER_ID;
            SetVehicleToRespawnEx(ArendInfo[v][aID]);
		}
    }
    
  	if(GotoInfo[playerid][gtGoID] != INVALID_PLAYER_ID) CheckPlayerGoCuff(playerid);
	if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
	{
		new
		    target = GotoInfo[playerid][gtID];

		temp_cuffer_sender[target] = INVALID_PLAYER_ID;
		temp_cuffer_receiver[playerid] = INVALID_PLAYER_ID;

		f_TogglePlayerControllable(target, true);
		SetPlayerSpecialAction(target, 0);
	    ClearAnims(target);
     	SendClientMessage(target, 0xFF5030AA, !"Сотрудник вышел из игры. Преследование прекращено");
        CheckPlayerGoCuff(target);
        CheckPlayerGoCuff(playerid);
	}
	if(temp_cuffer_receiver[playerid] != INVALID_PLAYER_ID)
	{
		new
		    target = temp_cuffer_receiver[playerid]-1;

		if(IsPlayerConnected(target))
		{
			SetPlayerSpecialAction(target, SPECIAL_ACTION_NONE);
			RemovePlayerAttachedObject(target, 0);

			temp_cuffer_sender[target] = INVALID_PLAYER_ID;
			temp_cuffer_receiver[playerid] = INVALID_PLAYER_ID;

			TogglePlayerControllable(target, 1);
			SendClientMessage(target, 0xFF5030AA, !"Сотрудник вышел из игры. Наручники сняты");
		}
	}
	if(temp_tie_receiver[playerid] != INVALID_PLAYER_ID)
	{
		new
		    target = temp_tie_receiver[playerid]-1;

		if(IsPlayerConnected(target))
		{
			temp_tie_sender[target] = INVALID_PLAYER_ID;
			temp_tie_receiver[playerid] = INVALID_PLAYER_ID;

			f_TogglePlayerControllable(target, true);
			SendClientMessage(target, 0xFF5030AA, !"Веревка снята");
		}
	}
	if(temp_cuffer_sender[playerid] != INVALID_PLAYER_ID)
	{
	    new
			time = PI[playerid][pWanted] * 300 + 1800,
			cufferid = temp_cuffer_sender[playerid]-1;

        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 0);
        temp_cuffer_sender[playerid] = INVALID_PLAYER_ID;
        //temp_cuffer_receiver[cufferid] = INVALID_PLAYER_ID;

	    PI[playerid][pJailTime] = time;
	    PI[playerid][pWanted] = 0;
	    SetPlayerWantedLevel(playerid, 0);
	    ResetPlayerWeapons(playerid);

        PI[playerid][pPrison] = RandomEx(1,3);

        PI[playerid][pJailAdmin] = 0;
			            
	    new
			query[200];

	    format(query, sizeof query, "UPDATE `accounts` SET `JailTime` = '%d', `Prison` = '%d', `Wanted` = '0', `JailAdmin` = '0' WHERE `ID` = '%d'", PI[playerid][pJailTime], PI[playerid][pPrison], PI[playerid][pID]);
	    mysql_tquery(mysql, query);
	    new
	        frmt_exit_cuff[120];

		format(frmt_exit_cuff, sizeof frmt_exit_cuff, "Арестованный {FFFFFF}%s {269BD8}вышел из игры", PN(playerid));
		SendClientMessage(cufferid, 0x269BD8FF, frmt_exit_cuff);

	    format(frmt_exit_cuff, sizeof frmt_exit_cuff, "Игрок %s вышел при аресте и был отправлен в тюрьму", PN(playerid));
	    SendClientMessageToAll(0xFF5030AA, frmt_exit_cuff);

	}
	if(GotoInfo[playerid][gtGoID] != INVALID_PLAYER_ID)
	{
	    new
			time = PI[playerid][pWanted] * 300 + 1800,
			cufferid = GotoInfo[playerid][gtGoID];

		if(!IsACop(cufferid))
			return 1;
			
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 0);
        CheckPlayerGoCuff(cufferid);
        CheckPlayerGoCuff(playerid);

	    PI[playerid][pJailTime] = time;
	    PI[playerid][pWanted] = 0;
	    SetPlayerWantedLevel(playerid, 0);
	    ResetPlayerWeapons(playerid);

        PI[playerid][pPrison] = RandomEx(1,3);
        
        PI[playerid][pJailAdmin] = 0;

	    new
			query[200];

	    format(query, sizeof query, "UPDATE `accounts` SET `JailTime` = '%d', `Prison` = '%d', `Wanted` = '0', `JailAdmin` = '0' WHERE `ID` = '%d'", PI[playerid][pJailTime], PI[playerid][pPrison], PI[playerid][pID]);
	    mysql_tquery(mysql, query);
	    new
	        frmt_exit_cuff[120];

		format(frmt_exit_cuff, sizeof frmt_exit_cuff, "Арестованный {FFFFFF}%s {269BD8}вышел из игры", PN(playerid));
		SendClientMessage(cufferid, 0x269BD8FF, frmt_exit_cuff);

	    format(frmt_exit_cuff, sizeof frmt_exit_cuff, "Игрок %s вышел при аресте и был отправлен в тюрьму", PN(playerid));
	    SendClientMessageToAll(0xFF5030AA, frmt_exit_cuff);

	}

	if(temp_pursuit_sender[playerid] != INVALID_PLAYER_ID)
	{
	    if(!PI[playerid][pJailTime])
	    {
		    new
				time = PI[playerid][pWanted] * 300 + 1800,
				cufferid = temp_pursuit_sender[playerid]-1;

		    PI[playerid][pJailTime] = time;
		    PI[playerid][pWanted] = 0;
		    SetPlayerWantedLevel(playerid, 0);
		    temp_pursuit_sender[playerid] = INVALID_PLAYER_ID;
		    temp_pursuit_receiver[cufferid] = INVALID_PLAYER_ID;
			ResetPlayerWeapons(playerid);

	        PI[playerid][pPrison] = RandomEx(1,3);
	        
	        PI[playerid][pJailAdmin] = 0;

		    new
				query[200];

		    format(query, sizeof query, "UPDATE `accounts` SET `JailTime` = '%d', `Prison` = '%d', `Wanted` = '0', `JailAdmin` = '0' WHERE `ID` = '%d'", PI[playerid][pJailTime], PI[playerid][pPrison], PI[playerid][pID]);
		    mysql_tquery(mysql, query);

		    new
		        frmt_exit_cuff[120];

			format(frmt_exit_cuff, sizeof frmt_exit_cuff, "Погоня прервана ({FFFFFF}%s {269BD8}вышел из игры)", PN(playerid));
			SendClientMessage(cufferid, 0x269BD8FF, frmt_exit_cuff);

		    format(frmt_exit_cuff, sizeof frmt_exit_cuff, "Игрок %s вышел при аресте и был отправлен в тюрьму", PN(playerid));
		    SendClientMessageToAll(0xFF5030AA, frmt_exit_cuff);
	    }
	}

	if(gCalls[playerid][gCaller] == playerid || gCalls[playerid][gCallee] == playerid)
	{
		new
			id;
			
		if(gCalls[playerid][gCaller] == playerid)
			id = gCalls[playerid][gCallee];
			
		else if(gCalls[playerid][gCallee] == playerid)
			id = gCalls[playerid][gCaller];
			
		else
			return SendClientMessage(playerid, COLOR_GREY, !"Ошибка (#112)");
			
		SendClientMessage(id, COLOR_YELLOW, !"Собеседник вышел из игры");
		SetPlayerSpecialAction(id, SPECIAL_ACTION_STOPUSECELLPHONE);
		SetTimerEx("@__ClearPhone",2000,false,"i",id);
		gCalls[playerid][gCaller] = INVALID_PLAYER_ID;
		gCalls[playerid][gCallee] = INVALID_PLAYER_ID;
		gCalls[id][gCaller] = INVALID_PLAYER_ID;
		gCalls[id][gCallee] = INVALID_PLAYER_ID;
		temp_call[playerid] = false;
		temp_call[id] = false;
	}
    for(new i; i < 3; i++)
	{
		if(gNewsDialee[i] == playerid)
		{
			gNewsDialee[i] = INVALID_PLAYER_ID;
			SendClientMessage(gNewsDialer[i], COLOR_YELLOW, "Игрок вышел из игры");
		}
	}

	if(IsPlayerConnected(playerid) && IsPlayerLogged[playerid])
	{
		if(PI[playerid][pID])
		{
			new newstring[24];


			new Year, Month, Day;
			getdate(Year, Month, Day);

			format(newstring, sizeof newstring, "%d-%d-%d", Day, Month, Year);
			SetString(PI[playerid][pLastLogin], newstring);

			new weaponstr[500];
			for(new x; x < 13; x ++)
			{
			    new gun, ammo; GetPlayerWeaponData(playerid, x, gun, ammo);
				format(weaponstr, sizeof(weaponstr), "%s%d %d ",weaponstr, (gun<PI[playerid][pGuns][x])?gun:PI[playerid][pGuns][x], (ammo<PI[playerid][pAmmos][x])?ammo:PI[playerid][pAmmos][x]);
			}

			static const fmt_str[] = "UPDATE `accounts` SET `Money` = '%d', `Exp` = '%d', `Level` = '%d', `Bank` = '%d', `Age` = '%d', `ZKP` = '%d', `Salary` = '%d', `SDPistol_Skill` = '%d', `Eagle_Skill` = '%d', `ShotGun_Skill` = '%d', `MP5_Skill` = '%d', `AK47_Skill` = '%d', `M4_Skill` = '%d', `HP` = '%.2f', `LastLogin` = '%s', `Played` = '%d', `Weapons` = '%s', `Bonus` = '%d', `Disease` = '%d', `MesDisease` = '%d', `Wanted` = '%d', `PointsOrg` = '%d', `MuteTime` = '%d', `PointsLoader` = '%d', `PointsFactory` = '%d', `PointsRoad` = '%d', `AdminTime` = '%d', `TruckSkill` = '%d' WHERE `ID` = '%d'";
			new format_query[sizeof(fmt_str) + 490];
			format(format_query,sizeof(format_query),fmt_str,PI[playerid][pMoney], PI[playerid][pExp], PI[playerid][pLevel], PI[playerid][pBank], PI[playerid][pAge], PI[playerid][pZKP], PI[playerid][pSalary], PI[playerid][pSDPistol_Skill], PI[playerid][pEagle_Skill], PI[playerid][pShotGun_Skill], PI[playerid][pMP5_Skill], PI[playerid][pAK47_Skill], PI[playerid][pM4_Skill], PI[playerid][pHealth], PI[playerid][pLastLogin], PI[playerid][pPlayed], weaponstr, PI[playerid][pBonus], PI[playerid][pDisease], PI[playerid][pMesDisease], PI[playerid][pWanted], PI[playerid][pPointsOrg], PI[playerid][pMuteTime], PI[playerid][pPointsLoader], PI[playerid][pPointsFactory], PI[playerid][pPointsRoad], PI[playerid][pAdminTime], PI[playerid][pTruckSkill],PI[playerid][pID]);
			mysql_function_query(mysql, format_query, false, "", "");
		}
	
		if(PI[playerid][pHouseKey]!=0)SaveHouse(PI[playerid][pHouseKey]);
  		SaveAccessories(playerid);
		new string[128];
		format(string,sizeof(string),"UPDATE `accounts` SET `Online_status` = '1001' WHERE `ID` = %d;",PI[playerid][pID]);
		mysql_tquery(mysql, string);

		pTemp[playerid][pVehicle] = INVALID_VEHICLE_ID;
		strmid(ExitInfo[playerid][ExitName],PN(playerid), 0, strlen(PN(playerid)), 32), ExitInfo[playerid][ExitTime] = GetTickCount();

		DestroyAllTextDraws(playerid);
		DisablePlayerRaceCheckpoint(playerid);
		IsPlayerLogged[playerid] = false;



	}
	new namez[25]; GetPlayerName(playerid, namez, 25);
	// проверка казино,если игроки вышли во время того когда рулетка крутится (НЕ ПЕРЕВОДИТЬ)
	if(temp_table[playerid] != -1)
	{
		new tableid = temp_table[playerid];
	  	for(new i; i < 4; i++)
	  	{
	    	if(gTable[tableid][tPlayers][i] == playerid) gTable[tableid][tPlayers][i] = INVALID_PLAYER_ID;
	  	}

	  	new frmt_player_bet[20 + MAX_PLAYER_NAME];

	  	new check[4];

	  	for(new t; t < 4; t++) check[t] = INVALID_PLAYER_ID;

	  	foreach(new i:Player)
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


	        	if(check[0] == INVALID_PLAYER_ID) PlayerTextDrawSetString(i, casino_table[tableid][8], "-");

	        	if(check[1] == INVALID_PLAYER_ID) PlayerTextDrawSetString(i, casino_table[tableid][9], "-");

	        	if(check[2] == INVALID_PLAYER_ID) PlayerTextDrawSetString(i, casino_table[tableid][10], "-");

	        	if(check[3] == INVALID_PLAYER_ID)PlayerTextDrawSetString(i, casino_table[tableid][11], "-");

	        	format(frmt_player_bet, sizeof frmt_player_bet, "%d$", gTable[tableid][tBet]);
	        	PlayerTextDrawSetString(i, casino_table[tableid][16], frmt_player_bet);

	        	format(frmt_player_bet, sizeof frmt_player_bet, "%d$", gTable[tableid][tBet]*Casino_TotalPlayer(tableid));
	        	PlayerTextDrawSetString(i, casino_table[tableid][17], frmt_player_bet);
	    	}
	  	}
	  	if(gTable[tableid][tStatus] && check[0] == INVALID_PLAYER_ID && check[1] == INVALID_PLAYER_ID && check[2] == INVALID_PLAYER_ID && check[3] == INVALID_PLAYER_ID)
		{
			gTable[tableid][tStep] = 29,gTable[tableid][tBet] = 0,gTable[tableid][tStatus] = false;
			KillTimer(CasinoTimer[tableid]);
		}
	  	format(frmt_player_bet, sizeof frmt_player_bet, "%d/4", Casino_TotalPlayer(tableid));
	  	TextDrawSetString(crupie_table[tableid][6], frmt_player_bet);
	}
	if(PI[playerid][pCarInfoTimer] != 0)
	{
		HideCarInfo(playerid);
		KillTimer(PI[playerid][pCarInfoTimer]);
		PI[playerid][pCarInfoTimer] = 0;
	}
	if(PI[playerid][pJob] == JOB_TRUCKER && pTemp[playerid][pTruckID] != INVALID_VEHICLE_ID)
	{
		SetVehicleToRespawn(pTemp[playerid][pTruckID]);
		if(IsValidDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]))
			DestroyDynamic3DTextLabel(pTemp[playerid][pTruckWagonText]);

		pTemp[playerid][pTruckID] = INVALID_VEHICLE_ID;
		if(pTemp[playerid][pTruckWagonID] != INVALID_VEHICLE_ID)
		{
			DestroyVehicle(pTemp[playerid][pTruckWagonID]);
			pTemp[playerid][pTruckWagonID] = INVALID_VEHICLE_ID;
		}
		for(new i2;i2<4;i2++)
		{
			for(new i;i<10;i++)
			{
				if(gTruckLoadTurn[i2][i] == playerid || gTruckLoadTurn[i2][i] == playerid)
					gTruckLoadTurn[i2][i] = INVALID_PLAYER_ID;
			}
		}
	}
	if(PI[playerid][pJob] == JOB_MECHANIC && pTemp[playerid][pMechID] != INVALID_VEHICLE_ID)
	{
		SetVehicleToRespawn(pTemp[playerid][pMechID]);
		if(IsValidDynamic3DTextLabel(pTemp[playerid][pMechText]))
			DestroyDynamic3DTextLabel(pTemp[playerid][pMechText]);

		pTemp[playerid][pMechID] = INVALID_VEHICLE_ID;
		pTemp[playerid][pMechFuel] = 0;
	}
	// ====== Развозчики
	if(GetPVarInt(playerid, "ProductID") > 0)
	{
 		ProductInfo[GetPVarInt(playerid, "ProductID")][pStatus] = 0;
		DeletePVar(playerid, "ProductLoad");
		DeletePVar(playerid, "ProductInfo");
		SetVehicleToRespawn(GetPVarInt(playerid, "CarProduct"));
		if(GetPVarInt(playerid, "PRODVEH") != 0)
		{
			DestroyVehicleEx(GetPVarInt(playerid, "PRODVEH"));
			SetPVarInt(playerid, "PRODVEH", 0);
		}
		DeletePVar(playerid, "ProductID");
		DisablePlayerRaceCheckpoint(playerid);
		
		if(IsValidDynamic3DTextLabel(JobText3D[playerid]))
			DestroyDynamic3DTextLabel(JobText3D[playerid]);
        DeletePVar(playerid, "CarProduct");
	}
	return true;
}
@__roadput(playerid);
@__roadput(playerid)
{
	if(InJob[playerid] == 5 && temp_job_status[playerid] == 2)
	{

	    RemovePlayerAttachedObject(playerid,0);
	    RemovePlayerAttachedObject(playerid,1);
	    
		if(PI[playerid][pDaysSalary] > 0)
	    	temp_job_amount[playerid] += 240;

		else
		    temp_job_amount[playerid] += 120;
		    
	    new
	        frmt_worked[100];
	        
		if(PI[playerid][pDaysSalary] > 0)
			format(frmt_worked, sizeof frmt_worked, "Вы положили щебень. {42B02C}+$240{FFFFFF} к зарплате. Заработано: {FF9900}$%d", temp_job_amount[playerid]);
			
		else
			format(frmt_worked, sizeof frmt_worked, "Вы положили щебень. {42B02C}+$120{FFFFFF} к зарплате. Заработано: {FF9900}$%d", temp_job_amount[playerid]);

	    SendClientMessage(playerid, COLOR_WHITE, frmt_worked);
		PI[playerid][pPointsRoad] += 3;
		UpdatePlayerData(playerid, "PointsRoad", PI[playerid][pPointsRoad]);
		
		if(PI[playerid][pQuest] == 1 && PI[playerid][pQuestStatus] == 1)
		{
		    PI[playerid][pQuestProcess]++;
		    UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
			if(PI[playerid][pQuestProcess] >= 20)
			{
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		    	SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы перенесли 20 тележек. Отправляйтесь к Саймону");
			}
		}

		for(new i = 0; i < 4; i++)
			TogglePlayerDynamicCP(playerid, gRoadGet[i], false),
			TogglePlayerDynamicCP(playerid, gRoadCP[i], false);

	    RoadGet[playerid] = 0;
		temp_job_status[playerid] = 1;

		new
		    checkpoint = RandomEx(0, 3);

	    TogglePlayerDynamicCP(playerid, gRoadGet[checkpoint], true);
	    RoadGet[playerid] = checkpoint+1;


		f_TogglePlayerControllable(playerid, true);
		temp_job_time[playerid] = 3;
	}
	return 1;
}
@__roadget(playerid);
@__roadget(playerid)
{
	if(InJob[playerid] == 5 && temp_job_status[playerid] == 1)
	{
	    /*if(!IsPlayerInDynamicArea(playerid, gRoadGetArea[RoadGet[playerid]-1]) || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		{
	    	RemovePlayerAttachedObject(playerid,0);
	    	RemovePlayerAttachedObject(playerid,1);

			for(new i = 0; i < 4; i ++)
				TogglePlayerDynamicCP(playerid, gRoadGet[i], false);

		    RoadGet[playerid] = 0;

			new
			    checkpoint = RandomEx(0, 3);

		    TogglePlayerDynamicCP(playerid, gRoadGet[checkpoint], true);
		    RoadGet[playerid] = checkpoint+1;

			f_TogglePlayerControllable(playerid, true);
	    	temp_job_status[playerid] = 1;
		    return SendClientMessage(playerid, -1, "Вы потеряли весь щебень по дороге (НЕ ПЕРЕВОДИТЬ)");
		}*/


		//job_road[playerid] = CreateDynamicRectangle(718.6, -1678.6, 744.1, -1669.1, -1, -1, playerid);

		DeletePVar(playerid,"UseAnim");
		new
		    checkpoint = RandomEx(0, 3);
			    
		TogglePlayerDynamicCP(playerid, gRoadCP[checkpoint], true);
        RoadCP[playerid] = checkpoint+1;
		
		temp_job_status[playerid] = 2;
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отвезите щебень на место стройки");
		SetPlayerAttachedObject(playerid, 1, 2060, 1, -0.59, 1.616571, -0.065124, 76.480148, 102.781570, 190.952545, 1.1, 0.5, 1.0);
		temp_job_time[playerid] = 2;
		for(new i = 0; i < 4; i ++)
			TogglePlayerDynamicCP(playerid, gRoadGet[i], false);
	}
	return 1;
}
@__AutoReady(playerid);
@__AutoReady(playerid)
{
	new
		objectid = temp_auto_object[playerid],
		table = temp_auto_table[playerid]-1;

	temp_auto_object[playerid] = 0;
	DestroyDynamicObject(objectid);
	//temp_auto_model[playerid] = 0;

	temp_auto_table[playerid] = 0;
	AutoTableStat[table] = false;

	RemovePlayerAttachedObject(playerid, 0);
	RemovePlayerAttachedObject(playerid, 1);

	if(!IsPlayerInDynamicArea(playerid, AutoWork[table]))
	{
		GameTextForPlayer(playerid, "~r~FAIL", 1000, 1);
		temp_auto_amount[playerid] = 1;
		return SendClientMessage(playerid, COLOR_GREY, !"Вы потеряли детали по дороге");
	}
	

    new
		randombreak = RandomEx(0, 50);
		
	if(randombreak > 47)
	{
		SendClientMessage(playerid, COLOR_GREY, !"Вы сделали бракованную запчасть");
		GameTextForPlayer(playerid, "~r~FAIL", 1000, 1);
		temp_auto_amount[playerid] = 1;
		return 1;
	}

	temp_auto_amount[playerid] = 3;

	ClearAnimations(playerid);
    SetPlayerAttachedObject(playerid, 0, 2969, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0);
    
	temp_auto_model[playerid] = 0;

	SendClientMessage(playerid, COLOR_WHITE, !"Вы собрали запчасть. Отнесите ее на склад");
	ApplyAnimation(playerid, !"CARRY", !"crry_prtial", 4.0, 1, 1, 1, 1, 1, 1);
	SetPlayerCheckpoint(playerid, 2564.0759, -1292.8741, 1044.1250, 2.0);
	return 1;
}
@__OperationReady(playerid, sender);
@__OperationReady(playerid, sender)
{
	new
	    frmt_action[128];
	    
	format(frmt_action, sizeof frmt_action, "{7AC71F}[Успешно] {FFC800}%s{FFFFFF} провел(а) вам курс лечения", PN(sender));
    SendClientMessage(playerid, COLOR_WHITE, frmt_action);
	format(frmt_action, sizeof frmt_action, "%s сделал(а) операцию %s", PN(sender), PN(playerid));
    ProxDetector(25, sender, frmt_action, COLOR_ME);

	Delete3DTextLabel(temp_disease_text[playerid]);
	PI[playerid][pDisease] = 0;
	GiveMoney(sender, 1500, "операция");
	UpdatePlayerData(playerid, "Disease", PI[playerid][pDisease]);
	TogglePlayerControllable(playerid,true);
	ClearAnimations(sender);
	ClearAnimations(playerid);
	return 1;
}
public OnPlayerEnterDynamicArea(playerid, areaid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 1;
	if((areaid == arTruckLoadOne || areaid == arTruckLoadTwo || areaid == arTruckLoadThree) && PI[playerid][pJob] == JOB_TRUCKER && pTemp[playerid][pTruckID] != INVALID_VEHICLE_ID)
	{
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы начать загрузку - {63BD4E}Посигнальте");
	}
 	if(areaid == Ships[playerid] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new panels, tires, doors, lights;
        new vehicleid = GetPlayerVehicleID(playerid);
        GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
        tires = 15;
        UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
    }
    if(areaid == gHealExit)
	{
 		if(PI[playerid][pHealth] < 80.0)
		 	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете выйти из больницы, пока не вылечитесь");
		 	
		new world = GetPlayerVirtualWorld(playerid);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		switch(world)
		{
			case 1:
			{
			    pTemp[playerid][pAntiAir] += 7;
				J_SetPlayerFacingAngle(playerid, 335.2464);
				SetPlayerPos(playerid, 1176.8413,-1324.0846,14.0412);
			}
			case 2:
			{
			    pTemp[playerid][pAntiAir] += 7;
				J_SetPlayerFacingAngle(playerid, 2.3200);
				SetPlayerPos(playerid, 1607.4996,1818.8636,10.8203);
			}
			default:
			{
			    pTemp[playerid][pAntiAir] += 7;
				J_SetPlayerFacingAngle(playerid, 180.0);
				SetPlayerPos(playerid, -2668.9080,636.9764,14.4531);
			}
		}
		//NoEnterPickup[playerid] =2;
 		//f_TogglePlayerControllable(playerid,false);
		return true;
 	}
	    
	else if(areaid == gPDDInfo)
	{

	    new
			frmt_info[2300];
		strcat(frmt_info,"{FFFFFF}Общие положения:\n");
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
        ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Правила дорожного движения", frmt_info, !"Закрыть", !"");

	}

	else if(areaid >= gJobInvite[0] && areaid <= gJobInvite[2])
	{
		ShowPlayerDialogEx(playerid, 346, DIALOG_STYLE_TABLIST_HEADERS, !"Устройство на работу", !"{FFFFFF}Наименование\t{FFFFFF}Требования\n{FF7319}1.{FFFFFF} Водитель автобуса\t2 уровень\n{FF7319}2.{FFFFFF} Таксист\t3 уровень\n{FF7319}3.{FFFFFF} Механик\t3 уровень\n{FF7319}4.{FFFFFF} Развозчик заказов\t3 уровень\n{FF7319}5.{FFFFFF} Дальнобойщик\t4 уровень", !"OK", !"Отмена");
	}
	else if(areaid == gGangStockArea)
	{
	    if(PI[playerid][pFraction]-2 == GetPlayerVirtualWorld(playerid)-1)
			ShowPlayerDialogEx(playerid, 612, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");
	}
	else if(areaid == gMafiaStockArea)
	{
	    if(PI[playerid][pFraction]-12 == GetPlayerVirtualWorld(playerid)-1)
	    {
			new
				gunamount = GetPVarInt(playerid,"carrygun"),
				ammo = GetPVarInt(playerid,"carryammo");

			if(gunamount || ammo)
			{
				SetPVarInt(playerid, "carrygun", 0);
				SetPVarInt(playerid, "carryammo", 0);
				RemovePlayerAttachedObject(playerid, 3);
				ApplyAnimation(playerid, !"CARRY", !"putdwn", 1.0, 0, 1, 1, 0, 0, 1);

				new
				    mafiaid = PI[playerid][pFraction] - 12;


				gMafiaStorage[mafiaid][0] += gunamount;
				gMafiaStorage[mafiaid][1] += ammo;
				UpdateTextMafia();
			}
			ShowPlayerDialogEx(playerid, 654, DIALOG_STYLE_LIST, !"Общак", !"Единицы оружия\nПатроны\nДеньги\nНаркотики", !"Далее", !"Отмена");
		}
	}
	else if(areaid == gMafiaDrugs)
	{
		if(!IsAMafia(playerid))
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Доступно только мафиям");

		if(InJob[playerid] > 0 && InJob[playerid] != 9)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже где-то работаете");
		    
		if(InJob[playerid] != 9)
			ShowPlayerDialogEx(playerid, 699, DIALOG_STYLE_INPUT, !"Ферма", !"{FFFFFF}Аренда поля для сбора наркотиков: {33AA00}1000${FFFFFF}/Минута\n\nВведите время аренды:\n\n{AFAFAF}Значение должно быть от 5 до 20 минут", !"Аренда", !"Отмена");

		else
			ShowPlayerDialogEx(playerid, 700, DIALOG_STYLE_MSGBOX, !"Ферма", !"{FFFFFF}Вы действительно хотите завершить аренду поля?", !"Да", !"Отмена");
	}
	else if(areaid >= gBarrier_Area[0] && areaid <= gBarrier_Area[51])
	{
		if(GetBarrierID(playerid) != -1)
		{
		    if((GetBarrierID(playerid) >= 0 && GetBarrierID(playerid) <= 11) && GetPVarInt(playerid, "doortext") == 0)
		    {
				if(PI[playerid][pFraction] != 1)
				    return 1;

				switch(GetPlayerVirtualWorld(playerid))
				{
				    case 1: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
				    case 2: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
				    case 3: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
				}

 	 			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Нажмите клавишу {FFE805}быстрого бега{FFFFFF}, чтобы открыть/закрыть дверь");
                SetPVarInt(playerid, "doortext", true);
			}
		    if((GetBarrierID(playerid) >= 12 && GetBarrierID(playerid) <= 23) && GetPVarInt(playerid, "doortext") == 0)
		    {
				if(PI[playerid][pFraction] != 8)
				    return 1;

				switch(GetPlayerVirtualWorld(playerid))
				{
				    case 2: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
				    case 0: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
				    case 12: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
				}

 	 			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Нажмите клавишу {FFE805}быстрого бега{FFFFFF}, чтобы открыть/закрыть дверь");
                SetPVarInt(playerid, "doortext", true);
			}
		    if((GetBarrierID(playerid) >= 24 && GetBarrierID(playerid) <= 35) && GetPVarInt(playerid, "doortext") == 0)
		    {
				if(PI[playerid][pFraction] != 9)
				    return 1;

				switch(GetPlayerVirtualWorld(playerid))
				{
				    case 1: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
				    case 2: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
				    case 3: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
				}

 	 			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Нажмите клавишу {FFE805}быстрого бега{FFFFFF}, чтобы открыть/закрыть дверь");
                SetPVarInt(playerid, "doortext", true);
			}
		    if((GetBarrierID(playerid) >= 36 && GetBarrierID(playerid) <= 39) && GetPVarInt(playerid, "doortext") == 0)
		    {
				if(PI[playerid][pFraction] != 11)
				    return 1;

 	 			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Нажмите клавишу {FFE805}быстрого бега{FFFFFF}, чтобы открыть/закрыть дверь");
                SetPVarInt(playerid, "doortext", true);
			}
		}
	}
	else if(areaid >= gFermGrassArea[0] && areaid <= gFermGrassArea[5])
	{
		if(!IsAMafia(playerid))
		    return 1;

		if(InJob[playerid] != 9)
		    return 1;

        new grassid = gFermGrassArea[0] - areaid;
        
		if(pTemp[playerid][pGrass] == grassid+1)
		    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы недавно собирали урожай с этого куста, подойдите к другому");
		
		if(!PI[playerid][pBag])
		{
			if(PI[playerid][pDrugs]+20 > 500)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете унести больше наркотиков");
		}
		else
		{
			if(PI[playerid][pDrugs]+20 > 1000)
			    return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете унести больше наркотиков");
		
		}
		
		PI[playerid][pDrugs] += 20;
		UpdatePlayerData(playerid, "Drugs", PI[playerid][pDrugs]);
		GameTextForPlayer(playerid, "~b~+20 gramm", 3000, 1);
		ApplyAnimation(playerid, !"CARRY", !"putdwn", 4.0, 0, 0, 0, 0, 0, 1);
		pTemp[playerid][pGrass] = grassid+1;
	}
	else if(areaid >= gArmyStockArea[0] && areaid <= gArmyStockArea[1])
	{
		new armyid = GetPlayerVirtualWorld(playerid)-1;
		if(PI[playerid][pFraction] == 7)
		{
			new
				gunamount = GetPVarInt(playerid,"carrygun"),
				ammo = GetPVarInt(playerid,"carryammo");
				
			if(gunamount || ammo)
			{
				SetPVarInt(playerid, "carrygun", 0);
				SetPVarInt(playerid, "carryammo", 0);
				RemovePlayerAttachedObject(playerid, 3);
				ApplyAnimation(playerid, !"CARRY", !"putdwn", 1.0, 0, 1, 1, 0, 0, 1);
				if(GetPlayerVirtualWorld(playerid) == 1 || GetPlayerVirtualWorld(playerid) == 2)
				{
				    WHDataUpdate();
				    
				    if(gArmyWarehouse[armyid][0] + gunamount <= 50000)
						gArmyWarehouse[armyid][0] += gunamount;
						
					else
					    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под боеприпасы");
						
					if(gArmyWarehouse[armyid][1] + ammo <= 120000)
						gArmyWarehouse[armyid][1] += ammo;
						
					else
						SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под патроны");
						
				}
			}
			if(!GetPVarInt(playerid,"carrygun") && temp_army_loadfr[playerid] == 7)
			{
				ClearAnimations(playerid);
				if(GetPlayerVirtualWorld(playerid) == 1 || GetPlayerVirtualWorld(playerid) == 2)
				{
				    if(gArmyWarehouse[armyid][0] - 300 < 0 || gArmyWarehouse[armyid][1] - 300 < 0)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов или боеприпасов");

					gArmyWarehouse[armyid][0] -= 300;
					gArmyWarehouse[armyid][1] -= 300;
					WHDataUpdate();
				}
				
				ApplyAnimation(playerid, !"CARRY", !"liftup", 1.0, 0, 1, 1, 0, 0, 1);
				SetTimerEx("@__CarryDelay",1000, false, "i", playerid);
				SetPlayerAttachedObject(playerid, 3, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0);

				SetPVarInt(playerid, "carrygun", 300);
				SetPVarInt(playerid, "carryammo", 300);
			}
		}
		else if(IsAMafia(playerid) && pTemp[playerid][pWarehouseRob])
		{
		    if(GetPVarInt(playerid, "carrygun"))
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть ящик с оружием");

			if(!GetPVarInt(playerid, "carrygun"))
			{
				if(GetPlayerVirtualWorld(playerid) == 1 || GetPlayerVirtualWorld(playerid) == 2)
				{
				    if(gArmyWarehouse[armyid][0] - 300 < 0 || gArmyWarehouse[armyid][1] - 300 < 0)
						return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно патронов или боеприпасов");

					gArmyWarehouse[armyid][0] -= 300;
					gArmyWarehouse[armyid][1] -= 300;
					WHDataUpdate();
				}
				ClearAnimations(playerid);
				ApplyAnimation(playerid, !"CARRY", !"liftup", 1.0, 0, 1, 1, 0, 0, 1);
				SetTimerEx("@__CarryDelay",1000, false, "i", playerid);
				SetPlayerAttachedObject(playerid, 3, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0);
				SetPVarInt(playerid, "carrygun", 300);
				SetPVarInt(playerid, "carryammo", 300);
			}
		}
	}
	
	else if(areaid >= gPDStockArea[0] && areaid <= gPDStockArea[2])
	{
		new
		    pdid = -1;

		switch(GetPlayerVirtualWorld(playerid))
		{
		    case 3: pdid = 0;
		    case 4: pdid = 1;
		    case 5: pdid = 2;
		}

		if(pdid == -1)
		    return 1;
		    
		if(PI[playerid][pFraction] == 7 && temp_army_loadfr[playerid] == 8 && temp_army_loadsf[playerid] == pdid+1)
		{
			new
				gunamount = GetPVarInt(playerid,"carrygun"),
				ammo = GetPVarInt(playerid,"carryammo");

			if(gunamount || ammo)
			{
				SetPVarInt(playerid, "carrygun", 0);
				SetPVarInt(playerid, "carryammo", 0);
				RemovePlayerAttachedObject(playerid, 3);
				ApplyAnimation(playerid, !"CARRY", !"putdwn", 1.0, 0, 1, 1, 0, 0, 1);
				if(GetPlayerVirtualWorld(playerid) == 3 || GetPlayerVirtualWorld(playerid) == 4 || GetPlayerVirtualWorld(playerid) == 5)
				{
				    WHDataUpdate();

				    if(gPDWarehouse[pdid][0] + gunamount <= 50000)
						gPDWarehouse[pdid][0] += gunamount;

					else
					    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под боеприпасы");

					if(gPDWarehouse[pdid][1] + ammo <= 50000)
						gPDWarehouse[pdid][1] += ammo;

					else
						SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под патроны");

				}
			}
		}
	}
	else if(areaid == gFBIStockArea)
	{
		if(PI[playerid][pFraction] == 7 && temp_army_loadfr[playerid] == 11 && temp_army_loadsf[playerid] == 0)
		{
			new
				gunamount = GetPVarInt(playerid,"carrygun"),
				ammo = GetPVarInt(playerid,"carryammo");

			if(gunamount || ammo)
			{
				SetPVarInt(playerid, "carrygun", 0);
				SetPVarInt(playerid, "carryammo", 0);
				RemovePlayerAttachedObject(playerid, 3);
				ApplyAnimation(playerid, !"CARRY", !"putdwn", 1.0, 0, 1, 1, 0, 0, 1);
				if(GetPlayerVirtualWorld(playerid) == 10)
				{
                    WHDataUpdate();
						
				    if(gFBIWarehouse[0] + gunamount <= 50000)
						gFBIWarehouse[0] += gunamount;

					else
					    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под боеприпасы");

					if(gFBIWarehouse[1] + ammo <= 50000)
						gFBIWarehouse[1] += ammo;

					else
						SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под патроны");

				}
			}
		}
	}
	else if(areaid >= gArmyArmour[0] && areaid <= gArmyArmour[1])
	{
		new armyid = -1;
		switch(GetPlayerVirtualWorld(playerid))
		{
		    case 1: armyid = 2;
		    case 2: armyid = 1;
		}
		if(armyid == -1) return 1;
		    
		if((PI[playerid][pFraction] == 7 && PI[playerid][pSubfraction] == armyid) || (PI[playerid][pFraction] == 7 && PI[playerid][pRank] == 11)) SetArmour(playerid, 100);
		return true;
	}
	else if(areaid >= gArmyEat[0] && areaid <= gArmyEat[1])
	{
		new
		    armyid = -1;

		switch(GetPlayerVirtualWorld(playerid))
		{
		    case 1: armyid = 2;
		    case 2: armyid = 1;
		}

		if(armyid == -1)
		    return 1;

		if((PI[playerid][pFraction] == 7 && PI[playerid][pSubfraction] == armyid) || (PI[playerid][pFraction] == 7 && PI[playerid][pRank] == 11))
		{
            if(PI[playerid][pHealth] < 100)
            {
				temp_eat[playerid] = 1;
				SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Введите {32CD32}/eat{FFFFFF}, чтобы употребить купленное");
				SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы выбросить продукт, введите {32CD32}/put");
				SetPlayerSpecialAction(playerid, 25), SetPlayerAttachedObject(playerid,0,2215,3,0.232999,-0.376998,-0.408999,54.199886,-35.700153,-35.000019,1.000000,1.000000,1.000000);
			}
		    else
		        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не голодны");
		}

	}
	else if(areaid >= gHallStockArea[0] && areaid <= gHallStockArea[3])
	{
		new
		    hallid = -1,
			area = -1;

		switch(GetPlayerVirtualWorld(playerid))
		{
		    case 6: hallid = 1, area = 0;
		    case 7: hallid = 2, area = 1;
		    case 8: hallid = 3, area = 2;
		    case 9: hallid = 0, area = 3;
		}

		if(hallid == -1)
		    return 1;
			    
		if(PI[playerid][pFraction] == 7 && temp_army_loadfr[playerid] == 10 && temp_army_loadsf[playerid] == hallid)
		{
			new
				gunamount = GetPVarInt(playerid,"carrygun"),
				ammo = GetPVarInt(playerid,"carryammo");

			if(gunamount || ammo)
			{
				SetPVarInt(playerid, "carrygun", 0);
				SetPVarInt(playerid, "carryammo", 0);
				RemovePlayerAttachedObject(playerid, 3);
				ApplyAnimation(playerid, !"CARRY", !"putdwn", 1.0, 0, 1, 1, 0, 0, 1);
				WHDataUpdate();
					
			    if(gHallWarehouse[area][0] + gunamount <= 50000)
					gHallWarehouse[area][0] += gunamount;

				else
				    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под боеприпасы");

				if(gHallWarehouse[area][1] + ammo <= 50000)
					gHallWarehouse[area][1] += ammo;

				else
					SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}На складе недостаточно места под патроны");


			}
		}
	}
	
	else if(areaid >= gHallCard[0] && areaid <= gHallCard[2])
	{
 		ShowPlayerDialogEx(playerid, 571, DIALOG_STYLE_LIST, !"Покупка лицензий", !"{FF7319}1.{FFFFFF} Купить лицензию на оружие\n{FF7319}2.{FFFFFF} Купить билет рекордсмена", !"Далее", !"Закрыть");
	}
	else if(areaid >= gHallFamily[0] && areaid <= gHallFamily[2])
	{
	    ShowPlayerDialogEx(playerid, 580, DIALOG_STYLE_LIST, !"Семьи", !"{FF7319}1.{FFFFFF} Информация о семье\n{FF7319}2.{FFFFFF} Создание семьи\n{FF7319}3.{FFFFFF} Список семей", !"Далее", !"Закрыть");
	}
	else if(areaid >= gHallInfo[0] && areaid <= gHallInfo[2])
	{
	    new
	        frmt_hall_info[500];
	        
		format(frmt_hall_info, sizeof frmt_hall_info, "Казна: {33AA33}%d${FFFFFF}\nНалог на бизнес: {A52A2A}%d%%{FFFFFF}\nНалог на зарплату гос.организаций: {A52A2A}%d%%{FFFFFF}\nПенсионный возраст: {A52A2A}%d{FFFFFF} лет в штате\nРазмер Пенсии: {33AA33}%d$", OrgInfo[9][oMoney], gBusinessNalog, gSalaryNalog, gPensionAge, gPension);
	    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_LIST, !"Информация о штате {0066FF}Virtual.", frmt_hall_info, !"Закрыть", !"");
	}
	else if(areaid >= gHallCharity[0] && areaid <= gHallCharity[2])
	{
 		ShowPlayerDialogEx(playerid, 577, DIALOG_STYLE_LIST, !"Пожертвование", !"{FF7319}1.{FFFFFF} Пожертвовать средства\n{FF7319}2.{FFFFFF} Список крупнейших благотворителей", !"Далее", !"Закрыть");
	}
	else if(areaid >= gHallEstate[0] && areaid <= gHallEstate[2])
	{
	    new
	        frmt_estate_info[400];
	        
		format(frmt_estate_info, sizeof frmt_estate_info, "{FFFFFF}Дома: {33AA33}%d{FFFFFF} (Освобождается: {FF0000}%d{FFFFFF})\n{FFFFFF}Бизнесы: {33AA33}%d{FFFFFF} (Освобождается: {FF0000}%d{FFFFFF})\n{FFFFFF}АЗС: {33AA33}%d{FFFFFF} (Освобождается: {FF0000}%d{FFFFFF})", gHouseFree, gHouseSeal, gBusinessFree, gBusinessSeal, gFillingFree, gFillingSeal);
	    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Свободное имущество", frmt_estate_info, !"Закрыть", !"");
	}
	else if(areaid >= gPDGunArea[0] && areaid <= gPDGunArea[2])
	{
		if(PI[playerid][pFraction] == 8)
		{
			new pdid = -1;
			switch(GetPlayerVirtualWorld(playerid))
			{
			    case 3: pdid = 1;
			    case 4: pdid = 2;
			    case 5: pdid = 3;
			}
			if(pdid == -1) return 1;
			if(PI[playerid][pSubfraction] != pdid) return 1;
			if(PI[playerid][pGunLic] != YES_LICENSE) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет лицензии на оружие");
			ShowPlayerDialogEx(playerid, 437, DIALOG_STYLE_LIST, !"Выберите оружие", !"Silenced Pistol\nDesert Eagle\nMP5\nShotgun\nM4\nДубинка\nБронежилет", !"Выбор", !"Отмена");
		}
		return 1;
	}
	else if(areaid == gFBIGunArea)
	{
		if(PI[playerid][pFraction] != 11)
			return 1;

		if(PI[playerid][pGunLic] != YES_LICENSE)
	        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет лицензии на оружие");
		        
		ShowPlayerDialogEx(playerid, 436, DIALOG_STYLE_LIST, !"Выберите оружие", !"Silenced Pistol\nDesert Eagle\nMP5\nShotgun\nM4\nДубинка\nБронежилет", !"Выбор", !"Отмена");
		return 1;
	}
	else if(areaid >= gMafiaGunArea[0] && areaid <= gMafiaGunArea[2])
	{
		new mafiaid = -1;
		for(new i; i < 3; i++)
		{
			if(gMafiaGunArea[i] == areaid)
			{
				mafiaid = i;
				break;
			}
		}
		if(mafiaid == -1)
			return 1;

		if(PI[playerid][pFraction] - 12 != mafiaid)
			return 1;

		if(PI[playerid][pGunLic] != YES_LICENSE)
	        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет лицензии на оружие");
	        
		ShowPlayerDialogEx(playerid, 446, DIALOG_STYLE_LIST, !"Выберите оружие", !"Desert Eagle\nMP5\nShotgun\nM4\nCountry Rifle", !"Выбор", !"Отмена");

	}
	else if(areaid >= gHallGunArea[0] && areaid <= gHallGunArea[3])
	{
		if(PI[playerid][pFraction] == 10)
		{
			new
			    subid = -1;

			switch(GetPlayerVirtualWorld(playerid))
			{
			    case 6: subid = 1;
			    case 7: subid = 2;
			    case 8: subid = 3;
			    case 9: subid = 0;
			}
			    
			if(PI[playerid][pSubfraction] != subid)
			    return 1;

			if(PI[playerid][pGunLic] != YES_LICENSE)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет лицензии на оружие");
		        
			ShowPlayerDialogEx(playerid, 438, DIALOG_STYLE_LIST, !"Выберите оружие", !"Desert Eagle\nShotgun\nДубинка\nБронежилет", !"Выбор", !"Отмена");
		}
	}
	else if(areaid == gHallMoneyArea)
	{
		if(PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != 0 || PI[playerid][pRank] < 11)
		    return 1;

		ShowPlayerDialogEx(playerid, 479, DIALOG_STYLE_LIST, !"Казна штата", !"{FF7319}1.{FFFFFF} Выделение денег организациям\n{FF7319}2.{FFFFFF} Пенсионный фонд\n{FF7319}3.{FFFFFF} Выдача премий\n{FF7319}4.{FFFFFF} Изменение налогообложения", !"Далее", !"Отмена");
	}
	else if(areaid >= gGangEnter[0] && areaid <= gGangEnter[4])
	{
		if(IsPlayerInAnyVehicle(playerid))
			return 1;
			
		new gangid = -1;
		for(new i; i < 5; i++)
		{
			if(gGangEnter[i] == areaid)
			{
				gangid = i;
				break;
			}
		}
		if(gangid == -1)
			return 1;

		if(PI[playerid][pFraction] - 2 != gangid && !PI[playerid][pGangKey])
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет ключа от дома банды");

		SetPlayerInterior(playerid, 12);
		SetPlayerVirtualWorld(playerid, gangid+1);
		SetPlayerPos(playerid, 2694.2107,-739.1675,1181.0209);
		J_SetPlayerFacingAngle(playerid, 90.0);
		TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
	}
	else if(areaid == gGangExit)
	{
		if(IsPlayerInAnyVehicle(playerid))
			return 1;
			
		new gangid = GetPlayerVirtualWorld(playerid)-1;
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, gGangInt[gangid][0], gGangInt[gangid][1], gGangInt[gangid][2]);
		J_SetPlayerFacingAngle(playerid, gGangInt[gangid][3]);
		TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
	}
	else if(areaid == gCasinoEnter)
	{
		if(IsPlayerInAnyVehicle(playerid))
			return 1;
			
		if(PI[playerid][pLevel] < 3)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны прожить 3 года в штате чтобы попасть в это заведение");

		SetPlayerInterior(playerid, 10);
		SetPlayerVirtualWorld(playerid, 1);
		SetPlayerPos(playerid, 2016.7852, 1017.8334, 996.8750);
		J_SetPlayerFacingAngle(playerid, 90.7619);
		TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
	}
	else if(areaid == gCasinoExit)
	{
		if(IsPlayerInAnyVehicle(playerid))
			return 1;
			
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, 2024.4956, 1007.7509, 10.8203);
		J_SetPlayerFacingAngle(playerid, 270.385);
		TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
		
		if(InJob[playerid] == 8)
		{
		    if(temp_table[playerid] != -1)
		    {
		        new table = temp_table[playerid];

                gTable[table][tCrup] = INVALID_PLAYER_ID;
                temp_table[playerid] = -1;

			}
			
			SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);

	        TotalCrupie--;
	        InJob[playerid] = 0;

			SendClientMessage(playerid, COLOR_WHITE,"{7AC71F}[Успешно] {FFFFFF}Вы закончили работу крупье");
		}
	}
	else if(areaid == gCasinoCrupie)
	{
	        
		if(InJob[playerid] != 8)
		{
		    if(PI[playerid][pLevel] < 5)
		        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны прожить 5 лет в штате чтобы устроиться на работу крупье");

	    	ShowPlayerDialogEx(playerid, 439, DIALOG_STYLE_MSGBOX, !"Казино", !"{FFFFFF}Вы действительно хотите устроиться на работу крупье?", !"Да", !"Отмена");
		}
		
		else
		    ShowPlayerDialogEx(playerid, 442, DIALOG_STYLE_MSGBOX, !"Казино", !"{FFFFFF}Вы хотите уволиться с работы крупье?", !"Да", !"Отмена");

	}

	else if(areaid >= gHospitalElevator[0][0] && areaid <= gHospitalElevator[2][0])
	{
		if(PI[playerid][pFraction] == 1)
		{

			new world = GetPlayerVirtualWorld(playerid);
			switch(world)
			{
				case 1:
				{
			        if(PI[playerid][pSubfraction] == 1 || PI[playerid][pRank] == 11)
			        {
        				SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
	   		 			SetPlayerPos(playerid, 1161.5959, -1328.7960, 31.4970);
	   		 			J_SetPlayerFacingAngle(playerid, 1.0000);
			        }
		        }
		        case 2:
		        {
			        if(PI[playerid][pSubfraction] == 3 || PI[playerid][pRank] == 11)
			        {
        				SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
	   		 			SetPlayerPos(playerid, 1597.9515, 1804.7810, 30.4688);
	                    J_SetPlayerFacingAngle(playerid, 270.0000);
			        }
		        }
		        case 3:
				{
			        if(PI[playerid][pSubfraction] == 2 || PI[playerid][pRank] == 11)
			        {
        				SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
	   		 			SetPlayerPos(playerid, -2679.4358, 591.2363, 66.0938);
	                    J_SetPlayerFacingAngle(playerid, 270.0000);
			        }
				}
			}
			pTemp[playerid][pAntiAir] += 4;
		}
	}
	else if(areaid == gHospitalElevator[0][1])
	{
		if(PI[playerid][pFraction] == 1)
		{
			if(1 == PI[playerid][pSubfraction] || PI[playerid][pRank] == 11)
			{
				SetPlayerInterior(playerid, 3);
				SetPlayerVirtualWorld(playerid, 1);
	            SetPlayerPos(playerid, 703.8452, 1519.8060, 1306.1029);
				J_SetPlayerFacingAngle(playerid, 87.2506);
				pTemp[playerid][pAntiAir] += 4;
			}
		}
	}
	else if(areaid == gHospitalElevator[1][1])
	{
		if(PI[playerid][pFraction] == 1)
		{
			if(3 == PI[playerid][pSubfraction] || PI[playerid][pRank] == 11)
			{
				SetPlayerInterior(playerid, 3);
				SetPlayerVirtualWorld(playerid, 2);
	            SetPlayerPos(playerid, 703.8452, 1519.8060, 1306.1029);
				J_SetPlayerFacingAngle(playerid, 87.2506);
				pTemp[playerid][pAntiAir] += 4;
			}
		}
	}
	else if(areaid == gHospitalElevator[2][1])
	{
		if(PI[playerid][pFraction] == 1)
		{
			if(2 == PI[playerid][pSubfraction] || PI[playerid][pRank] == 11)
			{
				SetPlayerInterior(playerid, 3);
				SetPlayerVirtualWorld(playerid, 3);
	            SetPlayerPos(playerid, 703.8452, 1519.8060, 1306.1029);
				J_SetPlayerFacingAngle(playerid, 87.2506);
				pTemp[playerid][pAntiAir] += 4;
			}
		}
	}
	else if(areaid == gFBIElevator[0])
	{
	    if(PI[playerid][pFraction] != 11)
	        return 1;

		ShowPlayerDialogEx(playerid, 635, DIALOG_STYLE_LIST, !"Лифт", !"Второй этаж\nКрыша", !"Выбор", !"Отмена");
	        

	}
	else if(areaid == gFBIElevator[1])
	{
	    if(PI[playerid][pFraction] != 11)
	        return 1;

	    ShowPlayerDialogEx(playerid, 636, DIALOG_STYLE_LIST, !"Лифт", !"Первый этаж\nКрыша", !"Выбор", !"Отмена");


	}
	else if(areaid == gFBIElevator[2])
	{
	    if(PI[playerid][pFraction] != 11)
	        return 1;
        
	    ShowPlayerDialogEx(playerid, 637, DIALOG_STYLE_LIST, !"Лифт", !"Первый этаж\nВторой этаж", !"Выбор", !"Отмена");
	}
	else if(areaid >= gDiseaseArea[0] && areaid <= gDiseaseArea[2])
	{
	    if(temp_inject_need[playerid] == true || temp_operation_need[playerid] == true) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже проходите курс лечения");
	    if(!PI[playerid][pDisease]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не больны!");
	        
	    new frmt_disease[154];
	        
		if(PI[playerid][pDisease] == 1 || PI[playerid][pDisease] == 2) format(frmt_disease, sizeof frmt_disease, "{FFFFFF}Вы больны болезнью {FF0000}%s{FFFFFF}.\nСтоимость лечения {00AB0C}%d$\n{FFFFFF}Для лечения вам необходимо пройти курс из 5 уколов", gDiseaseName[PI[playerid][pDisease]-1], gDiseasePrice[PI[playerid][pDisease]-1]);
		else if(PI[playerid][pDisease] == 3 || PI[playerid][pDisease] == 4 || PI[playerid][pDisease] == 5 || PI[playerid][pDisease] == 6) format(frmt_disease, sizeof frmt_disease, "{FFFFFF}Вы больны болезнью {FF0000}%s{FFFFFF}.\nСтоимость лечения {00AB0C}%d$\n{FFFFFF}Для лечения вам необходимо пройти операцию", gDiseaseName[PI[playerid][pDisease]-1], gDiseasePrice[PI[playerid][pDisease]-1]);
		ShowPlayerDialogEx(playerid, 189, DIALOG_STYLE_MSGBOX, !"Лечение", frmt_disease, !"Оплатить", !"Отмена");

	}
	else if(areaid == OperTable)
	{
	    if(PI[playerid][pFraction] == 1 && PI[playerid][pRank] >= 4 || PI[playerid][pSubfraction] == GetPlayerVirtualWorld(playerid))
	    {
			new str[300], total = 0;
			foreach( new i: Player)
	        {
			    if(IsPlayerLogged[i] == true && IsPlayerConnected(i) && i != playerid)
				{
		            if(IsPlayerInRangeOfPoint(i, 10, 700.1089,1515.0142,1309.7780) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid) && i != playerid && temp_operation_need[i] == true || temp_inject_need[i] == true)
					{
						format(str, sizeof str, "%s%s\n", str, PN(i));
						total++;
					}
	            }
	        }
	        if(total != 0) ShowPlayerDialogEx(playerid, 190, DIALOG_STYLE_LIST, !"Операционный стол", str, !"Выбор", !"Отмена");
			else SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В палате нет больных пациентов");
		}
	}
	else if(areaid == gAutoSchool)
	{
		ShowPlayerDialogEx(playerid, 710, DIALOG_STYLE_LIST, !"Экзамен", !"Выберите вид транспорта, на который хотите получить лицензию:\n{FF7319}1.{FFFFFF} Наземный транспорт\t{42B02C}500$\n{FF7319}2.{FFFFFF} Воздушный транспорт\t{42B02C}10000$\n{FF7319}3.{FFFFFF} Водный транспорт\t\t{42B02C}3000$", !"OK", !"Отмена");
	}
 	else if(areaid >= BankMenu[0] && areaid <= BankMenu[2])
 	{
	 	if(PI[playerid][pBizKey])
		 	ShowPlayerDialogEx(playerid, 791, DIALOG_STYLE_LIST, !"Услуги банка", !"Мои счета\nОткрыть новый счёт\nСнять деньги с кассы бизнеса", !"Принять", !"Отмена");
	 	
	 	else
	 		ShowPlayerDialogEx(playerid, 791, DIALOG_STYLE_LIST, !"Услуги банка", !"Мои счета\nОткрыть новый счёт", !"Принять", !"Отмена");

 	}
 	else if(areaid >= BankProperty[0] && areaid <= BankProperty[2])
 	{
		if(PI[playerid][pHouseKey] || PI[playerid][pBizKey])
	 		ShowPlayerDialogEx(playerid, 790, DIALOG_STYLE_LIST, !"Услуги банка", !"Оплата дома\nОплата бизнеса\nОплата АЗС", !"Перейти", !"Отмена");

		else
		    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет имущества");
 	}
  	else if(areaid >= BankReturn[0] && areaid <= BankReturn[2])
 	{
		ShowPlayerDialogEx(playerid, 780, DIALOG_STYLE_LIST, !"Услуги банка", !"Вернуть деньги за дом\nВернуть деньги за бизнес\nВернуть деньги за АЗС", !"Перейти", !"Отмена");
 	}
	else if(areaid >= gSignal[0] && areaid <= gSignal[3])
	{
	    if(!PI[playerid][pCars])
			return 1;

		new
			bizid = areaid - gSignal[0];

		ShowPlayerDialogEx(playerid, 210, DIALOG_STYLE_LIST, !"Улучшения автомобиля", !"{FF7319}1.{FFFFFF} Сигнализация\n{FF7319}2.{FFFFFF} Основной цвет\n{FF7319}3.{FFFFFF} Дополнительный цвет", !"Купить", !"Выход"), pTemp[playerid][pCarBiz] = bizid+57;
	}

  	else if(areaid >= PTSConfirm[0] && areaid <= PTSConfirm[2])
 	{
 	    if(!PI[playerid][pCars]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас нет личного т/с");

 	    if(PI[playerid][pPTS] == 1 || !temp_car_num_get[playerid]) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Для начала установите номерные знаки ({FFFF00}/gps -> Авторынки/Тюнинги -> Пункт выдачи номеров{FFFFFF})");
 	    
 	        
		ShowPlayerDialogEx(playerid, 694, DIALOG_STYLE_MSGBOX, !"Получение ПТС", !"{FFFFFF}Для Вас готово ПТС\n\nВы хотите его забрать?", !"Да", !"Отмена");
 	}
 	else if(areaid >= gPDTicket[0] && areaid <= gPDTicket[2])
 	{
 	    if(!PI[playerid][pFine])
        	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет неоплаченных штрафов");
        	
		new
		    frmt_ticket_message[128];
		    
		format(frmt_ticket_message, sizeof frmt_ticket_message, "\n\n{FFFFFF}Оплатить штраф в размере {FF0000}%d${FFFFFF}?\n\n", PI[playerid][pFine]);
		ShowPlayerDialogEx(playerid, 695, DIALOG_STYLE_MSGBOX, !"Оплата штрафа", frmt_ticket_message, !"Да", !"Отмена");
 	}
 	else if(areaid >= gPDJail[0] && areaid <= gPDJail[2])
 	{
 	    if(!PI[playerid][pWanted])
        	return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет розыска");

		new
            time;
            
		if(PI[playerid][pWanted] > 1)
		    time = (PI[playerid][pWanted]-1) * 300;

		else
		    time = PI[playerid][pWanted] * 300;

		new
		    frmt_wanted_message[128];

		format(frmt_wanted_message, sizeof frmt_wanted_message, "{FFFFFF}Вы действительно хотите сдаться с повинной ?\n\nВремя заключения: {FF0000}%d{FFFFFF} минут", time/60);
		ShowPlayerDialogEx(playerid, 696, DIALOG_STYLE_MSGBOX, !"Сдача с повинной", frmt_wanted_message, !"Да", !"Отмена");
 	}
 	else if(areaid >= gFlyer[0] && areaid <= gFlyer[2])
 	{
 	    if(PI[playerid][pFraction] != 9)
        	return 1;
        	
		switch(GetPlayerVirtualWorld(playerid))
		{
		    case 1: if(PI[playerid][pSubfraction] != 1) return 1;
		    case 2: if(PI[playerid][pSubfraction] != 3) return 1;
		    case 3: if(PI[playerid][pSubfraction] != 2) return 1;
		}
		
		pTemp[playerid][pFlyersList] = 0;
		
		new
		    frmt_flyers_list[2900],
			query_get_list[350],
			name[24],
			id,
			flyers_count;

		format(query_get_list, sizeof query_get_list, "SELECT `id`, `name`, `sender` FROM `flyers` WHERE `checked` = 1 AND `subfraction` = %d AND `count` > 0 LIMIT 0, 41", PI[playerid][pSubfraction]);
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
 	else if(areaid >= gPhoto[0] && areaid <= gPhoto[2])
 	{
 	    if(PI[playerid][pFraction] != 9)
        	return 1;
        	
		switch(GetPlayerVirtualWorld(playerid))
		{
		    case 1: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
		    case 2: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
		    case 3: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
		}

		new
		    weapon,
		    ammo;
		    
        GetPlayerWeaponData(playerid, GetWeaponSlot(43), weapon, ammo);

		if(ammo > 0 && weapon == 43)
			return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас уже есть фотоаппарат!");

		_GiveGun(playerid, 43, 10);
		SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы взяли фотоаппарат");

	}
	else if(areaid >= gRadioBoard[0] && areaid <= gRadioBoard[2])
	{
 	    if(PI[playerid][pFraction] != 9)
        	return 1;

		switch(GetPlayerVirtualWorld(playerid))
		{
		    case 1: if(PI[playerid][pSubfraction] != 1 && PI[playerid][pRank] < 11) return 1;
		    case 2: if(PI[playerid][pSubfraction] != 3 && PI[playerid][pRank] < 11) return 1;
		    case 3: if(PI[playerid][pSubfraction] != 2 && PI[playerid][pRank] < 11) return 1;
		}
		
		ShowPlayerDialogEx(playerid, 529, DIALOG_STYLE_INPUT, !"Доска", !"{FFFFFF}Введите текст:\n\n{AFAFAF}Используйте символ \"|\" для переноса текста на другую строку", !"Готово", !"Отмена");
	}
 	for(new i; i < bag_count; i++)
 	{
 		if(areaid == bag_area[i])
 	    {
			new
				msg_toall[100];

			format(msg_toall, sizeof msg_toall, "Вы нашли мешок с %d$", bag_value[i]);
			SendClientMessage(playerid, COLOR_YELLOW, msg_toall);

			format(msg_toall, sizeof msg_toall, "%s(%d) подобрал мешок с %d$", PN(playerid), playerid, bag_value[i]);
			SendClientMessageToAll(COLOR_BLUE, msg_toall);
			
			GiveMoney(playerid, bag_value[i], "нашел мешок");
			DestroyDynamicPickup(bag_pickup[i]);
			
			bag_value[i] = 0;
			
 	        bag_count--;
 	        DestroyDynamicArea(bag_area[i]);
 	    }
 	}
	if(PI[playerid][pFraction] == 7)
	{
		for(new i, j = GetVehiclePoolSize(); i <= j; i++)
		{
		    if(i == INVALID_VEHICLE_ID)
		        continue;
		        
			if(areaid == VehicleLoad[i][vlArea])
			{
				if(VehicleLoad[i][vlLoading] == true && (GetPVarInt(playerid,"carrygun") || GetPVarInt(playerid,"carryammo")))
				{

				 	if(VehicleLoad[i][vlLimit] + 1 > 25) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В т.с. недостаточно места");

					SetPVarInt(playerid, "carrygun", 0);
					SetPVarInt(playerid, "carryammo", 0);
					
					VehicleLoad[i][vlLimit] ++;
					
					RemovePlayerAttachedObject(playerid, 3);
					ApplyAnimation(playerid, !"CARRY", !"putdwn", 1.0, 0, 1, 1, 0, 0, 1);

					new
						mes[128];

					format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[i][vlLimit]);
					UpdateDynamic3DTextLabelText(VehicleLoad[i][vlText], COLOR_WHITE, mes);

				}
				else if(VehicleLoad[i][vlUnloading] == true && !GetPVarInt(playerid,"carrygun") && !GetPVarInt(playerid,"carryammo"))
				{
					if(VehicleLoad[i][vlLimit] - 1 < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В т.с. недостаточно боеприпасов");
						
					VehicleLoad[i][vlLimit] --;
					SetPVarInt(playerid, "carrygun", 300);
					SetPVarInt(playerid, "carryammo", 300);
					
					new
						mes[128];

					format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[i][vlLimit]);
					UpdateDynamic3DTextLabelText(VehicleLoad[i][vlText], COLOR_WHITE, mes);

					ApplyAnimation(playerid, !"CARRY", !"liftup", 1.0, 0, 1, 1, 0, 0, 1);
					SetTimerEx("@__CarryDelay",1000, false, "i", playerid);
					SetPlayerAttachedObject(playerid, 3, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0);
				}

			}
		}
	}
	if(IsAMafia(playerid))
	{
		for(new i, j = GetVehiclePoolSize(); i <= j; i++)
		{
		    if(i == INVALID_VEHICLE_ID)
		        continue;

			if(areaid == VehicleLoad[i][vlArea])
			{
				if(VehicleLoad[i][vlMafLoading] == true && (GetPVarInt(playerid,"carrygun") || GetPVarInt(playerid,"carryammo")))
				{

					if(VehicleLoad[i][vlLimit] + 1 > 25) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В т.с. недостаточно места");

					VehicleLoad[i][vlLimit] ++;

					SetPVarInt(playerid, "carrygun", 0);
					SetPVarInt(playerid, "carryammo", 0);

					RemovePlayerAttachedObject(playerid, 3);
					ApplyAnimation(playerid, !"CARRY", !"putdwn", 1.0, 0, 1, 1, 0, 0, 1);


					new
						mes[128];

					format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[i][vlLimit]);
					UpdateDynamic3DTextLabelText(VehicleLoad[i][vlText], COLOR_WHITE, mes);

				}
				else if(VehicleLoad[i][vlMafUnloading] == true && !GetPVarInt(playerid,"carrygun") && !GetPVarInt(playerid,"carryammo"))
				{
					if(VehicleLoad[i][vlLimit] - 1 < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В т.с. недостаточно боеприпасов");

					VehicleLoad[i][vlLimit] --;
					SetPVarInt(playerid, "carrygun", 300);
					SetPVarInt(playerid, "carryammo", 300);

					new
						mes[128];

					format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[i][vlLimit]);
					UpdateDynamic3DTextLabelText(VehicleLoad[i][vlText], COLOR_WHITE, mes);

					ApplyAnimation(playerid, !"CARRY", !"liftup", 1.0, 0, 1, 1, 0, 0, 1);
					SetTimerEx("@__CarryDelay",1000, false, "i", playerid);
					SetPlayerAttachedObject(playerid, 3, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0);
				}
				else if(VehicleLoad[i][vlRob] == true && !GetPVarInt(playerid,"carrygun") && !GetPVarInt(playerid,"carryammo"))
				{
					if(VehicleLoad[i][vlLimit] - 1 < 0) return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В т.с. недостаточно боеприпасов");
					
					VehicleLoad[i][vlLimit] --;
					SetPVarInt(playerid, "carrygun", 300);
					SetPVarInt(playerid, "carryammo", 300);
					new
						mes[128];

					format(mes, sizeof mes, "Ящиков: {C6E8E8}%d/25", VehicleLoad[i][vlLimit]);
					UpdateDynamic3DTextLabelText(VehicleLoad[i][vlText], COLOR_WHITE, mes);

					ApplyAnimation(playerid, !"CARRY", !"liftup", 1.0, 0, 1, 1, 0, 0, 1);
					SetTimerEx("@__CarryDelay",1000, false, "i", playerid);
					SetPlayerAttachedObject(playerid, 3, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0);
				}
				return 1;
			}
		}
	}
 	if(areaid == RoadInvite)
 	{
	    if(IsPlayerInAnyVehicle(playerid))
	        return 1;
	        
		if(InJob[playerid] != 5)
			ShowPlayerDialogEx(playerid, 410, DIALOG_STYLE_MSGBOX, !"Строитель дорог", !"{FFFFFF}Вы действительно хотите устроиться на работу строителя дорог?", !"Да", !"Отмена");

		else
		    ShowPlayerDialogEx(playerid, 411, DIALOG_STYLE_MSGBOX, !"Строитель дорог", !"{FFFFFF}Вы хотите уволиться с работы строителя дорог?", !"Да", !"Отмена");
	}
 	else if(areaid == PorterInvite)
 	{
	    if(IsPlayerInAnyVehicle(playerid))
	        return 1;
	        
		if(InJob[playerid] != 6)
			ShowPlayerDialogEx(playerid, 415, DIALOG_STYLE_MSGBOX, !"Грузчик", !"{FFFFFF}Вы действительно хотите устроиться на работу грузчиком?", !"Да", !"Отмена");

		else
		    ShowPlayerDialogEx(playerid, 416, DIALOG_STYLE_MSGBOX, !"Грузчик", !"{FFFFFF}Вы хотите уволиться с работы грузчиком?", !"Да", !"Отмена");
	}
	else if(areaid == AutoInvite)
 	{
	    if(IsPlayerInAnyVehicle(playerid))
	        return 1;

		if(InJob[playerid] != 7)
			ShowPlayerDialogEx(playerid, 417, DIALOG_STYLE_MSGBOX, !"Сборщик автозапчастей", !"{FFFFFF}Вы действительно хотите устроиться на работу сборщика автозапчастей?", !"Да", !"Отмена");

		else
		    ShowPlayerDialogEx(playerid, 428, DIALOG_STYLE_MSGBOX, !"Сборщик автозапчастей", !"{FFFFFF}Вы хотите уволиться с работы сборщика автозапчастей?", !"Да", !"Отмена");
	}
    new
		pstate = GetPlayerState(playerid);

	if(areaid >= AutoLoad[0] && areaid <= AutoLoad[5] && pstate == PLAYER_STATE_ONFOOT && InJob[playerid] == 7 && temp_auto_amount[playerid] == 1)
 	{
		new
			table;

		for(new i; i < 6; i++)
		{
			if(AutoLoad[i] == areaid)
				table = i;
		}

		if(AutoTime[table])
			return SendClientMessage(playerid, COLOR_GREY, !"На этом столе нет деталей. Подойдите к другому");

		AutoTime[table] = 10;

		temp_auto_amount[playerid] = 2;
		SendClientMessage(playerid, COLOR_WHITE, !"Вы взяли детали. Теперь идите к столу, чтобы собрать запчасть");
		new
		    rand = RandomEx(0, 4),
			modelid;

		if(AutoItem[rand] == 1003)
            modelid = 1090;
		else
            modelid = AutoItem[rand];

  		SetPlayerAttachedObject(playerid, 0, modelid, 6, AutoSpare[rand][0], AutoSpare[rand][1], AutoSpare[rand][2], AutoSpare[rand][3], AutoSpare[rand][4], AutoSpare[rand][5], AutoSpare[rand][6], AutoSpare[rand][7], AutoSpare[rand][8]);
  		temp_auto_rand[playerid] = rand+1;

  		temp_auto_model[playerid] = AutoItem[rand];
 	}
	else if(areaid >= AutoWork[0] && areaid <= AutoWork[9] && pstate == PLAYER_STATE_ONFOOT && InJob[playerid] == 7 && temp_auto_amount[playerid] == 2)
	{
		if(temp_auto_object[playerid])
			return 1;

		new
			table;

		for(new i; i < 10; i++)
		{
			if(AutoWork[i] == areaid)
				table = i;
		}

		if(AutoTableStat[table])
			return SendClientMessage(playerid, COLOR_GREY, !"Стол занят. Подойдите к другому");

	    if(IsPlayerInAnyVehicle(playerid))
			return 1;


		RemovePlayerAttachedObject(playerid, 0);

		new objectid;

		if(temp_auto_model[playerid] == 1090 || temp_auto_model[playerid] == 1719)
            objectid = CreateDynamicObject(temp_auto_model[playerid], AutoTables[table][0], AutoTables[table][1], AutoTables[table][2], 0.0, 0.0, AutoRotation[temp_auto_rand[playerid]-1][0]);
            
		else if(temp_auto_model[playerid] == 1104 || temp_auto_model[playerid] == 1020)
            objectid = CreateDynamicObject(temp_auto_model[playerid], AutoTables[table][0], AutoTables[table][1]+1.0, AutoTables[table][2], 0.0, 0.0, AutoRotation[temp_auto_rand[playerid]-1][0]);


		temp_auto_object[playerid] = objectid;
		temp_auto_table[playerid] = table+1;
		AutoTableStat[table] = true;
		ClearAnimations(playerid);
		ApplyAnimation(playerid, !"CAR_CHAT", !"CAR_Sc4_BL", 4.0, 1, 1, 1, 0, 6000, 0);
		SetPlayerAttachedObject(playerid, 0, 18644, 5, 0.078999, 0.042999, -0.012999, -3.299995, 0.000000, 0.000000);
		SetPlayerAttachedObject(playerid, 1, 19627, 6, 0.065999, 0.051999, 0.021000, 90.699989, 0.000000, -75.400009);

		SetTimerEx("@__AutoReady",6000, false, "i", playerid);
	}
	else if(areaid == AutoUnload && InJob[playerid] == 7 && temp_auto_amount[playerid] == 3)
	{
	    if(IsPlayerInAnyVehicle(playerid))
			return 1;

		ApplyAnimation(playerid, !"CARRY", !"putdwn", 4.0, 0, 1, 1, 0, 0, 1);
		
		if(PI[playerid][pDaysSalary] > 0)
			temp_auto_salary[playerid] += 200;
			
		else
		    temp_auto_salary[playerid] += 100;

		new
			frmt_salary[120];

		if(PI[playerid][pDaysSalary] > 0)
			format(frmt_salary, sizeof frmt_salary, "Запчасть сдана на склад. {42B02C}+$200{FFFFFF} к зарплате. Заработано: {8D2424}$%d", temp_auto_salary[playerid]);
			
		else
			format(frmt_salary, sizeof frmt_salary, "Запчасть сдана на склад. {42B02C}+$100{FFFFFF} к зарплате. Заработано: {8D2424}$%d", temp_auto_salary[playerid]);

		SendClientMessage(playerid, COLOR_WHITE, frmt_salary);
		PI[playerid][pPointsFactory] += 3;
		UpdatePlayerData(playerid, "PointsFactory", PI[playerid][pPointsFactory]);
		if(PI[playerid][pQuest] == 5 && PI[playerid][pQuestStatus] == 1)
		{
		    PI[playerid][pQuestProcess]++;
		    UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
			if(PI[playerid][pQuestProcess] >= 20)
			{
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		    	SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы собрали 20 автозапчастей. Отправляйтесь к Саймону");
			}
		}

		RemovePlayerAttachedObject(playerid, 0);
		temp_auto_amount[playerid] = 1;
		DisablePlayerCheckpoint(playerid);
	}
	else if(areaid >= TeleportPickup[0] && areaid <= TeleportPickup[sizeof(TeleportInfo)-1])
	{
	    if(IsPlayerInAnyVehicle(playerid))
        	return 1;
        	
		if(justtp_exit[playerid] == true)
		{
			justtp_exit[playerid] = false;
			return 1;
		}

		if(PI[playerid][pJailTime] > 0)
			return 1;

        justtp_exit[playerid] = true;

		if(InJob[playerid] == 7)
		{
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

        new tp = areaid - TeleportPickup[0];

		if(PI[playerid][pFraction] == 10)
		{
			if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
			{
				new
				    target = GotoInfo[playerid][gtID];

				J_SetPlayerFacingAngle(target, TeleportInfo[tp][tpExitPos_A]);
				J_SetPlayerPos(target, TeleportInfo[tp][tpExitPos_X]+0.9*-floatsin(TeleportInfo[tp][tpExitPos_A], degrees), TeleportInfo[tp][tpExitPos_Y]+0.9*floatcos(TeleportInfo[tp][tpExitPos_Y], degrees), TeleportInfo[tp][tpExitPos_Z]);
		        justtp_exit[target] = true;
				if(GetPlayerVirtualWorld(target)==0 && GetPlayerInterior(target)==0)
				{
					NoEnterPickup[target] = 4;
			 		f_TogglePlayerControllable(target,false);
		 		}
		 		SetPlayerInterior(target, TeleportInfo[tp][tpExitInt]);
				SetPlayerVirtualWorld(target, TeleportInfo[tp][tpExitWorld]);

				temp_cuffer_sender[target] = INVALID_PLAYER_ID;
				temp_cuffer_receiver[playerid] = INVALID_PLAYER_ID;

				f_TogglePlayerControllable(target, true);
				SetPlayerSpecialAction(target, 0);
			    ClearAnims(target);
		        CheckPlayerGoCuff(target);
		        CheckPlayerGoCuff(playerid);
			}
		}
		if(tp == 21 || tp == 22 || tp == 23)
		{
		    PI[playerid][pHeal] = 1;
		    PI[playerid][pHealTime] = 0;
		}
		if(tp == 76 || tp == 78 || tp == 80 || tp == 82)
		{
			new
			    hallid = -1;

			switch(tp)
			{
			    case 76: hallid = 1;
			    case 78: hallid = 2;
			    case 80: hallid = 3;
			    case 82: hallid = 0;
			}
			
			if(hallid == -1)
			    return 1;
			    
			if((PI[playerid][pFraction] != 10 || PI[playerid][pSubfraction] != hallid) && (PI[playerid][pFraction] != 7 && temp_army_loadfr[playerid] != 10 && temp_army_loadsf[playerid] != hallid))
				return 1;
			    
		}
		if(tp == 52 || tp == 54 || tp == 84 || tp == 86)
		{
		    new
		        armyid = -1;
		        
			if(tp == 52 || tp == 84)
				armyid = 2;
				
			else if(tp == 54 || tp == 86)
			    armyid = 1;
			
			if(armyid == -1)
			    return 1;
			    
			if((PI[playerid][pFraction] != 7 || PI[playerid][pSubfraction] != armyid) && (PI[playerid][pFraction] != 7 || PI[playerid][pRank] < 11))
			    return 1;

		}
		if(tp == 0 || tp == 72 || tp == 74 || tp == 62 || tp == 66 || tp == 70)
		{
		    new
		        pdid = -1;

			if(tp == 0 || tp == 66)
				pdid = 2;

			else if(tp == 72 || tp == 62)
			    pdid = 1;
			    
			else if(tp == 74 || tp == 70)
				pdid = 3;

			if(pdid == -1)
			    return 1;

			if((PI[playerid][pFraction] != 8 || PI[playerid][pSubfraction] != pdid) && (PI[playerid][pFraction] != 8 || PI[playerid][pRank] < 11) && (PI[playerid][pFraction] != 7 && temp_army_loadfr[playerid] != 8 && temp_army_loadsf[playerid] != pdid))
			    return 1;
		}
		if(tp == 50)
		{
			if(PI[playerid][pLevel] < 2)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы должны прожить 2 года в штате чтобы попасть в это заведение");

		}
		if(tp == 88)
		{
			if((PI[playerid][pFraction] != 11) && (PI[playerid][pFraction] != 7 && temp_army_loadfr[playerid] != 11 && temp_army_loadsf[playerid] != 0))
			    return 1;
		}
		if(tp == 8)
		{
			if(PI[playerid][pFraction] != 11)
			    return 1;
		
		}
		
		J_SetPlayerFacingAngle(playerid, TeleportInfo[tp][tpExitPos_A]);
		//SetPlayerPos(playerid, TeleportInfo[tp][tpExitPos_X]+1.9*-floatsin(TeleportInfo[tp][tpExitPos_A], degrees), TeleportInfo[tp][tpExitPos_Y]+1.9*floatcos(TeleportInfo[tp][tpExitPos_Y], degrees), TeleportInfo[tp][tpExitPos_Z]);
		SetPlayerPos(playerid, TeleportInfo[tp][tpExitPos_X], TeleportInfo[tp][tpExitPos_Y], TeleportInfo[tp][tpExitPos_Z]);
        
		if(GetPlayerVirtualWorld(playerid)==0 && GetPlayerInterior(playerid)==0)
		{
			NoEnterPickup[playerid] = 2;
	 		f_TogglePlayerControllable(playerid,false);
 		}
 		SetPlayerInterior(playerid, TeleportInfo[tp][tpExitInt]);
		SetPlayerVirtualWorld(playerid, TeleportInfo[tp][tpExitWorld]);
		return true;
	}

	for(new h; h < OWNABLEHOUSES; h++)
	{
	    if(areaid == HouseArea[h])
	    {
     		if(!IsPlayerInAnyVehicle(playerid))
			{
				if(justtp_exit[playerid] == true)
				{
					justtp_exit[playerid] = false;
					return 1;
				}

				if(GetString(HouseInfo[h][hOwner],"The State"))
				{
					new
					    string[151 + 4 + 9 + 12];
					    
					new classname[40];
					switch(HouseInfo[h][hLevel])
					{
						case 0: classname = "Эконом";
						case 1: classname = "Cредний";
						case 2: classname = "Элитный";
						case 3: classname = "Особняк";
						default: classname = "Неизвестно";
					}
					
			        InfoHouse[playerid] = h;
					format(string,sizeof(string),"\
					{FFFFFF}House ID: \t{1E90FF}%d\n\
					{FFFFFF}Цена дома: \t{1E90FF}$%d\n\
					{FFFFFF}Класс: \t\t{1E90FF}%s\n\n\
					{FFFFFF}Для покупки нажмите {34C924}Купить",HouseInfo[h][hID],HouseInfo[h][hCost],classname);
					ShowPlayerDialogEx(playerid, 29, DIALOG_STYLE_MSGBOX, !"Дом продается", string, !"Купить", !"Отмена");
				}
				else
				{
				    InfoHouse[playerid] = h;
				    
					new
					    string[195 + 4 + MAX_PLAYER_NAME + 12];
					    
					new classname[40];
					switch(HouseInfo[h][hLevel])
					{
						case 0: classname = "Эконом";
						case 1: classname = "Cредний";
						case 2: classname = "Элитный";
						case 3: classname = "Особняк";
						default: classname = "Неизвестно";
					}
								
					format(string,sizeof(string), "\
					{FFFFFF}House ID: \t{1E90FF}%d\n\
					{FFFFFF}Цена дома: \t{1E90FF}%d$\n\
					{FFFFFF}Владелец: \t{1E90FF}%s\n\
					{FFFFFF}Класс: \t\t{1E90FF}%s\n\n\
					{FFFFFF}Для входа в дом нажмите {34C924}Войти",HouseInfo[h][hID],HouseInfo[h][hCost],HouseInfo[h][hOwner],classname);
				    ShowPlayerDialogEx(playerid, 30, DIALOG_STYLE_MSGBOX, !"Вход", string, !"Войти", !"Отмена");
				}
			}
		}
	}
	for(new b; b < MAX_BIZ; b++)
	{
	    if(areaid == BusinessArea[b])
	    {
     		if(!IsPlayerInAnyVehicle(playerid))
			{
				if(justtp_exit[playerid] == true)
				{
					justtp_exit[playerid] = false;
					return 1;
				}
			    
                if(b < 0)
					return SendClientMessage(playerid,COLOR_GREY,"Ошибка (#100)");
					
                InfoBiz[playerid] = b;

                if(GetString(BizInfo[b][bOwner], "The State"))
				{
					new format_business_buy[56];
					format(format_business_buy,sizeof(format_business_buy),"{FFFFFF}Этот бизнес продается за {FF0000}$%d.",BizInfo[b][bCost]);
					ShowPlayerDialogEx(playerid, 642, DIALOG_STYLE_MSGBOX, !"Бизнес", format_business_buy, !"Войти", !"Купить");
				}
				else
				{
    				if(BizInfo[b][bLock])
				    {
					    if(BizInfo[b][bState] == 16 && PI[playerid][pAge] < 18)
					        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не можете зайти в этот бизнес так как Вам меньше 18-ти лет");
				    
					    if(BizInfo[b][bEnterPrice])
					    {
							new format_business_enterprice[46];
							format(format_business_enterprice, sizeof format_business_enterprice, "{FFFFFF}Стоимость входа {FF0000}$%d.", BizInfo[b][bEnterPrice]);
							ShowPlayerDialogEx(playerid, 760, DIALOG_STYLE_MSGBOX, !"Бизнес", format_business_enterprice, !"Войти", !"Отмена");
					    }
						else
					    {
							new bint = BizInfo[b][bBint]-1;
							if(bint < 0 || bint >= MAX_BINTS)
								return SendClientMessage(playerid,COLOR_GREY,"Ошибка (#99)");


							if(BizInfo[b][bState] == 8)
								return ShowPlayerDialogEx(playerid, 740, DIALOG_STYLE_MSGBOX, !"Автосалон", !"{FFFFFF}Вы хотите войти в автосалон класса: Эконом?", !"Да", !"Нет");

							if(BizInfo[b][bState] == 9)
								return ShowPlayerDialogEx(playerid, 741, DIALOG_STYLE_MSGBOX, !"Автосалон", !"{FFFFFF}Вы хотите войти в автосалон класса: Средний?", !"Да", !"Нет");

							if(BizInfo[b][bState] == 10)
								return ShowPlayerDialogEx(playerid, 742, DIALOG_STYLE_MSGBOX, !"Автосалон", !"{FFFFFF}Вы хотите войти в автосалон класса: Элитный?", !"Да", !"Нет");

							if(BizInfo[b][bState] == 11)
								return ShowPlayerDialogEx(playerid, 743, DIALOG_STYLE_MSGBOX, !"Мотосалон", !"{FFFFFF}Вы хотите войти в мотосалон?", !"Да", !"Нет");

	                        justtp_exit[playerid] = true;

		    				SetPlayerPos(playerid, BizInts[bint][bintX], BizInts[bint][bintY], BizInts[bint][bintZ]);

							SetPlayerInterior(playerid, BizInts[bint][bintInterior]);
							SetPlayerVirtualWorld(playerid, b+1);

							SetPlayerFacingAngle(playerid, BizInts[bint][bintR]);
							BizEntered[playerid] = BizInfo[b][bID];
							BizInfo[b][bVisit] ++;

							if(BizInfo[b][bImprove][0])
								SendClientMessage(playerid,COLOR_GREY,"В этом бизнесе имеется аптечка. Чтобы восстановить здоровье используйте {FFFFFF}/healup ({00CC00}$150{FFFFFF})");
						}
					}
				}
			}
		}
	}
 	for(new bc = 0; bc < MAX_BINTS; bc++)
	{
		if(areaid == BintExitArea[bc])
		{
			if(justtp_exit[playerid] == true)
			{
				justtp_exit[playerid] = false;
				return 1;
			}


			new
				businessid = BizEntered[playerid]-1;

			if(businessid < 0)
				return 1;

            justtp_exit[playerid] = true;
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

 			SetPlayerPos(playerid, BizInfo[businessid][bEnter_X], BizInfo[businessid][bEnter_Y], BizInfo[businessid][bEnter_Z]);


			SetPlayerFacingAngle(playerid, BizInfo[businessid][bEnter_R]);
	        BizEntered[playerid] = 0;
	 	}
		else if(areaid == BintBuyArea[bc])
		{
			new
				businessid = BizEntered[playerid]-1;

			if(businessid < 0)
				return 1;

			new businesstype = BizInfo[businessid][bState];
			switch(businesstype)
			{
				case 1:
				{
				    new
						format_shop_buy[480];

	   				for(new i; i < SHOP_OBJECTS; i++)
			   			format(format_shop_buy, sizeof format_shop_buy, "{ffffff}%s%s {7AC71F}($%d)\n", format_shop_buy, ShopObject[i], ShopPrice[i]);

					ShowPlayerDialogEx(playerid, 774, DIALOG_STYLE_LIST, !"Магазин 24/7", format_shop_buy, !"Купить", !"Выход");
				}
				case 2: ShowPlayerDialogEx(playerid, 716, DIALOG_STYLE_LIST, !"Клуб", !"Пиво [$215]\nВино [$330]\nШампанское [$335]\nВиски [$290]\nШаверма [$490]", !"Купить", !"Выход");
				case 3: ShowPlayerDialogEx(playerid, 717, DIALOG_STYLE_LIST, !"Ресторан", !"Запеченный лосось [$580]\nСтейк средний прожарки [$650]\nСалат с судаком [$540]\nВино [$330]\nМалиновый чизкейк [$335]", !"Купить", !"Выход");
				case 4: ShowPlayerDialogEx(playerid, 718, DIALOG_STYLE_LIST, !"Burger Shot", !"Бургер с курицей [$380]\nБургер с говядиной[$410]\nЧизбургер [$425]\nКартошка Фри [$110]\nГазированный напиток(Pepsi/Cola/Fanta) [$230]", !"Купить", !"Выход");
				case 5: ShowPlayerDialogEx(playerid, 719, DIALOG_STYLE_LIST, !"Pizza Hut", !"Пицца Маргарита [$356]\nПицца 4 сыра [$390]\nКальцоне с ветчиной [$335]\nГазированный напиток(Pepsi/Cola/Fanta) [$230]", !"Купить", !"Выход");
				case 6: ShowPlayerDialogEx(playerid, 720, DIALOG_STYLE_LIST, !"Cluckin Bell", !"Бургер с курицей [$380]\nКуриные крылышки [$325]\nХотдог с куриной сосиской [$295]\nПирожок с яблоком [$270]\nЧай/Кофе [$220]", !"Купить", !"Выход");
				case 7:
				{
					if(justtp_exit[playerid] == true)
					{
						justtp_exit[playerid] = false;
						return 1;
					}
					else {
						if(!ChangingSkin[playerid]) {
							ChangingSkin[playerid] = true;
							new Float: pos[4];

							GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
							GetPlayerFacingAngle(playerid, pos[3]);
							SetPVarFloat(playerid, "posx", pos[0]);
							SetPVarFloat(playerid, "posy", pos[1]);
							SetPVarFloat(playerid, "posz", pos[2]);
							SetPVarFloat(playerid, "posa", pos[3]);
							SetPVarInt(playerid, "interior", GetPlayerInterior(playerid));
							SetPVarInt(playerid, "vw", GetPlayerVirtualWorld(playerid));
							f_TogglePlayerControllable(playerid, false);
							SetPlayerInterior(playerid, 14);
							SetPlayerVirtualWorld(playerid, playerid + 1);
							SetPlayerPos(playerid, 258.7497, -41.3828, 1002.0234);
							SetPlayerFacingAngle(playerid, 70.0);
							SetPlayerCameraPos(playerid, 258.7498 + (2.5 * floatsin(-70.0, degrees)), -41.3828 + (2.5 * floatcos(-70.0, degrees)), 1002.5);
							SetPlayerCameraLookAt(playerid, 258.7497, -41.3828, 1002.0234);
							SetPVarInt(playerid, "clothes_class", 1);
							SetPVarInt(playerid, "clothes_sel", 0);
							SetPVarInt(playerid, "curskin", GetPlayerSkin(playerid));
							ShowPlayerClothesTD(playerid);
						}
					}
				}
				case 12: ShowPlayerDialogEx(playerid, 721, DIALOG_STYLE_LIST, !"Оружейный магазин", !"Кастет 50$\nБейсбольная бита 100$\nДробовик 70$ за 1 патрон\nDesert Eagle 60$ за 1 патрон\nПолуавтомат MP5 30$ за 1 патрон\nАвтомат AK47 60$ за 1 патрон\nВинтовка 70$ за 1 патрон\nАвтомат M4 60$ за 1 патрон", !"Далее", !"Отмена");
				case 13:
				{
					ShowPlayerDialogEx(playerid, 293, DIALOG_STYLE_LIST, !"Магазин аксессуаров", !"1. Шапки\n2. Наушники\n3. Панамы\n4. Кепки\n5. Очки\n6. Банданы\n7. Шляпы\n8. Часы", !"Выбрать", !"Отмена");
				}
				case 14: ShowPlayerDialogEx(playerid, 377, DIALOG_STYLE_LIST, !"Агентство недвижимости", !"Выберите тип недвижимости:\n{FF7319}1.{FFFFFF} Дома\n{FF7319}2.{FFFFFF} Бизнесы\n{FF7319}3.{FFFFFF} АЗС", !"Выбор", !"Выход");
				case 15:
				{
				    if(0 == gPaintBall[pbStatus])
				        return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}В данный момент нет доступных игр");
				        
					new
					    frmt_center_message[128],
						status[10];
					    
					strcat(frmt_center_message, "№. Название\tКол-во участников\tДо начала\n");


					if(gPaintBall[pbStatus] == 1)
					{
						if(gPaintBall[pbPlayers] == 30)
						    strcat(status, "{FF0000}");
						    
						else
						    strcat(status, "{33AA33}");
						    
						format(frmt_center_message, sizeof frmt_center_message, "%s{FF7319}1.{FFFFFF} PaintBall\t%s%d/30{FFFFFF}\t%s", frmt_center_message, status, gPaintBall[pbPlayers], Convert(gPaintBall[pbTimer]));
					}
					
					else
						format(frmt_center_message, sizeof frmt_center_message, "%s{FF7319}1.{FFFFFF} PaintBall\t{FF0000}%d/30\t0:00{FFFFFF}", frmt_center_message, gPaintBall[pbPlayers]);

					ShowPlayerDialogEx(playerid, 464, DIALOG_STYLE_TABLIST_HEADERS, !"Центр развлечений", frmt_center_message, !"Выбор", !"Отмена");
				}
				case 16: ShowPlayerDialogEx(playerid, 217, DIALOG_STYLE_TABLIST_HEADERS, !"Sex Shop", !"{FFFFFF}№. Название\tСтоимость\n{FF7319}1.{FFFFFF} Имитатор №1\t{33AA33}2500$\n{FF7319}2.{FFFFFF} Имитатор №2\t{33AA33}3200$\n{FF7319}3.{FFFFFF} Имитатор №3\t{33AA33}4000$\n{FF7319}4.{FFFFFF} Имитатор №4\t{33AA33}5500$\n{FF7319}5.{FFFFFF} Пламенная душа\t{33AA33}15000$\n{FF7319}6.{FFFFFF} Ненасытная клубничка\t{33AA33}17000$\n{FF7319}7.{FFFFFF} Плохой полицейский\t{33AA33}20000$\n{FF7319}8.{FFFFFF} Женщина кошка\t{33AA33}20000$", !"Купить", !"Выход");

			}
		}
	}
	return true;
}
public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	if(areaid >= TeleportPickup[0] && areaid <= TeleportPickup[sizeof(TeleportInfo)-1])
	{

	}
	else if(areaid == gDemorgan)
	{
		if(PI[playerid][pPrison] == 4 && PI[playerid][pJailTime] > 0)
		{
		    J_SetPlayerPos(playerid, -1462.3071, -1435.1337, 1001.2538);
			J_SetPlayerFacingAngle(playerid, 84.6462);
		}
	}
	else if(areaid == RoadZone && InJob[playerid] == 5)
	{
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
	else if(areaid == PorterZone && InJob[playerid] == 6)
	{
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
    for(new i; i < sizeof(gCasinoTableCrupie); i++)
    {
        if(areaid == gCasinoTableCrupie[i])
		{
		    if(InJob[playerid] == 8 && temp_table[playerid] != -1)
		    {
		        new table = temp_table[playerid];
		        
                gTable[table][tCrup] = INVALID_PLAYER_ID;
                temp_table[playerid] = -1;
                
			}
		}
    }
    if(areaid == gGameCenter)
    {
		if(pTemp[playerid][pRegPaint])
		{
		    gPaintBall[pbPlayers]--;
		    pTemp[playerid][pRegPaint] = false;
		}
    }
	return true;
}
public ReloadAllAnims(playerid)
{
    PreloadAnimLib(playerid,"BASEBALL");
   	PreloadAnimLib(playerid,"BEACH");
	PreloadAnimLib(playerid,"benchpress");
	PreloadAnimLib(playerid,"BD_FIRE");
   	PreloadAnimLib(playerid,"BOMBER");
   	PreloadAnimLib(playerid,"CAMERA");
	PreloadAnimLib(playerid,"CAR_CHAT");
	PreloadAnimLib(playerid,"CARRY");
	PreloadAnimLib(playerid,"CASINO");
	PreloadAnimLib(playerid,"COP_AMBIENT");
 	PreloadAnimLib(playerid,"CRACK");
	PreloadAnimLib(playerid,"DAM_JUMP");
	PreloadAnimLib(playerid,"DEALER");
	PreloadAnimLib(playerid,"DODGE");
	PreloadAnimLib(playerid,"FOOD");
	PreloadAnimLib(playerid,"GANGS");
	PreloadAnimLib(playerid,"GRAVEYARD");
	PreloadAnimLib(playerid,"HEIST9");
	PreloadAnimLib(playerid,"INT_HOUSE");
	PreloadAnimLib(playerid,"INT_OFFICE");
	PreloadAnimLib(playerid,"KISSING");
	PreloadAnimLib(playerid,"LOWRIDER");
	PreloadAnimLib(playerid,"MD_CHASE");
	PreloadAnimLib(playerid,"ON_LOOKERS");
	PreloadAnimLib(playerid,"PARK");
	PreloadAnimLib(playerid,"PAULNMAC");
	PreloadAnimLib(playerid,"PED");
	PreloadAnimLib(playerid,"RYDER");
   	PreloadAnimLib(playerid,"RAPPING");
   	PreloadAnimLib(playerid,"RIOT");
	PreloadAnimLib(playerid,"SHOP");
   	PreloadAnimLib(playerid,"SMOKING");
	PreloadAnimLib(playerid,"SNM");
	PreloadAnimLib(playerid,"STRIP");
	PreloadAnimLib(playerid,"SUNBATHE");
	PreloadAnimLib(playerid,"SWAT");
	PreloadAnimLib(playerid,"SWEET");
	PreloadAnimLib(playerid,"OTB");
	PreloadAnimLib(playerid,"ROB_BANK");
	PreloadAnimLib(playerid,"goggles");
	PreloadAnimLib(playerid,"BAR");
	PreloadAnimLib(playerid,"SPRAYCAN");
	PreloadAnimLib(playerid,"MISC");
	PreloadAnimLib(playerid,"MEDIC");
	PreloadAnimLib(playerid,"GYMNASIUM");
	PreloadAnimLib(playerid,"POLICE");
	PreloadAnimLib(playerid,"DANCING");
	PreloadAnimLib(playerid,"CRIB");
	PreloadAnimLib(playerid,"FAT");
	PreloadAnimLib(playerid,"KNIFE");
	PreloadAnimLib(playerid,"CHAINSAW");
	PreloadAnimLib(playerid, "SWORD");
	ClearAnims(playerid);
	return true;
}

public OnPlayerSpawn(playerid)
{
    if(!IsPlayerLogged[playerid]) J_Kick(playerid);
	//if(gDebug) return SetPlayerVirtualWorld(playerid, 0);
    pTemp[playerid][pAntiAir] = 3;
    pTemp[playerid][pOnMP] = false;
    SetPlayerColor(playerid,0xFFFFFF11);
    
	new hour, minute, second;
	gettime(hour, minute, second);
	SetPlayerTime(playerid, hour, minute);

	resetgun(playerid);

	for(new x; x < 13; x ++) _SetGun(playerid, PI[playerid][pGuns][x], PI[playerid][pAmmos][x]);

	PI[playerid][pLastGun]=0;
	PI[playerid][pLastAmmo]=0;
	PlayerPlaySound(playerid, 1069, 0.0, 0.0, 0.0);
 	StopAudioStreamForPlayer(playerid);

 	if(temp_table[playerid] != -1)
  	{
   		new table = temp_table[playerid];

		gTable[table][tCrup] = INVALID_PLAYER_ID;
  		temp_table[playerid] = -1;

	}
    if(!IsPlayerLogged[playerid])
	{
		J_Kick(playerid);
		return true;
	}
	DeletePVar(playerid, "watch_filling");
	DeletePVar(playerid, "watch_business");
	DeletePVar(playerid, "watch_house");
	RemovePlayerAttachedObject(playerid,9);

  	gunmute[playerid] = gettime()+5;
 	if(GotoInfo[playerid][gtGoID] != INVALID_PLAYER_ID) CheckPlayerGoCuff(playerid);
	if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
	{
		new
		    target = GotoInfo[playerid][gtID];
		    
		temp_cuffer_sender[target] = INVALID_PLAYER_ID;
		temp_cuffer_receiver[target] = INVALID_PLAYER_ID;

		f_TogglePlayerControllable(target, true);
		SetPlayerSpecialAction(target, 0);
	    ClearAnims(target);
        CheckPlayerGoCuff(target);
        CheckPlayerGoCuff(playerid);
	}
	if(temp_cuffer_receiver[playerid] != INVALID_PLAYER_ID)
	{
		new
		    target = temp_cuffer_receiver[playerid]-1;

		if(IsPlayerConnected(target))
		{
			SetPlayerSpecialAction(target, SPECIAL_ACTION_NONE);
			RemovePlayerAttachedObject(target, 0);

			temp_cuffer_sender[target] = INVALID_PLAYER_ID;
			temp_cuffer_receiver[target] = INVALID_PLAYER_ID;

			TogglePlayerControllable(target, 1);
		}
	}
	if(temp_tie_receiver[playerid] != INVALID_PLAYER_ID)
	{
		new
		    target = temp_tie_receiver[playerid]-1;

		if(IsPlayerConnected(target))
		{
			temp_tie_sender[target] = INVALID_PLAYER_ID;
			temp_tie_receiver[playerid] = INVALID_PLAYER_ID;

			f_TogglePlayerControllable(target, true);
		}
	}
	if(temp_cuffer_sender[playerid] != INVALID_PLAYER_ID)
	{
	    new
			time = PI[playerid][pWanted] * 300 + 1800,
			cufferid = temp_cuffer_sender[playerid]-1;

        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 0);
        temp_cuffer_sender[playerid] = INVALID_PLAYER_ID;
        temp_cuffer_receiver[cufferid] = INVALID_PLAYER_ID;

	    PI[playerid][pJailTime] = time;
	    PI[playerid][pWanted] = 0;
	    SetPlayerWantedLevel(playerid, 0);
	    ResetPlayerWeapons(playerid);

        PI[playerid][pPrison] = RandomEx(1,3);
        
        PI[playerid][pJailAdmin] = 0;

	    new
			query[200];

	    format(query, sizeof query, "UPDATE `accounts` SET `JailTime` = '%d', `Prison` = '%d', `Wanted` = '0', `JailAdmin` = '0' WHERE `ID` = '%d'", PI[playerid][pJailTime], PI[playerid][pPrison], PI[playerid][pID]);
	    mysql_tquery(mysql, query);
	}
	if(GotoInfo[playerid][gtGoID] != INVALID_PLAYER_ID)
	{
	    new
			time = PI[playerid][pWanted] * 300 + 1800,
			cufferid = GotoInfo[playerid][gtGoID];

		if(!IsACop(cufferid))
		    return 1;
		    
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 0);
        CheckPlayerGoCuff(cufferid);
        CheckPlayerGoCuff(playerid);

	    PI[playerid][pJailTime] = time;
	    PI[playerid][pWanted] = 0;
	    SetPlayerWantedLevel(playerid, 0);
	    ResetPlayerWeapons(playerid);

        PI[playerid][pPrison] = RandomEx(1,3);
        
        PI[playerid][pJailAdmin] = 0;

	    new
			query[200];

	    format(query, sizeof query, "UPDATE `accounts` SET `JailTime` = '%d', `Prison` = '%d', `Wanted` = '0', `JailAdmin` = '0' WHERE `ID` = '%d'", PI[playerid][pJailTime], PI[playerid][pPrison], PI[playerid][pID]);
	    mysql_tquery(mysql, query);
	}
	if(pTemp[playerid][pMechID] != INVALID_VEHICLE_ID) MechSpawnEx(playerid);
	if(pTemp[playerid][pProductID] != INVALID_VEHICLE_ID) ProductSpawnEx(playerid);
	if(TempBGObject[playerid] != -1)
	{
	    DestroyPlayerObject(playerid, TempBGObject[playerid]);
	    TempBGObject[playerid] = -1;
	}
	SetPlayerWantedLevel(playerid, PI[playerid][pWanted]);
	GangZoneHideForPlayer(playerid, HideMapZone);
	SpecInfo[playerid][specSpectating] = false;
	SetPlayerDrunkLevel(playerid, 0);
	SetPlayerSkills(playerid);
	ResetDynamicCPs(playerid);
	DisableAllRaceCPs(playerid);
	CheckPlayerGoCuff(playerid);
	PI[playerid][pShowName]     = 1;
    HouseEntered[playerid] 		= 0;
    BizEntered[playerid] 		= 0;
    Controllable[playerid] 		= true;
    Clother[playerid] 			= -1;
	InJob[playerid] 			= 0;
    if(PI[playerid][pSkin] == 0)
	{
		Clother[playerid] = 0;
     	SetPlayerBuySkin(playerid);
	    return true;
	}
	else
	{
	    SetCameraBehindPlayer(playerid);
	    SetPlayerSkinEx(playerid, PI[playerid][pSkin]);
	}
	
	if(pTemp[playerid][pPaintTeam] > 0)
	{
		if(pTemp[playerid][pPaintTeam] == 1)
			gPaintBall[pbRedTeam]--;

		else if(pTemp[playerid][pPaintTeam] == 2)
			gPaintBall[pbBlueTeam]--;

	    PaintUpdate(pTemp[playerid][pPaintTeam]);
	    pTemp[playerid][pPaintTeam] = 0;
		for(new td; td < 8; td++)
			TextDrawHideForPlayer(playerid, tdPaintBall[td]);

	    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы потерпели поражение в мероприятии PaintBall");
	    
		PI[playerid][pDead] = false;
		SetPlayerPos(playerid, 827.5557,7.4137,1004.1870);
		SetPlayerFacingAngle(playerid, 271.5084);
		SetPlayerInterior(playerid, 3);
		SetPlayerVirtualWorld(playerid, 68);
		ResetPlayerWeapons(playerid);
		J_SetPlayerHealth(playerid, 100);

		BizEntered[playerid] = 68;
		if(PI[playerid][pFraction])
			SetPlayerColor(playerid, gFractionColor[PI[playerid][pFraction] - 1]);

		else
			SetPlayerColor(playerid, 0xFFFFFF11);

    	RemovePlayerAttachedObject(playerid, 8);
	    PI[playerid][pMaskON] = 0;

	    SetPlayerSkinEx(playerid, PI[playerid][pOldSkin]);

		for(new td; td < 8; td++)
			TextDrawHideForPlayer(playerid, tdPaintBall[td]);

	    pTemp[playerid][pPaintTeam] = 0;

		return 1;
	}
	// =========================================================================
	//GetSkinOfPlayer(playerid);
	SettingSpawn(playerid);
	//SetPlayerSkinEx(playerid, GetSkinOfPlayer(playerid));

    IsPlayerSpawned[playerid] = true;
    
   	if(PI[playerid][pSpectating]) StopPlayerSpectate(playerid);
	return true;
}
stock GetSkinOfPlayer(playerid)
{
	new skin;
	if(PI[playerid][pFraction] > 0 || PI[playerid][pSubfraction] > 0 && PI[playerid][pFractionSkin] > 0)
	    skin = PI[playerid][pFractionSkin];

	else skin = PI[playerid][pSkin];
	return skin;
}
stock Float:floatrand(Float:maxrand)
{
	new rand = random(floatround(maxrand * 10.0)); //rand = 0 - 9
	return float(rand) / 10.0;
}

stock SettingSpawn(playerid)
{
    if(IsPlayerNPC(playerid)) return true;
    f_TogglePlayerControllable(playerid, true);
    
	new skin = GetSkinOfPlayer(playerid);

   	/*if(PI[playerid][pHospital]>0)
	    J_SetPlayerHealth(playerid,PI[playerid][pHealth]);

	else
	{
	    if(PI[playerid][pLevel]>1)
	    {
		    PI[playerid][pHospital]=1;
		    J_SetPlayerHealth(playerid,20);
		}
	}*/
 	if(PI[playerid][pJailTime] > 0)
	{
	    if(!PI[playerid][pJailAdmin])
	    {
		    switch(random(4))
		    {
		        case 0: SetSpawnInfoEx(playerid, 42, 226.9169, 109.1662, 999.0156, 181.7349);
		        case 1: SetSpawnInfoEx(playerid, 42, 222.7322, 108.9943, 999.0156, 181.7349);
		        case 2: SetSpawnInfoEx(playerid, 42, 218.7821, 109.3731, 999.0156, 181.7349);
		        case 3: SetSpawnInfoEx(playerid, 42, 214.7852, 108.9267, 999.0156, 181.7349);
			}
		    switch(PI[playerid][pPrison])
		    {
				case 0..1:
				{
					SetPlayerVirtualWorld(playerid, 2);
		            SetPlayerInterior(playerid, 10);
		 		}
		        case 2:
				{
					SetPlayerVirtualWorld(playerid, 0);
		            SetPlayerInterior(playerid, 10);
		 		}
		        case 3:
				{
					SetPlayerVirtualWorld(playerid, 12);
		            SetPlayerInterior(playerid, 10);
				}
		    }
	    }
	    else
	    {
		    SetSpawnInfoEx(playerid, 42, -1462.3071, -1435.1337, 1001.2538, 84.6462);
		    SetPlayerVirtualWorld(playerid, 20);
			SetPlayerInterior(playerid, 5);
	    }
	    
		J_SetPlayerHealth(playerid, 100);
    	SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы посмотреть сколько Вам осталось сидеть в тюрьме, введите команду {FFFF00}/ptime");
		if(PI[playerid][pJailKey] && !PI[playerid][pJailAdmin])
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

 	else if(PI[playerid][pDead] || PI[playerid][pHealth] < 20.0)//Если чувак спавниться в больничке
	{
	    PI[playerid][pDead] = false;
        switch(random(16))//spawn больнички
		{
			case 0: SetSpawnInfoEx(playerid, skin, 698.1334, 1539.2463, 1306.1029, 180.1824);
			case 1: SetSpawnInfoEx(playerid, skin, 700.3589,1539.2889,1306.1029,174.5423);
			case 2: SetSpawnInfoEx(playerid, skin, 702.6758,1539.2542,1306.1029,179.6184);
			case 3: SetSpawnInfoEx(playerid, skin, 704.8028,1539.3495,1306.1029,182.6265);
			case 4: SetSpawnInfoEx(playerid, skin, 704.9193,1537.3452,1306.1029,359.8888);
			case 5: SetSpawnInfoEx(playerid, skin, 702.7484,1537.4052,1306.1029,3.2728);
			case 6: SetSpawnInfoEx(playerid, skin, 700.2785,1537.2789,1306.1029,358.3848);
			case 7: SetSpawnInfoEx(playerid, skin, 698.0598,1537.4175,1306.1029,1.2048);
			case 8: SetSpawnInfoEx(playerid, skin, 682.8416,1537.3025,1306.1029,358.1969);
			case 9: SetSpawnInfoEx(playerid, skin, 680.7443,1537.3580,1306.1029,1.0403);
			case 10: SetSpawnInfoEx(playerid, skin, 678.1501,1537.3337,1306.1029,0.2883);
			case 11: SetSpawnInfoEx(playerid, skin, 675.9568,1537.2734,1306.1029,1.0636);
			case 12: SetSpawnInfoEx(playerid, skin, 676.0109,1539.2842,1306.1029,178.3259);
			case 13: SetSpawnInfoEx(playerid, skin, 678.3596,1539.2207,1306.1029,178.5139);
			case 14: SetSpawnInfoEx(playerid, skin, 680.5267,1539.3403,1306.1029,181.1459);
			case 15: SetSpawnInfoEx(playerid, skin, 682.9220,1539.2468,1306.1029,180.9579);
		}
		switch(PI[playerid][pCheepses])//spawn больнички
		{
		    case 1:
		    {
		        SetPlayerVirtualWorld(playerid, 1);
		    	SetPlayerInterior(playerid, 3);
		    }
		    case 2:
		    {
		        SetPlayerVirtualWorld(playerid, 2);
		    	SetPlayerInterior(playerid, 3);
		    }
		    default:
			{
			 	SetPlayerVirtualWorld(playerid, 3);
		    	SetPlayerInterior(playerid, 3);
			}
		}
	    J_SetPlayerHealth(playerid,15);
	}

	else//спавн дома
	{
		if(PI[playerid][pSpawn] == 2 && PI[playerid][pHouseKey] && GetPVarInt(playerid,"SpecOn") != 1)//проверка выбора спавна и наличия ключей
		{
			if(GetString(HouseInfo[PI[playerid][pHouseKey]-1][hOwner], PN(playerid)))//проверка соответствия имени и
			{
			    new hid = PI[playerid][pHouseKey]-1;
			    HouseEntered[playerid] = hid+1;//отмечает в каком доме находиться чувак и отправляет его туда
				SetSpawnInfoEx(playerid, skin, HouseInfo[hid][hExit_X],HouseInfo[hid][hExit_Y],HouseInfo[hid][hExit_Z],0.0);
				SetPlayerInterior(playerid,HouseInfo[hid][hInt]);
				SetPlayerVirtualWorld(playerid, hid+1+50);
			}
			else
			{
				for(new i;i < 3;i ++)// перебираеться количество комнат
				{
					if(GetString(HRoomOwner[PI[playerid][pHouseKey]-1][i], PN(playerid)))//возвращает комнаты
					{
					    new hid = PI[playerid][pHouseKey]-1;
					    HouseEntered[playerid] = hid+1;
						SetSpawnInfoEx(playerid, skin, HouseInfo[hid][hExit_X],HouseInfo[hid][hExit_Y],HouseInfo[hid][hExit_Z],0.0);
						SetPlayerInterior(playerid,HouseInfo[hid][hInt]);
						SetPlayerVirtualWorld(playerid,hid+1+50);
					}
				}
			}
		}
		else if(PI[playerid][pFraction] && GetPVarInt(playerid,"SpecOn") != 1)
		{
			new fractionid = PI[playerid][pFraction]-1;
			if(PI[playerid][pSubfraction])
			{
				new frid;
				frid = GetSubfractionID(fractionid+1);
				new subid = PI[playerid][pSubfraction] - 1;
				TogglePlayerControllable(playerid, false);
				SetPlayerInterior(playerid, gSubfractionSpawnData[frid][subid][0]);
				SetPlayerVirtualWorld(playerid,gSubfractionSpawnData[frid][subid][1]);
				SetSpawnInfoEx(playerid, skin, gSubfractionSpawnC[frid][subid][0],gSubfractionSpawnC[frid][subid][1],gSubfractionSpawnC[frid][subid][2],gSubfractionSpawnC[frid][subid][3]);
				TogglePlayerControllable(playerid, true);
			}
			else
			{
		        TogglePlayerControllable(playerid, false);
				SetPlayerVirtualWorld(playerid, gFractionSpawnData[fractionid][1]);
				SetPlayerInterior(playerid, gFractionSpawnData[fractionid][0]);
				SetSpawnInfoEx(playerid, skin, gFractionSpawnC[fractionid][0], gFractionSpawnC[fractionid][1], gFractionSpawnC[fractionid][2], gFractionSpawnC[fractionid][3]);
				TogglePlayerControllable(playerid, true);
			}
			SetCameraBehindPlayer(playerid);
		}
		else
		{
  			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			
			if(PI[playerid][pFraction] && !pTemp[playerid][pTempLeader])
				SetPlayerColor(playerid,gFractionColor[PI[playerid][pFraction] - 1]);

		    if(PI[playerid][pLevel] < 3 && GetPVarInt(playerid,"SpecOn") != 1)
		    {
		        switch(random(5))
				{
			    	case 0: SetSpawnInfoEx(playerid, skin, 1756.8386, -1895.6216, 13.5563, 271.9627);
			        case 1: SetSpawnInfoEx(playerid, skin, 1762.1580, -1897.0398, 13.5624, 360.0000);
			        case 2: SetSpawnInfoEx(playerid, skin, 1761.9823, -1893.3030, 13.5606, 181.5132);
			        case 3: SetSpawnInfoEx(playerid, skin, 1772.1035, -1897.9346, 13.5535, 360.0000);
			        case 4: SetSpawnInfoEx(playerid, skin, 1771.9164, -1891.3057, 13.5620, 182.8943);
			        //case 5: SetSpawnInfoEx(playerid, skin,
			    }
			}
			
			else if(PI[playerid][pLevel] > 2  && PI[playerid][pLevel] < 7 && GetPVarInt(playerid,"SpecOn") != 1)
				SetSpawnInfoEx(playerid, skin, -1969.0582, 159.8374, 27.6875, 177.5901);

			else if(PI[playerid][pLevel] > 6 && GetPVarInt(playerid,"SpecOn") != 1)
				SetSpawnInfoEx(playerid, skin, 2846.0134, 1291.2833, 11.3906, 92.5072);
		}
	}

	if(PI[playerid][pFraction])
		SetPlayerColor(playerid,gFractionColor[PI[playerid][pFraction] - 1]);
		
	if(pTemp[playerid][pTempLeader])
	    SetPlayerColor(playerid,0xFFFFFF11);

 	//SetPlayerSkinEx(playerid, GetSkinOfPlayer(playerid));
	if(GetPVarInt(playerid,"SpecOn") == 1)
	{
		new oldint = GetPVarInt(playerid,"oldint"), oldworld = GetPVarInt(playerid,"oldworld"),
		Float: X = GetPVarFloat(playerid,"oldx"),
		Float: Y = GetPVarFloat(playerid,"oldy"),
		Float: Z = GetPVarFloat(playerid,"oldz");
		
		SetPlayerPos(playerid,X,Y,Z);
		SetPlayerInterior(playerid, oldint);
		SetPlayerVirtualWorld(playerid, oldworld);
		DeletePVar(playerid,"SpecOn");
	}
	return true;
}

stock ClearChatForPlayer(playerid)
{
	for(new i; i < 20; i ++)SCM(playerid, -1, " ");
	return true;
}
stock ClearChatToAll()
{
	for(new i; i < 20; i ++) SCMTA(-1, " ");
	return true;
}

stock CheckMiner(playerid)
{
    for(new i; i < sizeof(MinPos); i ++)TogglePlayerDynamicCP(playerid, MinerCP[i], false);
	TogglePlayerDynamicCP(playerid, MinerDownCP, false);
	RemovePlayerAttachedObjectEx(playerid, 7);
    return true;
}
stock CheckPorter(playerid)
{
	TogglePlayerDynamicCP(playerid, PorterDownCP, false);
	RemovePlayerAttachedObjectEx(playerid, 7);
    return true;
}
stock IsNoInvalidKiller(playerid, killerid)
{
    if(killerid != INVALID_PLAYER_ID && killerid != playerid) return true;
    return false;
}
public OnPlayerDeath(playerid, killerid, reason)
{
    if(IsPlayerNPC(playerid))return 1;
    if(IsPlayerLogged[playerid])
    {
        if(IsPlayerSpawned[playerid] == false) return false;
		PI[playerid][pDead] = true;
		if(pTemp[playerid][pPaintTeam] > 0) return PI[playerid][pDead] = false;
		IsPlayerSpawned[playerid] = false;
		if(PI[playerid][pLastGun] > 0)
		{
			PI[playerid][pLastGun]=0;
			PI[playerid][pLastAmmo]=0;
		}
		_ResetGun(playerid);
		pTemp[playerid][pAntiAir] += 5;
  		/*if(pTemp[playerid][pDeathCar] != INVALID_VEHICLE_ID && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		{
	 		pTemp[playerid][pDeathCar] = INVALID_VEHICLE_ID;
    		ExitCar(playerid);
    		new Float:X,Float:Y,Float:Z;
		    GetPlayerPos(playerid,X,Y,Z);
			SetPlayerPos(playerid,X,Y,Z);

		}*/
  		if(temp_pursuit_receiver[playerid] != INVALID_PLAYER_ID && temp_pursuit_sender[killerid] != INVALID_PLAYER_ID)
		{
        	temp_pursuit_receiver[playerid] = INVALID_PLAYER_ID;
    		temp_pursuit_sender[killerid] = INVALID_PLAYER_ID;
   			SendClientMessage(killerid, COLOR_LIGHTBLUE, !"Погоня прервана");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, !"Погоня прервана");
		}
		if(ChangingSkin[playerid])
		{
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
		
        PlayerTextDrawHide(playerid, Spectate[playerid]);
		StopAudioStreamForPlayer(playerid);
		DeletePVar(playerid, "watch_filling");
		DeletePVar(playerid, "watch_business");
		DeletePVar(playerid, "watch_house");

		////
		InJob[playerid]=0;

		/////
		J_SetPlayerHealth(playerid,15);
	 	if(GotoInfo[playerid][gtGoID]!=INVALID_PLAYER_ID)CheckPlayerGoCuff(playerid);
		if(GotoInfo[playerid][gtID] != INVALID_PLAYER_ID)
		{
			new
			    target = GotoInfo[playerid][gtID];

			temp_cuffer_sender[target] = INVALID_PLAYER_ID;
			temp_cuffer_receiver[target] = INVALID_PLAYER_ID;

			f_TogglePlayerControllable(target, true);
			SetPlayerSpecialAction(target, 0);
		    ClearAnims(target);
	     	SendClientMessage(target, 0xFF5030AA, !"Преследование прекращено");
	        CheckPlayerGoCuff(target);
	        CheckPlayerGoCuff(playerid);
		}
		if(temp_cuffer_receiver[playerid] != INVALID_PLAYER_ID)
		{
			new
			    target = temp_cuffer_receiver[playerid]-1;

			if(IsPlayerConnected(target))
			{
				SetPlayerSpecialAction(target, SPECIAL_ACTION_NONE);
				RemovePlayerAttachedObject(target, 0);

				temp_cuffer_sender[target] = INVALID_PLAYER_ID;
				temp_cuffer_receiver[target] = INVALID_PLAYER_ID;

				TogglePlayerControllable(target, 1);
				SendClientMessage(target, 0xFF5030AA, !"Наручники сняты");
			}
		}
		if(temp_tie_receiver[playerid] != INVALID_PLAYER_ID)
		{
			new
			    target = temp_tie_receiver[playerid]-1;

			if(IsPlayerConnected(target))
			{
				temp_tie_sender[target] = INVALID_PLAYER_ID;
				temp_tie_receiver[playerid] = INVALID_PLAYER_ID;

				f_TogglePlayerControllable(target, true);
				SendClientMessage(target, 0xFF5030AA, !"Веревка снята");
			}
		}
		if(temp_cuffer_sender[playerid] != INVALID_PLAYER_ID || GotoInfo[playerid][gtGoID] != INVALID_PLAYER_ID)
		{
		    new
				time = PI[playerid][pWanted] * 300 + 1800,
				cufferid = temp_cuffer_sender[playerid]-1;

	        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	        RemovePlayerAttachedObject(playerid, 0);
	        temp_cuffer_sender[playerid] = INVALID_PLAYER_ID;
	        temp_cuffer_receiver[cufferid] = INVALID_PLAYER_ID;

		    PI[playerid][pJailTime] = time;
		    PI[playerid][pWanted] = 0;
		    SetPlayerWantedLevel(playerid, 0);
		    ResetPlayerWeapons(playerid);

	        PI[playerid][pPrison] = RandomEx(1,3);
	        
	        PI[playerid][pJailAdmin] = 0;

		    new
				query[200];

		    format(query, sizeof query, "UPDATE `accounts` SET `JailTime` = '%d', `Prison` = '%d', `Wanted` = '0', `JailAdmin` = '0' WHERE `ID` = '%d'", PI[playerid][pJailTime], PI[playerid][pPrison], PI[playerid][pID]);
		    mysql_tquery(mysql, query);

		}

	    gunmute[playerid] = gettime()+5;


		for(new i; i < 13; i++)
			TextDrawHideForPlayer(playerid, select_skin[i]);

		if(!PI[playerid][pJailTime])
		{
			if(IsPlayerToKvadrat(playerid,-891.3302,-2950.0190,2915.9917,560.3257)) PI[playerid][pCheepses]=1;
			else if(IsPlayerToKvadrat(playerid,-2929.6589,-2889.1660,-1326.9077,1493.1770)) PI[playerid][pCheepses]=3;
			else PI[playerid][pCheepses]=2;
		    PI[playerid][pHeal] = 1;
		    PI[playerid][pHealTime] = 0;
		    f_TogglePlayerControllable(playerid,true);
		}
 		if(temp_table[playerid] != -1)
  		{
	   		new table = temp_table[playerid];

			gTable[table][tCrup] = INVALID_PLAYER_ID;
	  		temp_table[playerid] = -1;
		}

		if(pTemp[playerid][pMechID] != INVALID_VEHICLE_ID) MechSpawnEx(playerid);
		if(pTemp[playerid][pProductID] != INVALID_VEHICLE_ID) ProductSpawnEx(playerid);
		if(killerid != INVALID_PLAYER_ID)
		{
			new
				gang_killer,
				gang_kill;

			gang_killer = PI[killerid][pFraction];
			gang_kill = PI[playerid][pFraction];

			if(gang_killer != gang_kill)
			{
				if(GangInfo[gang_killer][gCapture] && GangInfo[gang_kill][gCapture] == 1)
				{
					for(new i; i < MAX_GANGZONE; i++)
					{
						if(PlayerToKvadrat(killerid, GZMZ[i][gCoords][0], GZMZ[i][gCoords][1], GZMZ[i][gCoords][2], GZMZ[i][gCoords][3]))
						{
							if(GangInfo[gang_killer][gCaptureID] == GangInfo[gang_kill][gCaptureID])
							{
								for(new p = 0, j = GetPlayerPoolSize(); p <= j; p++)
							        if (IsPlayerConnected(p) && !PI[p][pKillList])
							    		SendDeathMessageToPlayer(p, killerid, playerid, reason);

								GangInfo[gang_killer][gScore] = GangInfo[gang_killer][gScore]+1;
        						CaptureUpdate(gang_killer);
							}
						}
					}
				}
			}
		    if(IsAMafia(killerid) && IsBizWar == 2)
			{
			    if(IsPlayerInDynamicArea(killerid, gBizWarArea))
			    {
				    if(gang_killer != gang_kill && gang_killer == gNapadMafia && IsBizWar == 2) gBizWarScore[0] += 1;
				    else if(gang_killer != gang_kill && gang_killer != gNapadMafia && IsBizWar == 2) gBizWarScore[1] += 1;
				    for(new p = 0, j = GetPlayerPoolSize(); p <= j; p++)
			        {
			            if(IsPlayerConnected(p) && !PI[p][pKillList])
				        	if(IsAMafia(p))
				            	SendDeathMessageToPlayer(p, killerid, playerid, reason);
			    	}
			    	BizWarUpdate(gang_killer);
		    	}
			}
			
		}
	    if(killerid != INVALID_PLAYER_ID && !IsACop(killerid) && !IsAMafia(killerid) && !IsAGang(killerid) && PI[killerid][pFraction] != 7 && !pTemp[killerid][pPaintTeam])
		{
			if(!PI[killerid][pWanted])
				PI[killerid][pWanted] = 2;
				
			else if(PI[killerid][pWanted] < 6)
				PI[killerid][pWanted] += 2;
				
			UpdatePlayerData(killerid, "Wanted", PI[killerid][pWanted]);
	        SetPlayerWantedLevel(killerid, PI[killerid][pWanted]);
	        
			new
			    fmrt_wanted_message[180];

			format(fmrt_wanted_message, sizeof fmrt_wanted_message, "Вы объявлены в розыск (+2). Причина: убийство. ((%d))", playerid);
	        SendClientMessage(killerid, 0xFF9900AA, fmrt_wanted_message);

			format(fmrt_wanted_message, sizeof fmrt_wanted_message, "[Внимание] %s объявлен в розыск (+2). Причина: Убийство.", PN(killerid));
			CopMes(0x007FFFFF, fmrt_wanted_message);
		}
		
	    if(killerid != INVALID_PLAYER_ID && !IsACop(killerid) && PI[killerid][pFraction] != 7 && !pTemp[killerid][pPaintTeam] && !IsPlayerInRangeOfPoint(killerid,200.0,368.5594,173.7236,1008.3893))
	    {
			PI[killerid][pZKP] -= 2;
			UpdatePlayerData(killerid, "ZKP", PI[killerid][pZKP]);
		}
		if(killerid != INVALID_PLAYER_ID && IsACop(killerid) && PI[playerid][pWanted] && !pTemp[killerid][pPaintTeam])
		{
			new
				fractionid = PI[killerid][pFraction]-1,
				rank = PI[killerid][pRank],
				fmrt_wanted_message[128];
				
			format(fmrt_wanted_message, sizeof fmrt_wanted_message, "Подозреваемый {FFFFFF}%s {269BD8}отправлен в КПЗ", PN(playerid));
			SendClientMessage(killerid, 0x269BD8FF, fmrt_wanted_message);
			
			format(fmrt_wanted_message, sizeof fmrt_wanted_message, "[Внимание] %s %s поймал преступника '%s'", gFractionRankName[fractionid][rank-1], PN(killerid), PN(playerid));
	  		CopMes(0x007FFFFF, fmrt_wanted_message);

			PI[playerid][pJailTime] = PI[playerid][pWanted] * 300;
			PI[playerid][pWanted] = 0;
			PI[playerid][pPrison] = RandomEx(1,3);
			PI[playerid][pJailAdmin] = 0;
			UpdatePlayerData(playerid, "Wanted", PI[playerid][pWanted]);
			UpdatePlayerData(playerid, "JailTime", PI[playerid][pJailTime]);
			UpdatePlayerData(playerid, "Prison", PI[playerid][pPrison]);
			UpdatePlayerData(playerid, "JailAdmin", PI[playerid][pJailAdmin]);


			SetPlayerWantedLevel(playerid, 0);
		}
		
		pTemp[playerid][pTakeShot] = 0;
		pTemp[playerid][pTakeDmg] = 0;
		pTemp[playerid][pAllDmg] = 0.0;
		pTemp[playerid][pCarDmg] = 0;
		if(PI[playerid][pJob] == JOB_MECHANIC && pTemp[playerid][pMechID] != INVALID_VEHICLE_ID)
		{
			SetVehicleToRespawn(pTemp[playerid][pMechID]);
			pTemp[playerid][pMechID] = INVALID_VEHICLE_ID;
			SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Рабочее т/с было отбуксировано");
			if(IsValidDynamic3DTextLabel(pTemp[playerid][pMechText]))
			{
				DestroyDynamic3DTextLabel(pTemp[playerid][pMechText]);
				pTemp[playerid][pMechText] = Text3D:INVALID_3DTEXT_ID;
			}
			pTemp[playerid][pMechFuel] = 0;
		}
		if(GetPVarInt(playerid, "ProductID") > 0)
		{
	 		ProductInfo[GetPVarInt(playerid, "ProductID")][pStatus] = 0;
			DeletePVar(playerid, "ProductLoad");
			DeletePVar(playerid, "ProductInfo");
			SetVehicleToRespawn(GetPVarInt(playerid, "CarProduct"));
			if(GetPVarInt(playerid, "PRODVEH") != 0)
			{
				DestroyVehicleEx(GetPVarInt(playerid, "PRODVEH"));
				SetPVarInt(playerid, "PRODVEH", 0);
			}
			DeletePVar(playerid, "ProductID");
			DisablePlayerRaceCheckpoint(playerid);

			if(IsValidDynamic3DTextLabel(JobText3D[playerid]))
				DestroyDynamic3DTextLabel(JobText3D[playerid]);
	        pTemp[playerid][pProductID] = INVALID_VEHICLE_ID;
	        DeletePVar(playerid, "CarProduct");
		}
	}
	return true;
}
stock IsABoat(carid)
{
	return (GetVehicleType(GetVehicleModel(carid)) == VEHICLE_TYPE_BOAT);
}

stock IsAPlane(carid)
{
	return (GetVehicleType(GetVehicleModel(carid)) == VEHICLE_TYPE_PLANE);
}
stock IsABike(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 510,509,481: return true;
	}
	return false;
}
stock IsAMoped(carid)
{
	return (GetVehicleType(GetVehicleModel(carid)) == VEHICLE_TYPE_TWOWEELS);
}
stock IsACar(carid)
{
	return (GetVehicleType(GetVehicleModel(carid)) == VEHICLE_TYPE_CAR);
}
public OnVehicleSpawn(vehicleid)
{
	GetVehiclePos(vehicleid, VehicleInfo[vehicleid][vX], VehicleInfo[vehicleid][vY], VehicleInfo[vehicleid][vZ]);
	GetVehicleZAngle(vehicleid, VehicleInfo[vehicleid][vA]);
	VehicleInfo[vehicleid][vFuel] = 40;

	/*if(vehicleid >= vProduct[0] && vehicleid <= vProduct[1])
	{
		foreach(new i:Player)
		{
			if(IsPlayerLogged[i]== false || GetPVarInt(i, "PRODVEH") != vehicleid) continue;
			Delete3DTextLabel(JobText3D[GetPVarInt(i, "CarProduct")]);
			DeletePVar(i, "PRODVEH");
			DeletePVar(i, "ProductLoad");
			ProductInfo[GetPVarInt(i, "ProductID")][pStatus] = false;
			DeletePVar(i, "ProductID");
			DeletePVar(i, "ProductJob");
		}
		DestroyVehicle(vehicleid);
	}*/
	if(vehicleid >= vBus[0] && vehicleid <= vBus[1])
	{
		if(ToggleLock(vehicleid)) ToggleLock(vehicleid);
		VehicleInfo[vehicleid][vFuel] = 40;
		VehicleInfo[vehicleid][vBusOwner] = INVALID_PLAYER_ID;

	}
	if(vehicleid >= vTaxi[0] && vehicleid <= vTaxi[1])
	{
		if(ToggleLock(vehicleid)) ToggleLock(vehicleid);
		VehicleInfo[vehicleid][vFuel] = 40;
   		foreach(new i : Player)
		{
			if(pTemp[i][pTaxiID] != vehicleid)
			    continue;

			if(IsValidDynamic3DTextLabel(pTemp[i][pTaxi3DText]))
				DestroyDynamic3DTextLabel(pTemp[i][pTaxi3DText]);

			pTemp[i][pTaxiID] = INVALID_VEHICLE_ID;
			pTemp[i][pTaxiPrice] = 0;
			pTemp[i][pTaxiTurn][0] = INVALID_PLAYER_ID;
			pTemp[i][pTaxiTurn][1] = INVALID_PLAYER_ID;
			pTemp[i][pTaxi3DText] = NONE_3D_TEXT;
			pTemp[i][pTaxiSelect] = false;
			pTemp[i][pTaxiDriver] = INVALID_PLAYER_ID;
			pTemp[i][pTaxiPass] = INVALID_PLAYER_ID;
			pTemp[i][pTaxiGoing] = false;
			pTemp[i][pTaxiStart] = 0.0;
			pTemp[i][pTaxiTotal] = 0;
			SendClientMessage(i, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Рабочее т/с было отбуксировано.");
			break;
		}
	}
	if(vehicleid >= vTruck[0][0] && vehicleid <= vTruck[2][1])
	{
		if(ToggleLock(vehicleid)) ToggleLock(vehicleid);
		VehicleInfo[vehicleid][vFuel] = 40;
		VehicleInfo[vehicleid][vTruckOwner] = INVALID_PLAYER_ID;
   		foreach(new i: Player)
		{
			if(pTemp[i][pTruckID] == vehicleid)
			{
				pTemp[i][pTruckID] = INVALID_VEHICLE_ID;
				if(IsValidDynamic3DTextLabel(pTemp[i][pTruckWagonText]))
				{
					DestroyDynamic3DTextLabel(pTemp[i][pTruckWagonText]);
					pTemp[i][pTruckWagonText] = Text3D:INVALID_3DTEXT_ID;
				}
				if(pTemp[i][pTruckWagonID] != INVALID_VEHICLE_ID)
				{
					DestroyVehicle(pTemp[i][pTruckWagonID]);
					pTemp[i][pTruckWagonID] = INVALID_VEHICLE_ID;
				}
				for(new j;j<10;j++)
				{
					if(gTruckLoadTurn[0][j] == i) gTruckLoadTurn[0][j] = INVALID_PLAYER_ID;
					if(gTruckLoadTurn[1][j] == i) gTruckLoadTurn[1][j] = INVALID_PLAYER_ID;
					if(gTruckLoadTurn[2][j] == i) gTruckLoadTurn[3][j] = INVALID_PLAYER_ID;
					if(gTruckLoadTurn[3][j] == i) gTruckLoadTurn[3][j] = INVALID_PLAYER_ID;
				}
			}
		}
	}
	/*if((GetVehicleModel(vehicleid)==426 && VehicleInfo[vehicleid][vTeam]==TEAM_LICENSERS) || GetVehicleModel(vehicleid)==538)DestroyDynamicObject(avtock[vehicleid]);
	if(GetVehicleModel(vehicleid)==426 && VehicleInfo[vehicleid][vTeam]==TEAM_LICENSERS)
	{
		avtock[vehicleid] = CreateDynamicObject(19309,0.0, 0.0, 0, 0.0, 0.0, 0.0, -1,  -1, -1,100.0);
		SetDynamicObjectMaterialText(avtock[vehicleid], 0, "Учебная",50, "Tahoma", 27, 1, -1, -65536, 1);
		AttachDynamicObjectToVehicle(avtock[vehicleid], vehicleid, 0.0, -0.5, 0.9, 0.0, 0.0, 0.0);
	}*/

	if(VehicleInfo[vehicleid][vTeam])
	{
	    for(new i; i < gFractionCarCount[VehicleInfo[vehicleid][vTeam]-1]; i++)
	    {
	        if(gFractionCar[VehicleInfo[vehicleid][vTeam]-1][i] == GetVehicleModel(vehicleid))
        		VehicleInfo[vehicleid][vRank] = OrgInfo[VehicleInfo[vehicleid][vTeam]-1][oCarRanks][i];
        	
		}
	}

	if(VehicleInfo[vehicleid][vTeam] == 7)
	{
		if(VehicleLoad[vehicleid][vlID] == vehicleid)
		{
			if(IsValidDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]);

			DestroyDynamicArea(VehicleLoad[vehicleid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[vehicleid][vlPickup]);

		    VehicleLoad[vehicleid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[vehicleid][vlLoading] = false;
			VehicleLoad[vehicleid][vlUnloading] = false;
			VehicleLoad[vehicleid][vlRob] = false;
			VehicleLoad[vehicleid][vlLimit] = 0;
			VehicleLoad[vehicleid][vlLoadFr] = -1;
			VehicleLoad[vehicleid][vlLoadSf] = -1;
			VehicleLoad[vehicleid][vlPickup] = -1;
			VehicleLoad[vehicleid][vlArea] = -1;
			VehicleLoad[vehicleid][vlText] = NONE_3D_TEXT;
		}
	}
	
	if(VehicleInfo[vehicleid][vTeam] == 11 || VehicleInfo[vehicleid][vTeam] == 12 || VehicleInfo[vehicleid][vTeam] == 13)
	{
		if(VehicleLoad[vehicleid][vlID] == vehicleid)
		{
			if(IsValidDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]);

			DestroyDynamicArea(VehicleLoad[vehicleid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[vehicleid][vlPickup]);

		    VehicleLoad[vehicleid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[vehicleid][vlMafLoading] = false;
			VehicleLoad[vehicleid][vlMafUnloading] = false;
			VehicleLoad[vehicleid][vlLimit] = 0;
			VehicleLoad[vehicleid][vlPickup] = -1;
			VehicleLoad[vehicleid][vlArea] = -1;
			VehicleLoad[vehicleid][vlText] = NONE_3D_TEXT;
		}
	}
	for(new i; i < sizeof CarInfo; i ++)
	{
		if(CarInfo[i][cVehID] != vehicleid)
			continue;

		for(new tn; tn < 14; tn++)
			if(CarInfo[i][cTuning][tn] != 0) AddVehicleComponent(CarInfo[i][cVehID], CarInfo[i][cTuning][tn]);

		ChangeVehicleColor(CarInfo[i][cVehID], CarInfo[i][cColor_1], CarInfo[i][cColor_2]);
		ToggleLock(CarInfo[i][cVehID]);

		ChangeVehiclePaintjob(CarInfo[i][cVehID], CarInfo[i][cPaintJob]);
		
		CarInfo[i][cVehID] = vehicleid;
		break;
	}

	VehicleInfo[vehicleid][vPlayer]=-1;

	if(IsAPlane(vehicleid)) J_SetVehicleHealth(vehicleid,3000);
	else J_SetVehicleHealth(vehicleid,1000);


	if((VehicleInfo[vehicleid][vTeam] >=1 && VehicleInfo[vehicleid][vTeam]<11) || VehicleInfo[vehicleid][vTeam]>19) VehicleInfo[vehicleid][vFuel] = 40.0;


	return true;
}
public OnVehicleDeath(vehicleid, killerid)
{
	if(vehicleid >= vBus[0] && vehicleid <= vBus[1])
	{
		if(ToggleLock(vehicleid)) ToggleLock(vehicleid);
		VehicleInfo[vehicleid][vFuel] = 40;
        if(VehicleInfo[vehicleid][vBusOwner] != INVALID_PLAYER_ID)
			BusSpawnEx(vehicleid);

	}
	if(vehicleid >= vTruck[0][0] && vehicleid <= vTruck[2][1])
	{
	    new player = VehicleInfo[vehicleid][vTruckOwner];
		if(player != INVALID_PLAYER_ID)
		{
			SendClientMessage(player,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Трак уничтожен. Вам было возвращено 20% от стоимости груза.");
			new back = pTemp[player][pTruckWeight]/100*80*2;
			GiveMoney(player,back,"Возврат за уничтоженый трак");
			if(pTemp[player][pTruckWagonID] != INVALID_VEHICLE_ID)
			{
				if(IsValidDynamic3DTextLabel(pTemp[player][pTruckWagonText]))
				{
					DestroyDynamic3DTextLabel(pTemp[player][pTruckWagonText]);
					pTemp[player][pTruckWagonText] = Text3D:INVALID_3DTEXT_ID;
				}
				DestroyVehicle(pTemp[player][pTruckWagonID]);
				pTemp[player][pTruckWagonID] = INVALID_VEHICLE_ID;
				pTemp[player][pTruckWagonTime] = 0;
				VehicleInfo[vehicleid][vTruckOwner] = INVALID_VEHICLE_ID;
				pTemp[player][pTruckWeight] = 0;
				pTemp[player][pTruckLoadID] = 0;
				SetPVarInt(player,"informed",0);
				DeletePVar(player,"mesto");
				SetPVarInt(player,"truckonroad",0);
			}
			pTemp[player][pTruckID] = INVALID_VEHICLE_ID;
		}
	}
	if(VehicleInfo[vehicleid][vTeam] == 7)
	{
		if(VehicleLoad[vehicleid][vlID] == vehicleid)
		{
			if(IsValidDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]);

			DestroyDynamicArea(VehicleLoad[vehicleid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[vehicleid][vlPickup]);

		    VehicleLoad[vehicleid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[vehicleid][vlLoading] = false;
			VehicleLoad[vehicleid][vlUnloading] = false;
			VehicleLoad[vehicleid][vlLimit] = 0;
			VehicleLoad[vehicleid][vlPickup] = -1;
			VehicleLoad[vehicleid][vlArea] = -1;
			VehicleLoad[vehicleid][vlLoadFr] = -1;
			VehicleLoad[vehicleid][vlLoadSf] = -1;
			VehicleLoad[vehicleid][vlText] = NONE_3D_TEXT;
		}
	}
	if(VehicleInfo[vehicleid][vTeam] == 11 || VehicleInfo[vehicleid][vTeam] == 12 || VehicleInfo[vehicleid][vTeam] == 13)
	{
		if(VehicleLoad[vehicleid][vlID] == vehicleid)
		{
			if(IsValidDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[vehicleid][vlText]);

			DestroyDynamicArea(VehicleLoad[vehicleid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[vehicleid][vlPickup]);

		    VehicleLoad[vehicleid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[vehicleid][vlMafLoading] = false;
			VehicleLoad[vehicleid][vlMafUnloading] = false;
			VehicleLoad[vehicleid][vlLimit] = 0;
			VehicleLoad[vehicleid][vlPickup] = -1;
			VehicleLoad[vehicleid][vlArea] = -1;
			VehicleLoad[vehicleid][vlText] = NONE_3D_TEXT;
		}
	}

	new get_rent = GetArendCarID(vehicleid);
	if(get_rent != INVALID_VEHICLE_ID && get_rent != (-1))
	{
		if(ToggleLock(vehicleid)) ToggleLock(vehicleid);
		new playerid = ArendInfo[get_rent][aPlayerID];
		ArendInfo[get_rent][aPlayerID] = INVALID_PLAYER_ID;
		if(IsPlayerConnected(playerid) && pTemp[playerid][pArendKey] == get_rent)
		{
			SendClientMessage(playerid, COLOR_GREY, !"Транспорт, который вы арендовали, был уничтожен. Аренда закончилась");
			pTemp[playerid][pArendKey] = INVALID_VEHICLE_ID;
		}
	}
	return true;
}
stock DestroyVehicleEx(vehicleid)
{
	DestroyVehicle(vehicleid);
	return true;
}
stock AudioMessage(playerid, text[], lang5[] = "ru", bool: Usepos)
{
	new str[256],Float:p[3];
	if(Usepos) GetPlayerPos(playerid,p[0],p[1],p[2]);
	format(str, 256, "http://translate.google.kg/translate_tts?ie=UTF-8&q=%s&tl=%s&prev=input", text, lang5);
	PlayAudioStreamForPlayer(playerid, str, p[0],p[1],p[2], 50.0, Usepos);
	return true;
}
public OnPlayerText(playerid, text[])
{
	new string[150];
	if(IsPlayerLogged[playerid] )
	{
		if(PI[playerid][pAdmin] > 0 && !ADuty[playerid])
		{
			ShowPlayerDialogEx(playerid, 211, 1, !"{74FFA0}Авторизация", !"{FFFFFF}Введите админ-пароль:", !"ОК", !"Отмена");
			return 0;
		}
	   	if(pTemp[playerid][pFlood] > gettime()) return !SCM(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {ffffff}Не флудите");

	    if(PI[playerid][pMuteTime] > 0)
		{
 			SetPlayerChatBubble(playerid, "пытается что-то сказать", COLOR_RED, 10.0, 5000);
   			SendMuteMessage(playerid, 0);
			return false;
		}
		if(PI[playerid][pSpectating]) return false;
		    
		pTemp[playerid][pFlood] = 1;

		if(strlen(text) > 100)
		    return !SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Слишком длинный текст");

		for(new i; i < sizeof gNewsDialee; i++)
		{
			if(gNewsDialee[i] == playerid && gNewsDialing[i])
			{
				new
					frmt_dial_message[128],
					subid = PI[gNewsDialer[i]][pSubfraction];
					
				format(frmt_dial_message, sizeof frmt_dial_message, "[Radio] %s [тел.]: %s", PN(playerid), text);
				for(new r = 0, j = GetPlayerPoolSize(); r <= j; r++)
				{
					if(PI[r][pRadio] == subid || r == playerid)
						SendClientMessage(r, 0x6B8E23FF, frmt_dial_message);
			    }
			    return false;
			}
		}
		if(temp_call[playerid])
		{
			new
				id;
				
			if(gCalls[playerid][gCaller] == playerid)
				id = gCalls[playerid][gCallee];
				
			else if(gCalls[playerid][gCallee] == playerid)
				id = gCalls[playerid][gCaller];

			else
				return SendClientMessage(playerid, COLOR_GREY, !"Ошибка (#112)");
			
			new mes[19 + 128 + MAX_PLAYER_NAME];
			new mesid[19 + 128 + MAX_PLAYER_NAME + 4];
		    if(PI[playerid][pFraction] > 0 && !pTemp[playerid][pDisguse])
		    {
				format(mes,sizeof(mes),"- [Телефон] %s {%s}(%s)",text,GetColor(playerid),cPN(playerid));
				format(mesid,sizeof(mesid),"- [Телефон] %s {%s}(%s) [%d]",text,GetColor(playerid),cPN(playerid),playerid);
			}
			else if(PI[playerid][pFraction] == 11 && pTemp[playerid][pDisguse] != 15)
			{
				format(mes,sizeof(mes),"- [Телефон] %s {%s}(%s)",text,GetDisguseColor(playerid),cPN(playerid));
				format(mesid,sizeof(mesid),"- [Телефон] %s {%s}(%s) [%d]",text,GetDisguseColor(playerid),cPN(playerid),playerid);
			}
			else
			{
			    format(mes,sizeof(mes),"- [Телефон] %s (%s)",text,cPN(playerid));
				format(mesid,sizeof(mesid),"- [Телефон] %s (%s) [%d]",text,cPN(playerid),playerid);
			}

    		foreach(new i : Player)
			{
				if(IsPlayerConnected(i) && PI[i][pID])
				{
					new color = 1, c, Float:rdist;
					rdist = GetPlayerDistanceToPlayer(playerid,i);
					if (rdist > 13.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(i)) continue;
					if(color)
					{
						switch(floatround(rdist))
						{
							case 0..4: c = 0xFFFFFFFF;
							case 5..8: c = 0xCCCCCCFF;
							case 9..14: c = 0xAAAAAAFF;
							default: c = 0x888888FF;
						}
					}
					else c = COLOR_WHITE;

					SendClientMessage(i,c,mesid);
				}
			}

			SetPlayerChatBubble(playerid, text, COLOR_WHITE, 20.0, 10000);
		
			format(mes,sizeof(mes),"[T] %s: %s", PN(playerid), text);
			SendClientMessage(id, COLOR_YELLOW, mes);
			
			return false;
		}

		if(GetString(text,")"))
		{
		    format(string,sizeof(string),"%s улыбается",cPN(playerid));
			ProxDetector(25,playerid,string,COLOR_ME);
			return false;
		}
		if(GetString(text,"))"))
		{
		    format(string,sizeof(string),"%s смеется",cPN(playerid));
			ProxDetector(25,playerid,string,COLOR_ME);
			return false;
		}
		if(GetString(text,"("))
		{
		    format(string,sizeof(string),"%s грустит",cPN(playerid));
			ProxDetector(25,playerid,string,COLOR_ME);
			return false;
		}
		if(GetString(text,"(("))
		{
		    if(PI[playerid][pSex] == 1)
				format(string,sizeof(string),"%s сильно расстроился",cPN(playerid));
				
		    else if(PI[playerid][pSex] == 2)
				format(string,sizeof(string),"%s сильно расстроилась",cPN(playerid));
				
			ProxDetector(25,playerid,string,COLOR_ME);
			return false;
		}

		/*if(IsAMg(text))
	    {
	        format(string,sizeof(string),"%s[%d] говорит: (( {AFAFAF}%s{FFFFFF} ))",cPN(playerid),playerid,text);
			ProxDetector(10,playerid,string,COLOR_WHITE,1);
			return false;
	    }*/
	    
		new mes[9 + 128 + MAX_PLAYER_NAME];
		new mesid[9 + 128 + MAX_PLAYER_NAME + 4];
	    if(PI[playerid][pFraction] > 0 && !pTemp[playerid][pDisguse])
	    {
			format(mes,sizeof(mes),"- %s {%s}(%s)",text,GetColor(playerid),cPN(playerid));
			format(mesid,sizeof(mesid),"- %s {%s}(%s) [%d]",text,GetColor(playerid),cPN(playerid),playerid);
		}
		else if(PI[playerid][pFraction] == 11 && pTemp[playerid][pDisguse] != 15)
		{
			format(mes,sizeof(mes),"- %s {%s}(%s)",text,GetDisguseColor(playerid),cPN(playerid));
			format(mesid,sizeof(mesid),"- %s {%s}(%s) [%d]",text,GetDisguseColor(playerid),cPN(playerid),playerid);
		}
		else
		{
		    format(mes,sizeof(mes),"- %s (%s)",text,cPN(playerid));
			format(mesid,sizeof(mesid),"- %s (%s) [%d]",text,cPN(playerid),playerid);
		}
		
		
   		foreach(new i : Player)
		{
			if(IsPlayerConnected(i) && PI[i][pID] )
			{
				new color = 1, c, Float:rdist;
				rdist = GetPlayerDistanceToPlayer(playerid,i);
				if (rdist > 13.0 || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(i)) continue;
				if(color)
				{
					switch(floatround(rdist))
					{
						case 0..4: c = 0xFFFFFFFF;
						case 5..8: c = 0xCCCCCCFF;
						case 9..14: c = 0xAAAAAAFF;
						default: c = 0x888888FF;
					}
				}
				else c = COLOR_WHITE;
				
				SendClientMessage(i,c,mesid);
			}
		}
		
		if(GetPVarInt(playerid,"narko") < gettime() && GetPVarInt(playerid,"mask") < gettime() && GetPVarInt(playerid,"healme") < gettime() && GetPVarInt(playerid,"trash") < gettime() && GetPVarInt(playerid,"repair") < gettime() && temp_tie_sender[playerid] == INVALID_PLAYER_ID && GetPVarInt(playerid,"anim_antidm") < gettime() && GetPVarInt(playerid,"UseAnim") != 1 && GetPVarInt(playerid,"Animation") != 1)
		{
			ApplyAnimation(playerid,"PED","IDLE_CHAT",8.1,0,1,1,1,1);
			SetTimerEx("ClearAnim",100*strlen(text), false, "d", playerid);
		}

		SetPlayerChatBubble(playerid, text, COLOR_WHITE, 20.0, 10000);
	}
	return false;
}
forward ClearAnim(playerid);
public ClearAnim(playerid) return ApplyAnimation(playerid, "CARRY", "crry_prtial",4.0,0,0,0,0,0,1);
public J_ApplyAnimation(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync)
{
    ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
    return true;
}
stock CheckColor(color)
{
	new str[8];
	format(str,8,"%06x",color >>> 8);
	return str;
}
stock GetTeamColor(team)
{
    new str[8];
	format(str, 8, "%06x", gFunctionColorFract[team] >>> 8);
	return str;
}
stock GetColor(playerid)
{
    new str[8];
	format(str, 8, "%06x", gFunctionColorFract[PI[playerid][pFraction] - 1] >>> 8);
	return str;
}
stock GetDisguseColor(playerid)
{
    new str[8];
	format(str, 8, "%06x", gFunctionColorFract[pTemp[playerid][pDisguse] - 1] >>> 8);
	return str;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!Controllable[playerid]) return ClearAnimations(playerid);
	if(GetVehicleModel(vehicleid)==538 ) ExitCar(playerid);
    if(temp_cuffer_sender[playerid] != INVALID_PLAYER_ID)
    {
		SendClientMessage(playerid, COLOR_GREY, !"Вы не можете сесть в т/с в наручниках");
		RemovePlayerFromVehicle(playerid);
		ClearAnimations(playerid);
		return 1;
	}
	if(GetVehicleModel(vehicleid)!=570 && GetVehicleModel(vehicleid)!=449)
	{
		new Float:x,Float:y,Float:z;
		GetVehiclePos(vehicleid,x,y,z);
		if(!IsPlayerInRangeOfPoint(playerid,20,x,y,z) && VehicleSpeed(vehicleid)<50) return ToCheat(0,playerid);
	}
	VehicleID[playerid]=vehicleid;
	if(!ispassenger)
	{
	    AntiCheatOFF[playerid][VEH_ROOT_HACK] = 2;
	    CheckEnterCar(playerid, vehicleid);
	}
	if(InJob[playerid] == 5 || InJob[playerid] == 6 || InJob[playerid] == 7)
	{
		SendClientMessage(playerid, COLOR_GREY, "Вы не можете сесть в Т/С, работая");
		RemovePlayerFromVehicle(playerid);
		HideCarInfo(playerid);
		ClearAnimations(playerid);
		return 1;
	}
	if(vehicleid >= vBus[0] && vehicleid <= vBus[1])
	{
		new driverid = GetVehicleSeat(vehicleid,0);
		if(IsPlayerConnected(driverid))
		{
			if(temp_bus_id[driverid] == vehicleid)
			{
				if(ispassenger) SetVehicleParamsForPlayer(vehicleid,playerid,0,0);
				else if(playerid != driverid) SetVehicleParamsForPlayer(vehicleid,playerid,0,1);
				else if(playerid == driverid) SetVehicleParamsForPlayer(vehicleid,playerid,0,0);
			}
		}
	}
	return true;
}
public OnPlayerExitVehicle(playerid, vehicleid)
{
    VehicleID[playerid]=INVALID_VEHICLE_ID;
	if(temp_fill_sender[playerid] != INVALID_PLAYER_ID)
	{
		new scdplayerid = temp_fill_sender[playerid];
		DeletePVar(playerid, "MechanicPrice");
		DeletePVar(playerid, "MechanicFuel");
		SendClientMessage(scdplayerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Игрок отказался от заправки т/с");
		SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы отказались от заправки т/с");
		temp_fill_sender[playerid] = INVALID_PLAYER_ID;
	}
	if(temp_repair_sender[playerid] != INVALID_PLAYER_ID)
	{
		new scdplayerid = temp_fill_sender[playerid];
		DeletePVar(playerid, "MechanicPrice");
		DeletePVar(playerid, "MechanicRepair");
		SendClientMessage(scdplayerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Игрок отказался от починки т/с");
		SendClientMessage(playerid,COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Вы отказались от починки т/с");
		temp_repair_sender[playerid] = INVALID_PLAYER_ID;
	}
	if(PI[playerid][pCarInfoTimer] != 0)
	{
		HideCarInfo(playerid);
		KillTimer(PI[playerid][pCarInfoTimer]);
		PI[playerid][pCarInfoTimer] = 0;
	}
	if(PI[playerid][pJob] == 1 && temp_bus_id[playerid] != INVALID_VEHICLE_ID && GetVehicleModel(temp_bus_id[playerid]) == 437 && GetPVarInt(playerid,"TesteR") != 1)
	{
		DisablePlayerRaceCheckpoint(playerid);
		SendClientMessage(playerid, COLOR_RED, !"У Вас есть 2 минуты, чтобы вернуться в автобус");
		SetPVarInt(playerid,"TesteR",1);
		temp_bus_spawn_timer[playerid] = SetTimerEx("@__BusSpawn",120000, false, "i", playerid);
	}
	if(PI[playerid][pJob] == JOB_TRUCKER && pTemp[playerid][pTruckID] != INVALID_VEHICLE_ID && GetPVarInt(playerid,"exitedtrans") != 1)
	{
		DisablePlayerRaceCheckpoint(playerid);
		SendClientMessage(playerid, COLOR_RED, !"У Вас есть 30 секунд, чтобы вернуться в грузовик");
		pTemp[playerid][pTruckSpawnTimer] = SetTimerEx("@TruckerSpawn",30000,false,"i",playerid);
		SetPVarInt(playerid,"exitedtrans",1);
	}
	if(PI[playerid][pJob] == JOB_MECHANIC && pTemp[playerid][pMechID] != INVALID_VEHICLE_ID && GetPVarInt(playerid,"exitveh") != 1)
	{
		DisablePlayerRaceCheckpoint(playerid);
		SendClientMessage(playerid, COLOR_RED, !"У Вас есть 30 секунд, чтобы вернуться в эвакуатор");
		pTemp[playerid][pMechSpawn] = SetTimerEx("@MechSpawn",30000,false,"i",playerid);
		SetPVarInt(playerid,"exitveh",1);
	}
	if(PI[playerid][pJob] == JOB_PRODUCT && pTemp[playerid][pProductID] != INVALID_VEHICLE_ID && GetPVarInt(playerid,"exitcar") != 1)
	{
		DisablePlayerRaceCheckpoint(playerid);
		SendClientMessage(playerid, COLOR_RED, !"У Вас есть 30 секунд, чтобы вернуться в т/с");
		pTemp[playerid][pProductSpawn] = SetTimerEx("@ProductSpawn",30000,false,"i",playerid);
		SetPVarInt(playerid,"exitcar",1);
	}
	//if(VehicleInfo[vehicleid][vPlayer]==playerid &&  GetVehicleModel(vehicleid)==512 && VehicleInfo[vehicleid][vTeam] == TEAM_LICENSERS) VehicleInfo[vehicleid][vPlayer] = -1;
	return true;
}
stock GetString(param1[],param2[])
{
	return !strcmp(param1, param2, false);
}
stock IsATaxi(carid)
{
	return (VehicleInfo[carid][vJob] == 5);
}
public PutInVehicle(playerid)
{
    return true;
}
stock CheckEnterCar(playerid, vehicleid)
{
	if(GetPlayerVirtualWorld(playerid)!=1228)
	{
		if(VehicleInfo[vehicleid][vJob] != 0)
		{
		    new hour,minuite,second;
		    gettime(hour,minuite,second);

			if(PI[playerid][pJob] != VehicleInfo[vehicleid][vJob])
			{
			    SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет ключей от этого транспорта!");
				ExitCar(playerid);
			}
		}
		else if(VehicleInfo[vehicleid][vTeam] != 0 && VehicleLoad[vehicleid][vlRob] == false)
		{
			if(PI[playerid][pFraction] != VehicleInfo[vehicleid][vTeam] || (PI[playerid][pSubfraction] != VehicleInfo[vehicleid][vSubTeam]) && PI[playerid][pRank] != 11)
			{
				if(VehicleInfo[vehicleid][vTeam] == 10 && VehicleInfo[vehicleid][vSubTeam] == 0 && GetVehicleModel(vehicleid) == 426 && PI[playerid][pRank] == 11)
				    return 1;

				SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данный транспорт принадлежит организации, в которой Вы не состоите");
				ExitCar(playerid);

			}
			else
			{
			    if(PI[playerid][pRank] < VehicleInfo[vehicleid][vRank])
			    {
					new
					    veh_info[100];
					    
					format(veh_info, sizeof veh_info, "{FF2222}[Ошибка] {FFFFFF}Данный транспорт доступен с %d ранга", VehicleInfo[vehicleid][vRank]);
			        SCM(playerid, COLOR_WHITE, veh_info);
					ExitCar(playerid);
			    }
			}
		}

		if(IsAPlane(vehicleid))
		{
			if(PI[playerid][pFlyLic] < YES_LICENSE)
			{
			    SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет лицензии на полеты");
				ExitCar(playerid);
				return true;
			}
		}
		if(IsABoat(vehicleid))
		{
			if(PI[playerid][pBoatLic] < YES_LICENSE)
			{
				SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет лицензии на вождение водного транспорта");
				ExitCar(playerid);
				return true;
			}
		}
		if(!IsAPlane(vehicleid) && !IsABoat(vehicleid) && !IsABike(vehicleid) && !IsAMoped(vehicleid))
		{
			if(PI[playerid][pCarLic] < YES_LICENSE)
			{
			    SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас нет лицензии на вождение");
				ExitCar(playerid);
				return true;
			}
		}
	}
	return true;
}
stock ExitCar(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))RemovePlayerFromVehicle(playerid);
	else ClearAnimations(playerid);
	HideCarInfo(playerid);
	return true;
}
stock SetPlayerMoney(playerid, money)
{
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, money);
	PI[playerid][pMoney] = money;
	return true;
}
public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(IsPlayerNPC(playerid)) return true;
	new vehid = GetPlayerVehicleID(playerid);
	if(oldstate == 2 && PI[playerid][plveh]!=-1)
	{
		DestroyVehicleEx(PI[playerid][plveh]);
		PI[playerid][plveh]= -1;
	}
    if(newstate == PLAYER_STATE_DRIVER)
	{
		DeletePVar(playerid,"TesteR");
		if(temp_bus_spawn_timer[playerid] && temp_bus_id[playerid] != INVALID_VEHICLE_ID && GetVehicleModel(temp_bus_id[playerid]) == 437) KillTimer(temp_bus_spawn_timer[playerid]);
		else if(pTemp[playerid][pTruckID] != INVALID_PLAYER_ID && GetVehicleModel(vehid) == 515 || GetVehicleModel(vehid) == 514 || GetVehicleModel(vehid) == 403) KillTimer(pTemp[playerid][pTruckSpawnTimer]),DeletePVar(playerid,"exitedtrans");
		else if(pTemp[playerid][pMechID] != INVALID_PLAYER_ID && GetVehicleModel(vehid) == 525) KillTimer(pTemp[playerid][pMechSpawn]),DeletePVar(playerid,"exitveh");
		else if(pTemp[playerid][pProductID] != INVALID_PLAYER_ID && GetVehicleModel(vehid) == 456) KillTimer(pTemp[playerid][pProductSpawn]),DeletePVar(playerid,"exitcar");
	}
	
	if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_PASSENGER )
	{
		AddRedCheater(playerid);
	}
	//crasher1488
	if(newstate == 2)
	{
		new minute, second;
		gettime(minute, minute, second);
		new Float:vehz;
		GetVehiclePos(vehid, vehz, vehz, vehz);
		if(vehz > 3050.000)
		{
			SetVehicleToRespawn(vehid);
			KickEx(playerid, 28);
		}
		if(GetPVarInt(playerid, "AC_SECSD") == second)
		{
			if(GetPVarInt(playerid, "AC_VEHID") != vehid)
			{
				new lstring[128];
				format(lstring, sizeof(lstring), "[AC] » Игрок %s[%d] возможно использует Crasher.", PN(playerid), playerid);
				SendAdminsMessage(0xFF00FFFF, lstring);
				return true;
			}
		}
		SetPVarInt(playerid, "AC_SECSD", second);
		SetPVarInt(playerid, "AC_VEHID", vehid);
	}
	// ==================================================
	if(newstate == PLAYER_STATE_DRIVER)
	{
	    if(oldstate == PLAYER_STATE_PASSENGER)
	    {
			AddRedCheater(playerid);
	    }
	}
	if(newstate == PLAYER_STATE_PASSENGER)
		SetPlayerArmedWeapon(playerid, 0);

	if(newstate == PLAYER_STATE_DRIVER)
		SetPlayerArmedWeapon(playerid, 0);
		
	//начало невстате
	if(newstate==2)
	{
	    new carid = GetPlayerVehicleID(playerid);
        new id = GetVehicleModel(carid)-400;


	    pTemp[playerid][pcarid] = vehid;
	    pTemp[playerid][pDeathCar] = vehid;

	    VehicleSeat[carid][0] = playerid;
		AntiCheatGetVehicleHealth(carid,VehicleInfo[carid][vHealth]);
	    pTemp[playerid][pVehicle] = carid;
     	CheckEnterCar(playerid, carid);
     	
        new arend_id = INVALID_PLAYER_ID;
        
		if(!IsABike(carid))
		{
	 	    if(PI[playerid][pFine] > 15000)
			{
			    RemovePlayerFromVehicle(playerid);
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У вас слишком много неоплаченных штрафов");
				return 1;
			}
			
			if(Transport[id][trFuelable] != 0)
			{
				PI[playerid][pCarInfoTimer] = SetTimerEx("@__UpdateCarInfo",700,true,"iii",playerid,carid,0);

		        if(GetEngineStatus(carid) <= 0)
		        {
					SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы завести двигатель введите {AAE63E}/engine{FFFFFF} или нажмите {AAE63E}CTRL");
					//SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Чтобы включить фары введите {AAE63E}/lights{FFFFFF} или нажмите {AAE63E}ALT");
	   			}
			}
			else
				SetEngineStatus(carid);

		}

		else
		    if(GetEngineStatus(carid) <= 0 && GetArendCarID(vehid, arend_id) == (-1)) SetEngineStatus(carid);
		    
		//if(newstate == 2 && GetVehicleModel(GetPlayerVehicleID(playerid)) == 433 || GetVehicleModel(GetPlayerVehicleID(playerid)) ==548) SCM(playerid,COLOR_WHITE,"[Подсказка] {FFFFFF}Для того чтобы начать развозку оборудования введи [/carm]");

		if(VehicleInfo[carid][vTeam] == 7 && VehicleInfo[carid][vSubTeam] == 2 && GetVehicleModel(carid) == 548 && (VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading]))
		{
		    VehicleLoad[carid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[carid][vlLoading] = false;
			VehicleLoad[carid][vlUnloading] = false;
			
			if(IsValidDynamic3DTextLabel(VehicleLoad[carid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[carid][vlText]);
				
			DestroyDynamicArea(VehicleLoad[carid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[carid][vlPickup]);

			VehicleLoad[carid][vlPickup] = -1;
			VehicleLoad[carid][vlArea] = -1;
			VehicleLoad[carid][vlText] = NONE_3D_TEXT;
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Загрузка/разгрузка завершена");
		}
		if(VehicleInfo[carid][vTeam] == 7 && VehicleInfo[carid][vSubTeam] == 1 && GetVehicleModel(carid) == 548 && (VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading]))
		{
		    VehicleLoad[carid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[carid][vlLoading] = false;
			VehicleLoad[carid][vlUnloading] = false;

			if(IsValidDynamic3DTextLabel(VehicleLoad[carid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[carid][vlText]);

			DestroyDynamicArea(VehicleLoad[carid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[carid][vlPickup]);

			VehicleLoad[carid][vlPickup] = -1;
			VehicleLoad[carid][vlArea] = -1;
			VehicleLoad[carid][vlText] = NONE_3D_TEXT;
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Загрузка/разгрузка завершена");


		}
		if(VehicleInfo[carid][vTeam] == 7 && VehicleInfo[carid][vSubTeam] == 1 && GetVehicleModel(carid) == 433 && (VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading]))
		{
		    VehicleLoad[carid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[carid][vlLoading] = false;
			VehicleLoad[carid][vlUnloading] = false;

			if(IsValidDynamic3DTextLabel(VehicleLoad[carid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[carid][vlText]);

			DestroyDynamicArea(VehicleLoad[carid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[carid][vlPickup]);

			VehicleLoad[carid][vlPickup] = -1;
			VehicleLoad[carid][vlArea] = -1;
			VehicleLoad[carid][vlText] = NONE_3D_TEXT;
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Загрузка/разгрузка завершена. Отправляйтесь на отмеченное место");
       		foreach(new i : Player)
		    {
		        if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
		            continue;

				if(PI[i][pFraction] != 7)
				    continue;

				temp_army_loadfr[i] = -1;

                if(PI[i][pFraction] == 7 && PI[i][pSubfraction] == 1)
                	temp_army_loadfr[i] = VehicleLoad[carid][vlLoadFr], temp_army_loadsf[i] = VehicleLoad[carid][vlLoadSf];
			}
			if(temp_army_loadfr[playerid] == 8 && temp_army_loadsf[playerid] == 1)
			    SetPlayerCheckpointExx(playerid, 1524.4845, -1677.8949, 6.2188, 4.0);
			    
			else if(temp_army_loadfr[playerid] == 8 && temp_army_loadsf[playerid] == 2)
			    SetPlayerCheckpointExx(playerid, -1606.3378, 672.0713, -4.9063, 4.0);
			    
			else if(temp_army_loadfr[playerid] == 8 && temp_army_loadsf[playerid] == 3)
			    SetPlayerCheckpointExx(playerid, 2297.1123, 2468.7571, 10.8203, 4.0);

			else if(temp_army_loadfr[playerid] == 11 && temp_army_loadsf[playerid] == 0)
			    SetPlayerCheckpointExx(playerid, -2514.5027,-679.0071,139.3203, 4.0);
			
			else if(temp_army_loadfr[playerid] == 10 && temp_army_loadsf[playerid] == 0)
			    SetPlayerCheckpointExx(playerid, 1103.9768,-2048.7588,69.0078, 4.0);
			    
			else if(temp_army_loadfr[playerid] == 10 && temp_army_loadsf[playerid] == 1)
			    SetPlayerCheckpointExx(playerid, 1481.2008,-1765.9036,18.7958, 4.0);

			else if(temp_army_loadfr[playerid] == 10 && temp_army_loadsf[playerid] == 2)
			    SetPlayerCheckpointExx(playerid, -2756.8206,375.7390,4.3343, 4.0);
			    
			else if(temp_army_loadfr[playerid] == 10 && temp_army_loadsf[playerid] == 3)
			    SetPlayerCheckpointExx(playerid, 2385.2861,2465.8862,10.8203, 4.0);

			VehicleLoad[carid][vlLoadFr] = -1;
			VehicleLoad[carid][vlLoadSf] = -1;
		}
		if(VehicleInfo[carid][vTeam] == 7 && VehicleInfo[carid][vSubTeam] == 2 && GetVehicleModel(carid) == 433 && (VehicleLoad[carid][vlLoading] || VehicleLoad[carid][vlUnloading]))
		{
		    VehicleLoad[carid][vlID] = INVALID_VEHICLE_ID;
			VehicleLoad[carid][vlLoading] = false;
			VehicleLoad[carid][vlUnloading] = false;

			if(IsValidDynamic3DTextLabel(VehicleLoad[carid][vlText]))
				DestroyDynamic3DTextLabel(VehicleLoad[carid][vlText]);

			DestroyDynamicArea(VehicleLoad[carid][vlArea]);
			DestroyDynamicPickup(VehicleLoad[carid][vlPickup]);

			VehicleLoad[carid][vlPickup] = -1;
			VehicleLoad[carid][vlArea] = -1;
			VehicleLoad[carid][vlText] = NONE_3D_TEXT;
			SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Загрузка/разгрузка завершена");
       		foreach(new i : Player)
		    {
		        if(!IsPlayerConnected(i) || !IsPlayerLogged[i])
		            continue;

				if(PI[i][pFraction] != 7)
				    continue;

				temp_army_loadfr[i] = -1;
			}

		}
		if(IsAMafia(playerid))
		{
			if(VehicleInfo[carid][vTeam] == PI[playerid][pFraction] && (VehicleLoad[carid][vlMafLoading] || VehicleLoad[carid][vlMafUnloading]))
			{
			    VehicleLoad[carid][vlID] = INVALID_VEHICLE_ID;
				VehicleLoad[carid][vlMafLoading] = false;
				VehicleLoad[carid][vlMafUnloading] = false;

				if(IsValidDynamic3DTextLabel(VehicleLoad[carid][vlText]))
					DestroyDynamic3DTextLabel(VehicleLoad[carid][vlText]);

				DestroyDynamicArea(VehicleLoad[carid][vlArea]);
				DestroyDynamicPickup(VehicleLoad[carid][vlPickup]);

				VehicleLoad[carid][vlPickup] = -1;
				VehicleLoad[carid][vlArea] = -1;
				VehicleLoad[carid][vlText] = NONE_3D_TEXT;
				SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Загрузка/разгрузка завершена");
			}
			else if(VehicleInfo[carid][vTeam] == 7 && VehicleInfo[carid][vSubTeam] == 1 && GetVehicleModel(carid) == 433 && VehicleLoad[carid][vlRob])
			{
			    VehicleLoad[carid][vlID] = INVALID_VEHICLE_ID;
				VehicleLoad[carid][vlLoading] = false;
				VehicleLoad[carid][vlUnloading] = false;
				VehicleLoad[carid][vlRob] = false;

				if(IsValidDynamic3DTextLabel(VehicleLoad[carid][vlText]))
					DestroyDynamic3DTextLabel(VehicleLoad[carid][vlText]);

				DestroyDynamicArea(VehicleLoad[carid][vlArea]);
				DestroyDynamicPickup(VehicleLoad[carid][vlPickup]);

				VehicleLoad[carid][vlPickup] = -1;
				VehicleLoad[carid][vlArea] = -1;
				VehicleLoad[carid][vlText] = NONE_3D_TEXT;
				RemovePlayerFromVehicle(playerid);
				HideCarInfo(playerid);
				SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Разгрузка боеприпасов завершена");
			}
		}

        if(vehid==INVALID_VEHICLE_ID || VehicleID[playerid]!=vehid)
		{
		    if(GetVehicleModel(vehid)!=538 && GetVehicleModel(vehid)!=449 && GetVehicleModel(vehid)!=570) ToCheat(1,playerid);
		}

     	if(GetArendCarID(vehid, arend_id) != (-1))
		{
			if(arend_id == INVALID_PLAYER_ID || !IsPlayerConnected(arend_id))
			{
			    new
					rc = GetArendCarID(vehid),
					frmt_arend_message[210];
	
			    format(frmt_arend_message, sizeof frmt_arend_message, "{FFFFFF}Транспорт для аренды\n\n- Модель: {86B9FF}%s{FFFFFF}\n- Стоимость: {86B9FF}%d${FFFFFF}\n\nЧтобы арендовать нажмите {86B9FF}\"Аренда\"{FFFFFF}", VehicleName[GetVehicleModel(vehid)-400], ArendInfo[rc][aCost]);
				ShowPlayerDialogEx(playerid, 112, DIALOG_STYLE_MSGBOX, !"Аренда", frmt_arend_message, !"Аренда", !"Отмена");
			}
			else if(arend_id != playerid)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот транспорт уже арендуют");
			    RemovePlayerFromVehicle(playerid);
			}
		}
		
		if(vehid >= vMoped[0] && vehid <= vMoped[1])
		{
		    if(PI[playerid][pLevel] > 2)
			{
			    RemovePlayerFromVehicle(playerid);
			    HideCarInfo(playerid);
		        SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Данный транспорт Вам больше недоступен");
		        return 1;
			}
		}
		if(vehid >= vBus[0] && vehid <= vBus[1])
		{
			if(PI[playerid][pJob] != 1)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не водитель автобуса");
				RemovePlayerFromVehicle(playerid);
				HideCarInfo(playerid);
				return 1;
			}
			if(temp_bus_id[playerid] == vehid)
			{
				if(temp_bus_spawn_timer[playerid]) KillTimer(temp_bus_spawn_timer[playerid]);
				SetNextBusCP(playerid, temp_bus_pos[playerid]);
				return 1;
			}
	
			if(VehicleInfo[vehid][vBusOwner] != INVALID_PLAYER_ID)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот автобус уже арендуют");
				RemovePlayerFromVehicle(playerid);
				HideCarInfo(playerid);
				return 1;
			}
			
			if(temp_bus_id[playerid] != INVALID_VEHICLE_ID && temp_bus_id[playerid] != vehid)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете автобус"), RemovePlayerFromVehicle(playerid);

			if(PI[playerid][pMoney] < 200)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно 200$ для аренды автобуса");
				RemovePlayerFromVehicle(playerid);
                HideCarInfo(playerid);
				return 1;
			}

      		ShowPlayerDialogEx(playerid, 481, DIALOG_STYLE_MSGBOX, !"Аренда автобуса", !"{FFFFFF}Стоимость аренды этого транспорта составляет {FA8072}200${FFFFFF}\n\nВы действительно хотите арендовать автобус?", !"Да", !"Нет");
		}
		if(vehid >= vTaxi[0] && vehid <= vTaxi[1])
		{
			if(PI[playerid][pJob] != 2)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не работаете таксистом");
				RemovePlayerFromVehicle(playerid);
				HideCarInfo(playerid);
				return 1;
			}
			if(pTemp[playerid][pTaxiID] == vehid)
				return 1;
				
    		foreach(new i : Player)
			{
				if(!IsPlayerConnected(i))
					continue;

				if(i == playerid)
					continue;

				if(pTemp[playerid][pTaxiID] == vehid)
				{
					SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Это такси уже арендуют");
					RemovePlayerFromVehicle(playerid);
					HideCarInfo(playerid);
				}
			}
			if(pTemp[playerid][pTaxiID] != INVALID_VEHICLE_ID && pTemp[playerid][pTaxiID] != vehid)
				return SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете такси"), RemovePlayerFromVehicle(playerid);

			if(PI[playerid][pMoney] < 200)
			{
				SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вам нужно 200$ для аренды такси");
				RemovePlayerFromVehicle(playerid);
                HideCarInfo(playerid);
				return 1;
			}
      		ShowPlayerDialogEx(playerid, 484, DIALOG_STYLE_MSGBOX, !"Аренда такси", !"{FFFFFF}Стоимость аренды этого транспорта составляет {FA8072}200${FFFFFF}\n\nВы действительно хотите арендовать такси?", !"Да", !"Нет");

		}
		
	}
	///конец невстате
	if(newstate == PLAYER_STATE_DRIVER)
    {
        if(GetVehicleModel(GetPlayerVehicleID(playerid))!=538 && GetVehicleModel(GetPlayerVehicleID(playerid))!=449 && GetVehicleModel(GetPlayerVehicleID(playerid))!=570 && GetVehicleModel(GetPlayerVehicleID(playerid))!=483)
		{
	        new model = GetPlayerVehicleSeat(playerid);
	        if(model != 128)
	        {
	            if(!model)
	            {
	                model = GetVehicleModel(GetPlayerVehicleID(playerid));
	                if(!(400 <= model <= 611) || Pb[model - 400 >>> 3] >>> ((model - 400 & 7) << 2) & 0xF == 15) ToCheat(1,playerid);
	            }
	            else ToCheat(1,playerid);
	        }
		}
  		if((vehid >= vProduct[0] && vehid <= vProduct[1]))
		{
  			if(GetPVarInt(playerid, "CarProduct") && GetPVarInt(playerid, "CarProduct") != vehid) return SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендовали транспортное средство."),RemovePlayerFromVehicle(playerid);
			if(PI[playerid][pJob] != JOB_PRODUCT) return RemovePlayerFromVehicle(playerid), SCM(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не развозчик заказов");
			if(GetPVarInt(playerid, "CarProduct") != vehid)
			{
				ShowPlayerDialogEx(playerid, 5570, 0, "Аренда", "\n{ffffff}Вы хотите арендовать данный автомобиль?\nСтоимость: {63BD4E}$200.\n\n", "Да", "Нет");
			}
			else if(vehid == GetPVarInt(playerid, "CarProduct"))
			{
   				if(GetPVarInt(playerid, "ProductID") > 0)
			    {
			    	new Float:VPos[3], i = ProductInfo[GetPVarInt(playerid, "ProductID")][pBizid]-1;
					GetPlayerPos(playerid, VPos[0], VPos[1], VPos[2]);
					DisablePlayerRaceCheckpoint(playerid);
					SetPlayerRaceCheckpoint(playerid, 1, BizInfo[i][bEnter_X], BizInfo[i][bEnter_Y], BizInfo[i][bEnter_Z], 0.0, 0.0, 0.0, 6);
					new string[60];
					format(string, sizeof string, "{ffffff}Продуктов: {FFC800}%d", ProductInfo[GetPVarInt(playerid, "ProductID")][pTill]);
					JobText3D[playerid] = CreateDynamic3DTextLabel(string, -1, 0.0, 0.0, 0.0, 30.0, INVALID_PLAYER_ID, vehid);
					Attach3DTextLabelToVehicle(JobText3D[playerid], vehid, 0.0, -1.0, 2.6);
				}
				else SetPlayerRaceCheckpoint(playerid, 1, 2785.4731,-2493.4939,13.6531, 0.0, 0.0, 0.0, 5.0);
			}
		}
	    if((vehid >= vMech[0] && vehid <= vMech[1]))
		{
			if(PI[playerid][pJob] != JOB_MECHANIC)
			{
				SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не работаете механиком");
				RemovePlayerFromVehicle(playerid);
				return 1;
			}
			if(pTemp[playerid][pMechID] == vehid) return 1;
			if(pTemp[playerid][pMechID] != INVALID_VEHICLE_ID)
			{
				SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете авто");
				RemovePlayerFromVehicle(playerid);
				return 1;
			}
			foreach(new i: Player)
			{
				if(pTemp[i][pMechID] == vehid)
				{
					SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Это авто уже арендуют.");
					RemovePlayerFromVehicle(playerid);
					return 1;
				}
			}
			if(GetMoney(playerid) < 200)
			{
				SendClientMessage(playerid,COLOR_WHITE,"{FF2222}[Ошибка] {FFFFFF}Вам нужно 200$ чтобы арендовать эвакуатор");
				return RemovePlayerFromVehicle(playerid);
			}
			totalstring[0] = 0;
			ShowPlayerDialogEx(playerid,5567,0,"Аренда авто","{FFFFFF}\nВы хотите арендовать это авто за {63BD4E}$200{FFFFFF}?\n\n","Да","Нет");
		}
		// truck321
	    if((vehid >= vTruck[0][0] && vehid <= vTruck[2][1]))
		{
			if(PI[playerid][pJob] != JOB_TRUCKER)
			{
				SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы не работаете дальнобойщиком");
				RemovePlayerFromVehicle(playerid);
				return 1;
			}
			if(pTemp[playerid][pTruckID] == vehid) return 1;
			if(pTemp[playerid][pTruckID] != INVALID_VEHICLE_ID)
			{
				SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Вы уже арендуете тягач");
				RemovePlayerFromVehicle(playerid);
				return 1;
			}
			foreach(new i: Player)
			{
				if(pTemp[i][pTruckID] == vehid)
				{
					SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Этот тягач уже арендуют.");
					RemovePlayerFromVehicle(playerid);
					return 1;
				}
			}
			new trucklevel, price;
			if((vehid >= vTruck[0][0] && vehid <= vTruck[0][1]))
				trucklevel = 1, price = 200;
			else if(vehid >= vTruck[1][0] && vehid <= vTruck[1][1])
				trucklevel = 2, price = 300;
			else
				trucklevel = 3, price = 350;

			if((trucklevel == 2 && PI[playerid][pTruckSkill] < TRUCK_LEVEL_2) || (trucklevel == 3 && PI[playerid][pTruckSkill] < TRUCK_LEVEL_3))
			{
				SendClientMessage(playerid,COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Ваш опыт работы дальнобойщиком недостаточен для этого транспорта");
				RemovePlayerFromVehicle(playerid);
				return 1;
			}
			if(GetMoney(playerid) < price)
			{
			    totalstring[0] = 0;
				format(totalstring,80,"{FF2222}[Ошибка] {FFFFFF}Вам нужно %d$ чтобы арендовать этот грузовик",price);
				SendClientMessage(playerid,COLOR_WHITE,totalstring);
				totalstring[0] = 0;
				return RemovePlayerFromVehicle(playerid);
			}
			SetPVarInt(playerid,"truckprice",price);
			totalstring[0] = 0;
			format(totalstring,130,"{FFFFFF}Вы хотите арендовать этот грузовик за {63BD4E}$%d{FFFFFF},\n чтобы возить на нем грузы?",price);
			ShowPlayerDialogEx(playerid,5556,0,"Аренда грузовика",totalstring,"Да","Нет");
		}
    }
    else if(newstate == PLAYER_STATE_PASSENGER)
    {
        new model = GetVehicleModel(vehid);
        if(GetVehicleModel(GetPlayerVehicleID(playerid))!=538 && GetVehicleModel(GetPlayerVehicleID(playerid))!=449 && GetVehicleModel(GetPlayerVehicleID(playerid))!=570 && GetVehicleModel(GetPlayerVehicleID(playerid))!=483)
        {
	        if(400 <= model <= 611)
	        {
	            model -= 400;
	            new seat = GetPlayerVehicleSeat(playerid);
	            if(seat != 128)
	            {
	                model = (Pb[model >>> 3] >>> ((model & 7) << 2)) & 0xF;
	                if(!model || model == 15) ToCheat(1,playerid);
	                else if(!(0 < seat <= model)) ToCheat(1,playerid);
	            }
	        }
	        else ToCheat(1,playerid);
		}

	    new driverid = GetVehicleSeat(vehid,0);
		if(vehid >= vBus[0] && vehid <= vBus[1] && driverid != INVALID_PLAYER_ID) //Пассажир сел в автобус
		{
			new price = temp_bus_price[driverid];
			if(PI[playerid][pLevel] < 3)
			{
			    //SetPlayerChatBubble(playerid, "показал(а) водителю проездной", COLOR_PURPLE, 15.0, 5000);
			    new
					frmt_action[60];

				format(frmt_action, sizeof frmt_action, "%s показал(а) водителю проездной", PN(playerid));
			    ProxDetector(25.0, playerid, frmt_action, COLOR_ME);
				return 1;
			}
			if(PI[playerid][pMoney] < price)
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег для оплаты проезда");
			    RemovePlayerFromVehicle(playerid);
			    HideCarInfo(playerid);
			    return 1;
			}
			new mes[12];
			format(mes,sizeof(mes),"~g~+$%d",price);
			GameTextForPlayer(driverid,mes,1000,1);
			format(mes,sizeof(mes),"~r~-$%d",price);
			GameTextForPlayer(playerid,mes,1000,1);

			GiveMoney(playerid, -price, "оплата проезда");
			GiveMoney(driverid, price, "зп проезда");
		}
		if(vehid >= vTaxi[0] && vehid <= vTaxi[1] && driverid != INVALID_PLAYER_ID) //Пассажир сел в такси
		{
			if(pTemp[driverid][pTaxiID] != vehid || !pTemp[driverid][pTaxiPrice])
				return 1;
				
			if(pTemp[driverid][pTaxiPass] == INVALID_PLAYER_ID)
			{
				if(PI[playerid][pMoney] < pTemp[driverid][pTaxiPrice])
				{
					SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}У Вас недостаточно денег");
					HideCarInfo(playerid);
					return RemovePlayerFromVehicle(playerid);
				}
				pTemp[driverid][pTaxiStart] = VehicleInfo[vehid][vMillage];
				pTemp[driverid][pTaxiPass] = playerid;
				pTemp[driverid][pTaxiGoing] = true;
			}
			else
			{
				if(pTemp[driverid][pTaxiTurn][0] == INVALID_PLAYER_ID)
					pTemp[driverid][pTaxiTurn][0] = playerid;
					
				else if(pTemp[driverid][pTaxiTurn][1] == INVALID_PLAYER_ID)
					pTemp[driverid][pTaxiTurn][1] = playerid;
					
				else
				{
					if(!IsPlayerConnected(pTemp[driverid][pTaxiTurn][0]) || GetPlayerVehicleID(pTemp[driverid][pTaxiTurn][0]) != vehid)
					{
						if(pTemp[driverid][pTaxiTurn][1] != INVALID_PLAYER_ID)
						{
							pTemp[driverid][pTaxiTurn][0] = pTemp[driverid][pTaxiTurn][1];
							pTemp[driverid][pTaxiTurn][1] = playerid;
						}
						else pTemp[driverid][pTaxiTurn][0] = playerid;
					}
					else if(!IsPlayerConnected(pTemp[driverid][pTaxiTurn][1]) || GetPlayerVehicleID(pTemp[driverid][pTaxiTurn][1]) != vehid)
						pTemp[driverid][pTaxiTurn][1] = playerid;

					else
					{
						SendClientMessage(playerid, COLOR_WHITE, !"{FF2222}[Ошибка] {FFFFFF}Произошла системная ошибка. Перезайдите в такси");
						HideCarInfo(playerid);
						RemovePlayerFromVehicle(playerid);
					}
				}
			}
		}
		////
	    new seat = GetPlayerVehicleSeat(playerid);
	    VehicleSeat[vehid][seat] = playerid;
	    pTemp[playerid][pVehicle] = vehid;
    }

	if(oldstate == 2 || oldstate == PLAYER_STATE_PASSENGER)
	{
	    new vehicleid = pTemp[playerid][pVehicle];
		if(GetVehicleModel(vehicleid)==570)
		{
		    NoEnterPickup[playerid] =2;
	    	f_TogglePlayerControllable(playerid,false);
		}

		if(!IsAPlane(vehicleid) && !IsABike(vehicleid))
		{
			if(PI[playerid][pCarInfoTimer] != 0)
			{
				HideCarInfo(playerid);
				KillTimer(PI[playerid][pCarInfoTimer]);
				PI[playerid][pCarInfoTimer] = 0;
			}
		}

 	}
    
	/*
	if(newstate==PLAYER_STATE_PASSENGER || newstate==PLAYER_STATE_DRIVER)
    {
        new vehicleid=GetPlayerVehicleID(playerid);
        if(GetVehicleModel(vehicleid)!=538 && GetVehicleModel(vehicleid)!=449 && GetVehicleModel(vehicleid)!=570)
        {
	        if(vehicleid==INVALID_VEHICLE_ID || VehicleID[playerid]!=vehicleid)
	        {
	            J_Kick(playerid);
	            return 1;
	        }
	 	}
    }
    */
	if(oldstate == PLAYER_STATE_DRIVER)
	{
		if(PI[playerid][pCarInfoTimer] != 0)
		{
			HideCarInfo(playerid);
			KillTimer(PI[playerid][pCarInfoTimer]);
			PI[playerid][pCarInfoTimer] = 0;
		}
	}
    
	return true;
}

