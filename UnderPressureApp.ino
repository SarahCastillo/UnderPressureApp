/* I used some of the SimbleeUITest source code to help build my user interface. Below is their copyright heading. 
 *  In this UnderPressureApp file, I provided comments next to the code blocks that I sourced from the SimbleeUITest.
 *  (e.g. //FROM SIMBLEE UI TEST SOURCE CODE). The rest is my original code.
 */

/*
  Copyright (c) 2015 RF Digital Corp. All Rights Reserved.

  The source code contained in this file and all intellectual property embodied in
  or covering the source code is the property of RF Digital Corp. or its licensors.
  Your right to use this source code and intellectual property is non-transferable,
  non-sub licensable, revocable, and subject to terms and conditions of the
  SIMBLEE SOFTWARE LICENSE AGREEMENT.
  http://www.simblee.com/licenses/SimbleeSoftwareLicenseAgreement.txt

  THE SOURCE CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND.

  This heading must NOT be removed from this file.
*/

#include <SimbleeForMobile.h>


//
// Screen numbers
//
#define HOME_SCREEN 1 //SIMBLEE UI TEST SOURCE CODE
#define BP_SCREEN 2
#define RECORDS_SCREEN 3
#define RECT_SCREEN 4
#define TEXTFIELD_SCREEN 7
#define IMAGE_SCREEN 8

//START SIMBLEE UI TEST SOURCE CODE
#define TITLE_TEXT_SIZE 40
#define TEXT_SIZE 16
#define HOME_BUTTON_LEFT_MARGIN 120
#define HOME_BUTTON_TOP_MARGIN 500
#define HOME_BUTTON_WIDTH 90
#define HOME_BUTTON_TEXT "Home"
//END SIMBLEE UI TEST SOURCE CODE

int myPressures [1000];
//int maxPressures [500];
//int minPressures [500];
int diffPressures [1000];
int filteredPressures [1000];

//
// The ID of the button which displays the testing screens
//
int toBPButtinID;
int toRecordsButtinID;

//
// The IDs of the various user interface widgets used in the screens.
//
int state;
float meanArtPress = 0;
int mapIndex = 0;
int sysIndex = 0;
int sysPressure = 121;
int diaIndex = 0;
int diaPressure = 72;
int count = 1;
float alpha = .1;
int counterButtonID;
int BPCounterButtonID;
int buttonPressCount;
int BPCountText;
int BPStartText;
int BPDiaText;
int BPEndText;
float sensor;
float voltage;
float pressureFLOAT;
int pressureINT;

//
// The ID of the button which return to the home screen
// This variable is a bit unique as it is redefined on each
// test screen, but always returns to the home screen when pressed.
//
int toHomeScreenButtonID;

//
// The number of the current screen being displayed
//
int currentScreen;

/**
 * Traditional Arduino setup routine
 * Initialize the SimbleeForMobile environment.
 * FROM SIMBLEE UI TEST SOURCE CODE
 */
void setup() {
  //
  // Enabled logging of the various events during application execution
  //
  Serial.begin(9600);
  Serial.println("Setup beginning");

  state = 0;
  buttonPressCount = 0;

  SimbleeForMobile.deviceName = "Under Pressure!";
  SimbleeForMobile.advertisementData = "t";

  // use a shared cache
  SimbleeForMobile.domain = "testing.simblee.com";

  // Begin Simble UI
  SimbleeForMobile.begin();

  Serial.println("Setup completed");
}

/**
 * The traditional Arduino loop method
 *
 * Enable SimbleeForMobile functionality by calling the process method
 * each time through the loop. This method must be called regularly for
 * functionality to work.
 */
