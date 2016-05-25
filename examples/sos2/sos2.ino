#include <Automaton.h>

Atm_led dot, dash;
Atm_timer stepTimer;
Atm_step step;
Appliance app;

const int pin = 4;
const int dotTime = 100;
const int dashTime = 300;
const int waitTime = 200;
const int longwaitTime = 300;
const int longerwaitTime = 1000;

void setup() {
  
  // Define two leds (patterns) and add them to the app
  app.component(  dot.begin( pin ).blink(  dotTime, waitTime, 3 ) );
  app.component( dash.begin( pin ).blink( dashTime, waitTime, 3 ) );
  
  // Define a timer and add it to the app
  app.component( stepTimer.begin( 1700 ).repeat( ATM_COUNTER_OFF ) );
  
  // Define a step sequencer, add it to the app and link it to the leds we defined earlier
  app.component( 
    step.begin()
      .onStep( 0,  dot, Atm_led::EVT_BLINK )
      .onStep( 1, dash, Atm_led::EVT_BLINK )
      .onStep( 2,  dot, Atm_led::EVT_BLINK )
  );
  
  // Set up the timer to drive the step sequencer
  stepTimer.onTimer( step, Atm_step::EVT_STEP );  
  
  // Start the timer
  stepTimer.trigger( Atm_timer::EVT_START );
}

void loop() {
  app.run();
}
