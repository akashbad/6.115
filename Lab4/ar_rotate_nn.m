function y = ar_rotate(matrix,angle)

[rows,cols]=size(matrix);

% Finds center of the matrix to be rotated
row_c = .5*rows + .5;
col_c = .5*cols + .5;

[length,width]=size(angle);

% Find how many angles to rotate through
no_angles = width

for h=1:width
    y=[];
    for i = 1:rows
        old_rows=[];
        for j = 1:cols
            row_old = round((i-row_c)*cos(angle(h)*(pi/180)) + (j-col_c)*sin(angle(h)*(pi/180)) + row_c) % Grab nearest row from the given matrix
            col_old = round(-(i-row_c)*sin(angle(h)*(pi/180)) + (j-col_c)*cos(angle(h)*(pi/180)) + col_c) % Grab nearest column from the given matrix
            if or(row_old>rows,row_old<=0)
                old_value=1; % If rows are out of bounds (negative or >15) set old value to one (white)
            elseif or(col_old>cols,col_old<=0)
                old_value=1; % Same thing for columns
            else
                old_value = matrix(row_old,col_old); % If everything is in bound, grab the matrix value at the calculated coordinates
            end
            old_rows=horzcat(old_rows,old_value); % Concatenate to form a row of values
        end
        y=vertcat(y,old_rows); % Concatenate the rows to make the image
    end
end
