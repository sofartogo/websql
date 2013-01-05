AUX_SOURCE_DIRECTORY(nedmalloc NEDMALLOC)

SET(WEBSQL_SRC
    evhttpx/evhttpx.c
    evhttpx/evthr/evthr.c
    evhttpx/httpparser/http-parser.c
    uuid/arc4random.c
    uuid/uuid.c
    cJSON.c
    log.c
    rbtree.c
    splaytree.c
    websql.c
    )

ADD_EXECUTABLE(websql ${WEBSQL_SRC})

# LINK_DIRECTORIES(${WEBSQL_EXTERNAL_LIBS})

TARGET_LINK_LIBRARIES(websql ${WEBSQL_EXTERNAL_LIBS} pthread m)
