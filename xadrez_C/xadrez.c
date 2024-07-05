#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define vazio 0
#define peao 1
#define cavalo 2
#define torre 3
#define bispo 4
#define rei 6
#define rainha 5
#define branco 1
#define preto 0

typedef struct
{
    int tipo;
    char cor;
    bool vivo;
    bool primeiro_mov;
} peca;

peca tabuleiro[8][8];

void iniciar_tabuleiro();
void imprimir_tabuleiro();
int caminho_peca_horizontal_vertical(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna);
int caminho_peca_diagonal(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna);
bool pode_atacar(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna);
bool esta_em_xeque(int rei_linha, int rei_coluna, char cor_rei, int *a_linha, int *a_coluna);
bool pode_bloquear(int linha_rei, int coluna_rei, int linha_atacante, int coluna_atacante, char cor_rei);
bool esta_em_xeque_mate();
bool verifica_fim_de_jogo();
void atualizacao_peca(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna);
int movimento_peca();

int main()
{
    bool jogar_novamente = true;
    while (jogar_novamente)
    {
        iniciar_tabuleiro();
        imprimir_tabuleiro();

        while (!verifica_fim_de_jogo())
        {
            movimento_peca();
            imprimir_tabuleiro();
        }

        printf("Deseja jogar novamente? (1 para sim, 0 para nao)\n");
        scanf("%d", &jogar_novamente);
    }
    return 0;
}

