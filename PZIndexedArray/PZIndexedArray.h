//
//  PZIndexedArray.h
//  SalesBagStandalone
//
//  Created by Patrick Zearfoss on 10/27/11.
//  Copyright (c) 2011 Mindgrub Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PZIndexedArray : NSObject <NSCopying>
{
    @private 
    NSMutableDictionary *dictionary_;
    NSMutableOrderedSet *orderedKeys_;
    
    SEL keySortSelector_;
    SEL objectSortSelector_;
    NSComparator keySortComparator_;
    NSComparator objectSortComparator_;
    
    BOOL sortsKeys_;
    BOOL sortsObjects_;
    BOOL usesComparatorForKeys_;
    BOOL usesComparatorForObjects_;
}

@property (nonatomic, assign) SEL keySortSelector;
@property (nonatomic, assign) SEL objectSortSelector;
@property (nonatomic, copy) NSComparator keySortComparator;
@property (nonatomic, copy) NSComparator objectSortComparator;

// accessing keys
- (id)keyAtIndex:(NSUInteger)index;
- (NSOrderedSet *)allKeys;
- (NSUInteger)keyCount;

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
