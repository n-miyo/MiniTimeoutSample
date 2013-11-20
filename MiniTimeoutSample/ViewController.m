// -*- mode:objc -*-
//
// Copyright (c) 2013 MIYOKAWA, Nobuyoshi (http://www.tempus.org/)
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#import "ViewController.h"
#import "server.h"

@interface ViewController ()
  <NSURLSessionDelegate>
@property (weak, nonatomic) IBOutlet UITextView *resultView;
@end

@implementation ViewController

#pragma mark - NSURLSession

- (IBAction)sessionButtonPresses:(UIButton *)button
{
  NSLog(@"%s", __FUNCTION__);
  dispatch_async(
    dispatch_get_global_queue( DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
      server();
  });
  self.resultView.text = @"running...";
  NSURLSessionConfiguration *sessionConfig =
  [NSURLSessionConfiguration defaultSessionConfiguration];
  sessionConfig.allowsCellularAccess = YES;
  sessionConfig.timeoutIntervalForRequest = button.tag;
  sessionConfig.timeoutIntervalForResource = 10;
  sessionConfig.HTTPMaximumConnectionsPerHost = 1;

  void (^handler)(NSData *, NSURLResponse *, NSError *) =
  ^(NSData *data, NSURLResponse *response, NSError *error) {
    NSString *s;
    if (error) {
      s = [NSString stringWithFormat:@"session error:\n%@",
           [error localizedDescription]];
    } else {
      s = [NSString stringWithFormat:@"session response:\n%@",
           [[NSString alloc]
            initWithData:data encoding:NSUTF8StringEncoding]];
    }
    dispatch_async(dispatch_get_main_queue(), ^{
      self.resultView.text = s;
    });
  };

  NSURLSession *session =
  [NSURLSession sessionWithConfiguration:sessionConfig
                                delegate:self
                           delegateQueue:nil];

  NSURLSessionDataTask *task;
  NSURL *url = [NSURL URLWithString:@"http://127.0.0.1:8080/"];
  task = [session dataTaskWithURL:url completionHandler:handler];

  [task resume];
}

@end

// EOF
