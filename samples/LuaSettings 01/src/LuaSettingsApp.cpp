#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "ciLua.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LuaSettingsApp : public AppBasic {
  public:
	void setup();
	void update();
	void draw();
    
    
    lua::Script mSettings;
};

void LuaSettingsApp::setup()
{
    lua::bindAll();
    
    if( mSettings.loadFile( getAssetPath( "Settings.lua" ) ) ){
        Vec2i windowSize = mSettings.get<Vec2i>( "windowSize" );
        
        setWindowSize( windowSize.x, windowSize.y );
        setWindowPos( mSettings.get<Vec2i>( "windowPos" ) );
        
        gl::enableVerticalSync( mSettings.get<bool>( "verticalSync" ) );
        setFrameRate( mSettings.get<int>( "framerate" ) );
    }
}

void LuaSettingsApp::update()
{
    if( mSettings.update() ){
        Vec2i windowSize = mSettings.get<Vec2i>( "windowSize" );
        
        setWindowSize( windowSize.x, windowSize.y );
        setWindowPos( mSettings.get<Vec2i>( "windowPos" ) );
        
        gl::enableVerticalSync( mSettings.get<bool>( "verticalSync" ) );
        setFrameRate( mSettings.get<int>( "framerate" ) );
    }
}

void LuaSettingsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( LuaSettingsApp, RendererGl )