void iniciar_tabuleiro()
{
    tabuleiro[1][0].tipo = peao;
    tabuleiro[1][0].primeiro_mov = true;
    tabuleiro[1][0].cor = 1;
    tabuleiro[1][0].vivo = true;
    tabuleiro[6][0].tipo = peao;
    tabuleiro[6][0].primeiro_mov = true;
    tabuleiro[6][0].cor = 0;
    tabuleiro[6][0].vivo = true;
    tabuleiro[1][1].tipo = peao;
    tabuleiro[1][1].primeiro_mov = true;
    tabuleiro[1][1].cor = 1;
    tabuleiro[1][1].vivo = true;
    tabuleiro[6][1].tipo = peao;
    tabuleiro[6][1].primeiro_mov = true;
    tabuleiro[6][1].cor = 0;
    tabuleiro[6][1].vivo = true;
    tabuleiro[1][2].tipo = peao;
    tabuleiro[1][2].primeiro_mov = true;
    tabuleiro[1][2].cor = 1;
    tabuleiro[1][2].vivo = true;
    tabuleiro[6][2].tipo = peao;
    tabuleiro[6][2].primeiro_mov = true;
    tabuleiro[6][2].cor = 0;
    tabuleiro[6][2].vivo = true;
    tabuleiro[1][3].tipo = peao;
    tabuleiro[1][3].primeiro_mov = true;
    tabuleiro[1][3].cor = 1;
    tabuleiro[1][3].vivo = true;
    tabuleiro[6][3].tipo = peao;
    tabuleiro[6][3].primeiro_mov = true;
    tabuleiro[6][3].cor = 0;
    tabuleiro[6][3].vivo = true;
    tabuleiro[1][4].tipo = peao;
    tabuleiro[1][4].primeiro_mov = true;
    tabuleiro[1][4].cor = 1;
    tabuleiro[1][4].vivo = true;
    tabuleiro[6][4].tipo = peao;
    tabuleiro[6][4].primeiro_mov = true;
    tabuleiro[6][4].cor = 0;
    tabuleiro[6][4].vivo = true;
    tabuleiro[1][5].tipo = peao;
    tabuleiro[1][5].primeiro_mov = true;
    tabuleiro[1][5].cor = 1;
    tabuleiro[1][5].vivo = true;
    tabuleiro[6][5].tipo = peao;
    tabuleiro[6][5].primeiro_mov = true;
    tabuleiro[6][5].cor = 0;
    tabuleiro[6][5].vivo = true;
    tabuleiro[1][6].tipo = peao;
    tabuleiro[1][6].primeiro_mov = true;
    tabuleiro[1][6].cor = 1;
    tabuleiro[1][6].vivo = true;
    tabuleiro[6][6].tipo = peao;
    tabuleiro[6][6].primeiro_mov = true;
    tabuleiro[6][6].cor = 0;
    tabuleiro[6][6].vivo = true;
    tabuleiro[1][7].tipo = peao;
    tabuleiro[1][7].primeiro_mov = true;
    tabuleiro[1][7].cor = 1;
    tabuleiro[1][7].vivo = true;
    tabuleiro[6][7].tipo = peao;
    tabuleiro[6][7].primeiro_mov = true;
    tabuleiro[6][7].cor = 0;
    tabuleiro[6][7].vivo = true;

    tabuleiro[0][0].tipo = torre;
    tabuleiro[0][0].cor = 1;
    tabuleiro[0][0].vivo = true;
    tabuleiro[0][0].primeiro_mov = true;
    tabuleiro[7][0].tipo = torre;
    tabuleiro[7][0].cor = 0;
    tabuleiro[7][0].vivo = true;
    tabuleiro[7][0].primeiro_mov = true;
    tabuleiro[0][7].tipo = torre;
    tabuleiro[0][7].cor = 1;
    tabuleiro[0][7].vivo = true;
    tabuleiro[0][7].primeiro_mov = true;
    tabuleiro[7][7].tipo = torre;
    tabuleiro[7][7].cor = 0;
    tabuleiro[7][7].vivo = true;
    tabuleiro[7][7].primeiro_mov = true;

    tabuleiro[0][1].tipo = cavalo;
    tabuleiro[0][1].cor = 1;
    tabuleiro[0][1].vivo = true;
    tabuleiro[0][6].tipo = cavalo;
    tabuleiro[0][6].cor = 1;
    tabuleiro[0][6].vivo = true;
    tabuleiro[7][1].tipo = cavalo;
    tabuleiro[7][1].cor = 0;
    tabuleiro[7][1].vivo = true;
    tabuleiro[7][6].tipo = cavalo;
    tabuleiro[7][6].cor = 0;
    tabuleiro[7][6].vivo = true;

    tabuleiro[0][2].tipo = bispo;
    tabuleiro[0][2].cor = 1;
    tabuleiro[0][2].vivo = true;
    tabuleiro[0][5].tipo = bispo;
    tabuleiro[0][5].cor = 1;
    tabuleiro[0][5].vivo = true;
    tabuleiro[7][2].tipo = bispo;
    tabuleiro[7][2].cor = 0;
    tabuleiro[7][2].vivo = true;
    tabuleiro[7][5].tipo = bispo;
    tabuleiro[7][5].cor = 0;
    tabuleiro[7][5].vivo = true;

    tabuleiro[0][4].tipo = rei;
    tabuleiro[0][4].cor = 1;
    tabuleiro[0][4].vivo = true;
    tabuleiro[0][4].primeiro_mov = true;
    tabuleiro[7][4].tipo = rei;
    tabuleiro[7][4].cor = 0;
    tabuleiro[7][4].vivo = true;
    tabuleiro[7][4].primeiro_mov = true;

    tabuleiro[0][3].tipo = rainha;
    tabuleiro[0][3].cor = 1;
    tabuleiro[0][3].vivo = true;
    tabuleiro[7][3].tipo = rainha;
    tabuleiro[7][3].cor = 0;
    tabuleiro[7][3].vivo = true;

    for (int origem_linha = 2; origem_linha < 6; origem_linha++)
    {
        for (int origem_coluna = 0; origem_coluna < 8; origem_coluna++)
        {
            tabuleiro[origem_linha][origem_coluna].tipo = vazio;
            tabuleiro[origem_linha][origem_coluna].cor = -1;
        }
    }
}

