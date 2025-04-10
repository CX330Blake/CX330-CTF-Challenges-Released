FROM php:8.1-apache

COPY . /var/www/html/
COPY flag.txt /flag.txt

RUN mkdir -p /var/www/html/log && \
    chown -R www-data:www-data /var/www/html/log && \
    chmod -R 755 /var/www/html/log

RUN a2enmod rewrite

EXPOSE 80

