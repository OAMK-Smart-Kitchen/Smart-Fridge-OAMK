//
//  Copyright 2012-2013, Andrii Mamchur
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
//  limitations under the License

#import "JsonLiteObjCCoverageTests.h"
#import "JsonLiteSenTestCaseExt.h"

#include "jsonlite.h"

#import "JsonLiteParser.h"
#import "JsonLiteAccumulator.h"
#import "JsonLiteSerializer.h"
#import "JsonLiteObjC.h"

#import <objc/runtime.h>
#import <objc/message.h>

static void state_suspend(jsonlite_callback_context *ctx) {
    jsonlite_parser_suspend(ctx->parser);
}

static void value_suspend(jsonlite_callback_context *ctx, jsonlite_token *token) {
    jsonlite_parser_suspend(ctx->parser);
}

@interface ParseSuspender : NSObject<JsonLiteParserDelegate>
@end

@implementation ParseSuspender

- (void)parser:(JsonLiteParser *)parser didFinishParsingWithError:(NSError *)errors {
}

- (void)parserDidStartObject:(JsonLiteParser *)parser {
    [parser suspend];
}

- (void)parserDidEndObject:(JsonLiteParser *)parser {
    [parser suspend];
}

- (void)parserDidStartArray:(JsonLiteParser *)parser {
    [parser suspend];
}

- (void)parserDidEndArray:(JsonLiteParser *)parser {
    [parser suspend];
}

- (void)parserFoundTrueToken:(JsonLiteParser *)parser {
    [parser suspend];
}

- (void)parserFoundFalseToken:(JsonLiteParser *)parser {
    [parser suspend];
}

- (void)parserFoundNullToken:(JsonLiteParser *)parser {
    [parser suspend];
}

- (void)parser:(JsonLiteParser *)parser foundKeyToken:(JsonLiteStringToken *)token {
    [parser suspend];
}

- (void)parser:(JsonLiteParser *)parser foundStringToken:(JsonLiteStringToken *)token {
    [parser suspend];
}

- (void)parser:(JsonLiteParser *)parser foundNumberToken:(JsonLiteNumberToken *)token {
    [parser suspend];
}

@end


@interface JsonLiteObjCCoverageTests()<JsonLiteParserDelegate>

@end

@implementation JsonLiteObjCCoverageTests

- (void)parser:(JsonLiteParser *)parser didFinishParsingWithError:(NSError *)error  {
}

- (void)parserDidStartObject:(JsonLiteParser *)parser {
    XCTAssertNotNil(parser, @"Parser is nil");
}

- (void)parserDidEndObject:(JsonLiteParser *)parser {
    XCTAssertNotNil(parser, @"Parser is nil");
}

- (void)parserDidStartArray:(JsonLiteParser *)parser {
    XCTAssertNotNil(parser, @"Parser is nil");
}

- (void)parserDidEndArray:(JsonLiteParser *)parser {
    XCTAssertNotNil(parser, @"Parser is nil");
}

- (void)parserFoundTrueToken:(JsonLiteParser *)parser {
    XCTAssertNotNil(parser, @"Parser is nil");
}

- (void)parserFoundFalseToken:(JsonLiteParser *)parser {
    XCTAssertNotNil(parser, @"Parser is nil");
}

- (void)parserFoundNullToken:(JsonLiteParser *)parser {
    XCTAssertNotNil(parser, @"Parser is nil");
}

- (void)parser:(JsonLiteParser *)parser foundKeyToken:(JsonLiteStringToken *)token {
    XCTAssertNotNil(parser, @"Parser is nil");
    XCTAssertNotNil(token, @"Token is nil");
    [token retain];
    [token retain];
    [token release];
    [token autorelease];
    XCTAssertTrue([token retainCount] > 0, @"Bad retainCount");
    XCTAssertTrue([token description] != nil, @"Bad description");
}

