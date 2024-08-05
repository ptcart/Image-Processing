import os.path
from tkinter import *
import tkinter
from tkinter import messagebox
from tkinter.filedialog import *
import math
from tkinter.simpledialog import *
from PIL import Image  # 필로우 라이브러리 중 Image 객체를 사용


## 함수 선언부
#////////////////////
# 공통 함수부
#////////////////////
def OnMalloc3D(t, h, w, initValue=0):
    memory = None
    memory = [[[initValue for _ in range(w)] for _ in range(h)] for _ in range(t)]
    return memory


def OnOpenDocument():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage
    global m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, mouseYN
    sx = sy = ex = ey = -1
    mouseYN.set(False)
    fileName = askopenfilename(parent=window, filetypes=(('컬러이미지', '*.png;*.jpg;*.bpm,*.tif'), ("모든 파일", "*.*")))
    ## 파일 크기 확인 + (중요)입력 영상 높이,폭 계산
    pillow = Image.open(fileName)  # 필로우 객체로 읽기
    m_oriH = pillow.height
    m_oriW = pillow.width

    ## 메모리 할당
    m_oriImage = OnMalloc3D(RGB, m_oriH, m_oriW)

    # 파일에서 메모리로 로딩
    pillowRGB = pillow.convert('RGB')  # RGB 모델로 변경
    for i in range(m_oriH):
        for j in range(m_oriW):
            r, g, b = pillowRGB.getpixel((j, i))
            m_oriImage[RR][i][j] = r
            m_oriImage[GG][i][j] = g
            m_oriImage[BB][i][j] = b

    ## equalImage() 호출
    equalImage()


def OnSaveDocument():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    if (m_tarImage == None):
        return
    wfp = asksaveasfile(parent=window, mode='wb', defaultextension='*.png',
                        filetypes=(('PNG파일', '*.png'), ('모든 파일', '*.*')))
    pillow = Image.new('RGB', (m_tarW, m_tarH))  # 핀 필로우 객체 생성
    for i in range(m_tarH):
        for k in range(m_tarW):
            r = m_tarImage[RR][i][k]
            g = m_tarImage[GG][i][k]
            b = m_tarImage[BB][i][k]
            pillow.putpixel((k, i), (r, g, b))

    pillow.save(wfp.name)
    messagebox.showinfo('성공', wfp.name + '로 저장됨')


