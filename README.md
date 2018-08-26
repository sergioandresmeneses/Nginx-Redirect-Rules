# Table of Content 

 1. Redirecting all the traffic to HTTPS
 2. Remove the date (year/month/day) format
 3. Redirecting all traffic to Google or another site
 4. Basic-Auth for the WP Dashboard
 
 
---
## Redirect query requests
For example, the URL http://mydomain/?page_id=197 to http://mydomain/contact

`if ($query_string ~ "page_id=197") {rewrite "^/$" http://mydomain/contact? permanent;}`

---
## Redirect all the traffic to HTTPS

`if ($scheme = http) { rewrite ^/(.*) https://$host/$1 permanent; }`

---
## Force WWW on all your pages

 `if ($host !~ "^www.") { return 301 $scheme://www.$host$request_uri; }`

---
## Remove the date (year/month/day) format

`rewrite "^/\d{4}/\d{1,2}/\d{1,2}/([^/]+)/?$" /$1 permanent;`

---
## Redirecting all traffic to Google

`return 301 http://google.com;`

> Redirecting all the traffic to another site (google.com for example) but keeping the Dashboard and our podcasts feed intact

`if ($request_uri !~ "^/(wp-|feed/podcast)"){return 301 http://google.com ; }`

---
## Basic-Auth for the WP Dashboard


 - For files:
```
location ~* (wp-login)\.php$ {
            auth_basic "Administrator Login";
            auth_basic_user_file /etc/nginx/conf.d/.htpasswd;
            fastcgi_pass   unix:/var/run/php5-fpm.sock ;
            fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
            include        fastcgi_params;
}
```

 - For directories:
 
```
location /path/ {
            auth_basic "Administrator Login";
            auth_basic_user_file /etc/nginx/conf.d/.htpasswd;
            
}
```

 > If you want to see PHP files, directly we recommend you to add the same PHP directives shown in the previous block of code.
 

 - For the whole site:

```
location / {
            auth_basic "Administrator Login";
            auth_basic_user_file /etc/nginx/conf.d/.htpasswd;
            index index.html index.htm index.php;
            if (!-e $request_filename) { rewrite . /index.php last; }
            
}
```
 
More info about the generation of the .htpasswd and this process in the [official Nginx Documentation](https://docs.nginx.com/nginx/admin-guide/security-controls/configuring-http-basic-authentication/)

---
## Simulating Conditions

In this case, we will redirect all the traffic to HTTP but some special URLS to HTTPS such as /cart/checkout/wp-content/

```
set $redirect_http 0;
if($scheme = 'https'){set $reditect_http 1;}
if($request_uri !~ "/(checkout|cart|wp-content)"){set $redirect_http 1$redirect_http;}
if($redirect_http = 11){rewrite ^/(.+) https://$host/$1 permanent;}
```