void loop() {
  /*
  delay(1000);
  sensor = analogRead(6);
  voltage = (sensor/1024) * 3.3;
  pressureFLOAT = 7.50062 * ((voltage/3.3)-.04)/(.018);
  pressureINT = 7.50062 * ((voltage/3.3)-.04)/(.018);
  Serial.println(sensor);
  Serial.println(voltage);
  Serial.println(pressureFLOAT);
  Serial.println(pressureINT);
  char countBuffer[30];
  sprintf(countBuffer, "%d", pressureINT);
  
  if (SimbleeForMobile.updatable){
  SimbleeForMobile.updateText(BPCountText, countBuffer);
  }
  
  SimbleeForMobile.process();
  
}
 */
  if (state == 1) {

  delay(500);
  sensor = analogRead(6);
  voltage = (sensor/1024) * 3.3;
  pressureFLOAT = 7.50062 * ((voltage/3.3)-.04)/(.018);
  pressureINT = 7.50062 * ((voltage/3.3)-.04)/(.018);
//  Serial.println(sensor);
//  Serial.println(voltage);
  Serial.println(pressureFLOAT);
//  Serial.println(pressureINT);
  char countBuffer[30];
  sprintf(countBuffer, "%d", pressureINT);

    if (pressureINT >= 165) {
      BPEndText = SimbleeForMobile.drawText(15, 320, "STOP PUMPING AND START RELEASING PRESSURE", WHITE, 14);
      SimbleeForMobile.updateColor(BPStartText, rgba(173, 216, 239, .9));
      state = 30;
  }
  
    if (SimbleeForMobile.updatable && state == 1){
      SimbleeForMobile.updateText(BPCountText, countBuffer);
  }
  
  }

  if (state == 30) {
  delay(500);
  sensor = analogRead(6);
  voltage = (sensor/1024) * 3.3;
  pressureFLOAT = 7.50062 * ((voltage/3.3)-.04)/(.018);
  pressureINT = 7.50062 * ((voltage/3.3)-.04)/(.018);
//  Serial.println(sensor);
//  Serial.println(voltage);
  Serial.println(pressureFLOAT);
//  Serial.println(pressureINT);
  char countBuffer[30];
  sprintf(countBuffer, "%d", pressureINT);
    if (pressureINT <= 150) {
      state = 31;
    }

      if (SimbleeForMobile.updatable && state == 30){
      SimbleeForMobile.updateText(BPCountText, countBuffer);
      }
  }
  

  if (state == 31) {
  delay(50);
  sensor = analogRead(6);
  voltage = (sensor/1024) * 3.3;
  pressureFLOAT = 7.50062 * ((voltage/3.3)-.04)/(.018);
  pressureINT = 7.50062 * ((voltage/3.3)-.04)/(.018);
//  Serial.println(sensor);
//  Serial.println(voltage);
//  Serial.println(pressureFLOAT);
  Serial.println(analogRead(2));
  char countBuffer[30];
  sprintf(countBuffer, "%d", pressureINT);
  
    if (analogRead(2) > 5 ) {
      state = 2;
      Serial.println("Measuring pressures");
    }
        if (SimbleeForMobile.updatable && state == 31){
      SimbleeForMobile.updateText(BPCountText, countBuffer);
        }
  }

  if (state == 2) {
  delay(25);
  sensor = analogRead(6);
  voltage = (sensor/1024) * 3.3;
  pressureFLOAT = 7.50062 * ((voltage/3.3)-.04)/(.018);
  pressureINT = 7.50062 * ((voltage/3.3)-.04)/(.018);
  char countBuffer[30];
  sprintf(countBuffer, "%d", pressureINT);
  
    if (SimbleeForMobile.updatable && state == 2)
  {
     SimbleeForMobile.updateText(BPCountText, countBuffer);
  }

    filteredPressures[count] = pressureINT;
    myPressures[count] = analogRead(2);
  
    count = count + 1;
if (count == 1000){
  Serial.println("Out of memory");
  state = 3;
}
  if (pressureINT <= 50) {
  SimbleeForMobile.updateColor(BPEndText, rgba(173, 216, 239, .9));
  state = 3;
  
  }
  }


  if (state == 3) {
    
//min and max pressure detection    
Serial.println("Detecting min and max pressures");
    for (int i = 2; i < 1000-1; i++){
      if (myPressures[i] >= myPressures[i + 1] && myPressures[i] > myPressures[i - 1]) {
        diffPressures[i] = myPressures[i];
//        minPressures[i] = 0;
      }
//       else if (myPressures[i] <= myPressures[i + 1] && myPressures[i] < myPressures[i - 1]){
//        minPressures[i] = myPressures[i];
//        maxPressures[i] = 0;
//       }
       else {
        diffPressures[i] = 0;
//        minPressures[i] = 0;
       }
    } 
//  for (int i = 2; i<500-1; i++){
//    Serial.println("pressure:");
//    Serial.println(myPressures[i]);
//    if(maxPressures[i] != 0){
//    Serial.println("max: ");
//    Serial.println(maxPressures[i]);
//    }
//    if (minPressures[i] !=0){
//    Serial.println("min: ");
//    Serial.println(minPressures[i]);
//    }
//  }
//calculate differential pressure
//   for (int j = 2; j < 500-1; j++){
//    if (minPressures[j] !=0){
//      for (int k = j; k < 500-1; k++){
//        if (maxPressures[k] !=0) {
//          diffPressures[k] = maxPressures[k] - minPressures[j];
     //     Serial.println(diffPressures[k]);
//        }
//      }
//    }
//   }
  for (int i = 2; i<1000-1; i++){
    if(diffPressures[i] !=0){
    Serial.println("diff: ");
    Serial.println(diffPressures[i]);
    Serial.println(i);

    }
  }
//search map
      for (int m = 2; m < 1000-1; m++){
        if (diffPressures[m] > meanArtPress){
          meanArtPress = diffPressures[m];
          mapIndex = m;
        } 
      }
       Serial.println("mean arterial pressure: ");
       Serial.println(meanArtPress);
       Serial.println("map index: ");
       Serial.println(mapIndex);
  
//
  for (int p = 2; p < mapIndex; p++){
    if (diffPressures[p] >= (0.5)*(meanArtPress) && diffPressures[p] <= (0.6)*(meanArtPress)){
      sysIndex = p;
    }
  }
  for (int q = mapIndex; q < 1000-1; q++){
    if (diffPressures[q] >= (0.8)*(meanArtPress) && diffPressures[q] <= (0.9)*(meanArtPress)){
      diaIndex = q;
    }
  }
      Serial.println("systolic index: ");
      Serial.println(sysIndex);
      Serial.println("diastolic index: ");
      Serial.println(diaIndex);
/* filtering
  filteredPressures[1] = alpha * myPressures[1];
  for (int n = 2; n < 500-1; n++){    
    filteredPressures[n] = alpha * myPressures[n] + (1-alpha) * filteredPressures[n-1];
  }*/    
    state = 4;
    
 if (state == 4){
  sysPressure = filteredPressures[sysIndex];
  Serial.println("systolic: ");
  Serial.println(sysPressure);
  diaPressure = filteredPressures[diaIndex];
  Serial.println("diastolic: ");
  Serial.println(diaPressure);
  char sysBuffer[30];
  sprintf(sysBuffer, "%d", sysPressure);
  char diaBuffer[30];
  sprintf(diaBuffer, "%d", diaPressure);
  SimbleeForMobile.updateText(BPCountText, sysBuffer);
  SimbleeForMobile.updateText(BPDiaText, diaBuffer);
  SimbleeForMobile.updateColor(BPDiaText, WHITE);
  
 }
      
  /*
  if (count == 0) {

  char textBuffer[50] = "Your Blood Pressure is";
   
  if (SimbleeForMobile.updatable && state == 2)
  {
  SimbleeForMobile.updateText(InstructionText, textBuffer );
  }
  state = 3;

  }

  }
  
  if (state == 3) {
  
  diastolic = 120;
  systolic = 80;
  char diastolicBuffer[30];
  sprintf(diastolicBuffer, "%d", diastolic);
  char systolicBuffer[30];
  sprintf(systolicBuffer, "%d", systolic);
  
  if (SimbleeForMobile.updatable && state == 3)
  {
  SimbleeForMobile.updateText(BPCountText, diastolicBuffer );
  SimbleeForMobile.updateText(SystolicText, systolicBuffer );

  }

  }
    
}*/
  }
SimbleeForMobile.process();
}

