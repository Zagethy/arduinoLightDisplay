
#define LED_ON			HIGH
#define LED_OFF			LOW


typedef struct
{
		int currentPattern;
		int timestampStart;
		bool patternComplete;
		int completeTime;
} Pattern;

typedef struct
{
		int ledPin;
		int onTime;
		int sequence;
}ledPatternInfo;

void setup();
void loop();

void initLEDs();
void patternStartup();
void selectPattern();

void patternShow( ledPatternInfo *ledOrder[], int ledOrderSize );
ledPatternInfo* addLedInfo( int pin, int onTime, int sequence );
void removeLedInfo( ledPatternInfo *ledOrder[], int ledOrderSize );
int calcPatternTime( ledPatternInfo *ledOrder[], int ledOrderSize );

void defaultPattern();
void pattern1();

