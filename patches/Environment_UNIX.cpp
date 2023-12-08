diff --git a/Foundation/src/Environment_UNIX.cpp b/Foundation/src/Environment_UNIX.cpp
index eb9042b9c..880d21aca 100644
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
@@ -197,7 +200,28 @@ void EnvironmentImpl::nodeIdImpl(NodeId& id)
 #include <fcntl.h>
 #include <cstdio>
 
-
+struct   ifreq {
+#define  IFNAMSIZ  16
+    char    ifr_name[IFNAMSIZ];
+    union {
+    struct  sockaddr ifru_addr;
+    struct  sockaddr ifru_dstaddr;
+    struct  sockaddr ifru_broadaddr;
+    struct sockaddr ifru_hwaddr;
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
+ZZ
 namespace Poco {
 
 
@@ -237,7 +261,11 @@ void EnvironmentImpl::nodeIdImpl(NodeId& id)
 	{
 		buf = new char[len];
 		ifc.ifc_len = len;
+		#ifdef __MVS__
+		ifc.ifcu_buf = buf;
+		#else			
 		ifc.ifc_buf = buf;
+		#endif
 		if (::ioctl(sock, SIOCGIFCONF, &ifc) < 0)
 		{
 			if (errno != EINVAL || lastlen != 0)
@@ -262,7 +290,7 @@ void EnvironmentImpl::nodeIdImpl(NodeId& id)
 		int rc = ioctl(sock, SIOCGIFHWADDR, ifr);
 		if (rc != -1)
 		{
-			const struct sockaddr* sa = reinterpret_cast<const struct sockaddr*>(&ifr->ifr_hwaddr);
+			const struct sockaddr* sa = reinterpret_cast<const struct sockaddr*>(&ifr->ifru_hwaddr);
 			if (sa->sa_family == ARPHRD_ETHER)
 			{
 				std::memcpy(&id, sa->sa_data, sizeof(id));
