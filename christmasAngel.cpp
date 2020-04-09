#include <Arduino.h>
#include <LibPrintf.h>
#include "header/christmasAngel.h"
#include "header/config.h"

Pattern pattern;

void setup()
{
	delay( 2000 ); // startup delay

	printf_init( Serial );
	Serial.begin( 115200 );

	initLEDs();

	pattern.currentPattern = PATTERN_STARTUP;
	pattern.timestampStart = millis();
	pattern.patternComplete = false;
}

void loop()
{
	if( pattern.patternComplete )
	{
		selectPattern();
	}

	switch( pattern.currentPattern )
	{
		case PATTERN_STARTUP:
			patternStartup();
			break;

		case PATTERN_ONE:
			pattern1();
			break;

		case PATTERN_NONE:
			defaultPattern();
			break;
	}
}

void selectPattern()
{
	// TODO algorithim to get a weighted random number to select which pattern to run

	pattern.currentPattern = PATTERN_ONE;

	pattern.timestampStart = millis();
	pattern.patternComplete = false;
}

int calcPatternTime( ledPatternInfo *ledOrder[], int ledOrderSize )
{
	int totalTime = 0;
	int maxSequence = 0;

	for( int i = 0; i < ledOrderSize; i++ )
	{
		if( ledOrder[ i ]->sequence > maxSequence )
		{
			maxSequence = ledOrder[ i ]->sequence;
		}
	}

	int maxTime[ maxSequence ] = { 0 };

	for( int i = 0; i < ledOrderSize; i++ )
	{
		if( maxTime[ ledOrder[ i ]->sequence ] < ledOrder[ i ]->onTime )
		{
			maxTime[ ledOrder[ i ]->sequence ] = ledOrder[ i ]->onTime;
		}
	}

	for( int i = 0; i < maxSequence; i++ )
	{
		printf( "Time To Add: %d \r\n", maxTime[ i ] );

		totalTime += maxTime[ i ];
	}

	printf( " On Time: %d  \r\n", totalTime );

	return totalTime;
}

void initLEDs()
{
	pinMode( LED_RING_1, OUTPUT );
	pinMode( LED_RING_2, OUTPUT );
	pinMode( LED_RING_3, OUTPUT );
	pinMode( LED_RING_4, OUTPUT );
	pinMode( LED_RING_5, OUTPUT );
	pinMode( LED_RING_6, OUTPUT );
	pinMode( LED_RING_7, OUTPUT );
	pinMode( LED_RING_8, OUTPUT );
	pinMode( LED_RING_9, OUTPUT );
	pinMode( LED_RING_10, OUTPUT );

	pinMode( LED_HAND, OUTPUT );
}

void patternStartup()
{
	ledPatternInfo *ledOrder[ LED_COUNT * 2 - 1 ];
	int ledOrderSize = 0;

	int startupDuration = 100;

	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_1, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_2, startupDuration, 1 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_3, startupDuration, 2 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_4, startupDuration, 3 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_5, startupDuration, 4 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_6, startupDuration, 5 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_7, startupDuration, 6 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_8, startupDuration, 7 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_9, startupDuration, 8 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_10, startupDuration, 9 );

	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_1, startupDuration, 18 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_2, startupDuration, 17 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_3, startupDuration, 16 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_4, startupDuration, 15 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_5, startupDuration, 14 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_6, startupDuration, 13 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_7, startupDuration, 12 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_8, startupDuration, 11 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_9, startupDuration, 10 );

	patternShow( ledOrder, ledOrderSize );

	removeLedInfo( ledOrder, ledOrderSize );
}

void defaultPattern()
{
	ledPatternInfo *ledOrder[ LED_COUNT ];
	int ledOrderSize = 0;

	int startupDuration = 1000;

	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_1, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_2, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_3, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_4, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_5, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_6, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_7, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_8, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_9, startupDuration, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_10, startupDuration, 0 );

	patternShow( ledOrder, ledOrderSize );

	removeLedInfo( ledOrder, ledOrderSize );
}

void pattern1()
{
	ledPatternInfo *ledOrder[ LED_COUNT * 2 - 2 ];
	int ledOrderSize = 0;

	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_1, 1000, 0 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_2, 1000, 1 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_3, 1000, 2 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_4, 1000, 3 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_5, 1000, 4 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_6, 1000, 4 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_7, 1000, 3 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_8, 1000, 2 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_9, 1000, 1 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_10, 1000, 0 );

	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_1, 1000, 8 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_2, 1000, 7 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_3, 1000, 6 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_4, 1000, 5 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_7, 1000, 5 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_8, 1000, 6 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_9, 1000, 7 );
	ledOrder[ ledOrderSize++ ] = addLedInfo( LED_RING_10, 1000, 8 );

	patternShow( ledOrder, ledOrderSize );

	removeLedInfo( ledOrder, ledOrderSize );
}

ledPatternInfo* addLedInfo( int pin, int onTime, int sequence )
{
	ledPatternInfo *orderSet;

	orderSet = ( ledPatternInfo* ) malloc( sizeof(ledPatternInfo) );

	orderSet->ledPin = pin;
	orderSet->onTime = onTime;
	orderSet->sequence = sequence;

	return orderSet;
}

void removeLedInfo( ledPatternInfo *ledOrder[], int ledOrderSize )
{
	for( int i = 0; i < ledOrderSize; i++ )
	{
		free( ledOrder[ i ] );
	}
}

void patternShow( ledPatternInfo *ledOrder[], int ledOrderSize )
{
	int timestamp = millis();
	int totalPatternTime = calcPatternTime( ledOrder, ledOrderSize );

	for( int i = 0; i < ledOrderSize; i++ )
	{
		if( timestamp > pattern.timestampStart + ( ledOrder[ i ]->onTime * ledOrder[ i ]->sequence ) && timestamp < pattern.timestampStart + ( ledOrder[ i ]->onTime * ( ledOrder[ i ]->sequence + 1 ) ) )
		{
			digitalWrite( ledOrder[ i ]->ledPin, LED_ON );
		}
		else
		{
			digitalWrite( ledOrder[ i ]->ledPin, LED_OFF );
		}
	}

	if( timestamp > ( pattern.timestampStart + totalPatternTime ) )
	{
		pattern.patternComplete = true;
	}
}
