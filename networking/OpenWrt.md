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
* Чтобы зафиксировать названия интерфейсов VPN:
  - указать `tun0` в `/etc/sing-box/config.json`
  - указать `dev tun1` в `/etc/openvpn/client.conf`
  - ```
    service sing-box stop
    service openvpn stop
    service sing-box start
    service openvpn start
    ```

# Дополнительно
* Установить dynamic dns и разрешить ssh-доступ извне с определённого IP

# Перезагрузка
```
service network restart
service getdomains restart
service firewall restart
```

# Проверки
```
curl -4 ifconfig.me
curl -4 --interface tun0 ifconfig.me
curl -4 --interface tun1 ifconfig.me 
nft list ruleset
ip rule list
```

# Другие варианты
* https://antizapret.prostovpn.org/tech.html (интересный вариант split tunnel через подмену DNS)
* https://github.com/gSpotx2f/ruantiblock_openwrt

# МТС Интернет
* PON-розетку перевести в Bridged
* Поставить галку Port Mapping LAN_1
* Если проблемы с получением IP-адреса на WAN (DHCP), то:
  - воткнуть в компьютер, получить IP-адрес
  - прописать MAC-адрес компьютера на WAN (устройство br-wan)
  - прописать полученный на компьютере IP-адрес как static на WAN
  - должен заработать WAN
  - вернуть DHCP на WAN
* Если после перезагрузки роутера, он не получает IP-адрес на WAN, то можно поставить static, а потом сразу же вернуть DHCP ("передёрнуть").

## Доступ к админке PON-розетки
В режиме бриджа админка PON-розетки становится недоступна, т.к. перестаёт работать как DHCP-сервер.

Чтобы это решить, в `/etc/config/network` добавляем ещё один интерфейс на br-wan со статическим IP-адресом в локальной подсети розетки:
```
config interface 'wanpon'
        option device 'br-wan'
        option proto 'static'
        option ipaddr '192.168.10.33'
        option netmask '255.255.255.0'
```

## Прочее
Можно сбросить PON-розетку через отключение питания (10+ секунд), тогда на розетке активируется дефолтный режим роутера.

Если не помогло, то звонить в поддержку 8 495 636 06 36, чтобы они дистанционно перезагрузили PON-розетку.
