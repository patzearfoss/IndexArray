//Copyright (c) 2011 Pat Zearfoss, http://zearfoss.wordpress.com
//
//Permission is hereby granted, free of charge, to any person obtaining
//a copy of this software and associated documentation files (the "Software"), 
//to deal in the Software without restriction, including
//without limitation the rights to use, copy, modify, merge, publish,
//distribute, sublicense, and/or sell copies of the Software, and to
//permit persons to whom the Software is furnished to do so, subject to
//the following conditions:
//
//The above copyright notice and this permission notice shall be
//included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import <Foundation/Foundation.h>

@interface PZMultiMap : NSObject <NSCopying>
{
    @private 
    NSMutableDictionary *dictionary_;
    NSMutableOrderedSet *orderedKeys_;
    
    NSComparator keySortComparator_;
    NSComparator objectSortComparator_;
}

@property (nonatomic, copy) NSComparator keySortComparator;
@property (nonatomic, copy) NSComparator objectSortComparator;

// accessing keys
- (id)keyAtIndex:(NSUInteger)index;
- (NSOrderedSet *)allKeys;
- (NSUInteger)keyCount;
- (BOOL)hasKey:(id)key;
- (NSUInteger)indexForKey:(id)key;

// accessing objects
- (id)objectForKeyAtIndex:(NSUInteger)keyIndex objectIndex:(NSUInteger)objIndex;
- (id)objectForKey:(id)key index:(NSUInteger)index;
- (NSArray *)allObjectsForKey:(id)key;
- (NSUInteger)count;

// adding objects
- (void)addObject:(id)object forKey:(id<NSCopying>)key;

// removing objects
- (void)removeObject:(id)object forKey:(id)key;

@end