def OnDraw():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage
    global m_oriH, m_oriW, m_tarH, m_tarW, hop
    # 몰라 일단 설정
    MAXSIZE = 512
    tarH = m_tarH
    tarW = m_tarW
    hop = 1
    if (tarH > MAXSIZE or tarW > MAXSIZE):
        # hop을 계산.
        if (tarW > tarH):
            hop = tarH // MAXSIZE
        else:
            hop = tarH // MAXSIZE

        tarH = tarH // hop
        tarW = tarW // hop

    ## 기존의 파일을 연 적이 있다 == 캔버스가 이미 붙어있다
    if canvas != None:
        canvas.destroy()
    # 벽, 캔버스, 종이 설정
    window.geometry(str(tarW) + 'x' + str(tarH))
    canvas = Canvas(window, height=tarH, width=tarW, bg='gray')
    OnBindMouse()  # 새로운 캔버스에 마우스 바인드하기
    paper = PhotoImage(height=tarH, width=tarW)  # 종이
    canvas.create_image((tarW // 2, tarH // 2), image=paper, state='normal')

    # ## 메모리 --> 화면
    ## 더블 버퍼링 기법 적용 (모두 메모리에 load하고 한방에 종이에 붙이기)
    rgbString = ""  # 전체에 대한 16진수 문자열
    for i in range(tarH):
        oneLineStr = ""  # 1줄에 대한 16진수 문자열
        for j in range(tarW):
            r = m_tarImage[RR][i * hop][j * hop]
            g = m_tarImage[GG][i * hop][j * hop]
            b = m_tarImage[BB][i * hop][j * hop]
            oneLineStr += '#%02x%02x%02x ' % (r, g, b)
        rgbString += '{' + oneLineStr + '} '
    paper.put(rgbString)
    canvas.pack()
    # 상태바 변경
    fnames = fileName.split('/')
    sbar.config(text=str(m_tarW) + 'x' + str(m_tarH) + ' ' + fnames[-1])


def OnBindMouse():
    global sx, sy, ex, ey, boxLine
    sx = sy = ex = ey = -1
    boxLine = None
    if (mouseYN.get()):
        canvas.bind('<Button-1>', leftClick)  # 마우스 왼쪽 버튼 클릭
        canvas.bind('<B1-Motion>', leftDrag)  # 마우스 왼쪽 누르고 끌기...
        canvas.bind('<ButtonRelease-1>', leftDrop)  # 마우스 왼쪽 떼기...
    else:
        canvas.unbind('<Button-1>')  # 마우스 왼쪽 버튼 클릭
        canvas.unbind('<B1-Motion>')  # 마우스 왼쪽 누르고 끌기...
        canvas.unbind('<ButtonRelease-1>')  # 마우스 왼쪽 떼기...


def leftClick(event):
    global sx, sy, ex, ey, boxLine, hop
    if boxLine != None:
        canvas.delete(boxLine)
    sx = event.x * hop
    sy = event.y * hop

def leftDrag(event):
    global sx, sy, ex, ey, boxLine, hop
    ex = event.x*hop
    ey = event.y*hop
    if boxLine != None:
        canvas.delete(boxLine)
    boxLine = canvas.create_rectangle(sx//hop, sy//hop, ex//hop, ey//hop, width=1)

def leftDrop(event):
    global sx, sy, ex, ey, boxLine, hop
    ex = event.x*hop
    ey = event.y*hop
    if sx > ex:
        sx, ex = ex, sx
    if sy > ey:
        sy, ey = ey, sy
    if boxLine != None:
        canvas.delete(boxLine)
    boxLine = canvas.create_rectangle(sx//hop, sy//hop, ex//hop, ey//hop, width=1)


# ////////////////////
# 영상처리 함수부
# ////////////////////
def equalImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def grayImage():
    global window, canvas, paper, fileName, mouseYN
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, boxLine
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW-1
        ey = m_tarH-1

    for i in range(m_oriH):
        for k in range(m_oriW):
            if (sx <= k < ex) and (sy <= i < ey):  # 영상 처리할 좌표가 사각형 안에 있으면
                value = m_oriImage[RR][i][k] + m_oriImage[GG][i][k] + m_oriImage[BB][i][k]
                m_tarImage[RR][i][k] = m_tarImage[GG][i][k] = m_tarImage[BB][i][k] = value // 3
            else:
                m_tarImage[RR][i][k] = m_oriImage[RR][i][k]
                m_tarImage[GG][i][k] = m_oriImage[GG][i][k]
                m_tarImage[BB][i][k] = m_oriImage[BB][i][k]

    ###########################
    OnDraw()


def addImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW-1
        ey = m_tarH-1

    value = askinteger('밝게/어둡게', '값', minvalue=-255, maxvalue=255)
    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    if (m_oriImage[rgb][i][k] + value < 0):
                        m_tarImage[rgb][i][k] = 0
                    elif (m_oriImage[rgb][i][k] + value > 255):
                        m_tarImage[rgb][i][k] = 255
                    else:
                        m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k] + value
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def reverseImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    m_tarImage[rgb][i][k] = 255 - m_oriImage[rgb][i][k]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def binaryImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    if (m_oriImage[rgb][i][k] < 127):
                        m_tarImage[rgb][i][k] = 0
                    elif (m_oriImage[rgb][i][k] >= 127):
                        m_tarImage[rgb][i][k] = 255
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def gammaImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    gamma = askinteger('감마', '값', minvalue=0, maxvalue=10)
    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k] // gamma
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def orImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    m_tmpImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    m_tmpImage = OnMalloc3D(RGB, m_tarH, m_tarW)

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW // 2):
                m_tmpImage[rgb][i][k] = 0
            for k in range(m_oriW // 2, m_oriW):
                m_tmpImage[rgb][i][k] = 255

    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    if (m_tarImage[rgb][i][k]) | (m_tmpImage[rgb][i][k]) >= 255:
                        m_tarImage[rgb][i][k] = 255
                    elif (m_tarImage[rgb][i][k]) | (m_tmpImage[rgb][i][k]) < 0:
                        m_tarImage[rgb][i][k] = 0
                    else:
                        m_tarImage[rgb][i][k] = m_tarImage[rgb][i][k] | m_tmpImage[rgb][i][k]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]


    #######################
    OnDraw()


def andImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    m_tmpImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)

    m_tmpImage = OnMalloc3D(RGB, m_tarH, m_tarW)

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW // 2):
                m_tmpImage[rgb][i][k] = 0
            for k in range(m_oriW // 2, m_oriW):
                m_tmpImage[rgb][i][k] = 255

    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    if (m_tarImage[rgb][i][k]) & (m_tmpImage[rgb][i][k]) >= 255:
                        m_tarImage[rgb][i][k] = 255
                    elif (m_tarImage[rgb][i][k]) & (m_tmpImage[rgb][i][k]) < 0:
                        m_tarImage[rgb][i][k] = 0
                    else:
                        m_tarImage[rgb][i][k] = m_tarImage[rgb][i][k] & m_tmpImage[rgb][i][k]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    #######################
    OnDraw()


def embossRGB():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, boxLine
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    MSIZE = 3
    mask = [[-1, 0, 0],
            [0, 0, 0],
            [0, 0, 1]]
    tmpOriImage = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2, 127.0);
    tmpTarImage = OnMalloc3D(RGB, m_tarH, m_tarW, 0.0)

    # 원본 이미지 ---> 임시 원본 이미지
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                tmpOriImage[rgb][i + 1][k + 1] = m_oriImage[rgb][i][k]

    # 회선 연산
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                S = 0.0
                for m in range(MSIZE):
                    for n in range(MSIZE):
                        S += mask[m][n] * tmpOriImage[rgb][i + m][k + n]
                tmpTarImage[rgb][i][k] = S

    # 후처리(127 더하기)
    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                tmpTarImage[rgb][i][k] += 127.0

    ## 임시 결과 이미지 --> 결과 이미지
    if (sx == -1):  # 마우스 사용 안함
        sx = 0
        sy = 0
        ex = m_tarW
        ey = m_tarH

    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                if (sx <= k < ex) and (sy <= i < ey):
                    if (tmpTarImage[rgb][i][k] < 0.0):
                        m_tarImage[rgb][i][k] = 0
                    elif (tmpTarImage[rgb][i][k] > 255.0):
                        m_tarImage[rgb][i][k] = 255
                    else:
                        m_tarImage[rgb][i][k] = int(tmpTarImage[rgb][i][k])
                else:
                    m_tarImage[RR][i][k] = m_oriImage[RR][i][k]
                    m_tarImage[GG][i][k] = m_oriImage[GG][i][k]
                    m_tarImage[BB][i][k] = m_oriImage[BB][i][k]
    #######################
    OnDraw()


import colorsys


def embossHSV():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, boxLine
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)

    # 원본 RGB --> 원본 HSI
    oriImageHSV = OnMalloc3D(RGB, m_tarH, m_oriW, 0.0)
    # RGB --> HSV 변환 입력
    for i in range(m_oriH):
        for k in range(m_oriW):
            r, g, b = m_oriImage[RR][i][k], m_oriImage[GG][i][k], m_oriImage[BB][i][k]
            h, s, v = colorsys.rgb_to_hsv(r, g, b)
            oriImageHSV[0][i][k], oriImageHSV[1][i][k], oriImageHSV[2][i][k] = h, s, v

    # ** 진짜 영상처리 알고리즘
    MSIZE = 3
    mask = [[-1, 0, 0],
            [0, 0, 0],
            [0, 0, 1]]
    tmpOriImageHSV = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2)
    tmpTarImageHSV = OnMalloc3D(RGB, m_tarH, m_tarW, 0.0)

    # 원본 이미지 ---> 임시 원보 이미지
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                tmpOriImageHSV[rgb][i + 1][k + 1] = oriImageHSV[rgb][i][k]

    # 회선 연산
    for i in range(m_oriH):
        for k in range(m_oriW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += mask[m][n] * tmpOriImageHSV[2][i + m][k + n]
            tmpTarImageHSV[2][i][k] = S
            tmpTarImageHSV[0][i][k] = tmpOriImageHSV[0][i][k]
            tmpTarImageHSV[1][i][k] = tmpOriImageHSV[1][i][k]

    # 후처리(127 더하기)
    for i in range(m_tarH):
        for k in range(m_tarW):
            tmpTarImageHSV[2][i][k] += 127.0
            if (tmpTarImageHSV[2][i][k] > 255.0):
                tmpTarImageHSV[2][i][k] = 255
            elif (tmpTarImageHSV[2][i][k] < 0.0):
                tmpTarImageHSV[2][i][k] = 0

    # HSV --> RGB

    ## 임시 결과 이미지 --> 결과 이미지
    if (sx == -1):  # 마우스 사용 안함
        sx = 0
        sy = 0
        ex = m_tarW
        ey = m_tarH

    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                if (sx <= k < ex) and (sy <= i < ey):
                    h, s, v = tmpTarImageHSV[0][i][k], tmpTarImageHSV[1][i][k], tmpTarImageHSV[2][i][k]
                    r, g, b = colorsys.hsv_to_rgb(h, s, v)
                    m_tarImage[RR][i][k], m_tarImage[GG][i][k], m_tarImage[BB][i][k] = int(r), int(g), int(b)

                else:
                    m_tarImage[RR][i][k] = m_oriImage[RR][i][k]
                    m_tarImage[GG][i][k] = m_oriImage[GG][i][k]
                    m_tarImage[BB][i][k] = m_oriImage[BB][i][k]

    #######################
    OnDraw()


def postImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    value = askinteger('경계', '값', minvalue=0, maxvalue=10)
    div = 255.0 / value
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용 안함
        sx = 0
        sy = 0
        ex = m_tarW
        ey = m_tarH
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                for m in range(value):
                    if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                        if (m_tarImage[rgb][i][k] >= int(div * m) and m_tarImage[rgb][i][k] < int(div * (m + 1))):
                            m_tarImage[rgb][i][k] = int(div * m)
                            break
                    else:
                        m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    ######################
    OnDraw()


def rangeImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    start = askinteger('범위', '시작', minvalue=0, maxvalue=255)
    end = askinteger('범위', '끝', minvalue=int(start), maxvalue=255)

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    if (start <= m_tarImage[rgb][i][k] and m_tarImage[rgb][i][k] <= end):
                        m_tarImage[rgb][i][k] = 255
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    ######################
    OnDraw()


def paraImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
                    value = (int)(255.0 - 255.0 * pow((m_tarImage[rgb][i][k] / 128.0 - 1.0), 2))
                    m_tarImage[rgb][i][k] = value
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    #######################
    OnDraw()


def zoomIn():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    scale = askinteger('확대', '배율', minvalue=1, maxvalue=10)
    m_tarH = m_oriH * scale
    m_tarW = m_oriW * scale
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i // scale][k // scale]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def zoomOut():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    scale = askinteger('축소', '배율', minvalue=1, maxvalue=10)
    m_tarH = (int)(m_oriH // scale)
    m_tarW = (int)(m_oriW // scale)
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i * scale][k * scale]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def rotateImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    angle = askinteger('회전', '각도', minvalue=0, maxvalue=360)
    radian = angle * 3.141592 / 180.0
    radian_90 = (90 - angle) * 3.141592 / 180.0
    m_tarH = int(m_oriH * math.cos(radian) + m_oriW * math.cos(radian_90))
    m_tarW = int(m_oriW * math.cos(radian_90) + m_oriW * math.cos(radian))

    oriCx = m_oriH // 2
    oriCy = m_oriW // 2
    tarCx = m_tarH // 2
    tarCy = m_tarW // 2

    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    tarX, tarY, oriX, oriY = 0, 0, 0, 0
    for rgb in range(RGB):
        for i in range(m_tarH):
            for k in range(m_tarW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    tarX = i
                    tarY = k
                    oriX = int(math.cos(radian) * (tarX - tarCx) + math.sin(radian) * (tarY - tarCy) + oriCx)
                    oriY = int(-math.sin(radian) * (tarX - tarCx) + math.cos(radian) * (tarY - tarCy) + oriCy)
                    if (0 <= oriX < m_oriH) and (0 <= oriY < m_oriW):
                        m_tarImage[rgb][tarX][tarY] = m_oriImage[rgb][oriX][oriY]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()


def moveImage():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    dX = askinteger('이동', 'X축', minvalue=0, maxvalue=360)
    dY = askinteger('이동', 'Y축', minvalue=0, maxvalue=360)
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    oriX = i
                    oriY = k
                    tarX = oriX + dX
                    tarY = oriY + dY
                    if (0 <= tarX < m_tarH) and (0 <= tarY < m_tarW):
                        m_tarImage[rgb][tarX][tarY] = m_oriImage[rgb][oriX][oriY]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()

def udMirror():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    X0 = m_oriW / 2
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    oriX = i
                    oriY = k
                    tarX = (int)((-1 * (oriX + 1)) + 2 * X0)
                    tarY = oriY
                    if (0 <= tarX < m_tarH) and (0 <= tarY < m_tarW):
                        m_tarImage[rgb][tarX][tarY] = m_oriImage[rgb][oriX][oriY]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    #######################
    OnDraw()

def lrMirror():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    Y0 = m_oriH / 2
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    oriX = i
                    oriY = k
                    tarX = oriX
                    tarY = (int)((-1 * (oriY + 1)) + 2 * Y0)
                    if (0 <= tarX < m_tarH) and (0 <= tarY < m_tarW):
                        m_tarImage[rgb][tarX][tarY] = m_oriImage[rgb][oriX][oriY]
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()

def endIn():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # ** 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    low = high = m_oriImage[0][0][0] = m_oriImage[1][0][0] = m_oriImage[2][0][0]
    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if m_oriImage[rgb][i][k] < low:
                    low = m_oriImage[rgb][i][k]

                if m_oriImage[rgb][i][k] > high:
                    high = m_oriImage[rgb][i][k]
    low = low + 50
    high = high - 50

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    newVal = (int)((m_oriImage[rgb][i][k] - low) / (high - low) * 255)
                    if newVal < 0:
                        newVal = 0
                    elif newVal > 255:
                        newVal = 255
                    m_tarImage[rgb][i][k] = newVal
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()

def histoEqual():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage, m_oriH, m_oriW, m_tarH, m_tarW
    # 메모리 해제 (생략 가능)
    m_tarImage = None
    # 중요! 결과 영상 크기 결정 --> 알고리즘에 따름..
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # 진짜 영상처리 알고리즘
    global sx, sy, ex, ey, boxLine
    if (sx == -1):  # 마우스 사용한 적 없을 때
        sx = 0
        sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_oriH):
            for k in range(m_oriW):
                m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    # 1단계: 빈도수 히스토그램 생성
    Rhist = [0] * 256
    Ghist = [0] * 256
    Bhist = [0] * 256

    for i in range(m_tarH):
        for k in range(m_tarW):
            Rhist[m_tarImage[0][i][k]] += 1
            Ghist[m_tarImage[1][i][k]] += 1
            Bhist[m_tarImage[2][i][k]] += 1

    # 2단계: 누적 히스토그램 생성
    sum_Rhist = [0] * 256
    sum_Ghist = [0] * 256
    sum_Bhist = [0] * 256
    sum_Rhist[0] = Rhist[0]
    sum_Ghist[0] = Ghist[0]
    sum_Bhist[0] = Bhist[0]

    for i in range(1, 256):
        sum_Rhist[i] = Rhist[i] + sum_Rhist[i - 1]
        sum_Ghist[i] = Ghist[i] + sum_Ghist[i - 1]
        sum_Bhist[i] = Bhist[i] + sum_Bhist[i - 1]


    # 3단계: 정규화된 히스토그램 생성
    nR = [0.0] * 256
    nG = [0.0] * 256
    nB = [0.0] * 256
    for i in range(256):
        nR[i] = sum_Rhist[i] * (1.0 / (m_oriW * m_oriH)) * 255.0
        nG[i] = sum_Ghist[i] * (1.0 / (m_oriW * m_oriH)) * 255.0
        nB[i] = sum_Bhist[i] * (1.0 / (m_oriW * m_oriH)) * 255.0


    # 4단계: 원래 값을 정규화된 값으로 치환
    for i in range(m_tarH):
        for k in range(m_tarW):
            if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                m_tarImage[0][i][k] = int(nR[m_oriImage[0][i][k]])
                m_tarImage[1][i][k] = int(nG[m_oriImage[1][i][k]])
                m_tarImage[2][i][k] = int(nB[m_oriImage[2][i][k]])
            else:
                m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]
    #######################
    OnDraw()

def histoStretch():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage
    global m_oriH, m_oriW, m_tarH, m_tarW
    ## 메모리 해제 필요없음
    ## 결과영상크기결정 --> 알고리즘에 따라 바뀜
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)

    low = [m_oriImage[0][0][0], m_oriImage[1][0][0], m_oriImage[2][0][0]]
    high = [m_oriImage[0][0][0], m_oriImage[1][0][0], m_oriImage[2][0][0]]
    for i in range(1, m_tarH):
        for k in range(1, m_tarW):
            for rgb in range(RGB):
                if low[rgb] > m_oriImage[rgb][i][k]:
                    low[rgb] = m_oriImage[rgb][i][k]
                elif high[rgb] < m_oriImage[rgb][i][k]:
                    high[rgb] = m_oriImage[rgb][i][k]
    # 진짜 영상처리
    global sx, sy, ex, ey
    if sx == -1:  # 마우스 클릭을 안했을 때
        sx = sy = 0
        ex = m_tarW
        ey = m_tarH
    for i in range(m_tarH):
        for k in range(m_tarW):
            for rgb in range(RGB):
                if sx <= k <= ex and sy <= i <= ey:  # 영상 처리할 좌표
                    newVal = float(m_oriImage[rgb][i][k] - low[rgb]) / (high[rgb] - low[rgb]) * 255.0
                    if (newVal < 0.0):
                        newVal = 0
                    if (newVal > 255.0):
                        newVal = 255
                    m_tarImage[rgb][i][k] = int(newVal)
                else:
                    m_tarImage[rgb][i][k] = m_oriImage[rgb][i][k]

    ######################
    OnDraw()

