/* project.c  -- simple app
*
* prompt: "say 'apple' or 'banana'."
* report: "You said <the utterance recognized>."
*/
#include <stdlib.h>	/* exit() */
#include <string.h>
#include <app.h>
#include <nl.h>
#include <recresult.h>
#include "nuance-config.h" 


#include <stdio.h>
#include <mysql.h>
#include <my_global.h>

#include "string_functions.h"
#include "sql_functions.h"
#include "date_time_functions.h"
#include "env_states.h"
#include "test_states.h"
#include "other_states.h"
#include "nuance_states.h"


#define _CRT_SECURE_NO_WARNINGS



//#include <tom.h>

int hardyness = 0;

char plantLocationStringArray[8][36];
char plantHabitStringArray[8][36];
char errorFixArray[8][24];
char errorStoreArray[8][24];
char errorEnvStringArray[8][24];

int numberStringArray[8];
void randomSuggestion(App *app);
void reverseSearchfn(App *app);

void foodfn(App *app) {
	AppSetGrammar(app, ".Choice");
	char buf[100];
	printf("\n I can help you find plants that can be used as substitutes for other foods. What foodstuff would you like to replace ? \n");
	AppAppendTTSPrompt(app, "I can help you find plants that can be used as substitutes for other foods. What foodstuff would you like to replace ?");
	NLGetStringSlotValue(AppGetNLResult(app), "fruit_said", buf, 100);

	if (!AppRecognize(app)) {
		printf("!AppRec\n");
		return;
	}
	if (!strcmp(buf, "egg_said")) {
		printf("You said egg egg egg egg.\n");
		AppAppendTTSPrompt(app, "You said egg egg egg egg.");
		goDoSQL(app, "food", "Egg");
	}

	AppGotoSelf(app);
}
void medicalfn(App *app) {
	AppSetGrammar(app, ".Choice");
	char buf[100];
	
	AppAppendTTSPrompt(app, "Tell me a little more about what you want help with.");



	//Sleep(10000);
	//AppGotoSelf(app);
	if (!AppRecognize(app)) {
		printf("!AppRec\n");
		return;
	}
	/*
	* Get the value of the "fruit" slot
	*/
	//AppAppendPrompt(app, "you_said.wav");


	NLGetStringSlotValue(AppGetNLResult(app), "condition_said", buf, 100);

	if (!strcmp(buf, "headache_said")) {
		//AppAppendPrompt(app, "apple.wav");
		AppAppendTTSPrompt(app, "I'm sorry to hear about your headache. Can I recommend an analgesic?");
		printf("You said you have a headache.\n");
		goDoAllTheSQL(app, "medicinal", "Analgesic");
	} else if (!strcmp(buf, "cold_said")) {
		//AppAppendPrompt(app, "apple.wav");
		AppAppendTTSPrompt(app, "you said food");
		printf("You said you have a cold. Here, grow a laxative.\n");
		goDoAllTheSQL(app, "medicinal", "Laxative");
	}
	else if (!strcmp(buf, "constipated_said")) {
		AppAppendTTSPrompt(app, "you said you need a massive shit");
		printf("Here, grow a laxative.\n");
		goDoAllTheSQL(app, "medicinal", "Laxative");
	}

	//exit(0);
	
	AppGotoSelf(app);
}

