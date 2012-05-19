#pragma once

#include "cinder/cinder.h"
#include "SLB.hpp"
#include "ciScript.h"

namespace lua {
    
    
    
    // std::vector< T >
    //------------------------------------------------
    
    template <typename T>
    static void bindVector( std::string name ){
		SLB::Class< std::vector< T > >( name.c_str() )
        .constructor()
        .set("push_back",(  void (std::vector< T >::*) ( const T& ) ) &std::vector< T >::push_back)
        .set("at",  ( T& (std::vector<T>::*) (size_t) ) &std::vector<T>::operator[] )
        .iterator("iterator", &std::vector<T>::begin, &std::vector<T>::end )
        .const_iterator("const_iterator", &std::vector<T>::begin, &std::vector<T>::end )
        .set("size", ( size_t (std::vector< T >::*) () ) &std::vector< T >::size )
        .set("clear",  &std::vector<T>::clear )
        ;
    };
    
    // Vec2i
    //------------------------------------------------
    static void bindVec2i(){
		SLB::Class< ci::Vec2i >( "Vec2i" )
        .constructor<int,int>()
        .property( "x", &ci::Vec2i::x )
        .property( "y", &ci::Vec2i::y )
        .set( "set", (  void (ci::Vec2i::*) ( int, int ) ) & ci::Vec2i::set )
        ;
    };
    
    // Vec2f
    //------------------------------------------------
    static void bindVec2f(){
		SLB::Class< ci::Vec2f >( "Vec2f" )
        .constructor<float,float>()
        .property( "x", &ci::Vec2f::x )
        .property( "y", &ci::Vec2f::y )
        .set( "set", (  void (ci::Vec2f::*) ( float, float ) ) & ci::Vec2f::set )
        ;
    };
    
    // Vec3f
    //------------------------------------------------
    static void bindVec3f(){
		SLB::Class< ci::Vec3f >( "Vec3f" )
        .constructor<float,float,float>()
        .property( "x", &ci::Vec3f::x )
        .property( "y", &ci::Vec3f::y )
        .property( "z", &ci::Vec3f::z )
        .set( "set", (  void (ci::Vec3f::*) ( float, float, float ) ) & ci::Vec3f::set )
        ;
    };
    
    // Rectf
    //------------------------------------------------
    static void bindRectf(){
		SLB::Class< ci::Rectf >( "Rectf" )
        .constructor<float,float,float,float>()
        .property( "x1", &ci::Rectf::x1 )
        .property( "y1", &ci::Rectf::y1 )
        .property( "x2", &ci::Rectf::x2 )
        .property( "y2", &ci::Rectf::y2 );
    };
    
    // Area
    //------------------------------------------------
    static void bindArea(){
		SLB::Class< ci::Area >( "Area" )
        .constructor<float,float,float,float>()
        .property( "x1", &ci::Area::x1 )
        .property( "y1", &ci::Area::y1 )
        .property( "x2", &ci::Area::x2 )
        .property( "y2", &ci::Area::y2 );
    };
    
    // Color
    //------------------------------------------------
    static void bindColor(){
		SLB::Class< ci::Color >( "Color" )
        .constructor<float,float,float>()
        .property( "r", &ci::Color::r )
        .property( "g", &ci::Color::g )
        .property( "b", &ci::Color::b );
    };
    
