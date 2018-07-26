
**Redirect all the traffic to HTTPS.**

`if ($scheme = http) { rewrite ^/(.*) https://$host/$1 permanent; }`

---
**Remove the date (year/month/day) format.**

`rewrite "^/\d{4}/\d{1,2}/\d{1,2}/([^/]+)/?$" /$1 permanent;`

---
**redirecting all traffic to Google**

`return 301 http://google.com;`

---
*Redirecting all the traffic to another site (google.com for example) but keeping the Dashboard and our podcasts feed intact*

`if ($request_uri !~ "^/(wp-|feed/podcast)"){return 301 http://google.com ; }`

---
**Basic-Auth for the WP Dashboard**

`location ~* (wp-login)\.php$ {
            auth_basic "Administrator Login";
            auth_basic_user_file /etc/nginx/conf.d/.htpasswd;
            fastcgi_pass   unix:/var/run/php5-fpm.sock ;
            fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
            include        fastcgi_params;
}`

---
**Simulating Conditions**

In this case, we will redirect all the traffic to HTTP but some special URLS to HTTPS such as /cart/checkout/wp-content/

`set $redirect_http 0;
if($scheme = 'https'){set $reditect_http 1;}
if($request_uri !~ "/(checkout|cart|wp-content)"){set $redirect_http 1$redirect_http;}
if($redirect_http = 11){rewrite ^/(.+) https://$host/$1 permanent;}`
