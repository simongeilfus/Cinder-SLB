#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

#include "ciLua.h"

using namespace ci;
using namespace ci::app;
using namespace std;


//-------------------------------------------------------------------------------------

class RandRectangles {
public:
    
    bool setup( lua::Script::LoadEvent event ){
        int   n = event.mRef->get< int >( "numRectangles" );
        float w = event.mRef->get< float >( "maxWidth" );
        float h = event.mRef->get< float >( "maxHeight" );
        
        mRects.clear();
        
        Rand::randSeed( event.mRef->get< int >( "randomSeed" ) );
        for( int i = 0; i < n; i++ ){
            Vec2f pos = Vec2f( Rand::randFloat( getWindowWidth() ), Rand::randFloat( getWindowHeight() ) );
            Vec2f size = Vec2f( Rand::randFloat( w ), Rand::randFloat( h ) );
            mRects.push_back( Rectf( pos, pos + size ) );
        }
        
        return false;
    }
    
    void draw(){
        for( int i = 0; i < mRects.size(); i++ ){
            gl::drawSolidRect( mRects[i] );
        }
    }
    
protected:
    
    vector<Rectf> mRects;
};

//-------------------------------------------------------------------------------------

class LuaSettingsApp : public AppBasic {
  public:
	void setup();
	void update();
	void draw();
    
    bool loadSettings( lua::Script::LoadEvent event );
    
    RandRectangles mRects;
    lua::Script mSettings;
};

void LuaSettingsApp::setup()
{
    lua::bindAll();
    
    mSettings.registerOnLoad( &mRects, &RandRectangles::setup );
    mSettings.registerOnLoad( this, &LuaSettingsApp::loadSettings );
    
    mSettings.loadFile( getAssetPath( "Settings.lua" ) );
}

void LuaSettingsApp::update()
{
    mSettings.update();
}

void LuaSettingsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    mRects.draw();
}

bool LuaSettingsApp::loadSettings( lua::Script::LoadEvent event ){
    Vec2i windowSize = event.mRef->get<Vec2i>( "windowSize" );
    
    setWindowSize( windowSize.x, windowSize.y );
    setWindowPos( event.mRef->get<Vec2i>( "windowPos" ) );
    
    gl::enableVerticalSync( event.mRef->get<bool>( "verticalSync" ) );
    setFrameRate( event.mRef->get<int>( "framerate" ) );
    
    return false;
}

CINDER_APP_BASIC( LuaSettingsApp, RendererGl )