- (void)parser:(JsonLiteParser *)parser foundStringToken:(JsonLiteStringToken *)token {
    XCTAssertNotNil(parser, @"Parser is nil");
    XCTAssertNotNil(token, @"Token is nil");
    [token retain];
    [token retain];
    [token release];
    [token autorelease];
    XCTAssertTrue([token retainCount] > 0, @"Bad retainCount");
    XCTAssertTrue([token description] != nil, @"Bad description");
}

- (void)parser:(JsonLiteParser *)parser foundNumberToken:(JsonLiteNumberToken *)token {
    XCTAssertNotNil(parser, @"Parser is nil");
    XCTAssertNotNil(token, @"Token is nil");
    [token retain];
    [token retain];
    [token release];
    [token autorelease];
    XCTAssertTrue([token retainCount] > 0, @"Bad retainCount");
    XCTAssertTrue([token description] != nil, @"Bad description");
}

- (void)testIncorrectInitialization {
    jsonlite_result result = jsonlite_parser_get_result(NULL);
    XCTAssertTrue(result == jsonlite_result_invalid_argument, @"Bad error");

    jsonlite_parser ps = jsonlite_parser_init(100);
    char json[] = "{}";
    result = jsonlite_parser_tokenize(NULL, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_argument, @"Bad error");
    
    result = jsonlite_parser_tokenize(ps, NULL, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_argument, @"Bad error");
    
    result = jsonlite_parser_tokenize(ps, json, 0);
    XCTAssertTrue(result == jsonlite_result_invalid_argument, @"Bad error");
    
    result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_ok, @"Bad error");
    
    jsonlite_parser_release(ps);
}

- (void)testEmptyCallbacks {
    char json[] = "{\"key\" : 12345, \"array\": [null, true, false, \"string\"]}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_ok, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testInvalidEscape {
    char json[] = "{\"key\" : \"\\u000Q\"}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_escape, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testInvalidNegativeNumber {
    char json[] = "{\"key\" : -w}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_number, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testInvalidHexNumber {
    char json[] = "{\"key\" : -0x0011}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_number, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testInvalidNumberEnding {
    char json[] = "{\"key\" : 123456w}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_number, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testInvalidFracStart {
    char json[] = "{\"key\" : 12345.A132}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_number, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testInvalidFracEnding {
    char json[] = "{\"key\" : 12345.132A}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_number, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testInvalidExpEnding {
    char json[] = "{\"key\" : 12345.132e01A}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_invalid_number, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testJsonChunk {
    char json1[] = "{\"key\" : 12345, \"obj\": {}, \"arr";
    char json2[] = "ay\":[null, true, false, \"string\"]}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json1, sizeof(json1) - 1);
    XCTAssertTrue(result == jsonlite_result_end_of_stream, @"Parse fails");
    result = jsonlite_parser_tokenize(ps, json2, sizeof(json2) - 1);
    XCTAssertTrue(result == jsonlite_result_ok, @"Parse fails");
    jsonlite_parser_release(ps);
}

- (void)testHashCollision {
    NSString *str1 = @"Test_#83410_Collision";
    NSString *str2 = @"Test_#152260_Collision";
    NSString *str3 = @"                u-1(l";
    
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:3];
    [array addObject:str1];
    [array addObject:str2];
    [array addObject:str3];

    JsonLiteSerializer *ser = [JsonLiteSerializer serializer];
    NSData *data = [ser serializeObject:array];
    
    id obj = [JsonLiteObjC objectFromData:data depth:32];
    XCTAssertTrue([array isEqual:obj], @"Not Equal");
}

