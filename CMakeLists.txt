cmake_minimum_required(VERSION 3.10)

project(WikiVoteQueryProcessing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(wiki_vote_query
    src/main.cpp
)

