#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "ciLua.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LuaOpenglApp : public AppBasic {
  public:
	void setup();
	void update();
	void draw();
    
    lua::Script mDrawScript;
};

void LuaOpenglApp::setup()
{
    setWindowSize( 200, 60 );
    mDrawScript.bindGL();
    mDrawScript.loadFile( loadAsset( "OpenglTest.lua" ) );
}

void LuaOpenglApp::update()
{
    mDrawScript.update();
}

void LuaOpenglApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    try {
        mDrawScript.call( "draw" );
    }
    catch( ... ){}
}


CINDER_APP_BASIC( LuaOpenglApp, RendererGl )