- (void)testParser {
    JsonLiteParser *parser = [JsonLiteParser parserWithDepth:32];
    JsonLiteAccumulator *acc = [JsonLiteAccumulator accumulatorWithDepth:32];
    parser.delegate = acc;
    NSData *data = [NSData data];
    
    [parser reset];
    [acc reset];
    [parser parse:data];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeInvalidArgument, @"Bad error");
    
    [parser reset];
    [acc reset];
    [parser parse:nil];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeInvalidArgument, @"Bad error");
    
    [parser reset];
    [acc reset];
    [parser parse:nil];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeInvalidArgument, @"Bad error");
    
    char json1[] = "     ";
    char json2[] = "{\"key\" : 12345, \"obj\": {}, \"arr";
    char json3[] = "ay\":[null, true, false, \"string\", {\"acb\" : 1}],";
    char json4[] = "\"child\": {\"key\" : 12345, \"array\":[]},";
    char json5[] = "\"mixarray\": [\"string\", 0, null, true, false] }";
 
    [parser reset];
    [acc reset];
    parser.delegate = acc;
    [parser parse:[NSData dataWithBytes:json1 length:sizeof(json1) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json2 length:sizeof(json2) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json3 length:sizeof(json3) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json4 length:sizeof(json4) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json5 length:sizeof(json5) - 1]];
    XCTAssertTrue(parser.parseError == nil, @"Incorrect error");
    
    [parser reset];
    [acc reset];
    parser.delegate = self;
    [parser parse:[NSData dataWithBytes:json1 length:sizeof(json1) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json2 length:sizeof(json2) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json3 length:sizeof(json3) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json4 length:sizeof(json4) - 1]];
    XCTAssertTrue([parser.parseError code] == JsonLiteCodeEndOfStream, @"Incorrect error");
    [parser parse:[NSData dataWithBytes:json5 length:sizeof(json5) - 1]];
    XCTAssertTrue(parser.parseError  == nil, @"Incorrect error");
    [acc reset];
    
    Class cls = [JsonLiteToken class];
    IMP imp = class_getMethodImplementation(cls, @selector(copyValue));
    imp(nil, nil);
}

- (void)testEmptyJsonChunk {
    char json1[] = "     ";
    char json2[] = "{\"key\" : 12345, \"obj\": {}, \"arr";
    char json3[] = "ay\":[null, true, false, \"string\"]}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json1, sizeof(json1) - 1);
    XCTAssertTrue(result == jsonlite_result_end_of_stream, @"Parse fails");
    result = jsonlite_parser_tokenize(ps, json2, sizeof(json2) - 1);
    XCTAssertTrue(result == jsonlite_result_end_of_stream, @"Parse fails");
    
    result = jsonlite_parser_tokenize(ps, json3, sizeof(json3) - 1);
    XCTAssertTrue(result == jsonlite_result_ok, @"Parse fails");
    
    jsonlite_parser_release(ps);
}

- (void)testJsonChunkIncorrectInitialization {
    char json1[] = "{\"key\" : 12345, \"obj\": {}, \"arr";
    char json2[] = "ay\":[null, true, false, \"string\"]}";
    jsonlite_parser ps = jsonlite_parser_init(100);
    XCTAssertTrue(ps != NULL, @"jsonlite_init_parser return NULL");
    jsonlite_result result = jsonlite_parser_tokenize(ps, json1, sizeof(json1) - 1);
    XCTAssertTrue(result == jsonlite_result_end_of_stream, @"Parse fails");
    jsonlite_parser next = jsonlite_parser_init(100);
    
    result = jsonlite_parser_tokenize(NULL, json2, sizeof(json2) - 1);
    XCTAssertTrue(result == jsonlite_result_invalid_argument, @"Bad error");

    result = jsonlite_parser_tokenize(ps, json2, sizeof(json2) - 1);
    XCTAssertTrue(result == jsonlite_result_ok, @"Parse fails");
    
    jsonlite_parser_release(ps);
    jsonlite_parser_release(next);
}

