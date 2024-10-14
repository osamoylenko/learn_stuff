# Настройка VPN split tunnel по доменам
* https://t.me/amnezia_vpn/204428/261586
* https://habr.com/ru/articles/767464/
* https://4pda.to/forum/index.php?showtopic=1085698

# Настройка дополнительного VPN
* https://itdog.info/nastrojka-klienta-openvpn-na-openwrt/
* `/etc/iproute2/rt_tables`
* `/etc/config/network`
* скопировать `/etc/hotplug.d/iface/30-vpnroute`
* `/etc/config/firewall`
* `/etc/init.d/getdomains`

# Проверки
```
curl -4 ifconfig.me
curl -4 --interface tun0 ifconfig.me
curl -4 --interface tun1 ifconfig.me 
nft list ruleset
ip rule list
```

# Другой интересный вариант split tunnel
https://antizapret.prostovpn.org/tech.html