def blurr():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage
    global m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, boxLine
    ## 메모리 해제 필요없음
    ## 결과영상크기결정 --> 알고리즘에 따라 바뀜
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # 진짜 영상처리
    MSIZE = 5

    mask = [[1 / (MSIZE ** 2) for _ in range(MSIZE)] for _ in range(MSIZE)]
    ## 임시 메모리 확보
    tempOriImage = OnMalloc3D(RGB, m_oriH + MSIZE - 1, m_oriW + MSIZE - 1, 127.0)
    tempTarImage = OnMalloc3D(RGB, m_oriH + MSIZE - 1, m_oriW + MSIZE - 1, 0.0)
    for rgb in range(RGB):
        for i in range(m_oriH):
            for j in range(m_oriW):
                tempOriImage[rgb][i + 1][j + 1] = m_oriImage[rgb][i][j]
    ## 회선 연산
    for rgb in range(RGB):
        for i in range(m_oriH):
            for j in range(m_oriW):
                S = 0.0
                for m in range(MSIZE):
                    for n in range(MSIZE):
                        S += tempOriImage[rgb][i + m][j + n] * mask[m][n]
                tempTarImage[rgb][i][j] = S
    ## 후처리 및 임시 결과 --> 결과
    if sx == -1:
        sx = sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_tarH):
            for j in range(m_tarW):
                if sx <= j <= ex and sy <= i <= ey:
                    v = int(tempTarImage[rgb][i][j])
                    if v > 255:
                        m_tarImage[rgb][i][j] = 255
                    elif v < 0:
                        m_tarImage[rgb][i][j] = 0
                    else:
                        m_tarImage[rgb][i][j] = v
                else:
                    m_tarImage[rgb][i][j] = m_oriImage[rgb][i][j]
    ######################
    OnDraw()

