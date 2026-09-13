# QtLocationRelayVdvGnss

Program to get GNSS location from a Windows computer and to relay it over UDP to VDV301tester, using fake GnssLocationService.
NMEA messages through COM port are also supported.

Needs to be built using MSVC to support winrt API.

## Changelog
- 20260913_1156
  - MapaVyresleni
    - added dragmap
    
- 20260906_2034
  - ui reorder
  - fixed port reopen

- 20260906_1805
  - serial port demo

- 20260906_1654
  - error log now appends the text

- 20260906_1619
  - added UdpSender

- 20260905_2205
  - first commit