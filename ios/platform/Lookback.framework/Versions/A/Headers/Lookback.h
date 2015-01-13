#import <Foundation/Foundation.h>
#import <LookBack/LookbackSettingsViewController.h>

/*! @header Lookback Public API
    Public interface for Lookback, the UX testing tool that records your screen
    and camera and uploads it to http://lookback.io for further study.
*/

/*! @class Lookback

    Lookback should be +[Lookback @link setupWithAppToken: @/link] before being used. After
    that, you can set its [Lookback @link enabled @/link] property to start and stop recording
    at any time. You can use @link LookbackSettingsViewController @/link to provide a user
    interface to do so.
    
    Rather than doing so manually, you can set -[Lookback @link shakeToRecord @/link] to
    display this UI whenever you shake your device.
*/
@interface Lookback : NSObject
/*! In your applicationDidFinishLaunching: or similar, call this method to prepare
    Lookback for use, using the App Token from your integration guide at lookback.io.
    @param appToken A string identifying your app, received from your app settings at http://lookback.io
*/
+ (void)setupWithAppToken:(NSString*)appToken;

/*! Shared instance of Lookback to use from your code. You must call
    +[Lookback @link setupWithAppToken:@/link] before calling this method. */
+ (Lookback*)lookback;

/*! Whether Lookback is set to recording. You can either set this programmatically,
    or use @link LookbackSettingsViewController @/link to let the user activate it. */
@property(nonatomic) BOOL enabled;

/*! If enabled, displays UI to start recording when you shake the device. Default NO.
    
    @discussion This is just a convenience method. It's roughly equivalent to implementing
    -[motionEnded:withEvent:] in your first responder, and modally displaying a
    LookbackSettingsViewController on the window's root view controller.
*/
@property(nonatomic) BOOL shakeToRecord;

/*! Is Lookback paused? Lookback will pause automatically when app is inactive.
    The value of this property is undefined if recording is not enabled (as there
    is nothing to pause). */
@property(nonatomic,getter=isPaused) BOOL paused;

/*! Identifier for the user who's currently using the app. You can filter on
    this property at lookback.io later. If your service has log in user names,
    you can use that here. Optional.
    @seealso http://lookback.io/docs/log-username
*/
@property(nonatomic,copy) NSString *userIdentifier;

/*! Track user navigation manually, if automatic tracking has been disabled.
    @see LookbackAutomaticallyLogViewAppearance
    @param viewIdentifier Unique human readable identifier for a specific view
*/
- (void)enteredView:(NSString*)viewIdentifier;

/*! Track user navigation manually, if automatic tracking has been disabled.
    @see LookbackAutomaticallyLogViewAppearance
    @param viewIdentifier Unique human readable identifier for a specific view
*/
- (void)exitedView:(NSString*)viewIdentifier;

// For debugging
@property(nonatomic,readonly) NSString *appToken;
@end

/*!
    If you only want to use Lookback in builds sent to testers (e g by using the
    CocoaPods :configurations=> feature), you need to avoid both linking with
    Lookback.framework and calling any Lookback code (since that would create
    a linker error). By making all your calls to Lookback_Weak instead of
    Lookback, your calls will be disabled when not linking with Lookback, and
    you thus avoid linker errors.
 
    @example <pre>
        [Lookback_Weak setupWithAppToken:@"<MYAPPTOKEN>"];
        [Lookback_Weak lookback].shakeToRecord = YES;
        
        [Lookback_Weak enteredView:@"Settings"];
        </pre>
*/
#define Lookback_Weak (NSClassFromString(@"Lookback"))


#pragma mark Settings

/*! @group Settings
    These settings can be set using [NSUserDefaults standardUserDefaults] to modify
    the behavior of Lookback. Some of these settings can be modified by the user
    from LookbackSettingsViewController.
*/

/*! If you implement the method `+(NSString*)lookBackIdentifier` in your view controller, that view will automatically be logged under that name (and later filter on it at lookback.io). Otherwise, your view controller's class name will be used instead, with prefix ("UI") and suffix ("ViewController") removed. You can disable this behavior by setting the NSUserDefaults key `LookbackAutomaticallyLogViewAppearance` to NO, and calling `-[LookBack enteredView:]` and `-[LookBack exitedView:]` methods manually.*/
static NSString *const LookbackAutomaticallyLogViewAppearance = @"com.thirdcog.lookback.autologViews";