def sharpning():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage
    global m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, boxLine
    ## 메모리 해제 필요없음
    ## 결과영상크기결정 --> 알고리즘에 따라 바뀜
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)
    # 진짜 영상처리
    MSIZE = 3
    mask = [[0.0, -1.0, 0.0],
            [-1.0, 5.0, -1.0],
            [0.0, -1.0, 0.0]]
    ## 임시 메모리 확보
    tempOriImage = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2, 127.0)
    tempTarImage = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2, 0.0)
    for rgb in range(RGB):
        for i in range(m_oriH):
            for j in range(m_oriW):
                tempOriImage[rgb][i + 1][j + 1] = m_oriImage[rgb][i][j]
    ## 회선 연산
    for rgb in range(RGB):
        for i in range(m_oriH):
            for j in range(m_oriW):
                S = 0.0
                for m in range(MSIZE):
                    for n in range(MSIZE):
                        S += tempOriImage[rgb][i + m][j + n] * mask[m][n]
                tempTarImage[rgb][i][j] = S
    ## 후처리 및 임시 결과 --> 결과
    if sx == -1:
        sx = sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for rgb in range(RGB):
        for i in range(m_tarH):
            for j in range(m_tarW):
                if sx <= j <= ex and sy <= i <= ey:
                    v = int(tempTarImage[rgb][i][j])
                    if v > 255:
                        m_tarImage[rgb][i][j] = 255
                    elif v < 0:
                        m_tarImage[rgb][i][j] = 0
                    else:
                        m_tarImage[rgb][i][j] = v
                else:
                    m_tarImage[rgb][i][j] = m_oriImage[rgb][i][j]
    ######################
    OnDraw()

