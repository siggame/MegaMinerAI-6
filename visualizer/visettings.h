#ifndef VISETTINGS_H
#define VISETTINGS_H

// CodeProject's Configuration Loader
#include "config.h"

#define ATTRIBUTE( vType, x ) \
	private: \
		vType x; \
		public: \
			vType get##x() \
			{ \
				return x; \
			} \
			void set##x( vType XXTemp ) \
			{ \
				x = XXTemp; \
			}

#define setAttr( x, y ) visettings::instance()->set##x( y )
#define getAttr( x ) visettings::instance()->get##x()

		class visettings
		{
			// SETUP GLOBAL ATTRIBUTES

			ATTRIBUTE( int, curX );
			ATTRIBUTE( int, curY );
			ATTRIBUTE( int, maxX );
			ATTRIBUTE( int, maxY );
			ATTRIBUTE( int, boardX );
			ATTRIBUTE( int, boardY );
			ATTRIBUTE( bool, MapGrid );

			ATTRIBUTE( int, unitSize );

			ATTRIBUTE( int, defaultMode );
			ATTRIBUTE( int, currentMode );
			ATTRIBUTE( int, frameNumber );
			ATTRIBUTE( int, lastFrame );
			ATTRIBUTE( int, speed );

			// This is the current play speed
			ATTRIBUTE( int, playSpeed );

			ATTRIBUTE( int, defaultSpeed);
			ATTRIBUTE( int, x2Speed );
			ATTRIBUTE( int, x4Speed );
			ATTRIBUTE( int, x8Speed );
			ATTRIBUTE( int, x16Speed );

			ATTRIBUTE( bool, dragging );

			ATTRIBUTE( int, boardHeightPx );
			ATTRIBUTE( int, boardWidthPx );

			ATTRIBUTE( int, doubleClickTime );

			// Texture Files

			ATTRIBUTE( string, defBGFileName );
			ATTRIBUTE( string, wallFileName );
			ATTRIBUTE( string, gridFileName );

			// Bot Textures
			//red bots
			ATTRIBUTE( string, redActionFile );
			ATTRIBUTE( string, redBuilderFile );
			ATTRIBUTE( string, redCannonFile );
			ATTRIBUTE( string, redDamageFile );
			ATTRIBUTE( string, redEngineFile );
			ATTRIBUTE( string, redForceFile );
			ATTRIBUTE( string, redFrameFile );
			ATTRIBUTE( string, redAttackFile );
			ATTRIBUTE( string, redBuildAnimFile );
			ATTRIBUTE( string, redJointFile );

			//blue bots
			ATTRIBUTE( string, bluActionFile );
			ATTRIBUTE( string, bluBuilderFile );
			ATTRIBUTE( string, bluCannonFile );
			ATTRIBUTE( string, bluDamageFile );
			ATTRIBUTE( string, bluEngineFile );
			ATTRIBUTE( string, bluForceFile );
			ATTRIBUTE( string, bluFrameFile );
			ATTRIBUTE( string, bluAttackFile );
			ATTRIBUTE( string, bluBuildAnimFile );
			ATTRIBUTE( string, bluJointFile );

			// Arena Stuff
			ATTRIBUTE( int, arenaMode );
			ATTRIBUTE( int, winnerScreenTime );
			ATTRIBUTE( int, initTime );

			// Font Stuff

			ATTRIBUTE( string, defaultFont );
			ATTRIBUTE( string, defaultFontWidths );

			ATTRIBUTE( bool, team1Talk );
			ATTRIBUTE( bool, team2Talk );
			ATTRIBUTE( bool, persistantTalking );

			ATTRIBUTE( int, team1Score );
			ATTRIBUTE( int, team2Score );

			public:
				static visettings *inst;
				static visettings *instance()
				{
					if( !inst )
						inst = new visettings();
					return inst;
				}

				visettings();
				~visettings();

				bool loadFromFile(string & errString);

		};
#endif
