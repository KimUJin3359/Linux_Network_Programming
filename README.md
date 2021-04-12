# Linux_Network_Programming

### Network 기본
#### 인터넷 원리
- Network
  - Net : 그물
  - 노드와 링크로 구성된 데이터 교환망
    - 노드 : 컴퓨팅 장치들
    - 링크 : 연결
- IP 주소
  - 노드들의 고유 ID
  - IPv4, IPv6
- 공유기(라우터)의 사용
  - PC끼리 연결하지 않고, 공유기를 거쳐 연결
  - 연결 PC가 늘어나도, 사용하는 랜카드는 PC당 1개
- 케이블
  - STP Cable
    - UTP : Unshieleded Twisted-Pair
    - STP : Shielded Twisted-Pair
    - EMI 방지를 위한 호일을 한번 더 감은 고급 케이블
  - UTP Cable
    - 다이렉트 케이블
    - 크로스 케이블
    - 잘못 사용하면 통신이 안됨
    - Auto MDI : 아무 케이블만 꽂아도, 잘 동작하는 기술(임베디드 보드들은 미지원)
    - PC, PC 등 동일 기종 간에는 크로스 케이블
    - PC와 Router 등 이기종 간에는 다이렉트 케이블
  - 동축케이블
  - 광(섬유)케이블
    - 빛 굴절을 이용하요, 선이 꺾이더라도 직진성으로 전달
  - 전송 스펙
    - CAT5e : 1Gbps, 100MHz 대역폭
    - CAT6 : 1Gbps, 250MHz 대역폭
    - CAT7 : 10Gbps, 600MHz 대역폭

#### 서버와 DNS

![그림](https://user-images.githubusercontent.com/50474972/114398417-bcf0b700-9bda-11eb-8692-59c68114fe30.JPG)

- 인터넷의 발전
  - 어떠한 한 공유폴더를 공유하여 사용했음
    - 해당 공유폴더를 가지고 있는 컴퓨터가 종료하면, 다른 작업을 하지 못함
    - 공용 컴퓨터(서버, 24시간 계속 켜두는 컴퓨터)를 둬서 위의 문제를 해결
- 인터넷의 창시자
  - 팀 버너스리
  - www(world wide web) : 가장 거대한 네트워크
  - w3c : www의 협회장
  - HTML 문서의 규격을 만듬
  - HTML 문서를 읽어내는 것 : 웹 브라우저
  - 해당 서버에 접속하려면 서버의 IP주소를 입력
- 렌더링
  - 소스코드(java script)를 가져와 빌드하여 보여주는 것
  - 브라우저를 렌더링 머신이라고도 함
- DNS(Domain Name System)
  - 사람이 이해하기 쉬운 도메인 주소를 IP로 변환
  - 인터넷상의 전화번호부  

#### 네트워크 분류
- 규모에 따른 분류
  - LAN(Local Area Network)
    - 랜카드 : 근거리 통신망을 위한 네트워크 카드
    - 랜케이블 : 근거리 통신망 용 케이블
    - 집안 / 사무실 / 소규모 공장 수준
    - Ethernet 방식으로 사용하는 소규모 네트워크
  - WAN(Wild Area Network)
    - LAN보다 넓은 네트워크를 의미
  - 인터넷
    - 가장 거대한 네트워크
    - ISP(Internet Service Provider) 업체 신청하여, 전용선 + IP를 사용
- Cell : 무선 이동통신을 위해 하나의 기지국이 포괄하는 범위
- Cellular
  - 한 지역을 여러개의 셀로 분할하여 운용하는 통신 방식
  - 주파수를 알뜰하게 쓰기 위함
  - 주파수 대역 : 사람의 수에 따라 대역폭이 많이 필요함
- IoT
  - 무선 네트워크가 Default 통신 방식
  - 네트워크 규모, 특징에 따라 필요한 속도, 가격 존재
    - 무선 LAN : Wifi/BLE
    - 실외 : Cellular - LTE/5G
    - 무선 WAN(LowerPowerWAN) : 낮은 전력으로 넓은 범위에서 쓸 수 있는 방법

### 프로토콜의 이해
- 프로토콜 : 통신의 약속
  - 통신의 두 주체가 같은 프로토콜을 쓴다면, 약속된 규칙으로 통신이 가능
  - HW : 장비 규칙, 신호 전달 속도
  - Format : 신호의 형태
  - Sequence : Handshake 방식, 신호 전달 순서
  - SW 동작 : 오류 검출을 위한 행동
- 프로토콜을 이해해야 하는 이유
  - 완벽한 통신 Application 제작 가능
  - 통신 App을 위한 Library 제작 가능
  - 프로토콜 내용대로 수행하는 Server 구축 가능

#### TCP/IP
- IP(Internet Protocol)
  - 송신 호스트와 수신 호스트가 정보를 주고받는데 사용하는 규약
  - 패킷 혹은 데이터그램이라고 하는 덩어리로 나뉘어 전송
  - 비 연결성
    - 패킷을 받을 대상이 없거나 해당 도착지의 주소가 불능 상태여도 패킷을 전송
  - 비 신뢰성
    - 통신 도중 패킷이 사라질 수 있음
    - 패킷이 순서대로 도착하지 않을 수 있음
  - IP Address : 인터넷 상에 있는 컴퓨터의 고유한 주소

```
이더넷(LAN) : CSMA/CD 사용, MAC주소를 통한 정보 공유
인터넷 : TCP/IP 사용, IP Address를 통한 정보 공유
TCP/IP 사용 시 라우터가 길을 미리 세팅(라우팅 : MST)
```

- TCP(Transmission Control Protocol)
  - 전송 제어 프로토콜
  - IP의 핵심 프로토콜 중 하나
  - 연결 지향(3way handshake)
  - 데이터 전달 보증
  - 순서 보증
  - 신뢰할 수 있는 프로토콜
- UDP(User Datagram Protocol)
  - 데이터 전달, 순서 보장 X
  - 속도가 빠름

#### Ethernet Cable
- 전송속도(bit rate)
  - bit per second(bps)
  - 초당 몇 bit를 전송하는지

  | UART 통신 | USB 통신 |
  | --- | --- |
  | 0.01MBps | 400MBps |
  | 느리다 | 빠름 |

- USB 통신을 쓰지 않는 이유
  - 엔지니어에게 USB는 어려움(개발시간, spec up)
  - 전력
- 대역폭
  - 주파수
    - 최대와 최소 주파수의 폭
    - 폭이 넓을수록 정보를 한꺼번에 실을 수 있는 양이 커짐
  - 통신
    - 한번에 데이터를 전송할 수 있는 양