def edge1():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage
    global m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, boxLine
    ## 메모리 해제 필요없음
    ## 결과영상크기결정 --> 알고리즘에 따라 바뀜
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)

    ## RGB --> HSI
    oriImageHSV = OnMalloc3D(RGB, m_oriH, m_oriW, 0.0)
    ## RGB --> HSV 변환 입력
    for i in range(m_oriH):
        for j in range(m_oriW):
            r, g, b = m_oriImage[RR][i][j], m_oriImage[GG][i][j], m_oriImage[BB][i][j]
            h, s, v = colorsys.rgb_to_hsv(r, g, b)
            oriImageHSV[0][i][j], oriImageHSV[1][i][j], oriImageHSV[2][i][j] = h, s, v

    # 진짜 영상처리
    MSIZE = 3
    mask = [[0, 0, 0],
            [-1, 1, 0],
            [0, 0, 0]]
    ## 임시 메모리 확보
    tempOriImageHSV = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2)
    tempTarImageHSV = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2, 0)
    for rgb in range(RGB):
        for i in range(m_oriH):
            for j in range(m_oriW):
                tempOriImageHSV[rgb][i + 1][j + 1] = oriImageHSV[rgb][i][j]
    ## 회선 연산
    for i in range(m_oriH):
        for j in range(m_oriW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tempOriImageHSV[2][i + m][j + n] * mask[m][n]
            tempTarImageHSV[2][i][j] = S
            tempTarImageHSV[1][i][j] = tempOriImageHSV[1][i][j]
            tempTarImageHSV[0][i][j] = tempOriImageHSV[0][i][j]

    ## 후처리 및 임시 결과 --> 결과
    if sx == -1:
        sx = sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for i in range(m_tarH):
        for j in range(m_tarW):
            if sx <= j <= ex and sy <= i <= ey:
                # 후처리
                tempTarImageHSV[2][i][j] += 127.0
                # h,s,v값 찾기
                h = tempTarImageHSV[0][i][j]
                s = tempTarImageHSV[1][i][j]
                v = tempTarImageHSV[2][i][j]
                # 오버플로우 체크
                if v > 255:
                    v = 255
                elif v < 0:
                    v = 0
                # rgb 변환
                r, g, b = colorsys.hsv_to_rgb(h, s, v)
                # 알맞은값 넣기
                m_tarImage[RR][i][j], m_tarImage[GG][i][j], m_tarImage[BB][i][j] = int(r), int(g), int(b)
            else:
                for rgb in range(RGB):
                    m_tarImage[rgb][i][j] = int(m_oriImage[rgb][i][j])
    ######################
    OnDraw()

def edge2():
    global window, canvas, paper, fileName
    global m_oriImage, m_tarImage
    global m_oriH, m_oriW, m_tarH, m_tarW
    global sx, sy, ex, ey, boxLine
    ## 메모리 해제 필요없음
    ## 결과영상크기결정 --> 알고리즘에 따라 바뀜
    m_tarH = m_oriH
    m_tarW = m_oriW
    # 메모리 할당
    m_tarImage = OnMalloc3D(RGB, m_tarH, m_tarW)

    ## RGB --> HSI
    oriImageHSV = OnMalloc3D(RGB, m_oriH, m_oriW, 0.0)
    ## RGB --> HSV 변환 입력
    for i in range(m_oriH):
        for j in range(m_oriW):
            r, g, b = m_oriImage[RR][i][j], m_oriImage[GG][i][j], m_oriImage[BB][i][j]
            h, s, v = colorsys.rgb_to_hsv(r, g, b)
            oriImageHSV[0][i][j], oriImageHSV[1][i][j], oriImageHSV[2][i][j] = h, s, v

    # 진짜 영상처리
    MSIZE = 3
    mask = [[0, -1, 0],
            [0, 1, 0],
            [0, 0, 0]]
    ## 임시 메모리 확보
    tempOriImageHSV = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2)
    tempTarImageHSV = OnMalloc3D(RGB, m_oriH + 2, m_oriW + 2, 0)
    for rgb in range(RGB):
        for i in range(m_oriH):
            for j in range(m_oriW):
                tempOriImageHSV[rgb][i + 1][j + 1] = oriImageHSV[rgb][i][j]
    ## 회선 연산
    for i in range(m_oriH):
        for j in range(m_oriW):
            S = 0.0
            for m in range(MSIZE):
                for n in range(MSIZE):
                    S += tempOriImageHSV[2][i + m][j + n] * mask[m][n]
            tempTarImageHSV[2][i][j] = S
            tempTarImageHSV[1][i][j] = tempOriImageHSV[1][i][j]
            tempTarImageHSV[0][i][j] = tempOriImageHSV[0][i][j]

    ## 후처리 및 임시 결과 --> 결과
    if sx == -1:
        sx = sy = 0
        ex = m_tarW - 1
        ey = m_tarH - 1

    for i in range(m_tarH):
        for j in range(m_tarW):
            if sx <= j <= ex and sy <= i <= ey:
                # 후처리
                tempTarImageHSV[2][i][j] += 127.0
                # h,s,v값 찾기
                h = tempTarImageHSV[0][i][j]
                s = tempTarImageHSV[1][i][j]
                v = tempTarImageHSV[2][i][j]
                # 오버플로우 체크
                if v > 255:
                    v = 255
                elif v < 0:
                    v = 0
                # rgb 변환
                r, g, b = colorsys.hsv_to_rgb(h, s, v)
                # 알맞은값 넣기
                m_tarImage[RR][i][j], m_tarImage[GG][i][j], m_tarImage[BB][i][j] = int(r), int(g), int(b)
            else:
                for rgb in range(RGB):
                    m_tarImage[rgb][i][j] = int(m_oriImage[rgb][i][j])
    ######################
    OnDraw()


