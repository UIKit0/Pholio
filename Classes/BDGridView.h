//
//  BDGridView.h
//
//  This displays a grid of |BDGridCell| views in a |UIScrollView| that
//  scrolls vertically, like scrolling through the pictures in the iOS
//  photos app.
//
//  Created by Brian Dewey on 4/21/11.
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

#import <UIKit/UIKit.h>

//
//  This is the default minimum amount of padding between cell columns in the view.
//  You need space for the user to tap between cells and bring up an edit menu.
//

#define kMinimumPadding         (20)

@class BDGridCell;
@protocol BDGridViewDataSource;
@protocol BDGridViewDelegate;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


@interface BDGridView : UIScrollView<UIGestureRecognizerDelegate> {
    
}

//
//  This is the minimum amount of padding between columns in the view.
//  The number of cells per row will be decreased to ensure that there is
//  at least this much padding.
//
//  Defaults to kMinimumPadding.
//

@property (nonatomic, assign) CGFloat minimumPadding;

//
//  The current amount of padding between columns in the view. This
//  is updated on |recomputeContentSize|.
//

@property (nonatomic, assign, readonly) CGFloat padding;

//
//  Optional padding at the top of the view contents.
//

@property (nonatomic, assign) CGFloat topContentPadding;

//
//  The computed number of cells per row. Based on |numberOfCells|, |cellSize|, 
//  and |view.frame|. Not valid until |reloadData| has been sent.
//

@property (nonatomic, readonly) NSUInteger cellsPerRow;

//
//  The computed number of rows. Based on |numberOfCells|, |cellSize|, and
//  |view.frame|. Not valid until |reloadData| has been sent.
//

@property (nonatomic, readonly) NSUInteger countOfRows;

//
//  The font color to use for the text in all cells.
//

@property (nonatomic, retain) UIColor *fontColor;

//
//  The font to use for the text in all cells.
//

@property (nonatomic, retain) UIFont *font;

//
//  The data source for this grid view.
//

@property (nonatomic, assign) id<BDGridViewDataSource> dataSource;

//
//  Delegate that responds to interaction events.
//

@property (nonatomic, assign) id<BDGridViewDelegate> gridViewDelegate;

//
//  Purely here for testability. Note that, in spite of the name, |lastVisibleIndex|
//  is *exclusive*. It's probably best called "firstNonVisibleIndex"
//  instead. 
//
//  TODO: Fire up the refactor engine :-)
//

@property (nonatomic, readonly) NSInteger firstVisibleIndex;
@property (nonatomic, readonly) NSInteger lastVisibleIndex;

//
//  Reloads / redraws the grid.
//

- (void)reloadData;

//
//  Gets the frame of a cell.
//

- (CGRect)frameForCellAtIndex:(NSUInteger)index;

//
//  Tells the grid that a new cell was inserted. Animates the change.
//

- (BDGridCell *)insertCellAtIndex:(NSUInteger)index;

//
//  Tells the grid view that a cell was deleted. Animates the change.
//

- (void)deleteCellAtIndex:(NSUInteger)index;

//
//  Gets a recycled cell.
//

- (BDGridCell *)dequeueCell;

//
//  Sets the active gap, with control over animation.
//

- (void)setActiveGap:(NSUInteger)activeGap animated:(BOOL)animated;

@end

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  The data source for a |BDGridView|.
//

@protocol BDGridViewDataSource <NSObject>

//
//  Return the number of cells in the view.
//

- (NSUInteger)gridViewCountOfCells:(BDGridView *)gridView;

//
//  Return the size of each grid cell.
//

- (CGSize)gridViewSizeOfCell:(BDGridView *)gridView;

//
//  Return a cell for the given index.
//

- (BDGridCell *)gridView:(BDGridView *)gridView cellForIndex:(NSUInteger)index;

@end

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  Respond to |BDGridView| events.
//

@protocol BDGridViewDelegate <NSObject>

@optional

//
//  Should the grid view allow any editing at all?
//

- (BOOL)gridViewShouldEdit:(BDGridView *)gridView;

//
//  Sent when the user tapped on a cell.
//

- (void)gridView:(BDGridView *)gridView didTapCell:(BDGridCell *)cell;

//
//  Sent when the user wants to insert a new item at |insertionPoint|.
//

- (void)gridView:(BDGridView *)gridView 
didInsertAtPoint:(NSUInteger)insertionPoint 
        fromRect:(CGRect)rect;

//
//  Sent when the user wants to insert a new item into an existing cell.
//  The delegate should implement this only if the cells are containers;
//  otherwise, implement only |gridView:didInsertAtPoint:fromRect:|.
//

- (void)gridView:(BDGridView *)gridView didInsertIntoCell:(BDGridCell *)cell;

//
//  The user moved an item from one index to another.
//

- (void)gridView:(BDGridView *)gridView didMoveItemFromIndex:(NSUInteger)initialIndex 
         toIndex:(NSUInteger)finalIndex;

//
//  Cut.
//

- (void)gridView:(BDGridView *)gridView didCut:(NSSet *)indexes;

//
//  Copy.
//

- (void)gridView:(BDGridView *)gridView didCopy:(NSSet *)indexes;

//
//  Can the delegate paste what's currently on the pasteboard?
//  NOTE: If you implement |gridViewCanPaste:|, you MUST also implement
//  |gridView:didRequestPasteAtPoint:|.
//

- (BOOL)gridViewCanPaste:(BDGridView *)gridView;

//
//  Paste.
//

- (void)gridView:(BDGridView *)gridView didPasteAtPoint:(NSUInteger)insertionPoint;

//
//  Paste into an existing cell. Delegates should implement this only if the cell
//  represents a container.
//

- (void)gridView:(BDGridView *)gridView didPasteIntoCell:(BDGridCell *)cell;

//
//  Delete.
//

- (void)gridView:(BDGridView *)gridView didDelete:(NSSet *)indexes;

@end