void imprimir_tabuleiro()
{
    printf("   0    1    2    3    4    5    6    7\n");
    for (int origem_linha = 0; origem_linha < 8; origem_linha++)
    { printf("%d", origem_linha);
        for (int origem_coluna = 0; origem_coluna < 8; origem_coluna++)
        {
            if (tabuleiro[origem_linha][origem_coluna].cor == 1)
            {
                switch (tabuleiro[origem_linha][origem_coluna].tipo)
                {
                case vazio:
                    printf("  .  ");
                    break;
                case peao:
                    printf("  P  ");
                    break;
                case torre:
                    printf("  T  ");
                    break;
                case cavalo:
                    printf("  C  ");
                    break;
                case bispo:
                    printf("  B  ");
                    break;
                case rainha:
                    printf("  Q  ");
                    break;
                case rei:
                    printf("  K  ");
                    break;
                }
            }
            else if (tabuleiro[origem_linha][origem_coluna].cor == 0)
            {
                switch (tabuleiro[origem_linha][origem_coluna].tipo)
                {
                case vazio:
                    printf("  .  ");
                    break;
                case peao:
                    printf("  p  ");
                    break;
                case torre:
                    printf("  t  ");
                    break;
                case cavalo:
                    printf("  c  ");
                    break;
                case bispo:
                    printf("  b  ");
                    break;
                case rainha:
                    printf("  q  ");
                    break;
                case rei:
                    printf("  k  ");
                    break;
                }
            }
            else
            {
                printf("  .  ");
            }
        }
        printf("\n\n");
    }
}
int caminho_peca_horizontal_vertical(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna)
{
    if(abs(destino_linha - origem_linha) != abs(destino_coluna - origem_coluna))
    {
        if(destino_linha - origem_linha > 0)
        {
            for(int ic = origem_linha + 1; ic < destino_linha; ic++)
            {
                if(tabuleiro[ic][origem_coluna].vivo == 1)
                {
                    return 1;
                }
            }
        }
        else if(destino_linha - origem_linha < 0)
        {
            for(int ic = origem_linha - 1; ic > destino_linha; ic--)
            {
                if(tabuleiro[ic][origem_coluna].vivo == 1)
                {
                    return 1;
                }
            }
        }
        if(destino_coluna - origem_coluna > 0)
        {
            for(int jc = origem_coluna + 1; jc < destino_coluna; jc++)
            {
                if(tabuleiro[origem_linha][jc].vivo == 1)
                {
                    return 1;
                }
            }
        }
        else if(destino_coluna - origem_coluna < 0)
        {
            for (int jc = origem_coluna - 1; jc > destino_coluna; jc--)
            {
                if(tabuleiro[origem_linha][jc].vivo == 1)
                {
                    return 1;
                }
            }
        }
        return 0;
    }
    return 1;
}

