function y = inv_radon(mat,angles,calib)

%ARI_INV_RADON  Performs the inverse radon transform of a matrix of projections
%  
%  ARI_INV_RADON takes a matrix of projections and a row vector of angles and rotates
%  the projections back to reconstruct the cross section of an object
%  
%  This version employs an image rotation function developed at LEES
%
%
%  Ariel Rodriguez
%  MIT LEES
%  July 2003
%
% See also SPIN_DUDE, AR_INTERP_BL
% snag the width of the matrix, in this case 24 measurements

[rows, cols] = size(mat);
n = cols;
img = ones(rows,rows); %sets up the empty image matrix, should be all white in the color map


% Primary loop
for i= 1:n
    g = mat(:,i); 
    h = [];
    for j = 1:rows % takes each column and expands it into a 15x15 matrix
        h = horzcat(h,g);
    end
    exp_vect= h;
    rot_vector = ar_rotate_bl(exp_vect,-angles(i)); % rotates with bilinear interpolation
    img = img + rot_vector ;% add the column back into the image matrix
end

img2 = img/rows; % Takes average of all elements in the matrix (useful for digitizing the picture later

% make image
figure(1)
colormap(gray)
imagesc(img2)
axis square