/**
 * Callback when a Central connects to this device
 * Reset the current screen to non being displayed
 * FROM SIMBLEE UI TEST SOURCE CODE
 */
void SimbleeForMobile_onConnect()
{
  currentScreen = -1;
}

/**
 * Callback when a Central disconnects from this device
 * Not used in this sketch. Could clean up any resources
 * no longer required.
 * FROM SIMBLEE UI TEST SOURCE CODE
 */
void SimbleeForMobile_onDisconnect()
{
}

/**
 * SimbleeForMobile ui callback requesting the user interface
 *
 * Check which screen is being requested.
 * If that is the current screen, simply return.
 * If it is a different screen, create the requested screen.
 * A screen request which is out of range, is logged and ignored.
 */
void ui()
{
  Serial.printf("Screen %d requested. Current screen is %d\n", SimbleeForMobile.screen, currentScreen);

  if (SimbleeForMobile.screen == currentScreen) return;

  currentScreen = SimbleeForMobile.screen;
  switch (SimbleeForMobile.screen)
  {
    case HOME_SCREEN:
      createHomeScreen();
      break;

    case BP_SCREEN:
      createBPScreen();
      break;

    case RECORDS_SCREEN:
      createRecordsScreen();
      updateCounterButtonText();
      break;

    default:
      Serial.print("ui: Uknown screen requested: ");
      Serial.println(SimbleeForMobile.screen);
  }
}

