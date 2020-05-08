
% close all;
% clc
clear
% id = 6;

% subf1 = 'OneDrive_1_9-26-2019\248_rtklib\';
subf1 = 'OneDrive_1_9-26-2019\248_openrtk\';
subf2 = 'float_openrtk\';

dataset_tag = 'Tesla';

for id = 1:7
    if id == 1
        fname1 = 'm8_008379_2019-09-05T17-41-08_sat_diff_000000_000000.txt';
        fname2 = 'rtk_gg_379.pos_diff_000000_000000.txt';
        sol = load(['.\', subf1, fname1]);
        sol_spp = load(['.\', subf2, fname2]);

        ss = strsplit(fname1, '_diff');
        dataset_tag = ss(1);
        dataset_tag = strrep(dataset_tag, '_', '-');

        idx = 1:length(sol);
        idx_spp = 1:length(sol_spp);
    elseif id == 2
        fname1 = 'm8_008380_2019-09-05T18-28-32_sat_diff_000000_000000.txt';
        fname2 = 'rtk_gg_380.pos_diff_000000_000000.txt';

        sol = load(['.\', subf1, fname1]);
    %     idx = find(sol(:, 1) > 414900 & sol(:, 1) < 415640);
        sol_spp = load(['.\', subf2, fname2]);
    %     sol_rtklib = load('.\OneDrive_1_9-26-2019\248_rtklib\m8_008381_2019-09-05T19-14-37_diff_000000_000000.txt');
        ss = strsplit(fname1, '_diff');
        dataset_tag = ss(1);
        dataset_tag = strrep(dataset_tag, '_', '-');

        idx = 1:length(sol);
        idx_spp = 1:length(sol_spp);

    elseif id == 3 % m8-3
        %% opensky
        fname1 = 'm8_008381_2019-09-05T19-14-37_sat_diff_000000_000000.txt';
        fname2 = 'rtk_gg_381.pos_diff_000000_000000.txt';

        sol = load(['.\', subf1, fname1]);
    %     idx = find(sol(:, 1) > 414900 & sol(:, 1) < 415640);
        sol_spp = load(['.\', subf2, fname2]);
    %     sol_rtklib = load('.\OneDrive_1_9-26-2019\248_rtklib\m8_008381_2019-09-05T19-14-37_diff_000000_000000.txt');
        ss = strsplit(fname1, '_diff');
        dataset_tag = ss(1);
        dataset_tag = strrep(dataset_tag, '_', '-');

    %     sol = load('.\248_openrtk\f9_190905_181418_DC-SF_sat_diff_414900_415640.txt');
    %     sol_spp = load('.\248_spp\f9_190905_181418_DC-SF_diff_414900_415640.txt');
    % 
    %     sol = load('.\248_openrtk\st_190905_DC-SF_sat_diff_414900_415640.txt');
    %     sol_spp = load('.\248_spp\st_190905_DC-SF_diff_414900_415640.txt');

        idx = 1:length(sol);
        idx_spp = 1:length(sol_spp);
    elseif id == 4
        fname1 = 'm8_008382_2019-09-05T20-00-31_sat_diff_000000_000000.txt';
        fname2 = 'rtk_gg_382.pos_diff_000000_000000.txt';

        sol = load(['.\', subf1, fname1]);
    %     idx = find(sol(:, 1) > 414900 & sol(:, 1) < 415640);
        sol_spp = load(['.\', subf2, fname2]);
    %     sol_rtklib = load('.\OneDrive_1_9-26-2019\248_rtklib\m8_008381_2019-09-05T19-14-37_diff_000000_000000.txt');
        ss = strsplit(fname1, '_diff');
        dataset_tag = ss(1);
        dataset_tag = strrep(dataset_tag, '_', '-');

    %      sol = load('.\248_openrtk\f9_190905_181418_DC-SF_sat_diff_000000_000000.txt');
    %     sol_spp = load('.\248_spp\f9_190905_181418_DC-SF_diff_000000_000000.txt');

    %     sol = load('.\248_openrtk\st_190905_DC-SF_sat_diff_416140_419010.txt');
    %     sol_spp = load('.\248_spp\st_190905_DC-SF_diff_416140_419010.txt');

        idx = 1:length(sol);
        idx_spp = 1:length(sol_spp);
    elseif id == 5 % m8-5
        fname1 = 'm8_008383_2019-09-05T20-49-50_sat_diff_000000_000000.txt';
        fname2 = 'rtk_gg_383.pos_diff_000000_000000.txt';

        sol = load(['.\', subf1, fname1]);
    %     idx = find(sol(:, 1) > 414900 & sol(:, 1) < 415640);
        sol_spp = load(['.\', subf2, fname2]);
    %     sol_rtklib = load('.\OneDrive_1_9-26-2019\248_rtklib\m8_008381_2019-09-05T19-14-37_diff_000000_000000.txt');
        ss = strsplit(fname1, '_diff');
        dataset_tag = ss(1);
        dataset_tag = strrep(dataset_tag, '_', '-');

    %     sol = load('.\248_openrtk\f9_190905_210831_Oakland-Hayward_sat_diff_421450_422610.txt');
    %     sol_spp = load('.\248_spp\f9_190905_210831_Oakland-Hayward_diff_421450_422610.txt');

    %      sol = load('.\248_openrtk\st_190905_Oakland-Hayward_sat_diff_421450_422610.txt');
    %     sol_spp = load('.\248_spp\st_190905_Oakland-Hayward_diff_421450_422610.txt');

        idx = 1:length(sol);
        idx_spp = 1:length(sol_spp);
    elseif id == 6
        fname1 = 'm8_008384_2019-09-05T21-35-09_sat_diff_000000_000000.txt';
        fname2 = 'rtk_gg_384.pos_diff_000000_000000.txt';

        sol = load(['.\', subf1, fname1]);
    %     idx = find(sol(:, 1) > 414900 & sol(:, 1) < 415640);
        sol_spp = load(['.\', subf2, fname2]);
    %     sol_rtklib = load('.\OneDrive_1_9-26-2019\248_rtklib\m8_008381_2019-09-05T19-14-37_diff_000000_000000.txt');
        ss = strsplit(fname1, '_diff');
        dataset_tag = ss(1);
        dataset_tag = strrep(dataset_tag, '_', '-');

        idx = 1:length(sol);
        idx_spp = 1:length(sol_spp);
    elseif id == 7
        fname1 = 'm8_008385_2019-09-05T22-20-09_sat_diff_000000_000000.txt';
        fname2 = 'rtk_gg_385.pos_diff_000000_000000.txt';

        sol = load(['.\', subf1, fname1]);
    %     idx = find(sol(:, 1) > 414900 & sol(:, 1) < 415640);
        sol_spp = load(['.\', subf2, fname2]);
    %     sol_rtklib = load('.\OneDrive_1_9-26-2019\248_rtklib\m8_008381_2019-09-05T19-14-37_diff_000000_000000.txt');
        ss = strsplit(fname1, '_diff');
        dataset_tag = ss(1);
        dataset_tag = strrep(dataset_tag, '_', '-');

        idx = 1:length(sol);
        idx_spp = 1:length(sol_spp);
    end

    hor_col = 8;

    % hold on
    hf = figure; 
    [h1, stat1] = cdfplot(abs(sol(idx,hor_col)));
    % legend(gca, 'rtklib')
    hold on
    % figure
    [h2, stat2] = cdfplot(abs(sol_spp(idx_spp,hor_col)));
    % legend(gca, 'openrtk')
    % figure;
    % [h3, stat3] = cdfplot(abs(sol_rtklib(:,hor_col)));

    % xlim(gca, [0 2]);
    xlabel(gca, 'error (m)')
    legend(gca, {'OpenRTK', 'mrtklib'})
    title(gca, ['Aceinna RTK: ', dataset_tag]);
    savefig(hf, [subf2, dataset_tag{1}]);


    % Y = prctile(abs(sol), [68, 95, 99.5], 1)
    % 
    % Yspp = prctile(abs(sol_spp), [68, 95, 99.5], 1)


    figure; hold on
    plot(sol(idx, 1), sol(idx, 8), 'b.-');
    plot(sol_spp(idx_spp, 1), sol_spp(idx_spp, 8), 'r.-');
    ylim(gca, [0, 2])
end
% plot(sol(idx, 1), sol(idx, 6), 'g.-');
% disp('openrtk stat: \n');
% rms(sol(idx, [8 7]));
% 
% Y = prctile(abs(sol(idx, [8 7])), [68, 95, 99.7], 1)'
% 
% 
% figure; hold on
% plot(sol_spp(idx_spp, 1), sol_spp(idx_spp, 5), 'b.-');
% plot(sol_spp(idx_spp, 1), sol_spp(idx_spp, 6), 'g.-');
% plot(sol_spp(idx_spp, 1), sol_spp(idx_spp, 7), 'r.-');
% disp('spp stat: \n');
% rms(sol_spp(idx_spp,[8 7]));
% Yspp = prctile(abs(sol_spp(idx_spp, [8 7])), [68, 95, 99.7], 1)'

%% residential



%% deep urban