    // FloatColor
    //------------------------------------------------
    static void bindColorA(){
		SLB::Class< ci::ColorA >( "ColorA" )
        .constructor<float,float,float,float>()
        .property( "r", &ci::ColorA::r )
        .property( "g", &ci::ColorA::g )
        .property( "b", &ci::ColorA::b )
        .property( "a", &ci::ColorA::a );
    };
    
    
    // Image
    //------------------------------------------------
    /*static void bindImage(){
		SLB::Class< Image >( "Image" )
        .constructor()
        .set( "clear", &Image::clear )
        .set( "bind", &Image::bind )
        .set( "unbind", &Image::unbind )
        .set( "loadImage", ( bool (Image::*) ( string ) ) &Image::loadImage )
        .set( "draw", ( void (Image::*) ( float, float ) ) &Image::draw )
        .set( "getWidth", &Image::getWidth )
        .set( "getHeight", &Image::getHeight )
        ;
    };*/
    
    
    // Graphics
    //------------------------------------------------
    static void bindGraphics(){
        SLB::Manager* m = SLB::Manager::defaultManager();
        
        /*//our openGL wrappers
        m->set( "ofPushMatrix", SLB::FuncCall::create( ofPushMatrix ) );
        m->set( "ofPopMatrix", SLB::FuncCall::create( ofPopMatrix ) );
        m->set( "ofTranslate", SLB::FuncCall::create( ( void (*) (float,float,float) ) ofTranslate ) );
        m->set( "ofScale", SLB::FuncCall::create( ofScale ) );
        m->set( "ofRotate", SLB::FuncCall::create( ( void (*) (float,float,float,float) ) ofRotate ) );
        m->set( "ofRotateX", SLB::FuncCall::create( ofRotateX ) );
        m->set( "ofRotateY", SLB::FuncCall::create( ofRotateY ) );
        m->set( "ofRotateZ", SLB::FuncCall::create( ofRotateZ ) );
        
        m->set( "ofSetCircleResolution", SLB::FuncCall::create( ofSetCircleResolution ) );
        m->set( "ofSetCurveResolution", SLB::FuncCall::create( ofSetCurveResolution ) );
        m->set( "ofSetSphereResolution", SLB::FuncCall::create( ofSetSphereResolution ) );
        
        // drawing options
        m->set( "ofNoFill", SLB::FuncCall::create( ofNoFill ) );
        m->set( "ofFill", SLB::FuncCall::create( ofFill ) );
        m->set( "ofSetLineWidth", SLB::FuncCall::create( ofSetLineWidth ) );
        
        // color options
        m->set( "ofSetColor", SLB::FuncCall::create( ( void (*) (int,int,int,int) ) ofSetColor ) );
        m->set( "ofSetGrayColor", SLB::FuncCall::create( (void (*) (int) ) ofSetColor ) );
        m->set( "ofSetHexColor", SLB::FuncCall::create( ofSetHexColor ) ); 
        
        // Blending
        m->set( "ofEnableBlendMode", SLB::FuncCall::create( ofEnableBlendMode ) );
        m->set( "ofDisableBlendMode", SLB::FuncCall::create( ofDisableBlendMode ) );
        
        // point sprites
        m->set( "ofEnablePointSprites", SLB::FuncCall::create( ofEnablePointSprites ) );
        m->set( "ofDisablePointSprites", SLB::FuncCall::create( ofDisablePointSprites ) );
        
        // transparency
        m->set( "ofEnableAlphaBlending", SLB::FuncCall::create( ofEnableAlphaBlending ) );
        m->set( "ofDisableAlphaBlending", SLB::FuncCall::create( ofDisableAlphaBlending ) );
        
        // smooth 
        m->set( "ofEnableSmoothing", SLB::FuncCall::create( ofEnableSmoothing ) );
        m->set( "ofDisableSmoothing", SLB::FuncCall::create( ofDisableSmoothing ) );
        
        // background
        m->set( "ofBackground", SLB::FuncCall::create( ( void (*) (int,int,int,int) ) ofBackground ) );
        m->set( "ofBackgroundHex", SLB::FuncCall::create( ofBackgroundHex ) );
        
        // user's access to settings (bgAuto, corner mode):
        m->set( "ofSetBackgroundAuto", SLB::FuncCall::create( ofSetBackgroundAuto ) );
        
        m->set( "ofClear", SLB::FuncCall::create( ( void (*) (float,float,float,float) ) ofClear ) );
        m->set( "ofClearAlpha", SLB::FuncCall::create( ofClearAlpha ) );
        
        // geometry
        m->set( "ofTriangle", SLB::FuncCall::create( ( void(*)(float,float,float,float,float,float) ) ofTriangle ) );
        m->set( "ofCircle", SLB::FuncCall::create( ( void (*) (float,float,float) ) ofCircle ) );
        m->set( "ofEllipse", SLB::FuncCall::create( ( void (*) (float,float,float,float) ) ofEllipse ) );
        m->set( "ofLine", SLB::FuncCall::create( ( void (*) (float,float,float,float) ) ofLine ) );
        m->set( "ofRect", SLB::FuncCall::create( ( void (*) (float,float,float,float) ) ofRect ) );
        m->set( "ofCurve", SLB::FuncCall::create( ofCurve ) );
        m->set( "ofBezier", SLB::FuncCall::create( ofBezier ) );
        
        
        // for polygons
        m->set( "ofBeginShape", SLB::FuncCall::create( ofBeginShape ) );
        m->set( "ofVertex", SLB::FuncCall::create( ( void (*) (float,float) ) ofVertex ) );
        m->set( "ofCurveVertex", SLB::FuncCall::create( ( void (*) (float,float) ) ofCurveVertex ) );
        m->set( "ofBezierVertex", SLB::FuncCall::create( ofBezierVertex ) );
        m->set( "ofEndShape", SLB::FuncCall::create( ofEndShape ) );
        m->set( "ofNextContour", SLB::FuncCall::create( ofNextContour ) );
        
        //3d
        m->set( "ofSphere", SLB::FuncCall::create( ( void (*) (float,float,float,float) ) ofSphere ) );
        m->set( "ofBox", SLB::FuncCall::create( ( void (*) (float,float,float,float) ) ofBox ) );
        
        // bitmapped type
        m->set( "ofSetDrawBitmapMode", SLB::FuncCall::create( ofSetDrawBitmapMode ) );
        m->set( "ofDrawBitmapString", SLB::FuncCall::create( ( void (*) (string,float,float) ) ofDrawBitmapString ) );*/
        
    };
    
    
    
    
    static void bindAll(){
        bindVec2i();
        bindVec2f();
        bindVec3f();
        bindRectf();
        bindArea();
        bindColor();
        bindColorA();
    };
};