/*! Normally when you start a recording, it will be paused whenever the application becomes inactive (backgrounded or screen locked). If you record a very long experience, it will take a long time to upload, and be difficult to manage. In this case, you might want to enable the "Upload when inactive" option in Settings (or the LookbackAutosplitSettingsKey BOOL NSUserDefaults key). Then, recording will stop when the app is inactive, the short experience uploaded, and a new recording started anew when the app becomes active.*/
static NSString *const LookbackAutosplitSettingsKey = @"com.thirdcog.lookback.autosplit";

/*! LookbackCameraEnabledSettingsKey controls whether the front-facing camera will record, in addition to recording the screen. */
static NSString *const LookbackCameraEnabledSettingsKey = @"com.thirdcog.lookback.camera.enabled";

/*! The BOOL NSUserDefaults key LookbackAudioEnabledSettingsKey controls whether audio will be recorded together with the front-facing camera. Does nothing if LookbackCameraEnabledSettingsKey is NO. */
static NSString *const LookbackAudioEnabledSettingsKey = @"com.thirdcog.lookback.audio.enabled";

/*! The BOOL NSUserDefaults key LookbackShowPreviewSettingsKey controls whether the user should be shown a preview image of their face at the bottom-right of the screen while recording, to make sure that they are holding their iPhone correctly and are well-framed. */
static NSString *const LookbackShowPreviewSettingsKey = @"com.thirdcog.lookback.preview.enabled";


/*! @group Notifications
    These notifications can be observed from [NSNotificationCenter defaultCenter].
*/

/*! When an experience upload starts, its URL is determined. You can then attach this URL to a bug report or similar.

    @example <pre>
        // Automatically put an experience's URL on the user's pasteboard when recording ends and upload starts.
        [[NSNotificationCenter defaultCenter] addObserverForName:LookbackStartedUploadingNotificationName object:nil queue:[NSOperationQueue mainQueue] usingBlock:^(NSNotification *note) {
            NSDate *when = [note userInfo][LookbackExperienceStartedAtUserInfoKey];
            if(fabs([when timeIntervalSinceNow]) < 60) { // Only if it's for an experience we just recorded
                NSURL *url = [note userInfo][LookbackExperienceDestinationURLUserInfoKey];
                [UIPasteboard generalPasteboard].URL = url;
            }
        }];</pre>
*/
static NSString *const LookbackStartedUploadingNotificationName = @"com.thirdcog.lookback.notification.startedUploading";

/*! UserInfo key in a @link LookbackStartedUploadingNotificationName @/link notification. The value is an NSURL that the user can visit
    on a computer to view the experience he/she just recorded. */
static NSString *const LookbackExperienceDestinationURLUserInfoKey = @"com.thirdcog.lookback.notification.startedUploading.destinationURL";

/*! UserInfo key in a @link LookbackStartedUploadingNotificationName @/link notification. The value is an NSDate of when the given experience
    was recorded (so you can correlate the upload with the recording). */
static NSString *const LookbackExperienceStartedAtUserInfoKey = @"com.thirdcog.lookback.notification.startedUploading.sessionStartedAt";



/*!
 *   @group Compatibility macros
 *   For compatibility with old code using Lookback under the miscapitalized or misprefixed names.
 */
#define LookBack Lookback
#define GFAutomaticallyLogViewAppearance LookbackAutomaticallyLogViewAppearance
#define GFAutosplitSettingsKey LookbackAutosplitSettingsKey
#define GFCameraEnabledSettingsKey LookbackCameraEnabledSettingsKey
#define GFAudioEnabledSettingsKey LookbackAudioEnabledSettingsKey
#define GFShowPreviewSettingsKey LookbackShowPreviewSettingsKey
#define GFStartedUploadingNotificationName LookbackStartedUploadingNotificationName
#define GFExperienceDestinationURLUserInfoKey LookbackExperienceDestinationURLUserInfoKey
#define GFExperienceStartedAtUserInfoKey LookbackExperienceStartedAtUserInfoKey

