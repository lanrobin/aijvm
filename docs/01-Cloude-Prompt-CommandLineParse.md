Please implement a light weight command line parse so I can run the aijvm as following:
aijvm --bj /usr/lib/jvm/java-25-openjdk-amd64/jmods --cp ./classes MainJavaClass

where:
--bj is the OpenJdk jmod folders contains the precompiled java runtime class and compress in jmod files.

--cp is the customer provided classes folder

MainJavaClass is the java class that customer want to run which has the public static void main(String[] args) method.

The pasred variable must store in a c++ object for later use, for example create JVM engine. Please use <filesystem> and <string_view> and also store the unrecognized the parameters in a map for future use.