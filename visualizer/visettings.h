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

			ATTRIBUTE( int, unitSize );

			ATTRIBUTE( int, defaultMode );
			ATTRIBUTE( int, currentMode );
			ATTRIBUTE( int, frameNumber );
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

			// Texture Files

			ATTRIBUTE( string, defBGFileName );
			ATTRIBUTE( string, wallFileName );
			ATTRIBUTE( string, gridFileName );


			// Arena Stuff
			ATTRIBUTE( int, arenaMode );
			ATTRIBUTE( int, winnerScreenTime );

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

				void loadFromFile();

		};
#endif
