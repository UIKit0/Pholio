//
//  IPPhotoScrollView.h
//
//  This subclass of IPPhotoScrollView lets you pinch-to-zoom to zoom in
//  and out of a photo.
//
//  Created by Brian Dewey on 6/4/11.
//  Copyright 2011 Brian Dewey. 
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <Foundation/Foundation.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

@class IPPhoto;
@interface IPPhotoScrollView : UIScrollView<UIScrollViewDelegate> { }

//
//  The photo we are displaying.
//

@property (nonatomic, retain) IPPhoto *photo;
@end