/**
 * SimbleeForMobile event callback method
 *
 * An event we've registered for, or a default event, has occur. Process the event.
 * Forward the event to the method which handles events for the screen currently displayed.
 */
void ui_event(event_t &event)
{
  if (event.type != EVENT_DRAG && event.type != 0) printEvent(event);
  // printEvent(event);

  switch (currentScreen)
  {
    case HOME_SCREEN:
      handleHomeScreenEvents(event);
      break;

    case BP_SCREEN:
      handleTextScreenEvents(event);
      handleBPStart(event);
      break;

    case RECORDS_SCREEN:
      handleButtonScreenEvents(event);
      break;
  }

  //
  // Could put the common "Home" button event here, but left it in each screen's handling to
  // keep each of those routines handling all the events for that screen.
  //
}

/**
 * Handle events which occur on the home screen.
 * 
 * Check which button generated the event and if it is an EVENT_RELEASE event type,
 * signifying the end of a button press, display the screen associated with the button.
 */
void handleHomeScreenEvents(event_t &event)
{
  if (event.id == toBPButtinID && event.type == EVENT_RELEASE)
  {
    SimbleeForMobile.showScreen(BP_SCREEN);
  } else if (event.id == toRecordsButtinID && event.type == EVENT_RELEASE)
  {
    SimbleeForMobile.showScreen(RECORDS_SCREEN);
  }
}

/**
 * Handle events which occur on the Text screen.
 * The only event that is handled is the EVENT_RELEASE on the button which returns
 * to the home screen.
 * FROM SIMBLEE UI TEST SOURCE CODE
 */
void handleTextScreenEvents(event_t &event)
{
  if (event.id == toHomeScreenButtonID && event.type == EVENT_RELEASE) {
    SimbleeForMobile.showScreen(HOME_SCREEN);
  }
}

/**
 * Handle events which occur on the Button screen.
 * Handle returning to the home screen event as well as when the "Pressed" button
 * is pressed, update the pressed count and text on that button.
 * FROM SIMBLEE UI TEST SOURCE CODE
 */
void handleButtonScreenEvents(event_t &event)
{
  if (event.id == toHomeScreenButtonID && event.type == EVENT_RELEASE) {
    SimbleeForMobile.showScreen(HOME_SCREEN);
  } else if (event.id == counterButtonID && event.type == EVENT_RELEASE) {
    buttonPressCount += 1;
    updateCounterButtonText();
  }

}

void handleBPStart(event_t &event) {
  if (event.id == BPCounterButtonID && event.type == EVENT_RELEASE) {
    SimbleeForMobile.updateColor(BPCountText, WHITE);
    SimbleeForMobile.updateColor(BPStartText, WHITE);
    state = 1;
  }
}
/**
 * Create the Home screen.
 *
 * This screen has a bunch of buttons which open subdisplays. Each subdisplay tests various
 * aspects of SimbleeUI
 */
