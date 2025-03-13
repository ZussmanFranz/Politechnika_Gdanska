function [index_number, Edges, I, B, A, b, r] = page_rank()
    index_number = 201253;  
    N = 7;
    Edges = [ 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7;
              4, 6, 3, 4, 5, 5, 6, 7, 4, 5, 6, 4, 6, 4, 7, 6, 4];
    d = 0.85;  % współczynnik tłumienia
    % macierz jednostkowa o wymiarze N (macierz rzadka powinna być zdefiniowana za pomocą funkcji speye)
    I = speye(N); 
    % macierz sąsiedztwa (macierz rzadka powinna być zdefiniowana za pomocą funkcji sparse – zastosuj wywołanie z pięcioma argumentami)
    B = sparse(Edges(2,:), Edges(1,:), ones(1, size(Edges,2)), N, N); % 
    outlinks = sum(B, 1)'; % wektor kolumnowy o rozmiarze N x 1
    % macierz diagonalna (macierz rzadka powinna być zdefiniowana za pomocą funkcji spdiags – zastosuj wywołanie z czterema argumentami)
    A = spdiags(1./outlinks, 0, N, N); %

    % b – wektor prawych stron równania (macierz gęsta)
    b = ones(N, 1) * ((1-d)/N);

    M = I - d * B * A;
    r = M \ b;

    bar(r);
    title('PageRank');
    xlabel('Page number');
    ylabel('PageRank value');
    
end
