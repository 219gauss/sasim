
wifi连接成功时，wifi图标会出现一个×，而且会显示connect，no Internet

原因：wifi连接成功后会进行验证，如果是要登录需要验证的WiFi，则会弹出验证页面，如果不是，则会登录google服务器请求204验证码，
如果返回204则表示网络可以正常连接，此时WiFi图标x会消失并且WiFi显示Connected。由于国内无法访问Google网站，所以默认会存在此问题。


frameworks\base\services\core\java\com\android\server\connectivity\NetworkMonitor.java

--- a/Android/frameworks/base/services/core/java/com/android/server/connectivity/NetworkMonitor.java
+++ b/Android/frameworks/base/services/core/java/com/android/server/connectivity/NetworkMonitor.java
@@ -86,10 +86,10 @@ public class NetworkMonitor extends StateMachine {
     // Default configuration values for captive portal detection probes.
     // TODO: append a random length parameter to the default HTTPS url.
     // TODO: randomize browser version ids in the default User-Agent String.
-    private static final String DEFAULT_HTTPS_URL     = "https://www.google.com/generate_204";
+    private static final String DEFAULT_HTTPS_URL     = "http://connect.rom.miui.com/generate_204";
     private static final String DEFAULT_HTTP_URL      =
-            "http://connectivitycheck.gstatic.com/generate_204";
-    private static final String DEFAULT_FALLBACK_URL  = "http://www.google.com/gen_204";
+            "http://connect.rom.miui.com/generate_204";
+    private static final String DEFAULT_FALLBACK_URL  = "http://connect.rom.miui.com/generate_204";
     private static final String DEFAULT_USER_AGENT    = "Mozilla/5.0 (X11; Linux x86_64) "
                                                       + "AppleWebKit/537.36 (KHTML, like Gecko) "
                                                       + "Chrome/52.0.2743.82 Safari/537.36";