void createHomeScreen()
{
  Serial.println("creating Home screen");
  
  //
  // Portrait mode is the default, so that isn't required
  // here, but shown for completeness. LANDSCAPE could be
  // used for that orientation.
  //
  
  //START SIMBLEE UI TEST SOURCE CODE
  SimbleeForMobile.beginScreen(rgba(173, 216, 230, .9), PORTRAIT);
  
  Serial.printf("Screen size %d x %d\n", SimbleeForMobile.screenWidth, SimbleeForMobile.screenHeight);

  int titleLeftMargin = 50;
  int titleTopMargin = 60;
  int leftMargin = 20;
  int leftMarginButton = 240;
  int topMargin = 140;
  int yDelta = 50;
  int yButtonOffset = 10;
  int buttonWidth = 200;
  //END SIMBLEE UI TEST SOURCE CODE

  SimbleeForMobile.drawText(120, 60, "WELCOME TO", WHITE, TEXT_SIZE);
  SimbleeForMobile.drawText(35, 70, "Under Presssure", WHITE, TITLE_TEXT_SIZE);

  toBPButtinID = SimbleeForMobile.drawButton(63, topMargin - yButtonOffset, buttonWidth, "Measure your BP", rgba(255, 105, 180, 0.6));
  topMargin += yDelta;

  toRecordsButtinID = SimbleeForMobile.drawButton(64, topMargin - yButtonOffset, buttonWidth, "View Records", rgba(255, 105, 180, 0.6));
  topMargin += yDelta;

  //
  // Receive notifications when a "release" occurs on the button.
  // Other event notifications are supported and can be combined in this call.
  // I.e. to receive press and release events you'd pass:
  //
  // EVENT_PRESS | EVENT_RELEASE
  //
  // into the function:
  //
  // SimbleeForMobile.setEvents(toBPButtinID, EVENT_PRESS | EVENT_RELEASE);
  //
  // However, you don't want to register for events which are not required as
  // that results in extra traffic.
  //
  SimbleeForMobile.setEvents(toBPButtinID, EVENT_RELEASE);
  SimbleeForMobile.setEvents(toRecordsButtinID, EVENT_RELEASE);
  SimbleeForMobile.endScreen();
  
  Serial.println("Home screen created");
}

/**
 * Create the text test screen.
 *
 * This screen displays multiple lines of text using the various text
 * creation calls supported by SimbleeForMoible
 */
void createBPScreen()
{
  Serial.println("creating BP screen");

  //
  // Default to Portrait orientation
  //
  SimbleeForMobile.beginScreen(rgba(173, 216, 230, .9), PORTRAIT);

  int titleLeftMargin = 50;
  int titleTopMargin = 60;

  int topMargin = 110;
  int deltaY = 20;

  int leftMargin = 20;

  SimbleeForMobile.drawText(50, 60, "MEASURE YOUR BLOOD PRESSURE", WHITE, TEXT_SIZE);
  BPCountText = SimbleeForMobile.drawText(50, 150, "0", rgba(173, 216, 230, .9), 150);
  BPDiaText = SimbleeForMobile.drawText(50, 300, "0", rgba(173, 216, 230, .9), 150);
  BPStartText = SimbleeForMobile.drawText(110, 300, "START PUMPING!", rgba(173, 216, 239, .9), TEXT_SIZE);

  
  BPCounterButtonID = SimbleeForMobile.drawButton(113, 100, 100, "Start!", rgba(255, 105, 180, 0.6));
  toHomeScreenButtonID = SimbleeForMobile.drawButton(HOME_BUTTON_LEFT_MARGIN, HOME_BUTTON_TOP_MARGIN, HOME_BUTTON_WIDTH, HOME_BUTTON_TEXT, rgba(255, 105, 180, 0.6));
  
  SimbleeForMobile.setEvents(toHomeScreenButtonID, EVENT_RELEASE);
  SimbleeForMobile.setEvents(BPCounterButtonID, EVENT_RELEASE);
  SimbleeForMobile.endScreen();
  
  Serial.println("BP screen created");
}

