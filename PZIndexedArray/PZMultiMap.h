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

/**
 A comparator to use when inserting objects
 */
@property (nonatomic, copy) NSComparator keySortComparator;

/**
 A comparator to use when inserting objects
 */
@property (nonatomic, copy) NSComparator objectSortComparator;

#pragma mark - accessing keys
- (id)keyAtIndex:(NSUInteger)index;

/**
 Returns the set of keys
 @return the sorted set of keys
 */
- (NSOrderedSet *)allKeys;

/**
 Returns the count of keys in the collection
 @return the count
 */
- (NSUInteger)keyCount;

/**
 Determine if the collection contains the key
 @param key the key to search for
 @return YES if the collection contains the key, NO otherwise
 */
- (BOOL)hasKey:(id)key;

/**
 Returns the index of the specified key.
 @param key the key
 @return the index or NSNotFound if the collection doesn't contain that key
 */
- (NSUInteger)indexForKey:(id)key;

#pragma mark - accessing objects
/**
 Returns the object at the given index for the given key index
 @param keyIndex the index of the key to return the object for
 @param objIndex the index of the object to return
 @return the object or nil if it does not exist
 */
- (id)objectForKeyAtIndex:(NSUInteger)keyIndex objectIndex:(NSUInteger)objIndex;

/**
 Returns the object at the specified index for the specified key
 @param key
 @param index
 @return the object or nil if it doesn't exist
 */
- (id)objectForKey:(id)key index:(NSUInteger)index;

/**
 Returns all objects for the given key
 @param key 
 @param the array objects for that key or nil if the key doesn't exist
 */
- (NSArray *)allObjectsForKey:(id)key;

/**
 Returns the count of objects in the Multimap
 */
- (NSUInteger)count;

#pragma mark - adding objects
/**
 Adds the specified object for the given key.
 If the key does not exist it will be created.
 @param object the object to add
 @param key the key to add it under
 */
- (void)addObject:(id)object forKey:(id<NSCopying>)key;

#pragma mark - removing objects
/**
 Removes all pointers to the specified object for the specified key
 @param object the object to remove
 @param key the under which to remove it
 */
- (void)removeObject:(id)object forKey:(id)key;

@end
