#if defined _quest_included
	#endinput
#endif
#define _quest_included

new
	gQuestSaimon,
	gQuestLinkoln;

public OnGameModeInit()
{
	CreateActor(234, 1771.3352, -1884.2300, 13.5528, 181.2930);
	CreateDynamic3DTextLabel("Gurama", 0xFFFFFFAA, 1771.3352, -1884.2300, 13.5528+1.0, 5.0);
	CreateDynamic3DTextLabel("[ALT]", 0xFFFFFFAA, 1771.3352, -1884.2300, 13.5528+0.5, 5.0);

	gQuestSaimon = CreateDynamicSphere(1771.3812, -1884.9320, 13.5528, 5.0);

	CreateActor(206, 380.8920, -2021.7834, 7.8359, 181.6688);
	CreateDynamic3DTextLabel("Batoni Rolandi", 0xFFFFFFAA, 380.8920, -2021.7834, 7.8359+1.0, 5.0);
	CreateDynamic3DTextLabel("[ALT]", 0xFFFFFFAA, 380.8920, -2021.7834, 7.8359+0.5, 5.0);

	gQuestLinkoln = CreateDynamicSphere(380.9093, -2022.4840, 7.8359, 5.0);

    #if defined quest_OnGameModeInit
         return quest_OnGameModeInit();
    #else
   	 	return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit quest_OnGameModeInit
#if defined quest_OnGameModeInit
	forward quest_OnGameModeInit();
#endif


public OnPlayerEnterDynamicArea(playerid, areaid)
{
    #if defined quest_OnPlayerEnterDynamicArea
         return quest_OnPlayerEnterDynamicArea(playerid, areaid);
    #else
   	 	return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea quest_OnPlayerEnterDynamicArea
#if defined quest_OnPlayerEnterDynamicArea
	forward quest_OnPlayerEnterDynamicArea(playerid, areaid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
 	if(newkeys & KEY_WALK && !IsPlayerInAnyVehicle(playerid))
	{
		if(IsPlayerInDynamicArea(playerid, gQuestSaimon))
		{
		    if(PI[playerid][pQuest] == 1 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
				ShowPlayerDialogEx(playerid, 1050, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Moicade.\nRogorc Vxedav Axlaxans Chamoxvedi, Ar Gifiqria imaze Tu rogor unda gamoimushavo fuli?\nTu Dagchirdeba Me Makvs Shentvis Samsaxuri.\nAqve Aketeben Gzas, dachirdebat bichebs xelis wamokvra, fulis shovnasac shedzleb\n\n{AFAFAF}Davaleba: Gadaitane 20 urika xreshit\nSachuqari: 3750$ da 1 EXP", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 1 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 20)
			{
			    new
					frmt_quest_info[170];

				format(frmt_quest_info, sizeof frmt_quest_info, "{AFAFAF}Davaleba: Gadaitane 20 Urika Xreshit\nSachuqari: 3750$ da 1 EXP\nShesrulebulia: %d/20", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", frmt_quest_info, !"Daxurva", !"");
			}
			else if(PI[playerid][pQuest] == 1 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] >= 20)
			    ShowPlayerDialogEx(playerid, 1051, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Yochag Kargad Gimushavia! Aige Sachuqari!", !"Shemdeg", !"");

			else if(PI[playerid][pQuest] == 2 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
				ShowPlayerDialogEx(playerid, 1151, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Ici ra vifiqre?. Kargi Droa Aigo Martvis Mowmoba.\nQalaqshi Avtomobilit Gadaadgileba Uketesia.\nMidit Avtoskolashi da Gaiare Gamocda. Valdebulebebi Cota Rtulia, Amitom Kargad Sheiswavle Sakitxebi.\nRodesac Chaabareb, Dabrundi Chemtan.\n\n{AFAFAF}Davaleba: Aige Martvis Mowmoba\nSachuqari: 3500$", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 2 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", !"{AFAFAF}Davaleba: Aige Martvis Mowmoba\nSachuqari: 3500$", !"Daxurva", !"");

			else if(PI[playerid][pQuest] == 2 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven Miiget {33AA33}3500$");
	            GiveMoney(playerid, 3500, "Davaleba 2");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 525);
	            }

		        PI[playerid][pQuest] = 3;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        	ShowPlayerDialogEx(playerid, 1053, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Vxedav Ukve Agigia Martvis Mowmoba.\nArcise Shors Datvirtuli Gemi Shemovida Portshi, Chem Dzmakacs Aqvs Chabarebuli Tvirti da Xalxi Chirdeba.\nSamsaxuri Arc Ise Rtulia, romlistvisac Kargad Gadagixdian.\n\n{AFAFAF}Davaleba: Gadaitane 20 Datvirtuli Yuti\nSachuqari: 4200$ da 1 EXP", !"Dadastureba", !"Uari");
			}
			
			

			else if(PI[playerid][pQuest] == 3 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 20)
			{
			    new
					frmt_quest_info[170];

				format(frmt_quest_info, sizeof frmt_quest_info, "{AFAFAF}Davaleba: Gadaitane 20 Datvirtuli Yuti\nSachuqari: 4200$ da 1 ехр\nShesrulebulia: %d/20", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", frmt_quest_info, !"Daxurva", !"");
			}
			else if(PI[playerid][pQuest] == 3 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] >= 20)
			    ShowPlayerDialogEx(playerid, 1054, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Chemi Dzmakaci Shenit Madlobelia", !"Shemdeg", !"");

			else if(PI[playerid][pQuest] == 4 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
			    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", !"{AFAFAF}Davaleba: Iyide Telefoni 24/7\nSachuqari: 3500$", !"Daxurva", !"");

			else if(PI[playerid][pQuest] == 4 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
		        ShowPlayerDialogEx(playerid, 1055, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Droa Sheidzino Axali Iphoni, Axlomaxlos Magaziashi Aris Axali Iphonebi.\n\n{AFAFAF}Davaleba: Sheidzine Telefoni 24/7\nSachuqari: 3500$", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 4 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven Miiget {33AA33}3500$");
	            GiveMoney(playerid, 3500, "Davaleba 4");

	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 525);
	            }

		        PI[playerid][pQuest] = 5;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
			    ShowPlayerDialogEx(playerid, 1056, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Mismine. Tu ar Daigale Samsaxurit, Shentvis Kidev Erti Patara Samsaxuri Maqvs.\nAvtomobilis Nawilebis Qarxanashi Vakansiaa.\nVfiqrob Kargad Gamoimushaveb.\n\n{AFAFAF}Davaleba: Sheagrove 20 Avtomobilis Nawili\nSachuqari: 5200$ da 1 EXP", !"Dadastureba", !"Uari");
			}
			else if(PI[playerid][pQuest] == 5 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 20)
			{
			    new
					frmt_quest_info[170];

				format(frmt_quest_info, sizeof frmt_quest_info, "{AFAFAF}Davaleba: Sheagrove 20 Avtomobilis Nawili\nSachuqari: 5200$ Da 1 EXP\nShesrulebulia: %d/20", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", frmt_quest_info, !"Daxurva", !"");
			}
			else if(PI[playerid][pQuest] == 5 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] != 20)
			    ShowPlayerDialogEx(playerid, 1056, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Mismine. Tu ar Daigle Samsaxurit, Shentvis Kidev Erti Patara Samsaxuri Maqvs.\nAvtomobilis Nawilebis Qarxanashi Vakansiaa.\nVfiqrob Kargad Gamoimushaveb.\n\n{AFAFAF}Davaleba: Sheagrove 20 Avtomobilis Nawili\nSachuqari: 5200$ da 1 EXP", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 5 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] >= 20)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}5200$ da 1 EXP");
	            GiveMoney(playerid, 5200, "Davaleba 5");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 780);
	            }

				PI[playerid][pExp]++;
				UpdatePlayerData(playerid, "Exp", PI[playerid][pExp]);
				CheckNextLevel(playerid);
		        PI[playerid][pQuest] = 6;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        ShowPlayerDialogEx(playerid, 1057, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}. Droa Gamoicvalo.\nAxlomaxloshi Aris Tansacmlis Magaziaa, Sheidzine Rame Normaluri.\n\n{AFAFAF}Davaleba: Sheidzine Axali Skini Magaziashi\nDavaleba: 5000$", !"Dadastureba", !"Uari");
			}
			else if(PI[playerid][pQuest] == 6 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", !"{AFAFAF}: Sheidzine Axali Skini Magaziashi\nSachuqari: 5000$", !"Daxurva", !"");

            else if(PI[playerid][pQuest] == 6 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] != 1)
		        ShowPlayerDialogEx(playerid, 1057, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Droa Gamoicvalo.\nAxlomaxloshi Tansacmlis Magaziaa, Sheidzine Rame Normaluri.\n\n{AFAFAF}Davaleba: Sheidzine Axali Skini Magaziashi\nDavaleba: 5000$", !"Dadastureba", !"Uari");

	        else if(PI[playerid][pQuest] == 6 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}5000$");
	            GiveMoney(playerid, 5000, "Davaleba 6");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 750);
	            }
		        PI[playerid][pQuest] = 7;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	            ShowPlayerDialogEx(playerid, 1058, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Aset Karg Skins Kargi Aqsesuari Mouxdeba.\nSheidzine rame aqsesuari Magaziashi.\n\n{AFAFAF}Davaleba: Mibrdzandit Aqsesuarebis Magaziashi Da sheidzinet Aqsesuari\nDavaleba: 4700$", !"Dadastureba", !"Uari");
			}
			else if(PI[playerid][pQuest] == 7 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
			    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", !"{AFAFAF}Davaleba: Sheidzine rame aqsesuari Magaziashi\nSachuqari: 4700$", !"Daxurva", !"");

            else if(PI[playerid][pQuest] == 7 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] != 1)
	            ShowPlayerDialogEx(playerid, 1058, DIALOG_STYLE_MSGBOX, !"Саймон", !"{FFFFFF}Aset Karg Skins Kargi Aqsesuari Mouxdeba..\nSheidzine Rame Aqsesuari Magaziashi.\n\n{AFAFAF}Davaleba: Mibrdzandit Aqsesuarebis Magaziashi Da Sheidzinet Aqsesuari\nDavaleba: 4700$", !"Dadastureba", !"Uari");

	    	else if(PI[playerid][pQuest] == 7 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}4700$");
	            GiveMoney(playerid, 4700, "Davaleba 7");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 705);
	            }
		        PI[playerid][pQuest] = 8;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, 1059, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Mivxvdi Rom Sheni Ndoba Sheidzleba, Sasiamovnoa Shentan Saqmis Dachera, Aige Patara Bonusi Chemgan.\nCotaxnit Mivdivar Qalaq-Garet.\nTu Dagaintersebs, Chem megobar Baton Rolandis Aqvs Shemotavazeba. Shen Shedzleb Mis Povnas Eshmakis Borbaltan.\n\n{AFAFAF}Davaleba: Gaesaubret Baton Rolandis\nSachuqari: 8000$ da 2 EXP", !"Dadastureba", !"Uari");
			}
	    	else if(PI[playerid][pQuest] == 8 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] == 0)
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", !"{AFAFAF}Davaleba:Gaesaubret Baton Rolandis\nDavaleba: 8000$ Da 2 EXP", !"Daxurva", !"");

	    	else if(PI[playerid][pQuest] == 8 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
				ShowPlayerDialogEx(playerid, 1059, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}.Mivxvdi Rom Sheni Ndoba Sheidzleba, Sasiamovnoa Shentan Saqmis Dachera, Aige Patara Bonusi Chemgan.\nCotaxnit Mivdivar Qalaq-Garet.\nTu Dagainteresebs, Chem Megobar Baton Rolandis Aqvs Shemotavazeba. Shen Shedzleb Mis Povnas Eshmakis Borbaltan.\n\n{AFAFAF}Davaleba: Gaesaubret Baton Rolandis\nSachuqari: 8000$ da 2 EXP", !"Dadastureba", !"Uari");

			else
			    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Jer-Jerobit Araferi Maqvs Shentvis", !"Daxurva", !"");
		}
		else if(IsPlayerInDynamicArea(playerid, gQuestLinkoln))
		{
	    	if(PI[playerid][pQuest] == 8 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] == 0)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven Miiget {33AA33}8000$ da 2 EXP");
	            GiveMoney(playerid, 8000, "Davaleba 8");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 1200);
	            }

				PI[playerid][pExp] += 2;
				UpdatePlayerData(playerid, "Exp", PI[playerid][pExp]);
				CheckNextLevel(playerid);
		        PI[playerid][pQuest] = 9;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
			    ShowPlayerDialogEx(playerid, 1060, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Gaumarjos, Me Batoni Rolandi var.\n, Guramam Mitxra Rom Moxvidodi. Shentvis Maqvs Samsaxuri.\nVimedovneb Gaqvs Martvis Mowmoba, Saswrafod Mchirdeba Avtobusis Mdzgoli.\nVfiqrob Martivad Gaumklavdebi.\n\n{AFAFAF}Davaleba: Gaiare 250 CheckPoint_i\nSachuqari: 7800$ da 2 EXP", !"Dadastureba", !"Uari");
			}
	    	else if(PI[playerid][pQuest] == 9 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
			    ShowPlayerDialogEx(playerid, 1060, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Gaumarjos,  Me Batoni Rolandi var \nGuramam Mitxra Rom Moxvidodi.\nVimedovneb Gaqvs Martvis Mowmoba, Saswrafod Mchirdeba Avtobusis Mdzgoli. \nVfiqrob Martivad Gaumklavdebi.\n\n{AFAFAF}Davaleba: Проехать 250 CheckPoint_i\nSachuqari: 7800$ da 2 EXP", !"Dadastureba", !"Uari");

	    	else if(PI[playerid][pQuest] == 9 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 250)
			{
			    new
					frmt_quest_info[170];

				format(frmt_quest_info, sizeof frmt_quest_info, "{AFAFAF}Davaleba: Gaiaret 250 CheckPoint_i\nSachuqari: 7800$ da 2 EXP\Shesrulebulia: %d/250", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", frmt_quest_info, !"Daxurva", !"");
			}
			else if(PI[playerid][pQuest] == 9 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] >= 250)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}7800$ da 2 EXP");
	            GiveMoney(playerid, 7800, "Davaleba 9");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 1170);
	            }
				PI[playerid][pExp] += 2;
				UpdatePlayerData(playerid, "Exp", PI[playerid][pExp]);
				CheckNextLevel(playerid);
		        PI[playerid][pQuest] = 10;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, 1061, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Mismine Didi Xania Ukve Shtatshi Cxovrob, Magram Samedicino Wignaki Jer ar gaqvs.\nTu Amieridan Mogindeba Samsaxuris Dawyeba, is aucileblad gamogadgeba.\nAiget is nebismieri Shtatis Saavadmkofoshi .\n\n{AFAFAF}Davaleba: Aiget Med Karta Saavadmkofoshi\nSachuqari: 6200$", !"Dadastureba", !"Uari");
			}

	    	else if(PI[playerid][pQuest] == 10 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
				ShowPlayerDialogEx(playerid, 1061, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Mismine Didi xania ukve shtatshi cxovrob, magram samedicino wignaki jer ar gaqvs.\nTu amieridan Mogindeba Samsaxuris dawyeba ,is aucileblad gamogadgeba.\nAige is nebismieri shtatis Saavadmkofoshi.\n\n{AFAFAF}Davaleba: Aiget Med Karta Saavadmkofoshi\nSachuqari: 6200$", !"Dadastureba", !"Uari");

	    	else if(PI[playerid][pQuest] == 10 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{AFAFAF}Davaleba: Miiget Med Karta Saavadmkofoshi\nНаграда: 6200$", !"Daxurva", !"");

			else if(PI[playerid][pQuest] == 10 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}6200$");
	            GiveMoney(playerid, 6200, "Davaleba 10");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 930);
	            }
		        PI[playerid][pQuest] = 11;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
                ShowPlayerDialogEx(playerid, 1062, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Zogjer Shtatshi Yofna Araa Usafrtxo, Shen Aucileblad Gchirdeba Iaragi.\nIaragis Tarebistvis gchirdebat licenzia, Am licenziis migebas shedzlebt Meriashi.\nEs ar waigebs did dros.\n\n{AFAFAF}Davaleba: Aiget Iaragis Licenzia Meriashi\nSachuqari: 6600$", !"Dadastureba", !"Uari");
			}

	    	else if(PI[playerid][pQuest] == 11 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
                ShowPlayerDialogEx(playerid, 1062, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Zogjer Shtatshi Yofna Araa Usafrtxo, Shen Aucileblad Gchirdeba Iaragi.\nIaragis Tarebistvis Gchirdebat Licenzia, Am Licenziis Migebas Shedzlebt Meriashi.\nES Ar waigebs did dros.\n\n{AFAFAF}Davaleba: Aiget Iaragis Licenzia Meriashi\nSachuqari: 6600$", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 11 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{AFAFAF}Davaleba: Aiget Iaragis Licenzia Meriashi\nSachuqari: 6600$", !"Daxurva", !"");

			else if(PI[playerid][pQuest] == 11 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}6600$");
	            GiveMoney(playerid, 6600, "Davaleba 11");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 990);
	            }
		        PI[playerid][pQuest] = 12;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        ShowPlayerDialogEx(playerid, 1063, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Tqven Ukve Aiget Licenzia, Magram Es ar aris sakmarisi.\nLicenziastan ertad aseve gchirdebat Srolis Gamocdileba daiwyet \"Desert Eagle_it"\" tirshi .\n\n{AFAFAF}Davaleba: Gaisrolet 200 Tyvia \"Desert Eagle_it\" Tiris Teritoriaze\nSachuqari: 7000$ da 15 Tyvia \"Desert Eegles\"", !"Dadastureba", !"Uari");
			}

	    	else if(PI[playerid][pQuest] == 12 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
		        ShowPlayerDialogEx(playerid, 1063, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Tqven Ukve Aiget Licenzia, Magram Es ar aris sakmarisi.\nLicenziastan ertad aseve gchirdebat Srolis Gamocdileba daiwyet \"Desert Eagle_it"\" tirshi .\n\n{AFAFAF}Davaleba: Gaisrolet 200 Tyvia \"Desert Eagle_it\" Tiris Teritoriaze\nSachuqari: 7000$ da 15 Tyvia \"Desert Eegles\"", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 12 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 200)
			{
			    new
					frmt_quest_info[170];

				format(frmt_quest_info, sizeof frmt_quest_info, "{AFAFAF}Davaleba: Gaisrolet 200 Tyvia \"Desert Eagle_it\" Tiris Teritoriaze\nDavaleba: 7000$ da 15 Tyvia \"Desert Eagles\"\nShesrulebulia: %d/200", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", frmt_quest_info, !"Daxurva", !"");
			}

			else if(PI[playerid][pQuest] == 12 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] >= 200)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}7000$ da 15 Tyvia Desert Eegles\");
	            GiveMoney(playerid, 7000, "Davaleba 12");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 1100);
	            }
	            _GiveGun(playerid, 24, 15);
		        PI[playerid][pQuest] = 13;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        ShowPlayerDialogEx(playerid, 1064, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Movida Dro Cotati Gavertot.\nShtatshi Xshirad Tardeba Turniri PaintBallshi, Miige Monawileoba masshi .\nEs Kargi Sashualebaa Rom Ar Dakargot karg xasiatze yofnis survili.\nAmavdroulad tqven dasachuqrdebit.\n\n{AFAFAF}Davaleba: Miiget Monawileoba PaintBall Turnirshi\nSachuqari: 7500$", !"Dadastureba", !"Uari");
			}

			else if(PI[playerid][pQuest] == 13 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
		        ShowPlayerDialogEx(playerid, 1064, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Movida Dro Cotati Gavertot.\nShtatshi Xshirad Tardeba Turniri PaintBallshi, Miige Monawileoba masshi .\nEs Kargi Sashualebaa Rom Ar Dakargot karg xasiatze yofnis survili.\nAmavdroulad tqven dasachuqrdebit.\n\n{AFAFAF}Davaleba: Miiget Monawileoba PaintBall Turnirshi\nSachuqari: 7500$", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 13 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{AFAFAF}Davaleba:Miiget Monawileoba PaintBall turnirshi \nSachuqari: 7500$", !"Daxurva", !"");

			else if(PI[playerid][pQuest] == 13 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Sachuqari {33AA33}7500$");
	            GiveMoney(playerid, 7500, "Davaleba 13");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 1150);
	            }
		        PI[playerid][pQuest] = 15;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        ShowPlayerDialogEx(playerid, 1066, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Gadatvirtuli dgis shemdeg droa cota shechamo.\nMidi uaxloes kafeshi da shechame.\n\n{AFAFAF}Davaleba: Iyidot nebismieri sachmeli nebismier kafeshi\nSachuqari: 7000$", !"Dadastureba", !"Uari");

		        //ShowPlayerDialogEx(playerid, 1065, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Imedia daisvene ukve.\nAxla ki droa kvlav dabrunde samsaxurshi.\nSatvirto avtomobilis mdzgolebs kargad uxdian, Unda mosinjo.\n\n{AFAFAF}Davaleba: Gadaitanot 15 tona tvirti\nSachuqari: 10000$ da 2 exp", !"Dadastureba", !"Uari");
			}

			else if(PI[playerid][pQuest] == 14 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
		        ShowPlayerDialogEx(playerid, 1065, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Imedia ukve daisvene.\nAxla ki droa kvlav dabrunde samsaxurshi.\nSatvirto avtomobilis mdzgolebs kargad uxdian, Unda mosinjo.\n\n{AFAFAF}Davaleba: Gadaitanot 15 tona tvirti\nSachuqari: 10000$ da 2 exp", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 14 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 15)
			{
			    new
					frmt_quest_info[170];

				format(frmt_quest_info, sizeof frmt_quest_info, "{AFAFAF}Davaleba: Gadaitanot 15 tonda tvirti\nSachuqari: 10000$ da 2 exp\nShesrulebulia: %d/15", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", frmt_quest_info, !"Daxurva", !"");
			}

			else if(PI[playerid][pQuest] == 14 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] >= 15)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven Miiget {33AA33}10000$");
	            GiveMoney(playerid, 10000, "Questi 14");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 1500);
	            }
				PI[playerid][pExp] += 2;
				UpdatePlayerData(playerid, "Exp", PI[playerid][pExp]);
				CheckNextLevel(playerid);
		        PI[playerid][pQuest] = 15;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        ShowPlayerDialogEx(playerid, 1066, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Gadatvirtuli dgis shemdeg droa cota shechamo\nMidi uaxloes kafeshi da shechame.\n\n{AFAFAF}Davaleba: Iyidot nebismieri sachmeli nebismier kafeshi\nDavaleba: 7000$", !"Dadastureba", !"Uari");
			}

			else if(PI[playerid][pQuest] == 15 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
		        ShowPlayerDialogEx(playerid, 1066, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Gadatvirtuli dgis shemdeg droa cota shechamo.\nMidi uaxloes kafeshi da shechame.\n\n{AFAFAF}Davaleba: Iyidot nebismieri sachmeli nebismier kafeshi\nDavaleba: 7000$", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 15 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
				ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{AFAFAF}{AFAFAF}Davaleba: Iyidot nebismieri sachmeli nebismier kafeshi\nDavaleba: 7000$", !"Daxurva", !"");

			else if(PI[playerid][pQuest] == 15 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 1)
			{
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven Miiget {33AA33}7000$");
	            GiveMoney(playerid, 7000, "Davaleba 15");
	            if(PI[playerid][pPromo])
	            {
	                new promoid = PI[playerid][pPromo]-1;
	                GivePromoMoney(playerid, promoid, 1050);
	            }
		        PI[playerid][pQuest] = 16;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	         	ShowPlayerDialogEx(playerid, 1067, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Davita martali yofila shen martlac kai kaci xar.\nMagram aq chveni tanamshromloba shewyda, davaleba agar maqvs shentvis. Magram rogorc ki gamochndeba samsaxuri\n Aucileblad dagirekav. Bolostvis ert rchevas mogcem , monaxe iseti samsaxuri romelic mogewoneba,\nMoewyve romelime organicaciashi da daiwye sheni kariera.\n\nWarmatebebi.\n\n{AFAFAF}Davaleba: Moewyot organizaciashi\nSachuqari: 25000$", !"Dadastureba", !"Uari");
			}

            else if(PI[playerid][pQuest] == 16 && PI[playerid][pQuestStatus] == 0 && PI[playerid][pQuestProcess] == 0)
	         	ShowPlayerDialogEx(playerid, 1067, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Davita martali iyo,shen martlac kai kaci xar.\nMagram aq chveni tanamshormloba shewyda,davaleba agar maqvs shentvis. Magram rogorc ki gamochndeba samsaxuri,\nAucileblad dagirekav. Bolostvis ert rchevas mogcem,monaxe iseti samsaxuri romelic mogewoneba\nMoewyve romelime organicaciashi da daiwye sheni kariera.\n\nWarmatebebi.\n\n{AFAFAF}Davaleba: Moewyot organizaciashi\nSachuqari: 25000$", !"Dadastureba", !"Uari");

			else if(PI[playerid][pQuest] == 16 && PI[playerid][pQuestStatus] != 0 && PI[playerid][pQuestProcess] != 1)
                ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{AFAFAF}{AFAFAF}Davaleba: Moewyo organicaciashi\nDavaleba: 25000$", !"Daxurva", !"");

			else
			    ShowPlayerDialogEx(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Jer jerobit armaqvs samsaxuri shentvis", !"Daxurva", !"");

		}
	}
    #if defined quest_OnPlayerKeyStateChange
         return quest_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
    #else
   	 	return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange quest_OnPlayerKeyStateChange
#if defined quest_OnPlayerKeyStateChange
	forward quest_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock QuestDialog(playerid, dialogid, response)
{
	switch(dialogid)
	{
		case 1050:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 1)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Gadaitanet 20 urika xreshi da dabrundit ukan");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Gaeshuret samsaxurisken \"Mshenebeli\" {FFFF00}(/gps -> Samsaxurebi -> Mshenebeli)");
		}
		case 1051:
		{
		    if(!response)
				return 1;

	    	if(PI[playerid][pQuest] != 1)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven miiget {33AA33}3750$ da 1 exp");
            GiveMoney(playerid, 3750, "Davaleba 1");
            if(PI[playerid][pPromo])
            {
                new promoid = PI[playerid][pPromo]-1;
                GivePromoMoney(playerid, promoid, 563);
            }
			PI[playerid][pExp]++;
			UpdatePlayerData(playerid, "Exp", PI[playerid][pExp]);
			CheckNextLevel(playerid);

			if(PI[playerid][pCarLic] != YES_LICENSE)
			{
		        PI[playerid][pQuest] = 2;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, 1052, DIALOG_STYLE_MSGBOX, !"Daviti", !"{FFFFFF}Ici ra vipiqre?. Droa aigo martvis mowmoba.\nMainc avtomobilit gadaadgileba shtatshi uketesia.\n.Midit avtoskolashi da gairet gamocda, valdebulebebi cota rtulia amitom kargad sheiswavlet sakitxebi.\nRodesac chaabareb dabrundi chemtan.\n\n{AFAFAF}Davaleba: Aiget martvis mowmoba\nSachuqari: 3500$", !"Dadastureba", !"Uari");
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Tqven ukve sheasrulet yvela davaleba");
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Вы получили {33AA33}3500$");
	            GiveMoney(playerid, 3500, "квест 2");
		        if(PI[playerid][pPromo])
		        {
		            new promoid = PI[playerid][pPromo]-1;
		            GivePromoMoney(playerid, promoid, 525);
		        }
		        PI[playerid][pQuest] = 3;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        	ShowPlayerDialogEx(playerid, 1053, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Rogorc vxedav martvis mowmoba chagibarebia, yochag.\nAxlomaxloshi portia sadac datvirtuli gemi chamovida, Chemi dzmakacs aqvs tvirti chabarebuli da xelis wamokvra ar awyens.\nAraa rtuli samsaxuri , kargadac gadagixdian.\n\n{AFAFAF}Davaleba: Gadaitanot 20 cali yuti\nSachuqari: 4200$ da 1 ехр", !"Dadastureba", !"Uari");
			}
		}
		case 1151:
		{
		    if(!response)
				return 1;

	    	if(PI[playerid][pQuest] != 2)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

			if(PI[playerid][pCarLic] != YES_LICENSE)
			{
		        PI[playerid][pQuest] = 2;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
				ShowPlayerDialogEx(playerid, 1052, DIALOG_STYLE_MSGBOX, !"Саймон", !"{FFFFFF}Ici ra vifiqre. Droa aigo martvis mowmoba.\nMainc avtoboilit gadaagileba shtatshi ufro advilia.\nWadi avtoskolashi da chaabare martvis mowmoba. Motxovnebi rtulia amitom yuradgebit iswavle .\nRodesac chaabareb dabrundi chemtan.\n\n{AFAFAF}Davaleba: Aigo martvis mowmoba\nDavaleba: 3500$", !"Dadastureba", !"Uari");
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}tqven ukve sheasrulet yvela davaleba");
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven miiget {33AA33}3500$");
	            GiveMoney(playerid, 3500, "квест 2");
		        if(PI[playerid][pPromo])
		        {
		            new promoid = PI[playerid][pPromo]-1;
		            GivePromoMoney(playerid, promoid, 525);
		        }
		        PI[playerid][pQuest] = 3;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        	ShowPlayerDialogEx(playerid, 1053, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Rogorc vxedav ukve martvis mowmoba ukve chagibarebia.\n.Axlomaxloshi portia sadac datvirtuli gemi chamovida, Chemi dzmakacs aqvs tvirti chabarebuli da xelis wamokvra ar awyens\nAraa rtuli samsaxuri., kargadac gadagixdian\n\n{AFAFAF}Davaleba: Davaleba gdaitanot 45 cali yuti\nSahuqari: 4200$ da 1 ехр", !"Dadastureba", !"Uari");
			}


		}
		case 1052:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 2)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Aigot martvis mowmoba");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Wadit avtoskolashi {FFFF00}(/gps -> Mnishvnelovani adgilebi -> Avtoskola)");
		}
		case 1053:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 3)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Gadaitanet 20 cali yuti");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Gaemgzavret samushaoze \"Mtvirtavi\" {FFFF00}(/gps -> Smushaoebi -> Mtvirtavi)");
		}
		case 1054:
		{
		    if(!response)
		        return 1;


	    	if(PI[playerid][pQuest] != 3)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven miiget {33AA33}4200$ da 1 exp");
            GiveMoney(playerid, 4200, "квест 3");
	        if(PI[playerid][pPromo])
	        {
	            new promoid = PI[playerid][pPromo]-1;
	            GivePromoMoney(playerid, promoid, 630);
	        }
			PI[playerid][pExp]++;
			UpdatePlayerData(playerid, "Exp", PI[playerid][pExp]);
			CheckNextLevel(playerid);


			if(0 == PI[playerid][pPhone])
			{
		        PI[playerid][pQuest] = 4;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        ShowPlayerDialogEx(playerid, 1055, DIALOG_STYLE_MSGBOX, !"Саймон", !"{FFFFFF}Droa iyidot axali iPhone. Axlomaxlos aris magazia sadac moitanes axali telephonebi\n\n{AFAFAF}Davaleba: Iyidot telephoni 24/7\nSachuqari: 3500$", !"Dadastureba", !"Uari");
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Tqven sheasrulet yvela davaleba");
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven miiget{33AA33}3500$");
	            GiveMoney(playerid, 3500, "Davaleba 4");
		        if(PI[playerid][pPromo])
		        {
		            new promoid = PI[playerid][pPromo]-1;
		            GivePromoMoney(playerid, promoid, 525);
		        }
		        PI[playerid][pQuest] = 5;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
			    ShowPlayerDialogEx(playerid, 1056, DIALOG_STYLE_MSGBOX, !"Gurama", !"{FFFFFF}Megobaro mismine. Mushaobit tu ar daigale, shentvis maqvs kidev erti samushao.\nAris samushao manqanebis nawilebis qarxanashi.\nShegidzlia miigo kargi fuli.\n\n{AFAFAF}Davaleba: Davaleba awwyot 20 cali avtonawili\nSachuqari: 5200$ da 1 ехр", !"Dadastureba", !"Uari");
			}
		}
		case 1055:
		{
		    if(!response)
				return 1;

	    	if(PI[playerid][pQuest] != 4)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Iyidet telephoni magaziashi 24/7");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Imisatvir rom monaxot magazia 24/7, gamoiyenet {FFFF00}/gps");
		}
		case 1056:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 5)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Aawyvet 20  cali avtonawili");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Gaemgzavret \"Avtonawilebi qarxanashi\" {FFFF00}(/gps -> Samusahoebi-> Avtonawilebi amwobi)");
		}
		case 1057:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 6)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Iyidet axali tansacmeli tansacmlis magaziashi");
		}
		case 1058:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 7)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}iyidet aqsesuari aqsesuarebi magaziashi");
		}
		case 1059:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 8)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestSaimon))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Gaemgzavret guramtan da daelaparaket mas");
		}
		case 1060:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 9)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Gaiaret 250 Nishnuli avtobusit");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Imisatvir rom moewyot samsaxurshi gaemgzavret uaxloes meriashi");
		}
		case 1061:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 10)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

			if(0 == PI[playerid][pMedCard])
			{
		        PI[playerid][pQuestStatus] = 1;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Miiget MedBarati saavadmyofoshi");
		        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Gaemgzavret uaxloes saavadmyofoshi");
	        }
	        else
	        {
			    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Tqven sheasrulet yvela davaleba");
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven miiget {33AA33}6200$");
	            GiveMoney(playerid, 6200, "Davaleba 10");
		        if(PI[playerid][pPromo])
		        {
		            new promoid = PI[playerid][pPromo]-1;
		            GivePromoMoney(playerid, promoid, 930);
		        }
		        PI[playerid][pQuest] = 11;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
                ShowPlayerDialogEx(playerid, 1062, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Zogjer shtati ar aris usaprtxo , amitom iyidet iaragi.\nImisatvis rom miigot licenzia tqven gchirdebam meriis tanamshromeli.\n Vfiqrob rom es ar waigebs did dros.\n\n{AFAFAF}Davaleba: Aigot iaragis licenzia meriashi\nSachuqari: 6600$", !"Dadastureba", !"Uari");
	        }
		}
		case 1062:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 11)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

			if(PI[playerid][pGunLic] != YES_LICENSE)
			{
		        PI[playerid][pQuestStatus] = 1;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Aiget licenzia meriashi");
		        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Gaemgzavret uaxloes meriashi");
	        }
	        else
	        {
			    SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Tqven sheasrulet yvela davaleba");
	            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Tqven miiget {33AA33}6600$");
	            GiveMoney(playerid, 6600, "Davaleba 11");
		        if(PI[playerid][pPromo])
		        {
		            new promoid = PI[playerid][pPromo]-1;
		            GivePromoMoney(playerid, promoid, 990);
		        }
		        PI[playerid][pQuest] = 12;
		        UpdatePlayerData(playerid, "Quest", PI[playerid][pQuest]);
		        PI[playerid][pQuestStatus] = 0;
		        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
		        PI[playerid][pQuestProcess] = 0;
		        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
		        ShowPlayerDialogEx(playerid, 1063, DIALOG_STYLE_MSGBOX, !"Batoni Rolandi", !"{FFFFFF}Axla shen ukve gaqvs licenzia magram es cotaa.\nLicensiis garda unda icode kargad srola.\nModi cota vivarjishot srolashi \"Udanbos Arwivi\" Tirshi.\n\n{AFAFAF}Davaleba: Isrolot 200 tyvia  \"Udabnos arwividan\" Tiris teritoriaze\nSachuqari: 7000$ da 15 tyvia \"Udabnos arwivis\"", !"Dadastureba", !"Uari");

	        }
		}
		case 1063:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 12)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Выстрелите 200 патрон из \"Пустынного орла\" на территории тира");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Подсказка] {FFFFFF}Отправляйтесь на \"Полигон для стрельбы\" {FFFF00}(/gps -> Важные места -> Полигон для стрельбы)");
		}
		case 1064:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 13)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
            SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Miiget monawileoba PaintBallshi");
            SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Gaemgzavret\"Gasartob centrshi\" {FFFF00}(/gps -> Mnishvnelovani adgilebi -> Gartobis centri)");
		}
		case 1065:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 14)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Gadaitanot 15 tona tvirti satvirto avtomobilit");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Gaemgzavret uaxloes meriashi samushaos dawyebisatvis");
		}
		case 1066:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 15)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Iyidet sachmeli nebismier kafeshi");
	        SendClientMessage(playerid, COLOR_WHITE, !"{FFC800}[Minishneba] {FFFFFF}Imisatvis rom naxot uaxloes kafe, gamoiyenet {FFFF00}/gps");
		}
		case 1067:
		{
		    if(!response)
		        return 1;

	    	if(PI[playerid][pQuest] != 16)
				return 1;

			if(0 == IsPlayerInDynamicArea(playerid, gQuestLinkoln))
			    return 1;

	        PI[playerid][pQuestStatus] = 1;
	        UpdatePlayerData(playerid, "QuestStatus", PI[playerid][pQuestStatus]);
	        PI[playerid][pQuestProcess] = 0;
	        UpdatePlayerData(playerid, "QuestProcess", PI[playerid][pQuestProcess]);
	        SendClientMessage(playerid, COLOR_WHITE, !"{DC143C}[QUEST] {FFFFFF}Moeywvet organizaciashi");
		}
	}
	return 1;
}