void AllInOneFn(App *app){
	char buf[100];

	AppSetGrammar(app, ".Choice");
	//AppAppendPrompt(app, "ask.wav");

	//AppAppendTTSPrompt(app, "would you prefer an apple or a banana? Ball bags.");


	AppAppendTTSPrompt(app, returnMySQLVersion()); 
	printf("\n%s", returnTime());
	printf("\n%s", returnDate());
	AppAppendTTSPrompt(app, returnTime());
	//AppAppendTTSPrompt(app, "So, you would like to buy a plant? Where abouts do you live?");
	AppAppendTTSPrompt(app, returnDate());
	
	
	//AppAppendTTSPrompt(app, returnTime());


	//Sleep(10000);
	//AppGotoSelf(app);
	if (!AppRecognize(app)) {
		printf("!AppRec\n");
		return;
	}
	/*
	* Get the value of the "fruit" slot
	*/
	//AppAppendPrompt(app, "you_said.wav");

	NLGetStringSlotValue(AppGetNLResult(app), "fruit_said", buf, 100);

	if (!strcmp(buf, "apple_said")) {
		//AppAppendPrompt(app, "apple.wav");
		AppAppendTTSPrompt(app, "you said apple");
		printf("You said you prefer an apple.\n");
	}
	else if (!strcmp(buf, "banana_said")) {
		//AppAppendPrompt(app, "banana.wav");
		AppAppendTTSPrompt(app, "you said banana");
		printf("You said you prefer a banana.\n");
	}
	else if (!strcmp(buf, "exit_said")) {
		printf("You said exit.\n");
		exit(0);
	}
	else {
		AppAppendTTSPrompt(app, "try again");
		//AppAppendPrompt(app, "try_again.wav");
		printf("You said you prefer a banana.\n");
	}

	AppGotoSelf(app);
}
//int main(int argc, char *argv[])
//{
//	App *app;
//	app = AppNew(&argc, argv);
//
//	if (app == NULL)
//		exit(-1);
//
//	AppCreateStateClass(app, "root", NULL, RootEntryFn, RootPostRecFn);
//	AppCreateState(app, "whole_shot", "root", AllInOneFn);
//	AppGo(app, "whole_shot");
//	return 0;
//}
int recognitionFlag = 0;
int firstFreeSpeak = 0;
void freeSpeakfn(App *app) {
	
	AppSetGrammar(app, ".Speak");
	
	
	if (firstFreeSpeak == 0) {
		AppAppendTTSPrompt(app, "How can I help?");
		firstFreeSpeak = 1;
	}
	else {
		AppAppendTTSPrompt(app, "What term would you like to add?");
	}

	if (!AppRecognize(app)) {
		printf("!AppRec\n");
		return;
	}

	int canopy_said = 2;
	int common_name_said = 2;
	int cultivar_said = 2;
	int cultivatedbeds_said = 2;
	int dappledshade_said = 2;
	int deepshade_said = 2;
	int eastwall_said = 2;
	int groundcover_said = 2;
	int habit_said = 2;
	int habitat_said = 2;
	int hardyness_said = 2;
	int hedge_said = 2;
	int hedgerow_said = 2;
	int height_said = 2;
	int latin_name_said = 2;
	int lawn_said = 2;
	int meadow_said = 2;
	int northwall_said = 2;
	int otherhabitats_said = 2;
	int pond_said = 2;
	int secondary_said = 2;
	int shade_said = 2;
	int shadyedge_said = 2;
	int southwall_said = 2;
	int sunnyedge_said = 2;
	int walls_said = 2;
	int westwall_said = 2;
	int width_said = 2;
	int woodlandgarden_said = 2;
	int shrub = 2;
	int annual = 2;
	int perennial = 2;
	int tree = 2;
	int perennial_climber = 2;
	int annual_slash_perennial = 2;
	int climber = 2;
	int fern = 2;
	int bulb = 2;
	int biennial = 2;
	int annual_slash_biennial = 2;
	int biennial_slash_perennial = 2;
	int bamboo = 2;
	int corm = 2;
	int lichen = 2;
	int annual_climber = 2;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////// PLANTLOCATION SLOTS    PLANTLOCATION SLOTS    PLANTLOCATION SLOTS    ///////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	NLGetIntSlotValue(AppGetNLResult(app), "canopy_said", &canopy_said);
	if (canopy_said == 1) {
		printf("%s\n", "You said canopy.");
		strcpy(plantLocationStringArray[envCounter], "Canopy");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "common_name_said", &common_name_said);
	if (common_name_said == 1) {
		printf("%s\n", "You said common name.");
		strcpy(plantLocationStringArray[envCounter], "Common name");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "cultivar_said", &cultivar_said);
	if (cultivar_said == 1) {
		printf("%s\n", "You said cultivar.");
		strcpy(plantLocationStringArray[envCounter], "Cultivar");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "cultivatedbeds_said", &cultivatedbeds_said);
	if (cultivatedbeds_said == 1) {
		printf("%s\n", "You said cultivated beds.");
		strcpy(plantLocationStringArray[envCounter], "CultivatedBeds");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "dappledshade_said", &dappledshade_said);
	if (dappledshade_said == 1) {
		printf("%s\n", "You said dappled shade.");
		strcpy(plantLocationStringArray[envCounter], "DappledShade");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "deepshade_said", &deepshade_said);
	if (deepshade_said == 1) {
		printf("%s\n", "You said deep shade.");
		strcpy(plantLocationStringArray[envCounter], "DeepShade");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "eastwall_said", &eastwall_said);
	if (eastwall_said == 1) {
		printf("%s\n", "You said east wall.");
		strcpy(plantLocationStringArray[envCounter], "EastWall");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "groundcover_said", &groundcover_said);
	if (groundcover_said == 1) {
		printf("%s\n", "You said ground cover.");
		strcpy(plantLocationStringArray[envCounter], "GroundCover");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "habit_said", &habit_said);
	if (habit_said == 1) {
		printf("%s\n", "You said habit.");
		strcpy(plantLocationStringArray[envCounter], "Habit");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "habitat_said", &habitat_said);
	if (habitat_said == 1) {
		printf("%s\n", "You said habitat.");
		strcpy(plantLocationStringArray[envCounter], "Habitat");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "hardyness_said", &hardyness_said);
	if (hardyness_said == 1) {
		printf("%s\n", "You said hardiness.");
		strcpy(plantLocationStringArray[envCounter], "Hardyness");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "hedge_said", &hedge_said);
	if (hedge_said == 1) {
		printf("%s\n", "You said hedge.");
		strcpy(plantLocationStringArray[envCounter], "Hedge");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "hedgerow_said", &hedgerow_said);
	if (hedgerow_said == 1) {
		printf("%s\n", "You said hedgerow.");
		strcpy(plantLocationStringArray[envCounter], "Hedgerow");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "height_said", &height_said);
	if (height_said == 1) {
		printf("%s\n", "You said height.");
		strcpy(plantLocationStringArray[envCounter], "Height");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "latin_name_said", &latin_name_said);
	if (latin_name_said == 1) {
		printf("%s\n", "You said latin name.");
		strcpy(plantLocationStringArray[envCounter], "Latin name");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "lawn_said", &lawn_said);
	if (lawn_said == 1) {
		printf("%s\n", "You said lawn.");
		strcpy(plantLocationStringArray[envCounter], "Lawn");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "meadow_said", &meadow_said);
	if (meadow_said == 1) {
		printf("%s\n", "You said meadow.");
		strcpy(plantLocationStringArray[envCounter], "Meadow");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "northwall_said", &northwall_said);
	if (northwall_said == 1) {
		printf("%s\n", "You said north wall.");
		strcpy(plantLocationStringArray[envCounter], "NorthWall");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "otherhabitats_said", &otherhabitats_said);
	if (otherhabitats_said == 1) {
		printf("%s\n", "You said other habitats.");
		strcpy(plantLocationStringArray[envCounter], "OtherHabitats");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "pond_said", &pond_said);
	if (pond_said == 1) {
		printf("%s\n", "You said pond.");
		strcpy(plantLocationStringArray[envCounter], "Pond");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "secondary_said", &secondary_said);
	if (secondary_said == 1) {
		printf("%s\n", "You said secondary.");
		strcpy(plantLocationStringArray[envCounter], "Secondary");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "shade_said", &shade_said);
	if (shade_said == 1) {
		printf("%s\n", "You said shade.");
		strcpy(plantLocationStringArray[envCounter], "Shade");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "shadyedge_said", &shadyedge_said);
	if (shadyedge_said == 1) {
		printf("%s\n", "You said shady edge.");
		strcpy(plantLocationStringArray[envCounter], "ShadyEdge");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "southwall_said", &southwall_said);
	if (southwall_said == 1) {
		printf("%s\n", "You said south wall.");
		strcpy(plantLocationStringArray[envCounter], "SouthWall");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "sunnyedge_said", &sunnyedge_said);
	if (sunnyedge_said == 1) {
		printf("%s\n", "You said sunny edge.");
		strcpy(plantLocationStringArray[envCounter], "SunnyEdge");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "walls_said", &walls_said);
	if (walls_said == 1) {
		printf("%s\n", "You said walls.");
		strcpy(plantLocationStringArray[envCounter], "Walls");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "westwall_said", &westwall_said);
	if (westwall_said == 1) {
		printf("%s\n", "You said west wall.");
		strcpy(plantLocationStringArray[envCounter], "WestWall");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "width_said", &width_said);
	if (width_said == 1) {
		printf("%s\n", "You said width.");
		strcpy(plantLocationStringArray[envCounter], "Width");
		envCounter = envCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "woodlandgarden_said", &woodlandgarden_said);
	if (woodlandgarden_said == 1) {
		printf("%s\n", "You said woodland garden.");
		strcpy(plantLocationStringArray[envCounter], "WoodlandGarden");
		envCounter = envCounter + 1;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////// HABIT SLOTS    HABIT SLOTS    HABIT SLOTS    //////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	NLGetIntSlotValue(AppGetNLResult(app), "shrub_said", &shrub);
	if (shrub == 1) {
		printf("%s\n", "You said Shrub.");
		strcpy(plantHabitStringArray[habitCounter], "Shrub");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "annual_said", &annual);
	if (annual == 1) {
		printf("%s\n", "You said Annual.");
		strcpy(plantHabitStringArray[habitCounter], "Annual");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "perennial_said", &perennial);
	if (perennial == 1) {
		printf("%s\n", "You said Perennial.");
		strcpy(plantHabitStringArray[habitCounter], "Perennial");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "tree_said", &tree);
	if (tree == 1) {
		printf("%s\n", "You said Tree.");
		strcpy(plantHabitStringArray[habitCounter], "Tree");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "perennial_climber_said", &perennial_climber);
	if (perennial_climber == 1) {
		printf("%s\n", "You said Perennial Climber.");
		strcpy(plantHabitStringArray[habitCounter], "Perennial Climber");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "annual_slash_perennial_said", &annual_slash_perennial);
	if (annual_slash_perennial == 1) {
		printf("%s\n", "You said Annual_slash_Perennial.");
		strcpy(plantHabitStringArray[habitCounter], "Annual_slash_Perennial");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "climber_said", &climber);
	if (climber == 1) {
		printf("%s\n", "You said Climber.");
		strcpy(plantHabitStringArray[habitCounter], "Climber");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "fern_said", &fern);
	if (fern == 1) {
		printf("%s\n", "You said Fern.");
		strcpy(plantHabitStringArray[habitCounter], "Fern");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "bulb_said", &bulb);
	if (bulb == 1) {
		printf("%s\n", "You said Bulb.");
		strcpy(plantHabitStringArray[habitCounter], "Bulb");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "biennial_said", &biennial);
	if (biennial == 1) {
		printf("%s\n", "You said Biennial.");
		strcpy(plantHabitStringArray[habitCounter], "Biennial");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "annual_slash_biennial_said", &annual_slash_biennial);
	if (annual_slash_biennial == 1) {
		printf("%s\n", "You said Annual_slash_Biennial.");
		strcpy(plantHabitStringArray[habitCounter], "Annual_slash_Biennial");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "biennial_slash_perennial_said", &biennial_slash_perennial);
	if (biennial_slash_perennial == 1) {
		printf("%s\n", "You said Biennial_slash_Perennial.");
		strcpy(plantHabitStringArray[habitCounter], "Biennial_slash_Perennial");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "bamboo_said", &bamboo);
	if (bamboo == 1) {
		printf("%s\n", "You said Bamboo.");
		strcpy(plantHabitStringArray[habitCounter], "Bamboo");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "corm_said", &corm);
	if (corm == 1) {
		printf("%s\n", "You said Corm.");
		strcpy(plantHabitStringArray[habitCounter], "Corm");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "lichen_said", &lichen);
	if (lichen == 1) {
		printf("%s\n", "You said Lichen.");
		strcpy(plantHabitStringArray[habitCounter], "Lichen");
		habitCounter = habitCounter + 1;
	}
	NLGetIntSlotValue(AppGetNLResult(app), "annual_climber_said", &annual_climber);
	if (annual_climber == 1) {
		printf("%s\n", "You said Annual Climber.");
		strcpy(plantHabitStringArray[habitCounter], "Annual Climber");
		habitCounter = habitCounter + 1;
	}
	
	int hardy = 0;
	if (NLGetIntSlotValue(AppGetNLResult(app), "hardy_said", &hardy) != 119){
		hardyness = hardy;
		printf("Hardy said.\n");
		printf("Hardy level: %d\n", hardy);
		}
	
	//int width = 0;
	//if (NLGetIntSlotValue(AppGetNLResult(app), "width_said", &width) != 119) {
	//	global_width = width;
	//	printf("Width said.");
	//}

	//int height = 0;
	//if (NLGetIntSlotValue(AppGetNLResult(app), "height", &height) != 119) {
	//	global_height = height;
	//	printf("Width said.");
	//}
	/*
	(tall) {
		<height_said 3>
	}
	(high) {
		<height_said 3>
	}
	(medium height) {
		<height_said 2>
	}
	(normal height) {
		<height_said 2>
	}
	(short) {
		<height_said 1>
	}


	; width
	(very wide) {
		<width_said 3>
	}
	(extra wide) {
		<width_said 3>
	}
	(wide) {
		<width_said 2>
	}
	(slim) {
		<width_said 1>
	}
	(thin) {
		<width_said 1>
	}
	]
	*/

	char buf[100];
	(NLGetStringSlotValue(AppGetNLResult(app), "suggestion_said", buf, 100));
	if (!strcmp("suggestion", buf)) {
		randomSuggestion(app);
		AppGotoSelf(app);
	}

	if ((AppGetRecognitionStage(app) == 4)){//&& (recognitionFlag == 1)) {
		AppGoto(app, "envCheck");
	}

/*
	if (!strcmp(buf, "canopy_said")) {
		AppAppendTTSPrompt(app, "You said canopy.");
		printf("You said canopy.\n");
		plantLocationStringArray[envCounter] = "Canopy";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "common_name_said")) {
		AppAppendTTSPrompt(app, "You said common name.");
		printf("You said common_name_said.\n");
		plantLocationStringArray[envCounter] = "Common name";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "cultivar_said")) {
		AppAppendTTSPrompt(app, "You said cultivar.");
		printf("You said cultivar_said.\n");
		plantLocationStringArray[envCounter] = "Cultivar";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "cultivatedbeds_said")) {
		AppAppendTTSPrompt(app, "You said cultivated beds.");
		printf("You said cultivatedbeds_said.\n");
		plantLocationStringArray[envCounter] = "CultivatedBeds";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "dappledshade_said")) {
		AppAppendTTSPrompt(app, "You said dappled shade.");
		printf("You said dappledshade_said.\n");
		plantLocationStringArray[envCounter] = "DappledShade";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "deepshade_said")) {
		AppAppendTTSPrompt(app, "You said deep shade.");
		printf("You said deepshade_said.\n");
		plantLocationStringArray[envCounter] = "DeepShade";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "eastwall_said")) {
		AppAppendTTSPrompt(app, "You said east wall.");
		printf("You said eastwall_said.\n");
		plantLocationStringArray[envCounter] = "EastWall";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "groundcover_said")) {
		AppAppendTTSPrompt(app, "You said ground cover.");
		printf("You said groundcover_said.\n");
		plantLocationStringArray[envCounter] = "GroundCover";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "habit_said")) {
		AppAppendTTSPrompt(app, "You said habit.");
		printf("You said habit_said.\n");
		plantLocationStringArray[envCounter] = "Habit";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "habitat_said")) {
		AppAppendTTSPrompt(app, "You said habitat.");
		printf("You said habitat_said.\n");
		plantLocationStringArray[envCounter] = "Habitat";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "hardyness_said")) {
		AppAppendTTSPrompt(app, "You said hardiness.");
		printf("You said hardyness_said.\n");
		plantLocationStringArray[envCounter] = "Hardyness";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "hedge_said")) {
		AppAppendTTSPrompt(app, "You said hedge.");
		printf("You said hedge_said.\n");
		plantLocationStringArray[envCounter] = "Hedge";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "hedgerow_said")) {
		AppAppendTTSPrompt(app, "You said hedgerow.");
		printf("You said hedgerow_said.\n");
		plantLocationStringArray[envCounter] = "Hedgerow";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "height_said")) {
		AppAppendTTSPrompt(app, "You said height.");
		printf("You said height_said.\n");
		plantLocationStringArray[envCounter] = "Height";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "latin_name_said")) {
		AppAppendTTSPrompt(app, "You said latin name.");
		printf("You said latin_name_said.\n");
		plantLocationStringArray[envCounter] = "Latin name";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "lawn_said")) {
		AppAppendTTSPrompt(app, "You said lawn.");
		printf("You said lawn_said.\n");
		plantLocationStringArray[envCounter] = "Lawn";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "meadow_said")) {
		AppAppendTTSPrompt(app, "You said meadow.");
		printf("You said meadow_said.\n");
		plantLocationStringArray[envCounter] = "Meadow";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "northwall_said")) {
		AppAppendTTSPrompt(app, "You said north wall.");
		printf("You said northwall_said.\n");
		plantLocationStringArray[envCounter] = "NorthWall";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "otherhabitats_said")) {
		AppAppendTTSPrompt(app, "You said other habitats.");
		printf("You said otherhabitats_said.\n");
		plantLocationStringArray[envCounter] = "OtherHabitats";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "pond_said")) {
		AppAppendTTSPrompt(app, "You said pond.");
		printf("You said pond_said.\n");
		plantLocationStringArray[envCounter] = "Pond";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "secondary_said")) {
		AppAppendTTSPrompt(app, "You said secondary.");
		printf("You said secondary_said.\n");
		plantLocationStringArray[envCounter] = "Secondary";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "shade_said")) {
		AppAppendTTSPrompt(app, "You said shade.");
		printf("You said shade_said.\n");
		plantLocationStringArray[envCounter] = "Shade";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "shadyedge_said")) {
		AppAppendTTSPrompt(app, "You said shady edge.");
		printf("You said shadyedge_said.\n");
		plantLocationStringArray[envCounter] = "ShadyEdge";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "southwall_said")) {
		AppAppendTTSPrompt(app, "You said south wall.");
		printf("You said southwall_said.\n");
		plantLocationStringArray[envCounter] = "SouthWall";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "sunnyedge_said")) {
		AppAppendTTSPrompt(app, "You said sunny edge.");
		printf("You said sunnyedge_said.\n");
		plantLocationStringArray[envCounter] = "SunnyEdge";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "walls_said")) {
		AppAppendTTSPrompt(app, "You said walls.");
		printf("You said walls_said.\n");
		plantLocationStringArray[envCounter] = "Walls";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "westwall_said")) {
		AppAppendTTSPrompt(app, "You said west wall.");
		printf("You said westwall_said.\n");
		plantLocationStringArray[envCounter] = "WestWall";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "width_said")) {
		AppAppendTTSPrompt(app, "You said width.");
		printf("You said width_said.\n");
		plantLocationStringArray[envCounter] = "Width";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else if (!strcmp(buf, "woodlandgarden_said")) {
		AppAppendTTSPrompt(app, "You said woodland garden.");
		printf("You said woodlandgarden_said.\n");
		plantLocationStringArray[envCounter] = "WoodlandGarden";
		envCounter = envCounter + 1;
		AppGoto(app, "env2");
	}
	else {
		AppAppendTTSPrompt(app, "Try again.");
	}*/
	
	AppGotoSelf(app);
}



int main(int argc, char *argv[])
{
	printf("test");
	//NuanceStatus statusP;
	//NuanceConfigBuildFromCommandLine(&argc, argv, 1, *statusP);

	App *app;
	
	app = AppNew(&argc, argv);
	
	
	//goDoAllTheSQL(app, "edible", "egg");

	if (app == NULL) {
		printf("What's going on here then?");
		sleep(2);
		exit(-1);
	}
	AppCreateStateClass(app, "root", NULL, RootEntryFn, RootPostRecFn);
	AppCreateState(app, "start", "root", startfn);
	
	AppCreateState(app, "askLocale", "root", askLocalefn);
	AppCreateState(app, "changeLocale", "root", changeLocalefn);

	AppCreateState(app, "greeting", "root", greetfn);
	


	AppCreateState(app, "whole_shot", "root", AllInOneFn);
	//AppCreateState(app, "first_q", "root", firstQfn);
	
	AppCreateState(app, "food", "root", foodfn);
	AppCreateState(app, "medicine", "root", medicalfn);
	AppCreateState(app, "environment", "root", environmentfn);
	AppCreateState(app, "env2", "root", environmentfn3);
	AppCreateState(app, "env2PandH", "root", envPandHfn);
	
	AppCreateState(app, "test", "root", testfn);
	AppCreateState(app, "zeroMatchesEnv", "root", envZeroMatches);
	AppCreateState(app, "envResultsBuf", "root", envResultsBufFn);
	AppCreateState(app, "envResults", "root", envResultsFn);

	AppCreateState(app, "envPreCheck", "root", envPreCheckfn);
	

	AppCreateState(app, "freeSpeak", "root", freeSpeakfn);
	AppCreateState(app, "envErrorFix", "root", envErrorFixfn);
	AppCreateState(app, "envCheck", "root", envCheckfn);
	AppCreateState(app, "envCheck1", "root", envCheckfn1);
	AppCreateState(app, "reverseSearch", "root", reverseSearchfn);

	//AppGo(app, "environment");
	AppGo(app, "reverseSearch");
	//AppGo(app, "freeSpeak");
	//AppGo(app, "test");
	return 0;
}



//
//void tamplateFN(App *app) {
//
//	AppSetGrammar(app, ".");
//	char buf[100];
//
//	AppAppendTTSPrompt(app, ".");
//	
//	if (!AppRecognize(app)) {
//		printf("!AppRec\n");
//		return;
//	}
//	NLGetStringSlotValue(AppGetNLResult(app), ".", buf, 100);
//
//	if (!strcmp(buf, "")) {
//		AppAppendTTSPrompt(app, ".");
//		printf("You said  .\n");
//		AppGoto("");
//	}
//	else if (!strcmp(buf, "")) {
//		AppAppendTTSPrompt(app, ".");
//		printf("You said  .\n");
//		AppGoto("");
//	}
//
//	AppGotoSelf(app);
//}

int firstRandomSuggestion = 0;
const char *a[18][35];
void randomSuggestion(App *app) {
	//a.append("Hardyness");
	//a.append("Latin name");
	if (firstRandomSuggestion == 0) {
		strcpy(a[0], "Canopy");
		strcpy(a[1], "Cultivated Beds");
		strcpy(a[2], "Dappled Shade");
		strcpy(a[3], "Deep Shade");
		strcpy(a[4], "East Wall");
		strcpy(a[5], "Ground Cover");
		strcpy(a[6], "Habitat");
		strcpy(a[7], "Hedge");
		strcpy(a[8], "Hedgerow");
		strcpy(a[9], "Lawn");
		strcpy(a[10], "Meadow");
		strcpy(a[11], "North Wall");
		strcpy(a[12], "Pond");
		strcpy(a[13], "Shade");
		strcpy(a[14], "Shady Edge");
		strcpy(a[15], "South Wall");
		strcpy(a[16], "Sunny Edge");
		strcpy(a[17], "West Wall");
		strcpy(a[18], "Woodland Garden");
		firstRandomSuggestion = 1;
	}

	printf("Suggestions: \n");
	srand((unsigned)time(NULL));
//	randomNumber = rand() % 10;
	AppAppendTTSPrompt(app, "Why not try searching by where the plant will grow, such as ");
	int randomMemory = 0;
	int min = 0; int max = 18; 
	for (int i = 0; i < 2; i++) {
		char buf10[150];
		int randomNumber = (rand() % (max + 1 - min)) + min;
		while (randomNumber == randomMemory) {
			randomNumber = (rand() % (max + 1 - min)) + min;
		}
		//printf("random number = %d\n", randomNumber);
		printf("%s\n", a[randomNumber]);
		//sprintf(buf10, "SELECT * FROM `plantlocations` WHERE `%s`=1", a[randomNumber]);
		AppAppendTTSPrompt(app, a[randomNumber]);
		//SQLspeakQuery(app, buf10);
		AppAppendSilence(app, 150);
		AppAppendTTSPrompt(app, " or ");
		randomMemory = randomNumber;
	}
	AppAppendTTSPrompt(app, " you could try searching by type of plant, like ");
	SQLspeakQueryResultsOnly(app, "SELECT `Habit` FROM `plantlocations` ORDER BY RAND() LIMIT 1");
	AppAppendTTSPrompt(app, " or ");
	SQLspeakQueryResultsOnly(app, "SELECT `Habit` FROM `plantlocations` ORDER BY RAND() LIMIT 1");
	if (!AppRecognize(app)) {
		printf("!AppRec\n");
		return;
	}
	//SELECT `Habit` FROM `plantlocations` ORDER BY RAND() LIMIT 1

}

const char *commonNameArray[3129][31];
int firstCommonNameRun = 0;
void reverseSearchfn(App *app) {
if (firstCommonNameRun == 0){
	strcpy(commonNameArray[0], "Okra");
	strcpy(commonNameArray[1], "Aibika");
	strcpy(commonNameArray[2], "Musk mallow");
	strcpy(commonNameArray[3], "Silver fir");
	strcpy(commonNameArray[4], "Red fir");
	strcpy(commonNameArray[5], "Balsam fir");
	strcpy(commonNameArray[6], "Grecian fir");
	strcpy(commonNameArray[7], "Colorado fir");
	strcpy(commonNameArray[8], "Momi fir");
	strcpy(commonNameArray[9], "She balsam");
	strcpy(commonNameArray[10], "Grand fir");
	strcpy(commonNameArray[11], "Nikko fir");
	strcpy(commonNameArray[12], "Subalpine fir");
	strcpy(commonNameArray[13], "Californian red fir");
	strcpy(commonNameArray[14], "Caucasian fir");
	strcpy(commonNameArray[15], "West Himalayan fir");
	strcpy(commonNameArray[16], "Noble fir");
	strcpy(commonNameArray[17], "Sacred fir");
	strcpy(commonNameArray[18], "Siberian fir");
	strcpy(commonNameArray[19], "Himalayan fir");
	strcpy(commonNameArray[20], "Flaky fir");
	strcpy(commonNameArray[21], "Sand verbena");
	strcpy(commonNameArray[22], "Trailing abutilon");
	strcpy(commonNameArray[23], "China jute");
	strcpy(commonNameArray[24], "Mulga acacia");
	strcpy(commonNameArray[25], "Wiry wattle");
	strcpy(commonNameArray[26], "Knife-leaf wattle");
	strcpy(commonNameArray[27], "Mimosa");
	strcpy(commonNameArray[28], "Green wattle");
	strcpy(commonNameArray[29], "Sweet acacia");
	strcpy(commonNameArray[30], "Sidney golden wattle");
	strcpy(commonNameArray[31], "Blackwood");
	strcpy(commonNameArray[32], "Kangaroo thorn");
	strcpy(commonNameArray[33], "Silver wattle");
	strcpy(commonNameArray[34], "Golden wattle");
	strcpy(commonNameArray[35], "Blue-leaved wattle");
	strcpy(commonNameArray[36], "Coastal wattle");
	strcpy(commonNameArray[37], "Prickly Moses");
	strcpy(commonNameArray[38], "Pirri-pirri bur");
	strcpy(commonNameArray[39], "Bear's breeches");
	strcpy(commonNameArray[40], "Feijoa");
	strcpy(commonNameArray[41], "Field maple");
	strcpy(commonNameArray[42], "Hornbeam maple");
	strcpy(commonNameArray[43], "Vine maple");
	strcpy(commonNameArray[44], "Hawthorn-leaved maple");
	strcpy(commonNameArray[45], "Amur maple");
	strcpy(commonNameArray[46], "Rock maple");
	strcpy(commonNameArray[47], "Oregon maple");
	strcpy(commonNameArray[48], "Box elder");
	strcpy(commonNameArray[49], "Japanese maple");
	strcpy(commonNameArray[50], "Moosewood");
	strcpy(commonNameArray[51], "Norway maple");
	strcpy(commonNameArray[52], "Sycamore");
	strcpy(commonNameArray[53], "Red maple");
	strcpy(commonNameArray[54], "Silver maple");
	strcpy(commonNameArray[55], "Sugar maple");
	strcpy(commonNameArray[56], "Big-tooth maple");
	strcpy(commonNameArray[57], "Black maple");
	strcpy(commonNameArray[58], "Mountain maple");
	strcpy(commonNameArray[59], "Tatarian maple");
	strcpy(commonNameArray[60], "Mace");
	strcpy(commonNameArray[61], "Musk milfoil");
	strcpy(commonNameArray[62], "Yarrow");
	strcpy(commonNameArray[63], "Sneeze-wort");
	strcpy(commonNameArray[64], "Indian millet");
	strcpy(commonNameArray[65], "Alpine calamint");
	strcpy(commonNameArray[66], "Basil thyme");
	strcpy(commonNameArray[67], "Wild Spaniard");
	strcpy(commonNameArray[68], "Speargrass");
	strcpy(commonNameArray[69], "Wolfsbane");
	strcpy(commonNameArray[70], "Wolfbane");
	strcpy(commonNameArray[71], "Aconite");
	strcpy(commonNameArray[72], "Sweet flag");
	strcpy(commonNameArray[73], "White baneberry");
	strcpy(commonNameArray[74], "Baneberry");
	strcpy(commonNameArray[75], "Herb Christopher");
	strcpy(commonNameArray[76], "Tara vine");
	strcpy(commonNameArray[77], "Kiwi fruit");
	strcpy(commonNameArray[78], "Red kiwi");
	strcpy(commonNameArray[79], "Silver vine");
	strcpy(commonNameArray[80], "Greasewood");
	strcpy(commonNameArray[81], "Maidenhair fern");
	strcpy(commonNameArray[82], "Pheasant's eye");
	strcpy(commonNameArray[83], "Ground elder");
	strcpy(commonNameArray[84], "Californian buckeye");
	strcpy(commonNameArray[85], "Chinese horse chestnut");
	strcpy(commonNameArray[86], "Sweet buckeye");
	strcpy(commonNameArray[87], "Ohio buckeye");
	strcpy(commonNameArray[88], "Horse chestnut");
	strcpy(commonNameArray[89], "Indian horse chestnut");
	strcpy(commonNameArray[90], "Red buckeye");
	strcpy(commonNameArray[91], "Japanese horse chestnut");
	strcpy(commonNameArray[92], "Red horse chestnut");
	strcpy(commonNameArray[93], "Fool's parsley");
	strcpy(commonNameArray[94], "Hoary balm of gilead");
	strcpy(commonNameArray[95], "Anise hyssop");
	strcpy(commonNameArray[96], "Mexican giant hyssop");
	strcpy(commonNameArray[97], "Korean mint");
	strcpy(commonNameArray[98], "Giant hyssop");
	strcpy(commonNameArray[99], "Century plant");
	strcpy(commonNameArray[100], "Ageratum");
	strcpy(commonNameArray[101], "Mountain dandelion");
	strcpy(commonNameArray[102], "Agrimony");
	strcpy(commonNameArray[103], "Corncockle");
	strcpy(commonNameArray[104], "Upland bent");
	strcpy(commonNameArray[105], "Tree of heaven");
	strcpy(commonNameArray[106], "Ground pine");
	strcpy(commonNameArray[107], "Bugle");
	strcpy(commonNameArray[108], "Akebia");
	strcpy(commonNameArray[109], "Hollyhock");
	strcpy(commonNameArray[110], "Alpine lady's mantle");
	strcpy(commonNameArray[111], "Lady's mantle");
	strcpy(commonNameArray[112], "Unicorn root");
	strcpy(commonNameArray[113], "Japan wood-oil tree");
	strcpy(commonNameArray[114], "Chinese wood-oil tree");
	strcpy(commonNameArray[115], "Manna tree");
	strcpy(commonNameArray[116], "Camel thorn");
	strcpy(commonNameArray[117], "Great water plantain");
	strcpy(commonNameArray[118], "Alkanet");
	strcpy(commonNameArray[119], "Garlic mustard");
	strcpy(commonNameArray[120], "Wild leek");
	strcpy(commonNameArray[121], "Babbington's leek");
	strcpy(commonNameArray[122], "Mouse garlic");
	strcpy(commonNameArray[123], "Aspen onion");
	strcpy(commonNameArray[124], "Wild garlic");
	strcpy(commonNameArray[125], "Keeled garlic");
	strcpy(commonNameArray[126], "Onion");
	strcpy(commonNameArray[127], "Potato onion");
	strcpy(commonNameArray[128], "Shallot");
	strcpy(commonNameArray[129], "Tree onion");
	strcpy(commonNameArray[130], "Nodding onion");
	strcpy(commonNameArray[131], "Rakkyo");
	strcpy(commonNameArray[132], "Prairie onion");
	strcpy(commonNameArray[133], "Welsh onion");
	strcpy(commonNameArray[134], "Egyptian leek");
	strcpy(commonNameArray[135], "Wild onion");
	strcpy(commonNameArray[136], "Daffodil garlic");
	strcpy(commonNameArray[137], "Twistedleaf garlic");
	strcpy(commonNameArray[138], "Field garlic");
	strcpy(commonNameArray[139], "Few-flowered leek");
	strcpy(commonNameArray[140], "Leek");
	strcpy(commonNameArray[141], "Chinese chives");
	strcpy(commonNameArray[142], "Rosy garlic");
	strcpy(commonNameArray[143], "Garlic");
	strcpy(commonNameArray[144], "Serpent garlic");
	strcpy(commonNameArray[145], "Chives");
	strcpy(commonNameArray[146], "Giant chives");
	strcpy(commonNameArray[147], "Rocambole");
	strcpy(commonNameArray[148], "German garlic");
	strcpy(commonNameArray[149], "Round-headed leek");
	strcpy(commonNameArray[150], "Miyama-rakkyo");
	strcpy(commonNameArray[151], "Three-cornered leek");
	strcpy(commonNameArray[152], "Garlic chives");
	strcpy(commonNameArray[153], "One-leaved onion");
	strcpy(commonNameArray[154], "Ramsons");
	strcpy(commonNameArray[155], "Swamp onion");
	strcpy(commonNameArray[156], "Alpine leek");
	strcpy(commonNameArray[157], "Crow garlic");
	strcpy(commonNameArray[158], "Jimbur");
	strcpy(commonNameArray[159], "Italian alder");
	strcpy(commonNameArray[160], "Alder");
	strcpy(commonNameArray[161], "Grey alder");
	strcpy(commonNameArray[162], "White alder");
	strcpy(commonNameArray[163], "Red alder");
	strcpy(commonNameArray[164], "Speckled alder");
	strcpy(commonNameArray[165], "Smooth alder");
	strcpy(commonNameArray[166], "Sitka alder");
	strcpy(commonNameArray[167], "Mountain alder");
	strcpy(commonNameArray[168], "Aloe vera");
	strcpy(commonNameArray[169], "Lemon verbena");
	strcpy(commonNameArray[170], "Marsh mallow");
	strcpy(commonNameArray[171], "Love lies bleeding");
	strcpy(commonNameArray[172], "Purple amaranth");
	strcpy(commonNameArray[173], "Rough pigweed");
	strcpy(commonNameArray[174], "Prince's feather");
	strcpy(commonNameArray[175], "Ataco");
	strcpy(commonNameArray[176], "Pigweed");
	strcpy(commonNameArray[177], "Amaranthus");
	strcpy(commonNameArray[178], "Calalu");
	strcpy(commonNameArray[179], "Roman wormwood");
	strcpy(commonNameArray[180], "Giant ragweed");
	strcpy(commonNameArray[181], "Saskatoon");
	strcpy(commonNameArray[182], "Downy serviceberry");
	strcpy(commonNameArray[183], "Korean juneberry");
	strcpy(commonNameArray[184], "Juneberry");
	strcpy(commonNameArray[185], "Allegheny shadberry");
	strcpy(commonNameArray[186], "Apple serviceberry");
	strcpy(commonNameArray[187], "Southern juneberry");
	strcpy(commonNameArray[188], "Snowy mespilus");
	strcpy(commonNameArray[189], "Quebec berry");
	strcpy(commonNameArray[190], "Marram grass");
	strcpy(commonNameArray[191], "Beach grass");
	strcpy(commonNameArray[192], "Lead plant");
	strcpy(commonNameArray[193], "False indigo");
	strcpy(commonNameArray[194], "Elephant yam");
	strcpy(commonNameArray[195], "Devil's tongue");
	strcpy(commonNameArray[196], "Pepper vine");
	strcpy(commonNameArray[197], "Hog peanut");
	strcpy(commonNameArray[198], "Pyramidal orchid");
	strcpy(commonNameArray[199], "Mount Atlas daisy");
	strcpy(commonNameArray[200], "Scarlet pimpernel");
	strcpy(commonNameArray[201], "Pearly everlasting");
	strcpy(commonNameArray[202], "Anchusa");
	strcpy(commonNameArray[203], "Bog rosemary");
	strcpy(commonNameArray[204], "Marsh andromeda");
	strcpy(commonNameArray[205], "Broom sedge");
	strcpy(commonNameArray[206], "Rock jasmine");
	strcpy(commonNameArray[207], "Wood anemone");
	strcpy(commonNameArray[208], "Wind flower");
	strcpy(commonNameArray[209], "Rue-anemone");
	strcpy(commonNameArray[210], "Yerba mansa");
	strcpy(commonNameArray[211], "Dill");
	strcpy(commonNameArray[212], "Angelica");
	strcpy(commonNameArray[213], "Chinese angelica");
	strcpy(commonNameArray[214], "Wild angelica");
	strcpy(commonNameArray[215], "Catsfoot");
	strcpy(commonNameArray[216], "Corn chamomile");
	strcpy(commonNameArray[217], "Mayweed");
	strcpy(commonNameArray[218], "Yellow camomile");
	strcpy(commonNameArray[219], "Sweet vernal grass");
	strcpy(commonNameArray[220], "Chervil");
	strcpy(commonNameArray[221], "Cow parsley");
	strcpy(commonNameArray[222], "Kidney vetch");
	strcpy(commonNameArray[223], "Snapdragon");
	strcpy(commonNameArray[224], "Parsley piert");
	strcpy(commonNameArray[225], "Ground nut");
	strcpy(commonNameArray[226], "Wild celery");
	strcpy(commonNameArray[227], "Celery");
	strcpy(commonNameArray[228], "Celeriac");
	strcpy(commonNameArray[229], "Putty root");
	strcpy(commonNameArray[230], "Dogbane");
	strcpy(commonNameArray[231], "Indian hemp");
	strcpy(commonNameArray[232], "Water hawthorn");
	strcpy(commonNameArray[233], "Columbine");
	strcpy(commonNameArray[234], "Wild columbine");
	strcpy(commonNameArray[235], "Thale cress");
	strcpy(commonNameArray[236], "Alpine rock cress");
	strcpy(commonNameArray[237], "Rock cress");
	strcpy(commonNameArray[238], "Peanut");
	strcpy(commonNameArray[239], "Chinese angelica tree");
	strcpy(commonNameArray[240], "Manchurian spikenard");
	strcpy(commonNameArray[241], "Udo");
	strcpy(commonNameArray[242], "Angelica tree");
	strcpy(commonNameArray[243], "Bristly sarsaparilla");
	strcpy(commonNameArray[244], "Manchurian angelica tree");
	strcpy(commonNameArray[245], "Wild sarsaparilla");
	strcpy(commonNameArray[246], "American spikenard");
	strcpy(commonNameArray[247], "Sakhalin spikenard");
	strcpy(commonNameArray[248], "Hercule's club");
	strcpy(commonNameArray[249], "Monkey-puzzle tree");
	strcpy(commonNameArray[250], "Bunya-bunya");
	strcpy(commonNameArray[251], "Cruel plant");
	strcpy(commonNameArray[252], "Grecian strawberry tree");
	strcpy(commonNameArray[253], "Arizona maderone");
	strcpy(commonNameArray[254], "Canary madrona");
	strcpy(commonNameArray[255], "Madrona");
	strcpy(commonNameArray[256], "Texas madrone");
	strcpy(commonNameArray[257], "Strawberry tree");
	strcpy(commonNameArray[258], "Great burdock");
	strcpy(commonNameArray[259], "Burdock");
	strcpy(commonNameArray[260], "Alpine bearberry");
	strcpy(commonNameArray[261], "Hairy manzanita");
	strcpy(commonNameArray[262], "Bigberry manzanita");
	strcpy(commonNameArray[263], "Manzanita");
	strcpy(commonNameArray[264], "Pine-mat manzanita");
	strcpy(commonNameArray[265], "Greenleaf manzanita");
	strcpy(commonNameArray[266], "Downy manzanita");
	strcpy(commonNameArray[267], "Bearberry");
	strcpy(commonNameArray[268], "Coralberry");
	strcpy(commonNameArray[269], "Marlberry");
	strcpy(commonNameArray[270], "Prickly poppy");
	strcpy(commonNameArray[271], "Jack in the pulpit");
	strcpy(commonNameArray[272], "Friar's cowl");
	strcpy(commonNameArray[273], "Birthwort");
	strcpy(commonNameArray[274], "Virginia snakeroot");
	strcpy(commonNameArray[275], "Snakeroot");
	strcpy(commonNameArray[276], "Dutchman's pipe");
	strcpy(commonNameArray[277], "Macqui");
	strcpy(commonNameArray[278], "Macachi");
	strcpy(commonNameArray[279], "Thrift");
	strcpy(commonNameArray[280], "Horseradish");
	strcpy(commonNameArray[281], "Mountain tobacco");
	strcpy(commonNameArray[282], "Arnica");
	strcpy(commonNameArray[283], "Red chokeberry");
	strcpy(commonNameArray[284], "Black chokeberry");
	strcpy(commonNameArray[285], "Purple chokeberry");
	strcpy(commonNameArray[286], "Arracacha");
	strcpy(commonNameArray[287], "Southernwood");
	strcpy(commonNameArray[288], "Wormwood");
	strcpy(commonNameArray[289], "Sweet wormwood");
	strcpy(commonNameArray[290], "Field southernwood");
	strcpy(commonNameArray[291], "Cina");
	strcpy(commonNameArray[292], "Russian tarragon");
	strcpy(commonNameArray[293], "Tarragon");
	strcpy(commonNameArray[294], "Sand sage");
	strcpy(commonNameArray[295], "Fringed wormwood");
	strcpy(commonNameArray[296], "Glacier wormwood");
	strcpy(commonNameArray[297], "White mugwort");
	strcpy(commonNameArray[298], "White sage");
	strcpy(commonNameArray[299], "Sea wormwood");
	strcpy(commonNameArray[300], "Beach wormwood");
	strcpy(commonNameArray[301], "Sage brush");
	strcpy(commonNameArray[302], "Alpine wormwood");
	strcpy(commonNameArray[303], "Mugwort");
	strcpy(commonNameArray[304], "Glasswort");
	strcpy(commonNameArray[305], "Pale vanilla lily");
	strcpy(commonNameArray[306], "Small vanilla lily");
	strcpy(commonNameArray[307], "Cuckoo pint");
	strcpy(commonNameArray[308], "Goat's beard");
	strcpy(commonNameArray[309], "Cane reed");
	strcpy(commonNameArray[310], "Giant reed");
	strcpy(commonNameArray[311], "Snake root");
	strcpy(commonNameArray[312], "Asarabacca");
	strcpy(commonNameArray[313], "Bedstraw milkweed");
	strcpy(commonNameArray[314], "Purple silkweed");
	strcpy(commonNameArray[315], "Swamp milkweed");
	strcpy(commonNameArray[316], "Low milkweed");
	strcpy(commonNameArray[317], "Purple milkweed");
	strcpy(commonNameArray[318], "Red silkweed");
	strcpy(commonNameArray[319], "Showy milkweed");
	strcpy(commonNameArray[320], "Common milkweed");
	strcpy(commonNameArray[321], "Pleurisy root");
	strcpy(commonNameArray[322], "Green milkweed");
	strcpy(commonNameArray[323], "Papaw");
	strcpy(commonNameArray[324], "Rooibos");
	strcpy(commonNameArray[325], "Chinese asparagus");
	strcpy(commonNameArray[326], "Fern asparagus");
	strcpy(commonNameArray[327], "Asparagus");
	strcpy(commonNameArray[328], "Shatavari");
	strcpy(commonNameArray[329], "Squinancy wort");
	strcpy(commonNameArray[330], "Dyer's woodruff");
	strcpy(commonNameArray[331], "King's spear");
	strcpy(commonNameArray[332], "Asphodel");
	strcpy(commonNameArray[333], "Aspidistra");
	strcpy(commonNameArray[334], "Black spleenwort");
	strcpy(commonNameArray[335], "Hen and chicken fern");
	strcpy(commonNameArray[336], "Scale fern");
	strcpy(commonNameArray[337], "Wall rue");
	strcpy(commonNameArray[338], "Hart's tongue fern");
	strcpy(commonNameArray[339], "Maidenhair spleenwort");
	strcpy(commonNameArray[340], "Bigleaf aster");
	strcpy(commonNameArray[341], "Michaelmas daisy");
	strcpy(commonNameArray[342], "Sea aster");
	strcpy(commonNameArray[343], "Swedish coffee");
	strcpy(commonNameArray[344], "Ground plum");
	strcpy(commonNameArray[345], "Milk vetch");
	strcpy(commonNameArray[346], "Tragacanth");
	strcpy(commonNameArray[347], "Great masterwort");
	strcpy(commonNameArray[348], "Cranberry heath");
	strcpy(commonNameArray[349], "Pine heath");
	strcpy(commonNameArray[350], "Candy carrot");
	strcpy(commonNameArray[351], "Black sassafras");
	strcpy(commonNameArray[352], "King William pine");
	strcpy(commonNameArray[353], "Lady fern");
	strcpy(commonNameArray[354], "Painted fern");
	strcpy(commonNameArray[355], "Silvery orach");
	strcpy(commonNameArray[356], "Grey sage brush");
	strcpy(commonNameArray[357], "Shadscale");
	strcpy(commonNameArray[358], "Sea orach");
	strcpy(commonNameArray[359], "Hastate orach");
	strcpy(commonNameArray[360], "Orach");
	strcpy(commonNameArray[361], "Quail bush");
	strcpy(commonNameArray[362], "Indian belladonna");
	strcpy(commonNameArray[363], "Deadly nightshade");
	strcpy(commonNameArray[364], "Aubretia");
	strcpy(commonNameArray[365], "Spotted laurel");
	strcpy(commonNameArray[366], "Golden alyssum");
	strcpy(commonNameArray[367], "Abyssinian oat");
	strcpy(commonNameArray[368], "Slender oat");
	strcpy(commonNameArray[369], "Red oat");
	strcpy(commonNameArray[370], "Wild oats");
	strcpy(commonNameArray[371], "Oats");
	strcpy(commonNameArray[372], "Naked oat");
	strcpy(commonNameArray[373], "Hungarian oat");
	strcpy(commonNameArray[374], "Oat");
	strcpy(commonNameArray[375], "Sterile oats");
	strcpy(commonNameArray[376], "Bristle oats");
	strcpy(commonNameArray[377], "Baboon root");
	strcpy(commonNameArray[378], "Bush groundsel");
	strcpy(commonNameArray[379], "Dwarf chaparral broom");
	strcpy(commonNameArray[380], "Mule fat");
	strcpy(commonNameArray[381], "Black horehound");
	strcpy(commonNameArray[382], "Balsam root");
	strcpy(commonNameArray[383], "Oregon sunflower");
	strcpy(commonNameArray[384], "Hedge bamboo");
	strcpy(commonNameArray[385], "Ryoku-chiku");
	strcpy(commonNameArray[386], "Coast banksia");
	strcpy(commonNameArray[387], "Silver banksia");
	strcpy(commonNameArray[388], "Wild indigo");
	strcpy(commonNameArray[389], "Land cress");
	strcpy(commonNameArray[390], "Yellow rocket");
	strcpy(commonNameArray[391], "Indian spinach");
	strcpy(commonNameArray[392], "Summer cypress");
	strcpy(commonNameArray[393], "Begonia");
	strcpy(commonNameArray[394], "Leopard lily");
	strcpy(commonNameArray[395], "Daisy");
	strcpy(commonNameArray[396], "Wax gourd");
	strcpy(commonNameArray[397], "Chitra");
	strcpy(commonNameArray[398], "Allegheny barberry");
	strcpy(commonNameArray[399], "Barberry");
	strcpy(commonNameArray[400], "Sugar beet");
	strcpy(commonNameArray[401], "Spinach beet");
	strcpy(commonNameArray[402], "Beetroot");
	strcpy(commonNameArray[403], "Swiss chard");
	strcpy(commonNameArray[404], "Sea beet");
	strcpy(commonNameArray[405], "Yellow birch");
	strcpy(commonNameArray[406], "Gold birch");
	strcpy(commonNameArray[407], "Scrub birch");
	strcpy(commonNameArray[408], "Cherry birch");
	strcpy(commonNameArray[409], "Dwarf birch");
	strcpy(commonNameArray[410], "River birch");
	strcpy(commonNameArray[411], "Water birch");
	strcpy(commonNameArray[412], "Paper birch");
	strcpy(commonNameArray[413], "Silver birch");
	strcpy(commonNameArray[414], "Grey birch");
	strcpy(commonNameArray[415], "White birch");
	strcpy(commonNameArray[416], "Indian paper birch");
	strcpy(commonNameArray[417], "Beggar ticks");
	strcpy(commonNameArray[418], "Beggar's ticks");
	strcpy(commonNameArray[419], "Burr marigold");
	strcpy(commonNameArray[420], "Sweet appleberry");
	strcpy(commonNameArray[421], "Appleberry");
	strcpy(commonNameArray[422], "Common appleberry");
	strcpy(commonNameArray[423], "Yellow wort");
	strcpy(commonNameArray[424], "Hard fern");
	strcpy(commonNameArray[425], "Hyacinth orchid");
	strcpy(commonNameArray[426], "Golden stars");
	strcpy(commonNameArray[427], "Ramie");
	strcpy(commonNameArray[428], "Tar vine");
	strcpy(commonNameArray[429], "Yatzi");
	strcpy(commonNameArray[430], "Borage");
	strcpy(commonNameArray[431], "Parsley fern");
	strcpy(commonNameArray[432], "Common moonwort");
	strcpy(commonNameArray[433], "Rattlesnake fern");
	strcpy(commonNameArray[434], "Blue grama");
	strcpy(commonNameArray[435], "Kurrajong");
	strcpy(commonNameArray[436], "Bushman's toilet paper");
	strcpy(commonNameArray[437], "Blue hesper palm");
	strcpy(commonNameArray[438], "Guadalupe palm");
	strcpy(commonNameArray[439], "Water shield");
	strcpy(commonNameArray[440], "Abyssinian cabbage");
	strcpy(commonNameArray[441], "Chinese mustard");
	strcpy(commonNameArray[442], "Curled mustard");
	strcpy(commonNameArray[443], "Green in the snow");
	strcpy(commonNameArray[444], "Root mustard");
	strcpy(commonNameArray[445], "Large chinese mustard");
	strcpy(commonNameArray[446], "Swollen-stem mustard");
	strcpy(commonNameArray[447], "Colza");
	strcpy(commonNameArray[448], "Swede");
	strcpy(commonNameArray[449], "Black mustard");
	strcpy(commonNameArray[450], "Wild cabbage");
	strcpy(commonNameArray[451], "Chinese broccoli");
	strcpy(commonNameArray[452], "Cauliflower");
	strcpy(commonNameArray[453], "Nine star perennial broccoli");
	strcpy(commonNameArray[454], "Cabbage");
	strcpy(commonNameArray[455], "Couve tronchuda");
	strcpy(commonNameArray[456], "Brussel sprout");
	strcpy(commonNameArray[457], "Kohl rabi");
	strcpy(commonNameArray[458], "Calabrese");
	strcpy(commonNameArray[459], "Sprouting broccoli");
	strcpy(commonNameArray[460], "Savoy cabbage");
	strcpy(commonNameArray[461], "Kale");
	strcpy(commonNameArray[462], "Turnip");
	strcpy(commonNameArray[463], "Pak choi");
	strcpy(commonNameArray[464], "Mizuna");
	strcpy(commonNameArray[465], "Stubble turnip");
	strcpy(commonNameArray[466], "Rosette pak choi");
	strcpy(commonNameArray[467], "Chinese cabbage");
	strcpy(commonNameArray[468], "Mustard spinach");
	strcpy(commonNameArray[469], "Wild turnip-rape");
	strcpy(commonNameArray[470], "Californian hyacinth");
	strcpy(commonNameArray[471], "Californian brome");
	strcpy(commonNameArray[472], "Mango");
	strcpy(commonNameArray[473], "Kozo");
	strcpy(commonNameArray[474], "Paper mulberry");
	strcpy(commonNameArray[475], "White bryony");
	strcpy(commonNameArray[476], "Red bryony");
	strcpy(commonNameArray[477], "Buddlia");
	strcpy(commonNameArray[478], "Orange ball tree");
	strcpy(commonNameArray[479], "Maori onion");
	strcpy(commonNameArray[480], "Golden lily");
	strcpy(commonNameArray[481], "Chittamwood");
	strcpy(commonNameArray[482], "Shittamwood");
	strcpy(commonNameArray[483], "Ironwood");
	strcpy(commonNameArray[484], "Corn rocket");
	strcpy(commonNameArray[485], "Turkish rocket");
	strcpy(commonNameArray[486], "Pig nut");
	strcpy(commonNameArray[487], "Thorow-wax");
	strcpy(commonNameArray[488], "Shrubby hare's ear");
	strcpy(commonNameArray[489], "Hare's ear");
	strcpy(commonNameArray[490], "Milkmaids");
	strcpy(commonNameArray[491], "Christmas bush");
	strcpy(commonNameArray[492], "Jelly palm");
	strcpy(commonNameArray[493], "Flowering rush");
	strcpy(commonNameArray[494], "Japanese box");
	strcpy(commonNameArray[495], "Box");
	strcpy(commonNameArray[496], "Mysore thorn");
	strcpy(commonNameArray[497], "Blue grass lily");
	strcpy(commonNameArray[498], "Sea rocket");
	strcpy(commonNameArray[499], "Large-flowered calamint");
	strcpy(commonNameArray[500], "Lesser calamint");
	strcpy(commonNameArray[501], "Calamint");
	strcpy(commonNameArray[502], "Redmaids");
	strcpy(commonNameArray[503], "Field marigold");
	strcpy(commonNameArray[504], "Pot marigold");
	strcpy(commonNameArray[505], "Water arum");
	strcpy(commonNameArray[506], "Beautyberry");
	strcpy(commonNameArray[507], "Finger poppy mallow");
	strcpy(commonNameArray[508], "Poppy mallow");
	strcpy(commonNameArray[509], "Crimson bottlebrush");
	strcpy(commonNameArray[510], "Water starwort");
	strcpy(commonNameArray[511], "Red cypress-pine");
	strcpy(commonNameArray[512], "Heather");
	strcpy(commonNameArray[513], "Incense cedar");
	strcpy(commonNameArray[514], "Star tulip");
	strcpy(commonNameArray[515], "Mariposa lily");
	strcpy(commonNameArray[516], "Yellow mariposa");
	strcpy(commonNameArray[517], "Sego lily");
	strcpy(commonNameArray[518], "Western marsh marigold");
	strcpy(commonNameArray[519], "Marsh marigold");
	strcpy(commonNameArray[520], "Carolina allspice");
	strcpy(commonNameArray[521], "Californian  allspice");
	strcpy(commonNameArray[522], "Fairyslipper");
	strcpy(commonNameArray[523], "Japanese bindweed");
	strcpy(commonNameArray[524], "Hedge bindweed");
	strcpy(commonNameArray[525], "Sea bindweed");
	strcpy(commonNameArray[526], "Wild hyacinth");
	strcpy(commonNameArray[527], "Quamash");
	strcpy(commonNameArray[528], "Gold of pleasure");
	strcpy(commonNameArray[529], "Camellia");
	strcpy(commonNameArray[530], "Tea plant");
	strcpy(commonNameArray[531], "Tussock bellflower");
	strcpy(commonNameArray[532], "Fairies thimbles");
	strcpy(commonNameArray[533], "Clustered bellflower");
	strcpy(commonNameArray[534], "Canterbury bells");
	strcpy(commonNameArray[535], "Chinese rampion");
	strcpy(commonNameArray[536], "Chimney bellflower");
	strcpy(commonNameArray[537], "Creeping bellflower");
	strcpy(commonNameArray[538], "Rampion");
	strcpy(commonNameArray[539], "Trumpet creeper");
	strcpy(commonNameArray[540], "Trumpet vine");
	strcpy(commonNameArray[541], "Achira");
	strcpy(commonNameArray[542], "Indian shot");
	strcpy(commonNameArray[543], "Hemp");
	strcpy(commonNameArray[544], "Caper");
	strcpy(commonNameArray[545], "Shepherd's purse");
	strcpy(commonNameArray[546], "Sweet pepper");
	strcpy(commonNameArray[547], "Tabasco pepper");
	strcpy(commonNameArray[548], "Tree pepper");
	strcpy(commonNameArray[549], "Siberian pea tree");
	strcpy(commonNameArray[550], "Shag-spine");
	strcpy(commonNameArray[551], "Large bittercress");
	strcpy(commonNameArray[552], "Wavy bittercress");
	strcpy(commonNameArray[553], "Hairy bittercress");
	strcpy(commonNameArray[554], "Spring cress");
	strcpy(commonNameArray[555], "Cuckoo flower");
	strcpy(commonNameArray[556], "American water cress");
	strcpy(commonNameArray[557], "Hoary cress");
	strcpy(commonNameArray[558], "Heart seed");
	strcpy(commonNameArray[559], "Welted thistle");
	strcpy(commonNameArray[560], "Musk thistle");
	strcpy(commonNameArray[561], "Swamp sedge");
	strcpy(commonNameArray[562], "Sand sedge");
	strcpy(commonNameArray[563], "Tufted sedge");
	strcpy(commonNameArray[564], "Stemless carline thistle");
	strcpy(commonNameArray[565], "Carline thistle");
	strcpy(commonNameArray[566], "Hornbeam");
	strcpy(commonNameArray[567], "American hornbeam");
	strcpy(commonNameArray[568], "Hottentot fig");
	strcpy(commonNameArray[569], "Sea fig");
	strcpy(commonNameArray[570], "Sweet hottentot fig");
	strcpy(commonNameArray[571], "Distaff thistle");
	strcpy(commonNameArray[572], "Safflower");
	strcpy(commonNameArray[573], "Caraway");
	strcpy(commonNameArray[574], "Water hickory");
	strcpy(commonNameArray[575], "California walnut");
	strcpy(commonNameArray[576], "Southern shagbark");
	strcpy(commonNameArray[577], "Chinese hickory");
	strcpy(commonNameArray[578], "Bitternut");
	strcpy(commonNameArray[579], "Scrub hickory");
	strcpy(commonNameArray[580], "Pignut");
	strcpy(commonNameArray[581], "Coastal pignut hickory");
	strcpy(commonNameArray[582], "Pecan");
	strcpy(commonNameArray[583], "Shellbark hickory");
	strcpy(commonNameArray[584], "Nutmeg hickory");
	strcpy(commonNameArray[585], "Sweet pignut");
	strcpy(commonNameArray[586], "Shagbark hickory");
	strcpy(commonNameArray[587], "Sand hickory");
	strcpy(commonNameArray[588], "Black hickory");
	strcpy(commonNameArray[589], "Mockernut");
	strcpy(commonNameArray[590], "Chestnut hybrids");
	strcpy(commonNameArray[591], "Bush chinkapin");
	strcpy(commonNameArray[592], "Japanese chestnut");
	strcpy(commonNameArray[593], "American sweet chestnut");
	strcpy(commonNameArray[594], "Chinese chestnut");
	strcpy(commonNameArray[595], "Ozark chinkapin");
	strcpy(commonNameArray[596], "Chinquapin");
	strcpy(commonNameArray[597], "Sweet chetsnut");
	strcpy(commonNameArray[598], "Chinese chinquapin");
	strcpy(commonNameArray[599], "Chinknut");
	strcpy(commonNameArray[600], "Japanese chinquapin");
	strcpy(commonNameArray[601], "Moreton Bay chestnut");
	strcpy(commonNameArray[602], "Indian bean tree");
	strcpy(commonNameArray[603], "Shawnee wood");
	strcpy(commonNameArray[604], "Small bur-parsley");
	strcpy(commonNameArray[605], "Papoose root");
	strcpy(commonNameArray[606], "New Jersey tea");
	strcpy(commonNameArray[607], "Buckbrush");
	strcpy(commonNameArray[608], "Cropleaf ceanothus");
	strcpy(commonNameArray[609], "Santa Barbara ceanothus");
	strcpy(commonNameArray[610], "Deer brush");
	strcpy(commonNameArray[611], "Smaller red-root");
	strcpy(commonNameArray[612], "Squaw carpet");
	strcpy(commonNameArray[613], "Hollyleaf ceanothus");
	strcpy(commonNameArray[614], "Oregon tea tree");
	strcpy(commonNameArray[615], "Blue brush");
	strcpy(commonNameArray[616], "Sticky laurel");
	strcpy(commonNameArray[617], "Balm of Gilead");
	strcpy(commonNameArray[618], "Atlas cedar");
	strcpy(commonNameArray[619], "Deodar");
	strcpy(commonNameArray[620], "Cedar of Lebanon");
	strcpy(commonNameArray[621], "Oriental bittersweet");
	strcpy(commonNameArray[622], "Climbing bittersweet");
	strcpy(commonNameArray[623], "Nettle tree");
	strcpy(commonNameArray[624], "Sugarberry");
	strcpy(commonNameArray[625], "Palo blanco");
	strcpy(commonNameArray[626], "Hackberry");
	strcpy(commonNameArray[627], "Paloblanco");
	strcpy(commonNameArray[628], "Small hackberry");
	strcpy(commonNameArray[629], "Common star thistle");
	strcpy(commonNameArray[630], "Cornflower");
	strcpy(commonNameArray[631], "Mountain cornflower");
	strcpy(commonNameArray[632], "Black knapweed");
	strcpy(commonNameArray[633], "Greater knapweed");
	strcpy(commonNameArray[634], "St. Barnaby's thistle");
	strcpy(commonNameArray[635], "Centaury");
	strcpy(commonNameArray[636], "Gotu kola");
	strcpy(commonNameArray[637], "Red valerian");
	strcpy(commonNameArray[638], "Button bush");
	strcpy(commonNameArray[639], "Chinese plum yew");
	strcpy(commonNameArray[640], "Japanese plum yew");
	strcpy(commonNameArray[641], "Korean plum yew");
	strcpy(commonNameArray[642], "Yunnan plum yew");
	strcpy(commonNameArray[643], "Little mouse-ear chickweed");
	strcpy(commonNameArray[644], "Carob");
	strcpy(commonNameArray[645], "Hornwort");
	strcpy(commonNameArray[646], "Chinese plumbago");
	strcpy(commonNameArray[647], "Katsura tree");
	strcpy(commonNameArray[648], "Redbud");
	strcpy(commonNameArray[649], "Chinese redbud");
	strcpy(commonNameArray[650], "Western redbud");
	strcpy(commonNameArray[651], "Judas tree");
	strcpy(commonNameArray[652], "Mountain mahogany");
	strcpy(commonNameArray[653], "Wax palm");
	strcpy(commonNameArray[654], "Iceland moss");
	strcpy(commonNameArray[655], "Morning brides");
	strcpy(commonNameArray[656], "Chinese quince");
	strcpy(commonNameArray[657], "Dwarf quince");
	strcpy(commonNameArray[658], "Japanese quince");
	strcpy(commonNameArray[659], "Turnip-rooted chervil");
	strcpy(commonNameArray[660], "Sham");
	strcpy(commonNameArray[661], "Lawson cypress");
	strcpy(commonNameArray[662], "Nootka cypress");
	strcpy(commonNameArray[663], "White cypress");
	strcpy(commonNameArray[664], "Leather leaf");
	strcpy(commonNameArray[665], "Blazing star");
	strcpy(commonNameArray[666], "Camomile");
	strcpy(commonNameArray[667], "Dwarf fan palm");
	strcpy(commonNameArray[668], "Ressurection fern");
	strcpy(commonNameArray[669], "Greater celandine");
	strcpy(commonNameArray[670], "Balmony");
	strcpy(commonNameArray[671], "Fat hen");
	strcpy(commonNameArray[672], "Mexican tea");
	strcpy(commonNameArray[673], "Wormseed");
	strcpy(commonNameArray[674], "Southern huauzontle");
	strcpy(commonNameArray[675], "Good King Henry");
	strcpy(commonNameArray[676], "Jerusalem oak");
	strcpy(commonNameArray[677], "Strawberry blite");
	strcpy(commonNameArray[678], "Fig-leaved goosefoot");
	strcpy(commonNameArray[679], "Tree spinach");
	strcpy(commonNameArray[680], "Oak-leaved goosefoot");
	strcpy(commonNameArray[681], "Narrow leaved goosefoot");
	strcpy(commonNameArray[682], "Huauzontle");
	strcpy(commonNameArray[683], "Cañihua");
	strcpy(commonNameArray[684], "All-seed");
	strcpy(commonNameArray[685], "Quinoa");
	strcpy(commonNameArray[686], "Red goosefoot");
	strcpy(commonNameArray[687], "Stinking goosefoot");
	strcpy(commonNameArray[688], "Desert willow");
	strcpy(commonNameArray[689], "Spotted wintergreen");
	strcpy(commonNameArray[690], "Pipsissewa");
	strcpy(commonNameArray[691], "Winter sweet");
	strcpy(commonNameArray[692], "Kan-chiku");
	strcpy(commonNameArray[693], "Thorny bamboo");
	strcpy(commonNameArray[694], "Square bamboo");
	strcpy(commonNameArray[695], "Fringe tree");
	strcpy(commonNameArray[696], "Soap lily");
	strcpy(commonNameArray[697], "Mexican orange flower");
	strcpy(commonNameArray[698], "Chop-suey greens");
	strcpy(commonNameArray[699], "Corn marigold");
	strcpy(commonNameArray[700], "Golden chinquapin");
	strcpy(commonNameArray[701], "Dwarf golden chinquapin");
	strcpy(commonNameArray[702], "Golden saxifrage");
	strcpy(commonNameArray[703], "Water mat");
	strcpy(commonNameArray[704], "Culeu");
	strcpy(commonNameArray[705], "Chick pea");
	strcpy(commonNameArray[706], "Blue sow thistle");
	strcpy(commonNameArray[707], "Endive");
	strcpy(commonNameArray[708], "Chicory");
	strcpy(commonNameArray[709], "Cowbane");
	strcpy(commonNameArray[710], "Foetid bugbane");
	strcpy(commonNameArray[711], "Black cohosh");
	strcpy(commonNameArray[712], "Sweet reed grass");
	strcpy(commonNameArray[713], "Camphor");
	strcpy(commonNameArray[714], "Stemless thistle");
	strcpy(commonNameArray[715], "Creeping thistle");
	strcpy(commonNameArray[716], "Wooly thistle");
	strcpy(commonNameArray[717], "No-azami");
	strcpy(commonNameArray[718], "Yellow spined thistle");
	strcpy(commonNameArray[719], "Cabbage thistle");
	strcpy(commonNameArray[720], "Marsh thistle");
	strcpy(commonNameArray[721], "Tuberous thistle");
	strcpy(commonNameArray[722], "Wavy-leaved thistle");
	strcpy(commonNameArray[723], "Common thistle");
	strcpy(commonNameArray[724], "Rock rose");
	strcpy(commonNameArray[725], "Labdanum");
	strcpy(commonNameArray[726], "Limequat");
	strcpy(commonNameArray[727], "Calamondin orange");
	strcpy(commonNameArray[728], "Citrange");
	strcpy(commonNameArray[729], "Water melon");
	strcpy(commonNameArray[730], "Bitter orange");
	strcpy(commonNameArray[731], "Ichant papeda");
	strcpy(commonNameArray[732], "Lemon");
	strcpy(commonNameArray[733], "Mandarin");
	strcpy(commonNameArray[734], "Sweet orange");
	strcpy(commonNameArray[735], "Sedge");
	strcpy(commonNameArray[736], "Yellow wood");
	strcpy(commonNameArray[737], "Broad-leaved spring beauty");
	strcpy(commonNameArray[738], "Alpine spring beauty");
	strcpy(commonNameArray[739], "Miner's lettuce");
	strcpy(commonNameArray[740], "Pink purslane");
	strcpy(commonNameArray[741], "Spring beauty");
	strcpy(commonNameArray[742], "Fragrant virgin's bower");
	strcpy(commonNameArray[743], "White clematis");
	strcpy(commonNameArray[744], "Traveller's joy");
	strcpy(commonNameArray[745], "Rocky Mountain beeplant");
	strcpy(commonNameArray[746], "Tickweed");
	strcpy(commonNameArray[747], "Glory flower");
	strcpy(commonNameArray[748], "Sweet pepper bush");
	strcpy(commonNameArray[749], "Wild basil");
	strcpy(commonNameArray[750], "Bluebeard");
	strcpy(commonNameArray[751], "Speckled wood lily");
	strcpy(commonNameArray[752], "Spurge olive");
	strcpy(commonNameArray[753], "Blessed thistle");
	strcpy(commonNameArray[754], "Ivy gourd");
	strcpy(commonNameArray[755], "Long leaved scurvy grass");
	strcpy(commonNameArray[756], "Danish scurvy grass");
	strcpy(commonNameArray[757], "Scurvy grass");
	strcpy(commonNameArray[758], "Job's tears");
	strcpy(commonNameArray[759], "Autumn crocus");
	strcpy(commonNameArray[760], "Stone root");
	strcpy(commonNameArray[761], "Bladder senna");
	strcpy(commonNameArray[762], "Blue spider wort");
	strcpy(commonNameArray[763], "Day flower");
	strcpy(commonNameArray[764], "Sweet fern");
	strcpy(commonNameArray[765], "Hemlock");
	strcpy(commonNameArray[766], "Cumberland rosemary");
	strcpy(commonNameArray[767], "Larkspur");
	strcpy(commonNameArray[768], "Lily of the valley");
	strcpy(commonNameArray[769], "Field bindweed");
	strcpy(commonNameArray[770], "Scammony");
	strcpy(commonNameArray[771], "Canada fleabane");
	strcpy(commonNameArray[772], "Sand coprosma");
	strcpy(commonNameArray[773], "Native currant");
	strcpy(commonNameArray[774], "Mirror plant");
	strcpy(commonNameArray[775], "Chinese goldenthread");
	strcpy(commonNameArray[776], "Goldthread");
	strcpy(commonNameArray[777], "Autumn coralroot");
	strcpy(commonNameArray[778], "Jute");
	strcpy(commonNameArray[779], "Jew's mallow");
	strcpy(commonNameArray[780], "Cabbage tree");
	strcpy(commonNameArray[781], "Portuguese crowberry");
	strcpy(commonNameArray[782], "Poverty grass");
	strcpy(commonNameArray[783], "Tickseed");
	strcpy(commonNameArray[784], "Coreopsis");
	strcpy(commonNameArray[785], "Coriander");
	strcpy(commonNameArray[786], "Redoul");
	strcpy(commonNameArray[787], "Tuhu");
	strcpy(commonNameArray[788], "Green osier");
	strcpy(commonNameArray[789], "Silky dogwood");
	strcpy(commonNameArray[790], "Creeping dogwood");
	strcpy(commonNameArray[791], "Bentham's cornel");
	strcpy(commonNameArray[792], "Giant dogwood");
	strcpy(commonNameArray[793], "Flowering dogwood");
	strcpy(commonNameArray[794], "Japanese dogwood");
	strcpy(commonNameArray[795], "Large-leaf dogwood");
	strcpy(commonNameArray[796], "Cornelian cherry");
	strcpy(commonNameArray[797], "Mountain dogwood");
	strcpy(commonNameArray[798], "Japanese cornel");
	strcpy(commonNameArray[799], "Round-leaved dogwood");
	strcpy(commonNameArray[800], "Dogwood");
	strcpy(commonNameArray[801], "Red osier dogwood");
	strcpy(commonNameArray[802], "Dwarf cornel");
	strcpy(commonNameArray[803], "Scorpion senna");
	strcpy(commonNameArray[804], "Annual scorpion vetch");
	strcpy(commonNameArray[805], "Crown vetch");
	strcpy(commonNameArray[806], "Cape Barren tea");
	strcpy(commonNameArray[807], "Strapwort");
	strcpy(commonNameArray[808], "Pampas grass");
	strcpy(commonNameArray[809], "Fumewort");
	strcpy(commonNameArray[810], "American hazel");
	strcpy(commonNameArray[811], "Hazel");
	strcpy(commonNameArray[812], "Chinese hazel");
	strcpy(commonNameArray[813], "Turkish hazel");
	strcpy(commonNameArray[814], "Beaked hazel");
	strcpy(commonNameArray[815], "California hazel");
	strcpy(commonNameArray[816], "Himalayan hazel");
	strcpy(commonNameArray[817], "Siberian filbert");
	strcpy(commonNameArray[818], "Indian tree hazel");
	strcpy(commonNameArray[819], "Filbert");
	strcpy(commonNameArray[820], "Japanese hazel");
	strcpy(commonNameArray[821], "Trazel");
	strcpy(commonNameArray[822], "Chinese trazel");
	strcpy(commonNameArray[823], "New Zealand laurel");
	strcpy(commonNameArray[824], "Cosmos");
	strcpy(commonNameArray[825], "Smoke tree");
	strcpy(commonNameArray[826], "Black-wood");
	strcpy(commonNameArray[827], "Brass buttons");
	strcpy(commonNameArray[828], "Cliffrose");
	strcpy(commonNameArray[829], "Seacale");
	strcpy(commonNameArray[830], "Tartar bread plant");
	strcpy(commonNameArray[831], "Bronvaux medlar");
	strcpy(commonNameArray[832], "Altai mountain thorn");
	strcpy(commonNameArray[833], "Parsley-leaved hawthorn");
	strcpy(commonNameArray[834], "Azarole");
	strcpy(commonNameArray[835], "Kansas hawthorn");
	strcpy(commonNameArray[836], "Cockspur thorn");
	strcpy(commonNameArray[837], "Black hawthorn");
	strcpy(commonNameArray[838], "Summer haw");
	strcpy(commonNameArray[839], "Midland hawthorn");
	strcpy(commonNameArray[840], "Red haw");
	strcpy(commonNameArray[841], "Hawthorn");
	strcpy(commonNameArray[842], "Hungarian hawthorn");
	strcpy(commonNameArray[843], "Mayhaw");
	strcpy(commonNameArray[844], "Scarlet haw");
	strcpy(commonNameArray[845], "Washington thorn");
	strcpy(commonNameArray[846], "Chinese haw");
	strcpy(commonNameArray[847], "Frosted hawthorn");
	strcpy(commonNameArray[848], "Manzanilla");
	strcpy(commonNameArray[849], "Dotted hawthorn");
	strcpy(commonNameArray[850], "River hawthorn");
	strcpy(commonNameArray[851], "Tansy-leaved thorn");
	strcpy(commonNameArray[852], "Murray lily");
	strcpy(commonNameArray[853], "Samphire");
	strcpy(commonNameArray[854], "Montbretia");
	strcpy(commonNameArray[855], "Saffron");
	strcpy(commonNameArray[856], "Japanese cedar");
	strcpy(commonNameArray[857], "Honewort");
	strcpy(commonNameArray[858], "Mitsuba");
	strcpy(commonNameArray[859], "Berry-bearing catchfly");
	strcpy(commonNameArray[860], "Gherkin");
	strcpy(commonNameArray[861], "Melon");
	strcpy(commonNameArray[862], "Horned cucumber");
	strcpy(commonNameArray[863], "Cucumber");
	strcpy(commonNameArray[864], "Cushaw pumpkin");
	strcpy(commonNameArray[865], "Buffalo gourd");
	strcpy(commonNameArray[866], "Winter squash");
	strcpy(commonNameArray[867], "Squash");
	strcpy(commonNameArray[868], "Pumpkin");
	strcpy(commonNameArray[869], "Silkworm thorn");
	strcpy(commonNameArray[870], "Cumin");
	strcpy(commonNameArray[871], "Stone mint");
	strcpy(commonNameArray[872], "Chinese fir");
	strcpy(commonNameArray[873], "Leyland cypress");
	strcpy(commonNameArray[874], "Arizona cypress");
	strcpy(commonNameArray[875], "Chinese weeping cypress");
	strcpy(commonNameArray[876], "Monterey cypress");
	strcpy(commonNameArray[877], "Italian cypress");
	strcpy(commonNameArray[878], "Himalayan cypress");
	strcpy(commonNameArray[879], "Chinese dodder");
	strcpy(commonNameArray[880], "Lesser dodder");
	strcpy(commonNameArray[881], "Japanese dodder");
	strcpy(commonNameArray[882], "Trailing bellflower");
	strcpy(commonNameArray[883], "Lady's hand");
	strcpy(commonNameArray[884], "Tree fern");
	strcpy(commonNameArray[885], "Black tree fern");
	strcpy(commonNameArray[886], "Cheese berry");
	strcpy(commonNameArray[887], "Pink mountain berry");
	strcpy(commonNameArray[888], "Sago palm");
	strcpy(commonNameArray[889], "Japanese sago palm");
	strcpy(commonNameArray[890], "Cyclamen");
	strcpy(commonNameArray[891], "Achocha");
	strcpy(commonNameArray[892], "Winged pigweed");
	strcpy(commonNameArray[893], "Quince");
	strcpy(commonNameArray[894], "Kenilworth ivy");
	strcpy(commonNameArray[895], "Cardoon");
	strcpy(commonNameArray[896], "Globe artichoke");
	strcpy(commonNameArray[897], "Bermuda grass");
	strcpy(commonNameArray[898], "Hound's tongue");
	strcpy(commonNameArray[899], "Tiger nut");
	strcpy(commonNameArray[900], "Galingale");
	strcpy(commonNameArray[901], "Nut grass");
	strcpy(commonNameArray[902], "Tree tomato");
	strcpy(commonNameArray[903], "Nerve root");
	strcpy(commonNameArray[904], "Leatherwood");
	strcpy(commonNameArray[905], "Berry bladder fern");
	strcpy(commonNameArray[906], "Brittle bladder fern");
	strcpy(commonNameArray[907], "Broom");
	strcpy(commonNameArray[908], "Kahikatea");
	strcpy(commonNameArray[909], "Rimu");
	strcpy(commonNameArray[910], "Cock's foot");
	strcpy(commonNameArray[911], "Marsh orchid");
	strcpy(commonNameArray[912], "Spotted orchid");
	strcpy(commonNameArray[913], "Dahlia");
	strcpy(commonNameArray[914], "White prairie clover");
	strcpy(commonNameArray[915], "Purple prairie clover");
	strcpy(commonNameArray[916], "Thrumwort");
	strcpy(commonNameArray[917], "Flax-leaved daphne");
	strcpy(commonNameArray[918], "Spurge laurel");
	strcpy(commonNameArray[919], "Mezereon");
	strcpy(commonNameArray[920], "Winter daphne");
	strcpy(commonNameArray[921], "Umbrella plant");
	strcpy(commonNameArray[922], "Sotol");
	strcpy(commonNameArray[923], "Downy thorn apple");
	strcpy(commonNameArray[924], "Thorn apple");
	strcpy(commonNameArray[925], "Wild carrot");
	strcpy(commonNameArray[926], "Carrot");
	strcpy(commonNameArray[927], "Waterleaf");
	strcpy(commonNameArray[928], "Stavesacre");
	strcpy(commonNameArray[929], "Chrysanthemum");
	strcpy(commonNameArray[930], "Crinkleroot");
	strcpy(commonNameArray[931], "Cut-leaved toothwort");
	strcpy(commonNameArray[932], "Tussock grass");
	strcpy(commonNameArray[933], "Tansy mustard");
	strcpy(commonNameArray[934], "Flixweed");
	strcpy(commonNameArray[935], "Prairie mimosa");
	strcpy(commonNameArray[936], "Flax lily");
	strcpy(commonNameArray[937], "Beach flax lily");
	strcpy(commonNameArray[938], "Sweet William");
	strcpy(commonNameArray[939], "Carnation");
	strcpy(commonNameArray[940], "Chinese pink");
	strcpy(commonNameArray[941], "Cheddar pink");
	strcpy(commonNameArray[942], "Pink");
	strcpy(commonNameArray[943], "Fringed pink");
	strcpy(commonNameArray[944], "Squirrel corn");
	strcpy(commonNameArray[945], "Dutchman's breeches");
	strcpy(commonNameArray[946], "Bleeding heart");
	strcpy(commonNameArray[947], "Snake lily");
	strcpy(commonNameArray[948], "Chocolate lily");
	strcpy(commonNameArray[949], "Burning bush");
	strcpy(commonNameArray[950], "Bush honeysuckle");
	strcpy(commonNameArray[951], "Rusty foxglove");
	strcpy(commonNameArray[952], "Large yellow foxglove");
	strcpy(commonNameArray[953], "Grecian foxglove");
	strcpy(commonNameArray[954], "Yellow foxglove");
	strcpy(commonNameArray[955], "Foxglove");
	strcpy(commonNameArray[956], "Crab grass");
	strcpy(commonNameArray[957], "Chinese yam");
	strcpy(commonNameArray[958], "Glutinous yam");
	strcpy(commonNameArray[959], "Persimmon");
	strcpy(commonNameArray[960], "Date plum");
	strcpy(commonNameArray[961], "American persimmon");
	strcpy(commonNameArray[962], "Umbrella leaf");
	strcpy(commonNameArray[963], "White wall rocket");
	strcpy(commonNameArray[964], "Wall rocket");
	strcpy(commonNameArray[965], "Perennial wall rocket");
	strcpy(commonNameArray[966], "Teasel");
	strcpy(commonNameArray[967], "Fuller's teasel");
	strcpy(commonNameArray[968], "Leather wood");
	strcpy(commonNameArray[969], "Pig's face");
	strcpy(commonNameArray[970], "Isu tree");
	strcpy(commonNameArray[971], "Sailor-caps");
	strcpy(commonNameArray[972], "Native hops");
	strcpy(commonNameArray[973], "Ammoniacum");
	strcpy(commonNameArray[974], "Great leopard's bane");
	strcpy(commonNameArray[975], "Wall whitlow grass");
	strcpy(commonNameArray[976], "Moldavian balm");
	strcpy(commonNameArray[977], "Ringal");
	strcpy(commonNameArray[978], "Mountain pepper");
	strcpy(commonNameArray[979], "Winter's bark");
	strcpy(commonNameArray[980], "Sundew");
	strcpy(commonNameArray[981], "Mountain avens");
	strcpy(commonNameArray[982], "Narrow buckler fern");
	strcpy(commonNameArray[983], "Crested wood fern");
	strcpy(commonNameArray[984], "Shield fern");
	strcpy(commonNameArray[985], "Male fern");
	strcpy(commonNameArray[986], "Mountain male fern");
	strcpy(commonNameArray[987], "Mission lettuce");
	strcpy(commonNameArray[988], "Squirting cucumber");
	strcpy(commonNameArray[989], "Cone flower");
	strcpy(commonNameArray[990], "Purple coneflower");
	strcpy(commonNameArray[991], "Jungle rice");
	strcpy(commonNameArray[992], "Barnyard millet");
	strcpy(commonNameArray[993], "Japanese millet");
	strcpy(commonNameArray[994], "Wild cucumber");
	strcpy(commonNameArray[995], "Viper's bugloss");
	strcpy(commonNameArray[996], "Paperbush");
	strcpy(commonNameArray[997], "Koda tree");
	strcpy(commonNameArray[998], "Anaqua");
	strcpy(commonNameArray[999], "Oleaster");
	strcpy(commonNameArray[1000], "Silverberry");
	strcpy(commonNameArray[1001], "Bastard oleaster");
	strcpy(commonNameArray[1002], "Goumi");
	strcpy(commonNameArray[1003], "Trebizond date");
	strcpy(commonNameArray[1004], "Elaeagnus");
	strcpy(commonNameArray[1005], "Autumn olive");
	strcpy(commonNameArray[1006], "Blueberry ash");
	strcpy(commonNameArray[1007], "Chinese water chestnut");
	strcpy(commonNameArray[1008], "Finger millet");
	strcpy(commonNameArray[1009], "Wire grass");
	strcpy(commonNameArray[1010], "Siberian ginseng");
	strcpy(commonNameArray[1011], "Canadian wild rye");
	strcpy(commonNameArray[1012], "Blue wild rye");
	strcpy(commonNameArray[1013], "Couch grass");
	strcpy(commonNameArray[1014], "Tassel flower");
	strcpy(commonNameArray[1015], "Purple crowberry");
	strcpy(commonNameArray[1016], "Rockberry");
	strcpy(commonNameArray[1017], "Mountain crowberry");
	strcpy(commonNameArray[1018], "Crowberry");
	strcpy(commonNameArray[1019], "Brittle bush");
	strcpy(commonNameArray[1020], "Ruby saltbush");
	strcpy(commonNameArray[1021], "Ethiopian banana");
	strcpy(commonNameArray[1022], "Corkwood tree");
	strcpy(commonNameArray[1023], "Sea grape");
	strcpy(commonNameArray[1024], "Ma Huang");
	strcpy(commonNameArray[1025], "Mormon tea");
	strcpy(commonNameArray[1026], "Mayflower");
	strcpy(commonNameArray[1027], "Willow herb");
	strcpy(commonNameArray[1028], "Codlins and cream");
	strcpy(commonNameArray[1029], "River beauty");
	strcpy(commonNameArray[1030], "Horsetail");
	strcpy(commonNameArray[1031], "Swamp horsetail");
	strcpy(commonNameArray[1032], "Dutch rush");
	strcpy(commonNameArray[1033], "Wood horsetail");
	strcpy(commonNameArray[1034], "Soft love grass");
	strcpy(commonNameArray[1035], "Tef");
	strcpy(commonNameArray[1036], "Cornish heath");
	strcpy(commonNameArray[1037], "Harbinger of spring");
	strcpy(commonNameArray[1038], "Beach aster");
	strcpy(commonNameArray[1039], "Loquat");
	strcpy(commonNameArray[1040], "Yerba santa");
	strcpy(commonNameArray[1041], "Antelope sage");
	strcpy(commonNameArray[1042], "Cotton grass");
	strcpy(commonNameArray[1043], "Stork's bill");
	strcpy(commonNameArray[1044], "Musk storksbill");
	strcpy(commonNameArray[1045], "Rocket");
	strcpy(commonNameArray[1046], "Button snakeroot");
	strcpy(commonNameArray[1047], "Field eryngo");
	strcpy(commonNameArray[1048], "Sea holly");
	strcpy(commonNameArray[1049], "Coastal wallflower");
	strcpy(commonNameArray[1050], "Wormseed mustard");
	strcpy(commonNameArray[1051], "Wallflower");
	strcpy(commonNameArray[1052], "Siberian wallflower");
	strcpy(commonNameArray[1053], "Coral tree");
	strcpy(commonNameArray[1054], "Cardinal spear");
	strcpy(commonNameArray[1055], "Dwarf kafferboom");
	strcpy(commonNameArray[1056], "Prickly cardinal");
	strcpy(commonNameArray[1057], "White trout-lily");
	strcpy(commonNameArray[1058], "Trout lily");
	strcpy(commonNameArray[1059], "Fawn lily");
	strcpy(commonNameArray[1060], "Dog's-tooth violet");
	strcpy(commonNameArray[1061], "Avalanche lily");
	strcpy(commonNameArray[1062], "Katakuri");
	strcpy(commonNameArray[1063], "Avelanche lily");
	strcpy(commonNameArray[1064], "Escallonia");
	strcpy(commonNameArray[1065], "Californian poppy");
	strcpy(commonNameArray[1066], "Gungurru");
	strcpy(commonNameArray[1067], "Red river gum");
	strcpy(commonNameArray[1068], "Lemon-scented gum");
	strcpy(commonNameArray[1069], "Mt. Wellington peppermint");
	strcpy(commonNameArray[1070], "Water mallee");
	strcpy(commonNameArray[1071], "Tasmanian blue gum");
	strcpy(commonNameArray[1072], "Red bloodwood");
	strcpy(commonNameArray[1073], "Cider gum");
	strcpy(commonNameArray[1074], "Yellow gum");
	strcpy(commonNameArray[1075], "Black box");
	strcpy(commonNameArray[1076], "Red stringybark");
	strcpy(commonNameArray[1077], "Yellow box");
	strcpy(commonNameArray[1078], "Tallow wood");
	strcpy(commonNameArray[1079], "Messmate");
	strcpy(commonNameArray[1080], "Cabbage gum");
	strcpy(commonNameArray[1081], "Snow gum");
	strcpy(commonNameArray[1082], "Spinning gum");
	strcpy(commonNameArray[1083], "Sydney peppermint");
	strcpy(commonNameArray[1084], "Blue mallee");
	strcpy(commonNameArray[1085], "Snappy gum");
	strcpy(commonNameArray[1086], "Mountain ash");
	strcpy(commonNameArray[1087], "Red ironbark");
	strcpy(commonNameArray[1088], "Manna gum");
	strcpy(commonNameArray[1089], "Gutta-percha");
	strcpy(commonNameArray[1090], "Ulmo");
	strcpy(commonNameArray[1091], "Stinkwood");
	strcpy(commonNameArray[1092], "Winged spindle tree");
	strcpy(commonNameArray[1093], "Strawberry bush");
	strcpy(commonNameArray[1094], "Wahoo");
	strcpy(commonNameArray[1095], "Spindle tree");
	strcpy(commonNameArray[1096], "Japanese spindle tree");
	strcpy(commonNameArray[1097], "Hemp agrimony");
	strcpy(commonNameArray[1098], "Joe pye weed");
	strcpy(commonNameArray[1099], "Thoroughwort");
	strcpy(commonNameArray[1100], "Gravel root");
	strcpy(commonNameArray[1101], "Candelilla");
	strcpy(commonNameArray[1102], "Wild spurge");
	strcpy(commonNameArray[1103], "Asthma weed");
	strcpy(commonNameArray[1104], "Caper spurge");
	strcpy(commonNameArray[1105], "Mountain snow");
	strcpy(commonNameArray[1106], "Naboom");
	strcpy(commonNameArray[1107], "Eyebright");
	strcpy(commonNameArray[1108], "Wombat berry");
	strcpy(commonNameArray[1109], "Native cherry");
	strcpy(commonNameArray[1110], "Pichi");
	strcpy(commonNameArray[1111], "Perennial buckwheat");
	strcpy(commonNameArray[1112], "Buckwheat");
	strcpy(commonNameArray[1113], "Tartarian buckwheat");
	strcpy(commonNameArray[1114], "American beech");
	strcpy(commonNameArray[1115], "Japanese beech");
	strcpy(commonNameArray[1116], "Oriental beech");
	strcpy(commonNameArray[1117], "Beech");
	strcpy(commonNameArray[1118], "Apache plume");
	strcpy(commonNameArray[1119], "Fountain bamboo");
	strcpy(commonNameArray[1120], "Asafoetida");
	strcpy(commonNameArray[1121], "Giant fennel");
	strcpy(commonNameArray[1122], "Galbanum");
	strcpy(commonNameArray[1123], "Musk root");
	strcpy(commonNameArray[1124], "Sheep's fescue");
	strcpy(commonNameArray[1125], "Fig");
	strcpy(commonNameArray[1126], "Wild fig");
	strcpy(commonNameArray[1127], "Queen of the prairie");
	strcpy(commonNameArray[1128], "Meadowsweet");
	strcpy(commonNameArray[1129], "Dropwort");
	strcpy(commonNameArray[1130], "Chinese parasol tree");
	strcpy(commonNameArray[1131], "Alerce");
	strcpy(commonNameArray[1132], "Fennel");
	strcpy(commonNameArray[1133], "Florence fennel");
	strcpy(commonNameArray[1134], "Swamp privet");
	strcpy(commonNameArray[1135], "Wild olive");
	strcpy(commonNameArray[1136], "Golden bell");
	strcpy(commonNameArray[1137], "Round kumquat");
	strcpy(commonNameArray[1138], "Oval kumquat");
	strcpy(commonNameArray[1139], "Californian strawberry");
	strcpy(commonNameArray[1140], "Beach strawberry");
	strcpy(commonNameArray[1141], "Strawberry");
	strcpy(commonNameArray[1142], "Hautbois strawberry");
	strcpy(commonNameArray[1143], "Rocky Mountain strawberry");
	strcpy(commonNameArray[1144], "Wild strawberry");
	strcpy(commonNameArray[1145], "Alpine strawberry");
	strcpy(commonNameArray[1146], "Scarlet strawberry");
	strcpy(commonNameArray[1147], "Green strawberry");
	strcpy(commonNameArray[1148], "American columbo");
	strcpy(commonNameArray[1149], "Green gentian");
	strcpy(commonNameArray[1150], "White ash");
	strcpy(commonNameArray[1151], "Narrow-leaved ash");
	strcpy(commonNameArray[1152], "Ash");
	strcpy(commonNameArray[1153], "Oregon ash");
	strcpy(commonNameArray[1154], "Black ash");
	strcpy(commonNameArray[1155], "Manna ash");
	strcpy(commonNameArray[1156], "Red ash");
	strcpy(commonNameArray[1157], "Blue ash");
	strcpy(commonNameArray[1158], "Arizona ash");
	strcpy(commonNameArray[1159], "Flannel flower");
	strcpy(commonNameArray[1160], "Purple fritillary");
	strcpy(commonNameArray[1161], "Kamchatka lily");
	strcpy(commonNameArray[1162], "Crown imperial");
	strcpy(commonNameArray[1163], "Snakehead fritillary");
	strcpy(commonNameArray[1164], "Pale-flowered fritillary");
	strcpy(commonNameArray[1165], "Yellow fritillary");
	strcpy(commonNameArray[1166], "Konini");
	strcpy(commonNameArray[1167], "Fuchsia");
	strcpy(commonNameArray[1168], "Fumitory");
	strcpy(commonNameArray[1169], "Blanket flower");
	strcpy(commonNameArray[1170], "Snowdrop");
	strcpy(commonNameArray[1171], "Beetleweed");
	strcpy(commonNameArray[1172], "Goat's rue");
	strcpy(commonNameArray[1173], "Downy hemp nettle");
	strcpy(commonNameArray[1174], "Common hemp nettle");
	strcpy(commonNameArray[1175], "Gallant soldier");
	strcpy(commonNameArray[1176], "Goosegrass");
	strcpy(commonNameArray[1177], "Hedge bedstraw");
	strcpy(commonNameArray[1178], "Sweet woodruff");
	strcpy(commonNameArray[1179], "Lady's bedstraw");
	strcpy(commonNameArray[1180], "Taka-no-tsume");
	strcpy(commonNameArray[1181], "Coast silk tassel");
	strcpy(commonNameArray[1182], "Fever bush");
	strcpy(commonNameArray[1183], "Potato orchid");
	strcpy(commonNameArray[1184], "Snowberry");
	strcpy(commonNameArray[1185], "Wax berry");
	strcpy(commonNameArray[1186], "Mountain snowberry");
	strcpy(commonNameArray[1187], "Creeping snowberry");
	strcpy(commonNameArray[1188], "Alpine wintergreen");
	strcpy(commonNameArray[1189], "Mountain checkerberry");
	strcpy(commonNameArray[1190], "Checkerberry");
	strcpy(commonNameArray[1191], "Shallon");
	strcpy(commonNameArray[1192], "Black huckleberry");
	strcpy(commonNameArray[1193], "Box huckleberry");
	strcpy(commonNameArray[1194], "Dwarf huckleberry");
	strcpy(commonNameArray[1195], "Dangleberry");
	strcpy(commonNameArray[1196], "Bear huckleberry");
	strcpy(commonNameArray[1197], "Scrambling lily");
	strcpy(commonNameArray[1198], "False jasmine");
	strcpy(commonNameArray[1199], "Spanish gorse");
	strcpy(commonNameArray[1200], "Dyer's greenweed");
	strcpy(commonNameArray[1201], "Yellow gentian");
	strcpy(commonNameArray[1202], "Marsh gentian");
	strcpy(commonNameArray[1203], "Spotted gentian");
	strcpy(commonNameArray[1204], "Japanese gentian");
	strcpy(commonNameArray[1205], "Felwort");
	strcpy(commonNameArray[1206], "Ague weed");
	strcpy(commonNameArray[1207], "Cut-leafed cranesbill");
	strcpy(commonNameArray[1208], "Spotted cranesbill");
	strcpy(commonNameArray[1209], "Native carrot");
	strcpy(commonNameArray[1210], "Meadow crane's bill");
	strcpy(commonNameArray[1211], "Herb Robert");
	strcpy(commonNameArray[1212], "Wood cranesbill");
	strcpy(commonNameArray[1213], "Sticky geranium");
	strcpy(commonNameArray[1214], "Yellow avens");
	strcpy(commonNameArray[1215], "White avens");
	strcpy(commonNameArray[1216], "Water avens");
	strcpy(commonNameArray[1217], "Purple avens");
	strcpy(commonNameArray[1218], "Wood avens");
	strcpy(commonNameArray[1219], "Chilean hazel");
	strcpy(commonNameArray[1220], "American ipecacuanna");
	strcpy(commonNameArray[1221], "Indian physic");
	strcpy(commonNameArray[1222], "Maidenhair tree");
	strcpy(commonNameArray[1223], "Ginkgo");
	strcpy(commonNameArray[1224], "Horned poppy");
	strcpy(commonNameArray[1225], "Black saltwort");
	strcpy(commonNameArray[1226], "Ground ivy");
	strcpy(commonNameArray[1227], "Water locust");
	strcpy(commonNameArray[1228], "Caspian locust");
	strcpy(commonNameArray[1229], "Honey locust");
	strcpy(commonNameArray[1230], "Floating manna grass");
	strcpy(commonNameArray[1231], "Eastern mannagrass");
	strcpy(commonNameArray[1232], "Soya bean");
	strcpy(commonNameArray[1233], "Wild liquorice");
	strcpy(commonNameArray[1234], "Liquorice");
	strcpy(commonNameArray[1235], "American liquorice");
	strcpy(commonNameArray[1236], "Chinese liquorice");
	strcpy(commonNameArray[1237], "Chinese swamp cypress");
	strcpy(commonNameArray[1238], "Marsh cudweed");
	strcpy(commonNameArray[1239], "Hedge hyssop");
	strcpy(commonNameArray[1240], "Silky oak");
	strcpy(commonNameArray[1241], "Rosin weed");
	strcpy(commonNameArray[1242], "Ramtil");
	strcpy(commonNameArray[1243], "Gunnera");
	strcpy(commonNameArray[1244], "Broomweed");
	strcpy(commonNameArray[1245], "Fragrant orchid");
	strcpy(commonNameArray[1246], "Soap tree");
	strcpy(commonNameArray[1247], "Kentucky coffee tree");
	strcpy(commonNameArray[1248], "Spanish nut");
	strcpy(commonNameArray[1249], "Hemp bush");
	strcpy(commonNameArray[1250], "Sweet tea vine");
	strcpy(commonNameArray[1251], "Baby's breath");
	strcpy(commonNameArray[1252], "Spurred gentian");
	strcpy(commonNameArray[1253], "Silver-bell tree");
	strcpy(commonNameArray[1254], "Sea purslane");
	strcpy(commonNameArray[1255], "Salt tree");
	strcpy(commonNameArray[1256], "Witch hazel");
	strcpy(commonNameArray[1257], "Coral pea");
	strcpy(commonNameArray[1258], "American pennyroyal");
	strcpy(commonNameArray[1259], "Ivy");
	strcpy(commonNameArray[1260], "Nepal ivy");
	strcpy(commonNameArray[1261], "Butterfly ginger");
	strcpy(commonNameArray[1262], "Sweet vetch");
	strcpy(commonNameArray[1263], "Liquorice root");
	strcpy(commonNameArray[1264], "Bitter sneezeweed");
	strcpy(commonNameArray[1265], "Sneezeweed");
	strcpy(commonNameArray[1266], "Rosilla");
	strcpy(commonNameArray[1267], "Frostweed");
	strcpy(commonNameArray[1268], "Sunflower");
	strcpy(commonNameArray[1269], "Giant sunflower");
	strcpy(commonNameArray[1270], "Showy sunflower");
	strcpy(commonNameArray[1271], "Wild sunflower");
	strcpy(commonNameArray[1272], "Prairie sunflower");
	strcpy(commonNameArray[1273], "Jerusalem artichoke");
	strcpy(commonNameArray[1274], "Everlasting flower");
	strcpy(commonNameArray[1275], "Curry plant");
	strcpy(commonNameArray[1276], "Heliotrope");
	strcpy(commonNameArray[1277], "Stinking hellebore");
	strcpy(commonNameArray[1278], "Black hellebore");
	strcpy(commonNameArray[1279], "Green hellebore");
	strcpy(commonNameArray[1280], "Common day lily");
	strcpy(commonNameArray[1281], "Yellow day lily");
	strcpy(commonNameArray[1282], "Coastal day lily");
	strcpy(commonNameArray[1283], "Grassleaf day lily");
	strcpy(commonNameArray[1284], "Hepatica");
	strcpy(commonNameArray[1285], "Downy cow-parsnip");
	strcpy(commonNameArray[1286], "Cow parsnip");
	strcpy(commonNameArray[1287], "Rupture wort");
	strcpy(commonNameArray[1288], "Hairy rupture wort");
	strcpy(commonNameArray[1289], "Sweet rocket");
	strcpy(commonNameArray[1290], "Rock geranium");
	strcpy(commonNameArray[1291], "Alum root");
	strcpy(commonNameArray[1292], "False roselle");
	strcpy(commonNameArray[1293], "Kenaf");
	strcpy(commonNameArray[1294], "Swamp hibiscus");
	strcpy(commonNameArray[1295], "Native rosella");
	strcpy(commonNameArray[1296], "Swamp rose mallow");
	strcpy(commonNameArray[1297], "Cotton rose");
	strcpy(commonNameArray[1298], "Chinese hibiscus");
	strcpy(commonNameArray[1299], "Roselle");
	strcpy(commonNameArray[1300], "Rose of Sharon");
	strcpy(commonNameArray[1301], "Flower of an hour");
	strcpy(commonNameArray[1302], "Holy grass");
	strcpy(commonNameArray[1303], "Galleta");
	strcpy(commonNameArray[1304], "Parang");
	strcpy(commonNameArray[1305], "Sea buckthorn");
	strcpy(commonNameArray[1306], "Willow-leaved sea buckthorn");
	strcpy(commonNameArray[1307], "Chinese sea buckthorn");
	strcpy(commonNameArray[1308], "Tibetan sea buckthorn");
	strcpy(commonNameArray[1309], "Common marestail");
	strcpy(commonNameArray[1310], "Greek mustard");
	strcpy(commonNameArray[1311], "Lacebark");
	strcpy(commonNameArray[1312], "Ribbonwood");
	strcpy(commonNameArray[1313], "Sausage vine");
	strcpy(commonNameArray[1314], "Creambush");
	strcpy(commonNameArray[1315], "Rock spiraea");
	strcpy(commonNameArray[1316], "Sea sandwort");
	strcpy(commonNameArray[1317], "Two-rowed barley");
	strcpy(commonNameArray[1318], "Six-row barley");
	strcpy(commonNameArray[1319], "Foxtail barley");
	strcpy(commonNameArray[1320], "Egyptian barley");
	strcpy(commonNameArray[1321], "Barley");
	strcpy(commonNameArray[1322], "Sprat barley");
	strcpy(commonNameArray[1323], "Kuro-giboshi");
	strcpy(commonNameArray[1324], "Nankai-giboshi");
	strcpy(commonNameArray[1325], "Water violet");
	strcpy(commonNameArray[1326], "Tsi");
	strcpy(commonNameArray[1327], "Japanese raisin tree");
	strcpy(commonNameArray[1328], "Japanese hop");
	strcpy(commonNameArray[1329], "Hop");
	strcpy(commonNameArray[1330], "Bluebell");
	strcpy(commonNameArray[1331], "Hyacinth");
	strcpy(commonNameArray[1332], "Seven barks");
	strcpy(commonNameArray[1333], "Hydrangea");
	strcpy(commonNameArray[1334], "Goldenseal");
	strcpy(commonNameArray[1335], "Water pennywort");
	strcpy(commonNameArray[1336], "Pennywort");
	strcpy(commonNameArray[1337], "John's cabbage");
	strcpy(commonNameArray[1338], "Cat's breeches");
	strcpy(commonNameArray[1339], "Virginia waterleaf");
	strcpy(commonNameArray[1340], "White henbane");
	strcpy(commonNameArray[1341], "Henbane");
	strcpy(commonNameArray[1342], "Tutsan");
	strcpy(commonNameArray[1343], "St. Andrews cross");
	strcpy(commonNameArray[1344], "St. John's wort");
	strcpy(commonNameArray[1345], "Smooth cat's ear");
	strcpy(commonNameArray[1346], "Spotted hawkweed");
	strcpy(commonNameArray[1347], "Cat's ear");
	strcpy(commonNameArray[1348], "Golden weather glass");
	strcpy(commonNameArray[1349], "Hyssop");
	strcpy(commonNameArray[1350], "Rocket candytuft");
	strcpy(commonNameArray[1351], "Candytuft");
	strcpy(commonNameArray[1352], "Holly");
	strcpy(commonNameArray[1353], "Cassine");
	strcpy(commonNameArray[1354], "Large gallberry");
	strcpy(commonNameArray[1355], "Horned holly");
	strcpy(commonNameArray[1356], "Japanese holly");
	strcpy(commonNameArray[1357], "Inkberry");
	strcpy(commonNameArray[1358], "Tarajo");
	strcpy(commonNameArray[1359], "American holly");
	strcpy(commonNameArray[1360], "Winterberry");
	strcpy(commonNameArray[1361], "Yaupon holly");
	strcpy(commonNameArray[1362], "Star anise");
	strcpy(commonNameArray[1363], "Aniseed tree");
	strcpy(commonNameArray[1364], "Chinese anise");
	strcpy(commonNameArray[1365], "Jewelweed");
	strcpy(commonNameArray[1366], "Touch-me-not");
	strcpy(commonNameArray[1367], "Pale jewelweed");
	strcpy(commonNameArray[1368], "Indigo bush");
	strcpy(commonNameArray[1369], "Ploughman's spikenard");
	strcpy(commonNameArray[1370], "Golden samphire");
	strcpy(commonNameArray[1371], "Elecampane");
	strcpy(commonNameArray[1372], "Moonflower");
	strcpy(commonNameArray[1373], "Bush moon flower");
	strcpy(commonNameArray[1374], "Wild potato vine");
	strcpy(commonNameArray[1375], "Morning glory");
	strcpy(commonNameArray[1376], "Skyrocket");
	strcpy(commonNameArray[1377], "Crested iris");
	strcpy(commonNameArray[1378], "Japanese water iris");
	strcpy(commonNameArray[1379], "Stinking gladwin");
	strcpy(commonNameArray[1380], "Purple flag");
	strcpy(commonNameArray[1381], "Orris");
	strcpy(commonNameArray[1382], "Rocky Mountain iris");
	strcpy(commonNameArray[1383], "Dalmation iris");
	strcpy(commonNameArray[1384], "Yellow flag");
	strcpy(commonNameArray[1385], "Roof iris");
	strcpy(commonNameArray[1386], "Woad");
	strcpy(commonNameArray[1387], "Yellow jasmine");
	strcpy(commonNameArray[1388], "Winter-flowering jasmin");
	strcpy(commonNameArray[1389], "Jessamine");
	strcpy(commonNameArray[1390], "Twinleaf");
	strcpy(commonNameArray[1391], "Hen and chickens houseleek");
	strcpy(commonNameArray[1392], "Chilean wine palm");
	strcpy(commonNameArray[1393], "Japanese walnut");
	strcpy(commonNameArray[1394], "Heartseed walnut");
	strcpy(commonNameArray[1395], "Chinese walnut");
	strcpy(commonNameArray[1396], "Butternut");
	strcpy(commonNameArray[1397], "Arizona walnut");
	strcpy(commonNameArray[1398], "Manchurian walnut");
	strcpy(commonNameArray[1399], "Texas walnut");
	strcpy(commonNameArray[1400], "Black walnut");
	strcpy(commonNameArray[1401], "Walnut");
	strcpy(commonNameArray[1402], "Buartnut");
	strcpy(commonNameArray[1403], "Baltic rush");
	strcpy(commonNameArray[1404], "Soft rush");
	strcpy(commonNameArray[1405], "Ashe juniper");
	strcpy(commonNameArray[1406], "Californian juniper");
	strcpy(commonNameArray[1407], "Chinese juniper");
	strcpy(commonNameArray[1408], "Juniper");
	strcpy(commonNameArray[1409], "Shore juniper");
	strcpy(commonNameArray[1410], "Aligator juniper");
	strcpy(commonNameArray[1411], "Syrian juniper");
	strcpy(commonNameArray[1412], "Grecian juniper");
	strcpy(commonNameArray[1413], "Creeping juniper");
	strcpy(commonNameArray[1414], "One-seed juniper");
	strcpy(commonNameArray[1415], "Western juniper");
	strcpy(commonNameArray[1416], "Desert juniper");
	strcpy(commonNameArray[1417], "Prickly juniper");
	strcpy(commonNameArray[1418], "Himalayan juniper");
	strcpy(commonNameArray[1419], "Temple juniper");
	strcpy(commonNameArray[1420], "Savine");
	strcpy(commonNameArray[1421], "Rocky Mountain juniper");
	strcpy(commonNameArray[1422], "Southern redcedar");
	strcpy(commonNameArray[1423], "Flaky juniper");
	strcpy(commonNameArray[1424], "Pencil cedar");
	strcpy(commonNameArray[1425], "Sheep laurel");
	strcpy(commonNameArray[1426], "Mountain laurel");
	strcpy(commonNameArray[1427], "Swamp laurel");
	strcpy(commonNameArray[1428], "Bachelor's button");
	strcpy(commonNameArray[1429], "Fluellen");
	strcpy(commonNameArray[1430], "Kinugasaso");
	strcpy(commonNameArray[1431], "Field scabious");
	strcpy(commonNameArray[1432], "Rewarewa");
	strcpy(commonNameArray[1433], "Red hot poker");
	strcpy(commonNameArray[1434], "Junegrass");
	strcpy(commonNameArray[1435], "Golden rain tree");
	strcpy(commonNameArray[1436], "Hyacinth bean");
	strcpy(commonNameArray[1437], "Scotch laburnum");
	strcpy(commonNameArray[1438], "Laburnum");
	strcpy(commonNameArray[1439], "Red root");
	strcpy(commonNameArray[1440], "Perennial lettuce");
	strcpy(commonNameArray[1441], "Lettuce");
	strcpy(commonNameArray[1442], "Celtuce");
	strcpy(commonNameArray[1443], "Wild lettuce");
	strcpy(commonNameArray[1444], "Huon pine");
	strcpy(commonNameArray[1445], "Bottle gourd");
	strcpy(commonNameArray[1446], "Crape myrtle");
	strcpy(commonNameArray[1447], "Intoxicating mint");
	strcpy(commonNameArray[1448], "White dead nettle");
	strcpy(commonNameArray[1449], "Henbit");
	strcpy(commonNameArray[1450], "Yellow archangel");
	strcpy(commonNameArray[1451], "Red dead nettle");
	strcpy(commonNameArray[1452], "Chilean bellflower");
	strcpy(commonNameArray[1453], "Nipplewort");
	strcpy(commonNameArray[1454], "Zabala fruit");
	strcpy(commonNameArray[1455], "Larch");
	strcpy(commonNameArray[1456], "Japanese larch");
	strcpy(commonNameArray[1457], "Tamarack");
	strcpy(commonNameArray[1458], "Sub-alpine larch");
	strcpy(commonNameArray[1459], "Western larch");
	strcpy(commonNameArray[1460], "Siberian larch");
	strcpy(commonNameArray[1461], "Dunkeld hybrid larch");
	strcpy(commonNameArray[1462], "Creosote bush");
	strcpy(commonNameArray[1463], "Gladich");
	strcpy(commonNameArray[1464], "Laserwort");
	strcpy(commonNameArray[1465], "Yellow-flowered pea");
	strcpy(commonNameArray[1466], "Beach pea");
	strcpy(commonNameArray[1467], "Perennial sweet pea");
	strcpy(commonNameArray[1468], "Bitter vetch");
	strcpy(commonNameArray[1469], "Lord Anson's pea");
	strcpy(commonNameArray[1470], "Sweet pea");
	strcpy(commonNameArray[1471], "Meadow vetchling");
	strcpy(commonNameArray[1472], "Chickling pea");
	strcpy(commonNameArray[1473], "Earthnut pea");
	strcpy(commonNameArray[1474], "Pukatea");
	strcpy(commonNameArray[1475], "Chilean laurel");
	strcpy(commonNameArray[1476], "Bay tree");
	strcpy(commonNameArray[1477], "Lavender");
	strcpy(commonNameArray[1478], "Spike lavender");
	strcpy(commonNameArray[1479], "French lavender");
	strcpy(commonNameArray[1480], "Tree Mallow");
	strcpy(commonNameArray[1481], "Lavatera");
	strcpy(commonNameArray[1482], "Tree lavatera");
	strcpy(commonNameArray[1483], "Labrador tea");
	strcpy(commonNameArray[1484], "Wild rosemary");
	strcpy(commonNameArray[1485], "Venus' looking glass");
	strcpy(commonNameArray[1486], "Corkwood");
	strcpy(commonNameArray[1487], "Duckweed");
	strcpy(commonNameArray[1488], "Lentil");
	strcpy(commonNameArray[1489], "Rakaf");
	strcpy(commonNameArray[1490], "Rough hawkbit");
	strcpy(commonNameArray[1491], "Edelweiss");
	strcpy(commonNameArray[1492], "Motherwort");
	strcpy(commonNameArray[1493], "Chinese motherwort");
	strcpy(commonNameArray[1494], "Pepperwort");
	strcpy(commonNameArray[1495], "Dittander");
	strcpy(commonNameArray[1496], "Maca");
	strcpy(commonNameArray[1497], "Cress");
	strcpy(commonNameArray[1498], "Wild pepper-grass");
	strcpy(commonNameArray[1499], "Yellow silver pine");
	strcpy(commonNameArray[1500], "Coast tea-tree");
	strcpy(commonNameArray[1501], "Lemon-scented tea tree");
	strcpy(commonNameArray[1502], "Lemon tea-tree");
	strcpy(commonNameArray[1503], "Tea-tree");
	strcpy(commonNameArray[1504], "Shasta daisy");
	strcpy(commonNameArray[1505], "Ox-eye daisy");
	strcpy(commonNameArray[1506], "Sand lily");
	strcpy(commonNameArray[1507], "Summer snowflake");
	strcpy(commonNameArray[1508], "Spring snowflake");
	strcpy(commonNameArray[1509], "Lovage");
	strcpy(commonNameArray[1510], "Bitter-root");
	strcpy(commonNameArray[1511], "Himalayan honeysuckle");
	strcpy(commonNameArray[1512], "Lyme grass");
	strcpy(commonNameArray[1513], "Giant wild rye");
	strcpy(commonNameArray[1514], "Volga wild rye");
	strcpy(commonNameArray[1515], "Squaw grass");
	strcpy(commonNameArray[1516], "Gayfeather");
	strcpy(commonNameArray[1517], "Mountain lovage");
	strcpy(commonNameArray[1518], "Scottish lovage");
	strcpy(commonNameArray[1519], "Kao-pau");
	strcpy(commonNameArray[1520], "Chinese privet");
	strcpy(commonNameArray[1521], "Privet");
	strcpy(commonNameArray[1522], "Golden-rayed lily");
	strcpy(commonNameArray[1523], "Hong Kong lily");
	strcpy(commonNameArray[1524], "Fire lily");
	strcpy(commonNameArray[1525], "Meadow lily");
	strcpy(commonNameArray[1526], "Madonna lily");
	strcpy(commonNameArray[1527], "Columbia tiger lily");
	strcpy(commonNameArray[1528], "Morning star lily");
	strcpy(commonNameArray[1529], "Bamboo lily");
	strcpy(commonNameArray[1530], "Tiger lily");
	strcpy(commonNameArray[1531], "White trumpet lily");
	strcpy(commonNameArray[1532], "Turk's Cap lily");
	strcpy(commonNameArray[1533], "Panther lily");
	strcpy(commonNameArray[1534], "Wood lily");
	strcpy(commonNameArray[1535], "Coral lily");
	strcpy(commonNameArray[1536], "Swamp lily");
	strcpy(commonNameArray[1537], "Poached egg plant");
	strcpy(commonNameArray[1538], "Sea lavender");
	strcpy(commonNameArray[1539], "Yellow toadflax");
	strcpy(commonNameArray[1540], "Spice bush");
	strcpy(commonNameArray[1541], "Twinflower");
	strcpy(commonNameArray[1542], "Pale flax");
	strcpy(commonNameArray[1543], "Purging flax");
	strcpy(commonNameArray[1544], "Perennial flax");
	strcpy(commonNameArray[1545], "Flax");
	strcpy(commonNameArray[1546], "Oriental sweet gum");
	strcpy(commonNameArray[1547], "Sweet gum");
	strcpy(commonNameArray[1548], "Tulip tree");
	strcpy(commonNameArray[1549], "Tanbark oak");
	strcpy(commonNameArray[1550], "Paint Indian");
	strcpy(commonNameArray[1551], "Gromwell");
	strcpy(commonNameArray[1552], "Cabbage palm");
	strcpy(commonNameArray[1553], "Cardinal flower");
	strcpy(commonNameArray[1554], "Lobelia");
	strcpy(commonNameArray[1555], "Pale spike");
	strcpy(commonNameArray[1556], "Devil's tobacco");
	strcpy(commonNameArray[1557], "Sweet alyssum");
	strcpy(commonNameArray[1558], "Italian ryegrass");
	strcpy(commonNameArray[1559], "Perennial ryegrass");
	strcpy(commonNameArray[1560], "Darnel");
	strcpy(commonNameArray[1561], "Longleaf mat-rush");
	strcpy(commonNameArray[1562], "Biscuitroot");
	strcpy(commonNameArray[1563], "Pestle parsnip");
	strcpy(commonNameArray[1564], "Fly honeysuckle");
	strcpy(commonNameArray[1565], "Italian honeysuckle");
	strcpy(commonNameArray[1566], "Twinberry");
	strcpy(commonNameArray[1567], "Boxleaf honeysuckle");
	strcpy(commonNameArray[1568], "Honeysuckle");
	strcpy(commonNameArray[1569], "Trumpet honeysuckle");
	strcpy(commonNameArray[1570], "Bird's foot trefoil");
	strcpy(commonNameArray[1571], "Greater bird's foot trefoil");
	strcpy(commonNameArray[1572], "Asparagus pea");
	strcpy(commonNameArray[1573], "Water purslane");
	strcpy(commonNameArray[1574], "Arrayan");
	strcpy(commonNameArray[1575], "Honesty");
	strcpy(commonNameArray[1576], "White lupin");
	strcpy(commonNameArray[1577], "Blue lupin");
	strcpy(commonNameArray[1578], "Tree lupin");
	strcpy(commonNameArray[1579], "Yellow lupin");
	strcpy(commonNameArray[1580], "Pearl lupin");
	strcpy(commonNameArray[1581], "Ragged Robin");
	strcpy(commonNameArray[1582], "Box thorn");
	strcpy(commonNameArray[1583], "Christmas berry");
	strcpy(commonNameArray[1584], "Chinese boxthorn");
	strcpy(commonNameArray[1585], "Pale wolfberry");
	strcpy(commonNameArray[1586], "Tomato");
	strcpy(commonNameArray[1587], "Currant tomato");
	strcpy(commonNameArray[1588], "Common club moss");
	strcpy(commonNameArray[1589], "Fir clubmoss");
	strcpy(commonNameArray[1590], "Club moss");
	strcpy(commonNameArray[1591], "Water horehound");
	strcpy(commonNameArray[1592], "Gypsywort");
	strcpy(commonNameArray[1593], "Bugleweed");
	strcpy(commonNameArray[1594], "Golden spider lily");
	strcpy(commonNameArray[1595], "Spider lily");
	strcpy(commonNameArray[1596], "Resurrection lily");
	strcpy(commonNameArray[1597], "Skeleton weed");
	strcpy(commonNameArray[1598], "Yellow skunk cabbage");
	strcpy(commonNameArray[1599], "Gooseneck loosestrife");
	strcpy(commonNameArray[1600], "Creeping Jenny");
	strcpy(commonNameArray[1601], "Yellow loosestrife");
	strcpy(commonNameArray[1602], "Purple loosestrife");
	strcpy(commonNameArray[1603], "Macadamia");
	strcpy(commonNameArray[1604], "Queensland nut");
	strcpy(commonNameArray[1605], "Plume poppy");
	strcpy(commonNameArray[1606], "Osage orange");
	strcpy(commonNameArray[1607], "Chile tarweed");
	strcpy(commonNameArray[1608], "Cucumber tree");
	strcpy(commonNameArray[1609], "Lily tree");
	strcpy(commonNameArray[1610], "Mu-lan");
	strcpy(commonNameArray[1611], "Star magnolia");
	strcpy(commonNameArray[1612], "Laurel magnolia");
	strcpy(commonNameArray[1613], "Oregon grape");
	strcpy(commonNameArray[1614], "Mexican barberry");
	strcpy(commonNameArray[1615], "Creeping Oregon grape");
	strcpy(commonNameArray[1616], "Texas mahonia");
	strcpy(commonNameArray[1617], "Southern crab");
	strcpy(commonNameArray[1618], "Chinese crab");
	strcpy(commonNameArray[1619], "Garland crab");
	strcpy(commonNameArray[1620], "Apple");
	strcpy(commonNameArray[1621], "Oregon crab");
	strcpy(commonNameArray[1622], "Prairie crab");
	strcpy(commonNameArray[1623], "Chinese apple");
	strcpy(commonNameArray[1624], "Crab apple");
	strcpy(commonNameArray[1625], "Paradise apple");
	strcpy(commonNameArray[1626], "Dwarf mallow");
	strcpy(commonNameArray[1627], "Cheeseweed");
	strcpy(commonNameArray[1628], "Mallow");
	strcpy(commonNameArray[1629], "Chinese mallow");
	strcpy(commonNameArray[1630], "Mandrake");
	strcpy(commonNameArray[1631], "Bigroot");
	strcpy(commonNameArray[1632], "Chilicothe");
	strcpy(commonNameArray[1633], "Pearl berry");
	strcpy(commonNameArray[1634], "White horehound");
	strcpy(commonNameArray[1635], "Water clover");
	strcpy(commonNameArray[1636], "Pineapple weed");
	strcpy(commonNameArray[1637], "German camomile");
	strcpy(commonNameArray[1638], "Ostrich fern");
	strcpy(commonNameArray[1639], "Stock");
	strcpy(commonNameArray[1640], "Mayten tree");
	strcpy(commonNameArray[1641], "Himalayan poppy");
	strcpy(commonNameArray[1642], "Indian cucumber root");
	strcpy(commonNameArray[1643], "Moon trefoil");
	strcpy(commonNameArray[1644], "Black medick");
	strcpy(commonNameArray[1645], "Toothed bur-clover");
	strcpy(commonNameArray[1646], "Alfalfa");
	strcpy(commonNameArray[1647], "Tea tree");
	strcpy(commonNameArray[1648], "Bunchflower");
	strcpy(commonNameArray[1649], "Bead tree");
	strcpy(commonNameArray[1650], "Honey flower");
	strcpy(commonNameArray[1651], "Whitey wood");
	strcpy(commonNameArray[1652], "White melilot");
	strcpy(commonNameArray[1653], "Melilot");
	strcpy(commonNameArray[1654], "Lemon balm");
	strcpy(commonNameArray[1655], "Bastard balm");
	strcpy(commonNameArray[1656], "Canada moonseed");
	strcpy(commonNameArray[1657], "Water mint");
	strcpy(commonNameArray[1658], "Corn mint");
	strcpy(commonNameArray[1659], "Japanese mint");
	strcpy(commonNameArray[1660], "American wild mint");
	strcpy(commonNameArray[1661], "Asian mint");
	strcpy(commonNameArray[1662], "Hart's pennyroyal");
	strcpy(commonNameArray[1663], "Horsemint");
	strcpy(commonNameArray[1664], "Pennyroyal");
	strcpy(commonNameArray[1665], "Corsican mint");
	strcpy(commonNameArray[1666], "Spearmint");
	strcpy(commonNameArray[1667], "Round-leaved mint");
	strcpy(commonNameArray[1668], "Ginger mint");
	strcpy(commonNameArray[1669], "Eau de Cologne mint");
	strcpy(commonNameArray[1670], "White peppermint");
	strcpy(commonNameArray[1671], "Black peppermint");
	strcpy(commonNameArray[1672], "Red raripila mint");
	strcpy(commonNameArray[1673], "Apple mint");
	strcpy(commonNameArray[1674], "Bogbean");
	strcpy(commonNameArray[1675], "False huckleberry");
	strcpy(commonNameArray[1676], "Annual mercury");
	strcpy(commonNameArray[1677], "Dog's mercury");
	strcpy(commonNameArray[1678], "Mountain bell");
	strcpy(commonNameArray[1679], "Oyster plant");
	strcpy(commonNameArray[1680], "Ice plant");
	strcpy(commonNameArray[1681], "Medlar");
	strcpy(commonNameArray[1682], "Dawn redwood");
	strcpy(commonNameArray[1683], "Pohutukawa");
	strcpy(commonNameArray[1684], "Northern rata");
	strcpy(commonNameArray[1685], "Southern rata");
	strcpy(commonNameArray[1686], "Spignel");
	strcpy(commonNameArray[1687], "Banana shrub");
	strcpy(commonNameArray[1688], "Yerba buena");
	strcpy(commonNameArray[1689], "Savory");
	strcpy(commonNameArray[1690], "Yam daisy");
	strcpy(commonNameArray[1691], "Wood millet");
	strcpy(commonNameArray[1692], "Yellow monkey flower");
	strcpy(commonNameArray[1693], "Great purple monkey flower");
	strcpy(commonNameArray[1694], "Monkey musk");
	strcpy(commonNameArray[1695], "Mauka");
	strcpy(commonNameArray[1696], "Marvel of Peru");
	strcpy(commonNameArray[1697], "Amur silver grass");
	strcpy(commonNameArray[1698], "Eulalia");
	strcpy(commonNameArray[1699], "Partridge berry");
	strcpy(commonNameArray[1700], "Mitrewort");
	strcpy(commonNameArray[1701], "Lemon bergamot");
	strcpy(commonNameArray[1702], "White basil-balm");
	strcpy(commonNameArray[1703], "Bergamot");
	strcpy(commonNameArray[1704], "Wild bergamot");
	strcpy(commonNameArray[1705], "Mint-leaved bergamot");
	strcpy(commonNameArray[1706], "Plains lemon monarda");
	strcpy(commonNameArray[1707], "Horse mint");
	strcpy(commonNameArray[1708], "Mountain pennyroyal");
	strcpy(commonNameArray[1709], "Coyote mint");
	strcpy(commonNameArray[1710], "Carrot tree");
	strcpy(commonNameArray[1711], "Povertyweed");
	strcpy(commonNameArray[1712], "Indian pipe");
	strcpy(commonNameArray[1713], "Water blinks");
	strcpy(commonNameArray[1714], "Whorlflower");
	strcpy(commonNameArray[1715], "Mulberry");
	strcpy(commonNameArray[1716], "White mulberry");
	strcpy(commonNameArray[1717], "Korean mulberry");
	strcpy(commonNameArray[1718], "Kuwa");
	strcpy(commonNameArray[1719], "Himalayan mulberry");
	strcpy(commonNameArray[1720], "Texas mulberry");
	strcpy(commonNameArray[1721], "Mongolian mulberry");
	strcpy(commonNameArray[1722], "Black mulberry");
	strcpy(commonNameArray[1723], "Red mulberry");
	strcpy(commonNameArray[1724], "Maidenhair vine");
	strcpy(commonNameArray[1725], "Japanese banana");
	strcpy(commonNameArray[1726], "Italian grape hyacinth");
	strcpy(commonNameArray[1727], "Tassel hyacinth");
	strcpy(commonNameArray[1728], "Grape hyacinth");
	strcpy(commonNameArray[1729], "Wall lettuce");
	strcpy(commonNameArray[1730], "Winter apple");
	strcpy(commonNameArray[1731], "Turkey bush");
	strcpy(commonNameArray[1732], "Boobyalla");
	strcpy(commonNameArray[1733], "Ngaio");
	strcpy(commonNameArray[1734], "Alpine forget-me-not");
	strcpy(commonNameArray[1735], "Water forget-me-not");
	strcpy(commonNameArray[1736], "Water chickweed");
	strcpy(commonNameArray[1737], "Californian bayberry");
	strcpy(commonNameArray[1738], "Wax myrtle");
	strcpy(commonNameArray[1739], "Bog myrtle");
	strcpy(commonNameArray[1740], "Bayberry");
	strcpy(commonNameArray[1741], "Northern bayberry");
	strcpy(commonNameArray[1742], "Chinese bayberry");
	strcpy(commonNameArray[1743], "Water milfoil");
	strcpy(commonNameArray[1744], "Myriad leaf");
	strcpy(commonNameArray[1745], "Sweet cicely");
	strcpy(commonNameArray[1746], "Cape myrtle");
	strcpy(commonNameArray[1747], "Myrtle");
	strcpy(commonNameArray[1748], "White lettuce");
	strcpy(commonNameArray[1749], "Lion's foot");
	strcpy(commonNameArray[1750], "Nagi");
	strcpy(commonNameArray[1751], "Sacred bamboo");
	strcpy(commonNameArray[1752], "Mazari palm");
	strcpy(commonNameArray[1753], "Jonquil");
	strcpy(commonNameArray[1754], "Poet's narcissus");
	strcpy(commonNameArray[1755], "Wild daffodil");
	strcpy(commonNameArray[1756], "Spikenard");
	strcpy(commonNameArray[1757], "Watercress");
	strcpy(commonNameArray[1758], "Skunk weed");
	strcpy(commonNameArray[1759], "American water lotus");
	strcpy(commonNameArray[1760], "Sacred water lotus");
	strcpy(commonNameArray[1761], "Mountain holly");
	strcpy(commonNameArray[1762], "Catmint");
	strcpy(commonNameArray[1763], "Oleander");
	strcpy(commonNameArray[1764], "Bead plant");
	strcpy(commonNameArray[1765], "Shoo fly");
	strcpy(commonNameArray[1766], "Tobacco");
	strcpy(commonNameArray[1767], "Tree tobacco");
	strcpy(commonNameArray[1768], "Wild tobacco");
	strcpy(commonNameArray[1769], "Wild fennel");
	strcpy(commonNameArray[1770], "Love-in-a-mist");
	strcpy(commonNameArray[1771], "Yellow fennel flower");
	strcpy(commonNameArray[1772], "Black cumin");
	strcpy(commonNameArray[1773], "Myrtle beech");
	strcpy(commonNameArray[1774], "Red beech");
	strcpy(commonNameArray[1775], "Silver beech");
	strcpy(commonNameArray[1776], "Roblé");
	strcpy(commonNameArray[1777], "Rauli");
	strcpy(commonNameArray[1778], "Lenga");
	strcpy(commonNameArray[1779], "Black beech");
	strcpy(commonNameArray[1780], "Mountain beech");
	strcpy(commonNameArray[1781], "Common spatterdock");
	strcpy(commonNameArray[1782], "Yellow water lily");
	strcpy(commonNameArray[1783], "Spatterdock");
	strcpy(commonNameArray[1784], "White water lily");
	strcpy(commonNameArray[1785], "Fragrant water lily");
	strcpy(commonNameArray[1786], "Tuberous water lily");
	strcpy(commonNameArray[1787], "Water fringe");
	strcpy(commonNameArray[1788], "Water tupelo");
	strcpy(commonNameArray[1789], "Ogeeche lime");
	strcpy(commonNameArray[1790], "Black tupelo");
	strcpy(commonNameArray[1791], "Sweet basil");
	strcpy(commonNameArray[1792], "Bush basil");
	strcpy(commonNameArray[1793], "Oso berry");
	strcpy(commonNameArray[1794], "Water dropwort");
	strcpy(commonNameArray[1795], "Meadow parsley");
	strcpy(commonNameArray[1796], "Evening primrose");
	strcpy(commonNameArray[1797], "Hooker's evening primrose");
	strcpy(commonNameArray[1798], "Snake-needle grass");
	strcpy(commonNameArray[1799], "Olive");
	strcpy(commonNameArray[1800], "Sainfoin");
	strcpy(commonNameArray[1801], "Sensitive fern");
	strcpy(commonNameArray[1802], "Rest harrow");
	strcpy(commonNameArray[1803], "Spiny rest harrow");
	strcpy(commonNameArray[1804], "Cotton thistle");
	strcpy(commonNameArray[1805], "Adder's tongue");
	strcpy(commonNameArray[1806], "Bee orchid");
	strcpy(commonNameArray[1807], "Brown bee orchid");
	strcpy(commonNameArray[1808], "Late spider orchid");
	strcpy(commonNameArray[1809], "Fly orchid");
	strcpy(commonNameArray[1810], "Yellow bee orchid");
	strcpy(commonNameArray[1811], "Woodcock orchid");
	strcpy(commonNameArray[1812], "Early spider orchid");
	strcpy(commonNameArray[1813], "Sawfly orchid");
	strcpy(commonNameArray[1814], "Devil's club");
	strcpy(commonNameArray[1815], "Opopanax");
	strcpy(commonNameArray[1816], "Indian fig");
	strcpy(commonNameArray[1817], "Prickly pear");
	strcpy(commonNameArray[1818], "Bunny ears");
	strcpy(commonNameArray[1819], "Bastard fig");
	strcpy(commonNameArray[1820], "Bug orchis");
	strcpy(commonNameArray[1821], "Marsh orchis");
	strcpy(commonNameArray[1822], "Early purple orchis");
	strcpy(commonNameArray[1823], "Military orchis");
	strcpy(commonNameArray[1824], "Green-winged orchid");
	strcpy(commonNameArray[1825], "Dark-winged orchis");
	strcpy(commonNameArray[1826], "Dittany of Crete");
	strcpy(commonNameArray[1827], "Sweet marjoram");
	strcpy(commonNameArray[1828], "Pot marjoram");
	strcpy(commonNameArray[1829], "Bible hyssop");
	strcpy(commonNameArray[1830], "Oregano");
	strcpy(commonNameArray[1831], "Greek oregano");
	strcpy(commonNameArray[1832], "Hardy marjoram");
	strcpy(commonNameArray[1833], "Bath asparagus");
	strcpy(commonNameArray[1834], "Star of Bethlehem");
	strcpy(commonNameArray[1835], "Cancer root");
	strcpy(commonNameArray[1836], "Broom rape");
	strcpy(commonNameArray[1837], "Indian potato");
	strcpy(commonNameArray[1838], "Golden club");
	strcpy(commonNameArray[1839], "Fragrant olive");
	strcpy(commonNameArray[1840], "Holly olive");
	strcpy(commonNameArray[1841], "Woolly sweet-cicely");
	strcpy(commonNameArray[1842], "Anise-root");
	strcpy(commonNameArray[1843], "Western sweet-cicely");
	strcpy(commonNameArray[1844], "Cinnamon fern");
	strcpy(commonNameArray[1845], "Interrupted fern");
	strcpy(commonNameArray[1846], "Royal fern");
	strcpy(commonNameArray[1847], "Hop hornbeam");
	strcpy(commonNameArray[1848], "Wood sorrel");
	strcpy(commonNameArray[1849], "Yellow sorrel");
	strcpy(commonNameArray[1850], "Iron cross plant");
	strcpy(commonNameArray[1851], "Redwood sorrel");
	strcpy(commonNameArray[1852], "Bermuda buttercup");
	strcpy(commonNameArray[1853], "Yellow wood sorrel");
	strcpy(commonNameArray[1854], "Oca");
	strcpy(commonNameArray[1855], "Violet wood sorrel");
	strcpy(commonNameArray[1856], "Sorrel tree");
	strcpy(commonNameArray[1857], "Mountain sorrel");
	strcpy(commonNameArray[1858], "Crazy weed");
	strcpy(commonNameArray[1859], "Ahipa");
	strcpy(commonNameArray[1860], "Jicama");
	strcpy(commonNameArray[1861], "Golden groundsel");
	strcpy(commonNameArray[1862], "Tree peony");
	strcpy(commonNameArray[1863], "Chinese peony");
	strcpy(commonNameArray[1864], "Peony");
	strcpy(commonNameArray[1865], "Moutan");
	strcpy(commonNameArray[1866], "Christ's thorn");
	strcpy(commonNameArray[1867], "Ginseng");
	strcpy(commonNameArray[1868], "Japanese ginseng");
	strcpy(commonNameArray[1869], "American ginseng");
	strcpy(commonNameArray[1870], "Sea daffodil");
	strcpy(commonNameArray[1871], "Old witch grass");
	strcpy(commonNameArray[1872], "European millet");
	strcpy(commonNameArray[1873], "Vine mesquite");
	strcpy(commonNameArray[1874], "Arctic poppy");
	strcpy(commonNameArray[1875], "Oriental poppy");
	strcpy(commonNameArray[1876], "Corn poppy");
	strcpy(commonNameArray[1877], "Opium poppy");
	strcpy(commonNameArray[1878], "Quito palm");
	strcpy(commonNameArray[1879], "Pellitory of the wall");
	strcpy(commonNameArray[1880], "Herb Paris");
	strcpy(commonNameArray[1881], "Grass of Parnassus");
	strcpy(commonNameArray[1882], "Algerian tea");
	strcpy(commonNameArray[1883], "Guayule");
	strcpy(commonNameArray[1884], "Wild quinine");
	strcpy(commonNameArray[1885], "Virginia creeper");
	strcpy(commonNameArray[1886], "Boston ivy");
	strcpy(commonNameArray[1887], "Passion flower");
	strcpy(commonNameArray[1888], "Passion fruit");
	strcpy(commonNameArray[1889], "Maypops");
	strcpy(commonNameArray[1890], "Banana passion fruit");
	strcpy(commonNameArray[1891], "Parsnip");
	strcpy(commonNameArray[1892], "Chinchweed");
	strcpy(commonNameArray[1893], "Common lousewort");
	strcpy(commonNameArray[1894], "Syrian rue");
	strcpy(commonNameArray[1895], "Ivy geranium");
	strcpy(commonNameArray[1896], "Rose-scented geranium");
	strcpy(commonNameArray[1897], "Lemon geranium");
	strcpy(commonNameArray[1898], "Pennyroyal geranium");
	strcpy(commonNameArray[1899], "Nutmeg geranium");
	strcpy(commonNameArray[1900], "Pheasant's foot geranium");
	strcpy(commonNameArray[1901], "Rose geranium");
	strcpy(commonNameArray[1902], "Apple geranium");
	strcpy(commonNameArray[1903], "Ivy-leaved geranium");
	strcpy(commonNameArray[1904], "Oak-leaved geranium");
	strcpy(commonNameArray[1905], "Peppermint geranium");
	strcpy(commonNameArray[1906], "White arrow arum");
	strcpy(commonNameArray[1907], "Green arrow arum");
	strcpy(commonNameArray[1908], "Garlic cress");
	strcpy(commonNameArray[1909], "Chinese fountain grass");
	strcpy(commonNameArray[1910], "Pearl millet");
	strcpy(commonNameArray[1911], "Sand-dune penstemon");
	strcpy(commonNameArray[1912], "Yellow penstemon");
	strcpy(commonNameArray[1913], "Small-flowered penstemon");
	strcpy(commonNameArray[1914], "Virginian stonecrop");
	strcpy(commonNameArray[1915], "Squaw apple");
	strcpy(commonNameArray[1916], "Yampa");
	strcpy(commonNameArray[1917], "Shiso");
	strcpy(commonNameArray[1918], "Purple shiso");
	strcpy(commonNameArray[1919], "Silk vine");
	strcpy(commonNameArray[1920], "Russian sage");
	strcpy(commonNameArray[1921], "Red bay");
	strcpy(commonNameArray[1922], "Dwarf geebung");
	strcpy(commonNameArray[1923], "Broad-leaved geebong");
	strcpy(commonNameArray[1924], "Pin-leaf geebung");
	strcpy(commonNameArray[1925], "Butterbur");
	strcpy(commonNameArray[1926], "Sweet coltsfoot");
	strcpy(commonNameArray[1927], "Sweet butterbur");
	strcpy(commonNameArray[1928], "Parsley");
	strcpy(commonNameArray[1929], "Hamburg parsley");
	strcpy(commonNameArray[1930], "Corn caraway");
	strcpy(commonNameArray[1931], "Hog's fennel");
	strcpy(commonNameArray[1932], "Masterwort");
	strcpy(commonNameArray[1933], "Marsh hog's fennel");
	strcpy(commonNameArray[1934], "Boldu");
	strcpy(commonNameArray[1935], "Fiddleneck");
	strcpy(commonNameArray[1936], "Canary grass");
	strcpy(commonNameArray[1937], "Runner bean");
	strcpy(commonNameArray[1938], "Lima bean");
	strcpy(commonNameArray[1939], "French bean");
	strcpy(commonNameArray[1940], "Amur cork tree");
	strcpy(commonNameArray[1941], "Mock orange");
	strcpy(commonNameArray[1942], "Jerusalem sage");
	strcpy(commonNameArray[1943], "Lamwick plant");
	strcpy(commonNameArray[1944], "Garden phlox");
	strcpy(commonNameArray[1945], "Senegal date palm");
	strcpy(commonNameArray[1946], "False mistletoe");
	strcpy(commonNameArray[1947], "Wharariki");
	strcpy(commonNameArray[1948], "New Zealand flax");
	strcpy(commonNameArray[1949], "Japanese photinia");
	strcpy(commonNameArray[1950], "Common reed");
	strcpy(commonNameArray[1951], "Lopseed");
	strcpy(commonNameArray[1952], "Frogfruit");
	strcpy(commonNameArray[1953], "Alpine celery pine");
	strcpy(commonNameArray[1954], "Celery top pine");
	strcpy(commonNameArray[1955], "Tanekaha");
	strcpy(commonNameArray[1956], "Stone bamboo");
	strcpy(commonNameArray[1957], "Half-black bamboo");
	strcpy(commonNameArray[1958], "Golden bamboo");
	strcpy(commonNameArray[1959], "Yellow-groove bamboo");
	strcpy(commonNameArray[1960], "Madake");
	strcpy(commonNameArray[1961], "Sweetshoot bamboo");
	strcpy(commonNameArray[1962], "Moso-chiku");
	strcpy(commonNameArray[1963], "Zig-zag bamboo");
	strcpy(commonNameArray[1964], "Kei-chiku");
	strcpy(commonNameArray[1965], "Big-node bamboo");
	strcpy(commonNameArray[1966], "Black bamboo");
	strcpy(commonNameArray[1967], "Ha-chiku");
	strcpy(commonNameArray[1968], "Kurodake");
	strcpy(commonNameArray[1969], "Ougon-kouchiku");
	strcpy(commonNameArray[1970], "Kou-chiku");
	strcpy(commonNameArray[1971], "Giant timber bamboo");
	strcpy(commonNameArray[1972], "Winter cherry");
	strcpy(commonNameArray[1973], "Cutleaf ground cherry");
	strcpy(commonNameArray[1974], "Clammy ground cherry");
	strcpy(commonNameArray[1975], "Tomatillo");
	strcpy(commonNameArray[1976], "Goldenberry");
	strcpy(commonNameArray[1977], "Wild tomatillo");
	strcpy(commonNameArray[1978], "Strawberry tomato");
	strcpy(commonNameArray[1979], "Ground cherry");
	strcpy(commonNameArray[1980], "Sticky ground cherry");
	strcpy(commonNameArray[1981], "Ninebark");
	strcpy(commonNameArray[1982], "Roundheaded rampion");
	strcpy(commonNameArray[1983], "Spiked rampion");
	strcpy(commonNameArray[1984], "Indian poke");
	strcpy(commonNameArray[1985], "Pokeweed");
	strcpy(commonNameArray[1986], "Bella sombra");
	strcpy(commonNameArray[1987], "Norway spruce");
	strcpy(commonNameArray[1988], "Chinese spruce");
	strcpy(commonNameArray[1989], "Sargent spruce");
	strcpy(commonNameArray[1990], "Weeping spruce");
	strcpy(commonNameArray[1991], "Mountain spruce");
	strcpy(commonNameArray[1992], "White spruce");
	strcpy(commonNameArray[1993], "Sakhalin spruce");
	strcpy(commonNameArray[1994], "Yezo spruce");
	strcpy(commonNameArray[1995], "Black spruce");
	strcpy(commonNameArray[1996], "Serbian spruce");
	strcpy(commonNameArray[1997], "Caucasian spruce");
	strcpy(commonNameArray[1998], "Blue spruce");
	strcpy(commonNameArray[1999], "Purple-coned spruce");
	strcpy(commonNameArray[2000], "Red spruce");
	strcpy(commonNameArray[2001], "Sitka spruce");
	strcpy(commonNameArray[2002], "Morinda spruce");
	strcpy(commonNameArray[2003], "Bristly ox-tongue");
	strcpy(commonNameArray[2004], "Hawkweed ox-tongue");
	strcpy(commonNameArray[2005], "Lily of the valley bush");
	strcpy(commonNameArray[2006], "Mouse-ear hawkweed");
	strcpy(commonNameArray[2007], "Aniseed");
	strcpy(commonNameArray[2008], "Greater burnet saxifrage");
	strcpy(commonNameArray[2009], "Burnet saxifrage");
	strcpy(commonNameArray[2010], "Bitter bark");
	strcpy(commonNameArray[2011], "Butterwort");
	strcpy(commonNameArray[2012], "White-bark pine");
	strcpy(commonNameArray[2013], "Bristle-cone pine");
	strcpy(commonNameArray[2014], "Chinese white pine");
	strcpy(commonNameArray[2015], "Mexican white pine");
	strcpy(commonNameArray[2016], "Jack pine");
	strcpy(commonNameArray[2017], "Lace-bark pine");
	strcpy(commonNameArray[2018], "Swiss stone pine");
	strcpy(commonNameArray[2019], "Siberian pine");
	strcpy(commonNameArray[2020], "Mexican pine nut");
	strcpy(commonNameArray[2021], "Beach pine");
	strcpy(commonNameArray[2022], "Big-cone pine");
	strcpy(commonNameArray[2023], "Cerro potosi pinyon");
	strcpy(commonNameArray[2024], "Japanese red pine");
	strcpy(commonNameArray[2025], "Short-leaf pine");
	strcpy(commonNameArray[2026], "Rocky Mountain piñon");
	strcpy(commonNameArray[2027], "Limber pine");
	strcpy(commonNameArray[2028], "Chilghoza pine");
	strcpy(commonNameArray[2029], "Aleppo pine");
	strcpy(commonNameArray[2030], "Korean nut pine");
	strcpy(commonNameArray[2031], "Sugar pine");
	strcpy(commonNameArray[2032], "Smooth-leaf pine");
	strcpy(commonNameArray[2033], "Single leaf piñon");
	strcpy(commonNameArray[2034], "Montezuma pine");
	strcpy(commonNameArray[2035], "Western white pine");
	strcpy(commonNameArray[2036], "Dwarf mountain pine");
	strcpy(commonNameArray[2037], "Bishop's pine");
	strcpy(commonNameArray[2038], "Austrian pine");
	strcpy(commonNameArray[2039], "Corsican pine");
	strcpy(commonNameArray[2040], "Pitch pine");
	strcpy(commonNameArray[2041], "Japanese white pine");
	strcpy(commonNameArray[2042], "Mexican weeping pine");
	strcpy(commonNameArray[2043], "Maritime pine");
	strcpy(commonNameArray[2044], "Italian stone pine");
	strcpy(commonNameArray[2045], "Ponderosa pine");
	strcpy(commonNameArray[2046], "Dwarf Siberian pine");
	strcpy(commonNameArray[2047], "Prickle pine");
	strcpy(commonNameArray[2048], "Parry piñon");
	strcpy(commonNameArray[2049], "Monterey pine");
	strcpy(commonNameArray[2050], "Paper-shell piñon");
	strcpy(commonNameArray[2051], "Red pine");
	strcpy(commonNameArray[2052], "Northern pitch pine");
	strcpy(commonNameArray[2053], "Chir pine");
	strcpy(commonNameArray[2054], "Digger pine");
	strcpy(commonNameArray[2055], "Pond pine");
	strcpy(commonNameArray[2056], "Southwestern white pine");
	strcpy(commonNameArray[2057], "White pine");
	strcpy(commonNameArray[2058], "Scot's pine");
	strcpy(commonNameArray[2059], "Chinese red pine");
	strcpy(commonNameArray[2060], "Loblolly pine");
	strcpy(commonNameArray[2061], "Twisted leaf pine");
	strcpy(commonNameArray[2062], "Japanese black pine");
	strcpy(commonNameArray[2063], "Soledad pine");
	strcpy(commonNameArray[2064], "Scrub pine");
	strcpy(commonNameArray[2065], "Himalayan blue pine");
	strcpy(commonNameArray[2066], "Betoum");
	strcpy(commonNameArray[2067], "Chinese pistache");
	strcpy(commonNameArray[2068], "Mastic tree");
	strcpy(commonNameArray[2069], "Terebinth");
	strcpy(commonNameArray[2070], "Pistachio");
	strcpy(commonNameArray[2071], "Pea");
	strcpy(commonNameArray[2072], "Field pea");
	strcpy(commonNameArray[2073], "Karo");
	strcpy(commonNameArray[2074], "Tarata");
	strcpy(commonNameArray[2075], "Weeping pittosporum");
	strcpy(commonNameArray[2076], "Tawhiwhi");
	strcpy(commonNameArray[2077], "Tobira");
	strcpy(commonNameArray[2078], "Cheesewood");
	strcpy(commonNameArray[2079], "Buck's-horn plantain");
	strcpy(commonNameArray[2080], "Ribwort plantain");
	strcpy(commonNameArray[2081], "Common plantain");
	strcpy(commonNameArray[2082], "Sea plantain");
	strcpy(commonNameArray[2083], "Hoary plantain");
	strcpy(commonNameArray[2084], "Blond psyllium");
	strcpy(commonNameArray[2085], "Fleawort");
	strcpy(commonNameArray[2086], "Butterfly orchid");
	strcpy(commonNameArray[2087], "White bog-orchid");
	strcpy(commonNameArray[2088], "Buttonwood");
	strcpy(commonNameArray[2089], "Oriental plane");
	strcpy(commonNameArray[2090], "Creamcups");
	strcpy(commonNameArray[2091], "Dwarf fern-leaf bamboo");
	strcpy(commonNameArray[2092], "Medake");
	strcpy(commonNameArray[2093], "Dwarf white-striped bamboo");
	strcpy(commonNameArray[2094], "Plumbago");
	strcpy(commonNameArray[2095], "Annual meadow grass");
	strcpy(commonNameArray[2096], "Mutton grass");
	strcpy(commonNameArray[2097], "Kentucky blue grass");
	strcpy(commonNameArray[2098], "Pine bluegrass");
	strcpy(commonNameArray[2099], "Tasmanian podocarp");
	strcpy(commonNameArray[2100], "Australian plum");
	strcpy(commonNameArray[2101], "Kusamaki");
	strcpy(commonNameArray[2102], "Alpine totara");
	strcpy(commonNameArray[2103], "Chilean podocarp");
	strcpy(commonNameArray[2104], "Willowleaf podocarp");
	strcpy(commonNameArray[2105], "Totara");
	strcpy(commonNameArray[2106], "Himalayan may apple");
	strcpy(commonNameArray[2107], "American mandrake");
	strcpy(commonNameArray[2108], "Jacob's ladder");
	strcpy(commonNameArray[2109], "Abcess root");
	strcpy(commonNameArray[2110], "Tuberose");
	strcpy(commonNameArray[2111], "Bitter milkwort");
	strcpy(commonNameArray[2112], "Senega snake root");
	strcpy(commonNameArray[2113], "Small Solomon's seal");
	strcpy(commonNameArray[2114], "Solomon's seal");
	strcpy(commonNameArray[2115], "Whorled Solomon's seal");
	strcpy(commonNameArray[2116], "Alpine knotweed");
	strcpy(commonNameArray[2117], "Willow grass");
	strcpy(commonNameArray[2118], "Knotweed");
	strcpy(commonNameArray[2119], "Bistort");
	strcpy(commonNameArray[2120], "Water smartweed");
	strcpy(commonNameArray[2121], "Black bindweed");
	strcpy(commonNameArray[2122], "Smartweed");
	strcpy(commonNameArray[2123], "Japanese knotweed");
	strcpy(commonNameArray[2124], "Red leg");
	strcpy(commonNameArray[2125], "Himalayan knotweed");
	strcpy(commonNameArray[2126], "Giant knotweed");
	strcpy(commonNameArray[2127], "False buckwheat");
	strcpy(commonNameArray[2128], "Alpine bistort");
	strcpy(commonNameArray[2129], "Yacon strawberry");
	strcpy(commonNameArray[2130], "Bearsfoot");
	strcpy(commonNameArray[2131], "Licorice fern");
	strcpy(commonNameArray[2132], "Polypody");
	strcpy(commonNameArray[2133], "Elderberry panax");
	strcpy(commonNameArray[2134], "Christmas fern");
	strcpy(commonNameArray[2135], "Hard shield fern");
	strcpy(commonNameArray[2136], "Giant holly fern");
	strcpy(commonNameArray[2137], "Hair-cap moss");
	strcpy(commonNameArray[2138], "Pickerel weed");
	strcpy(commonNameArray[2139], "Tacatricho 32");
	strcpy(commonNameArray[2140], "White poplar");
	strcpy(commonNameArray[2141], "Narrowleaf cottonwood");
	strcpy(commonNameArray[2142], "Balsam poplar");
	strcpy(commonNameArray[2143], "Eastern cottonwood");
	strcpy(commonNameArray[2144], "Cottonwood");
	strcpy(commonNameArray[2145], "Canadian aspen");
	strcpy(commonNameArray[2146], "Swamp cottonwood");
	strcpy(commonNameArray[2147], "Doronoki");
	strcpy(commonNameArray[2148], "Black poplar");
	strcpy(commonNameArray[2149], "Japanese aspen");
	strcpy(commonNameArray[2150], "Aspen poplar");
	strcpy(commonNameArray[2151], "American aspen");
	strcpy(commonNameArray[2152], "Western balsam poplar");
	strcpy(commonNameArray[2153], "Canadian poplar");
	strcpy(commonNameArray[2154], "Grey poplar");
	strcpy(commonNameArray[2155], "Rose moss");
	strcpy(commonNameArray[2156], "Green purslane");
	strcpy(commonNameArray[2157], "Golden purslane");
	strcpy(commonNameArray[2158], "Curly pondweed");
	strcpy(commonNameArray[2159], "Broad-leaved pondweed");
	strcpy(commonNameArray[2160], "Fennel-leaved pondweed");
	strcpy(commonNameArray[2161], "Silverweed");
	strcpy(commonNameArray[2162], "Tormentil");
	strcpy(commonNameArray[2163], "Shrubby cinquefoil");
	strcpy(commonNameArray[2164], "Marsh cinquefoil");
	strcpy(commonNameArray[2165], "Rough-fruited cinquefoil");
	strcpy(commonNameArray[2166], "Cinquefoil");
	strcpy(commonNameArray[2167], "Rock cinquefoil");
	strcpy(commonNameArray[2168], "Old field cinquefoil");
	strcpy(commonNameArray[2169], "Drumstick primula");
	strcpy(commonNameArray[2170], "Oxlip");
	strcpy(commonNameArray[2171], "Cowslip");
	strcpy(commonNameArray[2172], "Primrose");
	strcpy(commonNameArray[2173], "Sweet unicorn plant");
	strcpy(commonNameArray[2174], "Unicorn plant");
	strcpy(commonNameArray[2175], "Mint bush");
	strcpy(commonNameArray[2176], "King protea");
	strcpy(commonNameArray[2177], "Sugar bush");
	strcpy(commonNameArray[2178], "Plum-fruited Yew");
	strcpy(commonNameArray[2179], "Miro");
	strcpy(commonNameArray[2180], "Matai");
	strcpy(commonNameArray[2181], "Self-heal");
	strcpy(commonNameArray[2182], "Alabama cherry");
	strcpy(commonNameArray[2183], "Allegheny plum");
	strcpy(commonNameArray[2184], "American plum");
	strcpy(commonNameArray[2185], "Chickasaw plum");
	strcpy(commonNameArray[2186], "Sand plum");
	strcpy(commonNameArray[2187], "Clove cherry");
	strcpy(commonNameArray[2188], "Apricot");
	strcpy(commonNameArray[2189], "Wild cherry");
	strcpy(commonNameArray[2190], "Dwarf almond");
	strcpy(commonNameArray[2191], "Western sand cherry");
	strcpy(commonNameArray[2192], "Bokhara plum");
	strcpy(commonNameArray[2193], "Briançon apricot");
	strcpy(commonNameArray[2194], "Taiwan cherry");
	strcpy(commonNameArray[2195], "Greyleaf cherry");
	strcpy(commonNameArray[2196], "American cherry laurel");
	strcpy(commonNameArray[2197], "Cherry plum");
	strcpy(commonNameArray[2198], "Wild Himalayan cherry");
	strcpy(commonNameArray[2199], "Sour cherry");
	strcpy(commonNameArray[2200], "Morello cherry");
	strcpy(commonNameArray[2201], "Kentish red cherry");
	strcpy(commonNameArray[2202], "Bush sour cherry");
	strcpy(commonNameArray[2203], "Maraschino cherry");
	strcpy(commonNameArray[2204], "Chinese wild peach");
	strcpy(commonNameArray[2205], "Himalayan bird cherry");
	strcpy(commonNameArray[2206], "Dawyck cherry");
	strcpy(commonNameArray[2207], "Plum");
	strcpy(commonNameArray[2208], "Almond");
	strcpy(commonNameArray[2209], "Bitter cherry");
	strcpy(commonNameArray[2210], "Desert almond");
	strcpy(commonNameArray[2211], "Mongolian cherry");
	strcpy(commonNameArray[2212], "Korean cherry");
	strcpy(commonNameArray[2213], "Sour plum");
	strcpy(commonNameArray[2214], "Japanese bird cherry");
	strcpy(commonNameArray[2215], "Hog plum");
	strcpy(commonNameArray[2216], "Bush cherry");
	strcpy(commonNameArray[2217], "Holly-leaved cherry");
	strcpy(commonNameArray[2218], "Fuji cherry");
	strcpy(commonNameArray[2219], "Damson");
	strcpy(commonNameArray[2220], "Yamazakura");
	strcpy(commonNameArray[2221], "Cherry laurel");
	strcpy(commonNameArray[2222], "Portugal laurel");
	strcpy(commonNameArray[2223], "Catalina Island cherry");
	strcpy(commonNameArray[2224], "Mahaleb cherry");
	strcpy(commonNameArray[2225], "Manchurian apricot");
	strcpy(commonNameArray[2226], "Beach plum");
	strcpy(commonNameArray[2227], "Miyama cherry");
	strcpy(commonNameArray[2228], "Mexican plum");
	strcpy(commonNameArray[2229], "Smoothpit peach");
	strcpy(commonNameArray[2230], "Japanese apricot");
	strcpy(commonNameArray[2231], "Wild goose plum");
	strcpy(commonNameArray[2232], "Canadian plum");
	strcpy(commonNameArray[2233], "Japanese alpine cherry");
	strcpy(commonNameArray[2234], "Bird cherry");
	strcpy(commonNameArray[2235], "Pin cherry");
	strcpy(commonNameArray[2236], "Peach");
	strcpy(commonNameArray[2237], "Nectarine");
	strcpy(commonNameArray[2238], "Mountain cherry");
	strcpy(commonNameArray[2239], "Cambridge cherry");
	strcpy(commonNameArray[2240], "Dwarf American cherry");
	strcpy(commonNameArray[2241], "Creek plum");
	strcpy(commonNameArray[2242], "Himalayan cherry");
	strcpy(commonNameArray[2243], "Capulin cherry");
	strcpy(commonNameArray[2244], "Japanese plum");
	strcpy(commonNameArray[2245], "Rum cherry");
	strcpy(commonNameArray[2246], "Birch bark cherry");
	strcpy(commonNameArray[2247], "Siberian apricot");
	strcpy(commonNameArray[2248], "Apricot plum");
	strcpy(commonNameArray[2249], "Sloe");
	strcpy(commonNameArray[2250], "Pacific plum");
	strcpy(commonNameArray[2251], "Rosebud cherry");
	strcpy(commonNameArray[2252], "Dwarf russian almond");
	strcpy(commonNameArray[2253], "Nanking cherry");
	strcpy(commonNameArray[2254], "Flowering almond");
	strcpy(commonNameArray[2255], "Black sloe");
	strcpy(commonNameArray[2256], "Chokecherry");
	strcpy(commonNameArray[2257], "Western chokecherry");
	strcpy(commonNameArray[2258], "Rocky Mountain chokecherry");
	strcpy(commonNameArray[2259], "Black apricot");
	strcpy(commonNameArray[2260], "Duke cherry");
	strcpy(commonNameArray[2261], "Tokyo cherry");
	strcpy(commonNameArray[2262], "White balsam");
	strcpy(commonNameArray[2263], "Golden larch");
	strcpy(commonNameArray[2264], "Puahou");
	strcpy(commonNameArray[2265], "Tonkin bamboo");
	strcpy(commonNameArray[2266], "Metake");
	strcpy(commonNameArray[2267], "Douglas fir");
	strcpy(commonNameArray[2268], "Heropito");
	strcpy(commonNameArray[2269], "Strawberry guava");
	strcpy(commonNameArray[2270], "Yellow strawberry guava");
	strcpy(commonNameArray[2271], "Winged bean");
	strcpy(commonNameArray[2272], "Breadroot");
	strcpy(commonNameArray[2273], "Culen");
	strcpy(commonNameArray[2274], "Small Indian breadroot");
	strcpy(commonNameArray[2275], "Hop tree");
	strcpy(commonNameArray[2276], "Bracken");
	strcpy(commonNameArray[2277], "Caucasian wingnut");
	strcpy(commonNameArray[2278], "Japanese wingnut");
	strcpy(commonNameArray[2279], "Epaulette tree");
	strcpy(commonNameArray[2280], "Kudzu vine");
	strcpy(commonNameArray[2281], "Fleabane");
	strcpy(commonNameArray[2282], "Lungwort");
	strcpy(commonNameArray[2283], "Pasque flower");
	strcpy(commonNameArray[2284], "Pomegranate");
	strcpy(commonNameArray[2285], "Mountain mint");
	strcpy(commonNameArray[2286], "Hoary mountain mint");
	strcpy(commonNameArray[2287], "Virginia mountain mint");
	strcpy(commonNameArray[2288], "Pyracanth");
	strcpy(commonNameArray[2289], "Nepalese white thorn");
	strcpy(commonNameArray[2290], "Bog wintergreen");
	strcpy(commonNameArray[2291], "Green-flowered wintergreen");
	strcpy(commonNameArray[2292], "Wintergreen");
	strcpy(commonNameArray[2293], "Round-leaved wintergreen");
	strcpy(commonNameArray[2294], "Oil nut");
	strcpy(commonNameArray[2295], "Birch-leaved pear");
	strcpy(commonNameArray[2296], "Callery pear");
	strcpy(commonNameArray[2297], "Wild pear");
	strcpy(commonNameArray[2298], "Pear");
	strcpy(commonNameArray[2299], "Plymouth pear");
	strcpy(commonNameArray[2300], "Snow pear");
	strcpy(commonNameArray[2301], "Indian wild pear");
	strcpy(commonNameArray[2302], "Sand pear");
	strcpy(commonNameArray[2303], "Willow-leaved pear");
	strcpy(commonNameArray[2304], "Le Conte pear");
	strcpy(commonNameArray[2305], "Japanese evergreen oak");
	strcpy(commonNameArray[2306], "Sawthorn oak");
	strcpy(commonNameArray[2307], "Encina");
	strcpy(commonNameArray[2308], "White oak");
	strcpy(commonNameArray[2309], "Oriental white oak");
	strcpy(commonNameArray[2310], "Boz-pirnal oak");
	strcpy(commonNameArray[2311], "Swamp white oak");
	strcpy(commonNameArray[2312], "Turkey oak");
	strcpy(commonNameArray[2313], "Live oak");
	strcpy(commonNameArray[2314], "Kermes oak");
	strcpy(commonNameArray[2315], "Scarlet oak");
	strcpy(commonNameArray[2316], "Japanese emperor oak");
	strcpy(commonNameArray[2317], "Blue oak");
	strcpy(commonNameArray[2318], "California scrub oak");
	strcpy(commonNameArray[2319], "Northern pin oak");
	strcpy(commonNameArray[2320], "Black oak");
	strcpy(commonNameArray[2321], "Evergreen oak");
	strcpy(commonNameArray[2322], "Southern red oak");
	strcpy(commonNameArray[2323], "Hungarian oak");
	strcpy(commonNameArray[2324], "Shin oak");
	strcpy(commonNameArray[2325], "Oregon white oak");
	strcpy(commonNameArray[2326], "Holm oak");
	strcpy(commonNameArray[2327], "Shingle oak");
	strcpy(commonNameArray[2328], "Aleppo oak");
	strcpy(commonNameArray[2329], "Valonia oak");
	strcpy(commonNameArray[2330], "Californian black oak");
	strcpy(commonNameArray[2331], "American turkey oak");
	strcpy(commonNameArray[2332], "Lebanon oak");
	strcpy(commonNameArray[2333], "Californian white oak");
	strcpy(commonNameArray[2334], "Overcup oak");
	strcpy(commonNameArray[2335], "Burr oak");
	strcpy(commonNameArray[2336], "Blackjack oak");
	strcpy(commonNameArray[2337], "Swamp chestnut oak");
	strcpy(commonNameArray[2338], "Yellow chestnut oak");
	strcpy(commonNameArray[2339], "Water oak");
	strcpy(commonNameArray[2340], "Mexican blue oak");
	strcpy(commonNameArray[2341], "Pin oak");
	strcpy(commonNameArray[2342], "Sessile oak");
	strcpy(commonNameArray[2343], "Willow oak");
	strcpy(commonNameArray[2344], "Dwarf chinkapin oak");
	strcpy(commonNameArray[2345], "Rock chestnut oak");
	strcpy(commonNameArray[2346], "Downy oak");
	strcpy(commonNameArray[2347], "Sandpaper oak");
	strcpy(commonNameArray[2348], "Pedunculate oak");
	strcpy(commonNameArray[2349], "Red oak");
	strcpy(commonNameArray[2350], "Post oak");
	strcpy(commonNameArray[2351], "Cork oak");
	strcpy(commonNameArray[2352], "Wavyleaf oak");
	strcpy(commonNameArray[2353], "Chinese cork oak");
	strcpy(commonNameArray[2354], "Soap-bark tree");
	strcpy(commonNameArray[2355], "Crowfoot");
	strcpy(commonNameArray[2356], "Bulbous buttercup");
	strcpy(commonNameArray[2357], "Buttercup");
	strcpy(commonNameArray[2358], "Lesser celandine");
	strcpy(commonNameArray[2359], "Lesser spearwort");
	strcpy(commonNameArray[2360], "Creeping buttercup");
	strcpy(commonNameArray[2361], "Celery-leaved buttercup");
	strcpy(commonNameArray[2362], "Radish");
	strcpy(commonNameArray[2363], "Sea radish");
	strcpy(commonNameArray[2364], "Wild radish");
	strcpy(commonNameArray[2365], "Rat-tail radish");
	strcpy(commonNameArray[2366], "Prairie coneflower");
	strcpy(commonNameArray[2367], "Chinese foxglove");
	strcpy(commonNameArray[2368], "French scorzonera");
	strcpy(commonNameArray[2369], "Wild mignonette");
	strcpy(commonNameArray[2370], "Weld");
	strcpy(commonNameArray[2371], "Mignonette");
	strcpy(commonNameArray[2372], "Indian cherry");
	strcpy(commonNameArray[2373], "Common buckthorn");
	strcpy(commonNameArray[2374], "Red berry");
	strcpy(commonNameArray[2375], "Dahurian buckthorn");
	strcpy(commonNameArray[2376], "Alder buckthorn");
	strcpy(commonNameArray[2377], "Cascara sagrada");
	strcpy(commonNameArray[2378], "Avignon berry");
	strcpy(commonNameArray[2379], "Dyer's buckthorn");
	strcpy(commonNameArray[2380], "Indian hawthorn");
	strcpy(commonNameArray[2381], "Himalayan rhubarb");
	strcpy(commonNameArray[2382], "Sikkim rhubarb");
	strcpy(commonNameArray[2383], "Turkey rhubarb");
	strcpy(commonNameArray[2384], "Rhubarb");
	strcpy(commonNameArray[2385], "Tartarian rhubarb");
	strcpy(commonNameArray[2386], "Deer grass");
	strcpy(commonNameArray[2387], "Yellow rattle");
	strcpy(commonNameArray[2388], "Queen's crown");
	strcpy(commonNameArray[2389], "Rose root");
	strcpy(commonNameArray[2390], "Rosebay");
	strcpy(commonNameArray[2391], "Alpenrose");
	strcpy(commonNameArray[2392], "Rhododendron");
	strcpy(commonNameArray[2393], "Lapland rosebay");
	strcpy(commonNameArray[2394], "Rosebay rhododendron");
	strcpy(commonNameArray[2395], "Lemon sumach");
	strcpy(commonNameArray[2396], "Chinese gall");
	strcpy(commonNameArray[2397], "Dwarf sumach");
	strcpy(commonNameArray[2398], "Elm-leaved sumach");
	strcpy(commonNameArray[2399], "Western poison oak");
	strcpy(commonNameArray[2400], "Smooth sumach");
	strcpy(commonNameArray[2401], "Lemonade berry");
	strcpy(commonNameArray[2402], "Desert sumach");
	strcpy(commonNameArray[2403], "Poison ivy");
	strcpy(commonNameArray[2404], "Wax tree");
	strcpy(commonNameArray[2405], "Poison oak");
	strcpy(commonNameArray[2406], "Skunk bush");
	strcpy(commonNameArray[2407], "Stag's horn sumach");
	strcpy(commonNameArray[2408], "Lacquer  tree");
	strcpy(commonNameArray[2409], "Poison sumach");
	strcpy(commonNameArray[2410], "Isle of Man cabbage");
	strcpy(commonNameArray[2411], "Lundy cabbage");
	strcpy(commonNameArray[2412], "Alpine currant");
	strcpy(commonNameArray[2413], "American blackcurrant");
	strcpy(commonNameArray[2414], "Golden currant");
	strcpy(commonNameArray[2415], "Stink currant");
	strcpy(commonNameArray[2416], "Wax currant");
	strcpy(commonNameArray[2417], "Dogberry");
	strcpy(commonNameArray[2418], "Skunk currant");
	strcpy(commonNameArray[2419], "Currant-gooseberry");
	strcpy(commonNameArray[2420], "Hudson Bay currant");
	strcpy(commonNameArray[2421], "Prickly blackcurrant");
	strcpy(commonNameArray[2422], "Gummy gooseberry");
	strcpy(commonNameArray[2423], "Canyon gooseberry");
	strcpy(commonNameArray[2424], "Missouri gooseberry");
	strcpy(commonNameArray[2425], "Gooseberry-currant");
	strcpy(commonNameArray[2426], "Blackcurrant");
	strcpy(commonNameArray[2427], "Slender branched gooseberry");
	strcpy(commonNameArray[2428], "Buffalo currant");
	strcpy(commonNameArray[2429], "American mountain gooseberry");
	strcpy(commonNameArray[2430], "Rock red currant");
	strcpy(commonNameArray[2431], "Sierra gooseberry");
	strcpy(commonNameArray[2432], "Red currant");
	strcpy(commonNameArray[2433], "Flowering currant");
	strcpy(commonNameArray[2434], "Redcurrant");
	strcpy(commonNameArray[2435], "Transmontane sand verbena");
	strcpy(commonNameArray[2436], "Nordic currant");
	strcpy(commonNameArray[2437], "American red currant");
	strcpy(commonNameArray[2438], "Wild gooseberry");
	strcpy(commonNameArray[2439], "Jostaberry");
	strcpy(commonNameArray[2440], "Castor-oil plant");
	strcpy(commonNameArray[2441], "Supple Jack");
	strcpy(commonNameArray[2442], "Bristly locust");
	strcpy(commonNameArray[2443], "Black locust");
	strcpy(commonNameArray[2444], "Clammy locust");
	strcpy(commonNameArray[2445], "Great yellow cress");
	strcpy(commonNameArray[2446], "Yellow marsh-cress");
	strcpy(commonNameArray[2447], "Prickly rose");
	strcpy(commonNameArray[2448], "Low prairie rose");
	strcpy(commonNameArray[2449], "Banksia rose");
	strcpy(commonNameArray[2450], "Labrador rose");
	strcpy(commonNameArray[2451], "Dog rose");
	strcpy(commonNameArray[2452], "Pasture rose");
	strcpy(commonNameArray[2453], "Provence rose");
	strcpy(commonNameArray[2454], "China rose");
	strcpy(commonNameArray[2455], "French rose");
	strcpy(commonNameArray[2456], "Manipur wild-tea rose");
	strcpy(commonNameArray[2457], "Red-leafed rose");
	strcpy(commonNameArray[2458], "Wood rose");
	strcpy(commonNameArray[2459], "Cherokee rose");
	strcpy(commonNameArray[2460], "Cinnamon rose");
	strcpy(commonNameArray[2461], "Musk rose");
	strcpy(commonNameArray[2462], "Japanese rose");
	strcpy(commonNameArray[2463], "Nootka rose");
	strcpy(commonNameArray[2464], "Burnet rose");
	strcpy(commonNameArray[2465], "Cluster rose");
	strcpy(commonNameArray[2466], "Sweet briar");
	strcpy(commonNameArray[2467], "Ramanas rose");
	strcpy(commonNameArray[2468], "Apple rose");
	strcpy(commonNameArray[2469], "Virginia rose");
	strcpy(commonNameArray[2470], "Western wild rose");
	strcpy(commonNameArray[2471], "Damask rose");
	strcpy(commonNameArray[2472], "Tea rose");
	strcpy(commonNameArray[2473], "Rosemary");
	strcpy(commonNameArray[2474], "Indian madder");
	strcpy(commonNameArray[2475], "Wild madder");
	strcpy(commonNameArray[2476], "Madder");
	strcpy(commonNameArray[2477], "Hybrid berries");
	strcpy(commonNameArray[2478], "Mora comun");
	strcpy(commonNameArray[2479], "Alleghany blackberry");
	strcpy(commonNameArray[2480], "Mayes dewberry");
	strcpy(commonNameArray[2481], "Arctic bramble");
	strcpy(commonNameArray[2482], "Highbush blackberry");
	strcpy(commonNameArray[2483], "Dewberry");
	strcpy(commonNameArray[2484], "American dewberry");
	strcpy(commonNameArray[2485], "Cloudberry");
	strcpy(commonNameArray[2486], "Bush lawyer");
	strcpy(commonNameArray[2487], "Sand blackberry");
	strcpy(commonNameArray[2488], "Rocky Mountain raspberry");
	strcpy(commonNameArray[2489], "Golden evergreen raspberry");
	strcpy(commonNameArray[2490], "Northern dewberry");
	strcpy(commonNameArray[2491], "Blackberry");
	strcpy(commonNameArray[2492], "Mora de castilla");
	strcpy(commonNameArray[2493], "Swamp dewberry");
	strcpy(commonNameArray[2494], "Raspberry");
	strcpy(commonNameArray[2495], "Strawberry-raspberry");
	strcpy(commonNameArray[2496], "Oregon cut-leaf blackberry");
	strcpy(commonNameArray[2497], "Whitebark raspberry");
	strcpy(commonNameArray[2498], "Loganberry");
	strcpy(commonNameArray[2499], "Ceylon blackberry");
	strcpy(commonNameArray[2500], "Nepalese raspberry");
	strcpy(commonNameArray[2501], "Ceylon raspberry");
	strcpy(commonNameArray[2502], "Giant Colombian blackberry");
	strcpy(commonNameArray[2503], "Black raspberry");
	strcpy(commonNameArray[2504], "Thimbleberry");
	strcpy(commonNameArray[2505], "Japanese raspberry");
	strcpy(commonNameArray[2506], "Trailing wild raspberry");
	strcpy(commonNameArray[2507], "Japanese wineberry");
	strcpy(commonNameArray[2508], "Himalayan giant blackberry");
	strcpy(commonNameArray[2509], "Mauritius raspberry");
	strcpy(commonNameArray[2510], "Stone bramble");
	strcpy(commonNameArray[2511], "Salmonberry");
	strcpy(commonNameArray[2512], "Nagoon berry");
	strcpy(commonNameArray[2513], "American red raspberry");
	strcpy(commonNameArray[2514], "Creeping bramble");
	strcpy(commonNameArray[2515], "Southern dewberry");
	strcpy(commonNameArray[2516], "Elm-leaved bramble");
	strcpy(commonNameArray[2517], "Pacific dewberry");
	strcpy(commonNameArray[2518], "Spinach rhubarb");
	strcpy(commonNameArray[2519], "Sorrel");
	strcpy(commonNameArray[2520], "Sheeps sorrel");
	strcpy(commonNameArray[2521], "Alpine dock");
	strcpy(commonNameArray[2522], "Red dock");
	strcpy(commonNameArray[2523], "Maiden sorrel");
	strcpy(commonNameArray[2524], "Swamp dock");
	strcpy(commonNameArray[2525], "Sharp dock");
	strcpy(commonNameArray[2526], "Curled dock");
	strcpy(commonNameArray[2527], "Great water dock");
	strcpy(commonNameArray[2528], "Canaigre");
	strcpy(commonNameArray[2529], "Round-leaved dock");
	strcpy(commonNameArray[2530], "Herb Patience");
	strcpy(commonNameArray[2531], "Red-veined dock");
	strcpy(commonNameArray[2532], "Buckler-leaved sorrel");
	strcpy(commonNameArray[2533], "Sour greens");
	strcpy(commonNameArray[2534], "Bladder dock");
	strcpy(commonNameArray[2535], "Butcher's broom");
	strcpy(commonNameArray[2536], "Egyptian rue");
	strcpy(commonNameArray[2537], "Rue");
	strcpy(commonNameArray[2538], "Mountain rue");
	strcpy(commonNameArray[2539], "Scrub palmetto");
	strcpy(commonNameArray[2540], "Mexican palmetto");
	strcpy(commonNameArray[2541], "Bush palmetto");
	strcpy(commonNameArray[2542], "Cabbage palmetto");
	strcpy(commonNameArray[2543], "Bitter bloom");
	strcpy(commonNameArray[2544], "Wapato");
	strcpy(commonNameArray[2545], "Chinese arrowhead");
	strcpy(commonNameArray[2546], "Duck potato");
	strcpy(commonNameArray[2547], "Arrow head");
	strcpy(commonNameArray[2548], "Chicken claws");
	strcpy(commonNameArray[2549], "Feltleaf wiillow");
	strcpy(commonNameArray[2550], "White willow");
	strcpy(commonNameArray[2551], "Cricket bat willow");
	strcpy(commonNameArray[2552], "Golden willow");
	strcpy(commonNameArray[2553], "Peach leaved wilow");
	strcpy(commonNameArray[2554], "Common sallow");
	strcpy(commonNameArray[2555], "Eared sallow");
	strcpy(commonNameArray[2556], "Weeping willow");
	strcpy(commonNameArray[2557], "Goat willow");
	strcpy(commonNameArray[2558], "Violet willow");
	strcpy(commonNameArray[2559], "Missouri willow");
	strcpy(commonNameArray[2560], "Coyote willow");
	strcpy(commonNameArray[2561], "River willow");
	strcpy(commonNameArray[2562], "Crack willow");
	strcpy(commonNameArray[2563], "Rosegold pussy willow");
	strcpy(commonNameArray[2564], "Halberd-leaved willow");
	strcpy(commonNameArray[2565], "Woolly willow");
	strcpy(commonNameArray[2566], "Yellow willow");
	strcpy(commonNameArray[2567], "Pacific willow");
	strcpy(commonNameArray[2568], "Shining willow");
	strcpy(commonNameArray[2569], "Black willow");
	strcpy(commonNameArray[2570], "Bay willow");
	strcpy(commonNameArray[2571], "Purple osier");
	strcpy(commonNameArray[2572], "Creeping willow");
	strcpy(commonNameArray[2573], "Sitka wilow");
	strcpy(commonNameArray[2574], "Yew-leaf willow");
	strcpy(commonNameArray[2575], "Almond-leaved willow");
	strcpy(commonNameArray[2576], "Osier");
	strcpy(commonNameArray[2577], "Saltwort");
	strcpy(commonNameArray[2578], "Barilla plant");
	strcpy(commonNameArray[2579], "Thistle sage");
	strcpy(commonNameArray[2580], "Blue sage");
	strcpy(commonNameArray[2581], "Chia");
	strcpy(commonNameArray[2582], "Pineapple sage");
	strcpy(commonNameArray[2583], "Greek sage");
	strcpy(commonNameArray[2584], "Jupiter's distaff");
	strcpy(commonNameArray[2585], "Mexican chia");
	strcpy(commonNameArray[2586], "Spanish sage");
	strcpy(commonNameArray[2587], "Cancer weed");
	strcpy(commonNameArray[2588], "Californian black sage");
	strcpy(commonNameArray[2589], "Chinese sage");
	strcpy(commonNameArray[2590], "Sage");
	strcpy(commonNameArray[2591], "Apple sage");
	strcpy(commonNameArray[2592], "Meadow clary");
	strcpy(commonNameArray[2593], "White chia");
	strcpy(commonNameArray[2594], "Clary");
	strcpy(commonNameArray[2595], "Balsamic sage");
	strcpy(commonNameArray[2596], "Wild clary");
	strcpy(commonNameArray[2597], "Yellow elderberry");
	strcpy(commonNameArray[2598], "Blue elder");
	strcpy(commonNameArray[2599], "Red coast elder");
	strcpy(commonNameArray[2600], "American elder");
	strcpy(commonNameArray[2601], "Chinese elder");
	strcpy(commonNameArray[2602], "Dwarf elder");
	strcpy(commonNameArray[2603], "Black elder");
	strcpy(commonNameArray[2604], "Mexican elder");
	strcpy(commonNameArray[2605], "Elderberry");
	strcpy(commonNameArray[2606], "American red elder");
	strcpy(commonNameArray[2607], "Red elder");
	strcpy(commonNameArray[2608], "Elder");
	strcpy(commonNameArray[2609], "Brookweed");
	strcpy(commonNameArray[2610], "Blood root");
	strcpy(commonNameArray[2611], "American great burnet");
	strcpy(commonNameArray[2612], "Salad burnet");
	strcpy(commonNameArray[2613], "Great burnet");
	strcpy(commonNameArray[2614], "Wood sanicle");
	strcpy(commonNameArray[2615], "Bowstring hemp");
	strcpy(commonNameArray[2616], "Lavender-cotton");
	strcpy(commonNameArray[2617], "Holy flax");
	strcpy(commonNameArray[2618], "Western soapberry");
	strcpy(commonNameArray[2619], "Vegetable tallow");
	strcpy(commonNameArray[2620], "Tumbling Ted");
	strcpy(commonNameArray[2621], "Soapwort");
	strcpy(commonNameArray[2622], "Yellow trumpet");
	strcpy(commonNameArray[2623], "Pitcher plant");
	strcpy(commonNameArray[2624], "Chishima zasa");
	strcpy(commonNameArray[2625], "Miyako-zasa");
	strcpy(commonNameArray[2626], "Kuma-zasa");
	strcpy(commonNameArray[2627], "Azuma-zasa");
	strcpy(commonNameArray[2628], "Sassafras");
	strcpy(commonNameArray[2629], "Summer savory");
	strcpy(commonNameArray[2630], "Winter savory");
	strcpy(commonNameArray[2631], "Creeping savory");
	strcpy(commonNameArray[2632], "Thyme-leaved savory");
	strcpy(commonNameArray[2633], "Costus");
	strcpy(commonNameArray[2634], "Mountain lettuce");
	strcpy(commonNameArray[2635], "Swamp saxifrage");
	strcpy(commonNameArray[2636], "Dotted saxifrage");
	strcpy(commonNameArray[2637], "Strawberry saxifrage");
	strcpy(commonNameArray[2638], "Shepherd's needle");
	strcpy(commonNameArray[2639], "California peppertree");
	strcpy(commonNameArray[2640], "Huigen");
	strcpy(commonNameArray[2641], "Umbrella pine");
	strcpy(commonNameArray[2642], "Bulrush");
	strcpy(commonNameArray[2643], "Wool grass");
	strcpy(commonNameArray[2644], "Seaside bulrush");
	strcpy(commonNameArray[2645], "Bayonet grass");
	strcpy(commonNameArray[2646], "River club-rush");
	strcpy(commonNameArray[2647], "Spanish salsify");
	strcpy(commonNameArray[2648], "Teke-saghyz");
	strcpy(commonNameArray[2649], "Scorzonera");
	strcpy(commonNameArray[2650], "Tau-saghyz");
	strcpy(commonNameArray[2651], "Carpenter's square");
	strcpy(commonNameArray[2652], "Knotted figwort");
	strcpy(commonNameArray[2653], "Water betony");
	strcpy(commonNameArray[2654], "Common skullcap");
	strcpy(commonNameArray[2655], "Virginian skullcap");
	strcpy(commonNameArray[2656], "Rye");
	strcpy(commonNameArray[2657], "Mountain rye");
	strcpy(commonNameArray[2658], "Common stonecrop");
	strcpy(commonNameArray[2659], "Small houseleek");
	strcpy(commonNameArray[2660], "Loce restorer");
	strcpy(commonNameArray[2661], "Stonecrop");
	strcpy(commonNameArray[2662], "Crooked yellow stonecrop");
	strcpy(commonNameArray[2663], "Orpine");
	strcpy(commonNameArray[2664], "Narihiradake");
	strcpy(commonNameArray[2665], "Umbrella bamboo");
	strcpy(commonNameArray[2666], "Cobweb houseleek");
	strcpy(commonNameArray[2667], "Houseleek");
	strcpy(commonNameArray[2668], "Cineraria");
	strcpy(commonNameArray[2669], "Hoary groundsel");
	strcpy(commonNameArray[2670], "Ragwort");
	strcpy(commonNameArray[2671], "Mountain groundsel");
	strcpy(commonNameArray[2672], "Stinking groundsel");
	strcpy(commonNameArray[2673], "Groundsel");
	strcpy(commonNameArray[2674], "Wild senna");
	strcpy(commonNameArray[2675], "Coastal redwood");
	strcpy(commonNameArray[2676], "Big tree");
	strcpy(commonNameArray[2677], "Saw tooth palmetto");
	strcpy(commonNameArray[2678], "Saw-wort");
	strcpy(commonNameArray[2679], "Sesame");
	strcpy(commonNameArray[2680], "Foxtail millet");
	strcpy(commonNameArray[2681], "Yellow bristle grass");
	strcpy(commonNameArray[2682], "Green bristle grass");
	strcpy(commonNameArray[2683], "Buffalo berry");
	strcpy(commonNameArray[2684], "Okame-zasa");
	strcpy(commonNameArray[2685], "Bur cucumber");
	strcpy(commonNameArray[2686], "New Mexico prairie mallow");
	strcpy(commonNameArray[2687], "Pepper saxifrage");
	strcpy(commonNameArray[2688], "Moss campion");
	strcpy(commonNameArray[2689], "Red campion");
	strcpy(commonNameArray[2690], "White campion");
	strcpy(commonNameArray[2691], "Bladder campion");
	strcpy(commonNameArray[2692], "Compass plant");
	strcpy(commonNameArray[2693], "Cup plant");
	strcpy(commonNameArray[2694], "Prairie dock");
	strcpy(commonNameArray[2695], "White mustard");
	strcpy(commonNameArray[2696], "Charlock");
	strcpy(commonNameArray[2697], "Bastard stone-parsley");
	strcpy(commonNameArray[2698], "Tumble mustard");
	strcpy(commonNameArray[2699], "London rocket");
	strcpy(commonNameArray[2700], "Hedge mustard");
	strcpy(commonNameArray[2701], "Water parsnip");
	strcpy(commonNameArray[2702], "Skirret");
	strcpy(commonNameArray[2703], "False spikenard");
	strcpy(commonNameArray[2704], "Sarsaparilla");
	strcpy(commonNameArray[2705], "Greenbriar");
	strcpy(commonNameArray[2706], "China root");
	strcpy(commonNameArray[2707], "Carrion flower");
	strcpy(commonNameArray[2708], "Hag briar");
	strcpy(commonNameArray[2709], "False China root");
	strcpy(commonNameArray[2710], "Horse brier");
	strcpy(commonNameArray[2711], "Alexanders");
	strcpy(commonNameArray[2712], "Mock tomato");
	strcpy(commonNameArray[2713], "Horse nettle");
	strcpy(commonNameArray[2714], "Bittersweet");
	strcpy(commonNameArray[2715], "Wild potato");
	strcpy(commonNameArray[2716], "Colorado wild potato");
	strcpy(commonNameArray[2717], "Kangaroo apple");
	strcpy(commonNameArray[2718], "Mountain kangaroo apple");
	strcpy(commonNameArray[2719], "Aubergine");
	strcpy(commonNameArray[2720], "Pepino");
	strcpy(commonNameArray[2721], "Black nightshade");
	strcpy(commonNameArray[2722], "Sunberry");
	strcpy(commonNameArray[2723], "Garden huckleberry");
	strcpy(commonNameArray[2724], "Sticky nightshade");
	strcpy(commonNameArray[2725], "Pitiquiña");
	strcpy(commonNameArray[2726], "Limeña");
	strcpy(commonNameArray[2727], "Potato");
	strcpy(commonNameArray[2728], "Green kangaroo apple");
	strcpy(commonNameArray[2729], "Canadian goldenrod");
	strcpy(commonNameArray[2730], "Sweet goldenrod");
	strcpy(commonNameArray[2731], "Goldenrod");
	strcpy(commonNameArray[2732], "Field milk thistle");
	strcpy(commonNameArray[2733], "Prickly sow thistle");
	strcpy(commonNameArray[2734], "Sow thistle");
	strcpy(commonNameArray[2735], "Japanese pagoda tree");
	strcpy(commonNameArray[2736], "Mescal bean");
	strcpy(commonNameArray[2737], "Kowhai");
	strcpy(commonNameArray[2738], "Bollwyller pear");
	strcpy(commonNameArray[2739], "Korean mountain ash");
	strcpy(commonNameArray[2740], "American mountain ash");
	strcpy(commonNameArray[2741], "Whitebeam");
	strcpy(commonNameArray[2742], "Showy mountain ash");
	strcpy(commonNameArray[2743], "French hales");
	strcpy(commonNameArray[2744], "Service tree");
	strcpy(commonNameArray[2745], "Swedish whitebeam");
	strcpy(commonNameArray[2746], "Western mountain ash");
	strcpy(commonNameArray[2747], "Sitka mountain ash");
	strcpy(commonNameArray[2748], "Wild service tree");
	strcpy(commonNameArray[2749], "Sorghum");
	strcpy(commonNameArray[2750], "Millet grass");
	strcpy(commonNameArray[2751], "Bur reed");
	strcpy(commonNameArray[2752], "Cord grass");
	strcpy(commonNameArray[2753], "Prairie cord grass");
	strcpy(commonNameArray[2754], "Townsend's cord grass");
	strcpy(commonNameArray[2755], "Spanish broom");
	strcpy(commonNameArray[2756], "Corn spurrey");
	strcpy(commonNameArray[2757], "Sphagnum moss");
	strcpy(commonNameArray[2758], "Indian pink");
	strcpy(commonNameArray[2759], "Spinach");
	strcpy(commonNameArray[2760], "Japanese spiraea");
	strcpy(commonNameArray[2761], "Bridalwreath spiraea");
	strcpy(commonNameArray[2762], "Bridewort");
	strcpy(commonNameArray[2763], "Hardhack");
	strcpy(commonNameArray[2764], "Garland spiraea");
	strcpy(commonNameArray[2765], "Lady's tresses");
	strcpy(commonNameArray[2766], "Great duckweed");
	strcpy(commonNameArray[2767], "Alkali sakaton");
	strcpy(commonNameArray[2768], "Sand dropseed");
	strcpy(commonNameArray[2769], "Giant dropseed");
	strcpy(commonNameArray[2770], "Chinese artichoke");
	strcpy(commonNameArray[2771], "Downy woundwort");
	strcpy(commonNameArray[2772], "Wood betony");
	strcpy(commonNameArray[2773], "Marsh woundwort");
	strcpy(commonNameArray[2774], "Hedge woundwort");
	strcpy(commonNameArray[2775], "Prince's plume");
	strcpy(commonNameArray[2776], "Bladdernut");
	strcpy(commonNameArray[2777], "Bladder nut");
	strcpy(commonNameArray[2778], "American bladder nut");
	strcpy(commonNameArray[2779], "Chickweed");
	strcpy(commonNameArray[2780], "Chee grass");
	strcpy(commonNameArray[2781], "Esparto grass");
	strcpy(commonNameArray[2782], "Sleepy grass");
	strcpy(commonNameArray[2783], "Green needlegrass");
	strcpy(commonNameArray[2784], "Water soldier");
	strcpy(commonNameArray[2785], "Scootberry");
	strcpy(commonNameArray[2786], "Pink fivecorner");
	strcpy(commonNameArray[2787], "Storax tree");
	strcpy(commonNameArray[2788], "Shrubby seablite");
	strcpy(commonNameArray[2789], "Sea blite");
	strcpy(commonNameArray[2790], "Desert seepweed");
	strcpy(commonNameArray[2791], "Devil's bit scabious");
	strcpy(commonNameArray[2792], "Wolfberry");
	strcpy(commonNameArray[2793], "Prickly comfrey");
	strcpy(commonNameArray[2794], "Comfrey");
	strcpy(commonNameArray[2795], "Skunk cabbage");
	strcpy(commonNameArray[2796], "Asiatic sweetleaf");
	strcpy(commonNameArray[2797], "Sweet leaf");
	strcpy(commonNameArray[2798], "Hungarian lilac");
	strcpy(commonNameArray[2799], "Lilac");
	strcpy(commonNameArray[2800], "African marigold");
	strcpy(commonNameArray[2801], "Irish lace");
	strcpy(commonNameArray[2802], "Mexican tarragon");
	strcpy(commonNameArray[2803], "Muster-John-Henry");
	strcpy(commonNameArray[2804], "French marigold");
	strcpy(commonNameArray[2805], "Lemon marigold");
	strcpy(commonNameArray[2806], "English tree");
	strcpy(commonNameArray[2807], "Athel tamarisk");
	strcpy(commonNameArray[2808], "Tamarisk");
	strcpy(commonNameArray[2809], "Chinese tamarisk");
	strcpy(commonNameArray[2810], "Manna plant");
	strcpy(commonNameArray[2811], "Kashgar tree");
	strcpy(commonNameArray[2812], "Black bryony");
	strcpy(commonNameArray[2813], "Alecost");
	strcpy(commonNameArray[2814], "Dalmation pellitory");
	strcpy(commonNameArray[2815], "Pyrethrum");
	strcpy(commonNameArray[2816], "Feverfew");
	strcpy(commonNameArray[2817], "Tansy");
	strcpy(commonNameArray[2818], "Rubber dandelion");
	strcpy(commonNameArray[2819], "Dandelion");
	strcpy(commonNameArray[2820], "Swamp cypress");
	strcpy(commonNameArray[2821], "Yew");
	strcpy(commonNameArray[2822], "Pacific yew");
	strcpy(commonNameArray[2823], "Canadian yew");
	strcpy(commonNameArray[2824], "Japanese yew");
	strcpy(commonNameArray[2825], "Waratah");
	strcpy(commonNameArray[2826], "Catgut");
	strcpy(commonNameArray[2827], "New Zealand spinach");
	strcpy(commonNameArray[2828], "Rice paper plant");
	strcpy(commonNameArray[2829], "American germander");
	strcpy(commonNameArray[2830], "Wall germander");
	strcpy(commonNameArray[2831], "Cat thyme");
	strcpy(commonNameArray[2832], "Water germander");
	strcpy(commonNameArray[2833], "Wood sage");
	strcpy(commonNameArray[2834], "Bergbamboes");
	strcpy(commonNameArray[2835], "Drias plant");
	strcpy(commonNameArray[2836], "Navajo tea");
	strcpy(commonNameArray[2837], "Dog's cabbage");
	strcpy(commonNameArray[2838], "Marsh fern");
	strcpy(commonNameArray[2839], "Pennycress");
	strcpy(commonNameArray[2840], "American arbor-vitae");
	strcpy(commonNameArray[2841], "Biota");
	strcpy(commonNameArray[2842], "Western red cedar");
	strcpy(commonNameArray[2843], "Hiba");
	strcpy(commonNameArray[2844], "Cretan thyme");
	strcpy(commonNameArray[2845], "Camphor thyme");
	strcpy(commonNameArray[2846], "Headed savory");
	strcpy(commonNameArray[2847], "Cilician thyme");
	strcpy(commonNameArray[2848], "Caraway thyme");
	strcpy(commonNameArray[2849], "Mastic thyme");
	strcpy(commonNameArray[2850], "Wild thyme");
	strcpy(commonNameArray[2851], "Woolly thyme");
	strcpy(commonNameArray[2852], "Broad-leaved thyme");
	strcpy(commonNameArray[2853], "Common thyme");
	strcpy(commonNameArray[2854], "Lemon thyme");
	strcpy(commonNameArray[2855], "Twining fringed lily");
	strcpy(commonNameArray[2856], "Fringed lily");
	strcpy(commonNameArray[2857], "Foamflower");
	strcpy(commonNameArray[2858], "Tiger flower");
	strcpy(commonNameArray[2859], "American basswood");
	strcpy(commonNameArray[2860], "Carolina basswood");
	strcpy(commonNameArray[2861], "Small leaved lime");
	strcpy(commonNameArray[2862], "White basswood");
	strcpy(commonNameArray[2863], "Japanese lime");
	strcpy(commonNameArray[2864], "Mongolian lime");
	strcpy(commonNameArray[2865], "Large leaved lime");
	strcpy(commonNameArray[2866], "Silver lime");
	strcpy(commonNameArray[2867], "Common lime");
	strcpy(commonNameArray[2868], "Youth on age");
	strcpy(commonNameArray[2869], "Chinese cedar");
	strcpy(commonNameArray[2870], "Roman pimpernel");
	strcpy(commonNameArray[2871], "Upright hedge parsley");
	strcpy(commonNameArray[2872], "California nutmeg");
	strcpy(commonNameArray[2873], "Chinese nutmeg tree");
	strcpy(commonNameArray[2874], "Kaya");
	strcpy(commonNameArray[2875], "Yunnan nutmeg yew");
	strcpy(commonNameArray[2876], "Star jasmine");
	strcpy(commonNameArray[2877], "Chusan palm");
	strcpy(commonNameArray[2878], "Spiderwort");
	strcpy(commonNameArray[2879], "Salsify");
	strcpy(commonNameArray[2880], "Ling");
	strcpy(commonNameArray[2881], "Water chestnut");
	strcpy(commonNameArray[2882], "Caltrop");
	strcpy(commonNameArray[2883], "Snake gourd");
	strcpy(commonNameArray[2884], "Japanese snake gourd");
	strcpy(commonNameArray[2885], "Toad lily");
	strcpy(commonNameArray[2886], "Chickweed wintergreen");
	strcpy(commonNameArray[2887], "Piñole clover");
	strcpy(commonNameArray[2888], "Cup clover");
	strcpy(commonNameArray[2889], "Sour clover");
	strcpy(commonNameArray[2890], "Pin-point clover");
	strcpy(commonNameArray[2891], "Alsike clover");
	strcpy(commonNameArray[2892], "Crimson clover");
	strcpy(commonNameArray[2893], "Bighead clover");
	strcpy(commonNameArray[2894], "Red clover");
	strcpy(commonNameArray[2895], "White clover");
	strcpy(commonNameArray[2896], "Sea arrow grass");
	strcpy(commonNameArray[2897], "Marsh arrow grass");
	strcpy(commonNameArray[2898], "Sweet trefoil");
	strcpy(commonNameArray[2899], "Fenugreek");
	strcpy(commonNameArray[2900], "Vanilla plant");
	strcpy(commonNameArray[2901], "Red trillium");
	strcpy(commonNameArray[2902], "White trillium");
	strcpy(commonNameArray[2903], "Wakerobin");
	strcpy(commonNameArray[2904], "Toadshade");
	strcpy(commonNameArray[2905], "Painted trillium");
	strcpy(commonNameArray[2906], "Wild coffee");
	strcpy(commonNameArray[2907], "Lime berry");
	strcpy(commonNameArray[2908], "Sesame grass");
	strcpy(commonNameArray[2909], "Grassnut");
	strcpy(commonNameArray[2910], "Triticale");
	strcpy(commonNameArray[2911], "Bread wheat");
	strcpy(commonNameArray[2912], "Club wheat");
	strcpy(commonNameArray[2913], "Makha wheat");
	strcpy(commonNameArray[2914], "Spelt wheat");
	strcpy(commonNameArray[2915], "Shot wheat");
	strcpy(commonNameArray[2916], "Einkorn");
	strcpy(commonNameArray[2917], "Sanduri");
	strcpy(commonNameArray[2918], "Rivet wheat");
	strcpy(commonNameArray[2919], "Persian wheat");
	strcpy(commonNameArray[2920], "Wild emmer");
	strcpy(commonNameArray[2921], "Emmer");
	strcpy(commonNameArray[2922], "Durum wheat");
	strcpy(commonNameArray[2923], "Polish wheat");
	strcpy(commonNameArray[2924], "Khurasan wheat");
	strcpy(commonNameArray[2925], "Globeflower");
	strcpy(commonNameArray[2926], "Nasturtium");
	strcpy(commonNameArray[2927], "Dwarf nasturtium");
	strcpy(commonNameArray[2928], "Capucine");
	strcpy(commonNameArray[2929], "Canadian hemlock");
	strcpy(commonNameArray[2930], "Carolina hemlock");
	strcpy(commonNameArray[2931], "Chinese hemlock");
	strcpy(commonNameArray[2932], "Western hemlock");
	strcpy(commonNameArray[2933], "Mountain hemlock");
	strcpy(commonNameArray[2934], "Society garlic");
	strcpy(commonNameArray[2935], "Damiana");
	strcpy(commonNameArray[2936], "Tower cress");
	strcpy(commonNameArray[2937], "Coltsfoot");
	strcpy(commonNameArray[2938], "Small reed mace");
	strcpy(commonNameArray[2939], "Reedmace");
	strcpy(commonNameArray[2940], "Uñi");
	strcpy(commonNameArray[2941], "Gorse");
	strcpy(commonNameArray[2942], "Olluco");
	strcpy(commonNameArray[2943], "Winged elm");
	strcpy(commonNameArray[2944], "American elm");
	strcpy(commonNameArray[2945], "Japanese elm");
	strcpy(commonNameArray[2946], "Wych elm");
	strcpy(commonNameArray[2947], "Chinese elm");
	strcpy(commonNameArray[2948], "English elm");
	strcpy(commonNameArray[2949], "Siberian elm");
	strcpy(commonNameArray[2950], "Slippery elm");
	strcpy(commonNameArray[2951], "Rock elm");
	strcpy(commonNameArray[2952], "Cherry bark elm");
	strcpy(commonNameArray[2953], "California laurel");
	strcpy(commonNameArray[2954], "Sea oats");
	strcpy(commonNameArray[2955], "Sea squill");
	strcpy(commonNameArray[2956], "Stinging nettle");
	strcpy(commonNameArray[2957], "Roman nettle");
	strcpy(commonNameArray[2958], "Annual nettle");
	strcpy(commonNameArray[2959], "Bladderwort");
	strcpy(commonNameArray[2960], "Fairybells");
	strcpy(commonNameArray[2961], "Bellwort");
	strcpy(commonNameArray[2962], "Large-cluster blueberry");
	strcpy(commonNameArray[2963], "Low sweet blueberry");
	strcpy(commonNameArray[2964], "Farkleberry");
	strcpy(commonNameArray[2965], "Caucasian whortleberry");
	strcpy(commonNameArray[2966], "Rabbiteye blueberry");
	strcpy(commonNameArray[2967], "Dwarf bilberry");
	strcpy(commonNameArray[2968], "High-bush blueberry");
	strcpy(commonNameArray[2969], "Creeping blueberry");
	strcpy(commonNameArray[2970], "Alpine blueberry");
	strcpy(commonNameArray[2971], "Southern mountain cranberry");
	strcpy(commonNameArray[2972], "Black highbush blueberry");
	strcpy(commonNameArray[2973], "Hairy huckleberry");
	strcpy(commonNameArray[2974], "American cranberry");
	strcpy(commonNameArray[2975], "Georgia blueberry");
	strcpy(commonNameArray[2976], "Mountain huckleberry");
	strcpy(commonNameArray[2977], "Mortiño");
	strcpy(commonNameArray[2978], "Florida evergreen blueberry");
	strcpy(commonNameArray[2979], "Canadian blueberry");
	strcpy(commonNameArray[2980], "Bilberry");
	strcpy(commonNameArray[2981], "Deerberry");
	strcpy(commonNameArray[2982], "Western Blueberry");
	strcpy(commonNameArray[2983], "Evergreen huckleberry");
	strcpy(commonNameArray[2984], "Small cranberry");
	strcpy(commonNameArray[2985], "Madeiran whortleberry");
	strcpy(commonNameArray[2986], "Red bilberry");
	strcpy(commonNameArray[2987], "Kamchatka bilberry");
	strcpy(commonNameArray[2988], "Grouseberry");
	strcpy(commonNameArray[2989], "Small-cluster blueberry");
	strcpy(commonNameArray[2990], "Bog bilberry");
	strcpy(commonNameArray[2991], "Dryland blueberry");
	strcpy(commonNameArray[2992], "Rabbit-eye blueberry");
	strcpy(commonNameArray[2993], "Cowberry");
	strcpy(commonNameArray[2994], "Tobacco root");
	strcpy(commonNameArray[2995], "Indian valerian");
	strcpy(commonNameArray[2996], "Valerian");
	strcpy(commonNameArray[2997], "American valerian");
	strcpy(commonNameArray[2998], "Italian corn salad");
	strcpy(commonNameArray[2999], "Corn salad");
	strcpy(commonNameArray[3000], "Water celery");
	strcpy(commonNameArray[3001], "Eel grass");
	strcpy(commonNameArray[3002], "White hellebore");
	strcpy(commonNameArray[3003], "Moth mullein");
	strcpy(commonNameArray[3004], "Mullein");
	strcpy(commonNameArray[3005], "White mullein");
	strcpy(commonNameArray[3006], "Dark mullein");
	strcpy(commonNameArray[3007], "Wooly mullein");
	strcpy(commonNameArray[3008], "Hoary mullein");
	strcpy(commonNameArray[3009], "Great mullein");
	strcpy(commonNameArray[3010], "American blue vervain");
	strcpy(commonNameArray[3011], "Vervain");
	strcpy(commonNameArray[3012], "Hoary vervain");
	strcpy(commonNameArray[3013], "White vervain");
	strcpy(commonNameArray[3014], "Ironweed");
	strcpy(commonNameArray[3015], "American brooklime");
	strcpy(commonNameArray[3016], "Water speedwell");
	strcpy(commonNameArray[3017], "Brooklime");
	strcpy(commonNameArray[3018], "Germander speedwell");
	strcpy(commonNameArray[3019], "Common speedwell");
	strcpy(commonNameArray[3020], "Marsh speedwell");
	strcpy(commonNameArray[3021], "Beaumont's root");
	strcpy(commonNameArray[3022], "Withe rod");
	strcpy(commonNameArray[3023], "Arrow wood");
	strcpy(commonNameArray[3024], "Mooseberry");
	strcpy(commonNameArray[3025], "Wayfaring tree");
	strcpy(commonNameArray[3026], "Hobbleberry");
	strcpy(commonNameArray[3027], "Sheepberry");
	strcpy(commonNameArray[3028], "Smooth withe rod");
	strcpy(commonNameArray[3029], "Guelder rose");
	strcpy(commonNameArray[3030], "Stagberry");
	strcpy(commonNameArray[3031], "Southern black haw");
	strcpy(commonNameArray[3032], "Laurustinus");
	strcpy(commonNameArray[3033], "American vetch");
	strcpy(commonNameArray[3034], "Tufted vetch");
	strcpy(commonNameArray[3035], "Horsebean");
	strcpy(commonNameArray[3036], "Broad bean");
	strcpy(commonNameArray[3037], "Hairy tare");
	strcpy(commonNameArray[3038], "French vetch");
	strcpy(commonNameArray[3039], "Winter tares");
	strcpy(commonNameArray[3040], "Bush vetch");
	strcpy(commonNameArray[3041], "Fine-leaved vetch");
	strcpy(commonNameArray[3042], "Smooth tare");
	strcpy(commonNameArray[3043], "Large Russian vetch");
	strcpy(commonNameArray[3044], "Jerusalem pea");
	strcpy(commonNameArray[3045], "Greater periwinkle");
	strcpy(commonNameArray[3046], "Lesser periwinkle");
	strcpy(commonNameArray[3047], "Western dog violet");
	strcpy(commonNameArray[3048], "Canada violet");
	strcpy(commonNameArray[3049], "Dog violet");
	strcpy(commonNameArray[3050], "Horned violet");
	strcpy(commonNameArray[3051], "Marsh blue violet");
	strcpy(commonNameArray[3052], "Stream violet");
	strcpy(commonNameArray[3053], "Labrador violet");
	strcpy(commonNameArray[3054], "Alaska violet");
	strcpy(commonNameArray[3055], "Manchurian violet");
	strcpy(commonNameArray[3056], "Sweet violet");
	strcpy(commonNameArray[3057], "Palmate violet");
	strcpy(commonNameArray[3058], "Bird's foot violet");
	strcpy(commonNameArray[3059], "Grass pansy");
	strcpy(commonNameArray[3060], "Wood violet");
	strcpy(commonNameArray[3061], "Redwood violet");
	strcpy(commonNameArray[3062], "Wooly blue violet");
	strcpy(commonNameArray[3063], "Heartsease");
	strcpy(commonNameArray[3064], "Pansy");
	strcpy(commonNameArray[3065], "Mistletoe");
	strcpy(commonNameArray[3066], "Chaste tree");
	strcpy(commonNameArray[3067], "Bush grape");
	strcpy(commonNameArray[3068], "Summer grape");
	strcpy(commonNameArray[3069], "Amur river grape");
	strcpy(commonNameArray[3070], "Canyon grape");
	strcpy(commonNameArray[3071], "Grape");
	strcpy(commonNameArray[3072], "Spanish grape");
	strcpy(commonNameArray[3073], "California grape");
	strcpy(commonNameArray[3074], "Sweet winter grape");
	strcpy(commonNameArray[3075], "Currant grape");
	strcpy(commonNameArray[3076], "Crimson glory vine");
	strcpy(commonNameArray[3077], "Frost grape");
	strcpy(commonNameArray[3078], "Spiny vitis");
	strcpy(commonNameArray[3079], "Northern fox grape");
	strcpy(commonNameArray[3080], "Post-oak grape");
	strcpy(commonNameArray[3081], "Sweet mountain grape");
	strcpy(commonNameArray[3082], "Bird grape");
	strcpy(commonNameArray[3083], "Mustang grape");
	strcpy(commonNameArray[3084], "Red grape");
	strcpy(commonNameArray[3085], "Riverbank grape");
	strcpy(commonNameArray[3086], "Muscadine");
	strcpy(commonNameArray[3087], "Sand grape");
	strcpy(commonNameArray[3088], "Japanese horseradish");
	strcpy(commonNameArray[3089], "Desert fan palm");
	strcpy(commonNameArray[3090], "Kamahi");
	strcpy(commonNameArray[3091], "Japanese wisteria");
	strcpy(commonNameArray[3092], "American wisteria");
	strcpy(commonNameArray[3093], "Chinese wisteria");
	strcpy(commonNameArray[3094], "Silky wisteria");
	strcpy(commonNameArray[3095], "Baw-baw berry");
	strcpy(commonNameArray[3096], "Least duckweed");
	strcpy(commonNameArray[3097], "Chain fern");
	strcpy(commonNameArray[3098], "Spiny cocklebur");
	strcpy(commonNameArray[3099], "Cocklebur");
	strcpy(commonNameArray[3100], "Yellowhorn");
	strcpy(commonNameArray[3101], "Yellowroot");
	strcpy(commonNameArray[3102], "Grasstree");
	strcpy(commonNameArray[3103], "Indian basket grass");
	strcpy(commonNameArray[3104], "Spanish bayonet");
	strcpy(commonNameArray[3105], "Joshua tree");
	strcpy(commonNameArray[3106], "Spoonleaf yucca");
	strcpy(commonNameArray[3107], "Soapweed");
	strcpy(commonNameArray[3108], "Spanish dagger");
	strcpy(commonNameArray[3109], "Twisted-leaf yucca");
	strcpy(commonNameArray[3110], "Adam's needle");
	strcpy(commonNameArray[3111], "Our Lord's candle");
	strcpy(commonNameArray[3112], "Horned pondweed");
	strcpy(commonNameArray[3113], "Arum lily");
	strcpy(commonNameArray[3114], "Winged prickly ash");
	strcpy(commonNameArray[3115], "Prickly ash");
	strcpy(commonNameArray[3116], "Hercules club");
	strcpy(commonNameArray[3117], "Japanese pepper tree");
	strcpy(commonNameArray[3118], "Szechuan pepper");
	strcpy(commonNameArray[3119], "Sweet corn");
	strcpy(commonNameArray[3120], "Japanese zelkova");
	strcpy(commonNameArray[3121], "Atamasco lily");
	strcpy(commonNameArray[3122], "Sandfly bush");
	strcpy(commonNameArray[3123], "Wild rice");
	strcpy(commonNameArray[3124], "Manchurian wild rice");
	strcpy(commonNameArray[3125], "Golden alexanders");
	strcpy(commonNameArray[3126], "Jujube");
	strcpy(commonNameArray[3127], "Korean lawn grass");
	strcpy(commonNameArray[3128], "Syrian bean caper");
	firstCommonNameRun = 1;
}

	AppSetGrammar(app, ".ByName");
	AppAppendTTSPrompt(app, "Please say the common or latin name of a plant you want to search for.");
	if (!AppRecognize(app)) {
		printf("!AppRec\n");
		return;
	}
	char buf[100];
	int iCommonName = -1;
	if (NLGetIntSlotValue(AppGetNLResult(app), "common_name_said", &iCommonName) != 119) {
		AppAppendTTSPrompt(app, commonNameArray[iCommonName]);
		AppAppendTTSPrompt(app, "said.");
		char buf15[200];
		sprintf(buf15, "SELECT * FROM `plantlocations` WHERE `Common name`='%s'  GROUP BY `Latin name`", commonNameArray[iCommonName]);
		printf("%s\n", buf15);
		SQLReverseSearch(app, buf15);
		/*if (!AppRecognize(app)) {
			printf("!AppRec\n");
			return;
		}*/
		//char buf17[350];
		//sprintf(buf17, "SELECT `Latin Name`,`Common Name`,`Part of plant`,`Water`,`Calories`,`Protein`,`Fat` FROM composition WHERE `Common Name`='%s' GROUP BY `Latin name` LIMIT 0, 1", commonNameArray[iCommonName]);
		//speakComposition(app, char* type, char* str, int speak) {
		AppAppendTTSPrompt(app, "Nutritional composition:");
		char compositionBuf[300];
		strcpy(compositionBuf, commonNameArray[iCommonName]);
		speakComposition(app, "Common", compositionBuf, 1);
	/*	if (!AppRecognize(app)) {
			printf("!AppRec\n");
			return;
		}*/
		// sleep()
	}
	

	//Sleep(10000);
	//AppGotoSelf(app);
	if (!AppRecognize(app)) {
		printf("!AppRec\n");
		return;
	}
	/*
	* Get the value of the "fruit" slot
	*/
	//AppAppendPrompt(app, "you_said.wav");
	AppGotoSelf(app);


}