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

#import "PZMultiMap.h"

@interface PZMultiMap()
- (void)insertKeySorted:(id)key;
- (void)insertObject:(id)object array:(NSMutableArray *)array;

@property (nonatomic) BOOL sortsKeys;
@property (nonatomic) BOOL sortsObjects;
@property (nonatomic, strong) NSMutableDictionary *dictionary;
@property (nonatomic, strong) NSMutableOrderedSet *orderedKeys;

@end

@implementation PZMultiMap
@synthesize keySortComparator = keySortComparator_;
@synthesize objectSortComparator = objectSortComparator_;

- (id)init
{
    self = [super init];
    if (self)
    {
        _dictionary = [[NSMutableDictionary alloc] init];
        _orderedKeys = [[NSMutableOrderedSet alloc] init];
    }
    
    return self;
}


#pragma mark NSCopying
- (id)copyWithZone:(NSZone *)zone
{
    PZMultiMap *copy = [[[self class] alloc] init];
    copy.orderedKeys = [self.orderedKeys copyWithZone:zone];
    copy.dictionary = [self.dictionary copyWithZone:zone];
    copy.keySortComparator = self.keySortComparator;
    copy.objectSortComparator = self.objectSortComparator;

    
    return copy;   
}

// accessing keys
- (id)keyAtIndex:(NSUInteger)index
{
    if ([self.orderedKeys count] == 0)
    {
        return nil;
    }
    
    return [self.orderedKeys objectAtIndex:index];
}

- (NSOrderedSet *)allKeys
{
    return [self.orderedKeys copy];
}

- (NSUInteger)keyCount
{
    return [self.orderedKeys count];
}

- (BOOL)hasKey:(id)key
{
    NSInteger index = [self.orderedKeys indexOfObject:key];
    return index != NSNotFound;
}

- (NSUInteger)indexForKey:(id)key
{
    return [self.orderedKeys indexOfObject:key];
}

// accessing objects
- (id)objectForKey:(id)key index:(NSUInteger)index
{
    NSArray *array = [self.dictionary objectForKey:key];
    if (array && index < [array count])
    {
        return [array objectAtIndex:index];
    }
    
    return nil;
}

- (id)objectForKeyAtIndex:(NSUInteger)keyIndex objectIndex:(NSUInteger)objIndex
{
    id key = [self keyAtIndex:keyIndex];
    return [self objectForKey:key index:objIndex];
}

- (NSArray *)allObjectsForKey:(id)key
{
    return [[self.dictionary objectForKey:key] copy];
}

- (NSUInteger)count
{
    NSUInteger count = 0;
    for (id key in [self.dictionary allKeys])
    {
        count += [[self.dictionary objectForKey:key] count];
    }
    
    return count;
}

// adding objects
- (void)addObject:(id)object forKey:(id<NSCopying>)key
{
    NSMutableArray *array = [self.dictionary objectForKey:key];
    if (!array)
    {
        array = [NSMutableArray array];
        [self.dictionary setObject:array forKey:key];
        
        if (self.sortsKeys)
        {
            [self insertKeySorted:key];
        }
        else
        {
            [self.orderedKeys addObject:key];
        }
    }
    
    if (self.sortsObjects)
    {
        [self insertObject:object array:array];
    }
    else
    {
        [array addObject:object];
    }
}

// removing
- (void)removeObject:(id)object forKey:(id)key
{
    NSMutableArray *array = [self.dictionary objectForKey:key];
    [array removeObject:object];
    if ([array count] == 0)
    {
        [self.orderedKeys removeObject:key];
        [self.dictionary removeObjectForKey:key];
    }
}

#pragma mark - sorting
- (void)insertKeySorted:(id)key
{
    if ([self.orderedKeys count] == 0)
    {
        [self.orderedKeys addObject:key];
        return;
    }
    
    __block NSUInteger insertIndex = -1;

    
    [self.orderedKeys enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if (idx  < [self.orderedKeys count])
        {     
            NSComparisonResult result = NSOrderedAscending;

            result = self.keySortComparator(key, obj);

            
            if (result == NSOrderedAscending)
            {
                insertIndex = idx;
                *stop = YES;
            }
                                
        }
    }];
    
    if (insertIndex == -1)
    {
        [self.orderedKeys addObject:key];
    }
    else
    {
        [self.orderedKeys insertObject:key atIndex:insertIndex];
    }
}

- (void)insertObject:(id)object array:(NSMutableArray *)array
{
    if ([array count] == 0)
    {
        [array addObject:object];
        return;
    }
    
    __block NSUInteger insertIndex = -1;
    
    [array enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        NSComparisonResult result = NSOrderedAscending;
        

        result = self.objectSortComparator(object, obj);

        
        if (result == NSOrderedAscending)
        {
            insertIndex = idx;
            *stop = YES;
        }
    }];
    
    if (insertIndex == -1)
    {
        [array addObject:object];
    }
    else
    {
        [array insertObject:object atIndex:insertIndex];
    }
}

#pragma mark -  handling selectors and comparators


- (void)setKeySortComparator:(NSComparator)keySortComparator
{
    if (keySortComparator != keySortComparator_)
    {
        keySortComparator_ = [keySortComparator copy];
    }
    
    self.sortsKeys = keySortComparator != nil;
}

- (void)setObjectSortComparator:(NSComparator)objectSortComparator
{
    if (objectSortComparator != objectSortComparator_)
    {
        objectSortComparator_ = [objectSortComparator copy];
    }
    
    self.sortsObjects = objectSortComparator != nil;
}

@end
