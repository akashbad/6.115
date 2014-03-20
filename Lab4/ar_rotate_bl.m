function y = ar_rotate_bl(matrix,angle)
%AR_ROTATE_BL  Function that rotates a matrix by a set of angles
%  
%  AR_ROTATE_BL takes a matrix of projections and a row vector of angles and rotates
%  the projections about the given set of angles
%  
%  This version employs a bilinear interpolation method to improve image resolution
%  and accuracy
%
%  Ariel Rodriguez
%  MIT LEES
%  July 2003
%
% See also SPIN_DUDE, INV_RADON
[rows,cols]=size(matrix);
% Finds center of the matrix to be rotated
row_c = .5*rows + .5;
col_c = .5*cols + .5;

[length,width]=size(angle);

for h=1:width % Loop through each angle of rotation
    y=[];
    for i = 1:rows
        old_rows=[];
        for j = 1:cols
            row_old = (i-row_c)*cos(angle(h)*(pi/180)) + (j-col_c)*sin(angle(h)*(pi/180)) + row_c; % What row coordinate in the given matrix should be in the current position in the rotated matrix
            col_old = -(i-row_c)*sin(angle(h)*(pi/180)) + (j-col_c)*cos(angle(h)*(pi/180)) + col_c; % Same as above but the column coordinate
            
            % Determine the columns and rows that define the square around point with the row and column coordinates from above
            right_col = ceil(col_old); % Rightmost column to the point
            left_col = floor(col_old); % Leftmost column to the point
            top_row = floor(row_old); % Top row to the point
            bottom_row = ceil(row_old);% Bottom row to the point

            % Define four points surrounding the point in question by the rows and columns in the square, take care of boundary problems
            if (right_col == left_col)
                left_col = right_col - 1;
            end
            if (bottom_row == top_row)
                top_row = bottom_row - 1;
            end

            % More cleanup for rotations that place points outside the boundaries of the image matrix    
            if or(top_row<=0,top_row>rows)
                    top_left = 0;
                else    if or(left_col<=0, left_col>rows)
                        top_left = 0;
                        else top_left = matrix(top_row,left_col);
                        end
            end
                
            if or(top_row<=0,top_row>rows)
                    top_right = 0;
                else    if or(right_col<=0, right_col>rows)
                        top_right = 0;
                        else top_right = matrix(top_row, right_col);
                        end
            end
                
            if or(bottom_row<=0,bottom_row>rows)
                    bottom_right = 0;
                else    if or(right_col<=0, right_col>rows)
                        bottom_right = 0;
                        else bottom_right = matrix(bottom_row,right_col);
                        end
            end
                
            if or(bottom_row<=0,bottom_row>rows)
                    bottom_left = 0;
                else    if or(left_col<=0, left_col>rows)
                        bottom_left = 0;
                        else bottom_left = matrix(bottom_row,left_col);
                        end
            end
                
                
            % Interpolate by using the distance of the point from the right most column and top most row, I split this up into two column variables for ease of debugging
            col_interp1 = (right_col - col_old)*((bottom_row - row_old)*top_left + (row_old - top_row)*bottom_left);
            col_interp2 = (col_old - left_col)*((bottom_row - row_old)*top_right + (row_old-top_row)*bottom_right);

            % Compute new value from interpolated results
            old_value = col_interp1 + col_interp2;

            % Concatenate each value from the given matrix into the current row
            old_rows=horzcat(old_rows,old_value);
        end
        
        % Concatenate the rows
        y=vertcat(y,old_rows);
    end
end