# nginx v2

Creating an HTTP/1.0 server in C.  
The goal is to learn about network programming, handling user input, (multi threading ?), ...

## Try it

Compile and run it's as simple as that.  

```bash
make
./output [port number]
```

## State of the project

The tcp part of the project should be more or less finished.  
I am currently implementing parsers to parse the requests.  
Then I should simply have to create responses and the server should be (except for every method other than GET) up and running.  