int caminho_peca_diagonal(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna)
{
    if (abs(destino_linha - origem_linha) == abs(destino_coluna - origem_coluna)) {
        int dir_i = (destino_linha - origem_linha) > 0 ? 1 : -1;
        int dir_j = (destino_coluna - origem_coluna) > 0 ? 1 : -1;
        for (int ic = origem_linha + dir_i, jc = origem_coluna + dir_j; ic != destino_linha; ic += dir_i, jc += dir_j) {
            if (tabuleiro[ic][jc].vivo == 1) {
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

bool pode_atacar(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna)
{
    peca peca = tabuleiro[origem_linha][origem_coluna];
    int delta_linha = abs(destino_linha - origem_linha);
    int delta_coluna = abs(destino_coluna - origem_coluna);

    switch (peca.tipo)
    {
    case rainha:
        return ((delta_linha == delta_coluna || origem_linha == destino_linha || origem_coluna == destino_coluna) &&
                ((caminho_peca_horizontal_vertical(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0) ||
                 (caminho_peca_diagonal(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0)));
    case torre:
        return ((origem_linha == destino_linha || origem_coluna == destino_coluna) &&
                (caminho_peca_horizontal_vertical(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0));
    case bispo:
        return ((delta_linha == delta_coluna) && (caminho_peca_diagonal(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0));
    case cavalo:
        return (delta_linha == 2 && delta_coluna == 1) || (delta_linha == 1 && delta_coluna == 2);
    case peao:
        return ((tabuleiro[origem_linha][origem_coluna].vivo == tabuleiro[destino_linha][destino_coluna].vivo) &&
                ((origem_linha + 1 == destino_linha) && (origem_coluna + 1 == destino_coluna) ||
                 (origem_linha + 1 == destino_linha) && (origem_coluna - 1 == destino_coluna) ||
                 (origem_linha - 1 == destino_linha) && (origem_coluna + 1 == destino_coluna) ||
                 (origem_linha - 1 == destino_linha) && (origem_coluna - 1 == destino_coluna)));
    case rei:
        return (delta_linha <= 1 && delta_coluna <= 1);
    default:
        return false;
    }
}

bool esta_em_xeque(int rei_linha, int rei_coluna, char cor_rei, int *a_linha, int *a_coluna)
{
    for(int linha = 0; linha < 8; linha++)
    {
        for(int coluna = 0; coluna < 8; coluna++)
        {
            peca peca = tabuleiro[linha][coluna];
            if(peca.tipo != vazio && peca.cor != cor_rei)
            {
                if(pode_atacar(linha, coluna, rei_linha, rei_coluna))
                {
                    *a_linha = linha;
                    *a_coluna = coluna;
                    return true;
                }
            }
        }
    }
    return false;
}

bool pode_bloquear(int linha_rei, int coluna_rei, int linha_atacante, int coluna_atacante, char cor_rei)
{
    int nl, nc;
    int dLinha = (linha_atacante > linha_rei) ? 1 : (linha_atacante < linha_rei) ? -1 : 0;
    int dColuna = (coluna_atacante > coluna_rei) ? 1 : (coluna_atacante < coluna_rei) ? -1 : 0;

    int linha = linha_rei + dLinha;
    int coluna = coluna_rei + dColuna;
    if(tabuleiro[linha_atacante][coluna_atacante].tipo != cavalo) {
        while(linha != linha_atacante || coluna != coluna_atacante) {
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(tabuleiro[i][j].cor == cor_rei && tabuleiro[i][j].tipo != rei) {
                        if(pode_atacar(i, j, linha, coluna)) {
                            peca peca_destino = tabuleiro[linha][coluna];
                            tabuleiro[linha][coluna] = tabuleiro[i][j];
                            tabuleiro[i][j].tipo = vazio;
                            tabuleiro[i][j].vivo = false;

                            if(!esta_em_xeque(linha_rei, coluna_rei, cor_rei, &nl, &nc)) {
                                tabuleiro[i][j] = tabuleiro[linha][coluna];
                                tabuleiro[linha][coluna] = peca_destino;
                                return true;
                            }

                            tabuleiro[i][j] = tabuleiro[linha][coluna];
                            tabuleiro[linha][coluna] = peca_destino;
                        }
                    }
                }
            }
            linha += dLinha;
            coluna += dColuna;
        }
    } else {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(tabuleiro[i][j].cor == cor_rei && tabuleiro[i][j].tipo != rei) {
                    if(pode_atacar(i, j, linha_atacante, coluna_atacante))
                        return true;
                    }
                 }
            }
        }
    return false;
}

bool esta_em_xeque_mate()
{
    int reib_linha, reib_coluna;

    for(int linha = 0; linha < 8; linha++)
    {
        for(int coluna = 0; coluna < 8; coluna++)
        {
            if(tabuleiro[linha][coluna].tipo == rei && tabuleiro[linha][coluna].cor == branco)
            {
                reib_linha = linha;
                reib_coluna = coluna;
                break;
            }
        }
    }

    int reip_linha, reip_coluna;

    for(int linha = 0; linha < 8; linha++)
    {
        for(int coluna = 0; coluna < 8; coluna++)
        {
            if(tabuleiro[linha][coluna].tipo == rei && tabuleiro[linha][coluna].cor == preto)
            {
                reip_linha = linha;
                reip_coluna = coluna;
                break;
            }
        }
    }

    int movimentos[8][2] = {
        {1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}};
    int atacante_linha, atacante_coluna, nl, nc;

    if (esta_em_xeque(reib_linha, reib_coluna, branco, &atacante_linha, &atacante_coluna))
    {
        int local_seguro = 0;
        for(int movimento = 0; movimento < 8; movimento++)
        {
            int nova_linha, nova_coluna;
            nova_linha = reib_linha + movimentos[movimento][0];
            nova_coluna = reib_coluna + movimentos[movimento][1];
            if(nova_linha >= 0 && nova_linha < 8 && nova_coluna >= 0 && nova_coluna < 8 &&
              (tabuleiro[nova_linha][nova_coluna].vivo == false || tabuleiro[nova_linha][nova_coluna].cor != branco) &&
                !esta_em_xeque(nova_linha, nova_coluna, branco, &nl, &nc))
            {
                local_seguro++;
            }
        }

        if(!local_seguro && !pode_bloquear(reib_linha, reib_coluna, atacante_linha, atacante_coluna, branco))
        {
            printf("As brancas estao em xeque mate! Vitoria das pretas!\n");
            return true;
        }
    }
    else if (esta_em_xeque(reip_linha, reip_coluna, preto, &atacante_linha, &atacante_coluna))
    {
        int local_seguro = 0;
        for (int movimento = 0; movimento < 8; movimento++)
        {
            int nova_linha, nova_coluna;
            nova_linha = reip_linha + movimentos[movimento][0];
            nova_coluna = reip_coluna + movimentos[movimento][1];
            if (nova_linha >= 0 && nova_linha < 8 && nova_coluna >= 0 && nova_coluna < 8 &&
                (tabuleiro[nova_linha][nova_coluna].vivo == false || tabuleiro[nova_linha][nova_coluna].cor != preto) &&
                !esta_em_xeque(nova_linha, nova_coluna, preto, &nl, &nc))
            {
                local_seguro++;
            }
        }

        if (!local_seguro && !pode_bloquear(reip_linha, reip_coluna, atacante_linha, atacante_coluna, preto))
        {
            printf("As pretas estao em xeque mate! Vitoria das brancas!\n");
            return true;
        }
    }
    return false;
}

bool verifica_fim_de_jogo()
{
    int reib_linha, reib_coluna, reip_linha, reip_coluna;
    for (int linha = 0; linha < 8; linha++)
    {
        for (int coluna = 0; coluna < 8; coluna++)
        {
            if (tabuleiro[linha][coluna].tipo == rei && tabuleiro[linha][coluna].cor == 1)
            {
                reib_linha = linha;
                reib_coluna = coluna;
            }
        }
    }
    for (int linha = 0; linha < 8; linha++)
    {
        for (int coluna = 0; coluna < 8; coluna++)
        {
            if (tabuleiro[linha][coluna].tipo == rei && tabuleiro[linha][coluna].cor == 0)
            {
                reip_linha = linha;
                reip_coluna = coluna;
            }
        }
    }

    if (!tabuleiro[reib_linha][reib_coluna].vivo)
    {
        printf("O rei branco foi capturado! Fim de jogo!\n\n");
        return true;
    }
    else if (!tabuleiro[reip_linha][reip_coluna].vivo)
    {
        printf("O rei preto foi capturado! Fim de jogo!\n\n");
        return true;
    }
    else if (esta_em_xeque_mate())
    {
        return true;
    }
    else
        return false;
}

void atualizacao_peca(int origem_linha, int origem_coluna, int destino_linha, int destino_coluna)
{
    tabuleiro[destino_linha][destino_coluna].tipo = tabuleiro[origem_linha][origem_coluna].tipo;
    tabuleiro[destino_linha][destino_coluna].cor = tabuleiro[origem_linha][origem_coluna].cor;
    tabuleiro[destino_linha][destino_coluna].vivo = tabuleiro[origem_linha][origem_coluna].vivo;
    tabuleiro[origem_linha][origem_coluna].tipo = vazio;
    tabuleiro[origem_linha][origem_coluna].cor = -1;
    tabuleiro[origem_linha][origem_coluna].vivo = false;
}

int movimento_peca()
{
    int origem_linha, origem_coluna, destino_linha, destino_coluna, y, x;
    scanf("%d %d", &origem_linha, &origem_coluna);
    if (origem_linha < 0 || origem_linha >= 8 || origem_coluna < 0 || origem_coluna >= 8 || tabuleiro[origem_linha][origem_coluna].tipo == vazio)
    {
        printf("Posicao inicial invalida.\n\n");
        return -1;
    }
    scanf("%d %d", &destino_linha, &destino_coluna);
    if (destino_linha < 0 || destino_linha >= 8 || destino_coluna < 0 || destino_coluna >= 8)
    {
        printf("Nova posicao invalida.\n\n");
        return -1;
    }
    if (tabuleiro[origem_linha][origem_coluna].cor == tabuleiro[destino_linha][destino_coluna].cor)
    {
        printf("Movimento invalido.\n\n");
        return -1;
    }
    switch (tabuleiro[origem_linha][origem_coluna].tipo)
    {
    case peao:
        if (tabuleiro[origem_linha][origem_coluna].primeiro_mov)
        {
            if (((tabuleiro[1][origem_coluna].tipo || tabuleiro[6][origem_coluna].tipo) &&
                 (destino_linha == origem_linha + 2 || destino_linha == origem_linha - 2) &&
                 destino_coluna == origem_coluna))
            {
                if (caminho_peca_horizontal_vertical(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0)
                {
                    atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
                    tabuleiro[origem_linha][origem_coluna].primeiro_mov = false;
                }
                else
                {
                    printf("Ha pecas no caminho\n\n");
                    return -1;
                }
            }
            else if (tabuleiro[origem_linha][origem_coluna].vivo != tabuleiro[destino_linha][destino_coluna].vivo &&
                     (destino_linha == origem_linha + 1 || destino_linha == origem_linha - 1) &&
                     destino_coluna == origem_coluna)
            {
                atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
                tabuleiro[origem_linha][origem_coluna].primeiro_mov = false;
            }
            else if ((tabuleiro[origem_linha][origem_coluna].vivo == tabuleiro[destino_linha][destino_coluna].vivo) &&
                     ((origem_linha + 1 == destino_linha) && (origem_coluna + 1 == destino_coluna) ||
                      (origem_linha + 1 == destino_linha) && (origem_coluna - 1 == destino_coluna) ||
                      (origem_linha - 1 == destino_linha) && (origem_coluna + 1 == destino_coluna) ||
                      (origem_linha - 1 == destino_linha) && (origem_coluna - 1 == destino_coluna)))
            {
                atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
                tabuleiro[origem_linha][origem_coluna].primeiro_mov = false;
                if (destino_linha == 7 || destino_linha == 0)
                {
                    int tipo_peca = 1;
                    printf("Parabens, seu peao chegou ao fim do tabuleiro, digite o numero equivalente a peca na qual ele ira se tornar\n");
                    printf("1 peao, 2 cavalo, 3 torre, 4 bispo, 5 rainha\n");
                    scanf("%d", &tipo_peca);
                    tabuleiro[destino_linha][destino_coluna].tipo = tipo_peca;
                }
            }
            else
            {
                printf("Use o peao corretamente.\n\n");
            }
        }
        else
        {
            if (tabuleiro[origem_linha][origem_coluna].vivo != tabuleiro[destino_linha][destino_coluna].vivo &&
                (destino_linha == origem_linha + 1 || destino_linha == origem_linha - 1) &&
                destino_coluna == origem_coluna)
            {
                atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
                if (destino_linha == 7 || destino_linha == 0)
                {
                    int tipo_peca = 1;
                    printf("Parabens, seu peao chegou ao fim do tabuleiro, digite o numero equivalente a peca na qual ele ira se tornar\n");
                    printf("1 peao, 2 cavalo, 3 torre, 4 bispo, 5 rainha\n");
                    scanf("%d", &tipo_peca);
                    tabuleiro[destino_linha][destino_coluna].tipo = tipo_peca;
                }
            }
            else if ((tabuleiro[origem_linha][origem_coluna].vivo == tabuleiro[destino_linha][destino_coluna].vivo) &&
                     ((origem_linha + 1 == destino_linha) && (origem_coluna + 1 == destino_coluna) ||
                      (origem_linha + 1 == destino_linha) && (origem_coluna - 1 == destino_coluna) ||
                      (origem_linha - 1 == destino_linha) && (origem_coluna + 1 == destino_coluna) ||
                      (origem_linha - 1 == destino_linha) && (origem_coluna - 1 == destino_coluna)))
            {
                atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
                if (destino_linha == 7 || destino_linha == 0)
                {
                    int tipo_peca = 1;
                    printf("Parabens, seu peao chegou ao fim do tabuleiro, digite o numero equivalente a peca na qual ele ira se tornar\n");
                    printf("1 peao, 2 cavalo, 3 torre, 4 bispo, 5 rainha\n");
                    scanf("%d", &tipo_peca);
                    tabuleiro[destino_linha][destino_coluna].tipo = tipo_peca;
                }
            }
            else
            {
                printf("Use o peao corretamente.\n\n");
                return -1;
            }
        }
        break;

    case torre:
        if (origem_linha != destino_linha && origem_coluna != destino_coluna)
        {
            printf("Use a torre corretamente.\n\n");
            return -1;
        }
        else if (caminho_peca_horizontal_vertical(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0)
        {
            atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
        }
        else
        {
            printf("Ha pecas no caminho\n\n");
            return -1;
        }
        break;
    case cavalo:
        if ((destino_linha == origem_linha + 1 || destino_linha == origem_linha - 1) && (destino_coluna == origem_coluna + 2 || destino_coluna == origem_coluna - 2) || (destino_linha == origem_linha + 2 || destino_linha == origem_linha - 2) && (destino_coluna == origem_coluna + 1 || destino_coluna == origem_coluna - 1))
        {
            atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
        }
        else
        {
            printf("Use o cavalo corretamente.\n\n");
            return -1;
        }
        break;
    case bispo:
        y = origem_linha - destino_linha;
        x = origem_coluna - destino_coluna;
        if ((x == y || x == -y) && (destino_linha != origem_linha && destino_coluna != origem_coluna))
        {
            if (caminho_peca_diagonal(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0)
            {
                atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
            }
            else
            {
                printf("Ha pecas no caminho\n\n");
                return -1;
            }
        }
        else
        {
            printf("Use o bispo corretamente.\n\n");
            return -1;
        }
        break;
    case rainha:
        y = origem_linha - destino_linha;
        x = origem_coluna - destino_coluna;
        if ((x == y || x == -y) && (destino_linha != origem_linha && destino_coluna != origem_coluna))
        {
            if (caminho_peca_diagonal(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0)
            {
                atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
            }
            else
            {
                printf("Ha pecas no caminho\n\n");
                return -1;
            }
        }
        else if ((destino_linha != origem_linha && destino_coluna == origem_coluna) || (destino_linha == origem_linha && destino_coluna != origem_coluna))
        {
            if (caminho_peca_horizontal_vertical(origem_linha, origem_coluna, destino_linha, destino_coluna) == 0)
            {
                atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
            }
            else
            {
                printf("Ha pecas no caminho\n\n");
                return -1;
            }
        }
        else
        {
            printf("Use a rainha corretamente.\n\n");
            return -1;
        }
        break;
    case rei:
        if ((destino_coluna == origem_coluna + 1 || destino_coluna == origem_coluna - 1 || destino_coluna == origem_coluna) && (destino_linha == origem_linha + 1 || destino_linha == origem_linha - 1 || destino_linha == origem_linha))
        {

            atualizacao_peca(origem_linha, origem_coluna, destino_linha, destino_coluna);
        }
        else
        {
            printf("Use o rei corretamente.\n\n");
            return -1;
        }

        break;
    default:
        printf("Peca selecionada nao pode ser movida.\n\n");
        return -1;
    }
    /*
        =============================================================================
        COISAS A FAZER NA FUNcaO movimento_peca()
            movimento roque
        =============================================================================
    */
}
