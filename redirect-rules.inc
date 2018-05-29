
if ($scheme = http) { rewrite ^/(.*) https://$host/$1 permanent; }
if ($request_uri !~ "^/wp-"){return 301 https://new-domain.com ; }


rewrite "^/\d{4}/\d{1,2}/\d{1,2}/([^/]+)/?$" /$1 permanent;


#redirecting all traffic to Google
return 301 http://google.com;

#Redirecting all the traffic to another site (google.com for example) but keeping the Dashboard and our podcasts feed intact
if ($request_uri !~ "^/(wp-|feed/podcast)"){return 301 http://google.com ; }


Basic-Auth for the WP Dashboard

location ~* (wp-login)\.php$ {
            auth_basic "Administrator Login";
            auth_basic_user_file /etc/nginx/conf.d/.htpasswd;
            fastcgi_pass   unix:/var/run/php5-fpm.sock ;
            fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
            include        fastcgi_params;
}

Simulating Conditions