/**
 * Create the button test screen.
 * This screen displays multiple buttons using the various button
 * creation calls supported by SimbleeForMoible
 * FROM SIMBLEE UI TEST SOURCE CODE
 */
void createRecordsScreen()
{
  Serial.println("creating Records screen");
  
  //
  // Default to Portrait orientation
  //
  SimbleeForMobile.beginScreen(GRAY);

  int titleLeftMargin = 45;
  int titleTopMargin = 60;

  int buttonLeftMargin = 40;
  int buttonTopMargin = 120;
  int buttonWidth = 120;
  int buttonYDelta = 60;

  SimbleeForMobile.drawText(titleLeftMargin, titleTopMargin, "Button Screen", BLACK, TITLE_TEXT_SIZE);

  int buttonID = SimbleeForMobile.drawButton(buttonLeftMargin, buttonTopMargin, buttonWidth, "Press");
  buttonTopMargin += buttonYDelta;
  SimbleeForMobile.setEvents(buttonID, EVENT_PRESS);

  buttonID = SimbleeForMobile.drawButton(buttonLeftMargin, buttonTopMargin, buttonWidth, "Release", BLUE);
  buttonTopMargin += buttonYDelta;
  SimbleeForMobile.setEvents(buttonID, EVENT_RELEASE);

  buttonID = SimbleeForMobile.drawButton(buttonLeftMargin, buttonTopMargin, buttonWidth, "Position", RED, BOX_TYPE);
  buttonTopMargin += buttonYDelta;
  SimbleeForMobile.setEvents(buttonID, EVENT_PRESS | EVENT_RELEASE | EVENT_POSITION);

  buttonID = SimbleeForMobile.drawButton(buttonLeftMargin, buttonTopMargin, buttonWidth, "Text Button", YELLOW, TEXT_TYPE);
  SimbleeForMobile.setEvents(buttonID, EVENT_PRESS | EVENT_RELEASE | EVENT_POSITION);
  buttonTopMargin += buttonYDelta;

  counterButtonID = SimbleeForMobile.drawButton(buttonLeftMargin, buttonTopMargin, buttonWidth, "Pressed: 0", GREEN);
  SimbleeForMobile.setEvents(counterButtonID, EVENT_RELEASE);

  toHomeScreenButtonID = SimbleeForMobile.drawButton(HOME_BUTTON_LEFT_MARGIN, HOME_BUTTON_TOP_MARGIN, HOME_BUTTON_WIDTH, HOME_BUTTON_TEXT);

  SimbleeForMobile.setEvents(toHomeScreenButtonID, EVENT_RELEASE);
  SimbleeForMobile.endScreen();
  
  Serial.println("Records screen created");
}



/**
 * Utility method to update the text on the counter button.
 * FROM SIMBLEE UI TEST SOURCE CODE
 */
void updateCounterButtonText()
{
  char myBuffer[20];
  sprintf(myBuffer, "Pressed: %d", buttonPressCount);
  SimbleeForMobile.updateText(counterButtonID, myBuffer);
}

/*
  Utility method to print information regarding the given event
  FROM SIMBLEE UI TEST SOURCE CODE
*/
void printEvent(event_t &event)
{
  char eventType[10];

  switch (event.type)
  {
    case EVENT_PRESS:
      strcpy(eventType, "Press");
      break;
    case EVENT_RELEASE:
      strcpy(eventType, "Release");
      break;
    case EVENT_DRAG:
      strcpy(eventType, "Drag");
      break;
    case EVENT_POSITION:
      strcpy(eventType, "Position");
      break;
    case EVENT_COLOR:
      strcpy(eventType, "Color");
      break;
    default:
      strcpy(eventType, "Unknown");
      break;
  }

  Serial.printf("Event ID: %d Type: %d (%s) Value: %d Text: %s Coords: %d,%d\n",
                event.id, event.type, eventType, event.value, event.text, event.x, event.y);
}

