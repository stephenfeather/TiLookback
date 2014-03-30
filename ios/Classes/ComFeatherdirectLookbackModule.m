/**
 * Your Copyright Here
 *
 * Appcelerator Titanium is Copyright (c) 2009-2010 by Appcelerator, Inc.
 * and licensed under the Apache Public License (version 2)
 */
#import "ComFeatherdirectLookbackModule.h"
#import "TiBase.h"
#import "TiHost.h"
#import "TiUtils.h"
#import "TiApp.h"
#import <Lookback/Lookback.h>

@implementation ComFeatherdirectLookbackModule

#pragma mark Internal

// this is generated for your module, please do not change it
-(id)moduleGUID
{
	return @"c6cd4edb-5730-42a5-a071-d43d751f2c09";
}

// this is generated for your module, please do not change it
-(NSString*)moduleId
{
	return @"com.featherdirect.lookback";
}

#pragma mark Lifecycle

-(void)startup
{
	// this method is called when the module is first loaded
	// you *must* call the superclass
	[super startup];
    
    // Get our api key from Ti.App.Properties
    // Ti.App.Properties.setString('LookbackAppToken',"your_app_token");
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSString *apptoken = [[defaults stringForKey:@"LookbackAppToken"] copy];

    // if we have a token available, lets start up Lookback
    if (apptoken){
        [Lookback_Weak setupWithAppToken:apptoken];
        NSLog(@"[Lookback] has been setup with apptoken: %@", apptoken);
    } else {
        NSLog(@"[Lookback] apptoken is missing from properties, use .setup(apptoken)");
    }
    
    
    //setup Lookback
	
	NSLog(@"[INFO] %@ loaded",self);
}


-(void)shutdown:(id)sender
{
	// this method is called when the module is being unloaded
	// typically this is during shutdown. make sure you don't do too
	// much processing here or the app will be quit forceably
	
	// you *must* call the superclass
	[super shutdown:sender];
}

#pragma mark Cleanup 

-(void)dealloc
{
	// release any resources that have been retained by the module
	[super dealloc];
}

#pragma mark Internal Memory Management

-(void)didReceiveMemoryWarning:(NSNotification*)notification
{
	// optionally release any resources that can be dynamically
	// reloaded once memory is available - such as caches
	[super didReceiveMemoryWarning:notification];
}

#pragma mark Listener Notifications

-(void)_listenerAdded:(NSString *)type count:(int)count
{
	if (count == 1 && [type isEqualToString:@"my_event"])
	{
		// the first (of potentially many) listener is being added 
		// for event named 'my_event'
	}
}

-(void)_listenerRemoved:(NSString *)type count:(int)count
{
	if (count == 0 && [type isEqualToString:@"my_event"])
	{
		// the last listener called for event named 'my_event' has
		// been removed, we can optionally clean up any resources
		// since no body is listening at this point for that event
	}
}

#pragma Public APIs

// If enabled, displays UI to start recording when you shake the device. Default NO.
-(id)enableShakeToRecord:(id)arg
{
    [Lookback_Weak lookback].shakeToRecord = YES;
    return NUMBOOL([Lookback_Weak lookback].shakeToRecord);
}

-(id)disableShakeToRecord:(id)arg
{
    [Lookback_Weak lookback].shakeToRecord = NO;
    return NUMBOOL([Lookback_Weak lookback].shakeToRecord);
}

-(id)shakeToRecord
{
    NSLog(@"[Lookback] shakeToRecord enabled: %@", [Lookback_Weak lookback].shakeToRecord);
    return NUMBOOL([Lookback_Weak lookback].shakeToRecord);
}

// Whether Lookback is set to recording.
-(id)enabled
{
    return NUMBOOL([Lookback_Weak lookback].enabled);
}

// Is Lookback paused? Lookback will pause automatically when app is inactive.
//-(id)paused
//{
//    NSLog(@"paused? %@", [Lookback_Weak lookback].paused);
//    return [Lookback_Weak lookback].paused;
//}

//Identifier for the user who's currently using the app.
-(id)setUserIdentifier:(id)arg
{
    NSString *userIdentifier = [TiUtils stringValue:arg];
    [Lookback_Weak lookback].userIdentifier = userIdentifier;
    NSLog(@"[Lookback] userIdentifier set to: %@", userIdentifier);
    return [Lookback_Weak lookback].userIdentifier;
}



@end