- (void)testSuspendResume {
    char json1[] = "{\"key\" : 12345, \"obj\": {}, \"array\":[null, true, false, \"string\"]}";
    jsonlite_parser p = jsonlite_parser_init(100);
    jsonlite_parser_callbacks cbs = {
        &state_suspend,
        &state_suspend,
        &state_suspend,
        &state_suspend,
        &state_suspend,
        &state_suspend,
        &state_suspend,
        &state_suspend,
        &value_suspend,
        &value_suspend,
        &value_suspend,
        NULL
    };
    jsonlite_parser_set_callback(p, &cbs);
    
    jsonlite_result result = jsonlite_parser_resume(p);
    XCTAssertTrue(result == jsonlite_result_not_allowed, @"Bad result");
    
    result = jsonlite_parser_resume(NULL);
    XCTAssertTrue(result == jsonlite_result_invalid_argument, @"Bad result");
    
    result = jsonlite_parser_suspend(NULL);
    XCTAssertTrue(result == jsonlite_result_invalid_argument, @"Bad result");
    
    result = jsonlite_parser_suspend(p);
    XCTAssertTrue(result == jsonlite_result_not_allowed, @"Bad result");
    
    result = jsonlite_parser_tokenize(p, json1, sizeof(json1));
    XCTAssertTrue(result == jsonlite_result_suspended, @"Bad result");
    
    result = jsonlite_parser_terminate(p, jsonlite_result_invalid_argument);
    XCTAssertTrue(result == jsonlite_result_not_allowed, @"Bad result");
    
    result = jsonlite_result_suspended;
    while (result == jsonlite_result_suspended) {
        result = jsonlite_parser_resume(p);
    }
    
    XCTAssertTrue(result == jsonlite_result_ok, @"Bad result");
    
    result = jsonlite_parser_suspend(p);
    XCTAssertTrue(result == jsonlite_result_not_allowed, @"Bad result");
    
    jsonlite_parser_release(p);
}

- (void)testSuspendResumeObjC {
    char json1[] = "{\"key\" : 12345, \"obj\": {}, \"array\":[null, true, false, \"string\"]}";
    JsonLiteParser *parser = [JsonLiteParser parserWithDepth:32];
    ParseSuspender *del = [[ParseSuspender alloc] init];
    parser.delegate = del;
    
    NSError *error = [parser suspend];
    XCTAssertTrue([error code] == JsonLiteCodeNotAllowed, @"Incorrect error");
    
    error = [parser resume];
    XCTAssertTrue([error code] == JsonLiteCodeNotAllowed, @"Incorrect error");
    
    BOOL run = ![parser parse:[NSData dataWithBytes:json1 length:sizeof(json1) - 1]];
    while (run) {
        run = ![parser resume] && parser.parseError == nil;
    }

    [del release];
}

- (void)testCFHashCollection {
    NSString *json = @"{\"test4\": null, \"10D789E\" : null}";
    NSData *data = [json dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dic = [JsonLiteObjC objectFromData:data depth:8];
    id obj1 = [dic objectForKey:@"test4"];
    id obj2 = [dic objectForKey:@"10D789E"];
    XCTAssertEqualObjects(obj1, obj2, @"");
}

- (void)testKeyDepthCheck {
    char json[] = "{\"obj\": {\"obj\": {\"obj\": {}}}}";
    jsonlite_parser p = jsonlite_parser_init(2);
    
    jsonlite_result result = jsonlite_parser_tokenize(p, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_depth_limit, @"Incorrect result");
    
    jsonlite_parser_release(p);
}

- (void)testArrayValueDepthCheck {
    char json[] = "[1, [1, [1, [1, [0]]]]]";
    jsonlite_parser p = jsonlite_parser_init(2);
    
    jsonlite_result result = jsonlite_parser_tokenize(p, json, sizeof(json));
    XCTAssertTrue(result == jsonlite_result_depth_limit, @"Incorrect result");
    
    jsonlite_parser_release(p);
}


- (void)testMaxLong {
    NSNumber *number = [NSNumber numberWithLongLong:LONG_MAX];
    JsonLiteSerializer *ser = [JsonLiteSerializer serializer];
    NSData *data = [ser serializeObject:@[number]];
    NSArray *array = [JsonLiteObjC objectFromData:data depth:16];
    XCTAssertEqualObjects(number, [array lastObject], @"Objects are not equal");
}

- (void)testVersion {
    NSString *version = [JsonLiteObjC version];
    XCTAssertEqualObjects(version, @"1.1.1", @"Incorrect version");
}

@end
