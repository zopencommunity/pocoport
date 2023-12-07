diff --git a/Foundation/src/Environment_UNIX.cpp b/Foundation/src/Environment_UNIX.cpp
index eb9042b9c..b0fb6fa9f 100644
--- a/Foundation/src/Environment_UNIX.cpp
+++ b/Foundation/src/Environment_UNIX.cpp
@@ -27,6 +27,8 @@
 #endif
 
 
+
+
 namespace Poco {
 
 
@@ -185,7 +187,8 @@ void EnvironmentImpl::nodeIdImpl(NodeId& id)
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <net/if.h>
-#ifndef __CYGWIN__
+#ifndef __CYGWIN__ 
+#ifndef __MVS__
 #include <net/if_arp.h>
 #else // workaround for Cygwin, which does not have if_arp.h
 #define ARPHRD_ETHER 1 /* Ethernet 10Mbps */
@@ -197,6 +200,26 @@ void EnvironmentImpl::nodeIdImpl(NodeId& id)
 #include <fcntl.h>
 #include <cstdio>
 
+struct   ifreq {
+#define  IFNAMSIZ  16
+    char    ifr_name[IFNAMSIZ];
+    union {
+    struct  sockaddr ifru_addr;
+    struct  sockaddr ifru_dstaddr;
+    struct  sockaddr ifru_broadaddr;
+    short   ifru_flags;
+    int     ifru_metric;
+    caddr_t ifru_data;
+    } ifr_ifru;
+};
+
+struct   ifconf {
+    int  ifc_len;
+    union {
+    caddr_t   ifcu_buf;
+    struct    ifreq *ifcu_req;
+    } ifc_ifcu;
+};
 
 namespace Poco {
 
