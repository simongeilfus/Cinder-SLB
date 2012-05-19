#pragma once

#include "cinder/cinder.h"
#include "cinder/DataSource.h"
#include "cinder/Function.h"
#include "cinder/Filesystem.h"
#include "SLB.hpp"


#define LUAGL

#ifdef LUAGL

    #include "luagl.h"

#endif


namespace lua {
    
    
    
    class Script : public SLB::Script {
    public:
        
        
        // Loading Scripts and check for modifications
        //-----------------------------------------------------------------
        bool loadFile( ci::DataSourceRef dataSourceRef );
        bool loadFile( ci::fs::path path );
        
        
        struct LoadEvent {
            LoadEvent( Script* ref ) : mRef( ref ) {}
            
            Script* mRef;
        };
        
        template<typename T>
        ci::CallbackId registerOnLoad( T *obj, bool (T::*callback)(LoadEvent) ){
            return mOnLoadCallbacks.registerCb(std::bind1st(std::mem_fun(callback), obj));
        }
        
        void unregisterOnLoad( ci::CallbackId cbId ){
            mOnLoadCallbacks.unregisterCb( cbId );
        }
        
        //-----------------------------------------------------------------
        
        bool update();
        bool hasChanged();
        bool reload();
        
        
        // Getter and Setter
        //-----------------------------------------------------------------
        template<typename T>
        T get( std::string name ){
            return SLB::Script::get<T>( name.c_str() );
        }
        
        template<typename T>
        void set( std::string name, T value ){
            SLB::Script::set( name.c_str(), value );
        }
        
#ifdef LUAGL
        // Make Opengl Accessible
        //-----------------------------------------------------------------
        void bindGL(){
            luaopen_luagl( getState() );
        }
#endif
        
        
        // Call Methods with up to 7 arguments (Ugly implementation)
        //-----------------------------------------------------------------
        
        void call( std::string name ) {
            lua_State* state = getState();
            SLB::LuaCall< void( ) > call( state, name.c_str() );
            call();
        }    
        template< typename T1 >
        T1 call( std::string name ) {
            lua_State* state = getState();
            SLB::LuaCall< T1( ) > call( state, name.c_str() );
            return call();
        }
        
        
        
        template< typename T2 >
        void call( std::string name, T2 arg1 ){
            lua_State* state = getState();
            SLB::LuaCall< void( T2 ) > call( state, name.c_str() );
            call( arg1 );
        }
        template< typename T1, typename T2 >
        T1 call( std::string name, T2 arg1 ){
            lua_State* state = getState();
            SLB::LuaCall< T1( T2 ) > call( state, name.c_str() );
            return call( arg1 );
        }
        
        
        
        template< typename T2, typename T3 >
        void call( std::string name, T2 arg1, T3 arg2 ){
            lua_State* state = getState();
            SLB::LuaCall< void( T2, T3 ) > call( state, name.c_str() );
            call( arg1, arg2 );
        }
        template< typename T1, typename T2, typename T3 >
        T1 call( std::string name, T2 arg1, T3 arg2 ){
            lua_State* state = getState();
            SLB::LuaCall< T1( T2, T3 ) > call( state, name.c_str() );
            return call( arg1, arg2 );
        }
        
        
        
        
        template< typename T2, typename T3, typename T4 >
        void call( std::string name, T2 arg1, T3 arg2, T4 arg3 ){
            lua_State* state = getState();
            SLB::LuaCall< void( T2, T3, T4 ) > call( state, name.c_str() );
            return call( arg1, arg2, arg3 );
        }
        template< typename T1, typename T2, typename T3, typename T4 >
        T1 call( std::string name, T2 arg1, T3 arg2, T4 arg3 ){
            lua_State* state = getState();
            SLB::LuaCall< T1( T2, T3, T4 ) > call( state, name.c_str() );
            return call( arg1, arg2, arg3 );
        }
        
        
        
        
        template< typename T2, typename T3, typename T4, typename T5 >
        void call( std::string name, T2 arg1, T3 arg2, T4 arg3, T5 arg4 ){
            lua_State* state = getState();
            SLB::LuaCall< void( T2, T3, T4, T5 ) > call( state, name.c_str() );
            call( arg1, arg2, arg3, arg4 );
        }
        template< typename T1, typename T2, typename T3, typename T4, typename T5 >
        T1 call( std::string name, T2 arg1, T3 arg2, T4 arg3, T5 arg4 ){
            lua_State* state = getState();
            SLB::LuaCall< T1( T2, T3, T4, T5 ) > call( state, name.c_str() );
            return call( arg1, arg2, arg3, arg4 );
        }
        
        
        
        
        
        template< typename T2, typename T3, typename T4, typename T5, typename T6 >
        void call( std::string name, T2 arg1, T3 arg2, T4 arg3, T5 arg4, T6 arg5 ){
            lua_State* state = getState();
            SLB::LuaCall< void( T2, T3, T4, T5, T6 ) > call( state, name.c_str() );
            call( arg1, arg2, arg3, arg4, arg5 );
        }
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
        T1 call( std::string name, T2 arg1, T3 arg2, T4 arg3, T5 arg4, T6 arg5 ){
            lua_State* state = getState();
            SLB::LuaCall< T1( T2, T3, T4, T5, T6 ) > call( state, name.c_str() );
            return call( arg1, arg2, arg3, arg4, arg5 );
        }
        
        
        
        template< typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
        void call( std::string name, T2 arg1, T3 arg2, T4 arg3, T5 arg4, T6 arg5, T7 arg6 ){
            lua_State* state = getState();
            SLB::LuaCall< void( T2, T3, T4, T5, T6, T7 ) > call( state, name.c_str() );
            call( arg1, arg2, arg3, arg4, arg5, arg6 );
        }
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
        T1 call( std::string name, T2 arg1, T3 arg2, T4 arg3, T5 arg4, T6 arg5, T7 arg6 ){
            lua_State* state = getState();
            SLB::LuaCall< T1( T2, T3, T4, T5, T6, T7 ) > call( state, name.c_str() );
            return call( arg1, arg2, arg3, arg4, arg5, arg6 );
        }
        
        
        // Get Lua State
        //-----------------------------------------------------------------
        lua_State* getState() {
            return SLB::Script::getState();
        }
        
        std::string getName(){ return mPath.filename().string(); }
        
        
    private:
        
        ci::fs::path                        mPath;
        std::time_t                         mLastTime;
        ci::CallbackMgr< bool(LoadEvent) >  mOnLoadCallbacks;
    };
    
    
    
    /*class ScriptManager {
    public:
        static ScriptRef get( std::string filename );
        static void update();
        
        template <typename ArgumentsType, class ListenerClass >
        static void addUpdateListener(std::string script, ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&)){
            ofAddListener( mScriptsEvents[script], listener, listenerMethod );
        }
        
        template <typename ArgumentsType, class ListenerClass >
        static void removeUpdateListener(std::string script, ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&)){
            ofRemoveListener( mScriptsEvents[script], listener, listenerMethod );
        }
        
    private:
        static map< std::string, ScriptRef >              mScripts;
        static map< std::string, ofEvent< ofEventArgs > >    mScriptsEvents;
    };*/
}
