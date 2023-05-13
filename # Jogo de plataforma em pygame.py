# Jogo de plataforma em pygame
import pygame
import random

# Inicializar o pygame
pygame.init()

# Definir as cores
PRETO = (0, 0, 0)
BRANCO = (255, 255, 255)
VERMELHO = (255, 0, 0)
VERDE = (0, 255, 0)
AZUL = (0, 0, 255)

# Definir as dimensões da tela
LARGURA = 800
ALTURA = 600
tela = pygame.display.set_mode((LARGURA, ALTURA))

# Definir o título da janela
pygame.display.set_caption("Jogo de plataforma")

# Definir o relógio para controlar o FPS
relogio = pygame.time.Clock()

# Definir a classe do personagem
class Personagem(pygame.sprite.Sprite):
    def __init__(self):
        # Chamar o construtor da classe pai
        super().__init__()

        # Carregar a imagem do personagem
        self.image = pygame.image.load("mulher.png")

        # Obter o retângulo da imagem
        self.rect = self.image.get_rect()

        # Definir a posição inicial do personagem
        self.rect.x = 50
        self.rect.y = ALTURA - self.rect.height

        # Definir a velocidade do personagem
        self.vel_x = 0
        self.vel_y = 0

        # Definir a gravidade do personagem
        self.gravidade = 1

    def update(self):
        # Atualizar a posição do personagem de acordo com a velocidade e a gravidade
        self.vel_y += self.gravidade
        self.rect.x += self.vel_x
        self.rect.y += self.vel_y

        # Verificar se o personagem saiu da tela pela esquerda ou pela direita
        if self.rect.x < 0:
            self.rect.x = 0
        if self.rect.x > LARGURA - self.rect.width:
            self.rect.x = LARGURA - self.rect.width

        # Verificar se o personagem saiu da tela por baixo ou por cima
        if self.rect.y < 0:
            self.rect.y = 0
            self.vel_y = 0
        if self.rect.y > ALTURA - self.rect.height:
            self.rect.y = ALTURA - self.rect.height
            self.vel_y = 0

    def pular(self):
        # Fazer o personagem pular se ele estiver no chão
        if self.rect.y == ALTURA - self.rect.height:
            self.vel_y = -20

# Definir a classe do obstáculo
class Obstaculo(pygame.sprite.Sprite):
    def __init__(self):
        # Chamar o construtor da classe pai
        super().__init__()

        # Definir a largura e a altura do obstáculo
        largura = random.randint(50, 100)
        altura = random.randint(50, 100)

        # Criar uma superfície para o obstáculo
        self.image = pygame.Surface([largura, altura])

        # Preencher a superfície com uma cor aleatória
        cor = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
        self.image.fill(cor)

        # Obter o retângulo da superfície
        self.rect = self.image.get_rect()

        # Definir a posição inicial do obstáculo fora da tela pela direita
        self.rect.x = LARGURA + largura
        self.rect.y = ALTURA - altura

    def update(self):
        # Atualizar a posição do obstáculo de acordo com a velocidade
        vel_x = -10
        self.rect.x += vel_x

# Definir a classe da moeda
class Moeda(pygame.sprite.Sprite):
    def __init__(self):
        # Chamar o construtor da classe pai
        super().__init__()

        # Carregar a imagem da moeda
        self.image = pygame.image.load("moeda.png")

        # Obter o retângulo da imagem
        self.rect = self.image.get_rect()

        # Definir a posição inicial da moeda fora da tela pela direita
        self.rect.x = LARGURA + self.rect.width
        self.rect.y = random.randint(0, ALTURA - self.rect.height)

    def update(self):
        # Atualizar a posição da moeda de acordo com a velocidade
        vel_x = -10
        self.rect.x += vel_x

# Criar o personagem do jogo
personagem = Personagem()

# Criar os grupos de sprites
todos_sprites = pygame.sprite.Group()
todos_sprites.add(personagem)
obstaculos = pygame.sprite.Group()
moedas = pygame.sprite.Group()

# Definir o contador de tempo para criar os obstáculos e as moedas
tempo_obstaculo = 0
tempo_moeda = 0

# Definir a pontuação do jogo
pontuacao = 0

# Definir o estado do jogo
jogando = True

# Loop principal do jogo
while jogando:
    # Limitar o FPS a 60
    relogio.tick(60)

    # Processar os eventos do jogo
    for evento in pygame.event.get():
        # Verificar se o usuário clicou no botão de fechar a janela
        if evento.type == pygame.QUIT:
            # Sair do jogo
            jogando = False

        # Verificar se o usuário pressionou uma tecla
        if evento.type == pygame.KEYDOWN:
            # Verificar qual tecla foi pressionada
            if evento.key == pygame.K_LEFT:
                # Mover o personagem para a esquerda
                personagem.vel_x = -10
            if evento.key == pygame.K_RIGHT:
                # Mover o personagem para a direita
                personagem.vel_x = 10
            if evento.key == pygame.K_UP:
                # Fazer o personagem pular
                personagem.pular()

        # Verificar se o usuário soltou uma tecla
        if evento.type == pygame.KEYUP:
            # Verificar qual tecla foi solta
            if evento.key == pygame.K_LEFT or evento.key == pygame.K_RIGHT:
                # Parar o movimento horizontal do personagem
                personagem.vel_x = 0

    # Atualizar os sprites do jogo
    todos_sprites.update()

    # Verificar as colisões entre o personagem e os obstáculos
    colisoes_obstaculos = pygame.sprite.spritecollide(personagem, obstaculos, True)
    for obstaculo in colisoes_obstaculos:
        # Reduzir a vida do personagem em 10 pontos
        personagem.vida -= 10

    # Verificar as colisões entre o personagem e as moedas
    colisoes_moedas = pygame.sprite.spritecollide(personagem, moedas, True)
    for moeda in colisoes_moedas:
        # Aumentar a pontuação do jogo em 1 ponto
        pontuacao += 1

    # Verificar se o personagem ficou sem vida
    if personagem.vida <= 0:
        # Terminar o jogo com derrota
        jogando = False

    # Aumentar o contador de tempo para criar os obstáculos e as moedas
    tempo_obstaculo += 1
    tempo_moeda += 1

    # Verificar se é hora de criar um novo obstáculo
    if tempo_obstaculo == 60:
        # Criar um novo obstáculo e adicionar aos grupos de sprites
        obstaculo = Obstaculo()
        todos_sprites.add(obstaculo)
        obstaculos.add(obstaculo)
        # Zerar o contador de tempo para criar os obstáculos
        tempo_obstaculo = 0

    # Verificar se é hora de criar uma nova moeda
    if tempo_moeda == 30:
        # Criar uma nova moeda e adicionar aos grupos de sprites
        moeda = Moeda()
        todos_sprites.add(moeda)
        moedas.add(moeda)
        # Zerar o contador de tempo para criar as moedas
        tempo_moeda = 0

    # Preencher o fundo da tela com a cor preta
    tela.fill(PRETO)

    # Desenhar os sprites do jogo na tela
    todos_sprites.draw(tela)

    # Mostrar a pontuação do jogo na tela
    fonte = pygame.font.SysFont("Arial", 32)
    texto = fonte.render(f"Pontuação: {pontuacao}", True, BRANCO)
    tela.blit(texto, (10, 10))

    # Mostrar a vida do personagem na tela
    texto = fonte.render(f"Vida: {personagem.vida}", True, BRANCO)
    tela.blit(texto, (LARGURA - 150, 10))

    # Atualizar a tela
    pygame.display.flip()

# Finalizar o pygame
pygame.quit()