# Math Library

## -- Linear algebra formulas and explanations --

#### Since I have to learn all that (I'm in 10th grade), here are my formulas :




## 1. Vecteurs



### 1. Norme d'un vecteur
La norme (ou la magnitude) est la longueur du vecteur : 

$\displaystyle \| \vec{v} \| = \sqrt{v_x^2 + v_y^2 + v_z^2}$

### 2. Normalisation
La normalisation transforme un vecteur $\vec{v}$ en un vecteur de longueur 1 :  

$\displaystyle \hat{v} = \dfrac{\vec{v}}{\| \vec{v} \|} \qquad \text{où} \quad \| \vec{v} \| \neq 0$

### 3. Produit Scalaire
Le produit scalaire est une opération qui renvoie un scalaire. 

S'il est > 0, alors l'angle < 90°, $\;$ s'il est = 0, alors l'angle = 90° (les vecteurs sont orthogonaux -> perpendiculaires), $\;$ s'il est < 0, alors l'angle est > 90°

$\displaystyle \vec{a} \cdot \vec{b} = (a_x \times b_x) + (a_y \times b_y) + (a_z \times b_z)$

### 4. Produit Vectoriel
Le produit vectoriel renvoie un vecteur perpendiculaire au plan formé par $\vec{a}$ et $\vec{b}$ : 

$\displaystyle \vec{a} \times \vec{b} = \begin{pmatrix}
a_y b_z - a_z b_y \\[10pt]
a_z b_x - a_x b_z \\[10pt]
a_x b_y - a_y b_x
\end{pmatrix}$

### Distance entre deux points
Cela permet de calculer la distance entre deux points (deux vecteurs)

$\displaystyle d(A, B) = \sqrt{(b_x - a_x)^2 + (b_y - a_y)^2 + (b_z - a_z)^2}$

## 

## 2. Matrices

### 1. Matrice Identité $I_4$
C'est la base de départ. Elle ne modifie pas le vecteur.

$\displaystyle I_4 = \begin{pmatrix}
1 & 0 & 0 & 0 \\[6pt]
0 & 1 & 0 & 0 \\[6pt]
0 & 0 & 1 & 0 \\[6pt]
0 & 0 & 0 & 1
\end{pmatrix}$

### 2. Matrice de Translation
En **Column-major**, les valeurs de translation $t_x, t_y, t_z$ se trouvent dans la dernière colonne.

$\displaystyle M_{trans} = \begin{pmatrix}
1 & 0 & 0 & t_x \\[6pt]
0 & 1 & 0 & t_y \\[6pt]
0 & 0 & 1 & t_z \\[6pt]
0 & 0 & 0 & 1
\end{pmatrix}$

### 3. Matrice de Scale
Les facteurs d'échelle $s_x, s_y, s_z$ se situent sur la diagonale principale.

$\displaystyle M_{scale} = \begin{pmatrix}
s_x & 0   & 0   & 0 \\[6pt]
0   & s_y & 0   & 0 \\[6pt]
0   & 0   & s_z & 0 \\[6pt]
0   & 0   & 0   & 1
\end{pmatrix}$

### 4. Matrices de Rotation
Voici les rotations autour des trois axes principaux. L'angle est noté $\theta$.

**Rotation autour de l'axe X :**
$\displaystyle R_x(\theta) = \begin{pmatrix}
1 & 0 & 0 & 0 \\[6pt]
0 & \cos\theta & -\sin\theta & 0 \\[6pt]
0 & \sin\theta & \cos\theta & 0 \\[6pt]
0 & 0 & 0 & 1
\end{pmatrix}$

**Rotation autour de l'axe Y :**
$\displaystyle R_y(\theta) = \begin{pmatrix}
\cos\theta & 0 & \sin\theta & 0 \\[6pt]
0 & 1 & 0 & 0 \\[6pt]
-\sin\theta & 0 & \cos\theta & 0 \\[6pt]
0 & 0 & 0 & 1
\end{pmatrix}$

**Rotation autour de l'axe Z :**
$\displaystyle R_z(\theta) = \begin{pmatrix}
\cos\theta & -\sin\theta & 0 & 0 \\[6pt]
\sin\theta & \cos\theta & 0 & 0 \\[6pt]
0 & 0 & 1 & 0 \\[6pt]
0 & 0 & 0 & 1
\end{pmatrix}$


