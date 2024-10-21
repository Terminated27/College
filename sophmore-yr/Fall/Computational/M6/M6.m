% *** Aidan Chin, 9/22/23

% *** Aidan Chin, 11/08/2023, Updated for M6 ***

    %   *** Label carts from left to right as 1, 2, 3
    %   *** Label "collisions" A, B, C, etc. until everything is final
    %   *** do not use loops or functions
    %   *** use arrays to keep track of everything
    %   *** Formulas from M1, http://hyperphysics.phy-astr.gsu.edu/hbase/elacol2.html
    %   *** This code tracks the number of collisions between 3 objects in
    %   *** 1D elastic collision

clear

% ----- Getting Started -----

% givens

m = [ input('input mass of cart 1 (g): ') ...
        input('input mass of cart 2 (g): ') ...
        input('input mass of cart 3 (g): ') ]; 
        % mass of cars in g from left to right

v = [ input('input velocity of cart 1 (m/s): ') ...
        input('input velocity of cart 2 (m/s): ') ...
        input('input velocity of cart 3 (m/s): ') ]; 
        % velocity of cars in cm/s from left to right

threshold = input('please specify an error threshold: ');
        % error threshold where simulation will end

% check which cart collides first with cart 2

if abs(v(1)-v(2)) == abs(v(2)+v(3)) % if ambiguous, promps user to specify
    hit = input(['the first collision is ambiguous, please specify which ' ...
        'cart collides with card 2 first: ']);
elseif abs(v(1)-v(2)) > abs(v(2)+v(3)) % cart 1 collides first
    hit = 1; % set cart hit next to 1
elseif abs(v(1)-v(2)) < abs(v(2)+v(3)) % cart 3 collides first
    hit = 3; % set cart hit next to 3
end

% set up total masses for two types of collisions

m23 = m(2) + m(3); % total mass of carts 2 and 3 in g
m12 = m(1) + m(2); % total mass of carts 1 and 2 in g

% set up the checks by computing total energy and momentum

KE0 = sum(.5.*m.*v.^2); %calculates the total kenetic energy initially
P0 = sum(m.*v);         %calculates the total potential energy initially

c = 0; % set up counter for number of collisions

while v(1) > v(2) || v(3) < v(2) % loop if carts continue to collide

    if hit == 3 % checks if carts 2 and 3 will collide
        fprintf('carts 2 and 3 will collide\n') % state situation

        vR = [ 0 0 0 ];   % initialize vR
        
        vR(1) = v(1);  %no interaction - velocity of cart 1 remains constant in cm/s

        vR(2) = (m(2)-m(3))/m23*v(2) + 2*m(3)/m23*v(3); %resultant velocity of 
                                                            %cart 2 in cm/s 
        vR(3) = 2*m(2)/m23*v(2) - (m(2)-m(3))/m23*v(3); %resultant velocity of 
                                                            %cart 3 in cm/s
        
        fprintf(['after collision number %d the resultant velocity vector is' ...
            ' [ %d %d %d ]\n'], c, vR)
        %print the collision number and resultant velocity

        % check energy and momentum (expectations) 
        
        KER = sum(.5.*m.*vR.^2);%calculates the total kinetic energy of situation
        checkKE = KER-KE0; % Should be zero because no kenetic energy 
                                            % is added or removed
        PR = sum(m.*vR); %calculates the total potential energy of situation                                         
        checkP_B = PR-P0;          % should be zero because no potential energy
                                            % added or removed
                  
        % checks if error threshold has been reached
        if abs(checkP_B) > threshold || abs(checkKE) > threshold
            fprintf(['threshold has been reached, terminating simulation \n ' ...
                'Potential energy check: %d \n Kinetic energy check: %d \n' ...
                ],checkP_B, checkKE)
            break
            %state the threshold has been reached, and tell user the
            %simulation is terminated
        end
        hit = 1; %set next cart to be hit as 1
    elseif hit == 1 % checks if carts 1 and 2 will collide
        fprintf('carts 1 and 2 will collide\n')

        vR = [ 0 0 0 ]; % initialize vR
        
        vR(1) = (m(1)-m(2))/m12*v(1) + (2*m(2))/m12*v(2); %resultant velocity of 
                                                            %cart 1 in cm/s 
        vR(2) = (2*m(1)/m12)*v(1) - (m(1)-m(2))/m12*v(2); %resultant velocity of 
                                                            %cart 2 in cm/s 
        vR(3) = v(3); %no interaction - velocity of cart 3 remains constant in cm/s
        
        fprintf(['after collision number %d the resultant velocity vector is' ...
            ' [ %d %d %d ]\n'], c, vR) 
        %print the collision number and resultant velocity

        % check energy and momentum (expectations) 
        
        KER = sum(.5.*m.*vR.^2);%calculates the total kinetic energy of situation
        checkKE = KER-KE0; % Should be zero because no kenetic energy 
                                            % is added or removed
        PR = sum(m.*vR); %calculates the total potential energy of situation                                         
        checkP_B = PR-P0;          % should be zero because no potential energy
                                            % added or removed
       
        % checks if error threshold has been reached
        if abs(checkP_B) > threshold || abs(checkKE) > threshold
            fprintf(['threshold has been reached, terminating simulation \n ' ...
                'Potential energy check: %d \n Kinetic energy check: %d \n' ...
                ],checkP_B, checkKE)
            break
            %state the threshold has been reached, and tell user the
            %simulation is terminated
        end
        hit = 3; %set next cart to be hit as 3
    end
    try % in case there are no collisions, vR wont exist, therefore 
        % set a catch condition
        v = vR;
        c = c + 1;
    catch % if there are no collisions just exit loop
        break
    end
end
try %if there are no collisoins, vR wont exist, therefore set a catch condition
    fprintf(['after all collisions the resultant velocity vector is' ...
            ' [ %d %d %d ]\nThere are no more collisions\n'], vR) 
catch % say different message if carts never collide
    fprintf(['the carts will never collide the resultant velocity vector is' ...
            ' [ %d %d %d ]\n'], v) 
end