## 전역 변수부
window, canvas, paper = None, None, None
m_oriImage, m_tarImage = None, None
m_oriH, m_oriW, m_tarH, m_tarW = [0] * 4
fileName = ''
RR, GG, BB, RGB = 0, 1, 2, 3  # 상수 정의
sbar = None  # 상태바
sx, sy, ex, ey = [-1] * 4
boxLine = None

## 메인 코드부
window = Tk()
window.geometry('512x512')
window.title('Color Image Processing (RC 3)')

sbar = Label(window, text='상태바', bd=1, relief=SUNKEN, anchor=W)
sbar.pack(side=BOTTOM, fill=X)

mouseYN = BooleanVar()  # 마우스 상태 여부
mouseYN.set(False)  # 초기값 No

# 메뉴 만들기
mainMenu = Menu(window)  # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=OnOpenDocument)
fileMenu.add_command(label='저장', command=OnSaveDocument)
fileMenu.add_separator()
fileMenu.add_command(label='종료', command=exit)

pixelMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='화소점 처리', menu=pixelMenu)

pixelMenu.add_command(label='동일 이미지', command=equalImage)
pixelMenu.add_command(label='그레이 스케일', command=grayImage)
pixelMenu.add_command(label='밝게/어둡게', command=addImage)
pixelMenu.add_command(label='반전', command=reverseImage)
pixelMenu.add_command(label='이진화', command=binaryImage)
pixelMenu.add_command(label='감마보정', command=gammaImage)
logicMenu = Menu(pixelMenu, tearoff=0)
logicMenu.add_command(label='or', command=orImage)
logicMenu.add_command(label='and', command=andImage)
pixelMenu.add_cascade(label="논리연산", menu=logicMenu)
pixelMenu.add_command(label='포스트라이징', command=postImage)
pixelMenu.add_command(label='범위강조변환', command=rangeImage)
pixelMenu.add_command(label='파라볼라변환', command=paraImage)

geometryMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='기하학 처리', menu=geometryMenu)
geometryMenu.add_command(label='확대', command=zoomIn)
geometryMenu.add_command(label='축소', command=zoomOut)
geometryMenu.add_command(label='회전', command=rotateImage)
geometryMenu.add_command(label='이동', command=moveImage)
geometryMenu.add_command(label='상하반전', command=udMirror)
geometryMenu.add_command(label='좌우반전', command=lrMirror)

histoMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='히스토그램', menu=histoMenu)
histoMenu.add_command(label='엔드-인', command=endIn)
histoMenu.add_command(label='평활화', command=histoEqual)
histoMenu.add_command(label='스트레치', command=histoStretch)

areaMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='화소영역 처리', menu=areaMenu)
areaMenu.add_checkbutton(label='마우스 사용', onvalue=1, offvalue=0, variable=mouseYN, command=OnBindMouse)
areaMenu.add_command(label='엠보싱(RGB)', command=embossRGB)
areaMenu.add_command(label='엠보싱(HSI)', command=embossHSV)
areaMenu.add_command(label='블러링', command=blurr)
areaMenu.add_command(label='샤프닝', command=sharpning)
areaMenu.add_command(label='수직에지', command=edge1)
areaMenu.add_command(label='수평에지', command=edge2)

mouseMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='마우스 처리', menu=mouseMenu)
mouseMenu.add_checkbutton(label='마우스 사용', onvalue=1, offvalue=0, variable=mouseYN, command=OnBindMouse)

window.mainloop()
