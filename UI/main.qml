import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15


Window {
    id:root
    width: 1500
    height: 1000
    visible: true
    title: qsTr("Map")
    color: "#f5f5f5"
    property bool flag: false

////////////////////////////////////////////// line_1 //////////////////////////////////////////////
    // tajrish
    MyButton {
        id: tajrish
        width: 53
        height: 53
        x: 727
        y: 10
        z: 2
        color: "red"
        station.text: "Tajrish"
    }
    Label {
        x: 685
        y: 45
        z: 1
        Text {
            id: taj
            text: qsTr("Tajrish")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:tajrec
        x: 749
        y: 50
        z: 0
        width: 8
        height: 50
        radius: 5
        color : "red"
        opacity: 0.75
    }


    // geh
    MyButton {
        id: gheytariyeh
        width: 40
        height: 40
        x: 733.5
        y: 85
        z: 2
        color: "red"
        station.text: "Gheytariyeh"
    }
    Label {
        x: 665
        y: 93
        Text {
            id: geh
            text: qsTr("Gheytariyeh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:ctod
        x: 749
        y: 120
        z: 0
        width: 8
        height: 50
        radius: 5
        color : "red"
        opacity: 0.75
    }

    // gol
    MyButton {
        id: c
        width: 40
        height: 40
        x: 733.5
        y: 150
        z: 2
        color: "red"
        station.text: "Gholhak"
    }
    Label {
        x: 683
        y: 160
        Text {
            id: gol
            text: qsTr("Gholhak")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:ctode
        x: 749
        y: 180
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
        opacity: 0.75
    }

    // mir
    MyButton {
        id: d
        width: 40
        height: 40
        x: 733.5
        y: 215
        z: 2
        color: "red"
        station.text: "Mirdamad"
    }
    Label {
        x: 673
        y: 210
        Text {
            id: mir
            text: qsTr("Mirdamad")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:ctoe
        x: 749
        y: 240
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
        opacity: 0.75
    }

    // Shahid Haghani
    MyButton {
        id: e
        width: 40
        height: 40
        x: 733.5
        y: 280
        z: 2
        color: "red"
        station.text: "Shahid Haghani"
    }
    Rectangle {
        id:cttoe
        x: 749
        y: 300
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }
    Label {
        x: 780
        y: 292
        Text {
            id: haqani
            text: qsTr("Shahid Haghani")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }

    //
    MyButton {
        id: f
        width: 40
        height: 40
        x: 733.5
        y: 345
        z: 2
        color: "red"
        station.text: "Shahid Beheshti"
    }
    Label {
        x: 780
        y: 340
        Text {
            id: beheshti
            text: qsTr("Shahid Beheshti")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:coe
        x: 749
        y: 370
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    // Shahid Mofatteh
    MyButton {
        id: g
        width: 40
        height: 40
        x: 733.5
        y: 410
        z:  2
        color: "red"
        station.text: "Shahid Mofatteh"
    }
    Label {
        x: 780
        y: 420
        Text {
            id: mofateh
            text: qsTr("Shahid Mofatteh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:co
        x: 749
        y: 440
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    // Haftom-e Tir
    MyButton {
        id: h
        width: 40
        height: 40
        x: 733.5
        y: 475
        z: 2
        color: "red"
        station.text: "Haftom-e Tir"
    }
    Label {
        x: 780
        y: 475
        Text {
            id: tir
            text: qsTr("Haftom-e Tir")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cox
        x: 749
        y: 500
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    // Taleghani
    MyButton {
        id: i
        width: 40
        height: 40
        x: 733.5
        y: 540
        z: 2
        color: "red"
        station.text: "Taleghani"
    }
    Label {
        x: 780
        y: 535
        Text {
            id: taleghani
            text: qsTr("Taleghani")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:ciox
        x: 749
        y: 560
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    // Darvazeh Dowlat
    MyButton {
        id: j
        width: 40
        height: 40
        x: 733.5
        y: 605
        z: 2
        color: "red"
        station.text: "Darvazeh Dowlat"
    }
    Label {
        x: 780
        y: 637
        Text {
            id: dolat
            text: qsTr("Darvazeh Dowlat")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cx
        x: 749
        y: 630
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    // Panzdah-e Khordad
    MyButton {
        id: k
        width: 40
        height: 40
        x: 733.5
        y: 670
        z: 2
        color: "red"
        station.text: "Panzdah-e Khordad"
    }
    Label {
        x: 780
        y: 679
        Text {
            id: khordad
            text: qsTr("Panzdah-e Khordad")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cix
        x: 749
        y: 690
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    // Shoush
    MyButton {
        id: l
        width: 40
        height: 40
        x: 733.5
        y: 735
        z: 2
        color: "red"
        station.text: "Shoush"
    }
    Rectangle {
        id:copx
        x: 749
        y: 760
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }
    Label {
        x: 780
        y: 744
        Text {
            id: shoush
            text: qsTr("Shoush")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }

    // Jonoub Terminal
    MyButton {
        id: m
        width: 40
        height: 40
        x: 733.5
        y: 800
        z: 2
        color: "red"
        station.text: "Jonoub Terminal"
    }
    Label {
        x: 780
        y: 810
        Text {
            id: jonob
            text: qsTr("Jonoub Terminal")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cupx
        x: 749
        y: 820
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    // Shahr-e Rey
    MyButton {
        id: n
        width: 40
        height: 40
        x: 733.5
        y: 865
        z: 2
        color: "red"
        station.text: "Shahr-e Rey"
    }
    Label {
        x: 780
        y: 875
        Text {
            id: rey
            text: qsTr("Shahr-e Rey")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cjx
        x: 749
        y: 890
        z:  0
        width: 8
        height: 50
        radius: 5
        color : "red"
    }

    //  Kahrizak
    MyButton {
        id: o
        width: 53
        height: 53
        x: 727
        y: 935
        z: 2
        color: "red"
        station.text: "Kahrizak"
    }
    Label {
        x: 792
        y: 950
        Text {
            id: kah
            text: qsTr("Kahrizak")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }

////////////////////////////////////////////// line_3 //////////////////////////////////////////////

    // Gha'em
    MyButton {
        id: p
        width: 53
        height: 53
        x: 1435
        y: 270.5
        z: 2
        color: "#0047AB"
        station.text: "Gha'em"
    }
    Label {
        x: 1395
        y: 325
        Text {
            id: ghaem
            text: qsTr("Gha'em")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cxq
        x: 1320
        y: 295
        z:  0
        width: 130
        height: 8
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    // Aghdasiyeh
    MyButton {
        id: q
        width: 40
        height: 40
        x: 1300
        y: 280
        z: 2
        color: "#0047AB"
        station.text: "Aghdasiyeh"
    }
    Label {
        x: 1290
        y: 325
        Text {
            id: aghdasiyeh
            text: qsTr("Aghdasiyeh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cxiq
        x: 1200
        y: 295
        z:  0
        width: 130
        height: 8
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    // Shahid Zeynoddin
    MyButton {
        id: r
        width: 40
        height: 40
        x: 1165
        y: 280
        z: 2
        color: "#0047AB"
        station.text: "Shahid Zeynoddin"
    }
    Label {
        x: 1140
        y: 325
        Text {
            id: zeynoddin
            text: qsTr("Shahid Zeynoddin")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cxiqq
        x: 1050
        y: 295
        z:  0
        width: 130
        height: 8
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    // Shahid Ghodousi
    MyButton {
        id: s
        width: 40
        height: 40
        x: 1030
        y: 280
        z: 2
        color: "#0047AB"
        station.text: "Shahid Ghodousi"
    }
    Label {
        x: 1000
        y: 325
        Text {
            id: ghodousi
            text: qsTr("Shahid Ghodousi")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:ciqq
        x: 900
        y: 295
        z:  0
        width: 150
        height: 8
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }
    Rectangle {
        id:ciq
        x: 897
        y: 295
        z:  0
        width: 8
        height: 80
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }
    Rectangle {
        id:cioq
        x: 770
        y: 360
        z:  0
        width: 120
        height: 8
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //  Sohrevardi
    MyButton {
        id: t
        width: 40
        height: 40
        x: 881.75
        y: 345
        z: 2
        color: "#0047AB"
        station.text: "Sohrevardi"
    }
    Label {
        x: 875
        y: 390
        Text {
            id: sohrevardi
            text: qsTr("Sohrevardi")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:ciopq
        x: 620
        y: 360
        z:  0
        width: 120
        height: 8
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //Merza-ye Shirazi
    MyButton {
        id: u
        width: 40
        height: 40
        x: 585.25
        y: 345
        z: 2
        color: "#0047AB"
        station.text: "Merza-ye Shirazi"
    }
    Label {
        x: 585
        y: 325
        Text {
            id: shirazi
            text: qsTr("Merza-ye Shirazi")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cipq
        x: 601
        y: 360
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    // Meydan-e Jahad
    MyButton {
        id: v
        width: 40
        height: 40
        x: 585.25
        y: 410
        z: 2
        color: "#0047AB"
        station.text: "Meydan-e Jahad"
    }
    Label {
        x: 490
        y: 420
        z:1
        Text {
            id: jahad
            text: qsTr("Meydan-e Jahad")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cpq
        x: 601
        y: 410
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //  Meydan-e Hazrat-e ValiAsr
    MyButton {
        id: w
        width: 40
        height: 40
        x: 585.25
        y: 475
        z: 2
        color: "#0047AB"
        station.text: "Meydan-e Hazrat-e ValiAsr"
    }
    Label {
        x: 440
        y: 470
        z:1
        Text {
            id: valiasr
            text: qsTr("Meydan-e Hazrat-e ValiAsr")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cqpq
        x: 601
        y: 475
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //   Teatr-e Shahr
    MyButton {
        id: x
        width: 40
        height: 40
        x: 585.25
        y: 540
        z: 2
        color: "#0047AB"
        station.text: "Teatr-e Shahr"
    }
    Label {
        x: 525
        y: 520
        z:1
        Text {
            id: shahr
            text: qsTr("Teatr-e Shahr")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cqqpq
        x: 601
        y: 540
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //  Moniriyeh
    MyButton {
        id: y
        width: 40
        height: 40
        x: 585.25
        y: 605
        z: 2
        color: "#0047AB"
        station.text: "Moniriyeh"
    }
    Label {
        x: 527
        y: 620
        z:1
        Text {
            id: moniriyeh
            text: qsTr("Moniriyeh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cqq
        x: 601
        y: 605
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //  Mahdiyeh
    MyButton {
        id: z
        width: 40
        height: 40
        x: 585.25
        y: 670
        z: 2
        color: "#0047AB"
        station.text: "Mahdiyeh"
    }
    Label {
        x: 527
        y: 680
        z:1
        Text {
            id: mahdiyeh
            text: qsTr("Mahdiyeh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qpq
        x: 601
        y: 670
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    // Rahahan
    MyButton {
        id: ab
        width: 40
        height: 40
        x: 585.25
        y: 735
        z: 2
        color: "#0047AB"
        station.text: "Rahahan"
    }
    Label {
        x: 530
        y: 747
        z:1
        Text {
            id: rahahan
            text: qsTr("Rahahan")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qpsq
        x: 601
        y: 735
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //Javadiyeh
    MyButton {
        id: cd
        width: 40
        height: 40
        x: 585.25
        y: 800
        z: 2
        color: "#0047AB"
        station.text: "Javadiyeh"
    }
    Label {
        x: 528
        y: 810
        z:1
        Text {
            id: javadiyeh
            text: qsTr("Javadiyeh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cqoq
        x: 601
        y: 800
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //  Zamzam
    MyButton {
        id: ef
        width: 40
        height: 40
        x: 585.25
        y: 865
        z: 2
        color: "#0047AB"
        station.text: "Zamzam"
    }
    Label {
        x: 534
        y: 875
        z:1
        Text {
            id: zamzam
            text: qsTr("Zamzam")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cqpqq
        x: 601
        y: 475
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

    //  Azadegan
    MyButton {
        id: gh
        width: 53
        height: 53
        x: 580
        y: 935
        z: 2
        color: "#0047AB"
        station.text: "Azadegan"
    }
    Label {
        x: 534
        y: 920
        z:1
        Text {
            id: azadegan
            text: qsTr("Azadegan")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:cqqq
        x: 601
        y: 870
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#0047AB"
        opacity: 0.75
    }

////////////////////////////////////////////// line_4 //////////////////////////////////////////////
    // Shahid Kolahdouz
    MyButton {
        id: abc
        width: 53
        height: 53
        x: 1435
        y: 665
        z: 2
        color: "#f4c430"
        station.text: "Shahid Kolahdouz"
    }
    Label {
        x: 1400
        y: 650
        z:1
        Text {
            id: kolahdouz
            text: qsTr("Shahid Kolahdouz")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qq
        x: 1383
        y: 685
        z:  0
        width: 70
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Nirou Havaei
    MyButton {
        id: abcd
        width: 40
        height: 40
        x: 1355
        y: 670
        z: 2
        color: "#f4c430"
        station.text: "Nirou Havaei"
    }
    Label {
        x: 1355
        y: 715
        z:1
        Text {
            id: havaei
            text: qsTr("Nirou Havaei")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qqi
        x: 1300
        y: 685
        z:  0
        width: 60
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Nabard
    MyButton {
        id: abce
        width: 40
        height: 40
        x: 1285
        y: 670
        z: 2
        color: "#f4c430"
        station.text: "Nabard"
    }
    Label {
        x: 1294
        y: 715
        z:1
        Text {
            id: nabard
            text: qsTr("Nabard")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qi
        x: 1250
        y: 685
        z:  0
        width: 60
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Pirouzi
    MyButton {
        id: abcf
        width: 40
        height: 40
        x: 1215
        y: 670
        z: 2
        color: "#f4c430"
        station.text: "Pirouzi"
    }
    Label {
        x: 1243
        y: 715
        z:1
        Text {
            id: pirouzi
            text: qsTr("Pirouzi")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qri
        x: 1160
        y: 685
        z:  0
        width: 60
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Ebn-e Sina
    MyButton {
        id: abcg
        width: 40
        height: 40
        x: 1145
        y: 670
        z: 2
        color: "#f4c430"
        station.text: "Ebn-e Sina"
    }
    Label {
        x: 1137
        y: 715
        z:2
        Text {
            id: sina
            text: qsTr("Ebn-e Sina")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qki
        x: 1090
        y: 685
        z:  0
        width: 60
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Meydan-e Shohada
    MyButton {
        id: abch
        width: 40
        height: 40
        x: 1075
        y: 670
        z: 2
        color: "#f4c430"
        station.text: "Meydan-e Shohada"
    }
    Label {
        x: 980
        y: 715
        z:2
        Text {
            id: shohada
            text: qsTr("Meydan-e Shohada")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qkpi
        x: 900
        y: 685
        z:  0
        width: 180
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }
    Rectangle {
        id:qkpip
        x: 897
        y: 638
        z:  0
        width: 8
        height: 55
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }
    Rectangle {
        id:qpip
        x: 760
        y: 623
        z:  1
        width: 140
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    // Darvazeh Shemiran
    MyButton {
        id: abci
        width: 40
        height: 40
        x: 881.75
        y: 605
        z: 2
        color: "#f4c430"
        station.text: "Darvazeh Shemiran"
    }
    Label {
        x: 930
        y: 615
        z:0
        Text {
            id: shemiran
            text: qsTr("Darvazeh Shemiran")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:pip
        x: 676
        y: 575
        z:  1
        width: 8
        height: 55
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }
    Rectangle {
        id:pi
        x: 676
        y: 623
        z:  1
        width: 70
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Ferdowsi
    MyButton {
        id: abcj
        width: 40
        height: 40
        x: 660
        y: 540
        z: 2
        color: "#f4c430"
        station.text: "Ferdowsi"
    }
    Label {
        x: 660
        y: 520
        z:0
        Text {
            id: ferdowsi
            text: qsTr("Ferdowsi")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:pio
        x: 620
        y: 556
        z:  0
        width: 55
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Meydan-e Enghelab-e Eslami
    MyButton {
        id: abcjl
        width: 40
        height: 40
        x: 510
        y: 540
        z: 2
        color: "#f4c430"
        station.text: "Tajrish"
    }
    // Label {
    //     x: 660
    //     y: 520
    //     z:0
    //     Text {
    //         id: ferdowsi
    //         text: qsTr("Ferdowsi")
    //         font.pixelSize: 12
    //         font.family: "Vazirmatn"
    //     }
    // }
    Rectangle {
        id:piop
        x: 540
        y: 556
        z:  0
        width: 55
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Towhid
    MyButton {
        id: abcjj
        width: 40
        height: 40
        x: 440
        y: 540
        z: 2
        color: "#f4c430"
        station.text: "Towhid"
    }
    Label {
        x: 440
        y: 520
        z:0
        Text {
            id: towhid
            text: qsTr("Towhid")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:piokp
        x: 460
        y: 556
        z:  0
        width: 55
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //Shademan
    MyButton {
        id: abccj
        width: 40
        height: 40
        x: 370
        y: 540
        z: 2
        color: "#f4c430"
        station.text: "Shademan"
    }
    Label {
        x: 360
        y: 520
        z:2
        Text {
            id: shademan
            text: qsTr("Shademan")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:iop
        x: 400
        y: 556
        z:  0
        width: 55
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Ostad Mo'in
    MyButton {
        id: abcjb
        width: 40
        height: 40
        x: 300
        y: 540
        z: 2
        color: "#f4c430"
        station.text: "Ostad Mo'in"
    }
    Label {
        x: 285
        y: 520
        z:2
        Text {
            id: ostad
            text: qsTr("Ostad Mo'in")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:piopk
        x: 320
        y: 556
        z:  0
        width: 55
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Meydan-e Azadi
    MyButton {
        id: abcja
        width: 40
        height: 40
        x: 230
        y: 540
        z: 2
        color: "#f4c430"
        station.text: "Meydan-e Azadi"
    }
    Label {
        x: 190
        y: 520
        z:2
        Text {
            id: azadi
            text: qsTr("Meydan-e Azadi")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:op
        x: 260
        y: 556
        z:  0
        width: 55
        height: 8
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Eram-e Sabz
    MyButton {
        id: abcjaa
        width: 40
        height: 40
        x: 230
        y: 420
        z: 2
        color: "#f4c430"
        station.text: "Eram-e Sabz"
    }
    Label {
        x: 155
        y: 430
        z:2
        Text {
            id: eram
            text: qsTr("Eram-e Sabz")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:upi
        x: 245
        y: 450
        z:  0
        width: 8
        height: 110
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Allameh Jafari
    MyButton {
        id: abcjak
        width: 40
        height: 40
        x: 230
        y: 300
        z: 2
        color: "#f4c430"
        station.text: "Allameh Jafari"
    }
    Label {
        x: 147
        y: 310
        z:2
        Text {
            id: jafari
            text: qsTr("Allameh Jafari")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:upki
        x: 245
        y: 320
        z:  0
        width: 8
        height: 110
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    //  Kashani
    MyButton {
        id: abcjna
        width: 40
        height: 40
        x: 230
        y: 180
        z: 2
        color: "#f4c430"
        station.text: "Kashani"
    }
    Label {
        x: 183
        y: 175
        z:2
        Text {
            id: kashani
            text: qsTr("Kashani")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:uki
        x: 245
        y: 200
        z:  0
        width: 8
        height: 110
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

    // Chaharbagh
    MyButton {
        id: abcpja
        width: 53
        height: 53
        x: 223
        y: 10
        z: 2
        color: "#f4c430"
        station.text: "Chaharbagh"
    }
    Label {
        x: 150
        y: 30
        z:2
        Text {
            id: chaharbagh
            text: qsTr("Chaharbagh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:unki
        x: 245
        y: 55
        z:  0
        width: 8
        height: 140
        radius: 5
        color : "#f4c430"
        opacity: 0.75
    }

////////////////////////////////////////////// line_6 //////////////////////////////////////////////
    //  Haram-e Hazrat-e Abdolazim
    MyButton {
        id: abcppja
        width: 53
        height: 53
        x: 1435
        y: 935
        z: 2
        color: "#e11584"
        station.text: "Haram-e Hazrat-e Abdolazim"
    }
    Label {
        x: 1270
        y: 930
        z:2
        Text {
            id: haram
            text: qsTr("Haram-e Hazrat-e Abdolazim")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:nki
        x: 1090
        y: 957
        z:  0
        width: 360
        height: 8
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }

    //  Shahid Rezaei
    MyButton {
        id: abcha
        width: 40
        height: 40
        x: 1075
        y: 800
        z: 2
        color: "#e11584"
        station.text: "Shahid Rezaei"
    }
    Label {
        x: 1110
        y: 840
        z:2
        Text {
            id: rezaei
            text: qsTr("Shahid Rezaei")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:nmki
        x: 1090
        y: 825
        z:  0
        width: 8
        height: 137
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }
    Rectangle {
        id:nmxki
        x: 1090
        y: 700
        z:  0
        width: 8
        height: 137
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }
    Rectangle {
        id:mxki
        x: 1090
        y: 570
        z:  0
        width: 8
        height: 137
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }

    //  Emam Hossein
    MyButton {
        id: abcaha
        width: 40
        height: 40
        x: 1075
        y: 540
        z: 2
        color: "#e11584"
        station.text: "Emam Hossein"
    }
    Label {
        x: 1110
        y: 520
        z:2
        Text {
            id: hossein
            text: qsTr("Emam Hossein")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:mxi
        x: 750
        y: 492
        z:  0
        width: 345
        height: 8
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }
    Rectangle {
        id:xi
        x: 1090
        y: 492
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }

    //  Boostan-e laleh
    MyButton {
        id: wa
        width: 40
        height: 40
        x: 365
        y: 410
        z: 2
        color: "#e11584"
        station.text: "Boostan-e laleh"
    }
    Label {
        x: 400
        y: 390
        z:2
        Text {
            id: laleh
            text: qsTr("Boostan-e laleh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:mvxi
        x: 615
        y: 492
        z:  1
        width: 130
        height: 8
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }
    Rectangle {
        id:mxxi
        x: 380
        y: 492
        z:  1
        width: 210
        height: 8
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }
    Rectangle {
        id:mxzi
        x: 380
        y: 430
        z:  0
        width: 8
        height: 70
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }

    //  Yadegar-e Emam
    MyButton {
        id: abcajna
        width: 40
        height: 40
        x: 365
        y: 180
        z: 2
        color: "#e11584"
        station.text: "Yadegar-e Emam"
    }
    Label {
        x: 410
        y: 190
        z:2
        Text {
            id: yadegar
            text: qsTr("Yadegar-e Emam")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:mzi
        x: 380
        y: 210
        z:  0
        width: 8
        height: 210
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }

    //  Kouhsar
    MyButton {
        id: aajna
        width: 53
        height: 53
        x: 10
        y: 173
        z: 2
        color: "#e11584"
        station.text: "Kouhsar"
    }
    Label {
        x: 15
        y: 153
        z:2
        Text {
            id: kouhsar
            text: qsTr("Kouhsar")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:kmzi
        x: 260
        y: 197
        z:  0
        width: 130
        height: 7
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }
    Rectangle {
        id:zi
        x: 55
        y: 197
        z:  0
        width: 180
        height: 7
        radius: 5
        color : "#e11584"
        opacity: 0.75
    }

////////////////////////////////////////////// Bus_1 //////////////////////////////////////////////
    //  Tehran Pars
    MyButton {
        id: abac
        width: 53
        height: 53
        x: 1435
        y: 765
        z: 2
        color:"grey"
        station.text: "Tehran Pars"
    }
    Label {
        x: 1360
        y: 810
        z:2
        Text {
            id: tehranpars
            text: qsTr("Tehran Pars")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:zvi
        x: 1158
        y: 786
        z:  0
        width: 300
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:zvni
        x: 1158
        y: 697
        z:  0
        width: 15
        height: 103
        radius: 15
        color : "grey"
        opacity: 0.75
    }

    //  Bimeh
    MyButton {
        id: abja
        width: 53
        height: 53
        x: 10
        y: 533
        z: 2
        color:"grey"
        station.text: "Bimeh"
    }
    Label {
        x: 20
        y: 510
        z:2
        Text {
            id: bimeh
            text: qsTr("Bimeh")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:zni
        x: 1158
        y: 553
        z:  0
        width: 15
        height: 130
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:znxi
        x: 1100
        y: 552
        z:  0
        width: 73
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:znmi
        x: 820
        y: 552
        z:  0
        width: 270
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:nmi
        x: 820
        y: 553
        z:  0
        width: 15
        height: 79
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:nmik
        x: 750
        y: 617
        z:  0
        width: 85
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:xpip
        x: 673
        y: 570
        z:  0
        width: 15
        height: 63
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:piqw
        x: 673
        y: 619
        z:  0
        width: 70
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:pqiqw
        x: 50
        y: 553
        z:  0
        width: 200
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:piqwm
        x: 523
        y: 586
        z:  0
        width: 165
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:piwm
        x: 523
        y: 561
        z:  0
        width: 15
        height: 40
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:iwm
        x: 313
        y: 561
        z:  0
        width: 15
        height: 40
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:iwmq
        x: 242
        y: 561
        z:  0
        width: 15
        height: 40
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:iwmx
        x: 242
        y: 586
        z:  0
        width: 86
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }
    Rectangle {
        id:imx
        x: 315
        y: 586
        z:  0
        width: 220
        height: 15
        radius: 15
        color : "grey"
        opacity: 0.75
    }

////////////////////////////////////////////// Bus_2 //////////////////////////////////////////////
    //Khajeh Abdollah-e Ansari
    MyButton {
        id: asr
        width: 53
        height: 53
        x: 1090
        y: 170
        z:  2
        color:"#3B444B"
        station.text: "Khajeh Abdollah-e Ansari"
    }
    Label {
        x: 1160
        y: 170
        z:2
        Text {
            id: ansari
            text: qsTr("Khajeh Abdollah-e Ansari")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:imxp
        x: 1118
        y: 190
        z:  0
        width: 350
        height: 15
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }
    Rectangle {
        id:ixp
        x: 1453
        y: 190
        z:  0
        width: 15
        height: 90
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }
    Rectangle {
        id:ixvp
        x: 1453
        y: 314
        z:  0
        width: 15
        height: 255
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }
    Rectangle {
        id:ivp
        x: 1227
        y: 555
        z:  0
        width: 15
        height: 130
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }
    Rectangle {
        id:ivxp
        x: 1227
        y: 555
        z:  0
        width: 241
        height: 15
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }

    //Payaneh Javanmard
    MyButton {
        id: abpja
        width: 53
        height: 53
        x: 880
        y: 935
        z: 2
        color:"#3B444B"
        station.text: "Payaneh Javanmard"
    }
    Label {
        x: 940
        y: 950
        z:2
        Text {
            id: javanmorad
            text: qsTr("Payaneh Javanmard")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:iqvp
        x: 1227
        y: 700
        z:  0
        width: 15
        height: 128
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }
    Rectangle {
        id:iqp
        x: 1100
        y: 813
        z:  0
        width: 142
        height: 15
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }
    Rectangle {
        id:inqp
        x: 898
        y: 815
        z:  0
        width: 15
        height: 135
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }
    Rectangle {
        id:iqnqp
        x: 898
        y: 814
        z:  0
        width: 190
        height: 15
        radius: 15
        color : "#3B444B"
        opacity: 0.75
    }

////////////////////////////////////////////// Bus_3 //////////////////////////////////////////////
    // Shahid Sadr
    MyButton {
        id: bq
        width: 53
        height: 53
        x: 600
        y: 110
        z: 2
        color:"#54626F"
        station.text: "Shahid Sadr"
    }
    Label {
        x: 547
        y: 87
        z:2
        Text {
            id: sadr
            text: qsTr("Shahid Sadr")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:iqnp
        x: 619
        y: 27
        z:  0
        width: 15
        height: 110
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:qnp
        x: 619
        y: 26
        z:  0
        width: 120
        height: 15
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }

    //  Shahrak-e Shari'ati
    MyButton {
        id: gah
        width: 53
        height: 53
        x: 465
        y: 935
        z: 2
        color:"#54626F"
        station.text: "Shahrak-e Shari'ati"
    }
    Label {
        x: 360
        y: 970
        z:2
        Text {
            id: shahrak
            text: qsTr("Shahrak-e Shari'ati")
            font.pixelSize: 12
            font.family: "Vazirmatn"
        }
    }
    Rectangle {
        id:qnph
        x: 765
        y: 26
        z:  0
        width: 50
        height: 15
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:qniph
        x: 800
        y: 26
        z:  0
        width: 15
        height: 216
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:qnpmh
        x: 765
        y: 227
        z:  0
        width: 50
        height: 15
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:qnh
        x: 690
        y: 227
        z:  0
        width: 60
        height: 15
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:qnhmw
        x: 690
        y: 227
        z:  0
        width: 15
        height: 275
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:nhmw
        x: 600
        y: 488
        z:  0
        width: 106
        height: 15
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:nhw
        x: 415
        y: 488
        z:  0
        width: 200
        height: 15
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:nhuw
        x: 415
        y: 488
        z:  0
        width: 15
        height: 480
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }
    Rectangle {
        id:nhxuw
        x: 415
        y: 953
        z:  0
        width: 70
        height: 15
        radius: 15
        color : "#54626F"
        opacity: 0.75
    }

/////////////////////////////////////////////////////////////// box ///////////////////////////////////////////////////////////////

    Rectangle {
        x: 30
        y: 630
        width: 350
        height: 320
        radius: 20
        color: "#f5f5f5"
        border.color: "grey"
        border.width: 3
    }

    TextField {
        id: origin
        placeholderText: qsTr("Time")
        width: 210
        height: 40
        x: 50
        y: 650
        color: "black"

        background: Rectangle {
            radius: 10
            border.color: "#C9C9C9"
            border.width: 1.5
        }
        verticalAlignment: TextField.AlignVCenter

        font.pixelSize: 15
        font.weight: Font.Normal
        font.family: "Vazirmatn"
        leftPadding: 10
    }
    Rectangle {
        id: btnsearch
        x: 275
        y: 650
        width: 80
        height: 40
        radius: 10
        color: "#C9C9C9"
        Text {
            id: timetext
            text: qsTr("search")
            anchors.centerIn: parent
            color: "black"
            opacity: 0.75
        }
        MouseArea {
            id: recarea
            anchors.fill: parent
            hoverEnabled: true

            onPressed: parent.color = "grey"
            onReleased: parent.color = "#C9C9C9"
        }
    }

    Rectangle {
        x: 50
        y: 710
        width: 305
        height: 40
        radius: 10
        border.color: "#C9C9C9"
        border.width: 1.5
        color: "#f5f5f5"
        RadioButton {
            id: btn_bestdistance
            x: 2
            y: 3
            Text {
                id: txtdistance
                x: 27
                y: 8
                text: qsTr("Best Distance")
            }
        }
        RadioButton {
            id: btn_bestcost
            x: 114
            y: 3
            Text {
                id: txtcost
                x: 27
                y: 8
                text: qsTr("Best Cost")
            }
        }
        RadioButton {
            id: btn_besttime
            x: 207
            y: 3
            Text {
                id: txttime
                x: 27
                y: 8
                text: qsTr("Best Time")
            }
        }
    }

    Label {
        x: 50
        y: 790
        Text {
            text: qsTr("Arriving Time (Best Distance): ")
            font.bold: true
            font.pixelSize: 16
            font.family: "Vazirmatn"
        }
    }
    Label {
        id: lbl_timeForDistance
        x: 274
        y: 788
        Text {
            text: "11:30 am"
            font.bold: true
            font.pixelSize: 18
            font.family: "Vazirmatn"
        }
    }

    Label {
        x: 50
        y: 830
        Text {
            text: qsTr("Arriving Time (Lowest Cost): ")
            font.bold: true
            font.pixelSize: 16
            font.family: "Vazirmatn"
        }
    }
    Label {
        id:lbl_timeForCost
        x: 274
        y: 828
        Text {
            text: "11:30 am"
            font.bold: true
            font.pixelSize: 18
            font.family: "Vazirmatn"
        }
    }

    Label {
        x: 50
        y: 870
        Text {
            text: qsTr("Arriving Time (Shortest Time): ")
            font.bold: true
            font.pixelSize: 16
            font.family: "Vazirmatn"
        }
    }
    Label {
        id:lbl_timeForTime
        x: 274
        y: 868
        Text {
            text: "11:30 am"
            font.bold: true
            font.pixelSize: 18
            font.family: "Vazirmatn"
        }
    }
}
