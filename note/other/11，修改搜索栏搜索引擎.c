android默认的搜索栏的搜索引擎是谷歌，修改为百度


--- a/Android/packages/apps/QuickSearchBox/src/com/android/quicksearchbox/google/GoogleSearch.java
+++ b/Android/packages/apps/QuickSearchBox/src/com/android/quicksearchbox/google/GoogleSearch.java
@@ -134,18 +134,20 @@ public class GoogleSearch extends Activity {
         }
 
         try {
-            String query_code = getResources().getString(R.string.query_code);
+            //String query_code = getResources().getString(R.string.query_code);
             String searchUri = "";
             if (getResources().getBoolean(
                         R.bool.config_regional_search_use_clientid)) {
-                searchUri = mSearchDomainHelper.getSearchBaseUrl()
-                    + "&source=android-" + source
-                    + "&client=" + getResources().getString(R.string.google_clientidbase_ms)
-                    + query_code + URLEncoder.encode(query, "UTF-8");
+                // searchUri = mSearchDomainHelper.getSearchBaseUrl()
+                //     + "&source=android-" + source
+                //     + "&client=" + getResources().getString(R.string.google_clientidbase_ms)
+                //     + query_code + URLEncoder.encode(query, "UTF-8");
+                searchUri = "http://www.baidu.com/s?lm=0&si=&rn=10&ie=gb2312&ct=0&wd=" + URLEncoder.e
             } else {
-               searchUri = mSearchDomainHelper.getSearchBaseUrl()
-                    + "&source=android-" + source
-                    + query_code + URLEncoder.encode(query, "UTF-8");
+               // searchUri = mSearchDomainHelper.getSearchBaseUrl()
+               //      + "&source=android-" + source
+               //      + query_code + URLEncoder.encode(query, "UTF-8");
+                searchUri = "http://www.baidu.com/s?lm=0&si=&rn=10&ie=gb2312&ct=0&wd=" + URLEncoder.e
             }
             Log.i(TAG, " searchUri : " + searchUri);
             Intent launchUriIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(searchUri));
