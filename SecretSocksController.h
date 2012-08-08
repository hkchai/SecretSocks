//
//  SecretSocksController.h
//  Secret Socks
//
//  Created by Joshua Chan on 11/07/09.
//  Enhanced by HK Chai Nov 2011
//

#import <Cocoa/Cocoa.h>
#import "ssh_interface.h"
#import "TaskWrapper.h"

#include <stdio.h>
#include <string.h>
//#import <Security/Authorization.h>

// Number of seconds to wait for SSH to connect
#define SSH_TIMEOUT 10

@interface SecretSocksController : NSObject <TaskWrapperController> 
{
	IBOutlet NSMenuItem *connectMenu;
	IBOutlet NSMenuItem *disconnectMenu;
	
    // Settings menu
	IBOutlet NSTabView *tabs;
	IBOutlet NSTextField *hostnameField;
	IBOutlet NSTextField *portnumField;
	IBOutlet NSTextField *usernameField;
	IBOutlet NSTextField *passwordField;
	IBOutlet NSTextField *socksportField;
	IBOutlet NSButton *applyToNetwork;
	IBOutlet NSButton *toggleDrawer;
    IBOutlet NSButton *isAsymKeysFirst;
    IBOutlet NSButton *isAutoLogin;

    // Log menu
	IBOutlet NSTextView *statusLabel;
    
    // Help menu
    IBOutlet NSTextView *helpText;
    
	IBOutlet NSButton *connectButton;
	IBOutlet NSImageView *checkmark;
	IBOutlet NSProgressIndicator *busySpin;
	IBOutlet NSWindow *window;
	IBOutlet NSDrawer *drawer;

	IBOutlet NSDrawer *passwordDrawer;
	IBOutlet NSTextField *passwordField2;

	ssh_interface *sshInterface;
	bool isConnected;
	bool windowHasBeenClosed;
	NSBundle *thisBundle;
	
	NSUserDefaults *preferences;
}

- (id)init;
- (IBAction)showConfig:(id)sender;
- (IBAction)showStatus:(id)sender;
- (IBAction)showHelp:(id)sender;
- (IBAction)doConnect:(id)sender;
- (IBAction)stateChanged:(id)sender;
- (void)toggleCheckmark:(bool)status;
- (void)toggleSOCKSSetting:(bool)status;
- (void)loadPrefs;
- (void)savePrefs;
- (void)applicationWillFinishLaunching: (NSNotification *)aNotification;
- (BOOL)drawerShouldOpen:(NSDrawer *)sender;
- (BOOL)drawerShouldClose:(NSDrawer *)sender;
- (void)drawerDidOpen:(NSNotification *)notification;
- (void)windowDidMiniaturize:(NSNotification *)notification;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)theSender;
- (BOOL)windowShouldClose:(id)theWindow;
- (void)applicationWillTerminate:(NSApplication *)theApplication;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;

@end
