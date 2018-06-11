# MyOpenGL
## Computer graphics labs
Models download <a href="https://drive.google.com/file/d/1e8Bkbjby-ub8G93fnDDYvDT6CVysK7O4/view?usp=sharing">link<a/>.
<br>
Enter <kbd>1</kbd>, <kbd>2</kbd>, <kbd>3</kbd>, <kbd>4</kbd> or <kbd>5</kbd> for Legacy OpenGL, Modern OpenGL 2D, Modern OpenGL 3D, Modern Advanced OpenGL 3D or Procedural Terrian Generation.
<br>
Press <kbd>1</kbd>-<kbd>9</kbd> to change state.
<br>
Toggle on/off mouse cursor with <kbd>`</kbd>(default off).
<br>
Toggle on/off wireframe mode with <kbd>numpad 0</kbd>.
<br>
In Modern OpenGL 3D scenes 4-8, Modern Advanced OpenGL 3D scenes 2-3 and Procedural Terrian Generation you can:
<ul>
<li>Move camera with <kbd>W</kbd><kbd>A</kbd><kbd>S</kbd><kbd>D</kbd> and mouse</li>
<li>Hold <kbd>shift</kbd> to move faster</li>
</ul>
In Modern OpenGL 3D scene 9 you can:
<ul>
<li>Move camera with <kbd>W</kbd><kbd>A</kbd><kbd>S</kbd><kbd>D</kbd> and mouse</li>
<li>Hold <kbd>shift</kbd> to move faster</li>
<li>Press <kbd>space</kbd> to jump</li>
<li>Hold <kbd>ctrl</kbd> to crouch</li>
</ul>
  
# Проектна задача по компјутерска графика<br>Процедурална теренска генерација
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img1.png)
### State
Имаме класа State во која ќе генерираме терен. За контрола на State користиме класата StateManager. Секој State се состои од компоненти(класи) потребни за креирање на еден State. Ги користиме класите Camera, Light, TerrainMesh, Skybox, Entity и други дополнителни класи и променливи. Секои од овие се извршуваат во потребните методи како Init, HandleKeyEvents, Update, Render, RenderGui и други.
#### Init
Во Init ги иницијалазираме сите класи и кажуваме кои работи OpenGL ќе користи при цртање. Командата glEnable(GL_DEPTH_TEST) кажува OpenGL да користи buffer за длабочина. Командите glEnable(GL_CULL_FACE) и glCullFace(GL_BACK) кажуваат дека внатрешните лица да небидат нацртани. Со ова ги зголемуваме перформансите.	 Командите glEnable(GL_BLEND) и glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) се за овозможување на транспарентност на текстури со alpha бојата.
#### RenderGui
Овој метод кажува и контролира што ќе биде покажано во GUI-то. Како менување на параметрите на генерирање на теренот, менување на позиција и боја на светлото и други инофрмативни информации.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img2.png)
#### GenerateTrees
Овој метод го повикуваме внатре во Init методот каде генерираме модели(entities) на одредени случајни позиции каде што има трева на теренот. Моделите се дрва, трева, цвеќа, грмушки и слично.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img3.png)
#### Update
Во Update методот ги update shader uniforms на сите enteties, skybox, light и terrian. Исто така update на позицијата на камерата.
#### Render
Тука се повикуваат сите функции за цртање, се пресметува projection и view матриците. Исто така се цртаат само блиските enteties на камерата другите целосно се игнорираат. Со ова се зголемуваат перформансите.
#### HandleKeyEvents, HandleMouseEvents и HandleScrollEvents
Овие методи се за камерата кои читаат од корисничкиот влез како тастатура и маус.
### TerrainMesh
Се состои од класи како VertexArray, VertexBuffer, IndexBuffer, Shader, Texture и TerrainGenerator. Класите VertexArray, VertexBuffer, IndexBuffer содржат OpenGL команди за да може да се исцрта теренот. TerrainGenerator е класа за генерирање на сите vertex и index на теренот. Shader класата користи vertex и фрагмент shader terrain.
#### Texture
Имаме 4 Texture класи. Првата дифузна текстура за тревата на теренот. Втората е дифузна текстура за снегот на планитите на теренот. Третата текстурара е blend мапа која е ѓенерирана од TerrainGenerator класата. Четвртата е specular текстура за снегот.
#### Terrain shader
Во vertex делот од овој shader се пресметува позицијата на теренот. Исто така и видливоста(далечината) на моделот за да може потоа во fragment делот да се даде ефект на магла. Исто така кординатите за текстури ги ротираме 90 степени спротивно од стрелките на часовниотк за да се софпаднат текстурите со blend мапата. Во fragment  делот од овој shader се пресметува текстурата за теренот со помош на blend мапата. Се прави микс на текстурата трева и снег според зелената компонента од blend мапата. Исто така пресметуваме ambient, diffuse и specular кои на крај се собираат сите за да се добие текстура според светлото.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img4.png)
### TerrainGenerator
Овде се наоѓа главната класа за генерирање на теренот PerlinNoise.  Со PerlinNoise класата генерираме Перлин(Perlin) шум за дадени променливи(x,y) за да пресметаме височина(y кордината од vertex) на теренот. Во TerrainGenerator класата имаме 4 методи SetPerlin, createBlendMap, Generate и calculateNormal.
#### SetPerlin
Овде сетираме атрибутите за Перлин шумот кој ке го генерираме. Исто така ја повикуаме методот createBlendMap кој генерира .bmp blend мапа слика според големината на теренот. Го множиме перлин шумот со константа. Ако бројот е помал од 0 ќе се запише во пикселот црна боја(0,0,0), а ако е поголем од 0 тогаш пикселот ке биде перлин шумот помножен со константата бојата. Има граница ставено ако бројот надмине 255 пак да биде 255(црна боја). Blend мапата ќе биде црно бела затоа што пикселите ќе имаат исти вредности за R,G и B.<br>
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img5.png)<br>
#### Generate
Овде се генерираат сите vertex и index за теренот според дадена бројка и големина. Висината на секој vertex(y) и неговиот нормален y(пресметка со методот calculateNormal) се преметуваат со методот GetHeight од перлин класата.
### PerlinNoise
Со оваа класа се пресметува Перлин шум кој ни овозможува да генерираме терен според дадени атрибути како Seed, Persistence, Frequency, Amplitude и Octaves.
#### Seed
Ова е бројче кое се собира со фрекфренцијата за да се има покнторлиран шум.
#### Persistence
Со ова се контролира острината на шумот.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img6.png)
#### Frequency
Со ова се контролира фрекфренцијата на брановите на шумот.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img7.png)
#### Amplitude
Со ова се контролира амплитудата на шумот. Амплитудата ја множиме одкога ке го пресметаме шумот. Ова дава ефект на висина на планините.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img8.png)
#### Octaves
Колку пати да се повтори пресметката за шумот за да се добие финалниот шум.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img9.png)
### Light
Light класата има слични класи како TerrainMesh. Исто има променливи за ambient, diffuse и specular. Користи lampColor shader кој е многу едноставен. Можеме во реално време да менување сите променливи на Light класата.
### Skybox
Skybox класата користи слични класи како TerrainMesh. Има 6 текстури(десно, лево, горе, доле, пред, зад) со кој се генерира cubemap со кој можеме да направиме skybox. За подобри перформанси пред да цртаме skybox користиме glDepthFunc(GL_LEQUAL) и кога ќе нацртаме враќаме назат буферот за длабичина на glDepthFunc(GL_LESS) штo e по default.
### Tree и Grass
Oвие класи се дел од enteties. Користиме библиотеката Assimp за да можеме да прочитаме .obj модели заедно со нивните текстури ова го правиме со Mesh класата каде ги фчитуваме сите mesh од еден .obj и неговите текстури и правиме model. Секој mesh има свој Vertex Array. Во методот process во класата Mesh правиме оптимизација на текстурите што ги чува со помош на map. Ако текстурата више е зачувана немора да ја запишува повторно истата текстура. Целиот метод за читање и зачувување за сите mesh од еден модел се врши рекурзивно.
### Дополнителни библиотеки
Се користат дополнителните c++ библиотеки Assimp, Glad, GLFW, Glm, Stb и Imgui.
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img10.png)
![](https://github.com/kikoano/MyOpenGL/blob/master/images/img11.png)
#### Изработил: Кристијан Трајковски 
