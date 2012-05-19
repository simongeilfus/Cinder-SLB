#include "ciScript.h"

namespace lua {
    
    bool Script::loadFile( ci::DataSourceRef dataSourceRef ){
        return loadFile( dataSourceRef->getFilePath() );
    }
    
    bool Script::loadFile( ci::fs::path path ){
        
        bool loaded = false;
		mPath       = path;
        mLastTime   = ci::fs::last_write_time( mPath );
        
        loaded      = safeDoFile( path.c_str() );
            
        if( !loaded ){
            std::cout << "Script Error " << mPath.filename() << " : " << std::endl << "\t" << getLastError() << std::endl;
        }
        else {
            mOnLoadCallbacks.call( LoadEvent( this ) );
        }
        //else cout << "Script " << mPath.getFileName() << " compiled! " << endl; 
        
        return loaded;
    }
    
    
    bool Script::hasChanged(){
        return ci::fs::last_write_time( mPath ) > mLastTime;
    }
    bool Script::reload(){
        return loadFile( mPath );
    }
    
    bool Script::update(){
        try {
            if( hasChanged() ){
                return reload();
            }
        }
        catch( ... ){}
        return false;
    }
    
    
    //----------------------------
    
    
    /*map< string, ofxScriptRef > ofxScriptManager::mScripts;
    map< string, ofEvent< ofEventArgs > > ofxScriptManager::mScriptsEvents;
    
    ofxScriptRef ofxScriptManager::get( string filename ){
        if( mScripts.count( filename ) > 0 ){
            return mScripts[ filename ];
        }
        else {
            mScripts[ filename ] = ofxScriptRef( new Script() );
            if( mScripts[ filename ] ->loadFile( filename ) ){
                mScripts[ filename ] ->bindGL();
                return mScripts[ filename ];
            }
            else return ofxScriptRef();
        }
        return ofxScriptRef();
    }
    
    ofEventArgs voidScriptEventArgs;
    
    void ofxScriptManager::update(){
        for( map< string, ofxScriptRef >::iterator it = mScripts.begin(); it != mScripts.end(); ++it ){
            if( it->second->update() ){
                ofNotifyEvent( mScriptsEvents[it->first], voidScriptEventArgs );
            }
        }
    }*/

}