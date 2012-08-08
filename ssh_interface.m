//
//  ssh_interface.m
//  Secret Socks
//
//  Created by Joshua Chan on 10/07/09
//  Enhanced by HK Chai Nov 2011
//

#import "ssh_interface.h"


@implementation ssh_interface

@synthesize localSocksPort;
@synthesize serverSshPort;
@synthesize serverHostname;
@synthesize serverSshUsername;
@synthesize serverSshPasswd;


- (void)connectToServer:(id) controller 
{
	NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
	// Bundled obfuscated-openssh client.
	NSString *sshPath = [[thisBundle resourcePath] stringByAppendingString:@"/ssh"];
	// Dirty hack around openssh piped password restriction.
	NSString *askpassPath = [[thisBundle resourcePath] stringByAppendingString:@"/pass"];

	// Required arguments
	NSMutableArray *sshArguments = [NSMutableArray arrayWithObjects: 
		@"-p", serverSshPort,
		@"-l", serverSshUsername,
		@"-ND", localSocksPort,
		@"-o StrictHostKeyChecking=no",
		serverHostname,
		nil
	];

	// Set launch path
	[sshArguments insertObject: sshPath atIndex: 0];
	// Set environment
	NSDictionary *environment = [NSDictionary 
		dictionaryWithObjects:
			[NSArray arrayWithObjects: @":1", askpassPath, serverSshPasswd, nil]
		forKeys:
			[NSArray arrayWithObjects: @"DISPLAY", @"SSH_ASKPASS", @"SSH_PASSWD", nil]
	];
	[sshArguments insertObject: environment atIndex: 0];
	
	sshTask = [[TaskWrapper alloc] initWithController:controller arguments:sshArguments];
	[sshTask startProcess];

	return;
}


- (void)disconnectFromServer 
{
	[sshTask stopProcess];
}

- (bool)hasTerminated
{
	return [sshTask hasTerminated];
}

- (void)dealloc
{
	[self disconnectFromServer];
	[super dealloc];
}


@end


