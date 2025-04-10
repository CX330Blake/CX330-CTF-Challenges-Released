FROM php:8.1-apache

COPY . /var/www/html/
COPY flag.txt /flag.txt

RUN a2enmod rewrite

EXPOSE 80

